#pragma once

#include "duk_config.h"
#include "duktape.h"

#include "wx_type.h"

struct duk_exception {
	duk_errcode_t code;
	const char *MsgId;
};
struct duk_constant_struct {
	const char *name;
	duk_uint_t value;
};

#define duk_member_int(ctx, name, i) \
	duk_push_int(ctx, i); \
	duk_put_prop_string(ctx, -2, name) 
#define duk_member_str(ctx, name, i) \
	duk_push_string(ctx, i); \
	duk_put_prop_string(ctx, -2, name) 
#define duk_extends(ctx, child_name, parent_name) \
	duk_get_global_string(ctx, child_name); \
	duk_push_string(ctx, "prototype"); \
	duk_get_global_string(ctx, parent_name); \
	duk_put_prop(ctx, -3)
bool duk_reflect_constructor(duk_context *ctx);

void duk_property(duk_context *ctx, const char *name, duk_c_function setter, duk_c_function getter);
void duk_property_w(duk_context *ctx, const char *name, duk_c_function setter);
void duk_property_r(duk_context *ctx, const char *name, duk_c_function getter);

void duk_finalizer(duk_context *ctx, duk_c_function finalizer);

void duk_function_global(duk_context *ctx, const char *name, duk_c_function constructor, duk_idx_t nargs = DUK_VARARGS);
void duk_struct_global(duk_context *ctx, const char *name, duk_c_function constuctor);
void duk_method(duk_context *ctx, const char *name, duk_idx_t nargs, duk_c_function func);

void duk_constant(duk_context *ctx, const char *name, duk_uint_t value);
void duk_constant(duk_context *ctx, const duk_constant_struct *c, uint32_t len);

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
		duk_errout(ctx,
				   " - WX exception -\n"
				   "   File:      " PNT_STR "\n"
				   "   Function:  " PNT_STR "\n"
				   "   Sentence:  " PNT_STR "\n"
				   "   Line:      %d\n"
				   "   LastError: %d\n",
				   (LPCTSTR)err.File(),
				   (LPCTSTR)err.Function(),
				   (LPCTSTR)err.Sentence(),
				   err.Line(),
				   err.LastError());
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

bool duk_class_handle(duk_context *ctx, const char *class_name, HANDLE &hd, duk_idx_t idx = 0);
void duk_new_handle(duk_context *ctx, const char *class_name, HANDLE hd);

void *duk_get_buffer(duk_context *ctx, duk_size_t size);
template<class AnyClass>
AnyClass *duk_get_buffer(duk_context *ctx) reflect_as((AnyClass *)duk_get_buffer(ctx, sizeof(AnyClass)));

void duk_flags(duk_context *ctx,
			   const char *type,
			   const char *name, const char *parent_name,
			   const duk_constant_struct *dcs, uint32_t len);
template<size_t len>
void duk_flags(duk_context *ctx,
			   const char *type,
			   const char *name, const char *parent_name,
			   const duk_constant_struct (&dcs)[len]) {
	duk_flags(ctx, type, name, parent_name, dcs, len);
}

void load_duk_types(duk_context *ctx);
void load_duk_resource(duk_context *ctx);
void load_duk_dialog(duk_context *ctx);
void load_duk_window(duk_context *ctx);
void load_duk_console(duk_context *ctx);

duk_ret_t load_duk(duk_context *ctx);
