#include "wx_window.h"

#include "wx_duk.h"

template<class AnyClosure>
static bool _try_method(duk_context *ctx, const AnyClosure &closure) {
	if (auto obj = reuse_as<CWindow>(duk_member_handle(ctx))) 
		return wx_try(ctx, [&]() { closure(obj); });
	duk_errout(ctx, "Window method called on non-window object");
	return false;
}

class BaseOf_Window(DukWindow) {
	SFINAE_Window(DukWindow);
protected:
	duk_context *ctx;
	void *heapptr = O;
public:
	DukWindow(duk_context * ctx, void *heapptr = O) :
		ctx(ctx), heapptr(heapptr) {}
	~DukWindow() { heapptr = O; }
public:
	inline void OnDestroy() {
	}
};

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
	duk_flags(ctx, "MB", O, _MB_constant);
	duk_function_global(ctx, "MsgBox", duk_fn() {
		auto nargs = duk_get_top(ctx);
		LPCSTR lpCaption = duk_is_undefined(ctx, 0) ? "" : duk_to_string(ctx, 0);
		LPCSTR lpText = duk_is_undefined(ctx, 1) ? "" : duk_to_string(ctx, 1);
		MB uType = nargs > 2 ? reuse_as<MB>(duk_to_int(ctx, 2)) : (MB)MB::Ok;
		auto res = MsgBox(lpCaption, lpText, uType);
		duk_push_int(ctx, res);
		return 1;
	}, 3);

	static const duk_constant_struct _ClassStyle_constant[]{
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
	duk_flags(ctx, "ClassStyle", O, _ClassStyle_constant);
	//duk_class(ctx, "Class", O,
	//	duk_fn() {
	//		// Constructor for Class
	//		if (duk_reflect_constructor(ctx))
	//			return DUK_RET_INTERNAL_ERROR;
	//		// Set default class style
	//		duk_push_int(ctx, CS_VREDRAW | CS_HREDRAW | CS_OWNDC);
	//		duk_put_prop_string(ctx, -2, "Style");
	//		return 1;
	//	},
	//	duk_fn() {
	//		// Class method to create a new window class
	//		if (_try_method(ctx, [&](CWindow &obj) { obj->CreateClass(); }))
	//			return DUK_RET_INTERNAL_ERROR;
	//		return 0;
	//	}
	//);

	duk_class(ctx, "CreateStruct", O, 
		duk_fn() {
			duk_property(ctx, "Module",
				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					HMODULE hModule = O;
					if (duk_class_handle(ctx, "Module", hModule))
						return DUK_RET_TYPE_ERROR;
					obj->Module(hModule);
					return 0;
				},
				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					duk_new_handle_proxy(ctx, "Module", obj->Module());
					return 1;
				}
			);
			duk_property(ctx, "Menu",
				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					HMENU hMenu = O;
					if (duk_class_handle(ctx, "Menu", hMenu))
						return DUK_RET_TYPE_ERROR;
					obj->Menu(hMenu);
					return 0;
				},
				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					duk_new_handle_proxy(ctx, "Menu", obj->Menu());
					return 1;
				}
			);
			duk_property(ctx, "Parent",
				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					HWND hWnd = O;
					if (duk_class_handle(ctx, "Window", hWnd))
						return DUK_RET_TYPE_ERROR;
					obj->Parent(hWnd);
					return 0;
				},
				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					duk_new_handle_proxy(ctx, "WIndow", obj->Parent());
					return 1;
				}
			);
			duk_property(ctx, "Styles",
				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					int styles = duk_to_int(ctx, 0);
					obj->Styles(reuse_as<WS>(styles));
					return 0;
				},
				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_new_int_obj(ctx, "WS", obj->Styles().yield());
					return 1;
				}
			);
			duk_property(ctx, "Caption", 
				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					obj->Caption(duk_to_string(ctx, 0));
					return 0;
				},
				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_string(ctx, obj->Caption());
					return 1;
				}
			);
			duk_property(ctx, "StylesEx",
				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					obj->StylesEx(reuse_as<WSEX>(duk_to_int(ctx, 0)));
					return 0;
				},
				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_new_int_obj(ctx, "WSEX", obj->StylesEx().yield());
					return 1;
				}
			);
			duk_property(ctx, "Size", 
				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					LPoint Size;
					if (!duk_get_point(ctx, Size, 0))
						return DUK_RET_TYPE_ERROR;
					obj->Size(Size);
					return 0;
				},
 				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_point(ctx, obj->Size());
					return 1;
				}
			);
			duk_property(ctx, "Position", 
				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					LPoint Pos;
					if (!duk_get_point(ctx, Pos, 0))
						return DUK_RET_TYPE_ERROR;
					obj->Position(Pos);
					return 0;
				},
 				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_point(ctx, obj->Position());
					return 1;
				}
			);
			duk_property(ctx, "Rect", 
				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					LRect rc;
					if (!duk_get_rect(ctx, rc, 0))
						return DUK_RET_TYPE_ERROR;
					obj->Rect(rc);
					return 0;
				},
 				duk_fn() {
					auto obj = duk_get_buffer<CreateStructA>(ctx);
					if (!obj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_rect(ctx, obj->Rect());
					return 1;
				}
			);
			duk_method(ctx, "ClientRect", 2, duk_fn() {
				auto obj = duk_get_buffer<CreateStructA>(ctx);
				if (!obj)
					return DUK_RET_INTERNAL_ERROR;
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0))
					return DUK_RET_TYPE_ERROR;
				if (duk_is_undefined(ctx, 1))
					obj->ClientRect(rc);
				else
					obj->ClientRect(rc, duk_to_uint(ctx, 1));
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "ClientSize", 2, duk_fn() {
				auto obj = duk_get_buffer<CreateStructA>(ctx);
				if (!obj)
					return DUK_RET_INTERNAL_ERROR;
				LPoint Size;
				if (!duk_get_point(ctx, Size, 0))
					return DUK_RET_TYPE_ERROR;
				if (duk_is_undefined(ctx, 1))
					obj->ClientSize(Size);
				else
					obj->ClientSize(Size, duk_to_uint(ctx, 1));
				duk_push_this(ctx);
				return 1;
			});
			return 0;
		},
		duk_fn() {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					duk_push_this(ctx);
					auto pobj = (CreateStruct *)duk_push_buffer(ctx, sizeof(CreateStruct), 0);
					new(pobj) CreateStruct();
					duk_put_prop_string(ctx, -2, "__p");
					break;
				}
				case 1: {
					duk_get_global_string(ctx, "CreateStruct");
					if (duk_is_object(ctx, 0)) {
						if (!duk_instanceof(ctx, -1, 0))
							return DUK_RET_TYPE_ERROR;
						duk_get_prop_string(ctx, 0, "__p");
						if (duk_is_buffer(ctx, -1))
							return DUK_RET_TYPE_ERROR;
						duk_size_t size = 0;
						auto obj = (CreateStruct *)duk_get_buffer(ctx, -1, &size);
						if (size != sizeof(CreateStruct))
							return DUK_RET_TYPE_ERROR;
						duk_push_this(ctx);
						auto pobj = (CreateStruct *)duk_push_buffer(ctx, sizeof(CreateStruct), 0);
						new(pobj) CreateStruct(*obj);
						duk_put_prop_string(ctx, -2, "__p");
					} else
						return DUK_RET_TYPE_ERROR;
					break;
				}
			}
			return 0;
		}
	);

