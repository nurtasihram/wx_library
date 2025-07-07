#include "wx_window.h"

#include "wx_duk.h"

template<class AnyClass, class AnyClosure>
inline duk_c_function duk_set_safe(AnyClosure closure) {
	static auto _closure = closure;
	return duk_fn {
		auto pobj = duk_get_this__p<AnyClass>(ctx);
		if (!pobj)
			return DUK_RET_REFERENCE_ERROR;
		if constexpr (!std::is_void_v<decltype(_closure(ctx, pobj))>)
			return _closure(ctx, pobj);
		else {
			_closure(ctx, pobj);
			return 0;
		}
	};
}
template<class AnyClass, class AnyClosure>
inline duk_c_function duk_get_safe(AnyClosure closure) {
	static auto _closure = closure;
	return duk_fn {
		auto pobj = duk_get_this__p<AnyClass>(ctx);
		if (!pobj)
			return DUK_RET_REFERENCE_ERROR;
		if constexpr (!std::is_void_v<decltype(_closure(ctx, pobj))>)
			return _closure(ctx, pobj);
		else {
			_closure(ctx, pobj);
			return 1;
		}
	};
}

template<class AnyClass>
static duk_c_function duk_constructor_buffer = duk_constructor {
	if (duk_reflect_constructor(ctx))
		return 1;
	AnyClass *pobj = O;
	switch (duk_get_top(ctx)) {
		case 0: {
			pobj = duk_put_cstruct<AnyClass>(ctx);
			break;
		}
		case 1: {
			if (duk_is_object(ctx, 0)) {
				duk_push_current_function(ctx);
				if (!duk_instanceof(ctx, -1, 0))
					return DUK_RET_TYPE_ERROR;
				duk_get_prop_string(ctx, 0, "__p");
				duk_insert(ctx, 0);
			}
			if (duk_is_buffer(ctx, 0)) {
				duk_size_t size = 0;
				if (!duk_get_buffer(ctx, 0, &size))
					return DUK_RET_TYPE_ERROR;
				if (size != sizeof(AnyClass))
					return DUK_RET_TYPE_ERROR;
				duk_push_this(ctx);
				duk_push_string(ctx, "__p");
				duk_dup(ctx, 0);
				duk_def_prop(ctx, -3, DUK_DEFPROP_PRIVATE_CONST);
			}
			else
				return DUK_RET_TYPE_ERROR;
			break;
		}
	}
	return 0;
};

