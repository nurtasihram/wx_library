#include <iostream>

#include "wx_console.h"
#include "wx_realtime.h"

#include "wx_duk.h"

using namespace WX;

#pragma region Memory Management
static int duk_alloc_count = 0;
static Heap duk_mem_heap = Heap::Create();
static void *duk_alloc(void *udata, duk_size_t size) {
	(void)udata;
	if (!size)
		return O;
	duk_alloc_count++;
	return duk_mem_heap.Alloc(size, HeapAllocFlag::GenerateExceptions);
}
static void duk_free(void *udata, void *ptr) {
	(void)udata;
	if (!ptr)
		return;
	duk_alloc_count--;
	duk_mem_heap.Free(ptr);
}
static void *duk_realloc(void *udata, void *ptr, duk_size_t size) {
	if (!ptr)
		return duk_alloc(udata, size);
	if (!size) {
		duk_free(udata, ptr);
		return O;
	}
	return duk_mem_heap.Realloc(ptr, size);
}
static void duk_onfatal(void *udata, const char *msg) {
	throw duk_exception{ msg };
}
static duk_ret_t print_mem(duk_context * = O) {
	auto &&sum = duk_mem_heap.Summaries();
	Console.Log(
		_T("   Allocated: "), sum.Allocated(),
		_T("\n   Committed: "), sum.Committed(),
		_T("\n   Count: "), duk_alloc_count, _T("\n"));
	return 0;
}
#pragma endregion

static bool bEcho = true;
static bool bExit = false;
static bool bCmdl = false;
static bool bReset = false;

Event proc_ok = Event::Create().AutoReset();
static constexpr auto WX_DUK_ON_CMD = WM_USER + 1;

static UINT duk_cmdl_count = 0;

static duk_ret_t cmd_exe(duk_context *ctx) {
	auto lpszCode = duk_require_string(ctx, 0);
	duk_size_t szCode = duk_get_length(ctx, 0);
	duk_compile_lstring(ctx, DUK_COMPILE_SHEBANG, lpszCode, szCode);

	duk_push_global_object(ctx);  /* 'this' binding */
	duk_call_method(ctx, 0);

	if (bEcho && !duk_is_undefined(ctx, -1)) {
		auto lpsz = duk_to_string(ctx, -1);
		Console.LogA(lpsz, '\n');
		//duk_get_global_string(ctx, "print");
		//duk_dup(ctx, -2);
		//duk_call(ctx, 1);
	}

	return 0;
}

static duk_ret_t cmd_prc(duk_context *ctx) {
	++duk_cmdl_count;
	Console.Log(_T("\n -- JavaScript --\n"));
	proc_ok.Set();
_ret:
	Msg msg;
	try {
		while (msg.Get()) {
			if (msg.Window()) {
				msg.Translate();
				msg.Dispatch();
			}
			elif (msg.ID() == WX_DUK_ON_CMD) {
				duk_get_global_string(ctx, "cmd_exe");
				duk_push_string(ctx, msg.ParamW<LPCSTR>());
				auto rc = duk_pcall(ctx, 1);
				if (rc != DUK_EXEC_SUCCESS) {
					duk_dup(ctx, -1);
					duk_put_global_string(ctx, "LastError");
					duk_errout(ctx, "%s\n", duk_safe_to_stacktrace(ctx, -1));
				}
				if (bReset) {
					Console.Log(_T("reset\n"));
					--duk_cmdl_count;
					return 0;
				}
				if (bExit) {
					Console.Log(_T("exit\n\n"));
					--duk_cmdl_count;
					return 0;
				}
				if (bCmdl) {
					bCmdl = false;
					do {
						bReset = false;
						duk_get_global_string(ctx, "cmd_prc");
						duk_call(ctx, 0);
						duk_pop(ctx);
					} while (bReset);
					continue;
				}
				proc_ok.Set();
			}
		}
		--duk_cmdl_count;
		proc_ok.Set();
		return 0;
	} catch (duk_exception err) {
		duk_errout(ctx, "Duktape Exception: \n%s" ,err.msg);
		proc_ok.Set();
	} catch (Exception err) {
		duk_errout(ctx, "WX Exception: \n%s", (LPCSTR)err.toStringA());
		proc_ok.Set();
	} catch (const std::exception &err) {
		duk_errout(ctx, "C++ Exception: \n%s", err.what());
		proc_ok.Set();
	} catch (...) {
		Console.Err(_T("Other exception\n"));
		proc_ok.Set();
		bExit = true;
		return 0;
	}
	goto _ret;
}