#pragma region Window

#pragma region Constants
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
	duk_flags(ctx, "WS", O, _WS_constant);
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
	duk_flags(ctx, "WSEX", O, _WSEX_constant);
#pragma endregion

	duk_class(ctx, "Window", O,
		duk_fn() {

#pragma region Methods
			duk_method(ctx, "Destroy", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->Destroy(); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			});
			duk_method(ctx, "Close", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->Close(); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			});
			duk_method(ctx, "Delete", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->Delete(); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			});
#pragma region ShowWindow
			duk_method(ctx, "Hide", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->Hide(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "ShowNormal", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->ShowNormal(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "Normal", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->Normal(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "ShowMinimized", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->ShowMinimized(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "ShowMaximized", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->ShowMaximized(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "Maximize", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->Maximize(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "ShowNoActivate", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->ShowNoActivate(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "Show", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->Show(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "Minimize", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->Minimize(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "ShowMinNoActive", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->ShowMinNoActive(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "ShowNA", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->ShowNA(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "Restore", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->Restore(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "ShowDefault", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->ShowDefault(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "ForceMinimize", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->ForceMinimize(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "Max", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->Max(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
#pragma endregion
			duk_method(ctx, "BringToTop", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->BringToTop(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "MsgBox", 3, duk_fn() {
				auto nargs = duk_get_top(ctx);
				LPCSTR lpCaption = duk_to_string(ctx, 0);
				LPCSTR lpText = duk_to_string(ctx, 1);
				MB uType = nargs > 2 ? reuse_as<MB>(duk_to_int(ctx, 2)) : (MB)MB::Ok;
				int res = -1;
				if (_try_method(ctx, [&](CWindow &obj) { res = obj->MsgBox(lpCaption, lpText, uType); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_int(ctx, res);
				return 1;
			});
			duk_method(ctx, "Focus", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->Focus(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "IsFocus", 0, duk_fn() {
				bool res = false;
				if (_try_method(ctx, [&](CWindow &obj) { res = obj->IsFocus(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_boolean(ctx, res);
				return 1;
			});
			duk_method(ctx, "ScreenToClient", 1, duk_fn() {
				LPoint pt;
				if (!duk_get_point(ctx, pt, 0))
					return DUK_RET_TYPE_ERROR;
				if (_try_method(ctx, [&](CWindow &obj) { obj->ScreenToClient(pt); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_point(ctx, pt);
				return 1;
			});
			duk_method(ctx, "ClientToScreen", 1, duk_fn() {
				LPoint pt;
				if (!duk_get_point(ctx, pt, 0))
					return DUK_RET_TYPE_ERROR;
				if (_try_method(ctx, [&](CWindow &obj) { obj->ClientToScreen(pt); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_point(ctx, pt);
				return 1;
			});
			duk_method(ctx, "AdjustRect", 1, duk_fn() {
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0))
					return DUK_RET_TYPE_ERROR;
				if (_try_method(ctx, [&](CWindow &obj) { obj->AdjustRect(rc); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_rect(ctx, rc);
				return 1;
			});
			duk_method(ctx, "Move", 2, duk_fn() {
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0)) 
					return DUK_RET_TYPE_ERROR;
				bool bRedraw = duk_is_undefined(ctx, 1) ? true : duk_to_boolean(ctx, 1);
				if (_try_method(ctx, [&](CWindow &obj) { obj->Move(rc, bRedraw); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "Update", 0, duk_fn() {
				if (_try_method(ctx, [&](CWindow &obj) { obj->Update(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "RegisterTouch", 2, duk_fn() {
				bool bFine = duk_is_undefined(ctx, 0) ? true : duk_to_boolean(ctx, 1);
				bool bWantPalm = duk_is_undefined(ctx, 1) ? false : duk_to_boolean(ctx, 1);
				if (_try_method(ctx, [&](CWindow &obj) { obj->RegisterTouch(bFine, bWantPalm); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
#pragma endregion

#pragma region Properties
			/* RO bool Minimized */
			duk_property_r(ctx, "Minimized",
				duk_fn() {
					bool res = false;
					if (_try_method(ctx, [&](CWindow &obj) { res = obj->Iconic(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_boolean(ctx, res);
					return 1;
				}
			);
			/* WR bool Visible */
			duk_property(ctx, "Visible",
				duk_fn() {
					if (_try_method(ctx, [&](CWindow &obj) { obj->Visible(duk_to_boolean(ctx, 0)); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					bool res = false;
					if (_try_method(ctx, [&](CWindow &obj) { res = obj->Visible(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_boolean(ctx, res);
					return 1;
				}
			);
			/* WR bool Enabled */
			duk_property(ctx, "Enabled",
				duk_fn() {
					if (_try_method(ctx, [&](CWindow &obj) { obj->Enabled(duk_to_boolean(ctx, 0)); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					bool res = false;
					if (_try_method(ctx, [&](CWindow &obj) { res = obj->Enabled(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_boolean(ctx, res);
					return 1;
				}
			);
			/* RO Point ClientRect */
			duk_property_r(ctx, "ClientRect", duk_fn() {
				LRect rc;
				if (_try_method(ctx, [&](CWindow &obj) { rc = obj->ClientRect(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_rect(ctx, rc);
				return 1;
			});
			/* RO Point ClientSize */
			duk_property_r(ctx, "ClientSize", duk_fn() {
				LPoint Size;
				if (_try_method(ctx, [&](CWindow &obj) { Size = obj->ClientSize(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_point(ctx, Size);
				return 1;
			});
			/* WR Point Position */
			duk_property(ctx, "Position", 
				duk_fn() {
					LPoint Pos;
					if (!duk_get_point(ctx, Pos, 0))
						return DUK_RET_TYPE_ERROR;
					if (_try_method(ctx, [&](CWindow &obj) { obj->Position(Pos); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
 				duk_fn() {
					LPoint Pos;
					if (_try_method(ctx, [&](CWindow &obj) { Pos = obj->Position(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_point(ctx, Pos);
					return 1;
				}
			);
			/* WR Point Size */
			duk_property(ctx, "Size", 
				duk_fn() {
					LPoint Size;
					if (!duk_get_point(ctx, Size, 0))
						return DUK_RET_TYPE_ERROR;
					if (_try_method(ctx, [&](CWindow &obj) { obj->Size(Size); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
 				duk_fn() {
					LPoint Size;
					if (_try_method(ctx, [&](CWindow &obj) { Size = obj->Size(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_point(ctx, Size);
					return 1;
				}
			);
			/* WR Rect Rect */
			duk_property(ctx, "Rect", 
				duk_fn() {
					LRect rc;
					if (!duk_get_rect(ctx, rc, 0))
						return DUK_RET_TYPE_ERROR;
					if (_try_method(ctx, [&](CWindow &obj) { obj->Rect(rc); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
 				duk_fn() {
					LRect rc;
					if (_try_method(ctx, [&](CWindow &obj) { rc = obj->Rect(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_rect(ctx, rc);
					return 1;
				}
			);
			/* WR String Text */
			duk_property(ctx, "Text",
				duk_fn() {
					if (_try_method(ctx, [&](CWindow &obj) { obj->Text(duk_to_string(ctx, 0)); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					StringA res = O;
					if (_try_method(ctx, [&](CWindow &obj) { res = obj->TextA(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_string(ctx, res);
					return 1;
				}
			);
			/* WR Window Parent */
			duk_property(ctx, "Parent", 
				duk_fn() {
					HWND hParent = O; 
					if (duk_class_handle(ctx, "Window", hParent))
						return DUK_RET_TYPE_ERROR;
					if (_try_method(ctx, [&](CWindow &obj) { obj->Parent(hParent); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					HWND hParent = O;
					if (_try_method(ctx, [&](CWindow &obj) { hParent = obj->Parent(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_new_handle_proxy(ctx, "Window", hParent);
					return 1;
				}
			);
			/* WR Menu Menu */
			duk_property(ctx, "Menu", 
				duk_fn() {
					HMENU hMenu = O;
					if (duk_class_handle(ctx, "Menu", hMenu))
						return DUK_RET_TYPE_ERROR;
					if (_try_method(ctx, [&](CWindow &obj) { obj->Menu(hMenu); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					HMENU hMenu = O;
					if (_try_method(ctx, [&](CWindow &obj) { hMenu = obj->Menu(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_new_handle_proxy(ctx, "Menu", hMenu);
					return 1;
				}
			);
			/* WR Icon IconBig */
			duk_property(ctx, "IconBig",
				duk_fn() {
					HICON hIcon = O;
					if (duk_class_handle(ctx, "Icon", hIcon))
						return DUK_RET_TYPE_ERROR;
					if (_try_method(ctx, [&](CWindow &obj) { obj->IconBig(hIcon); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					HICON hIcon = O;
					if (_try_method(ctx, [&](CWindow &obj) { hIcon = obj->IconBig(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_new_handle_proxy(ctx, "Icon", hIcon);
					return 1;
				}
			);
			/* WR Icon IconSmall */
			duk_property(ctx, "IconSmall",
				duk_fn() {
					HICON hIcon = O;
					if (duk_class_handle(ctx, "Icon", hIcon))
						return DUK_RET_TYPE_ERROR;
					if (_try_method(ctx, [&](CWindow &obj) { obj->IconSmall(hIcon); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					HICON hIcon = O;
					if (_try_method(ctx, [&](CWindow &obj) { hIcon = obj->IconSmall(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_new_handle_proxy(ctx, "Icon", hIcon);
					return 1;
				}
			);

			/* WR Module Module */
			duk_property(ctx, "Module",
				duk_fn() {
					HMODULE hModule = O;
					if (duk_class_handle(ctx, "Module", hModule))
						return DUK_RET_TYPE_ERROR;
					if (_try_method(ctx, [&](CWindow &obj) { obj->Module(hModule); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					HMODULE hModule = O;
					if (_try_method(ctx, [&](CWindow &obj) { hModule = obj->Module(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_new_handle_proxy(ctx, "Module", hModule);
					return 1;
				}
			);
			/* WR Window HwndParent */
			duk_property(ctx, "HwndParent", 
				duk_fn() {
					HWND hParent = O; 
					if (duk_class_handle(ctx, "Window", hParent))
						return DUK_RET_TYPE_ERROR;
					if (_try_method(ctx, [&](CWindow &obj) { obj->HwndParent(hParent); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					HWND hParent = O;
					if (_try_method(ctx, [&](CWindow &obj) { hParent = obj->HwndParent(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_new_handle_proxy(ctx, "Window", hParent);
					return 1;
				}
			);
			/* WR int Styles */
			duk_property(ctx, "Styles", 
				duk_fn() {
					auto styles = duk_to_int(ctx, 0);
					if (_try_method(ctx, [&](CWindow &obj) { obj->Styles(reuse_as<WStyle>(styles)); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
 				duk_fn() {
					WStyle styles = WStyle::Overlapped;
					if (_try_method(ctx, [&](CWindow &obj) { styles = obj->Styles(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_new_int_obj(ctx, "WS", styles.yield());
					return 1;
				}
			);
			/* WR int StylesEx */
			duk_property(ctx, "StylesEx", 
				duk_fn() {
					auto styles = duk_to_int(ctx, 0);
					if (_try_method(ctx, [&](CWindow &obj) { obj->StylesEx(reuse_as<WStyleEx>(styles)); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
 				duk_fn() {
					WStyleEx styles = WStyleEx::No;
					if (_try_method(ctx, [&](CWindow &obj) { styles = obj->StylesEx(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_new_int_obj(ctx, "WSEX", styles.yield());
					return 1;
				}
			);
			/* WR int ID */
			duk_property(ctx, "ID",
				duk_fn() {
					if (_try_method(ctx, [&](CWindow &obj) { obj->ID(duk_to_int(ctx, 0)); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					LONG_PTR res = 0;
					if (_try_method(ctx, [&](CWindow &obj) { res = obj->ID(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_int(ctx, (duk_int_t)res);
					return 1;
				}
			);
			/* R String ClassName */
			duk_property_r(ctx, "ClassName", duk_fn() {
				StringA res = O;
				if (_try_method(ctx, [&](CWindow &obj) { res = obj->ClassNameA(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_string(ctx, res);
				return 1;
			});
			/* WR ClassMenuName */
			duk_property(ctx, "ClassMenuName", ///////////////
				duk_fn() {
					if (_try_method(ctx, [&](CWindow &obj) { obj->ClassMenuName(duk_to_string(ctx, 0)); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					LPCSTR res = O;
					if (_try_method(ctx, [&](CWindow &obj) { res = obj->ClassMenuNameA(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_string(ctx, res);
					return 1;
				}
			);
			/* WR ClassStyle ClassStyles */
			duk_property(ctx, "ClassStyles",
				duk_fn() {
					auto styles = duk_to_int(ctx, 0);
					if (_try_method(ctx, [&](CWindow &obj) { obj->ClassStyles(reuse_as<ClassStyle>(styles)); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					ClassStyle styles = ClassStyle::VRedraw;
					if (_try_method(ctx, [&](CWindow &obj) { styles = obj->ClassStyles(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_new_int_obj(ctx, "ClassStyle", styles.yield());
					return 1;
				}
			);
			/* WR Brush ClassBackground */
			duk_property(ctx, "ClassBackground",
				duk_fn() {
					HBRUSH hBrush = O;
					if (duk_class_handle(ctx, "Brush", hBrush))
						return DUK_RET_TYPE_ERROR;
					if (_try_method(ctx, [&](CWindow &obj) { obj->ClassBackground(hBrush); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					HBRUSH hBrush = O;
					if (_try_method(ctx, [&](CWindow &obj) { hBrush = obj->ClassBackground(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_new_handle_proxy(ctx, "Brush", hBrush);
					return 1;
				}
			);
			/* WR String ClassCursor */
			duk_property(ctx, "ClassCursor",
				duk_fn() {
					HCURSOR hCursor = O;
					if (duk_class_handle(ctx, "Cursor", hCursor))
						return DUK_RET_TYPE_ERROR;
					if (_try_method(ctx, [&](CWindow &obj) { obj->ClassCursor(hCursor); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					HCURSOR hCursor = O;
					if (_try_method(ctx, [&](CWindow &obj) { hCursor = obj->ClassCursor(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_new_handle_proxy(ctx, "Cursor", hCursor);
					return 1;
				}
			);
			/* WR String ClassIcon */
			duk_property(ctx, "ClassIcon",
				duk_fn() {
					HICON hIcon = O;
					if (duk_class_handle(ctx, "Icon", hIcon))
						return DUK_RET_TYPE_ERROR;
					if (_try_method(ctx, [&](CWindow &obj) { obj->ClassIcon(hIcon); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					HICON hIcon = O;
					if (_try_method(ctx, [&](CWindow &obj) { hIcon = obj->ClassIcon(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_new_handle_proxy(ctx, "Icon", hIcon);
					return 1;
				}
			);
			/* WR String ClassIconSm */
			duk_property(ctx, "ClassIconSm",
				duk_fn() {
					HICON hIcon = O;
					if (duk_class_handle(ctx, "Icon", hIcon))
						return DUK_RET_TYPE_ERROR;
					if (_try_method(ctx, [&](CWindow &obj) { obj->ClassIconSm(hIcon); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					HICON hIcon = O;
					if (_try_method(ctx, [&](CWindow &obj) { hIcon = obj->ClassIconSm(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_new_handle_proxy(ctx, "Icon", hIcon);
					return 1;
				}
			);
			/* WR Module ClassModule */
			duk_property(ctx, "ClassModule",
				duk_fn() {
					HMODULE hModule = O;
					if (duk_class_handle(ctx, "Module", hModule))
						return DUK_RET_TYPE_ERROR;
					if (_try_method(ctx, [&](CWindow &obj) { obj->ClassModule(hModule); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					HMODULE hModule = O;
					if (_try_method(ctx, [&](CWindow &obj) { hModule = obj->ClassModule(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_new_handle_proxy(ctx, "Module", hModule);
					return 1;
				}
			);
			/* WR uint_ptr ClassWndExtra */
			duk_property(ctx, "ClassWndExtra",
				duk_fn() {
					auto extra = duk_to_uint(ctx, 0);
					if (_try_method(ctx, [&](CWindow &obj) { obj->ClassWndExtra(extra); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					duk_uint_t extra = 0;
					if (_try_method(ctx, [&](CWindow &obj) { extra = (duk_uint_t)obj->ClassWndExtra(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_uint(ctx, extra);
					return 1;
				}
			);
			/* WR uint_ptr ClassClsExtra */
			duk_property(ctx, "ClassClsExtra",
				duk_fn() {
					auto extra = duk_to_uint(ctx, 0);
					if (_try_method(ctx, [&](CWindow &obj) { obj->ClassClsExtra(extra); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					duk_uint_t extra = 0;
					if (_try_method(ctx, [&](CWindow &obj) { extra = (duk_uint_t)obj->ClassClsExtra(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_uint(ctx, extra);
					return 1;
				}
			);
			/* WR uint16 ClassAtom */
			duk_property(ctx, "ClassAtom",
				duk_fn() {
					auto atom = duk_to_uint16(ctx, 0);
					if (_try_method(ctx, [&](CWindow &obj) { obj->ClassAtom(atom); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					duk_uint16_t atom = 0;
					if (_try_method(ctx, [&](CWindow &obj) { atom = obj->ClassAtom(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_uint(ctx, atom);
					return 1;
				}
			);
			/* RO DevCap DC */
			duk_property_r(ctx, "DC",
				duk_fn() {
					HDC hdc = O;
					if (_try_method(ctx, [&](CWindow &obj) { hdc = obj->DC(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_new_handle_proxy(ctx, "DevCap", hdc);
					return 1;
				}
			);
			/* RO uint ProcessId */
			duk_property_r(ctx, "ProcessId",
				duk_fn() {
					DWORD res = 0;
					if (_try_method(ctx, [&](CWindow &obj) { res = obj->ProcessId(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_uint(ctx, res);
					return 1;
				}
			);
			/* RO uint ThreadId */
			duk_property_r(ctx, "ThreadId",
				duk_fn() {
					DWORD res = 0;
					if (_try_method(ctx, [&](CWindow &obj) { res = obj->ThreadId(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_uint(ctx, res);
					return 1;
				}
			);
#pragma endregion

			return 0;
		},
		duk_fn() {
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
			duk_push_this(ctx);
			duk_finalizer(ctx, duk_fn() {
				if (auto obj = reuse_as<CWindow>(duk_member_handle(ctx)))
					if (wx_try(ctx, [&]() { obj->Destroy(); }))
						return DUK_RET_INTERNAL_ERROR;
				return 0;
			});
			return 1;
		}
	);
	duk_method(ctx, "Find", 1, duk_fn() {
		auto lpstr = duk_to_string(ctx, 0);
		auto hwnd = FindWindowA(O, lpstr);
		duk_new_handle_proxy(ctx, "Window", hwnd);
		return 1;
	});
#pragma endregion

}
