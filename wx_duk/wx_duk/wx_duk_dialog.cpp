#include "wx_dialog.h"

#include "wx_duk.h"

template<class AnyDlgStruct>
static void load_CommDlg(duk_context *ctx) {
	duk_put_prop_w(ctx, "Parent", duk_fn {
		auto pobj = duk_get_this__p<AnyDlgStruct>(ctx);
		if (!pobj) return DUK_RET_REFERENCE_ERROR;
		HANDLE hParent = O;
		if (!duk_get_class__p(ctx, "Window", hParent))
			return DUK_RET_TYPE_ERROR;
		pobj->Parent((HWND)hParent);
		return 0;
	});
	duk_put_prop_w(ctx, "Module", duk_fn {
		auto pobj = duk_get_this__p<AnyDlgStruct>(ctx);
		if (!pobj) return DUK_RET_REFERENCE_ERROR;
		HANDLE hModule = O;
		if (!duk_get_class__p(ctx, "Module", hModule))
			return DUK_RET_TYPE_ERROR;
		pobj->Module((HMODULE)hModule);
		return 0;
	});
	duk_put_prop_w(ctx, "Styles", duk_fn {
		auto pobj = duk_get_this__p<AnyDlgStruct>(ctx);
		if (!pobj) return DUK_RET_REFERENCE_ERROR;
		auto styles = duk_to_int(ctx, 0);
		pobj->Styles(reuse_as<typename AnyDlgStruct::Style>(styles));
		return 0;
	});
	duk_put_prop_w(ctx, "TemplateName", duk_fn {
		auto pobj = duk_get_this__p<AnyDlgStruct>(ctx);
		if (!pobj) return DUK_RET_REFERENCE_ERROR;
		auto lpszName = duk_to_string(ctx, 0);
		if (!lpszName)
			return 0;
		pobj->TemplateName(lpszName);
		return 0;
	});
}

static void load_ColorChoose(duk_context *ctx) {
	static const duk_constant __ColorChooseStyle_constant[]{
		{ "InitRGB", CC_RGBINIT },
		{ "FullOpen", CC_FULLOPEN },
		{ "PreventFullOpen", CC_PREVENTFULLOPEN },
		{ "ShowHelp", CC_SHOWHELP },
		{ "EnableHook", CC_ENABLEHOOK },
		{ "EnableTemplate", CC_ENABLETEMPLATE },
		{ "EnableTemplateHandle", CC_ENABLETEMPLATEHANDLE },
		{ "SolidColor", CC_SOLIDCOLOR },
		{ "AnyColor", CC_ANYCOLOR }
	};
	duk_add_flags(ctx, "ColorChooseStyle", O, __ColorChooseStyle_constant);
	duk_add_class(
		ctx, "ColorChoose", O,
		duk_structure {
			load_CommDlg<ColorChooseA>(ctx);
			duk_add_prop(ctx, "CustColors",
				duk_fn {
					auto pobj = duk_get_this__p<ColorChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					if (!duk_is_object(ctx, 0))
						return DUK_RET_TYPE_ERROR;
					duk_get_global_string(ctx, "Uint32Array");
					if (!duk_instanceof(ctx, 0, -1))
						return DUK_RET_TYPE_ERROR;
					auto len = duk_get_length(ctx, 0);
					if (len > 16) len = 16;
					duk_size_t size = 0;
					auto lpColors = pobj->CustColors();
					auto lpcColors = duk_get_buffer_data(ctx, 0, &size);
					memcpy_s((void *)lpColors, 16 * sizeof(COLORREF), lpcColors, len * sizeof(COLORREF));
					return 0;
				},
				duk_fn{
					duk_push_this(ctx);
					duk_get_prop_string(ctx, -1, "__CustColors");
					return 1;
				}
			);
			duk_put_prop_r(ctx, "Result", duk_fn {
				auto pobj = duk_get_this__p<ColorChooseA>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				duk_push_enum(ctx, "RGB", pobj->Result());
				return 1;
			});
			duk_add_method(ctx, "Choose", 0, duk_fn {
				auto pobj = duk_get_this__p<ColorChooseA>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				bool res = false;
				res = pobj->Choose();
				duk_push_boolean(ctx, res);
				return 1;
			});
			return 1;
		},
		duk_constructor {
			if (duk_reflect_constructor(ctx))
				return 1;
			ColorChooseA *pobj = O;
			switch (duk_get_top(ctx)) {
				case 0: {
					pobj = duk_put_cstruct<ColorChooseA>(ctx);
					break;
				}
				default:
					return DUK_RET_SYNTAX_ERROR;
			}
			duk_push_enum(ctx, "Uint32Array", 16);
			duk_size_t sz = 0;
			auto ptr = duk_get_buffer_data(ctx, -1, &sz);
			if (sz != 4 * 16)
				return DUK_RET_REFERENCE_ERROR;
			duk_put_prop_string(ctx, -2, "__CustColors");
			pobj->CustColors((ColorChooseA::ColorSet *)ptr);
			return 0;
		}
	);
}

