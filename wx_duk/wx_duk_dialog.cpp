#include "wx_dialog.h"

#include "wx_duk.h"

const char *duk_tmpl_string(duk_context *ctx, const char *name, const char *val) {
	duk_push_this(ctx);
	duk_push_string(ctx, val);
	duk_put_prop_string(ctx, -2, name);
	duk_get_prop_string(ctx, -1, name);
	return duk_get_string(ctx, -1);
}

template<class AnyClass, class AnyBlock >
inline bool _try_method(duk_context *ctx, AnyBlock block) {
	auto pobj = duk_get_buffer<AnyClass>(ctx);
	try {
		block(pobj);
	} catch (Exception err) {
		duk_errout(ctx, err);
		return true;
	}
	return false;
}

template<class AnyClass>
inline duk_c_function _dialog_constructor() {
	return [](duk_context *ctx) -> duk_ret_t {
		if (duk_reflect_constructor(ctx))
			return 1;
		duk_push_this(ctx);
		auto pobj = (AnyClass *)duk_push_buffer(ctx, sizeof(AnyClass), 0);
		new(pobj) AnyClass();
		duk_put_prop_string(ctx, -2, "__p");
		return 0;
	};
}

void load_duk_dialog(duk_context *ctx) {

#pragma region ChooserColorA
	duk_struct_global(ctx, "ChooserColorObj", [](duk_context *ctx) -> duk_ret_t {
		duk_property_w(ctx, "Parent", [](duk_context *ctx) -> duk_ret_t {
			HANDLE hParent = O;
			if (duk_class_handle(ctx, "Window", hParent))
				return DUK_RET_TYPE_ERROR;
			auto pobj = duk_get_buffer<ChooserColorA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			pobj->Parent((HWND)hParent);
			return 0;
		});
		duk_property_w(ctx, "Module", [](duk_context *ctx) -> duk_ret_t {
			HANDLE hModule = O;
			if (duk_class_handle(ctx, "Module", hModule))
				return DUK_RET_TYPE_ERROR;
			auto pobj = duk_get_buffer<ChooserColorA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			pobj->Module((HMODULE)hModule);
			return 0;
		});
		duk_property_w(ctx, "Styles", [](duk_context *ctx) -> duk_ret_t {
			auto styles = duk_to_int(ctx, 0);
			auto pobj = duk_get_buffer<ChooserColorA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			pobj->Styles(reuse_as<ChooserColorStyle>(styles));
			return 0;
		});
		duk_property_w(ctx, "TemplateName", [](duk_context *ctx) -> duk_ret_t {
			auto lpszName = duk_to_string(ctx, 0);
			if (!lpszName)
				return 0;
			lpszName = duk_tmpl_string(ctx, "__tn", lpszName);
			auto pobj = duk_get_buffer<ChooserColorA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			pobj->TemplateName(lpszName);
			return 0;
		});
		duk_property_r(ctx, "Result", [](duk_context *ctx) -> duk_ret_t {
			RGBColor color = 0xff0000;
			auto pobj = duk_get_buffer<ChooserColorA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			color = pobj->Result();
			duk_push_int(ctx, color);
			return 1;
		});
		duk_method(ctx, "Choose", 0, [](duk_context *ctx) -> duk_ret_t {
			bool res = false;
			auto pobj = duk_get_buffer<ChooserColorA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			res = pobj->Choose();
			duk_push_boolean(ctx, res);
			return 1;
		});
		return 1;
	});
	duk_function_global(ctx, "ChooserColor", _dialog_constructor<ChooserColorA>());
	duk_extends(ctx, "ChooserColor", "ChooserColorObj");
#pragma endregion

#pragma region ChooserFile
	duk_struct_global(ctx, "ChooserFileObj", [](duk_context *ctx) -> duk_ret_t {
		duk_property_w(ctx, "Parent", [](duk_context *ctx) -> duk_ret_t {
			HANDLE hParent = O;
			if (duk_class_handle(ctx, "Window", hParent))
				return DUK_RET_TYPE_ERROR;
			auto pobj = duk_get_buffer<ChooserFileA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			pobj->Parent((HWND)hParent);
			return 0;
		});
		duk_property_w(ctx, "Module", [](duk_context *ctx) -> duk_ret_t {
			HANDLE hModule = O;
			if (duk_class_handle(ctx, "Module", hModule))
				return DUK_RET_TYPE_ERROR;
			auto pobj = duk_get_buffer<ChooserFileA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			pobj->Module((HMODULE)hModule);
			return 0;
		});
		duk_property_w(ctx, "Styles", [](duk_context *ctx) -> duk_ret_t {
			auto styles = duk_to_int(ctx, 0);
			auto pobj = duk_get_buffer<ChooserFileA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			pobj->Styles(reuse_as<ChooserFileStyle>(styles));
			return 0;
		});
		duk_property_w(ctx, "TemplateName", [](duk_context *ctx) -> duk_ret_t {
			auto lpszName = duk_to_string(ctx, 0);
			if (!lpszName)
				return 0;
			lpszName = duk_tmpl_string(ctx, "__tn", lpszName);
			auto pobj = duk_get_buffer<ChooserFileA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			pobj->TemplateName(lpszName);
			return 0;
		});
		duk_property_r(ctx, "FileOffset", [](duk_context *ctx) -> duk_ret_t {
			auto pobj = duk_get_buffer<ChooserFileA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			duk_push_int(ctx, pobj->FileOffset());
			return 1;
		});
		duk_property_r(ctx, "FileExtension", [](duk_context *ctx) -> duk_ret_t {
			auto pobj = duk_get_buffer<ChooserFileA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			duk_push_int(ctx, pobj->FileExtension());
			return 1;
		});
		duk_property(ctx, "File", 
			[](duk_context *ctx) -> duk_ret_t {
				auto lpszFile = duk_to_string(ctx, 0);
				auto pobj = duk_get_buffer<ChooserFileA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				pobj->File(CString(lpszFile, MaxLenPath));
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				auto pobj = duk_get_buffer<ChooserFileA>(ctx);
				if (!pobj)
					return DUK_RET_INTERNAL_ERROR;
				duk_push_string(ctx, pobj->File());
				return 1;
			}
		);
		duk_property_r(ctx, "FileTitle", [](duk_context *ctx) -> duk_ret_t {
			auto pobj = duk_get_buffer<ChooserFileA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			auto lpszFileTitle = pobj->FileTitle();
			duk_push_string(ctx, lpszFileTitle);
			return 1;
		});
		duk_property_r(ctx, "CustomFilter", [](duk_context *ctx) -> duk_ret_t {
			auto pobj = duk_get_buffer<ChooserFileA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			auto lpszCustomFilter = pobj->CustomFilter();
			duk_push_string(ctx, lpszCustomFilter);
			return 1;
		});
		duk_property_w(ctx, "Filter", [](duk_context *ctx) -> duk_ret_t {
			auto lpszFilter = duk_to_string(ctx, 0);
			if (!lpszFilter)
				return 0;
			auto pobj = duk_get_buffer<ChooserFileA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			lpszFilter = duk_tmpl_string(ctx, "__filter", lpszFilter);
			pobj->Filter(lpszFilter);
			return 0;
		});
		duk_property_r(ctx, "FilterIndex", [](duk_context *ctx) -> duk_ret_t {
			auto pobj = duk_get_buffer<ChooserFileA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			duk_push_int(ctx, pobj->FilterIndex());
			return 1;
		});
		duk_property_w(ctx, "InitialDir", [](duk_context *ctx) -> duk_ret_t {
			auto lpszInitialDir = duk_to_string(ctx, 0);
			if (!lpszInitialDir)
				return 0;
			auto pobj = duk_get_buffer<ChooserFileA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			lpszInitialDir = duk_tmpl_string(ctx, "__idir", lpszInitialDir);
			pobj->InitialDir(lpszInitialDir);
			return 0;
		});
		duk_property_w(ctx, "Title", [](duk_context *ctx) -> duk_ret_t {
			auto lpszTitle = duk_to_string(ctx, 0);
			if (!lpszTitle)
				return 0;
			lpszTitle = duk_tmpl_string(ctx, "__title", lpszTitle);
			auto pobj = duk_get_buffer<ChooserFileA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			pobj->Title(lpszTitle);
			return 0;
		});
		duk_property_w(ctx, "DefExt", [](duk_context *ctx) -> duk_ret_t {
			auto lpszDefExt = duk_to_string(ctx, 0);
			if (!lpszDefExt)
				return 0;
			lpszDefExt = duk_tmpl_string(ctx, "__de", lpszDefExt);
			auto pobj = duk_get_buffer<ChooserFileA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			pobj->DefExt(lpszDefExt);
			return 0;
		});
		duk_method(ctx, "OpenFile", 0, [](duk_context *ctx) -> duk_ret_t {
			bool res = false;
			auto pobj = duk_get_buffer<ChooserFileA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			res = pobj->OpenFile();
			duk_push_boolean(ctx, res);
			return 1;
		});
		duk_method(ctx, "SaveFile", 0, [](duk_context *ctx) -> duk_ret_t {
			bool res = false;
			auto pobj = duk_get_buffer<ChooserFileA>(ctx);
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			res = pobj->SaveFile();
			duk_push_boolean(ctx, res);
			return 1;
		});
		return 1;
	});
	duk_function_global(ctx, "ChooserFile", _dialog_constructor<ChooserFileA>());
	duk_extends(ctx, "ChooserFile", "ChooserFileObj");
#pragma endregion

}

