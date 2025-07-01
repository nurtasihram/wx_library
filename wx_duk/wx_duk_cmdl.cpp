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
void duk_onfatal(duk_context *, duk_errcode_t code, const char *MsgId) {
	throw duk_exception{ code, MsgId };
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
static char js_code[1024]{ 0 };
static UINT duk_cmdl_count = 0;
static duk_context *ctx = O;

Event proc_ok = Event::Create().AutoReset();
static constexpr auto WX_DUK_ON_CMD = WM_USER + 1;
static constexpr auto WX_DUK_ON_EXIT = WM_USER + 1;

duk_ret_t eval_cmdl(duk_context *ctx) {
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
			else if (msg.ID() == WX_DUK_ON_CMD) {
				duk_eval_raw(
					ctx, js_code, 0,
					1 /*args*/ |
					DUK_COMPILE_EVAL |
					DUK_COMPILE_NOSOURCE |
					DUK_COMPILE_STRLEN |
					DUK_COMPILE_NOFILENAME);
				if (bEcho && !duk_is_undefined(ctx, -1)) {
					duk_get_global_string(ctx, "print");
					duk_dup(ctx, -2); // push the result of eval
					duk_call(ctx, 1);
				}
				duk_gc(ctx, 0);
				if (bReset) {
					Console.Log(_T("reset\n"));
					--duk_cmdl_count;
					return 0;
				}
				if (bCmdl) {
					bCmdl = false;
				__reset:
					duk_push_c_function(ctx, eval_cmdl, 0);
					duk_call(ctx, 0);
					duk_pop(ctx);
					if (bReset) {
						bReset = false;
						goto __reset;
					}
					continue;
				}
				if (bExit) {
					Console.Log(_T("exit\n\n"));
					bExit = false;
					--duk_cmdl_count;
					proc_ok.Set();
					return 0;
				}
				proc_ok.Set();
			}
		}
	} catch (duk_exception err) {
		Console.ErrA(
			"FATAL: ", err.MsgId, '\n',
			"CODE:  ", err.code, '\n');
		proc_ok.Set();
	} catch (WX::Exception err) {
		duk_errout(ctx, err);
		proc_ok.Set();
	} catch (...) {
		Console.Err(_T("Other exception\n"));
		proc_ok.Set();
		bExit = true;
		return 0;
	}
	goto _ret;
}

LThread msg_proc = [] {
__reset:
	duk_push_c_function(ctx, eval_cmdl, 0);
	duk_call(ctx, 0);
	duk_pop(ctx);
	if (bReset) {
		bReset = false;
		goto __reset;
	}
};

inline void ProcCmd() {
	msg_proc.Post(WX_DUK_ON_CMD);
	proc_ok.WaitForSignal();
}

void commandline(duk_context *ctx) {
	duk_push_global_object(ctx);
	duk_property(ctx, "echo",
		[](duk_context *ctx) -> duk_ret_t {
			bEcho = duk_to_boolean(ctx, 0);
			return 0;
		},
		[](duk_context *ctx) -> duk_ret_t {
			duk_push_boolean(ctx, bEcho);
			return 1;
		}
	);
	duk_property_r(ctx, "exit", [](duk_context *ctx) -> duk_ret_t {
		bExit = true;
		return 0;
	});
	duk_property_r(ctx, "cmdl", [](duk_context *ctx) -> duk_ret_t {
		bCmdl = true;
		return 0;
	});
	duk_property_r(ctx, "reset", [](duk_context *ctx) -> duk_ret_t {
		bReset = true;
		return 0;
	});
	duk_property_r(ctx, "clear", [](duk_context *ctx) -> duk_ret_t {
		Console.Clear();
		return 0;
	});
	duk_push_c_function(ctx, print_mem, 0);
	duk_put_global_string(ctx, "print_mem");
	duk_push_c_function(ctx, load_duk, 0);
	duk_call(ctx, 0);
	duk_pop(ctx);
	duk_eval_string(ctx, "Console.Reopen()");
	Console.Log(_T("\n - Duktape symbols loaded -\n"));
	print_mem();
	assertl(msg_proc.Create());
	proc_ok.WaitForSignal();
	while (duk_cmdl_count) {
		auto &&cur_pos = Console.CursorPosition();
		++cur_pos.x;
		Console.FillCharacter(_T('>'), duk_cmdl_count, cur_pos);
		cur_pos.x += duk_cmdl_count + 1;
		Console.CursorPosition(cur_pos);
		std::cin.getline(js_code, sizeof(js_code));
		ProcCmd();
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
