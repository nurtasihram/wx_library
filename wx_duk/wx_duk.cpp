#include <iostream>

#include "wx_window.h"
#include "duk_config.h"
#include "duktape.h"

using namespace WX;

struct duk_exception {
	duk_errcode_t code;
	const char *MsgId;
};

void duk_property(duk_context *ctx, const char *name, duk_c_function setter, duk_c_function getter) {
	duk_push_string(ctx, name);
	if (getter)
		duk_push_c_function(ctx, getter, 0);
	if (setter)
		duk_push_c_function(ctx, setter, 1);
	duk_def_prop(ctx, -(2 + (getter ? 1 : 0) + (setter ? 1 : 0)),
					/* getter */ (getter ? DUK_DEFPROP_HAVE_GETTER : 0) |
					/* setter */ (setter ? DUK_DEFPROP_HAVE_SETTER : 0) |
					/* configurable : false */	DUK_DEFPROP_CLEAR_CONFIGURABLE
	);
}
struct duk_property_struct {
	const char *name;
	duk_c_function setter, getter;
};
void duk_property(duk_context *ctx, const duk_property_struct *c, uint32_t len) {
	for (; len--; ++c)
		duk_property(ctx, c->name, c->setter, c->getter);
}
template<size_t len>
void duk_property(duk_context *ctx, const duk_property_struct(&c)[len]) {
	duk_property(ctx, c, len);
}

void duk_constant(duk_context *ctx, const char *name, duk_uint_t value) {
	duk_push_string(ctx, name);
	duk_push_uint(ctx, value);
	duk_def_prop(ctx, 0,
					/* value */				DUK_DEFPROP_HAVE_VALUE |
					/* enumerable : true */	DUK_DEFPROP_SET_ENUMERABLE |
					/* configurable : false */	DUK_DEFPROP_CLEAR_CONFIGURABLE
	);
}
struct duk_constant_struct {
	const char *name;
	duk_uint_t value;
};
void duk_constant(duk_context *ctx, const duk_constant_struct *c, uint32_t len) {
	for (; len--; ++c)
		duk_constant(ctx, c->name, c->value);
}
template<size_t len>
void duk_constant(duk_context *ctx, const duk_constant_struct(&c)[len]) {
	duk_constant(ctx, c, len);
}
void duk_function_global(duk_context *ctx, const char *name, duk_c_function constructor, duk_idx_t nargs = DUK_VARARGS) {
	duk_push_c_function(ctx, constructor, nargs);
	duk_put_global_string(ctx, name);
}
void duk_this_extends(duk_context *ctx, const char *classname) {
	duk_push_this(ctx);
	duk_get_global_string(ctx, classname);
	duk_set_prototype(ctx, -2);
}
void duk_class_extends(duk_context *ctx, const char *classname) {
	duk_push_object(ctx);
	duk_get_global_string(ctx, classname);
	duk_set_prototype(ctx, -2);
}

void duk_object_global(duk_context *ctx, void(*defs)(duk_context *ctx)) {
	duk_push_global_object(ctx);
	defs(ctx);
	duk_pop(ctx);
}
void duk_object_struct(duk_context *ctx, const char *name, void(*constuctor)(duk_context *ctx)) {
	duk_push_object(ctx);
	constuctor(ctx);
	duk_put_global_string(ctx, name);
}
void duk_member_int(duk_context *ctx, const char *name, duk_int_t i) {
	duk_push_int(ctx, i);
	duk_put_prop_string(ctx, -2, name);
}
void duk_member_function(duk_context *ctx, const char *name, duk_c_function func, duk_idx_t nargs = 0) {
	duk_push_c_function(ctx, func, nargs);
	duk_put_prop_string(ctx, -2, name);
}

HWND duk_member_HWND(duk_context *ctx) {
	duk_push_this(ctx);
	duk_get_prop_string(ctx, -1, "__p");
	if (duk_get_type(ctx, -1) != DUK_TYPE_POINTER)
		return nullptr; // pointer lost
	return (HWND)duk_get_pointer(ctx, -1);
}
void duk_member_HWND(duk_context *ctx, HWND hwnd) {
	duk_push_this(ctx);
	duk_push_string(ctx, "__p");
	duk_push_pointer(ctx, hwnd);
	duk_def_prop(ctx, -3,
				 DUK_DEFPROP_HAVE_VALUE
				 | DUK_DEFPROP_HAVE_WRITABLE | 0		// writable : false
				 | DUK_DEFPROP_HAVE_CONFIGURABLE | 0	// configurable : false
	);
}

template<class AnyBlock>
void wx_try(AnyBlock block) {
	try {
		block();
	} catch (Exception err) {
		auto atr = Console.Attr();
		Console.Log(_T(" - WX inner exception: "));
		Console.Attr(0x0C).Log(err, _T('\n'));
		Console.Attr(atr);
	}
}

