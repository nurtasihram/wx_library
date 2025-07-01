#include "wx_resource.h"

#include "wx_duk.h"

static void load_duk_module(duk_context *ctx) {
	duk_class(ctx, "Module", O,
		duk_fn() {
			duk_method(ctx, "Menu", 1, duk_fn() {
				auto obj = reuse_as<CModule>(duk_member_handle(ctx));
				HMENU hmenu = O;
				if (duk_is_string(ctx, 0)) {
					auto lpszName = duk_to_string(ctx, 0);
					if (wx_try(ctx, [&]() { hmenu = obj->Menu(lpszName); }))
						return DUK_RET_INTERNAL_ERROR;
				} else {
					auto wID = duk_to_uint16(ctx, 0);
					if (wx_try(ctx, [&]() { hmenu = obj->Menu(wID); }))
						return DUK_RET_INTERNAL_ERROR;
				}
				duk_new_handle(ctx, "Menu", hmenu);
				return 1;
			});
			duk_method(ctx, "Bitmap", 1, duk_fn() {
				auto obj = reuse_as<CModule>(duk_member_handle(ctx));
				HBITMAP hbitmap = O;
				if (duk_is_string(ctx, 0)) {
					auto lpszName = duk_to_string(ctx, 0);
					if (wx_try(ctx, [&]() { hbitmap = obj->Bitmap(lpszName); }))
						return DUK_RET_INTERNAL_ERROR;
				} else {
					auto wID = duk_to_uint16(ctx, 0);
					if (wx_try(ctx, [&]() { hbitmap = obj->Bitmap(wID); }))
						return DUK_RET_INTERNAL_ERROR;
				}
				duk_new_handle(ctx, "Bitmap", hbitmap);
				return 1;
			});
			duk_method(ctx, "Icon", 1, duk_fn() {
				auto obj = reuse_as<CModule>(duk_member_handle(ctx));
				HICON hicon = O;
				if (duk_is_string(ctx, 0)) {
					auto lpszName = duk_to_string(ctx, 0);
					if (wx_try(ctx, [&]() { hicon = obj->Icon(lpszName); }))
						return DUK_RET_INTERNAL_ERROR;
				} else {
					auto wID = duk_to_uint16(ctx, 0);
					if (wx_try(ctx, [&]() { hicon = obj->Icon(wID); }))
						return DUK_RET_INTERNAL_ERROR;
				}
				duk_new_handle(ctx, "Icon", hicon);
				return 1;
			});
			duk_method(ctx, "Cursor", 1, duk_fn() {
				auto obj = reuse_as<CModule>(duk_member_handle(ctx));
				HCURSOR hcursor = O;
				if (duk_is_string(ctx, 0)) {
					auto lpszName = duk_to_string(ctx, 0);
					if (wx_try(ctx, [&]() { hcursor = obj->Cursor(lpszName); }))
						return DUK_RET_INTERNAL_ERROR;
				} else {
					auto wID = duk_to_uint16(ctx, 0);
					if (wx_try(ctx, [&]() { hcursor = obj->Cursor(wID); }))
						return DUK_RET_INTERNAL_ERROR;
				}
				duk_new_handle(ctx, "Cursor", hcursor);
				return 1;
			});
			duk_method(ctx, "String", 1, duk_fn() {
				auto obj = reuse_as<CModule>(duk_member_handle(ctx));
				auto wID = duk_to_uint16(ctx, 0);
				if (wx_try(ctx, [&]() { duk_push_string(ctx, obj->StringA(wID)); }))
					return DUK_RET_INTERNAL_ERROR;
				return 1;
			});
			return 0;
		},
		duk_fn() {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					CModule mod = O;
					if (wx_try(ctx, [&]() { *mod = Module(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_member_handle(ctx, mod);
					break;
				}
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_member_handle(ctx, duk_get_pointer(ctx, 0));
					} else if (duk_is_null(ctx, 0)) {
						duk_member_handle(ctx, O);
					} else if (duk_is_string(ctx, 0)) {
						auto lpModuleName = duk_to_string(ctx, 0);
						CModule mod = O;
						if (wx_try(ctx, [&]() { *mod = Module(lpModuleName); }))
							return DUK_RET_INTERNAL_ERROR;
						duk_member_handle(ctx, mod);
					} else {
						duk_errout(ctx, "Module constructor: first argument must be a pointer to Module");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Module constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 0;
		}
	);
	duk_method(ctx, "Library", 1, duk_fn() {
		auto lpModuleName = duk_to_string(ctx, 0);
		CModule mod = O;
		if (wx_try(ctx, [&]() { *mod = Module(lpModuleName); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_new_handle(ctx, "Module", mod);
		return 1;
	});
}

static void load_duk_icon(duk_context *ctx) {
	duk_class(ctx, "Icon", O,
		duk_fn() {
			return 0;
		},
		duk_fn() {
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
		duk_fn() {
			return 0;
		},
		duk_fn() {
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

#pragma region GDI Object
static duk_ret_t GDI_destructor(duk_context *ctx) {
	duk_get_prop_string(ctx, 0, "__p");
	if (!duk_is_pointer(ctx, -1))
		return 0;
	//	Menu
	return 0;
}

static void load_duk_font(duk_context *ctx) {

#pragma region Constants
	//static const duk_constant_struct __FontType_constant[] {
	//	{ "Default", 0 },
	//	{ "Device", DEVICE_FONTTYPE },
	//	{ "Raster", RASTER_FONTTYPE },
	//	{ "TrueType", TRUETYPE_FONTTYPE }
	//};
	static const duk_constant_struct __FontType_constant[]{
		{ "Simulated", SIMULATED_FONTTYPE },
		{ "Printer", PRINTER_FONTTYPE },
		{ "Screen", SCREEN_FONTTYPE },
		{ "Bold", BOLD_FONTTYPE },
		{ "Italic", ITALIC_FONTTYPE },
		{ "Regular", REGULAR_FONTTYPE }
	};
	duk_flags(ctx, "FontType", O, __FontType_constant);
	static const duk_constant_struct __CharSets_constant[]{
		{ "ANSI", ANSI_CHARSET },
		{ "Default", DEFAULT_CHARSET },
		{ "Symbol", SYMBOL_CHARSET },
		{ "ShiftJIS", SHIFTJIS_CHARSET },
		{ "Hangeul", HANGEUL_CHARSET },
		{ "Hangul", HANGUL_CHARSET },
		{ "GB2312", GB2312_CHARSET },
		{ "ChineseBig5", CHINESEBIG5_CHARSET },
		{ "OEM", OEM_CHARSET },
		{ "Johab", JOHAB_CHARSET },
		{ "Hebrew", HEBREW_CHARSET },
		{ "Arabic", ARABIC_CHARSET },
		{ "Greek", GREEK_CHARSET },
		{ "Turkish", TURKISH_CHARSET },
		{ "Vietnamese", VIETNAMESE_CHARSET },
		{ "Thai", THAI_CHARSET },
		{ "EastEurope", EASTEUROPE_CHARSET },
		{ "Russian", RUSSIAN_CHARSET },
		{ "Mac", MAC_CHARSET },
		{ "Baltic", BALTIC_CHARSET }
	};
	duk_enums(ctx, "CharSets", O, __CharSets_constant);
	static const duk_constant_struct __OutPrecis_constant[]{
		{ "Default", OUT_DEFAULT_PRECIS },
		{ "String", OUT_STRING_PRECIS },
		{ "Character", OUT_CHARACTER_PRECIS },
		{ "Stroke", OUT_STROKE_PRECIS },
		{ "TrueType", OUT_TT_PRECIS },
		{ "Device", OUT_DEVICE_PRECIS },
		{ "Raster", OUT_RASTER_PRECIS },
		{ "TrueTypeOnly", OUT_TT_ONLY_PRECIS },
		{ "Outline", OUT_OUTLINE_PRECIS },
		{ "ScreenOutline", OUT_SCREEN_OUTLINE_PRECIS },
		{ "PostScriptOnly", OUT_PS_ONLY_PRECIS }
	};
	duk_enums(ctx, "OutPrecis", O, __OutPrecis_constant);
	static const duk_constant_struct __ClipPrecis_constant[]{
		{ "Default", CLIP_DEFAULT_PRECIS },
		{ "Character", CLIP_CHARACTER_PRECIS },
		{ "Stroke", CLIP_STROKE_PRECIS },
		{ "Mask", CLIP_MASK },
		{ "LH_Angles", CLIP_LH_ANGLES },
		{ "TT_Always", CLIP_TT_ALWAYS },
		{ "DFA_Disable", CLIP_DFA_DISABLE },
		{ "Embedded", CLIP_EMBEDDED }
	};
	duk_flags(ctx, "ClipPrecis", O, __ClipPrecis_constant);
	static const duk_constant_struct __Qualities_constant[]{
		{ "Default", DEFAULT_QUALITY },
		{ "Draf", DRAFT_QUALITY },
		{ "Proof", PROOF_QUALITY },
		{ "NonAntiAliased", NONANTIALIASED_QUALITY },
		{ "AntiAliased", ANTIALIASED_QUALITY },
		{ "ClearType", CLEARTYPE_QUALITY },
		{ "ClearTypeNatural", CLEARTYPE_NATURAL_QUALITY }
	};
	duk_enums(ctx, "Qualities", O, __Qualities_constant);
	static const duk_constant_struct __FontPitches_constant[]{
		{ "Default", DEFAULT_PITCH },
		{ "Fixed", FIXED_PITCH },
		{ "Variable", VARIABLE_PITCH },
		{ "Mono", MONO_FONT }
	};
	duk_enums(ctx, "FontPitches", O, __FontPitches_constant);
	static const duk_constant_struct __FontFamilies_constant[]{
		{ "DontCare", FF_DONTCARE },
		{ "Roman", FF_ROMAN },
		{ "Swiss", FF_SWISS },
		{ "Modern", FF_MODERN },
		{ "Script", FF_SCRIPT },
		{ "Decorative", FF_DECORATIVE }
	};
	duk_enums(ctx, "FontFamilies", O, __FontFamilies_constant);
#pragma endregion

	duk_class(ctx, "FontLogic", O,
		duk_fn() {
			duk_property(ctx, "Height",
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_int(ctx, pobj->Height());
					return 1;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					pobj->Height(duk_to_int(ctx, 0));
					return 0;
				}
			);
			duk_property(ctx, "Width",
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_int(ctx, pobj->Width());
					return 1;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					pobj->Width(duk_to_int(ctx, 0));
					return 0;
				}
			);
			duk_property(ctx, "Escapement",
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_int(ctx, pobj->Escapement());
					return 1;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					pobj->Escapement(duk_to_int(ctx, 0));
					return 0;
				}
			);
			duk_property(ctx, "Orientation",
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_int(ctx, pobj->Orientation());
					return 1;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					pobj->Orientation(duk_to_int(ctx, 0));
					return 0;
				}
			);
			duk_property(ctx, "Weight",
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_int(ctx, pobj->Weight());
					return 1;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					pobj->Weight(duk_to_int(ctx, 0));
					return 0;
				}
			);
			duk_property(ctx, "Italic",
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_boolean(ctx, pobj->Italic());
					return 1;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					pobj->Italic(duk_to_boolean(ctx, 0));
					return 0;
				}
			);
			duk_property(ctx, "Underline",
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_boolean(ctx, pobj->Underline());
					return 1;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					pobj->Underline(duk_to_boolean(ctx, 0));
					return 0;
				}
			);
			duk_property(ctx, "StrikeOut",
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_boolean(ctx, pobj->StrikeOut());
					return 1;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					pobj->StrikeOut(duk_to_boolean(ctx, 0));
					return 0;
				}
			);
			duk_property(ctx, "CharSet",
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_new_int_obj(ctx, "CharSets", (int)pobj->CharSet().yield());
					return 1;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					pobj->CharSet(reuse_as<CharSets>((BYTE)duk_to_uint16(ctx, 0)));
					return 0;
				}
			);
			duk_property(ctx, "OutPrecision",
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_new_int_obj(ctx, "OutPrecis", (int)pobj->OutPrecision().yield());
					return 1;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					pobj->OutPrecision(reuse_as<OutPrecis>((BYTE)duk_to_int(ctx, 0)));
					return 0;
				}
			);
			duk_property(ctx, "ClipPrecision",
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_new_int_obj(ctx, "ClipPrecis", (int)pobj->ClipPrecision().yield());
					return 1;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					pobj->ClipPrecision(reuse_as<ClipPrecis>((BYTE)duk_to_int(ctx, 0)));
					return 0;
				}
			);
			duk_property(ctx, "Quality",
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_new_int_obj(ctx, "Qualities", (int)pobj->Quality().yield());
					return 1;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					pobj->Quality(reuse_as<Qualities>((BYTE)duk_to_int(ctx, 0)));
					return 0;
				}
			);
			duk_property(ctx, "Pitch",
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_new_int_obj(ctx, "FontPitches", (int)pobj->Pitch().yield());
					return 1;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					pobj->Pitch(reuse_as<FontPitches>((BYTE)duk_to_int(ctx, 0)));
					return 0;
				}
			);
			duk_property(ctx, "Family",
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_new_int_obj(ctx, "FontFamilies", (int)pobj->Family().yield());
					return 1;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					pobj->Family(reuse_as<FontFamilies>((BYTE)duk_to_int(ctx, 0)));
					return 0;
				}
			);
			duk_property(ctx, "FaceName",
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_string(ctx, pobj->FaceName());
					return 1;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					pobj->FaceName(CString(duk_to_string(ctx, 0), LF_FACESIZE));
					return 0;
				}
			);
			duk_method(ctx, "toString", 0, duk_fn() {
				auto pobj = duk_get_buffer<FontLogicA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				duk_push_sprintf(
					ctx,
					"{\n"
					"  Height: %d,\n"
					"  Width: %d,\n"
					"  Escapement: %d,\n"
					"  Orientation: %d,\n"
					"  Weight: %d,\n"
					"  Italic: %s,\n"
					"  Underline: %s,\n"
					"  StrikeOut: %s,\n"
					"  CharSet: %s,\n"
					"  OutPrecision: %s,\n"
					"  ClipPrecision: %s,\n"
					"  Quality: %s,\n"
					"  Pitch: %s,\n"
					"  Family: %s,\n"
					"  FaceName: '%s'\n"
					"}",
					pobj->Height(), pobj->Width(), pobj->Escapement(), pobj->Orientation(), pobj->Weight(),
					smpl_to_string(pobj->Italic()), smpl_to_string(pobj->Underline()), smpl_to_string(pobj->StrikeOut()),
					duk_this_prop_to_string(ctx, "CharSet"), duk_this_prop_to_string(ctx, "OutPrecision"), duk_this_prop_to_string(ctx, "ClipPrecision"),
					duk_this_prop_to_string(ctx, "Quality"), duk_this_prop_to_string(ctx, "Pitch"), duk_this_prop_to_string(ctx, "Family"),
					(LPCSTR)pobj->FaceName());
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
					auto pobj = (FontLogicA *)duk_push_buffer(ctx, sizeof(FontLogicA), 0);
					new(pobj) FontLogicA();
					duk_put_prop_string(ctx, -2, "__p");
					return 0;
				}
			}
			return 0;
		}
	);
	duk_class(ctx, "Font", O,
		duk_fn() {
			return 0;
		},
		duk_fn() {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_member_handle(ctx, duk_get_pointer(ctx, 0));
					} else if (duk_is_null(ctx, 0)) {
						duk_member_handle(ctx, O);
					} else if (duk_is_object(ctx, 0)) {
						//auto pobj = duk_get_buffer<FontLogicA>(ctx, 0);
						//if (!pobj)
						//	return DUK_RET_INTERNAL_ERROR;
						//CFont font = O;
						//if (wx_try(ctx, [&]() { *font = Font(*pobj); }))
						//	return DUK_RET_INTERNAL_ERROR;
						//duk_member_handle(ctx, font);
					} else {
						duk_errout(ctx, "Font constructor: first argument must be a pointer to Font or FontLogic");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Font constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 1;
		}
	);
}