duk_ret_t load_duk_cmdl(duk_context *ctx, void *) {
	duk_push_global_object(ctx);
	duk_add_prop(ctx, "echo",
		duk_fn {
			bEcho = duk_to_boolean(ctx, 0);
			return 0;
		},
		duk_fn {
			duk_push_boolean(ctx, bEcho);
			return 1;
		}
	);
	duk_put_prop_r(ctx, "exit", duk_fn {
		bExit = true;
		return 0;
	});
	duk_put_prop_r(ctx, "cmdl", duk_fn {
		bCmdl = true;
		return 0;
	});
	duk_put_prop_r(ctx, "reset", duk_fn {
		bReset = true;
		return 0;
	});
	duk_put_prop_r(ctx, "clear", duk_fn {
		Console.Clear();
		return 0;
	});
	duk_push_undefined(ctx);
	duk_put_prop_string(ctx, -2, "LastError");
	duk_add_method(ctx, "print_mem", 0, print_mem);
	duk_add_method(ctx, "cmd_prc", 0, cmd_prc);
	duk_add_method(ctx, "cmd_exe", 1, cmd_exe);
	return 0;
}

class BaseOf_Window(DukWindow) {
	SFINAE_Window(DukWindow);
public:
	DukWindow() {}
public:
	inline void OnDestroy() {}
};

static duk_context *ctx = O;
LThread cmd_prc_thr = [] {
	//DukWindow duk_win;
	//assertl(duk_win.Create().Size({ 500, 300 }));
	//duk_win.Text(_T("DukWindow"));
	//duk_win.Show();
	//duk_push_new_cclass(ctx, "Window", duk_win);
	//duk_put_global_string(ctx, "test_win");
__reset:
	duk_get_global_string(ctx, "cmd_prc");
	duk_call(ctx, 0);
	duk_pop(ctx);
	duk_gc(ctx, 0);
	if (bReset) {
		bReset = false;
		goto __reset;
	}
	proc_ok.Set();
};

void duk_add_flags(duk_context *ctx,
				   const char *name, const char *parent_name,
				   duk_c_function add_const,
				   duk_c_function toString) {
	static duk_c_function _toString = toString;
	duk_add_class(
		ctx, name, parent_name,
		duk_structure {
			duk_add_method(ctx, "toString", 0, _toString);
			return 0;
		},
		duk_constructor {
			if (duk_reflect_constructor(ctx))
				return 1;
			auto val = duk_to_int(ctx, 0);
			duk_push_this(ctx);
			duk_int_prop(ctx, "val", val);
			return 0;
		},
		add_const
	);
}

void commandline(duk_context *ctx) {
	duk_push_global_object(ctx);
	using EnumClass = SW;

	duk_add_flags(
		ctx, EnumClass::__NameA, O,
		duk_fn {
			constexpr auto map = EnumTableA<EnumClass>;
			for (size_t i = 0; i < EnumClass::Count; ++i) {
				StringA key = map[i].key;
				duk_push_lstring(ctx, key, key.Length());
				duk_push_uint(ctx, EnumClass::__Vals[i]);
				duk_def_prop(ctx, -3, DUK_DEFPROP_PUBLIC_CONST);
			}
			return 0;
		},
		duk_fn {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "val");
			auto &&str = EnumClassParseA(small_cast<EnumClass>(duk_to_uint(ctx, -1)));
			duk_push_lstring(ctx, str, str.Length());
			return 1;
		}
	);

	//duk_load_library(ctx, load_duk_windows);
	duk_load_library(ctx, load_duk_cmdl);

	//duk_eval_string(ctx, "Console.Reopen()");
	Console.Log(_T("\n - Duktape symbols loaded -\n"));
	print_mem();

	assertl(cmd_prc_thr.Create());
	proc_ok.WaitForSignal();

	while (duk_cmdl_count) {
		// print prompt
		auto &&cur_pos = Console.CursorPosition();
		++cur_pos.x;
		Console.Fill(_T('>'), duk_cmdl_count, cur_pos);
		cur_pos.x += duk_cmdl_count + 1;
		Console.CursorPosition(cur_pos);
		// read input
		char js_code[1024]{ 0 };
		std::cin.getline(js_code, sizeof(js_code));
		// process input
		if (!cmd_prc_thr.StillActive()) {
			Console.Log(_T("Message procedurer had exited\n"));
			break;
		}
		cmd_prc_thr.Post(WX_DUK_ON_CMD, js_code);
		proc_ok.WaitForSignal();
	}
}

int main() {
	Console.Log(_T("Compilation Information:\n") COMPILATION_INFO);

	Console.Log(_T("\n -- Duktape x WindowX --\n\n"));

	ctx = duk_create_heap(duk_alloc, duk_realloc, duk_free, O, duk_onfatal);
	Console.Log(_T("\n - Duktape heap craeted -\n"));
	print_mem();

	commandline(ctx);

	duk_destroy_heap(ctx);
	Console.Log(_T("\n - Duktape destroyed -\n"));
	print_mem();

	system("pause");

	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					  _In_opt_ HINSTANCE hPrevInstance,
					  _In_ LPWSTR    lpCmdLine,
					  _In_ int       nCmdShow) {
	Console.Alloc();
	Console.Select();
	Console.Reopen();
	Console.Title(_T("Duktape X Window"));
	return main();
}
