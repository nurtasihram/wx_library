#pragma once

#include "duk_config.h"
#include "duktape.h"

#include "wx_type.h"

using namespace WX;

struct duk_exception {
	const char *msg;
};
struct duk_constant {
	const char *name;
	duk_size_t lenName = 0;
	duk_uint_t value;
};

#define duk_fn [](duk_context *ctx) -> duk_ret_t

const char *smpl_to_string(bool b);
const char *duk_this_prop_to_string(duk_context *ctx, const char *name);

void duk_add_object(duk_context *ctx, const char *name, duk_c_function constuctor);

/* Class */
static constexpr duk_uint_t DUK_DEFPROP_PUBLIC_CONST =
	DUK_DEFPROP_HAVE_VALUE |		// value
	DUK_DEFPROP_CLEAR_WRITABLE |	// unwritable
	DUK_DEFPROP_SET_ENUMERABLE |	// enumerable
	DUK_DEFPROP_CLEAR_CONFIGURABLE;	// unconfigurable
static constexpr duk_uint_t DUK_DEFPROP_PRIVATE_CONST =
	DUK_DEFPROP_HAVE_VALUE |		// value
	DUK_DEFPROP_CLEAR_WRITABLE |	// unwritable
	DUK_DEFPROP_CLEAR_ENUMERABLE |	// unenumerable
	DUK_DEFPROP_CLEAR_CONFIGURABLE;	// unconfigurable
void duk_int_prop(duk_context *ctx, const char *name, duk_int_t val);
void duk_add_prop(duk_context *ctx, const char *name, duk_c_function setter, duk_c_function getter);
void duk_add_prop_w(duk_context *ctx, const char *name, duk_c_function setter);
void duk_add_prop_r(duk_context *ctx, const char *name, duk_c_function getter);
void duk_add_const(duk_context *ctx, const duk_constant *c, uint32_t len);
void duk_add_method(duk_context *ctx, const char *name, duk_idx_t nargs, duk_c_function func);
void duk_put_destructor(duk_context *ctx, duk_c_function finalizer);
void duk_add_class(duk_context *ctx, const char *name, const char *extends,
				   duk_c_function cstr_struct,
				   duk_c_function cstr_class,
				   duk_c_function cstr_static = O);
bool duk_reflect_constructor(duk_context *ctx);
#define duk_structure duk_fn
#define duk_constructor duk_fn
#define duk_static  duk_fn
#define duk_set duk_fn
#define duk_get duk_fn

bool duk_get__p(duk_context *ctx, void *&ptr, duk_size_t size, duk_idx_t idx = -1);
void *duk_get_this__p(duk_context *ctx, duk_size_t size = 0);
template<class AnyHandle>
inline auto duk_get_this__p(duk_context *ctx) {
	if constexpr (IsRef<AnyHandle>)
		 return reuse_as<AnyHandle>(duk_get_this__p(ctx));
	else return reuse_as<AnyHandle *>(duk_get_this__p(ctx, sizeof(AnyHandle)));
}
void duk_put_this__p(duk_context *ctx, HANDLE hd);

inline auto duk_push_string(duk_context *ctx, const StringA &str) reflect_as(duk_push_lstring(ctx, str, str.Length()));

void *duk_put_cstruct(duk_context *ctx, duk_size_t size);
template<class AnyClass>
inline AnyClass *duk_put_cstruct(duk_context *ctx) reflect_as(new ((AnyClass *)duk_put_cstruct(ctx, sizeof(AnyClass))) AnyClass);

bool duk_get_class__p(duk_context *ctx, const char *class_name, void *&ptr, duk_size_t size, duk_idx_t idx);
template<class AnyHandle>
bool duk_get_class__p(duk_context *ctx, const char *class_name, AnyHandle &hd, duk_idx_t idx = 0) {
	if constexpr (IsRef<AnyHandle>)
		 return duk_get_class__p(ctx, class_name, ref_as<void *>(hd), 0, idx);
	else return duk_get_class__p(ctx, class_name, ref_as<void *>(hd), sizeof(AnyHandle), idx);
}

void duk_push_new_handle(duk_context *ctx, const char *class_name, HANDLE hd);
void duk_push_new_cclass(duk_context *ctx, const char *class_name, HANDLE hd);

/* Point & Rect */
bool duk_get_point(duk_context *ctx, WX::LPoint &point, duk_idx_t idx = -1);
void duk_push_point(duk_context *ctx, WX::LPoint point);
bool duk_get_rect(duk_context *ctx, WX::LRect &rect, duk_idx_t idx = -1);
void duk_push_rect(duk_context *ctx, const WX::LRect &rect);

/* Enums & Flags */
void duk_add_enum(duk_context *ctx,
				  const char *name, const char *parent_name,
				  const duk_constant *dcs, uint32_t len);
template<size_t len>
void duk_add_enum(duk_context *ctx,
				  const char *name, const char *parent_name,
				  const duk_constant(&dcs)[len])
{ duk_add_enum(ctx, name, parent_name, dcs, len); }
template<size_t len>
void duk_add_enum_flags(duk_context *ctx, const char *name, const duk_constant(&dcs)[len])
{ duk_add_enum(ctx, name, "FlagObj", dcs, len); }
template<size_t len>
void duk_add_enum_class(duk_context *ctx, const char *name, const duk_constant(&dcs)[len])
{ duk_add_enum(ctx, name, "EnumObj", dcs, len); }
void duk_push_enum(duk_context *ctx, const char *name, duk_int_t i);

template<size_t len>
struct duk_constants { duk_constant dcs[len]; };
template<class EnumClass, size_t...ind>
constexpr auto duk_constantof(std::index_sequence<ind...>) {
	constexpr auto map = EnumTableA<EnumClass>;
	constexpr auto val = EnumClass::__Vals;
	return duk_constants<EnumClass::Count>{ { { map[ind].key.lpsz, map[ind].key.len, (duk_uint_t)val[ind] }... }};
}
template<class EnumClass>
constexpr auto duk_constantof() reflect_as(duk_constantof<EnumClass>(std::make_index_sequence<EnumClass::Count>()));
template<class EnumClass>
void duk_add_enum_class(duk_context *ctx) {
	static const auto _constants = duk_constantof<EnumClass>();
	duk_add_enum_class(ctx, EnumClass::__NameA, _constants.dcs);
}
template<class EnumClass>
void duk_add_enum_flags(duk_context *ctx) {
	static const auto _constants = duk_constantof<EnumClass>();
	duk_add_enum_flags(ctx, EnumClass::__NameA, _constants.dcs);
}

/* Exception System */
void duk_errout(duk_context *ctx, const char *err_fmt, ...);
template<class AnyClosure>
bool wx_try(duk_context *ctx, const AnyClosure &closure) {
	try {
		closure();
	} catch (WX::Exception err) {
		duk_errout(ctx, err.toStringA());
		return true;
	}
	return false;
}

bool duk_load_library(duk_context *ctx, duk_safe_call_function func);

void load_duk_types(duk_context *ctx);
void load_duk_resource(duk_context *ctx);
void load_duk_gdi(duk_context *ctx);
void load_duk_window(duk_context *ctx);
void load_duk_dialog(duk_context *ctx);
void load_duk_control(duk_context *ctx);
void load_duk_console(duk_context *ctx);
void load_duk_realtime(duk_context *ctx);

duk_ret_t load_duk_windows(duk_context *ctx, void *);
