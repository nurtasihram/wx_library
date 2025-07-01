#include "wx_dialog.h"

#include "wx_duk.h"

template<class AnyDlgStruct>
static void load_CommDlg(duk_context *ctx) {
	duk_property_w(ctx, "Parent", duk_fn() {
		HANDLE hParent = O;
		if (duk_class_handle(ctx, "Window", hParent))
			return DUK_RET_TYPE_ERROR;
		auto pobj = duk_get_buffer<AnyDlgStruct>(ctx);
		if (!pobj)
			return DUK_RET_INTERNAL_ERROR;
		pobj->Parent((HWND)hParent);
		return 0;
	});
	duk_property_w(ctx, "Module", duk_fn() {
		HANDLE hModule = O;
		if (duk_class_handle(ctx, "Module", hModule))
			return DUK_RET_TYPE_ERROR;
		auto pobj = duk_get_buffer<AnyDlgStruct>(ctx);
		if (!pobj)
			return DUK_RET_INTERNAL_ERROR;
		pobj->Module((HMODULE)hModule);
		return 0;
	});
	duk_property_w(ctx, "Styles", duk_fn() {
		auto styles = duk_to_int(ctx, 0);
		auto pobj = duk_get_buffer<AnyDlgStruct>(ctx);
		if (!pobj)
			return DUK_RET_INTERNAL_ERROR;
		pobj->Styles(reuse_as<typename AnyDlgStruct::Style>(styles));
		return 0;
	});
	duk_property_w(ctx, "TemplateName", duk_fn() {
		auto lpszName = duk_to_string(ctx, 0);
		if (!lpszName)
			return 0;
		auto pobj = duk_get_buffer<AnyDlgStruct>(ctx);
		if (!pobj)
			return DUK_RET_INTERNAL_ERROR;
		pobj->TemplateName(lpszName);
		return 0;
	});
}

