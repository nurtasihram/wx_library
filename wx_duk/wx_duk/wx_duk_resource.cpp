#include "wx_resource.h"

#include "wx_duk.h"

static void load_duk_module(duk_context *ctx) {
	duk_class(ctx, "Module", O,
		[](duk_context *ctx) -> duk_ret_t {
			return 0;
		},
		[](duk_context *ctx) -> duk_ret_t {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					break;
				}
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_member_handle(ctx, duk_get_pointer(ctx, 0));
					} else {
						duk_errout(ctx, "Module constructor: first argument must be a pointer to Module");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Module constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 1;
		}
	);
}

static void load_duk_bitmap(duk_context *ctx) {
	duk_class(ctx, "Bitmap", O,
		[](duk_context *ctx) -> duk_ret_t {
			return 0;
		},
		[](duk_context *ctx) -> duk_ret_t {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					break;
				}
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_member_handle(ctx, duk_get_pointer(ctx, 0));
					} else {
						duk_errout(ctx, "Bitmap constructor: first argument must be a pointer to Bitmap");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Bitmap constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 1;
		}
	);
}

static void load_duk_pen(duk_context *ctx) {
	duk_class(ctx, "Pen", O,
		[](duk_context *ctx) -> duk_ret_t {
			return 0;
		},
		[](duk_context *ctx) -> duk_ret_t {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					break;
				}
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_member_handle(ctx, duk_get_pointer(ctx, 0));
					} else {
						duk_errout(ctx, "Pen constructor: first argument must be a pointer to Pen");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Pen constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 1;
		}
	);
	duk_method(ctx, "Solid", 2, [](duk_context *ctx) -> duk_ret_t {
		auto color = duk_to_int(ctx, 0);
		auto width = duk_to_int(ctx, 1);
		return 1;
	});
}

static void load_duk_brush(duk_context *ctx) {
	duk_class(ctx, "Brush", O,
		[](duk_context *ctx) -> duk_ret_t {
			return 0;
		},
		[](duk_context *ctx) -> duk_ret_t {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					break;
				}
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_member_handle(ctx, duk_get_pointer(ctx, 0));
					} else {
						duk_errout(ctx, "Brush constructor: first argument must be a pointer to Brush");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Brush constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 1;
		}
	);
}

static void load_duk_font(duk_context *ctx) {
}

static void load_duk_icon(duk_context *ctx) {
	duk_class(ctx, "Brush", O,
		[](duk_context *ctx) -> duk_ret_t {
			return 0;
		},
		[](duk_context *ctx) -> duk_ret_t {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					break;
				}
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_member_handle(ctx, duk_get_pointer(ctx, 0));
					} else {
						duk_errout(ctx, "Icon constructor: first argument must be a pointer to Icon");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Icon constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 1;
		}
	);
}

static void load_duk_cursor(duk_context *ctx) {
	duk_class(ctx, "Cursor", O,
		[](duk_context *ctx) -> duk_ret_t {
			return 0;
		},
		[](duk_context *ctx) -> duk_ret_t {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					break;
				}
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_member_handle(ctx, duk_get_pointer(ctx, 0));
					} else {
						duk_errout(ctx, "Cursor constructor: first argument must be a pointer to HCURSOR");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Cursor constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 1;
		}
	);
}

static void load_duk_palette(duk_context *ctx) {
}

static void load_duk_region(duk_context *ctx) {
}

