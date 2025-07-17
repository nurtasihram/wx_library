#include "wx_resource.h"

#include "wx_duk.h"

static void load_duk_module(duk_context *ctx) {
	duk_add_class(
		ctx, "Module", O,
		duk_structure {
			/* Menu */ duk_add_method(ctx, "Menu", 1, duk_fn {
				auto pobj = duk_get_this__p<CModule>(ctx);
				HMENU hmenu = O;
				if (duk_is_string(ctx, 0)) {
					auto lpszName = duk_to_string(ctx, 0);
					if (wx_try(ctx, [&] { hmenu = pobj->Menu(lpszName); }))
						return DUK_RET_REFERENCE_ERROR;
				} else {
					auto wID = duk_to_uint16(ctx, 0);
					if (wx_try(ctx, [&] { hmenu = pobj->Menu(wID); }))
						return DUK_RET_REFERENCE_ERROR;
				}
				duk_push_new_handle(ctx, "Menu", hmenu);
				return 1;
			});
			/* Bitmap */ duk_add_method(ctx, "Bitmap", 1, duk_fn {
				auto pobj = duk_get_this__p<CModule>(ctx);
				HBITMAP hbitmap = O;
				if (duk_is_string(ctx, 0)) {
					auto lpszName = duk_to_string(ctx, 0);
					if (wx_try(ctx, [&] { hbitmap = pobj->Bitmap(lpszName); }))
						return DUK_RET_REFERENCE_ERROR;
				} else {
					auto wID = duk_to_uint16(ctx, 0);
					if (wx_try(ctx, [&] { hbitmap = pobj->Bitmap(wID); }))
						return DUK_RET_REFERENCE_ERROR;
				}
				duk_push_new_handle(ctx, "Bitmap", hbitmap);
				return 1;
			});
			/* Icon */ duk_add_method(ctx, "Icon", 1, duk_fn {
				auto pobj = duk_get_this__p<CModule>(ctx);
				HICON hicon = O;
				if (duk_is_string(ctx, 0)) {
					auto lpszName = duk_to_string(ctx, 0);
					if (wx_try(ctx, [&] { hicon = pobj->Icon(lpszName); }))
						return DUK_RET_REFERENCE_ERROR;
				} else {
					auto wID = duk_to_uint16(ctx, 0);
					if (wx_try(ctx, [&] { hicon = pobj->Icon(wID); }))
						return DUK_RET_REFERENCE_ERROR;
				}
				duk_push_new_handle(ctx, "Icon", hicon);
				return 1;
			});
			/* Cursor */ duk_add_method(ctx, "Cursor", 1, duk_fn {
				auto pobj = duk_get_this__p<CModule>(ctx);
				HCURSOR hcursor = O;
				if (duk_is_string(ctx, 0)) {
					auto lpszName = duk_to_string(ctx, 0);
					if (wx_try(ctx, [&] { hcursor = pobj->Cursor(lpszName); }))
						return DUK_RET_REFERENCE_ERROR;
				} else {
					auto wID = duk_to_uint16(ctx, 0);
					if (wx_try(ctx, [&] { hcursor = pobj->Cursor(wID); }))
						return DUK_RET_REFERENCE_ERROR;
				}
				duk_push_new_handle(ctx, "Cursor", hcursor);
				return 1;
			});
			/* String */ duk_add_method(ctx, "String", 1, duk_fn {
				auto pobj = duk_get_this__p<CModule>(ctx);
				auto wID = duk_to_uint16(ctx, 0);
				if (wx_try(ctx, [&] { duk_push_string(ctx, pobj->StringA(wID)); }))
					return DUK_RET_REFERENCE_ERROR;
				return 1;
			});
			/* Menu */ duk_put_prop_r(ctx, "FileName", duk_fn {
				auto pobj = duk_get_this__p<CModule>(ctx);
				if (wx_try(ctx, [&] { duk_push_string(ctx, pobj->FileNameA()); }))
					return DUK_RET_REFERENCE_ERROR;
				return 1;
			});
			return 0;
		},
		duk_constructor {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					CModule mod = O;
					if (wx_try(ctx, [&] { *mod = Module(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_put_this__p(ctx, mod);
					break;
				}
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_put_this__p(ctx, duk_get_pointer(ctx, 0));
					} elif  (duk_is_null(ctx, 0)) {
						duk_put_this__p(ctx, O);
					} elif  (duk_is_string(ctx, 0)) {
						auto lpModuleName = duk_to_string(ctx, 0);
						CModule mod = O;
						if (wx_try(ctx, [&] { *mod = Module(lpModuleName); }))
							return DUK_RET_REFERENCE_ERROR;
						duk_put_this__p(ctx, mod);
					} else {
						duk_errout(ctx, "Module constructor: first argument must be a handler to HMODULE");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Module constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 0;
		},
		duk_static {
			/* Module */ duk_add_method(ctx, "Library", 1, duk_fn {
				auto lpModuleName = duk_to_string(ctx, 0);
				CModule mod = O;
				if (wx_try(ctx, [&] { *mod = Module(lpModuleName); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Module", mod);
				return 1;
			});
			return 0;
		}
	);
}

template<class AnyClass>
static void __CommRes(duk_context *ctx) {
	duk_add_method(ctx, "Destroy", 0, duk_fn {
		if (auto pobj = duk_get_this__p<AnyClass>(ctx))
			if (wx_try(ctx, [&] { pobj->Destroy(); }))
				return DUK_RET_REFERENCE_ERROR;
		return 0;
	});
}
static void load_duk_icon(duk_context *ctx) {
	duk_add_class(
		ctx, "Icon", O,
		duk_structure {
			__CommRes<CIcon>(ctx);
			return 0;
		},
		duk_constructor {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					break;
				}
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_put_this__p(ctx, duk_get_pointer(ctx, 0));
					} else {
						duk_errout(ctx, "Icon constructor: first argument must be a handler to HICON");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Icon constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			duk_put_destructor(ctx, duk_fn {
				duk_get_prop_string(ctx, 0, "__p");
				if (!duk_is_pointer(ctx, -1))
					return 0;
				if (auto dc = reuse_as<CIcon>(duk_get_pointer(ctx, -1)))
					dc->Destroy();
				duk_del_prop_string(ctx, 0, "__p");
				return 0;
			});
			return 0;
		}
	);
}
static void load_duk_cursor(duk_context *ctx) {
	duk_add_class(
		ctx, "Cursor", O,
		duk_structure {
			__CommRes<CCursor>(ctx);
			return 0;
		},
		duk_constructor {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					break;
				}
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_put_this__p(ctx, duk_get_pointer(ctx, 0));
					} else {
						duk_errout(ctx, "Cursor constructor: first argument must be a handler to HCURSOR");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Cursor constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 0;
		}
	);
}
static void load_duk_menu(duk_context *ctx) {
	duk_add_class(
		ctx, "Menu", O,
		duk_structure {
			__CommRes<CMenu>(ctx);
			/* <Self> */ duk_add_method(ctx, "Separator", 0, duk_fn {
				auto pobj = duk_get_this__p<CMenu>(ctx);
				if (!pobj)
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&] { pobj->Separator(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* <Self> */ duk_add_method(ctx, "String", 3, duk_fn {
				auto pobj = duk_get_this__p<CMenu>(ctx);
				if (!pobj)
					return DUK_RET_TYPE_ERROR;
				LPCSTR lpString = duk_to_string(ctx, 0);
				UINT_PTR uID = duk_is_undefined(ctx, 1) ? 0 : duk_to_int(ctx, 1);
				bool bEnable = duk_is_undefined(ctx, 2) ? true : duk_to_boolean(ctx, 2);
				if (wx_try(ctx, [&] { pobj->String(lpString, uID, bEnable); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* <Self> */ duk_add_method(ctx, "Check", 4, duk_fn {
				auto pobj = duk_get_this__p<CMenu>(ctx);
				if (!pobj)
					return DUK_RET_TYPE_ERROR;
				LPCSTR lpString = duk_to_string(ctx, 0);
				UINT_PTR uID = duk_is_undefined(ctx, 1) ? 0 : duk_to_int(ctx, 1);
				bool bChecked = duk_is_undefined(ctx, 2) ? 0 : duk_to_boolean(ctx, 2);
				bool bEnable = duk_is_undefined(ctx, 3) ? true : duk_to_boolean(ctx, 3);
				if (wx_try(ctx, [&] { pobj->Check(lpString, uID, bChecked, bEnable); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			/* <Self> */ duk_add_method(ctx, "Popup", 3, duk_fn {
				auto pobj = duk_get_this__p<CMenu>(ctx);
				if (!pobj)
					return DUK_RET_TYPE_ERROR;
				LPCSTR lpString = duk_to_string(ctx, 0);
				HMENU hPopup = nullptr;
				if (!duk_get_class__p(ctx, "Menu", hPopup, 1))
					return DUK_RET_TYPE_ERROR;
				bool bEnable = duk_is_undefined(ctx, 2) ? true : duk_to_boolean(ctx, 2);
				if (wx_try(ctx, [&] { pobj->Popup(lpString, hPopup, bEnable); }))
					return DUK_RET_REFERENCE_ERROR;
				if (hPopup) {
					duk_dup(ctx, 1);
					duk_put_destructor(ctx, O);
				}
				duk_push_this(ctx);
				return 1;
			});
			/* bool */ duk_add_method(ctx, "valueOf", 0, duk_fn {
				auto pobj = duk_get_this__p<CMenu>(ctx);
				if (!pobj)
					return DUK_RET_TYPE_ERROR;
				bool res = false;
				if (wx_try(ctx, [&] { res = *pobj; }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_boolean(ctx, res);
				return 1;
			});
			return 0;
		},
		duk_constructor {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					CMenu menu = O;
					if (wx_try(ctx, [&] { *menu = Menu(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_put_this__p(ctx, menu);
					break;
				}
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_put_this__p(ctx, duk_get_pointer(ctx, 0));
					} else {
						duk_errout(ctx, "Menu constructor: first argument must be a handler to HMENU");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					return DUK_ERR_SYNTAX_ERROR;
			}
			duk_push_this(ctx);
			duk_put_destructor(ctx, duk_fn {
				duk_get_prop_string(ctx, 0, "__p");
				if (!duk_is_pointer(ctx, -1))
					return 0;
				if (auto menu = reuse_as<CMenu>(duk_get_pointer(ctx, -1)))
					menu->Destroy();
				duk_del_prop_string(ctx, 0, "__p");
				return 0;
			});
			return 0;
		}
	);
	duk_add_method(
		/* Menu */ ctx, "MenuPopup", 0, duk_fn {
			CMenu menu = O;
			if (wx_try(ctx, [&] { *menu = Menu::CreatePopup(); }))
				return DUK_RET_REFERENCE_ERROR;
			duk_push_new_handle(ctx, "Menu", menu);
			return 1;
		}
	);
}

static void load_duk_accelerator(duk_context *ctx) {
}

void load_duk_resource(duk_context *ctx) {
	// Load GDI resources
	load_duk_module(ctx);
	load_duk_icon(ctx);
	load_duk_cursor(ctx);
	load_duk_menu(ctx);
	load_duk_accelerator(ctx);
//	load_duk_string_table(ctx);
}
