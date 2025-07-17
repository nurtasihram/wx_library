#include "wx_gdi.h"

#include "wx_duk.h"

template<class AnyClass>
static void __CommGDI(duk_context *ctx) {
	duk_put_method(ctx, "Delete", 0, duk_fn {
		if (auto pobj = duk_get_this__p<AnyClass>(ctx))
			if (wx_try(ctx, [&] { pobj->Delete(); }))
				return DUK_RET_REFERENCE_ERROR;
		return 0;
	});
}

static void load_duk_font(duk_context *ctx) {
#pragma region Constants
	//static const duk_constant __FontType_constant[] {
	//	{ "Default", 0 },
	//	{ "Device", DEVICE_FONTTYPE },
	//	{ "Raster", RASTER_FONTTYPE },
	//	{ "TrueType", TRUETYPE_FONTTYPE }
	//};
	static const duk_constant __FontType_constant[]{
		{ "Simulated", SIMULATED_FONTTYPE },
		{ "Printer", PRINTER_FONTTYPE },
		{ "Screen", SCREEN_FONTTYPE },
		{ "Bold", BOLD_FONTTYPE },
		{ "Italic", ITALIC_FONTTYPE },
		{ "Regular", REGULAR_FONTTYPE },
		//{ "PS_OpenType", PS_OPENTYPE_FONTTYPE },
		//{ "TT_OpenType", TT_OPENTYPE_FONTTYPE },
		//{ "Type1", TYPE1_FONTTYPE },
		//{ "Symbol", SYMBOL_FONTTYPE }
	};
	duk_add_global_flags(ctx, "FontType", O, __FontType_constant);
	static const duk_constant __CharSets_constant[]{
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
	duk_add_global_enums(ctx, "CharSets", O, __CharSets_constant);
	static const duk_constant __OutPrecis_constant[]{
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
	duk_add_global_enums(ctx, "OutPrecis", O, __OutPrecis_constant);
	static const duk_constant __ClipPrecis_constant[]{
		{ "Default", CLIP_DEFAULT_PRECIS },
		{ "Character", CLIP_CHARACTER_PRECIS },
		{ "Stroke", CLIP_STROKE_PRECIS },
		{ "Mask", CLIP_MASK },
		{ "LH_Angles", CLIP_LH_ANGLES },
		{ "TT_Always", CLIP_TT_ALWAYS },
		{ "DFA_Disable", CLIP_DFA_DISABLE },
		{ "Embedded", CLIP_EMBEDDED }
	};
	duk_add_global_flags(ctx, "ClipPrecis", O, __ClipPrecis_constant);
	static const duk_constant __Qualities_constant[]{
		{ "Default", DEFAULT_QUALITY },
		{ "Draf", DRAFT_QUALITY },
		{ "Proof", PROOF_QUALITY },
		{ "NonAntiAliased", NONANTIALIASED_QUALITY },
		{ "AntiAliased", ANTIALIASED_QUALITY },
		{ "ClearType", CLEARTYPE_QUALITY },
		{ "ClearTypeNatural", CLEARTYPE_NATURAL_QUALITY }
	};
	duk_add_global_enums(ctx, "Qualities", O, __Qualities_constant);
	static const duk_constant __FontPitches_constant[]{
		{ "Default", DEFAULT_PITCH },
		{ "Fixed", FIXED_PITCH },
		{ "Variable", VARIABLE_PITCH },
		{ "Mono", MONO_FONT }
	};
	duk_add_global_enums(ctx, "FontPitches", O, __FontPitches_constant);
	static const duk_constant __FontFamilies_constant[]{
		{ "DontCare", FF_DONTCARE },
		{ "Roman", FF_ROMAN },
		{ "Swiss", FF_SWISS },
		{ "Modern", FF_MODERN },
		{ "Script", FF_SCRIPT },
		{ "Decorative", FF_DECORATIVE }
	};
	duk_add_global_enums(ctx, "FontFamilies", O, __FontFamilies_constant);
#pragma endregion
	duk_put_global_class(
		ctx, "FontLogic", O,
		duk_structure {
			/* int */ duk_put_prop(ctx, "Height",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->Height(duk_to_int(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->Height());
					return 1;
				}
			);
			/* int */ duk_put_prop(ctx, "Width",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->Width(duk_to_int(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->Width());
					return 1;
				}
			);
			/* int */ duk_put_prop(ctx, "Escapement",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->Escapement(duk_to_int(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->Escapement());
					return 1;
				}
			);
			/* int */ duk_put_prop(ctx, "Orientation",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->Orientation(duk_to_int(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->Orientation());
					return 1;
				}
			);
			/* int */ duk_put_prop(ctx, "Weight",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->Weight(duk_to_int(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->Weight());
					return 1;
				}
			);
			/* bool */ duk_put_prop(ctx, "Italic",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->Italic(duk_to_boolean(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_boolean(ctx, pobj->Italic());
					return 1;
				}
			);
			/* bool */ duk_put_prop(ctx, "Underline",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->Underline(duk_to_boolean(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_boolean(ctx, pobj->Underline());
					return 1;
				}
			);
			/* bool */ duk_put_prop(ctx, "StrikeOut",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->StrikeOut(duk_to_boolean(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_boolean(ctx, pobj->StrikeOut());
					return 1;
				}
			);
			/* CharSets */ duk_put_prop(ctx, "CharSet",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->CharSet(reuse_as<CharSets>((BYTE)duk_to_uint16(ctx, 0)));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "CharSets", (int)pobj->CharSet().yield());
					return 1;
				}
			);
			/* OutPrecis */ duk_put_prop(ctx, "OutPrecision",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->OutPrecision(reuse_as<OutPrecis>((BYTE)duk_to_int(ctx, 0)));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "OutPrecis", (int)pobj->OutPrecision().yield());
					return 1;
				}
			);
			/* ClipPrecis */ duk_put_prop(ctx, "ClipPrecision",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->ClipPrecision(reuse_as<ClipPrecis>((BYTE)duk_to_int(ctx, 0)));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "ClipPrecis", (int)pobj->ClipPrecision().yield());
					return 1;
				}
			);
			/* Qualities */ duk_put_prop(ctx, "Quality",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->Quality(reuse_as<Qualities>((BYTE)duk_to_int(ctx, 0)));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "Qualities", (int)pobj->Quality().yield());
					return 1;
				}
			);
			/* FontPitches */ duk_put_prop(ctx, "Pitch",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->Pitch(reuse_as<FontPitches>((BYTE)duk_to_int(ctx, 0)));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "FontPitches", (int)pobj->Pitch().yield());
					return 1;
				}
			);
			/* FontFamilies */ duk_put_prop(ctx, "Family",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->Family(reuse_as<FontFamilies>((BYTE)duk_to_int(ctx, 0)));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "FontFamilies", (int)pobj->Family().yield());
					return 1;
				}
			);
			/* String */ duk_put_prop(ctx, "FaceName",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->FaceName(CString(duk_to_string(ctx, 0), LF_FACESIZE));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_string(ctx, pobj->FaceName());
					return 1;
				}
			);

			/* String */ duk_put_method(ctx, "toString", 0, duk_fn {
				auto pobj = duk_get_this__p<FontLogicA>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				auto lpszCharSet = duk_this_prop_to_string(ctx, "CharSet"),
					 lpszOutPrecis = duk_this_prop_to_string(ctx, "OutPrecision"),
					 lpszClipPrecis = duk_this_prop_to_string(ctx, "ClipPrecision");
				auto lpszQuality = duk_this_prop_to_string(ctx, "Quality"),
					 lpszPitch = duk_this_prop_to_string(ctx, "Pitch"),
					 lpszFamily = duk_this_prop_to_string(ctx, "Family");
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
					lpszCharSet, lpszOutPrecis, lpszClipPrecis, lpszQuality, lpszPitch, lpszFamily,
					(LPCSTR)pobj->FaceName());
				return 1;
			});
			return 0;
		},
		duk_constructor {
			if (duk_reflect_constructor(ctx))
				return 1;
			FontLogicA *pobj = O;
			switch (duk_get_top(ctx)) {
				case 0: {
					duk_push_this(ctx);
					duk_push_string(ctx, "__p");
					pobj = (FontLogicA *)duk_push_fixed_buffer(ctx, sizeof(FontLogicA));
					new(pobj) FontLogicA();
					duk_def_prop(ctx, -3,
								 DUK_DEFPROP_HAVE_VALUE |
								 DUK_DEFPROP_CLEAR_CONFIGURABLE |
								 DUK_DEFPROP_CLEAR_ENUMERABLE |
								 DUK_DEFPROP_CLEAR_WRITABLE
					);
					break;
				}
				case 1: {
					duk_size_t size = 0;
					if (duk_get_buffer(ctx, 0, &size))
						if (size == sizeof(FontLogicA)) {
							duk_push_this(ctx);
							duk_push_string(ctx, "__p");
							duk_dup(ctx, 0);
							duk_def_prop(ctx, -3,
										 DUK_DEFPROP_HAVE_VALUE |
										 DUK_DEFPROP_CLEAR_CONFIGURABLE |
										 DUK_DEFPROP_CLEAR_ENUMERABLE |
										 DUK_DEFPROP_CLEAR_WRITABLE
							);
							break;
						}
					return DUK_RET_TYPE_ERROR;
				}
			}
			return 0;
		}
	);
	duk_put_global_class(
		ctx, "Font", O,
		duk_structure {
			return 0;
		},
		duk_constructor {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_put_this__p(ctx, duk_get_pointer(ctx, 0));
					} elif  (duk_is_null(ctx, 0)) {
						duk_put_this__p(ctx, O);
					} elif  (duk_is_object(ctx, 0)) {
						duk_get_global_string(ctx, "FontLogic");
						if (!duk_instanceof(ctx, 0, -1))
							return DUK_RET_TYPE_ERROR;
						duk_push_this(ctx);
						duk_get_prop_string(ctx, 0, "__p");
						duk_size_t size = 0;
						auto lpLogFont = (FontLogicA *)duk_get_buffer(ctx, -1, &size);
						if (size != sizeof(FontLogicA))
							return DUK_RET_TYPE_ERROR;
						CFont font = O;
						if (wx_try(ctx, [&]() { *font = Font(*lpLogFont); }))
							return DUK_RET_REFERENCE_ERROR;
						duk_put_this__p(ctx, font);
					} else {
						duk_errout(ctx, "Font constructor: first argument must be a handler to HFONT or FontLogic");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Font constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 0;
		}
	);
}
static void load_duk_bitmap(duk_context *ctx) {
	duk_put_global_class(
		ctx, "Bitmap", O,
		duk_structure {
			__CommGDI<CBitmap>(ctx);
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
						duk_errout(ctx, "Bitmap constructor: first argument must be a handler to HBITMAP");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Bitmap constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 0;
		}
	);
}
static void load_duk_pen(duk_context *ctx) {
	static const duk_constant _PenStyles_constant[]{
		{ "Solid", PS_SOLID },
		{ "Dash", PS_DASH },
		{ "Dot", PS_DOT },
		{ "DashDot", PS_DASHDOT },
		{ "DashDotDot", PS_DASHDOTDOT },
		{ "Null", PS_NULL },
		{ "InsideFrame", PS_INSIDEFRAME },
		{ "UserStyle", PS_USERSTYLE },
		{ "Alternate", PS_ALTERNATE }
	};
	duk_add_global_flags(ctx, "PenStyles", O, _PenStyles_constant);
	duk_put_global_class(
		ctx, "PenLogic", O,
		duk_structure {
			__CommGDI<CPen>(ctx);
			/* PenStyles */ duk_put_prop(ctx, "Style",
				duk_set {
					auto pobj = duk_get_this__p<PenLogic>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->Style(reuse_as<PenStyles>(duk_to_int(ctx, 0)));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<PenLogic>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->Style().yield());
					return 1;
				}
			);
			/* Point */ duk_put_prop(ctx, "Width",
				duk_set {
					auto pobj = duk_get_this__p<PenLogic>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					LPoint width;
					if (!duk_get_point(ctx, width, 0))
						return DUK_RET_TYPE_ERROR;
					pobj->Width(width);
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<PenLogic>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_point(ctx, pobj->Width());
					return 1;
				}
			);
			/* RGB */ duk_put_prop(ctx, "Color",
				duk_set {
					auto pobj = duk_get_this__p<PenLogic>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					pobj->Color(duk_to_uint32(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<PenLogic>(ctx);
					if (!pobj)
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "RGB", pobj->Color());
					return 1;
				}
			);
			return 0;
		},
		duk_constructor {
			return 0;
		}
	);
	duk_put_global_class(
		ctx, "Pen", O,
		duk_structure {
			__CommGDI<CPen>(ctx);
			return 0;
		},
		duk_constructor {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_put_this__p(ctx, duk_get_pointer(ctx, 0));
					} elif  (duk_is_null(ctx, 0)) {
						duk_put_this__p(ctx, O);
					} elif  (duk_is_object(ctx, 0)) {
						duk_get_global_string(ctx, "PenLogic");
						if (!duk_instanceof(ctx, 0, -1))
							return DUK_RET_TYPE_ERROR;
						duk_push_this(ctx);
						duk_get_prop_string(ctx, 0, "__p");
						duk_size_t size = 0;
						auto lpLogPen = (PenLogic *)duk_get_buffer(ctx, -1, &size);
						if (size != sizeof(PenLogic))
							return DUK_RET_TYPE_ERROR;
						CPen pen = O;
						if (wx_try(ctx, [&]() { *pen = Pen::Create(*lpLogPen); }))
							return DUK_RET_REFERENCE_ERROR;
						duk_put_this__p(ctx, pen);
					} else {
						duk_errout(ctx, "Pen constructor: first argument must be a handler to HPEN or PenLogic");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Pen constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 0;
		},
		duk_static {
			/* Pen */ duk_put_method(ctx, "CreateSolid", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateSolid(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_put_method(ctx, "CreateDash", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateDash(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_put_method(ctx, "CreateDot", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateDot(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_put_method(ctx, "CreateDashDot", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateDashDot(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_put_method(ctx, "CreateDashDotDot", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateDashDotDot(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_put_method(ctx, "CreateNull", 2, duk_fn{
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateNull(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
									 });
			/* Pen */ duk_put_method(ctx, "CreateInsideFrame", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateInsideFrame(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_put_method(ctx, "CreateUserStyle", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateUserStyle(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_put_method(ctx, "CreateAlternate", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateAlternate(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_put_prop_r(ctx, "White", duk_fn {
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::White(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_put_prop_r(ctx, "Black", duk_fn {
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::Black(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_put_prop_r(ctx, "Null", duk_fn {
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::Null(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_put_prop_r(ctx, "DC", duk_fn {
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::DC(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			return 0;
		}
	);
}
static void load_duk_brush(duk_context *ctx) {

	static const duk_constant _HatchStyle_constant[]{
		{ "Horizontal", HS_HORIZONTAL },
		{ "Vertical", HS_VERTICAL },
		{ "FDiagonal", HS_FDIAGONAL },
		{ "BDiagonal", HS_BDIAGONAL },
		{ "Cross", HS_CROSS },
		{ "DiagCross", HS_DIAGCROSS }
	};
	duk_add_global_enums(ctx, "HatchStyle", O, _HatchStyle_constant);
	duk_put_global_class(
		ctx, "Brush", O,
		duk_structure {
			__CommGDI<CBrush>(ctx);
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
						duk_errout(ctx, "Brush constructor: first argument must be a handler to HBRUSH");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Brush constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 0;
		},
		duk_static {
			/* Brush */ duk_put_method(ctx, "CreateSolid", 1, duk_fn {
				auto color = duk_to_int(ctx, 0);
				CBrush brush = O;
				if (wx_try(ctx, [&] { *brush = Brush::CreateSolid(color); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Brush", brush);
				return 1;
			});
			/* Brush */ duk_put_method(ctx, "CreatePattern", 1, duk_fn {
				HBITMAP hBitmap = O;
				if (duk_get_class__p(ctx, "Bitmap", hBitmap))
					return DUK_RET_TYPE_ERROR;
				CBrush brush = O;
				if (wx_try(ctx, [&] { *brush = Brush::CreatePattern(hBitmap); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Brush", brush);
				return 1;
			});
			/* Brush */ duk_put_method(ctx, "CreateHatch", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto style = reuse_as<HatchStyle>(duk_to_int(ctx, 1));
				CBrush brush = O;
				if (wx_try(ctx, [&] { *brush = Brush::CreateHatch(color, style); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Brush", brush);
				return 1;
			});
			/* Brush */ duk_put_prop_r(ctx, "White", duk_fn {
				CBrush brush = O;
				if (wx_try(ctx, [&] { *brush = Brush::White(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Brush", brush);
				return 1;
			});
			/* Brush */ duk_put_prop_r(ctx, "LitGray", duk_fn {
				CBrush brush = O;
				if (wx_try(ctx, [&] { *brush = Brush::LitGray(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Brush", brush);
				return 1;
			});
			/* Brush */ duk_put_prop_r(ctx, "Gray", duk_fn {
				CBrush brush = O;
				if (wx_try(ctx, [&] { *brush = Brush::Gray(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Brush", brush);
				return 1;
			});
			/* Brush */ duk_put_prop_r(ctx, "DkGray", duk_fn {
				CBrush brush = O;
				if (wx_try(ctx, [&] { *brush = Brush::DkGray(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Brush", brush);
				return 1;
			});
			/* Brush */ duk_put_prop_r(ctx, "Black", duk_fn {
				CBrush brush = O;
				if (wx_try(ctx, [&] { *brush = Brush::Black(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Brush", brush);
				return 1;
			});
			/* Brush */ duk_put_prop_r(ctx, "Null", duk_fn {
				CBrush brush = O;
				if (wx_try(ctx, [&] { *brush = Brush::Null(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Brush", brush);
				return 1;
			});
			/* Brush */ duk_put_prop_r(ctx, "DC", duk_fn {
				CBrush brush = O;
				if (wx_try(ctx, [&] { *brush = Brush::DC(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Brush", brush);
				return 1;
			});
			return 0;
		}
	);

}
static void load_duk_palette(duk_context *ctx) {
	duk_put_global_class(
		ctx, "Palette", O,
		duk_structure {
			__CommGDI<CPalette>(ctx);
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
						duk_errout(ctx, "Palette constructor: first argument must be a handler to HPALETTE");
						return DUK_RET_TYPE_ERROR;
					}
					break;
				default:
					duk_errout(ctx, "Palette constructor: invalid number of arguments");
					return DUK_RET_TYPE_ERROR;
			}
			return 0;
		}
	);
}
static void load_duk_region(duk_context *ctx) {
}
static void load_duk_devcap(duk_context *ctx) {
	
	static auto _selectable = duk_set {
		if (!duk_is_object(ctx, 0))
			return false;
		duk_get_global_string(ctx, "Bitmap");
		if (duk_instanceof(ctx, 0, -1))
			return true;
		duk_get_global_string(ctx, "Brush");
		if (duk_instanceof(ctx, 0, -1))
			return true;
		duk_get_global_string(ctx, "Font");
		if (duk_instanceof(ctx, 0, -1))
			return true;
		duk_get_global_string(ctx, "Pen");
		if (duk_instanceof(ctx, 0, -1))
			return true;
		duk_get_global_string(ctx, "Rgn");
		if (duk_instanceof(ctx, 0, -1))
			return true;
		return false;
	};

	static duk_constant _MapModes_constant[]{
		{ "Text", MM_TEXT },
		{ "LoMetric", MM_LOMETRIC },
		{ "HiMetric", MM_HIMETRIC },
		{ "LoEnglish", MM_LOENGLISH },
		{ "HiEnglish", MM_HIENGLISH },
		{ "Twips", MM_TWIPS },
		{ "Isotropic", MM_ISOTROPIC },
		{ "Anisotropic", MM_ANISOTROPIC }
	};
	duk_add_global_enums(ctx, "MapModes", O, _MapModes_constant);
	static duk_constant _Stretches_constant[]{
		{ "And", BLACKONWHITE },
		{ "Or", WHITEONBLACK },
		{ "Del", COLORONCOLOR },
		{ "Half", HALFTONE }
	};
	duk_add_global_enums(ctx, "Stretches", O, _Stretches_constant);
	static duk_constant _PolyFills_constant[]{
		{ "Alternate", ALTERNATE },
		{ "Winding", WINDING }
	};
	duk_add_global_enums(ctx, "PolyFills", O, _PolyFills_constant);
	static duk_constant _TextAlign_constant[]{
		{ "NoUpDateCP", TA_NOUPDATECP },
		{ "UpDateCP", TA_UPDATECP },
		{ "Left", TA_LEFT },
		{ "Right", TA_RIGHT },
		{ "Center", TA_CENTER },
		{ "Top", TA_TOP },
		{ "Bottom", TA_BOTTOM },
		{ "Baseline", TA_BASELINE },
		{ "RTLReading", TA_RTLREADING }
	};
	duk_add_global_enums(ctx, "TextAlign", O, _TextAlign_constant);

	duk_put_global_class(
		ctx, "DevCap", O,
		duk_structure {
			/* void */ duk_put_method(ctx, "Delete", 0, duk_fn {
				if (auto pobj = duk_get_this__p<CDevCap>(ctx))
					if (wx_try(ctx, [&] { pobj->Delete(); }))
						return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				duk_del_prop_string(ctx, -1, "__p");
				return 0;
			});
			/* void */ duk_put_method(ctx, "DrawIcon", 2, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj)
					return DUK_RET_TYPE_ERROR;
				HICON hIcon = O;
				if (duk_get_class__p(ctx, "Icon", hIcon, 0))
					return DUK_RET_TYPE_ERROR;
				LPoint Pos;
				if (!duk_get_point(ctx, Pos, 1))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&] { pobj->DrawIcon(hIcon, Pos); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "DrawPixel", 2, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj)
					return DUK_RET_TYPE_ERROR;
				LPoint Pos;
				if (!duk_get_point(ctx, Pos, 0))
					return DUK_RET_TYPE_ERROR;
				auto color = duk_to_int(ctx, 1);
				if (wx_try(ctx, [&] { pobj->DrawPixel(color, Pos); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "DrawPie", 4, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj)
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
				if (wx_try(ctx, [&] { pobj->DrawPie(rc, start, end); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "DrawEllipse", 1, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj)
					return DUK_RET_TYPE_ERROR;
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&] { pobj->DrawEllipse(rc); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "DrawFocus", 1, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj)
					return DUK_RET_TYPE_ERROR;
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&] { pobj->DrawFocus(rc); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "Invert", 1, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj)
					return DUK_RET_TYPE_ERROR;
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&] { pobj->DrawFocus(rc); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "Fill", 2, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj)
					return DUK_RET_TYPE_ERROR;
				HBRUSH hBrush;
				if (duk_get_class__p(ctx, "Brush", hBrush, 0))
					return DUK_RET_TYPE_ERROR;
				LRect rc;
				if (wx_try(ctx, [&] {
					if (duk_get_rect(ctx, rc, 1))
						pobj->Fill(hBrush, rc);
					else
						pobj->Fill(hBrush);
				}))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "Select", 1, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj)
					return DUK_RET_TYPE_ERROR;
				duk_push_c_function(ctx, _selectable, 1);
				duk_dup(ctx, 0);
				duk_call(ctx, 1);
				if (!duk_to_boolean(ctx, -1))
					return DUK_RET_TYPE_ERROR;
				duk_get_prop_string(ctx, 0, "__p");
				if (!duk_is_pointer(ctx, -1))
					return DUK_RET_TYPE_ERROR;
				auto hgdiobj = duk_to_pointer(ctx, -1);
				pobj->Select(hgdiobj);
				return 0;
			});

			/* RGB */ duk_put_prop(ctx, "PenColor",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					auto color = duk_to_int(ctx, 0);
					if (wx_try(ctx, [&] { pobj->PenColor(color); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					COLORREF color = 0;
					if (wx_try(ctx, [&] { color = pobj->PenColor(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "RGB", color);
					return 1;
				}
			);
			/* RGB */ duk_put_prop(ctx, "BkColor",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					auto color = duk_to_int(ctx, 0);
					if (wx_try(ctx, [&] { pobj->BkColor(color); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					COLORREF color = 0;
					if (wx_try(ctx, [&] { color = pobj->BkColor(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "RGB", color);
					return 1;
				}
			);
			/* RGB */ duk_put_prop(ctx, "TextColor",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					auto color = duk_to_uint(ctx, 0);
					if (wx_try(ctx, [&] { pobj->TextColor(color); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					COLORREF color = 0;
					if (wx_try(ctx, [&] { color = pobj->TextColor(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "RGB", color);
					return 1;
				}
			);
			/* TextAlign */ duk_put_prop(ctx, "TextAligns",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					auto align = duk_to_uint(ctx, 0);
					if (wx_try(ctx, [&] { pobj->TextAligns(reuse_as<TextAlign>(align)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					auto align = reuse_as<TextAlign>(0);
					if (wx_try(ctx, [&] { align = pobj->TextAligns(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "TextAlign", align.yield());
					return 1;
				}
			);
			/* Point */ duk_put_prop(ctx, "ViewOrg",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					LPoint Pos;
					if (!duk_get_point(ctx, Pos))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->ViewOrg(Pos); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					LPoint Pos;
					if (wx_try(ctx, [&] { pobj->ViewOrg(Pos); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_point(ctx, Pos);
					return 1;
				}
			);
			/* Point */ duk_put_prop(ctx, "ViewExt",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					LPoint Ext;
					if (!duk_get_point(ctx, Ext))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->ViewExt(Ext); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					LPoint Ext;
					if (wx_try(ctx, [&] { pobj->ViewExt(Ext); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_point(ctx, Ext);
					return 1;
				}
			);
			/* Point */ duk_put_prop(ctx, "WindowOrg",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					LPoint Pos;
					if (!duk_get_point(ctx, Pos))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->WindowOrg(Pos); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					LPoint Pos;
					if (wx_try(ctx, [&] { pobj->WindowOrg(Pos); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_point(ctx, Pos);
					return 1;
				}
			);
			/* Point */ duk_put_prop(ctx, "WindowExt",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					LPoint Ext;
					if (!duk_get_point(ctx, Ext))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->WindowExt(Ext); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					LPoint Ext;
					if (wx_try(ctx, [&] { pobj->WindowExt(Ext); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_point(ctx, Ext);
					return 1;
				}
			);
			/* MapModes */ duk_put_prop(ctx, "MapMode",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					auto mode = duk_to_int(ctx, 0);
					if (wx_try(ctx, [&] { pobj->MapMode(reuse_as<MapModes>(mode)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					auto mode = reuse_as<MapModes>(0);
					if (wx_try(ctx, [&] { mode = pobj->MapMode(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "MapModes", mode.yield());
					return 1;
				}
			);
			/* Stretches */ duk_put_prop(ctx, "StretchMode",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					auto mode = duk_to_int(ctx, 0);
					if (wx_try(ctx, [&] { pobj->StretchMode(reuse_as<Stretches>(mode)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					auto mode = reuse_as<Stretches>(0);
					if (wx_try(ctx, [&] { mode = pobj->StretchMode(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "Stretches", mode.yield());
					return 1;
				}
			);
			/* PolyFills */ duk_put_prop(ctx, "PolyFillMode",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					auto mode = duk_to_int(ctx, 0);
					if (wx_try(ctx, [&] { pobj->PolyFill(reuse_as<PolyFills>(mode)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj)
						return DUK_RET_TYPE_ERROR;
					auto mode = reuse_as<PolyFills>(0);
					if (wx_try(ctx, [&] { mode = pobj->PolyFill(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "PolyFills", mode.yield());
					return 1;
				}
			);
			/* Point */ duk_put_prop_r(ctx, "Size", duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj)
					return DUK_RET_TYPE_ERROR;
				LPoint size;
				if (wx_try(ctx, [&] { size = pobj->Size(); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_point(ctx, size);
				return 1;
			});

			///* uint */ duk_put_prop_r(ctx, "PaletteRealize", duk_fn {
			//	auto pobj = duk_get_this__p<CDevCap>(ctx);
			//	if (!pobj)
			//		return DUK_RET_TYPE_ERROR;
			//	duk_uint_t size = 0;
			//	if (wx_try(ctx, [&] { size = pobj->PaletteRealize(); }))
			//		return DUK_RET_REFERENCE_ERROR;
			//	duk_push_uint(ctx, size);
			//	return 1;
			//});

			return 0;
		},
		duk_constructor {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					HDC dc = O;
					if (wx_try(ctx, [&] { dc = DevCap::CreateCompatible(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_put_this__p(ctx, dc);
					break;
				}
				case 1:
					if (duk_is_pointer(ctx, 0)) {
						duk_put_this__p(ctx, duk_get_pointer(ctx, 0));
					} elif  (duk_is_object(ctx, 0)) {
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
						if (wx_try(ctx, [&] { dc = DevCap::CreateCompatible(); }))
							return DUK_RET_REFERENCE_ERROR;
						duk_put_this__p(ctx, dc);
						duk_errout(ctx, "DevCap constructor: first argument must be a pointer to DevCap");
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
				if (auto dc = reuse_as<CDevCap>(duk_get_pointer(ctx, -1)))
					dc->Delete();
				duk_del_prop_string(ctx, 0, "__p");
				return 0;
			});
			return 0;
		}
	);

}

void load_duk_gdi(duk_context *ctx) {
	load_duk_bitmap(ctx);
	load_duk_pen(ctx);
	load_duk_brush(ctx);
	load_duk_font(ctx);
	load_duk_palette(ctx);
	load_duk_region(ctx);
	load_duk_devcap(ctx);
}