static void load_duk_menu(duk_context *ctx) {
	/*
	* <Menu> [ ... MenuItem ] </Menu>
	* <Menu-Popup> [ 'popup' ... MenuItem ] </Menu>
	* <MenuItem-Separator> { 'type' : 'sep' } </MenuItem-Separator>
	* <MenuItem-Popup>     { 'type' : 'popup', 'text' : 'any texts', 'items' : [ ... MenuItem ], 'disbled' : false } </MenuItem-Popup>
	* <MenuItem-Text>      { 'type' : 'text',  'text' : 'any texts', 'id' : 123, 'disbled' : false } </MenuItem-Text>
	* <MenuItem-Check>     { 'type' : 'check', 'text' : 'any texts', 'id' : 123, 'disbled' : false, 'unchecked' : false } </MenuItem-Check>
	*/
	//duk_get_context
	duk_class(ctx, "Menu", O,
		[](duk_context *ctx) -> duk_ret_t {
			duk_method(ctx, "Destroy", 0, [](duk_context *ctx) -> duk_ret_t {
				if (auto obj = reuse_as<CMenu>(duk_member_handle(ctx)))
					if (wx_try(ctx, [&]() { obj->Destroy(); }))
						return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "Separator", 0, [](duk_context *ctx) -> duk_ret_t {
				if (auto obj = reuse_as<CMenu>(duk_member_handle(ctx)))
					if (wx_try(ctx, [&]() { obj->Separator(); }))
						return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "String", 3, [](duk_context *ctx) -> duk_ret_t {
				LPCSTR lpString = duk_to_string(ctx, 0);
				UINT_PTR uID = duk_is_undefined(ctx, 1) ? 0 : duk_to_int(ctx, 1);
				bool bEnable = duk_is_undefined(ctx, 2) ? true : duk_to_boolean(ctx, 2);
				if (auto obj = reuse_as<CMenu>(duk_member_handle(ctx)))
					if (wx_try(ctx, [&]() { obj->String(lpString, uID, bEnable); }))
						return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "Check", 4, [](duk_context *ctx) -> duk_ret_t {
				LPCSTR lpString = duk_to_string(ctx, 0);
				UINT_PTR uID = duk_is_undefined(ctx, 1) ? 0 : duk_to_int(ctx, 1);
				bool bChecked = duk_is_undefined(ctx, 2) ? 0 : duk_to_boolean(ctx, 2);
				bool bEnable = duk_is_undefined(ctx, 3) ? true : duk_to_boolean(ctx, 3);
				if (auto obj = reuse_as<CMenu>(duk_member_handle(ctx)))
					if (wx_try(ctx, [&]() { obj->Check(lpString, uID, bChecked, bEnable); }))
						return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "Popup", 3, [](duk_context *ctx) -> duk_ret_t {
				LPCSTR lpString = duk_to_string(ctx, 0);
				HMENU hPopup = nullptr;
				bool bEnable = duk_is_undefined(ctx, 2) ? true : duk_to_boolean(ctx, 2);
				if (auto obj = reuse_as<CMenu>(duk_member_handle(ctx))) {
					duk_get_global_string(ctx, "Menu");
					if (!duk_instanceof(ctx, 1, -1)) {
						duk_errout(ctx, "Menu.Popup: second argument must be a Menu object");
						return DUK_RET_TYPE_ERROR;
					}
					duk_get_prop_string(ctx, 1, "__p");
					if (duk_get_type(ctx, -1) != DUK_TYPE_POINTER) {
						duk_errout(ctx, "Menu.Popup: second argument must be a valid Menu object");
						return DUK_RET_SYNTAX_ERROR;
					}
					hPopup = (HMENU)duk_get_pointer(ctx, -1);
					if (wx_try(ctx, [&]() { obj->Popup(lpString, hPopup, bEnable); }))
						return DUK_RET_INTERNAL_ERROR;
				}
				duk_push_this(ctx);
				return 1;
			});
			return 0;
		},
		[](duk_context *ctx) -> duk_ret_t {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					CMenu menu = O;
					if (wx_try(ctx, [&]() { *menu = Menu(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_member_handle(ctx, menu);
					break;
				}
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_member_handle(ctx, duk_get_pointer(ctx, 0));
					}
					else {
						duk_errout(ctx, "Menu constructor: first argument must be a pointer to Menu");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					return DUK_ERR_SYNTAX_ERROR;
			}
			return 0;
		}
	);
	duk_push_c_function(ctx, [](duk_context *ctx) -> duk_ret_t {
		if (auto obj = reuse_as<CMenu>(duk_member_handle(ctx)))
			if (wx_try(ctx, [&]() { obj->Destroy(); }))
				return DUK_RET_INTERNAL_ERROR;
		return 0;
	}, 1);
	duk_set_finalizer(ctx, -2);
	duk_function_global(ctx, "MenuPopup", [](duk_context *ctx) -> duk_ret_t {
		if (duk_reflect_constructor(ctx))
			return 1;
		switch (duk_get_top(ctx)) {
			case 0: {
				CMenu menu = O;
				if (wx_try(ctx, [&]() { *menu = Menu::CreatePopup(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_member_handle(ctx, menu);
				break;
			}
			default:
				duk_errout(ctx, "MenuPopup constructor: invalid number of arguments");
				return DUK_RET_TYPE_ERROR;
		}
		return 0;
	});
	duk_extends(ctx, "MenuPopup", "MenuObj");
}

static void load_duk_accelerator(duk_context *ctx) {
}

static void load_duk_devcap(duk_context *ctx) {
	duk_class(ctx, "DevCap", O,
		[](duk_context *ctx) -> duk_ret_t {
			duk_property(ctx, "PenColor",
				[](duk_context *ctx) -> duk_ret_t {
					auto color = duk_to_int(ctx, 0);
					if (auto obj = reuse_as<CDevCap>(duk_member_handle(ctx)))
						if (wx_try(ctx, [&]() { obj->PenColor(color); }))
							return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				[](duk_context *ctx) -> duk_ret_t {
					COLORREF color = 0;
					if (auto obj = reuse_as<CDevCap>(duk_member_handle(ctx)))
						if (wx_try(ctx, [&]() { color = obj->PenColor(); }))
							return DUK_RET_INTERNAL_ERROR;
					duk_push_int(ctx, color);
					return 1;
				}
			);
			duk_property(ctx, "BkColor",
				[](duk_context *ctx) -> duk_ret_t {
					auto color = duk_to_int(ctx, 0);
					if (auto obj = reuse_as<CDevCap>(duk_member_handle(ctx)))
						if (wx_try(ctx, [&]() { obj->BkColor(color); }))
							return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				[](duk_context *ctx) -> duk_ret_t {
					COLORREF color = 0;
					if (auto obj = reuse_as<CDevCap>(duk_member_handle(ctx)))
						if (wx_try(ctx, [&]() { color = obj->BkColor(); }))
							return DUK_RET_INTERNAL_ERROR;
					duk_push_int(ctx, color);
					return 1;
				}
			);
			duk_property(ctx, "ViewOrg",
				[](duk_context *ctx) -> duk_ret_t {
					LPoint Pos;
					if (!duk_get_point(ctx, Pos)) {
						return DUK_RET_TYPE_ERROR;
					}
					if (auto obj = reuse_as<CDevCap>(duk_member_handle(ctx)))
						if (wx_try(ctx, [&]() { obj->ViewOrg(Pos); }))
							return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				[](duk_context *ctx) -> duk_ret_t {
					LPoint Pos;
					if (auto obj = reuse_as<CDevCap>(duk_member_handle(ctx)))
						if (wx_try(ctx, [&]() { obj->ViewOrg(Pos); }))
							return DUK_RET_INTERNAL_ERROR;
					duk_push_point(ctx, Pos);
					return 1;
				}
			);
			duk_property(ctx, "ViewExt",
				[](duk_context *ctx) -> duk_ret_t {
					LPoint Ext;
					if (!duk_get_point(ctx, Ext)) {
						return DUK_RET_TYPE_ERROR;
					}
					if (auto obj = reuse_as<CDevCap>(duk_member_handle(ctx)))
						if (wx_try(ctx, [&]() { obj->ViewExt(Ext); }))
							return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				[](duk_context *ctx) -> duk_ret_t {
					LPoint Ext;
					if (auto obj = reuse_as<CDevCap>(duk_member_handle(ctx)))
						if (wx_try(ctx, [&]() { obj->ViewExt(Ext); }))
							return DUK_RET_INTERNAL_ERROR;
					duk_push_point(ctx, Ext);
					return 1;
				}
			);
			duk_property(ctx, "WindowOrg", 
				[](duk_context *ctx) -> duk_ret_t {
					LPoint Pos;
					if (!duk_get_point(ctx, Pos)) {
						return DUK_RET_TYPE_ERROR;
					}
					if (auto obj = reuse_as<CDevCap>(duk_member_handle(ctx)))
						if (wx_try(ctx, [&]() { obj->WindowOrg(Pos); }))
							return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				[](duk_context *ctx) -> duk_ret_t {
					LPoint Pos;
					if (auto obj = reuse_as<CDevCap>(duk_member_handle(ctx)))
						if (wx_try(ctx, [&]() { obj->WindowOrg(Pos); }))
							return DUK_RET_INTERNAL_ERROR;
					duk_push_point(ctx, Pos);
					return 1;
				}
			);
			duk_property(ctx, "WindowExt", 
				[](duk_context *ctx) -> duk_ret_t {
					LPoint Ext;
					if (!duk_get_point(ctx, Ext)) {
						return DUK_RET_TYPE_ERROR;
					}
					if (auto obj = reuse_as<CDevCap>(duk_member_handle(ctx)))
						if (wx_try(ctx, [&]() { obj->WindowExt(Ext); }))
							return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				[](duk_context *ctx) -> duk_ret_t {
					LPoint Ext;
					if (auto obj = reuse_as<CDevCap>(duk_member_handle(ctx)))
						if (wx_try(ctx, [&]() { obj->WindowExt(Ext); }))
							return DUK_RET_INTERNAL_ERROR;
					duk_push_point(ctx, Ext);
					return 1;
				}
			);
			return 0;
		},
		[](duk_context *ctx) -> duk_ret_t {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					HDC dc = O;
					if (wx_try(ctx, [&]() { dc = DevCap::CreateCompatible(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_member_handle(ctx, dc);
					break;
				}
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_member_handle(ctx, duk_get_pointer(ctx, 0));
					}
					else {
						duk_errout(ctx, "DevCap constructor: first argument must be a pointer to DevCap");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					return DUK_ERR_SYNTAX_ERROR;
			}
			return 0;
		}
	);
}

void load_duk_resource(duk_context *ctx) {
	// Load GDI resources
	load_duk_module(ctx);
	load_duk_bitmap(ctx);
	load_duk_pen(ctx);
	load_duk_brush(ctx);
	load_duk_font(ctx);
	load_duk_icon(ctx);
	load_duk_cursor(ctx);
	load_duk_palette(ctx);
	load_duk_region(ctx);
	load_duk_menu(ctx);
	load_duk_accelerator(ctx);
	load_duk_devcap(ctx);
//	load_duk_string_table(ctx);
}