static void load_duk_bitmap(duk_context *ctx) {
	duk_class(ctx, "Bitmap", O,
		duk_fn() {
			return 0;
		},
		duk_fn() {
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
		duk_fn() {
			return 0;
		},
		duk_fn() {
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
				case 2: {
					auto color = duk_to_int(ctx, 0);
					auto width = duk_to_int(ctx, 1);
					CPen pen = O;
					if (wx_try(ctx, [&]() { *pen = Pen::Create(color, width); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_member_handle(ctx, pen);
					return 1;
				}
				default:
					duk_errout(ctx, "Pen constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 1;
		}
	);
	duk_method(ctx, "CreateSolid", 2, duk_fn() {
		auto color = duk_to_int(ctx, 0);
		auto width = duk_to_int(ctx, 1);
		CPen pen = O;
		if (wx_try(ctx, [&]() { *pen = Pen::CreateSolid(color, width); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Pen");
		duk_push_pointer(ctx, pen);
		duk_new(ctx, 1);
		return 1;
	});
	duk_method(ctx, "CreateDash", 2, duk_fn() {
		auto color = duk_to_int(ctx, 0);
		auto width = duk_to_int(ctx, 1);
		CPen pen = O;
		if (wx_try(ctx, [&]() { *pen = Pen::CreateDash(color, width); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Pen");
		duk_push_pointer(ctx, pen);
		duk_new(ctx, 1);
		return 1;
	});
	duk_method(ctx, "CreateDot", 2, duk_fn() {
		auto color = duk_to_int(ctx, 0);
		auto width = duk_to_int(ctx, 1);
		CPen pen = O;
		if (wx_try(ctx, [&]() { *pen = Pen::CreateDot(color, width); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Pen");
		duk_push_pointer(ctx, pen);
		duk_new(ctx, 1);
		return 1;
	});
	duk_method(ctx, "CreateDashDot", 2, duk_fn() {
		auto color = duk_to_int(ctx, 0);
		auto width = duk_to_int(ctx, 1);
		CPen pen = O;
		if (wx_try(ctx, [&]() { *pen = Pen::CreateDashDot(color, width); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Pen");
		duk_push_pointer(ctx, pen);
		duk_new(ctx, 1);
		return 1;
	});
	duk_method(ctx, "CreateDashDotDot", 2, duk_fn() {
		auto color = duk_to_int(ctx, 0);
		auto width = duk_to_int(ctx, 1);
		CPen pen = O;
		if (wx_try(ctx, [&]() { *pen = Pen::CreateDashDotDot(color, width); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Pen");
		duk_push_pointer(ctx, pen);
		duk_new(ctx, 1);
		return 1;
	});
	duk_method(ctx, "CreateInsideFrame", 2, duk_fn() {
		auto color = duk_to_int(ctx, 0);
		auto width = duk_to_int(ctx, 1);
		CPen pen = O;
		if (wx_try(ctx, [&]() { *pen = Pen::CreateInsideFrame(color, width); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Pen");
		duk_push_pointer(ctx, pen);
		duk_new(ctx, 1);
		return 1;
	});
	duk_method(ctx, "CreateUserStyle", 2, duk_fn() {
		auto color = duk_to_int(ctx, 0);
		auto width = duk_to_int(ctx, 1);
		CPen pen = O;
		if (wx_try(ctx, [&]() { *pen = Pen::CreateUserStyle(color, width); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Pen");
		duk_push_pointer(ctx, pen);
		duk_new(ctx, 1);
		return 1;
	});
	duk_method(ctx, "CreateAlternate", 2, duk_fn() {
		auto color = duk_to_int(ctx, 0);
		auto width = duk_to_int(ctx, 1);
		CPen pen = O;
		if (wx_try(ctx, [&]() { *pen = Pen::CreateAlternate(color, width); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Pen");
		duk_push_pointer(ctx, pen);
		duk_new(ctx, 1);
		return 1;
	});
	duk_property_r(ctx, "White", duk_fn() {
		CPen pen = O;
		if (wx_try(ctx, [&]() { *pen = Pen::White(); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Pen");
		duk_push_pointer(ctx, pen);
		duk_new(ctx, 1);
		return 1;
	});
	duk_property_r(ctx, "Black", duk_fn() {
		CPen pen = O;
		if (wx_try(ctx, [&]() { *pen = Pen::Black(); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Pen");
		duk_push_pointer(ctx, pen);
		duk_new(ctx, 1);
		return 1;
	});
	duk_property_r(ctx, "Null", duk_fn() {
		CPen pen = O;
		if (wx_try(ctx, [&]() { *pen = Pen::Null(); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Pen");
		duk_push_pointer(ctx, pen);
		duk_new(ctx, 1);
		return 1;
	});
	duk_property_r(ctx, "DC", duk_fn() {
		CPen pen = O;
		if (wx_try(ctx, [&]() { *pen = Pen::DC(); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "DevCap");
		duk_push_pointer(ctx, pen);
		duk_new(ctx, 1);
		return 1;
	});
}

static void load_duk_brush(duk_context *ctx) {
	static const duk_constant_struct _HatchStyle_constant[]{
		{ "Horizontal", HS_HORIZONTAL },
		{ "Vertical", HS_VERTICAL },
		{ "FDiagonal", HS_FDIAGONAL },
		{ "BDiagonal", HS_BDIAGONAL },
		{ "Cross", HS_CROSS },
		{ "DiagCross", HS_DIAGCROSS }
	};
	duk_enums(ctx, "HatchStyle", O, _HatchStyle_constant);

	duk_class(ctx, "Brush", O,
		duk_fn() {
			return 0;
		},
		duk_fn() {
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
	duk_method(ctx, "CreateSolid", 1, duk_fn() {
		auto color = duk_to_int(ctx, 0);
		CBrush brush = O;
		if (wx_try(ctx, [&]() { *brush = Brush::CreateSolid(color); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Brush");
		duk_push_pointer(ctx, brush);
		duk_new(ctx, 1);
		return 1;
	});
	duk_method(ctx, "CreatePattern", 1, duk_fn() {
		HBITMAP hBitmap = O;
		if (duk_class_handle(ctx, "Bitmap", hBitmap))
			return DUK_RET_TYPE_ERROR;
		CBrush brush = O;
		if (wx_try(ctx, [&]()
				   { *brush = Brush::CreatePattern(hBitmap); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Brush");
		duk_push_pointer(ctx, brush);
		duk_new(ctx, 1);
		return 1;
	});
	duk_method(ctx, "CreateHatch", 2, duk_fn() {
		auto color = duk_to_int(ctx, 0);
		auto style = reuse_as<HatchStyle>(duk_to_int(ctx, 1));
		CBrush brush = O;
		if (wx_try(ctx, [&]() { *brush = Brush::CreateHatch(color, style); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Brush");
		duk_push_pointer(ctx, brush);
		duk_new(ctx, 1);
		return 1;
	});
	duk_property_r(ctx, "White", duk_fn() {
		CBrush brush = O;
		if (wx_try(ctx, [&]() { *brush = Brush::White(); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Brush");
		duk_push_pointer(ctx, brush);
		duk_new(ctx, 1);
		return 1;
	});
	duk_property_r(ctx, "LitGray", duk_fn() {
		CBrush brush = O;
		if (wx_try(ctx, [&]() { *brush = Brush::LitGray(); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Brush");
		duk_push_pointer(ctx, brush);
		duk_new(ctx, 1);
		return 1;
	});
	duk_property_r(ctx, "Gray", duk_fn() {
		CBrush brush = O;
		if (wx_try(ctx, [&]() { *brush = Brush::Gray(); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Brush");
		duk_push_pointer(ctx, brush);
		duk_new(ctx, 1);
		return 1;
	});
	duk_property_r(ctx, "DkGray", duk_fn() {
		CBrush brush = O;
		if (wx_try(ctx, [&]() { *brush = Brush::DkGray(); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Brush");
		duk_push_pointer(ctx, brush);
		duk_new(ctx, 1);
		return 1;
	});
	duk_property_r(ctx, "Black", duk_fn() {
		CBrush brush = O;
		if (wx_try(ctx, [&]() { *brush = Brush::Black(); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Brush");
		duk_push_pointer(ctx, brush);
		duk_new(ctx, 1);
		return 1;
	});
	duk_property_r(ctx, "Null", duk_fn() {
		CBrush brush = O;
		if (wx_try(ctx, [&]() { *brush = Brush::Null(); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "Brush");
		duk_push_pointer(ctx, brush);
		duk_new(ctx, 1);
		return 1;
	});
	duk_property_r(ctx, "DC", duk_fn() {
		CBrush brush = O;
		if (wx_try(ctx, [&]() { *brush = Brush::DC(); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_get_global_string(ctx, "DevCap");
		duk_push_pointer(ctx, brush);
		duk_new(ctx, 1);
		return 1;
	});
}

static void load_duk_palette(duk_context *ctx) {}

static void load_duk_region(duk_context *ctx) {
}

static void load_duk_menu(duk_context *ctx) {
	duk_class(ctx, "Menu", O,
		duk_fn() {
			duk_method(ctx, "Destroy", 0, duk_fn() {
				if (auto obj = reuse_as<CMenu>(duk_member_handle(ctx)))
					if (wx_try(ctx, [&]() { obj->Destroy(); }))
						return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				duk_del_prop_string(ctx, -1, "__p");
				return 0;
			});
			duk_method(ctx, "Separator", 0, duk_fn() {
				auto obj = reuse_as<CMenu>(duk_member_handle(ctx));
				if (!obj)
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&]() { obj->Separator(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "String", 3, duk_fn() {
				auto obj = reuse_as<CMenu>(duk_member_handle(ctx));
				if (!obj)
					return DUK_RET_TYPE_ERROR;
				LPCSTR lpString = duk_to_string(ctx, 0);
				UINT_PTR uID = duk_is_undefined(ctx, 1) ? 0 : duk_to_int(ctx, 1);
				bool bEnable = duk_is_undefined(ctx, 2) ? true : duk_to_boolean(ctx, 2);
				if (wx_try(ctx, [&]() { obj->String(lpString, uID, bEnable); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "Check", 4, duk_fn() {
				auto obj = reuse_as<CMenu>(duk_member_handle(ctx));
				if (!obj)
					return DUK_RET_TYPE_ERROR;
				LPCSTR lpString = duk_to_string(ctx, 0);
				UINT_PTR uID = duk_is_undefined(ctx, 1) ? 0 : duk_to_int(ctx, 1);
				bool bChecked = duk_is_undefined(ctx, 2) ? 0 : duk_to_boolean(ctx, 2);
				bool bEnable = duk_is_undefined(ctx, 3) ? true : duk_to_boolean(ctx, 3);
				if (wx_try(ctx, [&]() { obj->Check(lpString, uID, bChecked, bEnable); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				return 1;
			});
			duk_method(ctx, "Popup", 3, duk_fn() {
				auto obj = reuse_as<CMenu>(duk_member_handle(ctx));
				if (!obj)
					return DUK_RET_TYPE_ERROR;
				LPCSTR lpString = duk_to_string(ctx, 0);
				HMENU hPopup = nullptr;
				if (duk_class_handle(ctx, "Menu", hPopup, 1))
					return DUK_RET_TYPE_ERROR;
				bool bEnable = duk_is_undefined(ctx, 2) ? true : duk_to_boolean(ctx, 2);
				if (wx_try(ctx, [&]() { obj->Popup(lpString, hPopup, bEnable); }))
					return DUK_RET_INTERNAL_ERROR;
				if (hPopup) {
					duk_dup(ctx, 1);
					duk_finalizer(ctx, O);
				}
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
					CMenu menu = O;
					if (wx_try(ctx, [&]() { *menu = Menu(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_member_handle(ctx, menu);
					break;
				}
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_member_handle(ctx, duk_get_pointer(ctx, 0));
					} else {
						duk_errout(ctx, "Menu constructor: first argument must be a pointer to Menu");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					return DUK_ERR_SYNTAX_ERROR;
			}
			duk_push_this(ctx);
			duk_finalizer(ctx, duk_fn() {
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
	duk_function_global(ctx, "MenuPopup", duk_fn() {
		CMenu menu = O;
		if (wx_try(ctx, [&]() { *menu = Menu::CreatePopup(); }))
			return DUK_RET_INTERNAL_ERROR;
		duk_new_handle(ctx, "Menu", menu);
		return 1;
	}, 0);
}
#pragma region GDI Object

static void load_duk_devcap(duk_context *ctx) {
	
#pragma region Constants
	static duk_constant_struct _MapModes_constant[]{
		{ "Text", MM_TEXT },
		{ "LoMetric", MM_LOMETRIC },
		{ "HiMetric", MM_HIMETRIC },
		{ "LoEnglish", MM_LOENGLISH },
		{ "HiEnglish", MM_HIENGLISH },
		{ "Twips", MM_TWIPS },
		{ "Isotropic", MM_ISOTROPIC },
		{ "Anisotropic", MM_ANISOTROPIC }
	};
	duk_enums(ctx, "MapModes", O, _MapModes_constant);
	static duk_constant_struct _Stretches_constant[]{
		{ "And", BLACKONWHITE },
		{ "Or", WHITEONBLACK },
		{ "Del", COLORONCOLOR },
		{ "Half", HALFTONE }
	};
	duk_enums(ctx, "Stretches", O, _Stretches_constant);
#pragma endregion

	duk_class(ctx, "DevCap", O,
		duk_fn() {
			duk_method(ctx, "Delete", 0, duk_fn() {
				if (auto obj = reuse_as<CDevCap>(duk_member_handle(ctx)))
					if (wx_try(ctx, [&]() { obj->Delete(); }))
						return DUK_RET_INTERNAL_ERROR;
				duk_push_this(ctx);
				duk_del_prop_string(ctx, -1, "__p");
				return 0;
			});
			duk_method(ctx, "DrawIcon", 2, duk_fn() {
				auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
				if (!obj)
					return DUK_RET_TYPE_ERROR;
				HICON hIcon = O;
				if (duk_class_handle(ctx, "Icon", hIcon, 0))
					return DUK_RET_TYPE_ERROR;
				LPoint Pos;
				if (!duk_get_point(ctx, Pos, 1))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&]() { obj->DrawIcon(hIcon, Pos); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			});
			duk_method(ctx, "DrawPixel", 2, duk_fn() {
				auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
				if (!obj)
					return DUK_RET_TYPE_ERROR;
				LPoint Pos;
				if (!duk_get_point(ctx, Pos, 0))
					return DUK_RET_TYPE_ERROR;
				auto color = duk_to_int(ctx, 1);
				if (wx_try(ctx, [&]() { obj->DrawPixel(color, Pos); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			});
			duk_method(ctx, "DrawPie", 4, duk_fn() {
				auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
				if (!obj)
					return DUK_RET_TYPE_ERROR;
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0))
					return DUK_RET_TYPE_ERROR;
				LPoint start;
				if (!duk_get_point(ctx, start, 1))
					return DUK_RET_TYPE_ERROR;
				LPoint end;
				if (!duk_get_point(ctx, end, 2))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&]() { obj->DrawPie(rc, start, end); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			});
			duk_method(ctx, "DrawEllipse", 1, duk_fn() {
				auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
				if (!obj)
					return DUK_RET_TYPE_ERROR;
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&]() { obj->DrawEllipse(rc); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			});
			duk_method(ctx, "DrawFocus", 1, duk_fn() {
				auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
				if (!obj)
					return DUK_RET_TYPE_ERROR;
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&]() { obj->DrawFocus(rc); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			});
			duk_method(ctx, "Invert", 1, duk_fn() {
				auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
				if (!obj)
					return DUK_RET_TYPE_ERROR;
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&]() { obj->DrawFocus(rc); }))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			});
			duk_method(ctx, "Fill", 2, duk_fn() {
				auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
				if (!obj)
					return DUK_RET_TYPE_ERROR;
				HBRUSH hBrush;
				if (duk_class_handle(ctx, "Brush", hBrush, 0))
					return DUK_RET_TYPE_ERROR;
				LRect rc;
				if (wx_try(ctx, [&]() {
					if (duk_get_rect(ctx, rc, 1))
						obj->Fill(hBrush, rc);
					else
						obj->Fill(hBrush);
				}))
					return DUK_RET_INTERNAL_ERROR;
				return 0;
			});

#pragma region Properties
			duk_property(ctx, "PenColor",
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					auto color = duk_to_int(ctx, 0);
					if (wx_try(ctx, [&]() { obj->PenColor(color); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					COLORREF color = 0;
					if (wx_try(ctx, [&]() { color = obj->PenColor(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_int(ctx, color);
					return 1;
				}
			);
			duk_property(ctx, "BkColor",
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					auto color = duk_to_int(ctx, 0);
					if (wx_try(ctx, [&]() { obj->BkColor(color); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					COLORREF color = 0;
					if (wx_try(ctx, [&]() { color = obj->BkColor(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_int(ctx, color);
					return 1;
				}
			);
			duk_property(ctx, "ViewOrg",
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					LPoint Pos;
					if (!duk_get_point(ctx, Pos))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&]() { obj->ViewOrg(Pos); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					LPoint Pos;
					if (wx_try(ctx, [&]() { obj->ViewOrg(Pos); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_point(ctx, Pos);
					return 1;
				}
			);
			duk_property(ctx, "ViewExt",
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					LPoint Ext;
					if (!duk_get_point(ctx, Ext))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&]() { obj->ViewExt(Ext); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					LPoint Ext;
					if (wx_try(ctx, [&]() { obj->ViewExt(Ext); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_point(ctx, Ext);
					return 1;
				}
			);
			duk_property(ctx, "WindowOrg", 
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					LPoint Pos;
					if (!duk_get_point(ctx, Pos))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&]() { obj->WindowOrg(Pos); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					LPoint Pos;
					if (wx_try(ctx, [&]() { obj->WindowOrg(Pos); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_point(ctx, Pos);
					return 1;
				}
			);
			duk_property(ctx, "WindowExt", 
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					LPoint Ext;
					if (!duk_get_point(ctx, Ext))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&]() { obj->WindowExt(Ext); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					LPoint Ext;
					if (wx_try(ctx, [&]() { obj->WindowExt(Ext); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_push_point(ctx, Ext);
					return 1;
				}
			);
			duk_property(ctx, "MapMode",
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					auto mode = duk_to_int(ctx, 0);
					if (wx_try(ctx, [&]() { obj->MapMode(reuse_as<MapModes>(mode)); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					auto mode = reuse_as<MapModes>(0);
					if (wx_try(ctx, [&]() { mode = obj->MapMode(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_get_global_string(ctx, "MapModes");
					duk_push_int(ctx, mode.yield());
					duk_new(ctx, 1);
					return 1;
				}
			);
			duk_property(ctx, "StretchMode",
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					auto mode = duk_to_int(ctx, 0);
					if (wx_try(ctx, [&]() { obj->StretchMode(reuse_as<Stretches>(mode)); }))
						return DUK_RET_INTERNAL_ERROR;
					return 0;
				},
				duk_fn() {
					auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
					if (!obj)
						return DUK_RET_TYPE_ERROR;
					auto mode = reuse_as<Stretches>(0);
					if (wx_try(ctx, [&]() { mode = obj->StretchMode(); }))
						return DUK_RET_INTERNAL_ERROR;
					duk_get_global_string(ctx, "Stretches");
					duk_push_int(ctx, mode.yield());
					duk_new(ctx, 1);
					return 1;
				}
			);
			duk_property_r(ctx, "Size", duk_fn() {
				auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
				if (!obj)
					return DUK_RET_TYPE_ERROR;
				LPoint size;
				if (wx_try(ctx, [&]() { size = obj->Size(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_point(ctx, size);
				return 1;
			});
			duk_property_r(ctx, "PaletteRealize", duk_fn() {
				auto obj = reuse_as<CDevCap>(duk_member_handle(ctx));
				if (!obj)
					return DUK_RET_TYPE_ERROR;
				duk_uint_t size = 0;
				if (wx_try(ctx, [&]() { size = obj->PaletteRealize(); }))
					return DUK_RET_INTERNAL_ERROR;
				duk_push_uint(ctx, size);
				return 1;
			});
#pragma endregion

			return 0;
		},
		duk_fn() {
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
					} else if (duk_is_object(ctx, 0)) {
						duk_get_global_string(ctx, "DevCap");
						if (!duk_instanceof(ctx, 0, -1)) {
							duk_errout(ctx, "DevCap constructor: first argument must be a DevCap object");
							return DUK_RET_TYPE_ERROR;
						}
						duk_get_prop_string(ctx, 0, "__p");
						if (duk_get_type(ctx, -1) != DUK_TYPE_POINTER) {
							duk_errout(ctx, "DevCap constructor: first argument must be a valid DevCap object");
							return DUK_RET_SYNTAX_ERROR;
						}
						HDC dc = O;
						if (wx_try(ctx, [&]() { dc = DevCap::CreateCompatible(); }))
							return DUK_RET_INTERNAL_ERROR;
						duk_member_handle(ctx, dc);
						duk_errout(ctx, "DevCap constructor: first argument must be a pointer to DevCap");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					return DUK_ERR_SYNTAX_ERROR;
			}
			duk_push_this(ctx);
			duk_finalizer(ctx, duk_fn() {
				duk_get_prop_string(ctx, 0, "__p");
				if (!duk_is_pointer(ctx, -1))
					return 0;
				if (auto dc = reuse_as<CDevCap>(duk_get_pointer(ctx, -1)))
					dc->Delete();
				duk_del_prop_string(ctx, 0, "__p");
				return 0;
			});
			return 0;
		}
	);
}

static void load_duk_accelerator(duk_context *ctx) {
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
