#include "wx_console.h"

//#define DUK_USE_DEBUG
#include "wx_duk.h"

#pragma region Duktape

const char *smpl_to_string(bool b) {
	return b ? "true" : "false";
}

const char *duk_this_prop_to_string(duk_context *ctx, const char *name) {
	duk_push_this(ctx);
	duk_get_prop_string(ctx, -1, name);
	return duk_to_string(ctx, -1);
}

void duk_member_int(duk_context *ctx, const char *name, duk_idx_t i) {
	duk_push_int(ctx, i);;
	duk_put_prop_string(ctx, -2, name);
}
void duk_member_str(duk_context *ctx, const char *name, const char *i) {
	duk_push_string(ctx, i);
	duk_put_prop_string(ctx, -2, name);
}
void duk_extends(duk_context *ctx, const char *child_name, const char *parent_name) {
	duk_get_global_string(ctx, child_name);
	duk_push_string(ctx, "prototype");
	duk_get_global_string(ctx, parent_name);
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
	if (finalizer)
		duk_push_c_function(ctx, finalizer, 1);
	else
		duk_push_null(ctx);
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

void duk_push_new_int_obj(duk_context *ctx, const char *name, duk_int_t i) {
	duk_get_global_string(ctx, name);
	duk_push_int(ctx, i);
	duk_call(ctx, 1);
}

void duk_class(duk_context *ctx,
			   const char *name, const char *extends,
			   duk_c_function cstr_struct, duk_c_function cstr_class,
			   duk_c_function cstr_static) {
	auto &&obj_name = sprintf("%sObj", name);
	duk_struct_global(ctx, obj_name, cstr_struct);
	duk_function_global(ctx, name, cstr_class);
	duk_extends(ctx, name, obj_name);
	if (cstr_static)
		cstr_static(ctx);
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
	duk_put_prop(ctx, -3);
	//duk_def_prop(ctx, -3,
	//			 DUK_DEFPROP_HAVE_VALUE |
	//			 DUK_DEFPROP_CLEAR_WRITABLE |	// writable : false
	//			 DUK_DEFPROP_CLEAR_CONFIGURABLE	// configurable : false
	//);
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
//bool duk_class_takeoff_handle(duk_context *ctx, const char *class_name, HANDLE &hd, duk_idx_t idx) {
//	if (duk_is_null(ctx, idx))
//		return false;
//	duk_get_global_string(ctx, class_name);
//	if (!duk_instanceof(ctx, idx, -1))
//		return true;
//	duk_get_prop_string(ctx, idx, "__p");
//	if (duk_get_type(ctx, -1) != DUK_TYPE_POINTER)
//		return true;
//	hd = (HANDLE)duk_get_pointer(ctx, -1);
//	duk_put_prop_string(ctx, idx, )
//	return false;
//}
void duk_new_handle(duk_context *ctx, const char *class_name, HANDLE hd) {
	if (!hd) {
		duk_push_null(ctx);
		return;
	}
	duk_get_global_string(ctx, class_name);
	duk_push_pointer(ctx, hd);
	duk_new(ctx, 1);
}
void duk_new_handle_proxy(duk_context *ctx, const char *class_name, HANDLE hd) {
	if (!hd) {
		duk_push_null(ctx);
		return;
	}
	duk_get_global_string(ctx, class_name);
	duk_push_pointer(ctx, hd);
	duk_new(ctx, 1);
	duk_finalizer(ctx, O);
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