static void load_FontChoose(duk_context *ctx) {
	static const duk_constant __FontChooseStyle_constant[]{
		{ "ScreenFonts", CF_SCREENFONTS },
		{ "PrinterFonts", CF_PRINTERFONTS },
		{ "ShowHelp", CF_SHOWHELP },
		{ "EnableHook", CF_ENABLEHOOK },
		{ "EnableTemplate", CF_ENABLETEMPLATE },
		{ "EnableTemplateHandle", CF_ENABLETEMPLATEHANDLE },
		{ "InitTologFontStruct", CF_INITTOLOGFONTSTRUCT },
		{ "UseStyle", CF_USESTYLE },
		{ "Effects", CF_EFFECTS },
		{ "Apply", CF_APPLY },
		{ "Ansionly", CF_ANSIONLY },
		{ "NoVectorFonts", CF_NOVECTORFONTS },
		{ "NoSimulations", CF_NOSIMULATIONS },
		{ "LimitSize", CF_LIMITSIZE },
		{ "FixedPitchOnly", CF_FIXEDPITCHONLY },
		{ "WYSIWYG", CF_WYSIWYG },
		{ "ForceFontExist", CF_FORCEFONTEXIST },
		{ "ScalableOnly", CF_SCALABLEONLY },
		{ "TTOnly", CF_TTONLY },
		{ "NoFaceSel", CF_NOFACESEL },
		{ "NoStyleSel", CF_NOSTYLESEL },
		{ "NoSizeSel", CF_NOSIZESEL },
		{ "SelectScript", CF_SELECTSCRIPT },
		{ "NoScriptSel", CF_NOSCRIPTSEL },
		{ "NoVertFonts", CF_NOVERTFONTS },
		{ "InActiveFonts", CF_INACTIVEFONTS }
	};
	duk_add_flags(ctx, "ColorChooseStyle", O, __FontChooseStyle_constant);
	duk_add_class(
		ctx, "FontChoose", O,
		duk_structure {
			load_CommDlg<FontChooseA>(ctx);
			duk_add_prop(ctx, "FontTypes",
				duk_fn {
					auto pobj = duk_get_this__p<FontChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					auto ft = reuse_as<FontType>(duk_to_uint16(ctx, 0));
					pobj->FontTypes(ft);
					return 0;
				},
				duk_fn {
					auto pobj = duk_get_this__p<FontChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "FontType", pobj->FontTypes().yield());
					return 1;
				}
			);
			duk_add_prop(ctx, "SizeMin",
				duk_fn {
					auto pobj = duk_get_this__p<FontChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					pobj->SizeMin(duk_to_int(ctx, 0));
					return 0;
				},
				duk_fn {
					auto pobj = duk_get_this__p<FontChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->SizeMin());
					return 1;
				}
			);
			duk_add_prop(ctx, "SizeMax",
				duk_fn {
					auto pobj = duk_get_this__p<FontChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					auto size = duk_to_int(ctx, 0);
					pobj->SizeMax(size);
					return 0;
				},
				duk_fn {
					auto pobj = duk_get_this__p<FontChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->SizeMax());
					return 1;
				}
			);
			duk_add_prop(ctx, "PointSize",
				duk_fn {
					auto pobj = duk_get_this__p<FontChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					auto size = duk_to_int(ctx, 0);
					pobj->PointSize(size);
					return 0;
				},
				duk_fn {
					auto pobj = duk_get_this__p<FontChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_int(ctx, pobj->PointSize());
					return 1;
				}
			);
			duk_add_prop(ctx, "Color",
				duk_fn {
					auto pobj = duk_get_this__p<FontChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					auto size = duk_to_uint32(ctx, 0);
					pobj->Color(size);
					return 0;
				},
				duk_fn {
					auto pobj = duk_get_this__p<FontChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_enum(ctx, "RGB", pobj->Color());
					return 1;
				}
			);
			duk_add_prop(ctx, "LogFont",
				duk_fn {
					auto pobj = duk_get_this__p<FontChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_get_global_string(ctx, "FontLogic");
					if (!duk_instanceof(ctx, 0, -1))
						return DUK_RET_TYPE_ERROR;
					duk_push_this(ctx);
					duk_get_prop_string(ctx, 0, "__p");
					duk_size_t size = 0;
					duk_get_buffer(ctx, -1, &size);
					if (size != sizeof(FontLogicA))
						return DUK_RET_TYPE_ERROR;
					duk_put_prop_string(ctx, -2, "__LogFont");
					return 0;
				},
				duk_fn {
					auto pobj = duk_get_this__p<FontChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_this(ctx);
					duk_get_prop_string(ctx, -1, "__LogFont");
					duk_get_global_string(ctx, "FontLogic");
					duk_dup(ctx, -2);
					duk_new(ctx, 1);
					return 1;
				}
			);
			duk_add_method(ctx, "Choose", 0, duk_fn {
				auto pobj = duk_get_this__p<FontChooseA>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				duk_push_boolean(ctx, pobj->Choose());
				return 1;
			});
			return 0;
		},
		duk_constructor {
			if (duk_reflect_constructor(ctx))
				return 1;
			FontChooseA *pobj = O;
			FontLogicA *lpLogFont = O;
			switch (duk_get_top(ctx)) {
				case 1: {
					duk_get_global_string(ctx, "FontLogic");
					if (!duk_instanceof(ctx, 0, -1))
						return DUK_RET_TYPE_ERROR;
					duk_push_this(ctx);
					duk_get_prop_string(ctx, 0, "__p");
					duk_size_t size = 0;
					lpLogFont = (FontLogicA *)duk_get_buffer(ctx, -1, &size);
					if (size != sizeof(FontLogicA))
						return DUK_RET_TYPE_ERROR;
					duk_put_prop_string(ctx, -2, "__LogFont");
				}
				case 0: {
					pobj = duk_put_cstruct<FontChooseA>(ctx);
					break;
				}
				default:
					return DUK_RET_SYNTAX_ERROR;
			}
			if (!lpLogFont) {
				lpLogFont = (FontLogicA *)duk_push_fixed_buffer(ctx, sizeof(FontLogicA));
				new(lpLogFont) FontLogicA;
				duk_put_prop_string(ctx, -2, "__LogFont");
			}
			pobj->LogFont(lpLogFont);
			return 0;
		}
	);
}

