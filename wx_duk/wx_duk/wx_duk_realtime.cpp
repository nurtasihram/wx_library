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
	duk_push_object(ctx); // target	
	duk_push_object(ctx); // handler
	//duk_push_c_function()
	duk_push_proxy(ctx, 0);
#pragma endregion
}
