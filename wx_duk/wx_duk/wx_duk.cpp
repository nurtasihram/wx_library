#include "wx_console.h"

//#define DUK_USE_DEBUG
#include "wx_duk.h"

const char *smpl_to_string(bool b) {
	return b ? "true" : "false";
}

const char *duk_this_prop_to_string(duk_context *ctx, const char *name) {
	duk_push_this(ctx);
	duk_get_prop_string(ctx, -1, name);
	return duk_to_string(ctx, -1);
}

void duk_add_object(duk_context *ctx, const char *name, duk_c_function constuctor) {
	duk_push_string(ctx, name);
	duk_push_object(ctx);
	constuctor(ctx);
	duk_def_prop(ctx, -3, DUK_DEFPROP_PUBLIC_CONST);
}

void duk_int_prop(duk_context *ctx, const char *name, duk_int_t val) {
	duk_push_int(ctx, val);
	duk_put_prop_string(ctx, -2, name);
}
void duk_add_prop(duk_context *ctx, const char *name, duk_c_function setter, duk_c_function getter) {
	duk_push_string(ctx, name);
	duk_push_c_function(ctx, getter, 0);
	duk_push_c_function(ctx, setter, 1);
	duk_def_prop(ctx, -4,
				 DUK_DEFPROP_HAVE_GETTER |		// getter
				 DUK_DEFPROP_HAVE_SETTER |		// setter
				 DUK_DEFPROP_CLEAR_CONFIGURABLE	// unconfigurable 
	);
}
void duk_add_prop_w(duk_context *ctx, const char *name, duk_c_function setter) {
	duk_push_string(ctx, name);
	duk_push_c_function(ctx, setter, 1);
	duk_def_prop(ctx, -3,
				 DUK_DEFPROP_HAVE_SETTER |		// setter
				 DUK_DEFPROP_CLEAR_CONFIGURABLE	// unconfigurable
	);
}
void duk_add_prop_r(duk_context *ctx, const char *name, duk_c_function getter) {
	duk_push_string(ctx, name);
	duk_push_c_function(ctx, getter, 0);
	duk_def_prop(ctx, -3,
				 DUK_DEFPROP_HAVE_GETTER |		// getter
				 DUK_DEFPROP_CLEAR_CONFIGURABLE	// unconfigurable
	);
}
void duk_add_const(duk_context *ctx, const duk_constant *c, uint32_t len) {
	for (; len--; ++c) {
		duk_push_lstring(ctx, c->name, c->lenName);
		duk_push_uint(ctx, c->value);
		duk_def_prop(ctx, -3, DUK_DEFPROP_PUBLIC_CONST);
	}
}
void duk_add_method(duk_context *ctx, const char *name, duk_idx_t nargs, duk_c_function func) {
	duk_push_string(ctx, name);
	duk_push_c_function(ctx, func, nargs);
	duk_push_string(ctx, "name");
	duk_push_string(ctx, name);
	duk_def_prop(ctx, -3, DUK_DEFPROP_PUBLIC_CONST);
	duk_def_prop(ctx, -3, DUK_DEFPROP_PUBLIC_CONST);
}
void duk_put_destructor(duk_context *ctx, duk_c_function finalizer) {
	if (finalizer)
		 duk_push_c_function(ctx, finalizer, 1);
	else duk_push_null(ctx);
	duk_set_finalizer(ctx, -2);
}
void duk_add_class(duk_context *ctx,
						  const char *class_name, const char *extends_name,
						  duk_c_function put_member, duk_c_function constructor,
						  duk_c_function put_static) {
	// [class_name]
	duk_push_string(ctx, class_name);
	// [class_name] [constructor]
	duk_push_c_function(ctx, constructor, DUK_VARARGS);
	// [class_name] [constructor] [.name]
	duk_push_string(ctx, "name");
	// [class_name] [constructor] [.name] [class_name]
	duk_push_string(ctx, class_name);
	// [class_name] [constructor] (.name = class_name)
	duk_def_prop(ctx, -3, DUK_DEFPROP_PUBLIC_CONST);
	// [class_name] [constructor] [.prototype]
	duk_push_string(ctx, "prototype");
	// [class_name] [constructor] [.prototype] [object]
	duk_push_object(ctx);
	put_member(ctx);
	// [class_name] [constructor] (.prototype = object)
	duk_def_prop(ctx, -3, DUK_DEFPROP_PUBLIC_CONST);
	if (put_static)
		put_static(ctx);
	// (.class_name = constructor)
	duk_def_prop(ctx, -3, DUK_DEFPROP_PUBLIC_CONST);
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

void *duk_put_cstruct(duk_context *ctx, duk_size_t size) {
	duk_push_this(ctx);
	duk_push_string(ctx, "__p");
	auto pobj = duk_push_fixed_buffer(ctx, size);
	duk_def_prop(ctx, -3, DUK_DEFPROP_PUBLIC_CONST);
	duk_pop(ctx);
	return pobj;
}

bool duk_get__p(duk_context *ctx, void *&ptr, duk_size_t size, duk_idx_t idx) {
	duk_get_prop_string(ctx, idx, "__p");
	bool res = false;
	switch (duk_get_type(ctx, -1)) {
		case DUK_TYPE_POINTER:
			ptr = duk_get_pointer(ctx, -1);
			res = true;
			break;
		case DUK_TYPE_BUFFER: {
			duk_size_t read_size = 0;
			ptr = duk_get_buffer(ctx, -1, &read_size);
			if (size != read_size) {
				duk_errout(ctx, "buffer size %d invalid, should be %d",
						   read_size, size);
				break;
			}
			res = true;
			break;
		}
		case DUK_TYPE_UNDEFINED:
			duk_errout(ctx, "__p must be defined as a pointer or buffer");
			break;
		default:
			duk_errout(ctx, "__p must be a pointer or buffer");
	}
	duk_pop(ctx);
	return res;
}
void *duk_get_this__p(duk_context *ctx, duk_size_t size) {
	void *ptr = O;
	duk_push_this(ctx);
	duk_get__p(ctx, ptr, size, -1);
	return ptr;
}
void duk_put_this__p(duk_context *ctx, HANDLE hd) {
	duk_push_this(ctx);
	duk_push_string(ctx, "__p");
	duk_push_pointer(ctx, hd);
	duk_def_prop(ctx, -3, DUK_DEFPROP_PUBLIC_CONST);
	duk_pop(ctx);
}

bool duk_get_class__p(duk_context *ctx, const char *class_name, void *&ptr, duk_size_t size, duk_idx_t idx) {
	if (duk_is_null(ctx, idx))
		return true;
	bool res = false;
	duk_get_global_string(ctx, class_name);
	if (duk_instanceof(ctx, idx, -1))
		res = duk_get__p(ctx, ptr, size, idx);
	else duk_errout(ctx, "argument is not a instance of %s", class_name);
	duk_pop(ctx);
	return res;
}

void duk_push_new_handle(duk_context *ctx, const char *class_name, HANDLE hd) {
	if (!hd) {
		duk_push_null(ctx);
		return;
	}
	duk_get_global_string(ctx, class_name);
	duk_push_pointer(ctx, hd);
	duk_new(ctx, 1);
}
void duk_push_new_cclass(duk_context *ctx, const char *class_name, HANDLE hd) {
	if (!hd) {
		duk_push_null(ctx);
		return;
	}
	duk_get_global_string(ctx, class_name);
	duk_push_pointer(ctx, hd);
	duk_new(ctx, 1);
	duk_put_destructor(ctx, O);
}

bool duk_load_library(duk_context *ctx, duk_safe_call_function func) {
	duk_push_global_object(ctx);
	auto rc = duk_safe_call(ctx, func, O, 1, 0);
	if (rc == DUK_EXEC_SUCCESS) return true;
	duk_dup(ctx, -1);
	duk_put_global_string(ctx, "LastError");
	duk_errout(ctx, "Load library failed: \n%s\n", duk_safe_to_stacktrace(ctx, -1));
	return false;
}

duk_ret_t load_duk_windows(duk_context *ctx, void *) {
	duk_dup(ctx, 0);
	load_duk_types(ctx);
	load_duk_resource(ctx);
	load_duk_gdi(ctx);
	load_duk_window(ctx);
	load_duk_dialog(ctx);
	load_duk_control(ctx);
	load_duk_console(ctx);
	load_duk_realtime(ctx);
	return 0;
}
