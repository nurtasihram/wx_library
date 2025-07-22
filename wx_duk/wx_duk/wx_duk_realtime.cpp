#include "wx_realtime.h"

#include "wx_duk.h"

static void load_duk_handle(duk_context *ctx) {
	duk_add_enum_flags<HandleAccess>(ctx);
}

static void load_duk_event(duk_context *ctx) {
	duk_add_enum_flags<EventAccess>(ctx);
	duk_add_class(
		ctx, "Event", O,
		duk_structure {
			/* void */ duk_add_method(ctx, "Set", 0, duk_fn {
				auto pobj = duk_get_this__p<CEvent>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Set(); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_add_method(ctx, "Reset", 0, duk_fn {
				auto pobj = duk_get_this__p<CEvent>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Reset(); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_add_method(ctx, "Pulse", 0, duk_fn {
				auto pobj = duk_get_this__p<CEvent>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Pulse(); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			return 0;
		},
		duk_constructor {
			if (duk_reflect_constructor(ctx))
				return 1;
			switch (duk_get_top(ctx)) {
				case 0:
				case 1:
					break;
			}
			return 0;
		}
	);
}
static void load_duk_mutex(duk_context *ctx) {
	duk_add_class(
		ctx, "Mutex", O,
		duk_structure {
			/* void */ duk_add_method(ctx, "Release", 0, duk_fn {
				auto pobj = duk_get_this__p<CMutex>(ctx);
				if (!pobj) return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Release(); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			return 0;
		},
		duk_constructor {
			if (duk_reflect_constructor(ctx))
				return 1;
			return 0;
		}
	);
}

void load_duk_realtime(duk_context *ctx) {
	load_duk_handle(ctx);
	load_duk_event(ctx);
	load_duk_mutex(ctx);

#pragma region Environment
	duk_push_string(ctx, "Environment");
	duk_push_object(ctx); // target
	duk_push_object(ctx); // handler
	/* EnvVar */ duk_add_method(ctx, "get", 2, duk_fn {
		auto name = duk_to_string(ctx, 1);
		duk_push_object(ctx);
		duk_push_string(ctx, "name");
		duk_push_string(ctx, name);
		duk_def_prop(ctx, -3, DUK_DEFPROP_PRIVATE_CONST);
		/* String */ duk_add_method(ctx, "toString", 0, duk_fn {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "name");
			auto lpName = duk_get_string(ctx, -1);
			duk_push_string(ctx, Environment[lpName].Value());
			return 1;
		});
		/* String */ duk_add_prop_r(ctx, "Expand", duk_fn {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "name");
			auto lpName = duk_to_string(ctx, -1);
			duk_push_string(ctx, Environment[lpName].Expand());
			return 1;
		});
		return 1;
	});
	/* bool */ duk_add_method(ctx, "set", 3, duk_fn {
		auto name = duk_to_string(ctx, 1);
		auto val = duk_to_string(ctx, 0);
		Environment[name] = val;
		duk_push_boolean(ctx, true);
		return 1;
	});
	duk_push_proxy(ctx, 0);
	duk_def_prop(ctx, -3, DUK_DEFPROP_PUBLIC_CONST);
#pragma endregion
}
