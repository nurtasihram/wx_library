#include "wx_window.h"

#include "wx_duk.h"

using namespace WX;

template<class AnyClosure>
static bool _try_method(duk_context *ctx, const AnyClosure &closure) {
	if (auto obj = reuse_as<CWindow>(duk_member_handle(ctx))) 
		return wx_try(ctx, [&]() { closure(ctx, obj); });
	duk_errout(ctx, "Window method called on non-window object");
	return false;
}

void load_duk_window(duk_context *ctx) {

	static const duk_constant_struct _MB_constant[]{
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
	duk_flags(ctx, "FlagsObj", "MB", O, _MB_constant);
	duk_function_global(ctx, "MsgBox", [](duk_context *ctx) -> duk_ret_t {
		auto nargs = duk_get_top(ctx);
		LPCSTR lpCaption = duk_is_undefined(ctx, 0) ? "" : duk_to_string(ctx, 0);
		LPCSTR lpText = duk_is_undefined(ctx, 1) ? "" : duk_to_string(ctx, 1);
		MB uType = nargs > 2 ? reuse_as<MB>(duk_to_int(ctx, 2)) : (MB)MB::Ok;
		auto res = MsgBox(lpCaption, lpText, uType);
		duk_push_int(ctx, res);
		return 1;
	}, 3);

#pragma region Window
	static const duk_constant_struct _WS_constant[]{
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
	duk_flags(ctx, "FlagsObj", "WS", O, _WS_constant);
	static const duk_constant_struct _WSEX_constant[]{
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
	duk_flags(ctx, "FlagsObj", "WSEX", O, _WSEX_constant);
	duk_struct_global(ctx, "WObj", [](duk_context *ctx) -> duk_ret_t {

#pragma region Methods
#pragma region ShowWindow
		duk_method(ctx, "Hide", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Hide(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "ShowNormal", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->ShowNormal(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "Normal", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Normal(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "ShowMinimized", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->ShowMinimized(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "ShowMaximized", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->ShowMaximized(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "Maximize", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Maximize(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "ShowNoActivate", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->ShowNoActivate(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "Show", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Show(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "Minimize", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Minimize(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "ShowMinNoActive", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->ShowMinNoActive(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "ShowNA", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->ShowNA(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "Restore", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Restore(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "ShowDefault", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->ShowDefault(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "ForceMinimize", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->ForceMinimize(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "Max", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Max(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
#pragma endregion
		duk_method(ctx, "BringToTop", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->BringToTop(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "MsgBox", 3, [](duk_context *ctx) -> duk_ret_t {
			auto nargs = duk_get_top(ctx);
			LPCSTR lpCaption = duk_to_string(ctx, 0);
			LPCSTR lpText = duk_to_string(ctx, 1);
			MB uType = nargs > 2 ? reuse_as<MB>(duk_to_int(ctx, 2)) : (MB)MB::Ok;
			int res = -1;
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { res = obj->MsgBox(lpCaption, lpText, uType); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_int(ctx, res);
			return 1;
		});
		duk_method(ctx, "Focus", 0, [](duk_context *ctx) -> duk_ret_t {
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Focus(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_this(ctx);
			return 1;
		});
		duk_method(ctx, "IsFocus", 0, [](duk_context *ctx) -> duk_ret_t {
			bool res = false;
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { res = obj->IsFocus(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_boolean(ctx, res);
			return 1;
		});
		duk_method(ctx, "ScreenToClient", 1, [](duk_context *ctx) -> duk_ret_t {
			LPoint pt;
			if (!duk_get_point(ctx, pt, 0)) {
				duk_errout(ctx, "Window.ScreenToClient: first argument must be a Point object");
				return DUK_RET_TYPE_ERROR;
			}
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->ScreenToClient(pt); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_point(ctx, pt);
			return 1;
		});
		duk_method(ctx, "ClientToScreen", 1, [](duk_context *ctx) -> duk_ret_t {
			LPoint pt;
			if (!duk_get_point(ctx, pt, 0)) {
				duk_errout(ctx, "Window.ClientToScreen: first argument must be a Point object");
				return DUK_RET_TYPE_ERROR;
			}
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->ClientToScreen(pt); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_point(ctx, pt);
			return 1;
		});
		duk_method(ctx, "AdjustRect", 1, [](duk_context *ctx) -> duk_ret_t {
			LRect rc;
			if (!duk_get_rect(ctx, rc, 0)) {
				duk_errout(ctx, "Window.AdjustRect: first argument must be a Rect object");
				return DUK_RET_TYPE_ERROR;
			}
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->AdjustRect(rc); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_rect(ctx, rc);
			return 1;
		});
#pragma endregion

#pragma region Properties
		/* RO bool Minimized */
		duk_property_r(ctx, "Minimized",
			[](duk_context *ctx) -> duk_ret_t {
				bool res = false;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { res = obj->Iconic(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_boolean(ctx, res);
				return 1;
			}
		);
		/* WR bool Visible */
		duk_property(ctx, "Visible",
			[](duk_context *ctx) -> duk_ret_t {
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Visible(duk_to_boolean(ctx, 0)); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				bool res = false;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { res = obj->Visible(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_boolean(ctx, res);
				return 1;
			}
		);
		/* WR bool Enabled */
		duk_property(ctx, "Enabled",
			[](duk_context *ctx) -> duk_ret_t {
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Enabled(duk_to_boolean(ctx, 0)); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				bool res = false;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { res = obj->Enabled(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_boolean(ctx, res);
				return 1;
			}
		);
		/* WR int ID */
		duk_property(ctx, "ID",
			[](duk_context *ctx) -> duk_ret_t {
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->ID(duk_to_int(ctx, 0)); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				LONG_PTR res = 0;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { res = obj->ID(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_int(ctx, (duk_int_t)res);
				return 1;
			}
		);
		/* RO Point ClientRect */
		duk_property_r(ctx, "ClientRect", [](duk_context *ctx) -> duk_ret_t {
			LRect rc;
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { rc = obj->ClientRect(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_rect(ctx, rc);
			return 1;
		});
		/* RO Point ClientSize */
		duk_property_r(ctx, "ClientSize", [](duk_context *ctx) -> duk_ret_t {
			LPoint Size;
			if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { Size = obj->ClientSize(); }))
				return DUK_RET_INTERNAL_ERROR;
			duk_push_point(ctx, Size);
			return 1;
		});
		/* WR Point Position */
		duk_property(ctx, "Position", 
			[](duk_context *ctx) -> duk_ret_t {
				LPoint Pos;
				if (!duk_get_point(ctx, Pos, 0)) {
					duk_errout(ctx, "Window.Position: first argument must be a Point object");
					return DUK_RET_TYPE_ERROR;
				}
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Position(Pos); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
 			[](duk_context *ctx) -> duk_ret_t {
				LPoint Pos;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { Pos = obj->Position(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_point(ctx, Pos);
				return 1;
			}
		);
		/* WR Point Size */
		duk_property(ctx, "Size", 
			[](duk_context *ctx) -> duk_ret_t {
				LPoint Size;
				if (!duk_get_point(ctx, Size, 0)) {
					duk_errout(ctx, "Window.Size: first argument must be a Point object");
					return DUK_RET_TYPE_ERROR;
				}
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Size(Size); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
 			[](duk_context *ctx) -> duk_ret_t {
				LPoint Size;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { Size = obj->Size(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_point(ctx, Size);
				return 1;
			}
		);
		/* WR Rect Rect */
		duk_property(ctx, "Rect", 
			[](duk_context *ctx) -> duk_ret_t {
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0)) {
					duk_errout(ctx, "Window.Rect: first argument must be a Point object");
					return DUK_RET_TYPE_ERROR;
				}
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Rect(rc); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
 			[](duk_context *ctx) -> duk_ret_t {
				LRect rc;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { rc = obj->Rect(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_rect(ctx, rc);
				return 1;
			}
		);
		/* WR int Styles */
		duk_property(ctx, "Styles", 
			[](duk_context *ctx) -> duk_ret_t {
				auto styles = duk_to_int(ctx, 0);
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Styles(reuse_as<WStyle>(styles)); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
 			[](duk_context *ctx) -> duk_ret_t {
				WStyle styles = WStyle::Overlapped;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { styles = obj->Styles(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_int(ctx, styles.yield());
				return 1;
			}
		);
		/* WR int StylesEx */
		duk_property(ctx, "StylesEx", 
			[](duk_context *ctx) -> duk_ret_t {
				auto styles = duk_to_int(ctx, 0);
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->StylesEx(reuse_as<WStyleEx>(styles)); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
 			[](duk_context *ctx) -> duk_ret_t {
				WStyleEx styles = WStyleEx::No;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { styles = obj->StylesEx(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_int(ctx, styles.yield());
				return 1;
			}
		);
		/* WR String Text */
		duk_property(ctx, "Text",
			[](duk_context *ctx) -> duk_ret_t {
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Text(duk_to_string(ctx, 0)); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				StringA res = O;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { res = obj->TextA(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_string(ctx, res);
				return 1;
			}
		);
		/* WR Window Parent */
		duk_property(ctx, "Parent", 
			[](duk_context *ctx) -> duk_ret_t {
				HANDLE hParent = O; 
				if (duk_class_handle(ctx, "Window", hParent))
					return DUK_RET_TYPE_ERROR;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Parent((HWND)hParent); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				HWND hParent = O;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { hParent = obj->Parent(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_new_handle(ctx, "Window", hParent);
				return 1;
			}
		);
		/* WR Menu Menu */
		duk_property(ctx, "Menu", 
			[](duk_context *ctx) -> duk_ret_t {
				HANDLE hMenu = O;
				if (duk_class_handle(ctx, "Menu", hMenu))
					return DUK_RET_TYPE_ERROR;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->Menu((HMENU)hMenu); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				HMENU hMenu = O;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { hMenu = obj->Menu(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_new_handle(ctx, "Menu", hMenu);
				return 1;
			}
		);
		/* WR Icon IconBig */
		duk_property(ctx, "IconBig",
			[](duk_context *ctx) -> duk_ret_t {
				HANDLE hIcon = O;
				if (duk_class_handle(ctx, "Icon", hIcon))
					return DUK_RET_TYPE_ERROR;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->IconBig((HICON)hIcon); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				HICON hIcon = O;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { hIcon = obj->IconBig(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_new_handle(ctx, "Icon", hIcon);
				return 1;
			}
		);
		/* WR Icon IconSmall */
		duk_property(ctx, "IconSmall",
			[](duk_context *ctx) -> duk_ret_t {
				HANDLE hIcon = O;
				if (duk_class_handle(ctx, "Icon", hIcon))
					return DUK_RET_TYPE_ERROR;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { obj->IconSmall((HICON)hIcon); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				HICON hIcon = O;
				if (_try_method(ctx, [&](duk_context *ctx, CWindow &obj) { hIcon = obj->IconSmall(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_new_handle(ctx, "Icon", hIcon);
				return 1;
			}
		);
#pragma endregion

		return 0;
	});
	duk_function_global(ctx, "Window", [](duk_context *ctx) -> duk_ret_t {
		if (!duk_is_constructor_call(ctx))
			return 0;
		switch (duk_get_top(ctx)) {
			case 0:
			case 1:
				if (duk_is_pointer(ctx, 0)) {
					duk_member_handle(ctx, duk_get_pointer(ctx, 0));
					return 1;
				}
				break;
			default:
				return 0;
		}
		return 1;
	});
	duk_extends(ctx, "Window", "WObj");
	duk_method(ctx, "Find", 1, [](duk_context *ctx) -> duk_ret_t {
		auto lpstr = duk_to_string(ctx, 0);
		auto hwnd = FindWindowA(O, lpstr);
		duk_new_handle(ctx, "Window", hwnd);
		return 1;
	});
#pragma endregion

}