class BaseOf_Window(duk_window) {
	SFINAE_Window(duk_window);
public:
};

void load_symbols(duk_context *ctx) {

#define _VPROPS_(name, cclass, type, defval) \
	#name, \
	[](duk_context *ctx) -> duk_ret_t { \
		if (auto obj = reuse_as<cclass>(duk_member_HWND(ctx))) \
			obj.name(duk_to_##type(ctx, 0)); \
		return 0; \
	}, \
	[](duk_context *ctx) -> duk_ret_t { \
		if (auto obj = reuse_as<cclass>(duk_member_HWND(ctx))) \
			duk_push_##type(ctx, obj.name()); \
		else \
			duk_push_##type(ctx, defval); \
		return 1; \
	}
#define _VPROPS_TEXT_(type) \
	"Text", \
	[](duk_context *ctx) -> duk_ret_t { \
		if (auto obj = reuse_as<cclass>(duk_member_HWND(ctx))) \
			pObj->Text(duk_to_string(ctx, 0)); \
		return 0; \
	}, \
	[](duk_context *ctx) -> duk_ret_t { \
		if (auto obj = reuse_as<cclass>(duk_member_HWND(ctx))) \
			duk_push_string(ctx, pObj->Text()); \
		else \
			duk_push_string(ctx, ""); \
		return 1; \
	}

	/* Point */
	duk_object_struct(ctx, "PointObj", [](duk_context *ctx) {
		duk_member_int(ctx, "x", 0);
		duk_member_int(ctx, "y", 0);
		duk_member_function(ctx, "toString", [](duk_context *ctx) -> duk_ret_t {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "x");
			duk_get_prop_string(ctx, -2, "y");
			duk_push_sprintf(ctx, "{x:%d,y:%d}",
							 duk_get_int(ctx, -2),
							 duk_get_int(ctx, -1));
			return 1;
		});
	});
	duk_function_global(ctx, "Point", [](duk_context *ctx) {
		int nargs = duk_get_top(ctx);
		if (!duk_is_constructor_call(ctx))
			return 0;
		int x = 0, y = 0;
		switch (nargs) {
			case 0:
				break;
			case 1:
				if (duk_is_object(ctx, 0)) {
					duk_get_global_string(ctx, "Point");
					if (duk_instanceof(ctx, 0, -1))
						return 0;
				}
				x = y = duk_to_int(ctx, 0);
				break;
			case 2:
				x = duk_to_int(ctx, 0);
				y = duk_to_int(ctx, 1);
				break;
			default:
				return DUK_RET_SYNTAX_ERROR;
		}
		duk_this_extends(ctx, "PointObj");
		duk_push_this(ctx);
		duk_push_int(ctx, x);
		duk_put_prop_string(ctx, -2, "x");
		duk_push_int(ctx, y);
		duk_put_prop_string(ctx, -2, "y");
		return 0;
	});

	/* Rect */
	static auto __SRect = [](duk_context *ctx) -> LRect {
		duk_push_this(ctx);
		duk_get_prop_string(ctx, -1, "x0");
		duk_get_prop_string(ctx, -2, "y0");
		duk_get_prop_string(ctx, -3, "x1");
		duk_get_prop_string(ctx, -4, "y1");
		return{
			duk_get_int(ctx, -4),
			duk_get_int(ctx, -3),
			duk_get_int(ctx, -2),
			duk_get_int(ctx, -1)
		};
	};
	duk_object_struct(ctx, "RectObj", [](duk_context *ctx) {
		duk_member_int(ctx, "x0", 0);
		duk_member_int(ctx, "y0", 0);
		duk_member_int(ctx, "x1", 0);
		duk_member_int(ctx, "y1", 0);
		duk_property(ctx, "SizeX", nullptr, [](duk_context *ctx) -> duk_ret_t {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "x0");
			duk_get_prop_string(ctx, -2, "x1");
			auto x0 = duk_get_int(ctx, -2);
			auto x1 = duk_get_int(ctx, -1);
			duk_push_int(ctx, x1 - x0 + 1);
			return 1;
		});
		duk_property(ctx, "SizeY", nullptr, [](duk_context *ctx) -> duk_ret_t {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "y0");
			duk_get_prop_string(ctx, -2, "y1");
			auto y0 = duk_get_int(ctx, -2);
			auto y1 = duk_get_int(ctx, -1);
			duk_push_int(ctx, y1 - y0 + 1);
			return 1;
		});
		duk_property(ctx, "Size", nullptr, [](duk_context *ctx) -> duk_ret_t {
			auto &&r = __SRect(ctx);
			duk_push_global_object(ctx);
			duk_get_prop_string(ctx, -1, "Point");
			duk_push_int(ctx, r.xsize());
			duk_push_int(ctx, r.ysize());
			duk_new(ctx, 2);
			return 1;
		});
		duk_property(ctx, "LeftTop",
			[](duk_context *ctx) -> duk_ret_t {
				duk_get_prop_string(ctx, 0, "x");
				duk_get_prop_string(ctx, 0, "y");
				auto x0 = duk_get_int(ctx, -2),
					y0 = duk_get_int(ctx, -1);
				duk_push_this(ctx);
				duk_member_int(ctx, "x0", x0);
				duk_member_int(ctx, "y0", y0);
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				duk_push_this(ctx);
				duk_get_prop_string(ctx, -1, "x0");
				duk_get_prop_string(ctx, -2, "y0");
				auto x0 = duk_get_int(ctx, -2),
					y0 = duk_get_int(ctx, -1);
				duk_push_global_object(ctx);
				duk_get_prop_string(ctx, -1, "Point");
				duk_push_int(ctx, x0);
				duk_push_int(ctx, y0);
				duk_new(ctx, 2);
				return 1;
			}
		);
		duk_member_function(ctx, "toString", [](duk_context *ctx) -> duk_ret_t {
			auto &&r = __SRect(ctx);
			duk_push_sprintf(
				ctx, "{ x0: %d, y0: %d, x1: %d, y1: %d }",
				r.x0(), r.y0(), r.x1(), r.y1());
			return 1;
		});
	});
	duk_function_global(ctx, "Rect", [](duk_context *ctx) {
		if (!duk_is_constructor_call(ctx))
			return 0;
		int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
		switch (int nargs = duk_get_top(ctx)) {
			case 0:
				break;
			case 1:
				x0 = y0 = x1 = y1 = duk_to_int(ctx, 0);
				break;
			case 2:
				break;
			case 4:
				x0 = duk_to_int(ctx, 0);
				y0 = duk_to_int(ctx, 1);
				x1 = duk_to_int(ctx, 2);
				y1 = duk_to_int(ctx, 3);
				break;
			default:
				return 0;
		}
		duk_this_extends(ctx, "RectObj");
		duk_push_this(ctx);
		duk_member_int(ctx, "x0", x0);
		duk_member_int(ctx, "y0", y0);
		duk_member_int(ctx, "x1", x1);
		duk_member_int(ctx, "y1", y1);
		return 1;
	});

	/* Window */
	duk_object_struct(ctx, "WObj", [](duk_context *ctx) {
		duk_property(ctx, _VPROPS_(Visible, Window, boolean, false));
	});
	duk_function_global(ctx, "Window", [](duk_context *ctx) {
		if (!duk_is_constructor_call(ctx))
			return 0;
		duk_window::CreateStruct cs;
		switch (int nargs = duk_get_top(ctx)) {
			case 0:
			case 1:
				//if (duk_is_object(ctx))
				break;
			default:
				return 0;
		}
		duk_this_extends(ctx, "WObj");
		HWND hwnd = O;
		wx_try([&]() { hwnd = cs.Create(); });
		duk_member_HWND(ctx, hwnd);
		return 1;
	});
}

