#include "wx_console.h"

#include "wx_duk.h"

using namespace WX;

void duk_errout(duk_context *ctx, const char *err_fmt, ...) {
	char buf[2048];
	va_list args;
	va_start(args, err_fmt);
	vsprintf_s(buf, err_fmt, args);
	va_end(args);
	auto atr = Console.Attribute();
	Console.Attribute(0x0C).ErrA(CString(buf, sizeof(buf)));
	Console.Attribute(atr);
}

void duk_errout(duk_context *ctx, const WX::Exception &err) {
	duk_errout(ctx,
			   " - WX exception -\n"
			   "   File:      " PNT_STR "\n"
			   "   Function:  " PNT_STR "\n"
			   "   Sentence:  " PNT_STR "\n"
			   "   Line:      %d\n"
			   "   LastError: %d\n",
			   (LPCTSTR)err.File(),
			   (LPCTSTR)err.Function(),
			   (LPCTSTR)err.Sentence(),
			   err.Line(),
			   err.LastError());
}

void load_duk_console(duk_context *ctx) {
	duk_struct_global(ctx, "Console", [](duk_context *ctx) -> duk_ret_t {
		duk_method(ctx, "Attach", 1, [](duk_context *ctx) -> duk_ret_t {
			DWORD pid = 0;
			if (duk_is_number(ctx, 0))
				pid = duk_to_int(ctx, 0);
			if (!pid) {
				duk_errout(ctx, "Console.Attach: PID is not specified");
				return DUK_RET_TYPE_ERROR;
			}
			if (wx_try(ctx, [&]() { Console.Attach(pid); Console.Reopen(); }))
				return DUK_RET_INTERNAL_ERROR;
			return 0;
		});
		duk_method(ctx, "Alloc", 0, [](duk_context *ctx) -> duk_ret_t {
			if (wx_try(ctx, [&]() { Console.Alloc(); }))
				return DUK_RET_INTERNAL_ERROR;
			return 0;
		});
		duk_method(ctx, "Reopen", 0, [](duk_context *ctx) -> duk_ret_t {
			if (wx_try(ctx, [&]() { Console.Reopen(); }))
				return DUK_RET_INTERNAL_ERROR;
			return 0;
		});
		duk_method(ctx, "Select", 0, [](duk_context *ctx) -> duk_ret_t {
			if (wx_try(ctx, [&]() { Console.Select(); }))
				return DUK_RET_INTERNAL_ERROR;
			return 0;
		});
		duk_method(ctx, "Free", 0, [](duk_context *ctx) -> duk_ret_t {
			if (wx_try(ctx, [&]() { Console.Free(); }))
				return DUK_RET_INTERNAL_ERROR;
			return 0;
		});
		duk_method(ctx, "Out", 1, [](duk_context *ctx) -> duk_ret_t {
			if (wx_try(ctx, [&]() { Console.LogA(CString(duk_to_string(ctx, 0), 2048)); }))
				return DUK_RET_INTERNAL_ERROR;
			return 0;
		});
		duk_method(ctx, "ErrOut", DUK_VARARGS, [](duk_context *ctx) -> duk_ret_t {
			if (wx_try(ctx, [&]() { Console.ErrA(CString(duk_to_string(ctx, 0), 2048)); }))
				return DUK_RET_INTERNAL_ERROR;
			return 0;
		});
		duk_method(ctx, "Log", DUK_VARARGS, [](duk_context *ctx) -> duk_ret_t {
			auto nargs = duk_get_top(ctx);
			for (int i = 0; i < nargs; ++i)
				if (wx_try(ctx, [&]() { Console.LogA(CString(duk_to_string(ctx, i), 2048)); }))
					return DUK_RET_INTERNAL_ERROR;
			Console.LogA('\n');
			return 0;
		});
		duk_method(ctx, "Err", DUK_VARARGS, [](duk_context *ctx) -> duk_ret_t {
			auto nargs = duk_get_top(ctx);
			auto atr = Console.Attribute();
			Console.Attribute(0x0C);
			for (int i = 0; i < nargs; ++i)
				if (wx_try(ctx, [&]() { Console.ErrA(CString(duk_to_string(ctx, i), 2048)); })) {
					Console.Attribute(atr);
					return DUK_RET_INTERNAL_ERROR;
				}
			Console.ErrA('\n');
			Console.Attribute(atr);
			return 0;
		});
		duk_property_r(ctx, "Window",
			[](duk_context *ctx) -> duk_ret_t {
				duk_get_global_string(ctx, "Window");
				duk_push_pointer(ctx, Console.Window());
				duk_new(ctx, 1);
				return 1;
			}
		);
		duk_method(ctx, "ActiveScreenBuffer", 0, [](duk_context *ctx) -> duk_ret_t {
			if (wx_try(ctx, [&]() { Console.ActiveScreenBuffer(); }))
				return DUK_RET_INTERNAL_ERROR;
			return 0;
		});
		duk_method(ctx, "FlushInputBuffer", 0, [](duk_context *ctx) -> duk_ret_t {
			if (wx_try(ctx, [&]() { Console.FlushInputBuffer(); }))
				return DUK_RET_INTERNAL_ERROR;
			return 0;
		});
		duk_method(ctx, "FillCharacter", 3, [](duk_context *ctx) -> duk_ret_t {
			auto cCharacter = duk_to_string(ctx, 0);
			auto nLength = duk_to_int(ctx, 1);
			LPoint dwWriteCoord;
			if (!duk_get_point(ctx, dwWriteCoord, 2))
				return DUK_RET_TYPE_ERROR;
			if (wx_try(ctx, [&]() { duk_push_int(ctx, Console.FillCharacterA(cCharacter[0], nLength, dwWriteCoord)); }))
				return DUK_RET_INTERNAL_ERROR;
			return 1;
		});
		duk_method(ctx, "FillAttribute", 3, [](duk_context *ctx) -> duk_ret_t {
			auto wAttribute = duk_to_int(ctx, 0);
			auto nLength = duk_to_int(ctx, 1);
			LPoint dwWriteCoord;
			if (!duk_get_point(ctx, dwWriteCoord, 2))
				return DUK_RET_TYPE_ERROR;
			if (wx_try(ctx, [&]() { duk_push_int(ctx, Console.FillAttribute(wAttribute & 0xFF, nLength, dwWriteCoord)); }))
				return DUK_RET_INTERNAL_ERROR;
			return 1;
		});
		duk_method(ctx, "WriteCharacter", 3, [](duk_context *ctx) -> duk_ret_t {
			auto lpCharacters = duk_to_string(ctx, 0);
			auto nLength = duk_to_int(ctx, 1);
			LPoint dwWriteCoord;
			if (!duk_get_point(ctx, dwWriteCoord, 2))
				return DUK_RET_TYPE_ERROR;
			if (wx_try(ctx, [&]() { duk_push_int(ctx, Console.WriteCharacterA(lpCharacters, nLength, dwWriteCoord)); }))
				return DUK_RET_INTERNAL_ERROR;
			return 1;
		});
		duk_method(ctx, "WriteAttribute", 3, [](duk_context *ctx) -> duk_ret_t {
			auto lpCharacters = duk_to_string(ctx, 0);
			auto nLength = duk_to_int(ctx, 1) / 2;
			LPoint dwWriteCoord;
			if (!duk_get_point(ctx, dwWriteCoord, 2))
				return DUK_RET_TYPE_ERROR;
			if (wx_try(ctx, [&]() { duk_push_int(ctx, Console.WriteAttribute((const WORD *)lpCharacters, nLength, dwWriteCoord)); }))
				return DUK_RET_INTERNAL_ERROR;
			return 1;
		});
#pragma region Properties
		duk_property(ctx, "Title", 
			[](duk_context *ctx) -> duk_ret_t {
				if (auto lpTitle = duk_to_string(ctx, 0))
					if (wx_try(ctx, [&]() { Console.Title(lpTitle); }))
						return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				if (wx_try(ctx, [&]() { duk_push_string(ctx, Console.TitleA()); }))
					return DUK_RET_INTERNAL_ERROR;
				return 1;
			}
		);
		duk_property_r(ctx, "OrigalTitle", [](duk_context *ctx) -> duk_ret_t {
			if (wx_try(ctx, [&]() { duk_push_string(ctx, Console.OriginalTitleA()); }))
				return DUK_RET_INTERNAL_ERROR;
			return 1;
		});
		duk_property(ctx, "CodePage",
			[](duk_context *ctx) -> duk_ret_t {
				if (auto cp = duk_to_int(ctx, 0))
					if (wx_try(ctx, [&]() { Console.CodePage(cp); }))
						return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				if (wx_try(ctx, [&]() { duk_push_int(ctx, Console.CodePage()); }))
					return DUK_RET_INTERNAL_ERROR;
				return 1;
			}
		);
		duk_property(ctx, "Attribute", 
			[](duk_context *ctx) -> duk_ret_t {
				if (auto chAtr = duk_to_int(ctx, 0))
					if (wx_try(ctx, [&]() { Console.Attribute(chAtr & 0xFFFF); }))
						return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				if (wx_try(ctx, [&]() { duk_push_int(ctx, Console.Attribute()); }))
					return DUK_RET_INTERNAL_ERROR;
				return 1;
			}
		);
		duk_property(ctx, "CursorPosition",
			[](duk_context *ctx) -> duk_ret_t {
				LPoint pos;
				if (duk_get_point(ctx, pos))
					if (wx_try(ctx, [&]() { Console.CursorPosition(pos); }))
						return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				LPoint pos;
				if (wx_try(ctx, [&]() { duk_push_point(ctx, Console.CursorPosition()); }))
					return DUK_RET_INTERNAL_ERROR;
				return 1;
			}
		);
		duk_property(ctx, "CursorVisible",
			[](duk_context *ctx) -> duk_ret_t {
				bool vis = duk_to_boolean(ctx, 0);
				if (wx_try(ctx, [&]() { Console.CursorVisible(vis); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				bool vis = false;
				if (wx_try(ctx, [&]() { vis = Console.CursorVisible(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_boolean(ctx, vis);
				return 1;
			}
		);
#pragma endregion

		return 0;
	});
}
