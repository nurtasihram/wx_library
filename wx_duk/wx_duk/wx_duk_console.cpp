#include "wx_console.h"

#include "wx_duk.h"

void duk_errout(duk_context *ctx, const char *err_fmt, ...) {
	char buf[2048];
	va_list args;
	va_start(args, err_fmt);
	vsprintf_s(buf, err_fmt, args);
	va_end(args);
	auto atr = Console.Attributes();
	Console.Attributes(0x0C).ErrA(CString(buf, sizeof(buf)), '\n');
	Console.Attributes(atr);
}

void load_duk_console(duk_context *ctx) {
	duk_add_object(ctx, "Console", duk_fn {
		/* void */ duk_add_method(ctx, "Attach", 1, duk_fn {
			DWORD pid = duk_to_int(ctx, 0);
			if (wx_try(ctx, [&] { Console.Attach(pid); Console.Reopen(); }))
				return DUK_RET_REFERENCE_ERROR;
			return 0;
		});
		/* void */ duk_add_method(ctx, "Alloc", 0, duk_fn {
			if (wx_try(ctx, [&] { Console.Alloc(); }))
				return DUK_RET_REFERENCE_ERROR;
			return 0;
		});
		/* void */ duk_add_method(ctx, "Reopen", 0, duk_fn {
			if (wx_try(ctx, [&] { Console.Reopen(); }))
				return DUK_RET_REFERENCE_ERROR;
			return 0;
		});
		duk_add_method(ctx, "Select", 0, duk_fn {
			if (wx_try(ctx, [&] { Console.Select(); }))
				return DUK_RET_REFERENCE_ERROR;
			return 0;
		});
		duk_add_method(ctx, "Clear", 0, duk_fn {
			if (wx_try(ctx, [&] { Console.Clear(); }))
				return DUK_RET_REFERENCE_ERROR;
			return 0;
		});
		duk_add_method(ctx, "Color", 1, duk_fn {
			WORD wAttr = duk_to_uint16(ctx, 0);
			if (wx_try(ctx, [&] { Console.Color(wAttr); }))
				return DUK_RET_REFERENCE_ERROR;
			return 0;
		});
		duk_add_method(ctx, "Free", 0, duk_fn {
			if (wx_try(ctx, [&] { Console.Free(); }))
				return DUK_RET_REFERENCE_ERROR;
			return 0;
		});
		duk_add_method(ctx, "Out", 1, duk_fn {
			if (wx_try(ctx, [&] { Console.LogA(CString(duk_to_string(ctx, 0), 2048)); }))
				return DUK_RET_REFERENCE_ERROR;
			return 0;
		});
		duk_add_method(ctx, "ErrOut", DUK_VARARGS, duk_fn {
			if (wx_try(ctx, [&] { Console.ErrA(CString(duk_to_string(ctx, 0), 2048)); }))
				return DUK_RET_REFERENCE_ERROR;
			return 0;
		});
		duk_add_method(ctx, "Log", DUK_VARARGS, duk_fn {
			auto nargs = duk_get_top(ctx);
			for (int i = 0; i < nargs; ++i)
				if (wx_try(ctx, [&] { Console.LogA(CString(duk_to_string(ctx, i), 2048)); }))
					return DUK_RET_REFERENCE_ERROR;
			Console.LogA('\n');
			return 0;
		});
		duk_add_method(ctx, "Err", DUK_VARARGS, duk_fn {
			auto nargs = duk_get_top(ctx);
			auto atr = Console.Attributes();
			Console.Attributes(0x0C);
			for (int i = 0; i < nargs; ++i)
				if (wx_try(ctx, [&] { Console.ErrA(CString(duk_to_string(ctx, i), 2048)); })) {
					Console.Attributes(atr);
					return DUK_RET_REFERENCE_ERROR;
				}
			Console.ErrA('\n');
			Console.Attributes(atr);
			return 0;
		});
		duk_add_prop_r(ctx, "Window", duk_fn {
			duk_get_global_string(ctx, "Window");
			duk_push_pointer(ctx, Console.Window());
			duk_new(ctx, 1);
			return 1;
		});
		duk_add_method(ctx, "ActiveScreenBuffer", 0, duk_fn {
			if (wx_try(ctx, [&] { Console.ActiveScreenBuffer(); }))
				return DUK_RET_REFERENCE_ERROR;
			return 0;
		});
		duk_add_method(ctx, "FlushInputBuffer", 0, duk_fn {
			if (wx_try(ctx, [&] { Console.FlushInputBuffer(); }))
				return DUK_RET_REFERENCE_ERROR;
			return 0;
		});
		duk_add_method(ctx, "Fill", 3, duk_fn {
			auto cCharacter = duk_to_string(ctx, 0);
			auto nLength = duk_to_int(ctx, 1);
			LPoint dwWriteCoord;
			if (!duk_get_point(ctx, dwWriteCoord, 2))
				return DUK_RET_TYPE_ERROR;
			if (wx_try(ctx, [&] { duk_push_int(ctx, Console.Fill(cCharacter[0], nLength, dwWriteCoord)); }))
				return DUK_RET_REFERENCE_ERROR;
			return 1;
		});
		duk_add_method(ctx, "FillAttributes", 3, duk_fn {
			auto wAttribute = duk_to_int(ctx, 0);
			auto nLength = duk_to_int(ctx, 1);
			LPoint dwWriteCoord;
			if (!duk_get_point(ctx, dwWriteCoord, 2))
				return DUK_RET_TYPE_ERROR;
			if (wx_try(ctx, [&] { duk_push_int(ctx, Console.FillAttributes(wAttribute & 0xFF, nLength, dwWriteCoord)); }))
				return DUK_RET_REFERENCE_ERROR;
			return 1;
		});
		duk_add_method(ctx, "Write", 3, duk_fn {
			auto lpCharacters = duk_to_string(ctx, 0);
			auto nLength = duk_to_int(ctx, 1);
			LPoint dwWriteCoord;
			if (duk_get_point(ctx, dwWriteCoord, 2)) {
				if (wx_try(ctx, [&] { duk_push_int(ctx, Console.Write(lpCharacters, nLength, dwWriteCoord)); }))
					return DUK_RET_REFERENCE_ERROR;
			} elif (wx_try(ctx, [&] { duk_push_int(ctx, Console.Write(lpCharacters, nLength)); }))
				return DUK_RET_REFERENCE_ERROR;
			return 1;
		});
		duk_add_method(ctx, "WriteAttributes", 3, duk_fn {
			auto lpCharacters = duk_to_string(ctx, 0);
			auto nLength = duk_to_int(ctx, 1) / 2;
			LPoint dwWriteCoord;
			if (!duk_get_point(ctx, dwWriteCoord, 2))
				return DUK_RET_TYPE_ERROR;
			if (wx_try(ctx, [&] { duk_push_int(ctx, Console.WriteAttributes((const WORD *)lpCharacters, nLength, dwWriteCoord)); }))
				return DUK_RET_REFERENCE_ERROR;
			return 1;
		});
#pragma region Properties
		duk_add_prop(ctx, "Title",
			duk_fn {
				auto lpTitle = duk_to_string(ctx, 0);
				if (wx_try(ctx, [&] { Console.Title(lpTitle); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			},
			duk_fn {
				if (wx_try(ctx, [&] { duk_push_string(ctx, Console.TitleA()); }))
					return DUK_RET_REFERENCE_ERROR;
				return 1;
			}
		);
		duk_add_prop_r(ctx, "OriginalTitle", duk_fn {
			if (wx_try(ctx, [&] { duk_push_string(ctx, Console.OriginalTitleA()); }))
				return DUK_RET_REFERENCE_ERROR;
			return 1;
		});
		duk_add_prop(ctx, "CodePage",
			duk_fn {
				auto cp = duk_to_int(ctx, 0);
				if (wx_try(ctx, [&] { Console.CodePage(cp); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			},
			duk_fn {
				if (wx_try(ctx, [&] { duk_push_int(ctx, Console.CodePage()); }))
					return DUK_RET_REFERENCE_ERROR;
				return 1;
			}
		);
		duk_add_prop(ctx, "Attributes",
			duk_fn {
				auto chAtr = duk_to_int(ctx, 0);
				if (wx_try(ctx, [&] { Console.Attributes(chAtr & 0xFFFF); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			},
			duk_fn {
				if (wx_try(ctx, [&] { duk_push_int(ctx, Console.Attributes()); }))
					return DUK_RET_REFERENCE_ERROR;
				return 1;
			}
		);
		duk_add_prop(ctx, "CursorPosition",
			duk_fn {
				LPoint pos;
				if (!duk_get_point(ctx, pos))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&] { Console.CursorPosition(pos); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			},
			duk_fn {
				LPoint pos;
				if (wx_try(ctx, [&] { duk_push_point(ctx, Console.CursorPosition()); }))
					return DUK_RET_REFERENCE_ERROR;
				return 1;
			}
		);
		duk_add_prop(ctx, "CursorVisible",
			duk_fn {
				bool vis = duk_to_boolean(ctx, 0);
				if (wx_try(ctx, [&] { Console.CursorVisible(vis); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			},
			duk_fn {
				bool vis = false;
				if (wx_try(ctx, [&] { vis = Console.CursorVisible(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_boolean(ctx, vis);
				return 1;
			}
		);
#pragma endregion

		return 0; });
}
