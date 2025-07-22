#include "wx_gdi.h"

#include "wx_duk.h"

template<class AnyClass>
static void __CommGDI(duk_context *ctx) {
	duk_add_method(ctx, "Delete", 0, duk_fn {
		if (auto pobj = duk_get_this__p<AnyClass>(ctx))
			if (wx_try(ctx, [&] { pobj->Delete(); }))
				return DUK_RET_REFERENCE_ERROR;
		return 0;
	});
}

static void load_duk_font(duk_context *ctx) {
#pragma region Constants
	duk_add_enum_flags<FontType>(ctx);
	duk_add_enum_flags<CharSets>(ctx);
	duk_add_enum_flags<OutPrecis>(ctx);
	duk_add_enum_flags<ClipPrecis>(ctx);
	duk_add_enum_flags<Qualities>(ctx);
	duk_add_enum_flags<FontPitches>(ctx);
	duk_add_enum_flags<FontFamilies>(ctx);
#pragma endregion
	duk_add_class(
		ctx, "FontLogic", O,
		duk_structure {
			/* int */ duk_add_prop(ctx, "Height",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->Height(duk_to_int(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->Height());
					return 1;
				}
			);
			/* int */ duk_add_prop(ctx, "Width",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->Width(duk_to_int(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->Width());
					return 1;
				}
			);
			/* int */ duk_add_prop(ctx, "Escapement",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->Escapement(duk_to_int(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->Escapement());
					return 1;
				}
			);
			/* int */ duk_add_prop(ctx, "Orientation",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->Orientation(duk_to_int(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->Orientation());
					return 1;
				}
			);
			/* int */ duk_add_prop(ctx, "Weight",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->Weight(duk_to_int(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->Weight());
					return 1;
				}
			);
			/* bool */ duk_add_prop(ctx, "Italic",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->Italic(duk_to_boolean(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_boolean(ctx, pobj->Italic());
					return 1;
				}
			);
			/* bool */ duk_add_prop(ctx, "Underline",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->Underline(duk_to_boolean(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_boolean(ctx, pobj->Underline());
					return 1;
				}
			);
			/* bool */ duk_add_prop(ctx, "StrikeOut",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->StrikeOut(duk_to_boolean(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_boolean(ctx, pobj->StrikeOut());
					return 1;
				}
			);
			/* CharSets */ duk_add_prop(ctx, "CharSet",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->CharSet(reuse_as<CharSets>((BYTE)duk_to_uint16(ctx, 0)));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "CharSets", (int)pobj->CharSet().yield());
					return 1;
				}
			);
			/* OutPrecis */ duk_add_prop(ctx, "OutPrecision",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->OutPrecision(reuse_as<OutPrecis>((BYTE)duk_to_int(ctx, 0)));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "OutPrecis", (int)pobj->OutPrecision().yield());
					return 1;
				}
			);
			/* ClipPrecis */ duk_add_prop(ctx, "ClipPrecision",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->ClipPrecision(reuse_as<ClipPrecis>((BYTE)duk_to_int(ctx, 0)));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "ClipPrecis", (int)pobj->ClipPrecision().yield());
					return 1;
				}
			);
			/* Qualities */ duk_add_prop(ctx, "Quality",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->Quality(reuse_as<Qualities>((BYTE)duk_to_int(ctx, 0)));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "Qualities", (int)pobj->Quality().yield());
					return 1;
				}
			);
			/* FontPitches */ duk_add_prop(ctx, "Pitch",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->Pitch(reuse_as<FontPitches>((BYTE)duk_to_int(ctx, 0)));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "FontPitches", (int)pobj->Pitch().yield());
					return 1;
				}
			);
			/* FontFamilies */ duk_add_prop(ctx, "Family",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->Family(reuse_as<FontFamilies>((BYTE)duk_to_int(ctx, 0)));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "FontFamilies", (int)pobj->Family().yield());
					return 1;
				}
			);
			/* String */ duk_add_prop(ctx, "FaceName",
				duk_set {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->FaceName(CString(duk_to_string(ctx, 0), LF_FACESIZE));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<FontLogicA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_string(ctx, pobj->FaceName());
					return 1;
				}
			);

			/* String */ duk_add_method(ctx, "toString", 0, duk_fn {
				auto pobj = duk_get_this__p<FontLogicA>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
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
	duk_add_class(
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
					} elif (duk_is_null(ctx, 0)) {
						duk_put_this__p(ctx, O);
					} elif (duk_is_object(ctx, 0)) {
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
	duk_add_class(
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
	duk_add_enum_flags<PenStyles>(ctx);
	duk_add_class(
		ctx, "PenLogic", O,
		duk_structure {
			__CommGDI<CPen>(ctx);
			/* PenStyles */ duk_add_prop(ctx, "Style",
				duk_set {
					auto pobj = duk_get_this__p<PenLogic>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->Style(reuse_as<PenStyles>(duk_to_int(ctx, 0)));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<PenLogic>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->Style().yield());
					return 1;
				}
			);
			/* Point */ duk_add_prop(ctx, "Width",
				duk_set {
					auto pobj = duk_get_this__p<PenLogic>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					LPoint width;
					if (!duk_get_point(ctx, width, 0))
						return DUK_RET_TYPE_ERROR;
					pobj->Width(width);
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<PenLogic>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_point(ctx, pobj->Width());
					return 1;
				}
			);
			/* RGB */ duk_add_prop(ctx, "Color",
				duk_set {
					auto pobj = duk_get_this__p<PenLogic>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->Color(duk_to_uint32(ctx, 0));
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<PenLogic>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
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
	duk_add_class(
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
					} elif (duk_is_null(ctx, 0)) {
						duk_put_this__p(ctx, O);
					} elif (duk_is_object(ctx, 0)) {
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
			/* Pen */ duk_add_method(ctx, "CreateSolid", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateSolid(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_add_method(ctx, "CreateDash", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateDash(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_add_method(ctx, "CreateDot", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateDot(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_add_method(ctx, "CreateDashDot", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateDashDot(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_add_method(ctx, "CreateDashDotDot", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateDashDotDot(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_add_method(ctx, "CreateNull", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateNull(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
									 });
			/* Pen */ duk_add_method(ctx, "CreateInsideFrame", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateInsideFrame(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_add_method(ctx, "CreateUserStyle", 2, duk_fn {
				auto color = duk_to_int(ctx, 0);
				auto width = duk_to_int(ctx, 1);
				CPen pen = O;
				if (wx_try(ctx, [&] { *pen = Pen::CreateUserStyle(color, width); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Pen", pen);
				return 1;
			});
			/* Pen */ duk_add_method(ctx, "CreateAlternate", 2, duk_fn {
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

	duk_add_enum_flags<HatchStyle>(ctx);
	duk_add_class(
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
			/* Brush */ duk_add_method(ctx, "CreateSolid", 1, duk_fn {
				auto color = duk_to_int(ctx, 0);
				CBrush brush = O;
				if (wx_try(ctx, [&] { *brush = Brush::CreateSolid(color); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Brush", brush);
				return 1;
			});
			/* Brush */ duk_add_method(ctx, "CreatePattern", 1, duk_fn {
				HBITMAP hBitmap = O;
				if (duk_get_class__p(ctx, "Bitmap", hBitmap))
					return DUK_RET_TYPE_ERROR;
				CBrush brush = O;
				if (wx_try(ctx, [&] { *brush = Brush::CreatePattern(hBitmap); }))
					return DUK_RET_REFERENCE_ERROR;
				duk_push_new_handle(ctx, "Brush", brush);
				return 1;
			});
			/* Brush */ duk_add_method(ctx, "CreateHatch", 2, duk_fn {
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
	duk_add_class(
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


	duk_add_enum_flags<MapModes>(ctx);
	duk_add_enum_flags<Stretches>(ctx);
	duk_add_enum_flags<PolyFills>(ctx);
	duk_add_enum_flags<TextAlign>(ctx);

	duk_add_class(
		ctx, "DevCap", O,
		duk_structure {
			/* void */ duk_add_method(ctx, "Delete", 0, duk_fn {
				if (auto pobj = duk_get_this__p<CDevCap>(ctx))
					if (wx_try(ctx, [&] { pobj->Delete(); }))
						return DUK_RET_REFERENCE_ERROR;
				duk_push_this(ctx);
				duk_del_prop_string(ctx, -1, "__p");
				return 0;
			});
			/* void */ duk_add_method(ctx, "DrawIcon", 2, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj) return DUK_RET_TYPE_ERROR;
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
			/* void */ duk_add_method(ctx, "DrawPixel", 2, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj) return DUK_RET_TYPE_ERROR;
				LPoint Pos;
				if (!duk_get_point(ctx, Pos, 0))
					return DUK_RET_TYPE_ERROR;
				auto color = duk_to_int(ctx, 1);
				if (wx_try(ctx, [&] { pobj->DrawPixel(color, Pos); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_add_method(ctx, "DrawPie", 4, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj) return DUK_RET_TYPE_ERROR;
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
			/* void */ duk_add_method(ctx, "DrawEllipse", 1, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj) return DUK_RET_TYPE_ERROR;
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&] { pobj->DrawEllipse(rc); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_add_method(ctx, "DrawFocus", 1, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj) return DUK_RET_TYPE_ERROR;
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&] { pobj->DrawFocus(rc); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_add_method(ctx, "Invert", 1, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj) return DUK_RET_TYPE_ERROR;
				LRect rc;
				if (!duk_get_rect(ctx, rc, 0))
					return DUK_RET_TYPE_ERROR;
				if (wx_try(ctx, [&] { pobj->DrawFocus(rc); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_add_method(ctx, "Fill", 2, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj) return DUK_RET_TYPE_ERROR;
				HBRUSH hBrush;
				if (duk_get_class__p(ctx, "Brush", hBrush, 0))
					return DUK_RET_TYPE_ERROR;
				LRect rc;
				if (wx_try(ctx, [&] {
					if (duk_get_rect(ctx, rc, 1))
						 pobj->Fill(hBrush, rc);
					else pobj->Fill(hBrush);
				}))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_add_method(ctx, "Select", 1, duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj) return DUK_RET_TYPE_ERROR;
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

			/* RGB */ duk_add_prop(ctx, "PenColor",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					auto color = duk_to_int(ctx, 0);
					if (wx_try(ctx, [&] { pobj->PenColor(color); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					COLORREF color = 0;
					if (wx_try(ctx, [&] { color = pobj->PenColor(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "RGB", color);
					return 1;
				}
			);
			/* RGB */ duk_add_prop(ctx, "BkColor",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					auto color = duk_to_int(ctx, 0);
					if (wx_try(ctx, [&] { pobj->BkColor(color); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					COLORREF color = 0;
					if (wx_try(ctx, [&] { color = pobj->BkColor(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "RGB", color);
					return 1;
				}
			);
			/* RGB */ duk_add_prop(ctx, "TextColor",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					auto color = duk_to_uint(ctx, 0);
					if (wx_try(ctx, [&] { pobj->TextColor(color); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					COLORREF color = 0;
					if (wx_try(ctx, [&] { color = pobj->TextColor(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "RGB", color);
					return 1;
				}
			);
			/* TextAlign */ duk_add_prop(ctx, "TextAligns",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					auto align = duk_to_uint(ctx, 0);
					if (wx_try(ctx, [&] { pobj->TextAligns(reuse_as<TextAlign>(align)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					auto align = reuse_as<TextAlign>(0);
					if (wx_try(ctx, [&] { align = pobj->TextAligns(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "TextAlign", align.yield());
					return 1;
				}
			);
			/* Point */ duk_add_prop(ctx, "ViewOrg",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					LPoint Pos;
					if (!duk_get_point(ctx, Pos))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->ViewOrg(Pos); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					LPoint Pos;
					if (wx_try(ctx, [&] { pobj->ViewOrg(Pos); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_point(ctx, Pos);
					return 1;
				}
			);
			/* Point */ duk_add_prop(ctx, "ViewExt",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					LPoint Ext;
					if (!duk_get_point(ctx, Ext))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->ViewExt(Ext); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					LPoint Ext;
					if (wx_try(ctx, [&] { pobj->ViewExt(Ext); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_point(ctx, Ext);
					return 1;
				}
			);
			/* Point */ duk_add_prop(ctx, "WindowOrg",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					LPoint Pos;
					if (!duk_get_point(ctx, Pos))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->WindowOrg(Pos); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					LPoint Pos;
					if (wx_try(ctx, [&] { pobj->WindowOrg(Pos); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_point(ctx, Pos);
					return 1;
				}
			);
			/* Point */ duk_add_prop(ctx, "WindowExt",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					LPoint Ext;
					if (!duk_get_point(ctx, Ext))
						return DUK_RET_TYPE_ERROR;
					if (wx_try(ctx, [&] { pobj->WindowExt(Ext); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					LPoint Ext;
					if (wx_try(ctx, [&] { pobj->WindowExt(Ext); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_point(ctx, Ext);
					return 1;
				}
			);
			/* MapModes */ duk_add_prop(ctx, "MapMode",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					auto mode = duk_to_int(ctx, 0);
					if (wx_try(ctx, [&] { pobj->MapMode(reuse_as<MapModes>(mode)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					auto mode = reuse_as<MapModes>(0);
					if (wx_try(ctx, [&] { mode = pobj->MapMode(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "MapModes", mode.yield());
					return 1;
				}
			);
			/* Stretches */ duk_add_prop(ctx, "StretchMode",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					auto mode = duk_to_int(ctx, 0);
					if (wx_try(ctx, [&] { pobj->StretchMode(reuse_as<Stretches>(mode)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					auto mode = reuse_as<Stretches>(0);
					if (wx_try(ctx, [&] { mode = pobj->StretchMode(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "Stretches", mode.yield());
					return 1;
				}
			);
			/* PolyFills */ duk_add_prop(ctx, "PolyFillMode",
				duk_set {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					auto mode = duk_to_int(ctx, 0);
					if (wx_try(ctx, [&] { pobj->PolyFill(reuse_as<PolyFills>(mode)); }))
						return DUK_RET_REFERENCE_ERROR;
					return 0;
				},
				duk_get {
					auto pobj = duk_get_this__p<CDevCap>(ctx);
					if (!pobj) return DUK_RET_TYPE_ERROR;
					auto mode = reuse_as<PolyFills>(0);
					if (wx_try(ctx, [&] { mode = pobj->PolyFill(); }))
						return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "PolyFills", mode.yield());
					return 1;
				}
			);
			/* Point */ duk_put_prop_r(ctx, "Size", duk_fn {
				auto pobj = duk_get_this__p<CDevCap>(ctx);
				if (!pobj) return DUK_RET_TYPE_ERROR;
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
					} elif (duk_is_object(ctx, 0)) {
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