static void load_ChooserColor(duk_context *ctx) {
	static const duk_constant_struct __ChooserColorStyle_constant[]{
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
	duk_flags(ctx, "ChooserColorStyle", O, __ChooserColorStyle_constant);
	duk_class(ctx, "ChooserColor", O,
		duk_fn() {
			load_CommDlg<ChooserColorA>(ctx);
			duk_property_r(ctx, "Result", duk_fn() {
				RGBColor color = 0xff0000;
				auto pobj = duk_get_buffer<ChooserColorA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				color = pobj->Result();
				duk_push_int(ctx, color);
				return 1;
			});
			duk_method(ctx, "Choose", 0, duk_fn() {
				bool res = false;
				auto pobj = duk_get_buffer<ChooserColorA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				res = pobj->Choose();
				duk_push_boolean(ctx, res);
				return 1;
			});
			return 1;
		},
		duk_fn() {
			if (duk_reflect_constructor(ctx))
				return 1;
			ChooserColorA *pobj = O;
			switch (duk_get_top(ctx)) {
				case 0: {
					duk_push_this(ctx);
					pobj = (ChooserColorA *)duk_push_buffer(ctx, sizeof(ChooserColorA), 0);
					new(pobj) ChooserColorA();
					duk_put_prop_string(ctx, -2, "__p");
					break;
				}
				default:
					return DUK_RET_SYNTAX_ERROR;
			}
			duk_push_this(ctx);
			duk_get_global_string(ctx, "Uint32Array");
			duk_push_int(ctx, 16);
			duk_new(ctx, 1);
			duk_size_t sz = 0;
			auto ptr = duk_get_buffer_data(ctx, -1, &sz);
			if (sz != 4 * 16)
				return DUK_RET_INTERNAL_ERROR;
			duk_put_prop_string(ctx, -2, "CustColors");
			pobj->CustColors((ChooserColorA::ColorSet *)ptr);
			return 0;
		}
	);
}

static void load_ChooserFont(duk_context *ctx) {
	static const duk_constant_struct __ChooserFontStyle_constant[]{
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
	duk_flags(ctx, "ChooserColorStyle", O, __ChooserFontStyle_constant);
	duk_class(ctx, "ChooserFont", O,
		duk_fn() {
			load_CommDlg<ChooserFontA>(ctx);
			duk_property_r(ctx, "LogFont", duk_fn() {
				auto pobj = duk_get_buffer<ChooserFontA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				duk_get_global_string(ctx, "FontLogic");
				duk_push_buffer(ctx, sizeof(LOGFONT), 0);
				duk_push_pointer(ctx, &pobj->LogFont());
				duk_new(ctx, 1);
				return 1;
			});
		},
		duk_fn() {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0: {
					duk_push_this(ctx);
					auto pobj = (ChooserFontA *)duk_push_buffer(ctx, sizeof(ChooserFontA), 0);
					new(pobj) ChooserFontA();
					duk_put_prop_string(ctx, -2, "__p");
					return 0;
				}
				case 1: {
					if (duk_is_pointer(ctx, 0)) {
						duk_push_this(ctx);
						auto pobj = (ChooserFontA *)duk_get_pointer(ctx, 0);

					}
				}
			}
			return 0;
		}
	);
}

static void load_ChooserFile(duk_context *ctx) {
	static const duk_constant_struct __ChooserFileStyle_constant[]{
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
	duk_flags(ctx, "ChooserColorStyle", O, __ChooserFileStyle_constant);
	duk_class(ctx, "ChooserFile", O,
		duk_fn() {
			load_CommDlg<ChooserFileA>(ctx);
			duk_property_r(ctx, "FileOffset", duk_fn() {
				auto pobj = duk_get_buffer<ChooserFileA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				duk_push_int(ctx, pobj->FileOffset());
				return 1;
			});
			duk_property_r(ctx, "FileExtension", duk_fn() {
				auto pobj = duk_get_buffer<ChooserFileA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				duk_push_int(ctx, pobj->FileExtension());
				return 1;
			});
			duk_property(ctx, "File", 
				duk_fn() {
					auto pobj = duk_get_buffer<ChooserFileA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					auto lpszFile = duk_to_string(ctx, 0);
					auto len = duk_get_length(ctx, 0);
					if (len >= pobj->FileMaxLen())
						return DUK_RET_RANGE_ERROR;
					pobj->File(CString(lpszFile, MaxLenPath));
					return 0;
				},
				duk_fn() {
					auto pobj = duk_get_buffer<ChooserFileA>(ctx);
					if (!pobj)
						return DUK_RET_INTERNAL_ERROR;
					duk_push_string(ctx, pobj->File());
					return 1;
				}
			);
			duk_property_r(ctx, "FileTitle", duk_fn() {
				auto pobj = duk_get_buffer<ChooserFileA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				auto lpszFileTitle = pobj->FileTitle();
				duk_push_string(ctx, lpszFileTitle);
				return 1;
			});
			duk_property_r(ctx, "CustomFilter", duk_fn() {
				auto pobj = duk_get_buffer<ChooserFileA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				auto lpszCustomFilter = pobj->CustomFilter();
				duk_push_string(ctx, lpszCustomFilter);
				return 1;
			});
			duk_property_w(ctx, "Filter", duk_fn() {
				auto pobj = duk_get_buffer<ChooserFileA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				auto lpszFilter = duk_to_string(ctx, 0);
				if (!lpszFilter)
					return 0;
				pobj->Filter(lpszFilter);
				return 0;
			});
			duk_property_r(ctx, "FilterIndex", duk_fn() {
				auto pobj = duk_get_buffer<ChooserFileA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				duk_push_int(ctx, pobj->FilterIndex());
				return 1;
			});
			duk_property_w(ctx, "InitialDir", duk_fn() {
				auto pobj = duk_get_buffer<ChooserFileA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				auto lpszInitialDir = duk_to_string(ctx, 0);
				if (!lpszInitialDir)
					return 0;
				pobj->InitialDir(lpszInitialDir);
				return 0;
			});
			duk_property_w(ctx, "Title", duk_fn() {
				auto pobj = duk_get_buffer<ChooserFileA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				auto lpszTitle = duk_to_string(ctx, 0);
				if (!lpszTitle)
					return 0;
				pobj->Title(lpszTitle);
				return 0;
			});
			duk_property_w(ctx, "DefExt", duk_fn() {
				auto pobj = duk_get_buffer<ChooserFileA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				auto lpszDefExt = duk_to_string(ctx, 0);
				if (!lpszDefExt)
					return 0;
				pobj->DefExt(lpszDefExt);
				return 0;
			});
			duk_method(ctx, "OpenFile", 0, duk_fn() {
				auto pobj = duk_get_buffer<ChooserFileA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				bool res = false;
				res = pobj->OpenFile();
				duk_push_boolean(ctx, res);
				return 1;
			});
			duk_method(ctx, "SaveFile", 0, duk_fn() {
				auto pobj = duk_get_buffer<ChooserFileA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				bool res = false;
				res = pobj->SaveFile();
				duk_push_boolean(ctx, res);
				return 1;
			});
			return 1;
		},
		duk_fn() {
			if (duk_reflect_constructor(ctx))
				return 1;
			ChooserFileA *pobj = O;
			switch (duk_get_top(ctx)) {
				case 0: {
					duk_push_this(ctx);
					pobj = (ChooserFileA *)duk_push_buffer(ctx, sizeof(ChooserFileA), 0);
					new(pobj) ChooserFileA();
					duk_put_prop_string(ctx, -2, "__p");
					return 0;
				}
			}
			duk_push_this(ctx);
			duk_push_dynamic_buffer(ctx, 1024);
			auto lpstrFile = (LPSTR)duk_get_buffer(ctx, -1);
			duk_put_prop_string(ctx, -2, "__File");
			pobj->File(lpstrFile);
			pobj->FileMaxLen(1024);
			return 0;
		}
	);
}

void load_duk_dialog(duk_context *ctx) {
	load_ChooserColor(ctx);
	load_ChooserFile(ctx);
}