void commandline(duk_context *ctx) {
	char js_code[1024];
	for (; ;) {
		std::cout << " > ";
		std::cin.getline(js_code, sizeof(js_code));
		try {
			duk_eval_raw(
				ctx, js_code, 0,
				1 /*args*/ |
				DUK_COMPILE_EVAL |
				DUK_COMPILE_NOSOURCE |
				DUK_COMPILE_STRLEN |
				DUK_COMPILE_NOFILENAME);
		} catch (duk_exception err) {
			std::cout << "FATAL: " << err.MsgId << std::endl;
			std::cout << "CODE:  " << err.code << std::endl;
		}
	}
_ret:
	Msg msg;
	try {
		while (msg.Get()) {
			msg.Translate();
			msg.Dispatch();
		}
	} catch (...) {
		goto _ret;
	}
	system("pause");
}

void *duk_alloc(void *, duk_size_t size) {
	return malloc(size);
}
void *duk_realloc(void *, void *ptr, duk_size_t size) {
	return realloc(ptr, size);
}
void duk_free(void *, void *ptr) {
	free(ptr);
}
void duk_onfatal(duk_context *, duk_errcode_t code, const char *MsgId) {
	throw duk_exception{ code, MsgId };
}

int main() {
	duk_context *ctx = duk_create_heap(duk_alloc, duk_realloc, duk_free, O, duk_onfatal);
	load_symbols(ctx);
	commandline(ctx);
	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow) {
	Console.Alloc();
	Console.Select();
	Console.Reopen();
	return main();
}
