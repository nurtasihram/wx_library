#include "wx_console.h"

//#define DUK_USE_DEBUG
#include "wx_duk.h"

using namespace WX;

#pragma region Duktape
void duk_property(duk_context *ctx, const char *name, duk_c_function setter, duk_c_function getter) {
	duk_push_string(ctx, name);
	duk_push_c_function(ctx, getter, 0);
	duk_push_c_function(ctx, setter, 1);
	duk_def_prop(ctx, -4,
					/* getter */ DUK_DEFPROP_HAVE_GETTER |
					/* setter */ DUK_DEFPROP_HAVE_SETTER |
					/* configurable : false */	DUK_DEFPROP_CLEAR_CONFIGURABLE
	);
}
void duk_property_w(duk_context *ctx, const char *name, duk_c_function setter) {
	duk_push_string(ctx, name);
	duk_push_c_function(ctx, setter, 1);
	duk_def_prop(ctx, -3,
					/* setter */ DUK_DEFPROP_HAVE_SETTER |
					/* configurable : false */ DUK_DEFPROP_CLEAR_CONFIGURABLE
	);
}
void duk_property_r(duk_context *ctx, const char *name, duk_c_function getter) {
	duk_push_string(ctx, name);
	duk_push_c_function(ctx, getter, 0);
	duk_def_prop(ctx, -3,
					/* getter */ DUK_DEFPROP_HAVE_GETTER |
					/* configurable : false */ DUK_DEFPROP_CLEAR_CONFIGURABLE
	);
}

void duk_finalizer(duk_context *ctx, duk_c_function finalizer) {
	duk_push_c_function(ctx, finalizer, 1);
	duk_set_finalizer(ctx, -2);
}

void duk_constant(duk_context *ctx, const char *name, duk_uint_t value) {
	duk_push_string(ctx, name);
	duk_push_uint(ctx, value);
	duk_def_prop(ctx, -3,
					/* value */				DUK_DEFPROP_HAVE_VALUE |
					/* enumerable : true */	DUK_DEFPROP_SET_ENUMERABLE |
					/* configurable : false */	DUK_DEFPROP_CLEAR_CONFIGURABLE
	);
}
void duk_constant(duk_context *ctx, const duk_constant_struct *c, uint32_t len) {
	for (; len--; ++c)
		duk_constant(ctx, c->name, c->value);
}

void duk_function_global(duk_context *ctx, const char *name, duk_c_function constructor, duk_idx_t nargs) {
	duk_push_c_function(ctx, constructor, nargs);
	duk_put_global_string(ctx, name);
}
void duk_struct_global(duk_context *ctx, const char *name, duk_c_function constuctor) {
	duk_push_object(ctx);
	constuctor(ctx);
	duk_put_global_string(ctx, name);
}
void duk_method(duk_context *ctx, const char *name, duk_idx_t nargs, duk_c_function func) {
	duk_push_string(ctx, name);
	duk_push_c_function(ctx, func, nargs);
	duk_put_prop(ctx, -3);
}

bool duk_reflect_constructor(duk_context *ctx) {
	auto nargs = duk_get_top(ctx);
	if (duk_is_constructor_call(ctx))
		return false;
	duk_push_current_function(ctx);
	duk_insert(ctx, 0);
	duk_new(ctx, nargs);
	return true;
}

HANDLE duk_member_handle(duk_context *ctx) {
	duk_push_this(ctx);
	duk_get_prop_string(ctx, -1, "__p");
	if (duk_get_type(ctx, -1) != DUK_TYPE_POINTER)
		return O; // pointer lost
	return (HANDLE)duk_get_pointer(ctx, -1);
}
void duk_member_handle(duk_context *ctx, HANDLE hd) {
	duk_push_this(ctx);
	duk_push_string(ctx, "__p");
	duk_push_pointer(ctx, hd);
	duk_def_prop(ctx, -3,
				 DUK_DEFPROP_HAVE_VALUE
				 | DUK_DEFPROP_HAVE_WRITABLE | 0		// writable : false
				 | DUK_DEFPROP_HAVE_CONFIGURABLE | 0	// configurable : false
	);
}

bool duk_class_handle(duk_context *ctx, const char *class_name, HANDLE &hd, duk_idx_t idx) {
	if (duk_is_null(ctx, idx))
		return false;
	duk_get_global_string(ctx, class_name);
	if (!duk_instanceof(ctx, idx, -1))
		return true;
	duk_get_prop_string(ctx, idx, "__p");
	if (duk_get_type(ctx, -1) != DUK_TYPE_POINTER)
		return true;
	hd = (HANDLE)duk_get_pointer(ctx, -1);
	return false;
}
void duk_new_handle(duk_context *ctx, const char *class_name, HANDLE hd) {
	if (!hd) {
		duk_push_null(ctx);
		return;
	}
	duk_get_global_string(ctx, class_name);
	duk_push_pointer(ctx, hd);
	duk_new(ctx, 1);
}

void *duk_get_buffer(duk_context *ctx, duk_size_t size) {
	duk_push_this(ctx);
	duk_get_prop_string(ctx, -1, "__p");
	duk_size_t read_size = 0;
	auto pobj = duk_get_buffer(ctx, -1, &read_size);
	if (size != read_size) {
		duk_errout(ctx, "Buffer invalid\n");
		return O;
	}
	return pobj;
}
#pragma endregion

duk_ret_t load_duk(duk_context *ctx) {
	load_duk_types(ctx);
	load_duk_resource(ctx);
	load_duk_dialog(ctx);
	load_duk_window(ctx);
	load_duk_console(ctx);
	return 0;
}