static void load_FileChoose(duk_context *ctx) {
	static const duk_constant __FileChooseStyle_constant[]{
		{ "ReadOnly", OFN_READONLY },
		{ "OverwritePrompt", OFN_OVERWRITEPROMPT },
		{ "HideReadOnly", OFN_HIDEREADONLY },
		{ "NoChangeDir", OFN_NOCHANGEDIR },
		{ "ShowHelp", OFN_SHOWHELP },
		{ "EnableHook", OFN_ENABLEHOOK },
		{ "EnableTemplate", OFN_ENABLETEMPLATE },
		{ "EnableTemplateHandle", OFN_ENABLETEMPLATEHANDLE },
		{ "NoValidate", OFN_NOVALIDATE },
		{ "AllowMultiSelect", OFN_ALLOWMULTISELECT },
		{ "ExtensionDifferent", OFN_EXTENSIONDIFFERENT },
		{ "PathMustExist", OFN_PATHMUSTEXIST },
		{ "FileMustExist", OFN_FILEMUSTEXIST },
		{ "CreatePrompt", OFN_CREATEPROMPT },
		{ "ShareAware", OFN_SHAREAWARE },
		{ "NoReadOnlyReturn", OFN_NOREADONLYRETURN },
		{ "NoTestFileCreate", OFN_NOTESTFILECREATE },
		{ "NoNetworkButton", OFN_NONETWORKBUTTON },
		{ "NoLongNames", OFN_NOLONGNAMES },
		{ "Explorer", OFN_EXPLORER },
		{ "NodeReferenceLinks", OFN_NODEREFERENCELINKS },
		{ "LongNames", OFN_LONGNAMES },
		{ "EnableIncludeNotify", OFN_ENABLEINCLUDENOTIFY },
		{ "EnableSizing", OFN_ENABLESIZING },
		{ "DontAddToRecent", OFN_DONTADDTORECENT },
		{ "ForcesHowHidden", OFN_FORCESHOWHIDDEN }
	};
	duk_add_flags(ctx, "ColorChooseStyle", O, __FileChooseStyle_constant);
	duk_add_class(
		ctx, "FileChoose", O,
		duk_structure {
			load_CommDlg<FileChooseA>(ctx);
			duk_put_prop_r(ctx, "FileOffset", duk_fn {
				auto pobj = duk_get_this__p<FileChooseA>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				duk_push_int(ctx, pobj->FileOffset());
				return 1;
			});
			duk_put_prop_r(ctx, "FileExtension", duk_fn {
				auto pobj = duk_get_this__p<FileChooseA>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				duk_push_int(ctx, pobj->FileExtension());
				return 1;
			});
			duk_add_prop(ctx, "File",
				duk_fn {
					auto pobj = duk_get_this__p<FileChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					auto lpszFile = duk_to_string(ctx, 0);
					auto len = duk_get_length(ctx, 0);
					duk_push_this(ctx);
					duk_get_prop_string(ctx, -1, "__File");
					duk_size_t size = 0;
					auto lpszFileBuffer = (LPSTR)duk_get_buffer(ctx, -1, &size);
					if (lpszFileBuffer) {
						if (len >= size) {
							lpszFileBuffer = (LPSTR)duk_resize_buffer(ctx, -1, len + 1);
							pobj->FileMaxLen((DWORD)len + 1);
						}
					} else {
						duk_pop(ctx);
						lpszFileBuffer = (LPSTR)duk_push_dynamic_buffer(ctx, MAX_PATH * 2);
						duk_put_prop_string(ctx, -2, "__File");
						pobj->FileMaxLen(MAX_PATH * 2);
					}
					pobj->File(lpszFileBuffer);
					memcpy_s(lpszFileBuffer, pobj->FileMaxLen(), lpszFile, len + 1);
					return 0;
				},
				duk_fn {
					auto pobj = duk_get_this__p<FileChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_string(ctx, pobj->File());
					return 1;
				}
			);
			duk_add_prop(ctx, "FileMaxLen",
				duk_fn {
					auto pobj = duk_get_this__p<FileChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					auto len = duk_to_uint32(ctx, 0);
					if (len == pobj->FileMaxLen())
						return 0;
					duk_push_this(ctx);
					duk_get_prop_string(ctx, -1, "__File");
					duk_size_t size = 0;
					auto lpszFileBuffer = (LPSTR)duk_get_buffer(ctx, -1, &size);
					if (lpszFileBuffer) {
						lpszFileBuffer = (LPSTR)duk_resize_buffer(ctx, -1, len);
						pobj->FileMaxLen((DWORD)len);
					} else {
						duk_pop(ctx);
						lpszFileBuffer = (LPSTR)duk_push_dynamic_buffer(ctx, MAX_PATH * 2);
						duk_put_prop_string(ctx, -2, "__File");
						pobj->FileMaxLen(MAX_PATH * 2);
					}
					pobj->File(lpszFileBuffer);
					return 0;
				},
				duk_fn {
					auto pobj = duk_get_this__p<FileChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_uint(ctx, pobj->FileMaxLen());
					return 1;
				}
			);
			duk_add_prop(ctx, "FileTitle",
				duk_fn {
					auto pobj = duk_get_this__p<FileChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					auto lpszFileTitle = duk_to_string(ctx, 0);
					auto len = duk_get_length(ctx, 0);
					duk_push_this(ctx);
					duk_get_prop_string(ctx, -1, "__FileTitle");
					duk_size_t size = 0;
					auto lpszFileTitleBuffer = (LPSTR)duk_get_buffer(ctx, -1, &size);
					if (lpszFileTitleBuffer) {
						if (len >= size) {
							lpszFileTitleBuffer = (LPSTR)duk_resize_buffer(ctx, -1, len + 1);
							pobj->FileTitleMaxLen((DWORD)len + 1);
						}
					} else {
						duk_pop(ctx);
						lpszFileTitleBuffer = (LPSTR)duk_push_dynamic_buffer(ctx, MAX_PATH);
						duk_put_prop_string(ctx, -2, "__FileTitle");
						pobj->FileTitleMaxLen(MAX_PATH);
					}
					pobj->FileTitle(lpszFileTitleBuffer);
					memcpy_s(lpszFileTitleBuffer, pobj->FileTitleMaxLen(), lpszFileTitle, len + 1);
					return 0;
				},
				duk_fn {
					auto pobj = duk_get_this__p<FileChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_string(ctx, pobj->FileTitle());
					return 1;
				}
			);
			duk_add_prop(ctx, "CustomFilter",
				duk_fn {
					auto pobj = duk_get_this__p<FileChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					auto lpszCustomFilter = duk_to_string(ctx, 0);
					auto len = duk_get_length(ctx, 0);
					duk_push_this(ctx);
					duk_get_prop_string(ctx, -1, "__CustomFilter");
					duk_size_t size = 0;
					auto lpszCustomFilterBuffer = (LPSTR)duk_get_buffer(ctx, -1, &size);
					if (lpszCustomFilterBuffer) {
						if (len >= size) {
							lpszCustomFilterBuffer = (LPSTR)duk_resize_buffer(ctx, -1, len + 1);
							pobj->CustomFilterMaxLen((DWORD)len + 1);
						}
					} else {
						duk_pop(ctx);
						lpszCustomFilterBuffer = (LPSTR)duk_push_dynamic_buffer(ctx, MAX_PATH);
						duk_put_prop_string(ctx, -2, "__CustomFilter");
						pobj->CustomFilterMaxLen(MAX_PATH);
					}
					pobj->CustomFilter(lpszCustomFilterBuffer);
					memcpy_s(lpszCustomFilterBuffer, pobj->CustomFilterMaxLen(), lpszCustomFilter, len + 1);
					return 0;
				},
				duk_fn {
					auto pobj = duk_get_this__p<FileChooseA>(ctx);
					if (!pobj) return DUK_RET_REFERENCE_ERROR;
					duk_push_string(ctx, pobj->CustomFilter());
					return 1;
				}
			);
			duk_put_prop_w(ctx, "Filter", duk_fn {
				auto pobj = duk_get_this__p<FileChooseA>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				auto lpszFilter = duk_to_string(ctx, 0);
				if (!lpszFilter)
					return 0;
				pobj->Filter(lpszFilter);
				return 0;
			});
			duk_put_prop_r(ctx, "FilterIndex", duk_fn {
				auto pobj = duk_get_this__p<FileChooseA>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				duk_push_int(ctx, pobj->FilterIndex());
				return 1;
			});
			duk_put_prop_w(ctx, "InitialDir", duk_fn {
				auto pobj = duk_get_this__p<FileChooseA>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				auto lpszInitialDir = duk_to_string(ctx, 0);
				if (!lpszInitialDir)
					return 0;
				pobj->InitialDir(lpszInitialDir);
				return 0;
			});
			duk_put_prop_w(ctx, "Title", duk_fn {
				auto pobj = duk_get_this__p<FileChooseA>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				auto lpszTitle = duk_to_string(ctx, 0);
				if (!lpszTitle)
					return 0;
				pobj->Title(lpszTitle);
				return 0;
			});
			duk_put_prop_w(ctx, "DefExt", duk_fn {
				auto pobj = duk_get_this__p<FileChooseA>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				auto lpszDefExt = duk_to_string(ctx, 0);
				if (!lpszDefExt)
					return 0;
				pobj->DefExt(lpszDefExt);
				return 0;
			});
			duk_add_method(ctx, "OpenFile", 0, duk_fn {
				auto pobj = duk_get_this__p<FileChooseA>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				bool res = false;
				res = pobj->OpenFile();
				duk_push_boolean(ctx, res);
				return 1;
			});
			duk_add_method(ctx, "SaveFile", 0, duk_fn {
				auto pobj = duk_get_this__p<FileChooseA>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				bool res = false;
				res = pobj->SaveFile();
				duk_push_boolean(ctx, res);
				return 1;
			});
			return 1;
		},
		duk_constructor {
			if (duk_reflect_constructor(ctx))
				return 1;
			FileChooseA *pobj = O;
			switch (duk_get_top(ctx)) {
				case 0: {
					pobj = duk_put_cstruct<FileChooseA>(ctx);
					break;
				}
				default:
					return DUK_RET_SYNTAX_ERROR;
			}
			/// File
			auto lpstrFile = (LPSTR)duk_push_dynamic_buffer(ctx, MAX_PATH * 2);
			duk_put_prop_string(ctx, -2, "__File");
			pobj->File(lpstrFile);
			pobj->FileMaxLen(MAX_PATH * 2);
			/// FileTitle
			auto lpszFileTitle = (LPSTR)duk_push_dynamic_buffer(ctx, MAX_PATH);
			duk_put_prop_string(ctx, -2, "__FileTitle");
			pobj->FileTitle(lpszFileTitle);
			pobj->FileMaxLen(MAX_PATH);
			return 0;
		}
	);
}

void load_duk_dialog(duk_context *ctx) {
	load_ColorChoose(ctx);
	load_FontChoose(ctx);
	load_FileChoose(ctx);
}