void load_duk_window(duk_context *ctx) {
#pragma region Misc
	static const duk_constant _MB_constant[]{
		{ "Ok", MB_OK },
		{ "OkCancel", MB_OKCANCEL },
		{ "AbortRetryIgnore", MB_ABORTRETRYIGNORE },
		{ "YesNoCancel", MB_YESNOCANCEL },
		{ "YesNo", MB_YESNO },
		{ "RetryCancel", MB_RETRYCANCEL },
		{ "CancelTryContinue", MB_CANCELTRYCONTINUE },
		{ "IconHand", MB_ICONHAND },
		{ "IconQuestion", MB_ICONQUESTION },
		{ "IconExclamation", MB_ICONEXCLAMATION },
		{ "IconAsterisk", MB_ICONASTERISK },
		{ "UserIcon", MB_USERICON },
		{ "IconWarning", MB_ICONWARNING },
		{ "IconError", MB_ICONERROR },
		{ "IconInformation", MB_ICONINFORMATION },
		{ "IconStop", MB_ICONSTOP },
		{ "DefButton1", MB_DEFBUTTON1 },
		{ "DefButton2", MB_DEFBUTTON2 },
		{ "DefButton3", MB_DEFBUTTON3 },
		{ "DefButton4", MB_DEFBUTTON4 },
		{ "ApplModal", MB_APPLMODAL },
		{ "SystemModal", MB_SYSTEMMODAL },
		{ "TaskModal", MB_TASKMODAL },
		{ "Help", MB_HELP },
		{ "NoFocus", MB_NOFOCUS },
		{ "SetForeground", MB_SETFOREGROUND },
		{ "DefaultDesktopOnly", MB_DEFAULT_DESKTOP_ONLY },
		{ "Topmost", MB_TOPMOST },
		{ "Right", MB_RIGHT },
		{ "RtlReading", MB_RTLREADING },
		{ "ServiceNotification", MB_SERVICE_NOTIFICATION }
	};
	duk_add_global_flags(ctx, "MB", O, _MB_constant);
	duk_put_global_function(
		/* int */ ctx, "MsgBox", 3, duk_fn {
			LPCSTR lpCaption = duk_is_undefined(ctx, 0) ? "" : duk_to_string(ctx, 0);
			LPCSTR lpText = duk_is_undefined(ctx, 1) ? "" : duk_to_string(ctx, 1);
			MB uType = duk_is_undefined(ctx, 2) ? reuse_as<MB>(duk_to_int(ctx, 2)) : (MB)MB::Ok;
			auto res = MsgBox(lpCaption, lpText, uType);
			duk_push_int(ctx, res);
			return 1;
		}
	);

	static const duk_constant _SW_constant[]{
		{ "Hide", SW_HIDE },
		{ "ShowNormal", SW_SHOWNORMAL },
		{ "Normal", SW_NORMAL },
		{ "ShowMinimized", SW_SHOWMINIMIZED },
		{ "ShowMaximized", SW_SHOWMAXIMIZED },
		{ "Maximize", SW_MAXIMIZE },
		{ "ShowNoActivate", SW_SHOWNOACTIVATE },
		{ "Show", SW_SHOW },
		{ "Minimize", SW_MINIMIZE },
		{ "ShowMinNoActive", SW_SHOWMINNOACTIVE },
		{ "ShowNA", SW_SHOWNA },
		{ "Restore", SW_RESTORE },
		{ "ShowDefault", SW_SHOWDEFAULT },
		{ "ForceMinimize", SW_FORCEMINIMIZE },
		{ "Max", SW_MAX }
	};
	duk_add_global_enums(ctx, "SW", O, _SW_constant);

	static const duk_constant _WS_constant[]{
		{ "Overlapped", WS_OVERLAPPED },
		{ "Popup", WS_POPUP },
		{ "Child", WS_CHILD },
		{ "Minimize", WS_MINIMIZE },
		{ "Maximize", WS_MAXIMIZE },
		{ "MinimizeBox", WS_MINIMIZEBOX },
		{ "MaximizeBox", WS_MAXIMIZEBOX },
		{ "SizeBox", WS_SIZEBOX },
		{ "Visible", WS_VISIBLE },
		{ "Disabled", WS_DISABLED },
		{ "ClipSiblings", WS_CLIPSIBLINGS },
		{ "ClipChildren", WS_CLIPCHILDREN },
		{ "Caption", WS_CAPTION },
		{ "Border", WS_BORDER },
		{ "DlgFrame", WS_DLGFRAME },
		{ "VScroll", WS_VSCROLL },
		{ "HScroll", WS_HSCROLL },
		{ "SysMenu", WS_SYSMENU },
		{ "ThickFrame", WS_THICKFRAME },
		{ "Group", WS_GROUP },
		{ "TabStop", WS_TABSTOP },
		{ "Tiled", WS_TILED },
		{ "Iconic", WS_ICONIC },
		{ "TiledWindow", WS_TILEDWINDOW },
		{ "PopupWindow", WS_POPUPWINDOW },
		{ "OverlappedWindow", WS_OVERLAPPEDWINDOW }
	};
	duk_add_global_flags(ctx, "WindowStyle", O, _WS_constant);

	static const duk_constant _WSEX_constant[]{
		{ "No", 0 },
		{ "DlgModalFrame", WS_EX_DLGMODALFRAME },
		{ "NoParentNotify", WS_EX_NOPARENTNOTIFY },
		{ "TopMost", WS_EX_TOPMOST },
		{ "AcceptFiles", WS_EX_ACCEPTFILES },
		{ "Transparent", WS_EX_TRANSPARENT },
		{ "MdiChild", WS_EX_MDICHILD },
		{ "ToolWindow", WS_EX_TOOLWINDOW },
		{ "WindowEdge", WS_EX_WINDOWEDGE },
		{ "ClientEdge", WS_EX_CLIENTEDGE },
		{ "ContextHelp", WS_EX_CONTEXTHELP },
		{ "Right", WS_EX_RIGHT },
		{ "Left", WS_EX_LEFT },
		{ "ReadingR2L", WS_EX_RTLREADING },
		{ "ReadingL2R", WS_EX_LTRREADING },
		{ "LeftScrollBar", WS_EX_LEFTSCROLLBAR },
		{ "RightScrollBar", WS_EX_RIGHTSCROLLBAR },
		{ "ControlParent", WS_EX_CONTROLPARENT },
		{ "StaticEdge", WS_EX_STATICEDGE },
		{ "AppWindow", WS_EX_APPWINDOW },
		{ "Layered", WS_EX_LAYERED },
		{ "NoInheritLayout", WS_EX_NOINHERITLAYOUT },
		{ "NoRedirectionBitmap", WS_EX_NOREDIRECTIONBITMAP },
		{ "LayoutR2L", WS_EX_LAYOUTRTL },
		{ "Composited", WS_EX_COMPOSITED },
		{ "NoActivate", WS_EX_NOACTIVATE },
		{ "OverlappedWindow", WS_EX_OVERLAPPEDWINDOW },
		{ "PaletteWindow", WS_EX_PALETTEWINDOW }
	};
	duk_add_global_flags(ctx, "WindowStyleEx", O, _WSEX_constant);

	duk_put_global_class(
		ctx, "WindowPlacement", O,
		duk_structure {
			duk_put_prop(
				/* bool */ ctx, "SetMinPosition",
				duk_set_safe<WindowPlacement>([](duk_context *ctx, WindowPlacement *pobj) {
					pobj->SetMinPosition(duk_to_boolean(ctx, 0));
				}),
				duk_get {
					auto pobj = duk_get_this__p<WindowPlacement>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_boolean(ctx, pobj->SetMinPosition());
					return 1;
				}
			);
			duk_put_prop(
				/* bool */ ctx, "RestoreToMaximized",
				duk_set_safe<WindowPlacement>([](duk_context *ctx, WindowPlacement *pobj) {
					pobj->RestoreToMaximized(duk_to_boolean(ctx, 0));
				}),
				duk_get {
					auto pobj = duk_get_this__p<WindowPlacement>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_boolean(ctx, pobj->RestoreToMaximized());
					return 1;
				}
			);
			duk_put_prop(
				/* bool */ ctx, "Async",
				duk_set_safe<WindowPlacement>([](duk_context *ctx, WindowPlacement *pobj) {
					pobj->SetMinPosition(duk_to_boolean(ctx, 0));
				}),
				duk_get {
					auto pobj = duk_get_this__p<WindowPlacement>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_boolean(ctx, pobj->Async());
					return 1;
				}
			);
			duk_put_prop(
				/* WindowShowFlags */ ctx, "ShowFlags",
				duk_set_safe<WindowPlacement>([](duk_context *ctx, WindowPlacement *pobj) {
					pobj->ShowFlags(reuse_as<SW>(duk_to_uint(ctx, 0)));
				}),
				duk_get {
					auto pobj = duk_get_this__p<WindowPlacement>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "SW", pobj->ShowFlags().yield());
					return 1;
				}
			);
			duk_put_prop(
				/* Point */ ctx, "MinPosition",
				duk_set_safe<WindowPlacement>([](duk_context *ctx, WindowPlacement *pobj) {
					pobj->SetMinPosition(duk_to_boolean(ctx, 0));
					LPoint Pos;
					if (!duk_get_point(ctx, Pos, 0))
						return DUK_RET_TYPE_ERROR;
					pobj->MinPosition(Pos);
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<WindowPlacement>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					auto &&Pos = pobj->MinPosition();
					duk_push_point(ctx, Pos);
					return 1;
				}
			);
			duk_put_prop(
				/* Point */ ctx, "MaxPosition",
				duk_set_safe<WindowPlacement>([](duk_context *ctx, WindowPlacement *pobj) {
					LPoint Pos;
					if (!duk_get_point(ctx, Pos, 0))
						return DUK_RET_TYPE_ERROR;
					pobj->MaxPosition(Pos);
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<WindowPlacement>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					auto &&Pos = pobj->MaxPosition();
					duk_push_point(ctx, Pos);
					return 1;
				}
			);
			duk_put_prop(
				/* Point */ ctx, "NormalPosition",
				duk_set_safe<WindowPlacement>([](duk_context *ctx, WindowPlacement *pobj) {
					LRect Pos;
					if (!duk_get_rect(ctx, Pos, 0))
						return DUK_RET_TYPE_ERROR;
					pobj->NormalPosition(Pos);
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<WindowPlacement>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					auto &&Pos = pobj->NormalPosition();
					duk_push_rect(ctx, Pos);
					return 1;
				}
			);
			duk_put_method(
				/* String */ ctx, "toString", 0, duk_fn {
				auto pobj = duk_get_this__p<WindowPlacement>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				auto lpszShowFlags = duk_this_prop_to_string(ctx, "ShowFlags");
				auto lpszMinPos = duk_this_prop_to_string(ctx, "MinPosition"),
					 lpszMaxPos = duk_this_prop_to_string(ctx, "MaxPosition"),
					 lpszNormalPos = duk_this_prop_to_string(ctx, "NormalPosition");
				duk_push_sprintf(
					ctx,
					"{\n"
					"  SetMinPosition: %s,\n"
					"  RestoreToMaximized: %s,\n"
					"  Async: %s,\n"
					"  ShowFlags: %s,\n"
					"  MinPosition: %s,\n"
					"  MaxPosition: %s,\n"
					"  NormalPosition: %s\n"
					"}",
					smpl_to_string(pobj->SetMinPosition()),
					smpl_to_string(pobj->RestoreToMaximized()),
					smpl_to_string(pobj->Async()),
					lpszShowFlags,
					lpszMinPos,
					lpszMaxPos,
					lpszNormalPos
				);
				return 1;
			});
			return 0;
		},
		duk_constructor_buffer<WindowPlacement>
	);

	duk_put_global_class(
		ctx, "WindowInfo", O,
		duk_structure {
			duk_put_prop(
				/* Rect */ ctx, "Rect",
				duk_set_safe<WindowInfo>([](duk_context *ctx, WindowInfo *pobj) {
					LRect r;
					if (!duk_get_rect(ctx, r, 0))
						return DUK_RET_TYPE_ERROR;
					pobj->Rect(r);
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<WindowInfo>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					auto &&r = pobj->Rect();
					duk_push_rect(ctx, r);
					return 1;
				}
			);
			duk_put_prop(
				/* Rect */ ctx, "ClientRect",
				duk_set_safe<WindowInfo>([](duk_context *ctx, WindowInfo *pobj) {
					LRect r;
					if (!duk_get_rect(ctx, r, 0))
						return DUK_RET_TYPE_ERROR;
					pobj->ClientRect(r);
					return 0;
				}),
				duk_get{
					auto pobj = duk_get_this__p<WindowInfo>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					auto &&r = pobj->ClientRect();
					duk_push_rect(ctx, r);
					return 1;
				}
			);
			duk_put_prop(
				/* WS */ ctx, "Styles",
				duk_set_safe<WindowInfo>([](duk_context *ctx, WindowInfo *pobj) {
					pobj->Styles(reuse_as<WS>(duk_to_uint(ctx, 0)));
				}),
				duk_get {
					auto pobj = duk_get_this__p<WindowInfo>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "WindowStyle", pobj->Styles().yield());
					return 1;
				}
			);
			duk_put_prop(
				/* WSEX */ ctx, "StylesEx",
				duk_set_safe<WindowInfo>([](duk_context *ctx, WindowInfo *pobj) {
					pobj->StylesEx(reuse_as<WSEX>(duk_to_uint(ctx, 0)));
				}),
				duk_get {
					auto pobj = duk_get_this__p<WindowInfo>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "WindowStyleEx", pobj->StylesEx().yield());
					return 1;
				}
			);
			duk_put_prop(
				/* int */ ctx, "Status",
				duk_set_safe<WindowInfo>([](duk_context *ctx, WindowInfo *pobj) {
					pobj->Status(duk_to_int(ctx, 0));
				}),
				duk_get {
					auto pobj = duk_get_this__p<WindowInfo>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->Status());
					return 1;
				}
			);
			duk_put_prop(
				/* Point */ ctx, "Borders",
				duk_set_safe<WindowInfo>([](duk_context *ctx, WindowInfo *pobj) {
					LPoint p;
					if (!duk_get_point(ctx, p, 0))
						return DUK_RET_TYPE_ERROR;
					pobj->Borders(p);
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<WindowInfo>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					auto &&p = pobj->Borders();
					duk_push_point(ctx, p);
					return 1;
				}
			);
			duk_put_prop(
				/* Atom */ ctx, "ClassAtom",
				duk_set_safe<WindowInfo>([](duk_context *ctx, WindowInfo *pobj) {
					pobj->ClassAtom(duk_to_uint(ctx, 0));
				}),
				duk_get {
					auto pobj = duk_get_this__p<WindowInfo>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_uint(ctx, pobj->ClassAtom());
					return 1;
				}
			);
			duk_put_prop(
				/* WORD */ ctx, "CreatorVersion",
				duk_set_safe<WindowInfo>([](duk_context *ctx, WindowInfo *pobj) {
					pobj->CreatorVersion(duk_to_uint(ctx, 0));
				}),
				duk_get {
					auto pobj = duk_get_this__p<WindowInfo>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_uint(ctx, pobj->CreatorVersion());
					return 1;
				}
			);
			return 0;
		},
		duk_constructor_buffer<WindowInfo>
	);
#pragma endregion

#pragma region WindowClass
	static const duk_constant _ClassStyle_constant[]{
		{ "VRedraw", CS_VREDRAW },
		{ "HRedraw", CS_HREDRAW },
		{ "Redraw", CS_VREDRAW | CS_HREDRAW },
		{ "DoubleClick", CS_DBLCLKS },
		{ "OwnDC", CS_OWNDC },
		{ "ClassDC", CS_CLASSDC },
		{ "ParentDC", CS_PARENTDC },
		{ "NoClose", CS_NOCLOSE },
		{ "SaveBits", CS_SAVEBITS },
		{ "ByteAlignClient", CS_BYTEALIGNCLIENT },
		{ "ByteAlignWindow", CS_BYTEALIGNWINDOW },
		{ "GlobalClass", CS_GLOBALCLASS },
		{ "IME", CS_IME },
		{ "DropShadow", CS_DROPSHADOW }
	};
	duk_add_global_flags(ctx, "ClassStyle", O, _ClassStyle_constant);
	static auto __WndClass_properties = [](duk_context *ctx, auto alfa) {
		using AnyWndClass = decltype(alfa);
		duk_put_prop(
			/* ClassStyle */ ctx, "Styles",
			duk_set_safe<AnyWndClass>([](duk_context *ctx, AnyWndClass *pobj) {
				pobj->Styles(reuse_as<ClassStyle>(duk_to_uint(ctx, 0)));
			}),
			duk_get {
				auto pobj = duk_get_this__p<AnyWndClass>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				duk_push_enum(ctx, "ClassStyle", pobj->Styles().yield());
				return 1;
			}
		);
		/* int */ duk_put_prop_r(ctx, "ClsExtra", duk_fn {
			auto pobj = duk_get_this__p<AnyWndClass>(ctx);
			if (!pobj)
				return DUK_RET_REFERENCE_ERROR;
			duk_push_int(ctx, pobj->ClsExtra());
			return 1;
		});
		duk_put_prop(
			/* int */ ctx, "WndExtra",
			duk_set_safe<AnyWndClass>([](duk_context *ctx, AnyWndClass *pobj) {
				pobj->WndExtra(duk_to_int(ctx, 0));
			}),
			duk_get {
				auto pobj = duk_get_this__p<AnyWndClass>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				duk_push_int(ctx, pobj->WndExtra());
				return 1;
			}
		);
		duk_put_prop(
			/* Module */ ctx, "Module",
			duk_set_safe<AnyWndClass>([](duk_context *ctx, AnyWndClass *pobj) {
				HMODULE hModule = O;
				if (!duk_get_class__p(ctx, "Module", hModule))
					return DUK_RET_TYPE_ERROR;
				pobj->Module(hModule);
				return 0;
			}),
			duk_get {
				auto pobj = duk_get_this__p<AnyWndClass>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_cclass(ctx, "Module", pobj->Module());
				return 1;
			}
		);
		duk_put_prop(
			/* Icon */ ctx, "Icon",
			duk_set_safe<AnyWndClass>([](duk_context *ctx, AnyWndClass *pobj) {
				HICON hIcon = O;
				if (!duk_get_class__p(ctx, "Icon", hIcon))
					return DUK_RET_TYPE_ERROR;
				pobj->Icon(hIcon);
				return 0;
			}),
			duk_get {
				auto pobj = duk_get_this__p<AnyWndClass>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_cclass(ctx, "Icon", pobj->Icon());
				return 1;
			}
		);
		duk_put_prop(
			/* Cursor */ ctx, "Cursor",
			duk_set_safe<AnyWndClass>([](duk_context *ctx, AnyWndClass *pobj) {
				HCURSOR hCursor = O;
				if (!duk_get_class__p(ctx, "Cursor", hCursor))
					return DUK_RET_TYPE_ERROR;
				pobj->Cursor(hCursor);
				return 0;
			}),
			duk_get {
				auto pobj = duk_get_this__p<AnyWndClass>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_cclass(ctx, "Cursor", pobj->Cursor());
				return 1;
			}
		);
		duk_put_prop(
			/* Brush */ ctx, "Background",
			duk_set_safe<AnyWndClass>([](duk_context *ctx, AnyWndClass *pobj) {
				HBRUSH hBrush = O;
				if (!duk_get_class__p(ctx, "Brush", hBrush))
					return DUK_RET_TYPE_ERROR;
				pobj->Background(hBrush);
				return 0;
			}),
			duk_get {
				auto pobj = duk_get_this__p<AnyWndClass>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_cclass(ctx, "Brush", pobj->Background());
				return 1;
			}
		);
		duk_put_prop(
			/* Menu */ ctx, "Menu",
			duk_set_safe<AnyWndClass>([](duk_context *ctx, AnyWndClass *pobj) {
				if (duk_is_string(ctx, 0))
					pobj->Menu(duk_to_string(ctx, 0));
				else if (duk_is_number(ctx, 0))
					pobj->Menu(duk_to_uint16(ctx, 0));
				else
					return DUK_RET_TYPE_ERROR;
				return 0;
			}),
			duk_get {
				auto pobj = duk_get_this__p<AnyWndClass>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_cclass(ctx, "Menu", pobj->Menu());
				return 1;
			}
		);
		duk_put_prop(
			/* String */ ctx, "Name",
			duk_set_safe<AnyWndClass>([](duk_context *ctx, AnyWndClass *pobj) {
				pobj->Name(duk_to_string(ctx, 0));
			}),
			duk_get {
				auto pobj = duk_get_this__p<AnyWndClass>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				duk_push_string(ctx, pobj->Name());
				return 1;
			}
		);
		duk_put_prop(
			/* Atom */ ctx, "Atom",
			duk_set_safe<AnyWndClass>([](duk_context *ctx, AnyWndClass *pobj) {
				pobj->Atom(duk_to_uint16(ctx, 0));
			}),
			duk_get {
				auto pobj = duk_get_this__p<AnyWndClass>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				duk_push_uint(ctx, pobj->Atom());
				return 1;
			}
		);
		/* Atom */ duk_put_method(ctx, "Register", 0, duk_fn {
			auto pobj = duk_get_this__p<AnyWndClass>(ctx);
			if (!pobj)
				return DUK_RET_REFERENCE_ERROR;
			WORD atom = 0;
			if (wx_try(ctx, [&] { atom = pobj->Register(); }))
				return DUK_RET_REFERENCE_ERROR;
			duk_push_uint(ctx, atom);
			return 1;
		});
		/* void */ duk_put_method(ctx, "Unregister", 0, duk_fn {
			auto pobj = duk_get_this__p<AnyWndClass>(ctx);
			if (!pobj)
				return DUK_RET_REFERENCE_ERROR;
			if (wx_try(ctx, [&] { pobj->Unregister(); }))
				return DUK_RET_REFERENCE_ERROR;
			return 0;
		});
		/* void */ duk_put_method(ctx, "GetInfo", 0, duk_fn {
			auto pobj = duk_get_this__p<AnyWndClass>(ctx);
			if (!pobj)
				return DUK_RET_REFERENCE_ERROR;
			if (wx_try(ctx, [&] { pobj->GetInfo(); }))
				return DUK_RET_REFERENCE_ERROR;
			return 0;
		});
	};
	static auto __WndClass_constructor = [](auto alfa) {
		using AnyWndClass = decltype(alfa);
		return duk_fn {
			if (duk_reflect_constructor(ctx))
				return 1;
			AnyWndClass *pobj = O;
			switch (duk_get_top(ctx)) {
				case 0: {
					pobj = duk_put_cstruct<AnyWndClass>(ctx);
					break;
				}
				case 1: {
					duk_size_t size = 0;
					if (auto ptr = (AnyWndClass *)duk_get_buffer_data(ctx, 0, &size)) {
						duk_push_this(ctx);
						duk_push_string(ctx, "__p");
						duk_dup(ctx, 0);
						duk_def_prop(ctx, -3, DUK_DEFPROP_PRIVATE_CONST);
					}
				}
			}
			return 0;
		};
	};
	duk_put_global_class(
		ctx, "WindowClass", O,
		duk_fn {
			__WndClass_properties(ctx, WindowClassA{});
			return 0;
		},
		__WndClass_constructor(WindowClassA{})
	);
	duk_put_global_class(
		ctx, "WindowClassEx", O,
		duk_fn {
			__WndClass_properties(ctx, WindowClassExA{});
			duk_put_prop(ctx, "IconSm",
				duk_fn {
					auto pobj = duk_get_this__p<WindowClassExA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					HICON hIcon = O;
					if (!duk_get_class__p(ctx, "IconSmall", hIcon))
						return DUK_RET_TYPE_ERROR;
					pobj->IconSmall(hIcon);
					return 0;
				},
				duk_fn {
					auto pobj = duk_get_this__p<WindowClassExA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Icon", pobj->IconSmall());
					return 1;
				}
			);
			return 0;
		},
		__WndClass_constructor(WindowClassExA{})
	);
#pragma endregion

#pragma region CreateStruct
	duk_put_global_class(
		ctx, "CreateStruct", O, 
		duk_structure {
			duk_put_prop(
				/* Module */ ctx, "Module",
				duk_set_safe<CreateStructA>([](duk_context *ctx, CreateStructA *pobj) {
					HMODULE hModule = O;
					if (!duk_get_class__p(ctx, "Module", hModule))
						return DUK_RET_TYPE_ERROR;
					pobj->Module(hModule);
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CreateStructA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Module", pobj->Module());
					return 1;
				}
			);
			duk_put_prop(
				/* Menu */ ctx, "Menu",
				duk_set_safe<CreateStructA>([](duk_context *ctx, CreateStructA *pobj) {
					HMENU hMenu = O;
					if (!duk_get_class__p(ctx, "Menu", hMenu))
						return DUK_RET_TYPE_ERROR;
					pobj->Menu(hMenu);
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CreateStructA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Menu", pobj->Menu());
					return 1;
				}
			);
			duk_put_prop(
				/* Window */ ctx, "Parent",
				duk_set_safe<CreateStructA>([](duk_context *ctx, CreateStructA *pobj) {
					HWND hWnd = O;
					if (!duk_get_class__p(ctx, "Window", hWnd))
						return DUK_RET_TYPE_ERROR;
					pobj->Parent(hWnd);
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CreateStructA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Window", pobj->Parent());
					return 1;
				}
			);
			duk_put_prop(
				/* WS */ ctx, "Styles",
				duk_set_safe<CreateStructA>([](duk_context *ctx, CreateStructA *pobj) {
					pobj->Styles(reuse_as<WS>(duk_to_int(ctx, 0)));
				}),
				duk_get {
					auto pobj = duk_get_this__p<CreateStructA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "WindowStyle", pobj->Styles().yield());
					return 1;
				}
			);
			duk_put_prop(
				/* String */ ctx, "Caption",
				duk_set_safe<CreateStructA>([](duk_context *ctx, CreateStructA *pobj) {
					pobj->Caption(duk_to_string(ctx, 0));
				}),
				duk_get {
					auto pobj = duk_get_this__p<CreateStructA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_string(ctx, pobj->Caption());
					return 1;
				}
			);
			duk_put_prop(
				/* WSEX */ ctx, "StylesEx",
				duk_set_safe<CreateStructA>([](duk_context *ctx, CreateStructA *pobj) {
					pobj->StylesEx(reuse_as<WSEX>(duk_to_int(ctx, 0)));
				}),
				duk_get {
					auto pobj = duk_get_this__p<CreateStructA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "WindowStyleEx", pobj->StylesEx().yield());
					return 1;
				}
			);
			duk_put_prop(
				/* Point */ ctx, "Size",
				duk_set_safe<CreateStructA>([](duk_context *ctx, CreateStructA *pobj) {
					LPoint Size;
					if (!duk_get_point(ctx, Size, 0))
						return DUK_RET_TYPE_ERROR;
					pobj->Size(Size);
					return 0;
				}),
 				duk_get {
					auto pobj = duk_get_this__p<CreateStructA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_point(ctx, pobj->Size());
					return 1;
				}
			);
			duk_put_prop(
				/* Point */ ctx, "Position",
				duk_set_safe<CreateStructA>([](duk_context *ctx, CreateStructA *pobj) {
					LPoint Pos;
					if (!duk_get_point(ctx, Pos, 0))
						return DUK_RET_TYPE_ERROR;
					pobj->Position(Pos);
					return 0;
				}),
 				duk_get {
					auto pobj = duk_get_this__p<CreateStructA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_point(ctx, pobj->Position());
					return 1;
				}
			);
			duk_put_prop(
				/* Rect */ ctx, "Rect",
				duk_set_safe<CreateStructA>([](duk_context *ctx, CreateStructA *pobj) {
					LRect rc;
					if (!duk_get_rect(ctx, rc, 0))
						return DUK_RET_TYPE_ERROR;
					pobj->Rect(rc);
					return 0;
				}),
 				duk_get {
					auto pobj = duk_get_this__p<CreateStructA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_rect(ctx, pobj->Rect());
					return 1;
				}
			);
			/* void */ duk_put_method(ctx, "ClientRect", 2, duk_fn {
				auto pobj = duk_get_this__p<CreateStructA>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0))
					return DUK_RET_TYPE_ERROR;
				if (duk_is_undefined(ctx, 1))
					pobj->ClientRect(rc);
				else
					pobj->ClientRect(rc, duk_to_uint(ctx, 1));
				return 0;
			});
			/* void */ duk_put_method(ctx, "ClientSize", 2, duk_fn {
				auto pobj = duk_get_this__p<CreateStructA>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				LPoint Size;
				if (!duk_get_point(ctx, Size, 0))
					return DUK_RET_TYPE_ERROR;
				if (duk_is_undefined(ctx, 1))
					pobj->ClientSize(Size);
				else
					pobj->ClientSize(Size, duk_to_uint(ctx, 1));
				return 0;
			});
			return 0;
		},
		duk_constructor {
			if (duk_reflect_constructor(ctx))
				return 1;
			CreateStructA *pobj = O;
			switch (duk_get_top(ctx)) {
				case 0: {
					pobj = duk_put_cstruct<CreateStructA>(ctx);
					break;
				}
				case 1: {
					if (duk_is_object(ctx, 0)) {
						duk_push_current_function(ctx);
						if (!duk_instanceof(ctx, -1, 0))
							return DUK_RET_TYPE_ERROR;
						duk_get_prop_string(ctx, 0, "__p");
						duk_insert(ctx, 0);
					}
					if (duk_is_buffer(ctx, 0)) {
						auto pobj = duk_get_this__p<CreateStructA>(ctx);
						duk_push_this(ctx);
						duk_push_string(ctx, "__p");
						duk_dup(ctx, 0);
						duk_def_prop(ctx, -3, DUK_DEFPROP_PRIVATE_CONST);
					}
					else
						return DUK_RET_TYPE_ERROR;
					break;
				}
			}
			return 0;
		}
	);
#pragma endregion

	duk_put_global_class(
		ctx, "Window", O,
		duk_structure {
			/* void */ duk_put_method(ctx, "Destroy", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Destroy(); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "Close", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Close(); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "Delete", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Delete(); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});

#pragma region Method
			/* void */ duk_put_method(ctx, "Hide", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Hide(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* void */ duk_put_method(ctx, "ShowNormal", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->ShowNormal(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* void */ duk_put_method(ctx, "Normal", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Normal(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* void */ duk_put_method(ctx, "ShowMinimized", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->ShowMinimized(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* void */ duk_put_method(ctx, "ShowMaximized", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->ShowMaximized(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* void */ duk_put_method(ctx, "Maximize", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Maximize(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* void */ duk_put_method(ctx, "ShowNoActivate", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->ShowNoActivate(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* void */ duk_put_method(ctx, "Show", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Show(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* void */ duk_put_method(ctx, "Minimize", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Minimize(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* void */ duk_put_method(ctx, "ShowMinNoActive", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->ShowMinNoActive(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* void */ duk_put_method(ctx, "ShowNA", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->ShowNA(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* void */ duk_put_method(ctx, "Restore", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Restore(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* void */ duk_put_method(ctx, "ShowDefault", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->ShowDefault(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* void */ duk_put_method(ctx, "ForceMinimize", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->ForceMinimize(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* void */ duk_put_method(ctx, "Max", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Max(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});

			/* void */ duk_put_method(ctx, "BringToTop", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->BringToTop(); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* int */ duk_put_method(ctx, "MsgBox", 3, duk_fn{
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				auto nargs = duk_get_top(ctx);
				LPCSTR lpCaption = duk_to_string(ctx, 0);
				LPCSTR lpText = duk_to_string(ctx, 1);
				MB uType = nargs > 2 ? reuse_as<MB>(duk_to_int(ctx, 2)) : (MB)MB::Ok;
				int res = -1;
				if (wx_try(ctx, [&] { res = pobj->MsgBox(lpCaption, lpText, uType); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_int(ctx, res);
				return 1;
			});
			/* void */ duk_put_method(ctx, "Focus", 0, duk_fn{
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Focus(); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* bool */ duk_put_method(ctx, "IsFocus", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				bool res = false;
				if (wx_try(ctx, [&] { res = pobj->IsFocus(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_boolean(ctx, res);
				return 1;
			});
			/* Point */ duk_put_method(ctx, "ScreenToClient", 1, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				LPoint pt;
				if (!duk_get_point(ctx, pt, 0))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&] { pobj->ScreenToClient(pt); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_point(ctx, pt);
				return 1;
			});
			/* Point */ duk_put_method(ctx, "ClientToScreen", 1, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				LPoint pt;
				if (!duk_get_point(ctx, pt, 0))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&] { pobj->ClientToScreen(pt); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_point(ctx, pt);
				return 1;
			});
			/* Rect */ duk_put_method(ctx, "AdjustRect", 1, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&] { pobj->AdjustRect(rc); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_rect(ctx, rc);
				return 1;
			});
			/* void */ duk_put_method(ctx, "Move", 2, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0)) 
					return DUK_RET_TYPE_ERROR;
				bool bRedraw = duk_is_undefined(ctx, 1) ? true : duk_to_boolean(ctx, 1);
				if (wx_try(ctx, [&] { pobj->Move(rc, bRedraw); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "Update", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Update(); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "RegisterTouch", 2, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				bool bFine = duk_is_undefined(ctx, 0) ? true : duk_to_boolean(ctx, 1);
				bool bWantPalm = duk_is_undefined(ctx, 1) ? false : duk_to_boolean(ctx, 1);
				if (wx_try(ctx, [&] { pobj->RegisterTouch(bFine, bWantPalm); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "UnregisterTouch", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->UnregisterTouch(); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "HasChild", 1, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				HWND hWnd = O;
				if (!duk_get_class__p(ctx, "Window", hWnd))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&] { pobj->HasChild(hWnd); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "EnumChild", 1, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (!duk_is_callable(ctx, 0))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&] {
					pobj->EnumChild([&](HWND hWnd) {
						duk_dup(ctx, 0);
						duk_push_new_cclass(ctx, "Window", hWnd);
						duk_call(ctx, 1);
						bool res = duk_is_undefined(ctx, -1) ? true : duk_to_boolean(ctx, -1);
						duk_pop(ctx);
						return res;
					});
				}))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "EnumProp", 1, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (!duk_is_callable(ctx, 0))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&] {
					pobj->EnumProp([&](HWND hWnd, LPCSTR lpString, HANDLE hData) {
						duk_dup(ctx, 0);
						duk_push_new_cclass(ctx, "Window", hWnd);
						duk_push_string(ctx, lpString);
						duk_push_pointer(ctx, hData);
						duk_call(ctx, 1);
						bool res = duk_is_undefined(ctx, -1) ? true : duk_to_boolean(ctx, -1);
						duk_pop(ctx);
						return res;
					});
				}))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});

			/* bool */ duk_put_method(ctx, "valueOf", 0, duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				bool res = false;
				if (wx_try(ctx, [&] { res = *pobj; }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_boolean(ctx, res);
				return 1;
			});
#pragma endregion

#pragma region Properties
			/* bool */ duk_put_prop_r(ctx, "Iconic", duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				bool res = false;
				if (wx_try(ctx, [&] { res = pobj->Iconic(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_boolean(ctx, res);
				return 1;
			});
			/* bool */ duk_put_prop_r(ctx, "Zoomed", duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				bool res = false;
				if (wx_try(ctx, [&] { res = pobj->Zoomed(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_boolean(ctx, res);
				return 1;
			});
			duk_put_prop(
				/* bool */ ctx, "Visible",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					if (wx_try(ctx, [&] { pobj->Visible(duk_to_boolean(ctx, 0)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					bool res = false;
					if (wx_try(ctx, [&] { res = pobj->Visible(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_boolean(ctx, res);
					return 1;
				}
			);
			duk_put_prop(
				/* bool */ ctx, "Enabled",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					if (wx_try(ctx, [&] { pobj->Enabled(duk_to_boolean(ctx, 0)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					bool res = false;
					if (wx_try(ctx, [&] { res = pobj->Enabled(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_boolean(ctx, res);
					return 1;
				}
			);
			/* Point */ duk_put_prop_r(ctx, "ClientRect", duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				LRect rc;
				if (wx_try(ctx, [&] { rc = pobj->ClientRect(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_rect(ctx, rc);
				return 1;
			});
			/* Point */ duk_put_prop_r(ctx, "ClientSize", duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				LPoint Size;
				if (wx_try(ctx, [&] { Size = pobj->ClientSize(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_point(ctx, Size);
				return 1;
			});
			duk_put_prop(
				/* Point */ ctx, "Position",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					LPoint Pos;
					if (!duk_get_point(ctx, Pos, 0))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->Position(Pos); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
 				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					LPoint Pos;
					if (wx_try(ctx, [&] { Pos = pobj->Position(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_point(ctx, Pos);
					return 1;
				}
			);
			duk_put_prop(
				/* Point */ ctx, "Size",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					LPoint Size;
					if (!duk_get_point(ctx, Size, 0))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->Size(Size); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
 				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					LPoint Size;
					if (wx_try(ctx, [&] { Size = pobj->Size(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_point(ctx, Size);
					return 1;
				}
			);
			duk_put_prop(
				/* Rect */ ctx, "Rect",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					LRect rc;
					if (!duk_get_rect(ctx, rc, 0))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->Rect(rc); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
 				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					LRect rc;
					if (wx_try(ctx, [&] { rc = pobj->Rect(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_rect(ctx, rc);
					return 1;
				}
			);
			duk_put_prop(
				/* WindowPlacement */ ctx, "Placement",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					duk_get_global_string(ctx, "WindowPlacement");
					if (!duk_instanceof(ctx, 0, -1))
						return DUK_RET_TYPE_ERROR;
					duk_get_prop_string(ctx, -1, "__p");
					duk_size_t read_size = 0;
					auto pPlacement = (WINDOWPLACEMENT *)duk_get_buffer(ctx, -1, &read_size);
					if (read_size != sizeof(WINDOWPLACEMENT)) {
						duk_errout(ctx, "Buffer invalid");
						return DUK_RET_TYPE_ERROR;
					}
					if (wx_try(ctx, [&] { pobj->Placement(*pPlacement); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
 				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_get_global_string(ctx, "WindowPlacement");
					auto pPlacement = (WindowPlacement *)duk_push_fixed_buffer(ctx, sizeof(WindowPlacement));
					if (wx_try(ctx, [&] { *pPlacement = pobj->Placement(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_new(ctx, 1);
					return 1;
				}
			);
			duk_put_prop_r(
				/* WindowInfo */ ctx, "Info",
 				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_get_global_string(ctx, "WindowInfo");
					auto pInfo = (WindowInfo *)duk_push_fixed_buffer(ctx, sizeof(WindowInfo));
					if (wx_try(ctx, [&] { *pInfo = pobj->Info(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_new(ctx, 1);
					return 1;
				}
			);
			duk_put_prop_r(
				/* uint */ ctx, "TextLength", duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					if (wx_try(ctx, [&] { duk_push_uint(ctx, pobj->TextLengthA()); }))
						return DUK_RET_REFERENCE_ERROR;
					return 1;
				}
			);
			duk_put_prop(
				/* String */ ctx, "Text",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					if (wx_try(ctx, [&] { pobj->Text(duk_to_string(ctx, 0)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					if (wx_try(ctx, [&] { duk_push_string(ctx, pobj->TextA()); }))
						return DUK_RET_REFERENCE_ERROR;
					return 1;
				}
			);
			/* String */ duk_put_prop_r(ctx, "ModuleFileName", duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				StringA res = O;
				if (wx_try(ctx, [&] { res = pobj->ModuleFileNameA(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_string(ctx, res);
				return 1;
			});
			duk_put_prop(
				/* Window */ ctx, "Parent",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					HWND hParent = O; 
					if (!duk_get_class__p(ctx, "Window", hParent))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->Parent(hParent); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					HWND hParent = O;
					if (wx_try(ctx, [&] { hParent = pobj->Parent(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Window", hParent);
					return 1;
				}
			);
			duk_put_prop_r(
				/* Window */ ctx, "Next",
				duk_get{
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Window", pobj->Next());
					return 1;
				}
			);
			duk_put_prop_r(
				/* Window */ ctx, "Prev",
				duk_get{
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Window", pobj->Prev());
					return 1;
				}
			);
			duk_put_prop(
				/* Menu */ ctx, "Menu",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					HMENU hMenu = O;
					if (!duk_get_class__p(ctx, "Menu", hMenu))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->Menu(hMenu); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					HMENU hMenu = O;
					if (wx_try(ctx, [&] { hMenu = pobj->Menu(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Menu", hMenu);
					return 1;
				}
			);
			/* Menu */ duk_put_prop_r(ctx, "SysMenu", duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				HMENU hMenu = O;
				if (wx_try(ctx, [&] { hMenu = pobj->SysMenu(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_cclass(ctx, "Menu", hMenu);
				return 1;
			});
			/* Region */ duk_put_prop(ctx, "Region", ////////////////////////////
				duk_set {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					HRGN hRgn = O;
					if (!duk_get_class__p(ctx, "Region", hRgn))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->Region(hRgn); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					HRGN hRgn = O;
					//if (wx_try(ctx, [&] { hRgn = pobj->Region(); }))
					//	return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Region", hRgn);
					return 1;
				}
			);
			duk_put_prop(
				/* Icon */ ctx, "Icon",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					HICON hIcon = O;
					if (!duk_get_class__p(ctx, "Icon", hIcon))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->Icon(hIcon); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					HICON hIcon = O;
					if (wx_try(ctx, [&] { hIcon = pobj->Icon(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Icon", hIcon);
					return 1;
				}
			);
			duk_put_prop(
				/* Icon */ ctx, "IconSmall",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					HICON hIcon = O;
					if (!duk_get_class__p(ctx, "Icon", hIcon))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->IconSmall(hIcon); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					HICON hIcon = O;
					if (wx_try(ctx, [&] { hIcon = pobj->IconSmall(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Icon", hIcon);
					return 1;
				}
			);
			duk_put_prop(
				/* Icon */ ctx, "IconSmall2",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					HICON hIcon = O;
					if (!duk_get_class__p(ctx, "Icon", hIcon))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->IconSmall2(hIcon); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					HICON hIcon = O;
					if (wx_try(ctx, [&] { hIcon = pobj->IconSmall2(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Icon", hIcon);
					return 1;
				}
			);
#pragma region Window Extra
			/* WindowProcedure */ ////////////////////////////////////////////
			duk_put_prop(
				/* Module */ ctx, "Module",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					HMODULE hModule = O;
					if (!duk_get_class__p(ctx, "Module", hModule))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->Module(hModule); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					HMODULE hModule = O;
					if (wx_try(ctx, [&] { hModule = pobj->Module(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Module", hModule);
					return 1;
				}
			);
			duk_put_prop(
				/* Window */ ctx, "HwndParent",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					HWND hParent = O; 
					if (!duk_get_class__p(ctx, "Window", hParent))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->HwndParent(hParent); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					HWND hParent = O;
					if (wx_try(ctx, [&] { hParent = pobj->HwndParent(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Window", hParent);
					return 1;
				}
			);
			duk_put_prop(
				/* WS */ ctx, "Styles",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					if (wx_try(ctx, [&] { pobj->Styles(reuse_as<WStyle>(duk_to_int(ctx, 0))); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
 				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					WStyle styles = WStyle::Overlapped;
					if (wx_try(ctx, [&] { styles = pobj->Styles(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "WindowStyle", styles.yield());
					return 1;
				}
			);
			duk_put_prop(
				/* WSEX */ ctx, "StylesEx",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					if (wx_try(ctx, [&] { pobj->StylesEx(reuse_as<WStyleEx>(duk_to_int(ctx, 0))); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
 				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					WStyleEx styles = WStyleEx::No;
					if (wx_try(ctx, [&] { styles = pobj->StylesEx(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "WindowStyleEx", styles.yield());
					return 1;
				}
			);
			/* pointer */ duk_put_prop(ctx, "UserData", ///////////////
				duk_set {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					if (wx_try(ctx, [&] { pobj->UserData(duk_to_int(ctx, 0)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					LONG_PTR data = 0;
					if (wx_try(ctx, [&] { data = pobj->UserData(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, (duk_int_t)data);
					return 1;
				}
			);
			/* long_ptr */ duk_put_prop(ctx, "ID", ///////////////
				duk_set {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					if (wx_try(ctx, [&] { pobj->ID(duk_to_int(ctx, 0)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					LONG_PTR uID = 0;
					if (wx_try(ctx, [&] { uID = pobj->ID(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, (duk_int_t)uID);
					return 1;
				}
			);
#pragma endregion
			/* String */ duk_put_prop_r(ctx, "ClassName", duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				StringA res = O;
				if (wx_try(ctx, [&] { res = pobj->ClassNameA(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_string(ctx, res);
				return 1;
			});
#pragma region Window Class Extra
			/* Atom */ duk_put_prop(ctx, "ClassAtom", ////////////////////////
				duk_set { 
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					auto atom = duk_to_uint16(ctx, 0);
					if (wx_try(ctx, [&] { pobj->ClassAtom(atom); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_uint16_t atom = 0;
					if (wx_try(ctx, [&] { atom = pobj->ClassAtom(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_uint(ctx, atom);
					return 1;
				}
			);
			/* String */ duk_put_prop(ctx, "ClassMenuName", ////////////////////////
				duk_set {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					if (wx_try(ctx, [&] { pobj->ClassMenuName(duk_to_string(ctx, 0)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					LPCSTR res = O;
					if (wx_try(ctx, [&] { res = pobj->ClassMenuNameA(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_string(ctx, res);
					return 1;
				}
			);
			duk_put_prop(
				/* ClassStyle */ ctx, "ClassStyles",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					if (wx_try(ctx, [&] { pobj->ClassStyles(reuse_as<ClassStyle>(duk_to_int(ctx, 0))); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					ClassStyle styles = ClassStyle::VRedraw;
					if (wx_try(ctx, [&] { styles = pobj->ClassStyles(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "ClassStyle", styles.yield());
					return 1;
				}
			);
			duk_put_prop(
				/* Brush */ ctx, "ClassBackground",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					HBRUSH hBrush = O;
					if (!duk_get_class__p(ctx, "Brush", hBrush))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->ClassBackground(hBrush); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					HBRUSH hBrush = O;
					if (wx_try(ctx, [&] { hBrush = pobj->ClassBackground(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Brush", hBrush);
					return 1;
				}
			);
			duk_put_prop(
				/* Cursor */ ctx, "ClassCursor",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					HCURSOR hCursor = O;
					if (!duk_get_class__p(ctx, "Cursor", hCursor))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->ClassCursor(hCursor); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					HCURSOR hCursor = O;
					if (wx_try(ctx, [&] { hCursor = pobj->ClassCursor(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Cursor", hCursor);
					return 1;
				}
			);
			duk_put_prop(
				/* Icon */ ctx, "ClassIcon",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					HICON hIcon = O;
					if (!duk_get_class__p(ctx, "Icon", hIcon))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->ClassIcon(hIcon); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					HICON hIcon = O;
					if (wx_try(ctx, [&] { hIcon = pobj->ClassIcon(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Icon", hIcon);
					return 1;
				}
			);
			duk_put_prop(
				/* Module */ ctx, "ClassModule",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					HMODULE hModule = O;
					if (!duk_get_class__p(ctx, "Module", hModule))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->ClassModule(hModule); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					HMODULE hModule = O;
					if (wx_try(ctx, [&] { hModule = pobj->ClassModule(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Module", hModule);
					return 1;
				}
			);
			duk_put_prop(
				/* uint_ptr */ ctx, "ClassWndExtra",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					if (wx_try(ctx, [&] { pobj->ClassWndExtra(duk_to_uint(ctx, 0)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_uint_t extra = 0;
					if (wx_try(ctx, [&] { extra = (duk_uint_t)pobj->ClassWndExtra(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_uint(ctx, extra);
					return 1;
				}
			);
			duk_put_prop(
				/* uint_ptr */ ctx, "ClassClsExtra",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					if (wx_try(ctx, [&] { pobj->ClassClsExtra(duk_to_uint(ctx, 0)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_uint_t extra = 0;
					if (wx_try(ctx, [&] { extra = (duk_uint_t)pobj->ClassClsExtra(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_uint(ctx, extra);
					return 1;
				}
			);
			/* WindowProcedure */ ////////////////////////////////////////////
			duk_put_prop(
				/* Icon */ ctx, "ClassIconSmall",
				duk_set_safe<CWindow>([](duk_context *ctx, CWindow pobj) {
					HICON hIcon = O;
					if (!duk_get_class__p(ctx, "Icon", hIcon))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->ClassIconSmall(hIcon); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				}),
				duk_get {
					auto pobj = duk_get_this__p<CWindow>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					HICON hIcon = O;
					if (wx_try(ctx, [&] { hIcon = pobj->ClassIconSmall(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_new_cclass(ctx, "Icon", hIcon);
					return 1;
				}
			);
#pragma endregion
			/* WindowClass */ duk_put_prop_r(ctx, "Class", duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				duk_get_global_string(ctx, "WindowClass");
				auto pWndClass = (WindowClassA *)duk_push_fixed_buffer(ctx, sizeof(WindowClassA));
				if (wx_try(ctx, [&] { *pWndClass = pobj->ClassA(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_new(ctx, 1);
				return 1;
			});
			/* WindowClassEx */ duk_put_prop_r(ctx, "ClassEx", duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				duk_get_global_string(ctx, "WindowClassEx");
				auto pWndClass = (WindowClassExA *)duk_push_fixed_buffer(ctx, sizeof(WindowClassExA));
				if (wx_try(ctx, [&] { *pWndClass = pobj->ClassExA(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_new(ctx, 1);
				return 1;
			});
			/* DevCap */ duk_put_prop_r(ctx, "DC", duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				HDC hdc = O;
				if (wx_try(ctx, [&] { hdc = pobj->DC(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_cclass(ctx, "DevCap", hdc);
				return 1;
			});
			/* uint */ duk_put_prop_r(ctx, "ProcessId", duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				DWORD res = 0;
				if (wx_try(ctx, [&] { res = pobj->ProcessId(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_uint(ctx, res);
				return 1;
			});
			/* uint */ duk_put_prop_r(ctx, "ThreadId", duk_fn {
				auto pobj = duk_get_this__p<CWindow>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				DWORD res = 0;
				if (wx_try(ctx, [&] { res = pobj->ThreadId(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_uint(ctx, res);
				return 1;
			});
#pragma endregion
			return 0;
		},
		duk_constructor {
			if (!duk_is_constructor_call(ctx))
				return 0;
			switch (duk_get_top(ctx)) {
				case 0:
					break;
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_put_this__p(ctx, duk_get_pointer(ctx, 0));
						return 0;
					}
					if (duk_is_object(ctx, 0)) {
						duk_get_global_string(ctx, "CreateStruct");
						if (duk_instanceof(ctx, 0, -1)) {
							duk_get_prop_string(ctx, 0, "__p");
							duk_size_t size = 0;
							auto pCS = (CreateStructA *)duk_get_buffer(ctx, -1, &size);
							if (!pCS || size != sizeof(CreateStructA))
								return DUK_RET_TYPE_ERROR;
						}
					}
					break;
				default:
					return 0;
			}
			duk_push_this(ctx);
			duk_put_destructor(ctx, duk_fn {
				if (auto pobj = duk_get_this__p<CWindow>(ctx))
					if (wx_try(ctx, [&] { pobj->Destroy(); }))
						return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			return 0;
		},
		duk_static {
			duk_put_method(
				/* Window */ ctx, "Find", 2, duk_fn {
					LPCSTR lpszName = O, lpszClass = O;
					if (!duk_is_undefined(ctx, 1))
						lpszClass = duk_to_string(ctx, 1);
					lpszName = duk_to_string(ctx, 0);
					if (wx_try(ctx, [&] { duk_push_new_cclass(ctx, "Window", Window::Find(lpszName, lpszClass)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 1;
				}
			);
			duk_put_prop_r(
				/* Window */ ctx, "Focussed", duk_fn {
					if (wx_try(ctx, [&] { duk_push_new_cclass(ctx, "Window", Window::Focussed()); }))
						return DUK_RET_REFERENCE_ERROR;
					return 1;
				}
			);
			duk_put_prop_r(
				/* Window */ ctx, "Active", duk_fn {
					if (wx_try(ctx, [&] { duk_push_new_cclass(ctx, "Window", Window::Active()); }))
						return DUK_RET_REFERENCE_ERROR;
					return 1;
				}
			);
			duk_put_prop_r(
				/* Window */ ctx, "Desktop", duk_fn {
					if (wx_try(ctx, [&] { duk_push_new_cclass(ctx, "Window", Window::Desktop()); }))
						return DUK_RET_REFERENCE_ERROR;
					return 1;
				}
			);
			duk_put_prop(
				/* Window */ ctx, "Foreground",
				duk_set {
					HWND hWnd = O;
					if (!duk_get_class__p(ctx, "Window", hWnd))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { Window::Foreground(hWnd); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					if (wx_try(ctx, [&] { duk_push_new_cclass(ctx, "Window", Window::Foreground()); }))
						return DUK_RET_REFERENCE_ERROR;
					return 1;
				});
			return 0;
		}
	);

}
