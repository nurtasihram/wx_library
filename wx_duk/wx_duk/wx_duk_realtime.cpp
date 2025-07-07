#include "wx_realtime.h"

#include "wx_duk.h"

static void load_duk_handle(duk_context *ctx) {
	static const duk_constant _HandleAccess_constant[]{
		{ "Delete", DELETE },
		{ "ReadCtl", READ_CONTROL },
		{ "WriteDAC", WRITE_DAC },
		{ "WriteOwner", WRITE_OWNER },
		{ "Sync", SYNCHRONIZE },
		{ "GenericRead", GENERIC_READ },
		{ "GenericWrite", GENERIC_WRITE },
		{ "GenericExecute", GENERIC_EXECUTE },
		{ "GenericAll", GENERIC_ALL }
	};
	duk_add_global_flags(ctx, "HandleAccess", O, _HandleAccess_constant);
}

static void load_duk_event(duk_context *ctx) {
	static const duk_constant _EventAccess_constant[]{
		{ "All", EVENT_ALL_ACCESS },
		{ "Modify", EVENT_MODIFY_STATE }
	};
	duk_add_global_flags(ctx, "EventAccess", O, _EventAccess_constant);
	duk_put_global_class(
		ctx, "Event", O,
		duk_structure {
			/* void */ duk_put_method(ctx, "Set", 0, duk_fn {
				auto pobj = duk_get_this__p<CEvent>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Set(); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "Reset", 0, duk_fn {
				auto pobj = duk_get_this__p<CEvent>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
				if (wx_try(ctx, [&] { pobj->Reset(); }))
					return DUK_RET_REFERENCE_ERROR;
				return 0;
			});
			/* void */ duk_put_method(ctx, "Pulse", 0, duk_fn {
				auto pobj = duk_get_this__p<CEvent>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
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
	duk_put_global_class(
		ctx, "Mutex", O,
		duk_structure {
			/* void */ duk_put_method(ctx, "Release", 0, duk_fn {
				auto pobj = duk_get_this__p<CMutex>(ctx);
				if (!pobj)
					return DUK_RET_REFERENCE_ERROR;
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
static void load_duk_environment(duk_context *ctx) {
	duk_push_object(ctx); // target
	duk_push_object(ctx); // handler
	//duk_push_c_function()
	duk_push_proxy(ctx, 0);
}

void load_duk_realtime(duk_context *ctx) {
	load_duk_handle(ctx);
	load_duk_event(ctx);
	load_duk_mutex(ctx);
}
