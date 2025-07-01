#pragma once

#include "duk_config.h"
#include "duktape.h"

#include "wx_type.h"

using namespace WX;

struct duk_exception {
	duk_errcode_t code;
	const char *MsgId;
};
struct duk_constant_struct {
	const char *name;
	duk_uint_t value;
};

const char *smpl_to_string(bool b);
const char *duk_this_prop_to_string(duk_context *ctx, const char *name);

void duk_member_int(duk_context *ctx, const char *name, duk_idx_t i);
void duk_member_str(duk_context *ctx, const char *name, const char *i);
void duk_extends(duk_context *ctx, const char *child_name, const char *parent_name);
bool duk_reflect_constructor(duk_context *ctx);

void duk_property(duk_context *ctx, const char *name, duk_c_function setter, duk_c_function getter);
void duk_property_w(duk_context *ctx, const char *name, duk_c_function setter);
void duk_property_r(duk_context *ctx, const char *name, duk_c_function getter);

void duk_finalizer(duk_context *ctx, duk_c_function finalizer);

void duk_function_global(duk_context *ctx, const char *name, duk_c_function constructor, duk_idx_t nargs = DUK_VARARGS);
void duk_struct_global(duk_context *ctx, const char *name, duk_c_function constuctor);
void duk_method(duk_context *ctx, const char *name, duk_idx_t nargs, duk_c_function func);

void duk_push_new_int_obj(duk_context *ctx, const char *name, duk_int_t i);

void duk_class(duk_context *ctx, const char *name, const char *extends, duk_c_function cstr_struct, duk_c_function cstr_class, duk_c_function cstr_static = O);

void duk_constant(duk_context *ctx, const char *name, duk_uint_t value);
void duk_constant(duk_context *ctx, const duk_constant_struct *c, uint32_t len);

void duk_enable_logout(bool bLogout);
void duk_logout(duk_context *ctx, const char *err_fmt, ...);

void duk_errout(duk_context *ctx, const char *err_fmt, ...);
void duk_errout(duk_context *ctx, const WX::Exception &err);

#if UNICODE
#define PNT_STR "%ls"
#else
#define PNT_STR "%s"
#endif
template<class AnyClosure>
bool wx_try(duk_context *ctx, const AnyClosure &closure) {
	try {
		closure();
	} catch (WX::Exception err) {
		duk_errout(ctx, err);
		return true;
	}
	return false;
}

bool duk_get_point(duk_context *ctx, WX::LPoint &point, duk_idx_t idx = -1);
void duk_push_point(duk_context *ctx, WX::LPoint point);

bool duk_get_rect(duk_context *ctx, WX::LRect &rect, duk_idx_t idx = -1);
void duk_push_rect(duk_context *ctx, const WX::LRect &rect);

HANDLE duk_member_handle(duk_context *ctx);
void duk_member_handle(duk_context *ctx, HANDLE hd);

void *duk_get_buffer(duk_context *ctx, duk_size_t size);
template<class AnyClass>
AnyClass *duk_get_buffer(duk_context *ctx) reflect_as((AnyClass *)duk_get_buffer(ctx, sizeof(AnyClass)));

bool duk_class_handle(duk_context *ctx, const char *class_name, HANDLE &hd, duk_idx_t idx = 0);
template<class AnyHandle>
bool duk_class_handle(duk_context *ctx, const char *class_name, AnyHandle &hd, duk_idx_t idx = 0) reflect_as((bool)duk_class_handle(ctx, class_name, (HANDLE &)hd, idx));

void duk_new_handle(duk_context *ctx, const char *class_name, HANDLE hd);
void duk_new_handle_proxy(duk_context *ctx, const char *class_name, HANDLE hd);

void duk_flags(duk_context *ctx,
			   const char *type,
			   const char *name, const char *parent_name,
			   const duk_constant_struct *dcs, uint32_t len);
template<size_t len>
void duk_flags(duk_context *ctx,
			   const char *name, const char *parent_name,
			   const duk_constant_struct (&dcs)[len])
{ duk_flags(ctx, "FlagsObj", name, parent_name, dcs, len); }
template<size_t len>
void duk_enums(duk_context *ctx,
			   const char *name, const char *parent_name,
			   const duk_constant_struct(&dcs)[len])
{ duk_flags(ctx, "EnumsObj", name, parent_name, dcs, len); }

template<class AnyClass, class AnyBlock>
inline bool duk_try_struct_method(duk_context *ctx, AnyBlock block) {
	auto pobj = duk_get_buffer<AnyClass>(ctx);
	try {
		block(pobj);
	} catch (Exception err) {
		duk_errout(ctx, err);
		return true;
	}
	return false;
}
#define duk_fn() [](duk_context *ctx) -> duk_ret_t


void load_duk_types(duk_context *ctx);
void load_duk_resource(duk_context *ctx);
void load_duk_dialog(duk_context *ctx);
void load_duk_window(duk_context *ctx);
void load_duk_console(duk_context *ctx);

duk_ret_t load_duk(duk_context *ctx);
