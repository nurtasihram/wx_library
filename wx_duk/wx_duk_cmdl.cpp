#include <iostream>

#include "wx_console.h"
#include "wx_realtime.h"

#include "wx_duk.h"

using namespace WX;

#pragma region Memory Management
int duk_alloc_count = 0;
Heap duk_mem_heap = Heap::Create();
void *duk_alloc(void *udata, duk_size_t size) {
	(void)udata;
	if (!size)
		return O;
	duk_alloc_count++;
	return duk_mem_heap.Alloc(size, HeapAllocFlag::GenerateExceptions);
}
void duk_free(void *udata, void *ptr) {
	(void)udata;
	if (!ptr)
		return;
	duk_alloc_count--;
	duk_mem_heap.Free(ptr);
}
void *duk_realloc(void *udata, void *ptr, duk_size_t size) {
	if (!ptr)
		return duk_alloc(udata, size);
	if (!size) {
		duk_free(udata, ptr);
		return O;
	}
	return duk_mem_heap.Realloc(ptr, size);
}
void duk_onfatal(void *udata, const char *msg) {
	throw duk_exception{ msg };
}
duk_ret_t print_mem(duk_context * = O) {
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

static duk_ret_t msg_proc(duk_context *ctx) {
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
			elif  (msg.ID() == WX_DUK_ON_CMD) {
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
						duk_get_global_string(ctx, "msg_proc");
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
		duk_errout(ctx, err.msg);
		proc_ok.Set();
	} catch (Exception err) {
		duk_errout(ctx, err.FormatA());
		proc_ok.Set();
	} catch (...) {
		Console.Err(_T("Other exception\n"));
		proc_ok.Set();
		bExit = true;
		return 0;
	}
	goto _ret;
}

duk_ret_t load_duk_cmdl(duk_context *ctx) {
	duk_push_global_object(ctx);
	duk_put_prop(ctx, "echo",
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
	duk_put_global_string(ctx, "LastError");
	duk_put_global_function(ctx, "print_mem", 0, print_mem);
	duk_put_global_function(ctx, "msg_proc", 0, msg_proc);
	duk_put_global_function(ctx, "cmd_exe", 1, cmd_exe);
	return 0;
}

static duk_context *ctx = O;
LThread msg_proc_thr = [] {
__reset:
	duk_get_global_string(ctx, "msg_proc");
	duk_call(ctx, 0);
	duk_pop(ctx);
	duk_gc(ctx, 0);
	if (bReset) {
		bReset = false;
		goto __reset;
	}
	proc_ok.Set();
};

void commandline(duk_context *ctx) {
	duk_push_c_function(ctx, load_duk, 0);
	duk_call(ctx, 0);
	duk_pop(ctx);

	duk_push_c_function(ctx, load_duk_cmdl, 0);
	duk_call(ctx, 0);
	duk_pop(ctx);

	duk_eval_string(ctx, "Console.Reopen()");
	Console.Log(_T("\n - Duktape symbols loaded -\n"));
	print_mem();

	assertl(msg_proc_thr.Create());
	proc_ok.WaitForSignal();

	while (duk_cmdl_count) {
		// print prompt
		auto &&cur_pos = Console.CursorPosition();
		++cur_pos.x;
		Console.FillCharacter(_T('>'), duk_cmdl_count, cur_pos);
		cur_pos.x += duk_cmdl_count + 1;
		Console.CursorPosition(cur_pos);
		// read input
		char js_code[1024]{ 0 };
		std::cin.getline(js_code, sizeof(js_code));
		// process input
		if (!msg_proc_thr.StillActive()) {
			Console.Log(_T("Message procedurer had exited\n"));
			break;
		}
		msg_proc_thr.Post(WX_DUK_ON_CMD, js_code);
		proc_ok.WaitForSignal();
	}
}

int main() {
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
