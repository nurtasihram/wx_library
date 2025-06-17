#include "wx_duk.h"

using namespace WX;

bool duk_get_point(duk_context *ctx, LPoint &point, duk_idx_t idx) {
	if (duk_is_array(ctx, idx)) {
		duk_dup(ctx, idx);
		duk_get_prop_index(ctx, -1, 0);
		point.x = duk_get_int(ctx, -1);
		duk_get_prop_index(ctx, -2, 1);
		point.y = duk_get_int(ctx, -1);
	}
	else if (duk_is_object(ctx, idx)) {
		duk_get_prop_string(ctx, -1, "x");
		point.x = duk_get_int(ctx, -1);
		duk_get_prop_string(ctx, -2, "y");
		point.y = duk_get_int(ctx, -1);
	}
	else if (duk_is_number(ctx, idx))
		point = duk_get_int(ctx, idx);
	else
		return false;
	return true;
}
void duk_push_point(duk_context *ctx, LPoint point) {
	duk_get_global_string(ctx, "Point");
	duk_push_int(ctx, point.x);
	duk_push_int(ctx, point.y);
	duk_new(ctx, 2);
}

bool duk_get_rect(duk_context *ctx, LRect &rect, duk_idx_t idx) {
	if (duk_is_array(ctx, idx)) {
		duk_dup(ctx, idx);
		duk_get_prop_index(ctx, -1, 0);
		rect.left = duk_get_int(ctx, -1);
		duk_get_prop_index(ctx, -2, 1);
		rect.top = duk_get_int(ctx, -1);
		duk_get_prop_index(ctx, -3, 2);
		rect.right = duk_get_int(ctx, -1);
		duk_get_prop_index(ctx, -4, 3);
		rect.bottom = duk_get_int(ctx, -1);
	}
	else if (duk_is_object(ctx, idx)) {
		duk_get_prop_string(ctx, -1, "x0");
		rect.left = duk_get_int(ctx, -1);
		duk_get_prop_string(ctx, -2, "y0");
		rect.top = duk_get_int(ctx, -1);
		duk_get_prop_string(ctx, -3, "x1");
		rect.right = duk_get_int(ctx, -1);
		duk_get_prop_string(ctx, -4, "y1");
		rect.bottom = duk_get_int(ctx, -1);
	}
	else if (duk_is_number(ctx, idx))
		rect = duk_get_int(ctx, idx);
	else
		return false;
	return true;
}
void duk_push_rect(duk_context *ctx, const LRect &rect) {
	duk_get_global_string(ctx, "Rect");
	duk_push_int(ctx, rect.left);
	duk_push_int(ctx, rect.top);
	duk_push_int(ctx, rect.right);
	duk_push_int(ctx, rect.bottom);
	duk_new(ctx, 4);
}

struct enum_inf {
	const duk_constant_struct *pEnums = O;
	uint32_t count = 0;
	const char *name = O;
	static bool get_static(duk_context *ctx, enum_inf &ei) {
		duk_get_prop_string(ctx, -1, "__p");
		if (duk_get_type(ctx, -1) != DUK_TYPE_POINTER)
			return true;
		ei.pEnums = (const duk_constant_struct *)duk_get_pointer(ctx, -1);
		if (!ei.pEnums)
			return true;
		duk_pop(ctx);
		duk_get_prop_string(ctx, -1, "__c");
		ei.count = duk_to_int(ctx, -1);
		if (ei.count == 0)
			return true;
		duk_pop(ctx);
		duk_get_prop_string(ctx, -1, "__n");
		ei.name = duk_to_string(ctx, -1);
		if (!ei.name)
			return true;
		if (!*ei.name)
			return true;
		duk_pop(ctx);
		return false;
	}
	static bool get(duk_context *ctx, enum_inf &ei) {
		duk_push_this(ctx);
		duk_get_prop_string(ctx, -1, "__o");
		return get_static(ctx, ei);
	}
};
void duk_flags(duk_context *ctx,
			   const char *type,
			   const char *name, const char *parent_name,
			   const duk_constant_struct* dcs, uint32_t len) {
	duk_function_global(ctx, name, [](duk_context *ctx) -> duk_ret_t {
		if (duk_reflect_constructor(ctx))
			return 1;
		auto val = duk_to_int(ctx, 0);
		duk_push_this(ctx);
		duk_member_int(ctx, "val", val);
		duk_push_current_function(ctx);
		duk_put_prop_string(ctx, -2, "__o");
		return 0;
	}, 1);
	duk_get_global_string(ctx, name);
	duk_push_string(ctx, "__p");
	duk_push_pointer(ctx, (void *)dcs);
	duk_def_prop(ctx, -3,
				 DUK_DEFPROP_HAVE_VALUE
				 | DUK_DEFPROP_HAVE_WRITABLE | 0		// writable : false
				 | DUK_DEFPROP_HAVE_CONFIGURABLE | 0	// configurable : false
	);
	duk_constant(ctx, dcs, len);
	duk_method(ctx, "toString", 0, [](duk_context *ctx) -> duk_ret_t {
		duk_push_this(ctx);
		enum_inf ei;
		if (enum_inf::get_static(ctx, ei))
			return DUK_RET_INTERNAL_ERROR;
		const char *fmt1 = "  %s: 0x%x,\n";
		const char *fmt2 = "  %s: 0x%x\n";
		duk_push_string(ctx, "{\n");
		int i = 0;
		auto fmt = fmt1;
		do {
			duk_push_sprintf(ctx, fmt, ei.pEnums[i].name, ei.pEnums[i].value);
			if (++i == ei.count - 1)
				fmt = fmt2;
		} while (i < ei.count);
		duk_push_string(ctx, "}\n");
		duk_concat(ctx, ei.count + 2);
		return 1;
	});
	duk_member_int(ctx, "__c", len);
	duk_member_str(ctx, "__n", name);
	if (parent_name) {
		duk_get_global_string(ctx, parent_name);
		duk_put_prop_string(ctx, -2, "__l");
	}
	duk_extends(ctx, name, type);
}
void load_duk_enum(duk_context *ctx) {
	static auto __pushFlags = [](duk_context *ctx, duk_int_t val, const enum_inf &ei) -> duk_ret_t {
		if (val == 0) {
			for (int i = 0; i < ei.count; ++i) {
				auto &e = ei.pEnums[i];
				if (e.value == 0) {
					duk_push_sprintf(ctx, "%s.%s", ei.name, e.name);
					return 1;
				}
			}
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "__o");
			duk_get_prop_string(ctx, -1, "__l");
			if (duk_is_undefined(ctx, -1)) {
				duk_pop_3(ctx);
				duk_push_sprintf(ctx, "0x%x", val);
			}
			else {
				duk_push_int(ctx, val);
				duk_new(ctx, 1);
				duk_to_string(ctx, -1);
				duk_insert(ctx, -3);
				duk_pop_2(ctx);
			}
			return 1;
		}
		int concats = 0;
		for (int i = 0; i < ei.count; ++i) {
			auto &e = ei.pEnums[i];
			if (!e.value) continue;
			if ((val & e.value) == e.value) {
				val &= ~e.value;
				duk_push_sprintf(ctx, "%s.%s", ei.name, e.name);
				++concats;
				if (val == 0)
					break;
				duk_push_string(ctx, "|");
				++concats;
			}
		}
		if (val != 0) {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "__o");
			duk_get_prop_string(ctx, -1, "__l");
			if (duk_is_undefined(ctx, -1)) {
				duk_pop_3(ctx);
				duk_push_sprintf(ctx, "0x%x", val);
				++concats;
			}
			else {
				duk_push_int(ctx, val);
				duk_new(ctx, 1);
				duk_to_string(ctx, -1);
				duk_insert(ctx, -3);
				duk_pop_2(ctx);
				++concats;
			}
		}
		duk_concat(ctx, concats);
		return 1;
	};
	static auto __pushEnum = [](duk_context *ctx, duk_int_t val, const enum_inf &ei) -> duk_ret_t {
		for (int i = 0; i < ei.count; ++i) {
			auto &e = ei.pEnums[i];
			if (e.value == 0) {
				duk_push_sprintf(ctx, "%s.%s", ei.name, e.name);
				return 1;
			}
		}
		duk_push_this(ctx);
		duk_get_prop_string(ctx, -1, "__o");
		duk_get_prop_string(ctx, -1, "__l");
		if (duk_is_undefined(ctx, -1)) {
			duk_pop_3(ctx);
			duk_push_sprintf(ctx, "0x%x", val);
		}
		else {
			duk_push_int(ctx, val);
			duk_new(ctx, 1);
			duk_to_string(ctx, -1);
			duk_insert(ctx, -3);
			duk_pop_2(ctx);
		}
		return DUK_RET_INTERNAL_ERROR;
	};
	static auto _toString = [](duk_context *ctx) -> duk_ret_t {
		duk_push_this(ctx);
		duk_get_prop_string(ctx, -1, "val");
		auto val = duk_to_int(ctx, -1);
		duk_pop(ctx);
		duk_get_prop_string(ctx, -1, "stringOf");
		duk_push_this(ctx);
		duk_push_int(ctx, val);
		duk_call_method(ctx, 1);
		return 1;
	};
	duk_struct_global(ctx, "FlagsObj", [](duk_context *ctx) -> duk_ret_t {
		duk_member_int(ctx, "val", 0);
		duk_method(ctx, "valueOf", 0, [](duk_context *ctx) -> duk_ret_t {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "val");
			return 1;
		});
		duk_method(ctx, "stringOf", 1, [](duk_context *ctx) -> duk_ret_t {
			duk_int_t val = duk_to_int(ctx, 0);
			enum_inf ei;
			if (enum_inf::get(ctx, ei))
				return DUK_RET_TYPE_ERROR;
			return __pushFlags(ctx, val, ei);
		});
		duk_method(ctx, "toString", 0, _toString);
		return 0;
	});
	duk_struct_global(ctx, "EnumObj", [](duk_context *ctx) -> duk_ret_t {
		duk_member_int(ctx, "val", 0);
		duk_method(ctx, "valueOf", 0, [](duk_context *ctx) -> duk_ret_t {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "val");
			return 1;
		});
		duk_method(ctx, "stringOf", 1, [](duk_context *ctx) -> duk_ret_t {
			auto val = duk_to_int(ctx, 0);
			enum_inf ei;
			if (enum_inf::get(ctx, ei))
				return DUK_RET_TYPE_ERROR;
			return __pushEnum(ctx, val, ei);
		});
		duk_method(ctx, "toString", 0, _toString);
		return 0;
	});
}
void load_duk_point(duk_context *ctx) {
	duk_struct_global(ctx, "PointObj", [](duk_context *ctx) -> duk_ret_t {
		duk_member_int(ctx, "x", 0);
		duk_member_int(ctx, "y", 0);
		duk_method(ctx, "toString", 0, [](duk_context *ctx) -> duk_ret_t {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "x");
			auto x = duk_get_int(ctx, -1);
			duk_get_prop_string(ctx, -2, "y");
			auto y = duk_get_int(ctx, -1);
			duk_push_sprintf(ctx, "{x:%d,y:%d}", x, y);
			return 1;
		});
		return 0;
	});
	duk_function_global(ctx, "Point", [](duk_context *ctx) -> duk_ret_t {
		if (duk_reflect_constructor(ctx))
			return 1;
		LPoint p;
		switch (duk_get_top(ctx)) {
			case 0:
				break;
			case 1:
				if (!duk_get_point(ctx, p, 0))
					return DUK_RET_SYNTAX_ERROR;
				break;
			case 2:
				p.x = duk_to_int(ctx, 0);
				p.y = duk_to_int(ctx, 1);
				break;
			default:
				return DUK_RET_SYNTAX_ERROR;
		}
		duk_push_this(ctx);
		duk_push_int(ctx, p.x);
		duk_put_prop_string(ctx, -2, "x");
		duk_push_int(ctx, p.y);
		duk_put_prop_string(ctx, -2, "y");
		return 0;
	});
	duk_extends(ctx, "Point", "PointObj");
}

void load_duk_rect(duk_context *ctx) {
	duk_struct_global(ctx, "RectObj", [](duk_context *ctx) -> duk_ret_t {
		duk_member_int(ctx, "x0", 0);
		duk_member_int(ctx, "y0", 0);
		duk_member_int(ctx, "x1", 0);
		duk_member_int(ctx, "y1", 0);
		duk_property_r(ctx, "SizeX", [](duk_context *ctx) -> duk_ret_t {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "x0");
			auto x0 = duk_get_int(ctx, -1);
			duk_get_prop_string(ctx, -2, "x1");
			auto x1 = duk_get_int(ctx, -1);
			duk_push_int(ctx, x1 - x0 + 1);
			return 1;
		});
		duk_property_r(ctx, "SizeY", [](duk_context *ctx) -> duk_ret_t {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "y0");
			auto y0 = duk_get_int(ctx, -1);
			duk_get_prop_string(ctx, -2, "y1");
			auto y1 = duk_get_int(ctx, -1);
			duk_push_int(ctx, y1 - y0 + 1);
			return 1;
		}
		);
		duk_property_r(ctx, "Size", [](duk_context *ctx) -> duk_ret_t {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "x0");
			auto x0 = duk_get_int(ctx, -1);
			duk_get_prop_string(ctx, -2, "y0");
			auto y0 = duk_get_int(ctx, -1);
			duk_get_prop_string(ctx, -3, "x1");
			auto x1 = duk_get_int(ctx, -1);
			duk_get_prop_string(ctx, -4, "y1");
			auto y1 = duk_get_int(ctx, -1);
			duk_get_global_string(ctx, "Point");
			duk_push_int(ctx, x1 - x0 + 1);
			duk_push_int(ctx, y1 - y0 + 1);
			duk_new(ctx, 2);
			return 1;
		});
		duk_method(ctx, "toString", 0, [](duk_context *ctx) -> duk_ret_t {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "x0");
			auto x0 = duk_get_int(ctx, -1);
			duk_get_prop_string(ctx, -2, "y0");
			auto y0 = duk_get_int(ctx, -1);
			duk_get_prop_string(ctx, -3, "x1");
			auto x1 = duk_get_int(ctx, -1);
			duk_get_prop_string(ctx, -4, "y1");
			auto y1 = duk_get_int(ctx, -1);
			duk_push_sprintf(ctx, "{x0:%d,y0:%d,x1:%d,y1:%d}", x0, y0, x1, y1);
			return 1;
		});
		return 0;
	});
	duk_function_global(ctx, "Rect", [](duk_context *ctx) -> duk_ret_t {
		if (duk_reflect_constructor(ctx))
			return 1;
		LRect r;
		switch (duk_get_top(ctx)) {
			case 0:
				break;
			case 1:
				r = duk_to_int(ctx, 0);
				break;
			case 2:
				break;
			case 4:
				r.left = duk_to_int(ctx, 0);
				r.top = duk_to_int(ctx, 1);
				r.right = duk_to_int(ctx, 2);
				r.bottom = duk_to_int(ctx, 3);
				break;
			default:
				return 0;
		}
		duk_push_this(ctx);
		duk_member_int(ctx, "x0", r.left);
		duk_member_int(ctx, "y0", r.top);
		duk_member_int(ctx, "x1", r.right);
		duk_member_int(ctx, "y1", r.bottom);
		return 0;
	});
	duk_extends(ctx, "Rect", "RectObj");
}
static void load_duk_color(duk_context *ctx) {
	static auto push_rgb = [](duk_context *ctx, duk_ret_t val) {
		duk_push_sprintf(ctx,
						 "{red:%d,green:%d,blue:%d}",
						 GetRValue(val),
						 GetGValue(val),
						 GetBValue(val));
	};
	duk_struct_global(ctx, "RGBObj", [](duk_context *ctx) -> duk_ret_t {
		duk_member_int(ctx, "val", 0);
		duk_property(ctx, "red",
			[](duk_context *ctx) -> duk_ret_t {
				auto red = duk_to_int(ctx, 0) & 0xFF;
				duk_push_this(ctx);
				duk_get_prop_string(ctx, -1, "val");
				auto val = duk_to_int(ctx, -1);
				duk_pop(ctx);
				val &= RGB(0x00, 0xFF, 0xFF);
				val |= RGB(red, 0x00, 0x00);
				duk_member_int(ctx, "val", val);
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				duk_push_this(ctx);
				duk_get_prop_string(ctx, -1, "val");
				auto val = duk_to_int(ctx, -1);
				duk_push_int(ctx, GetRValue(val));
				return 1;
			}
		);
		duk_property(ctx, "green",
			[](duk_context *ctx) -> duk_ret_t {
				auto green = duk_to_int(ctx, 0) & 0xFF;
				duk_push_this(ctx);
				duk_get_prop_string(ctx, -1, "val");
				auto val = duk_to_int(ctx, -1);
				duk_pop(ctx);
				val &= RGB(0xFF, 0x00, 0xFF);
				val |= RGB(0x00, green, 0x00);
				duk_member_int(ctx, "val", val);
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				duk_push_this(ctx);
				duk_get_prop_string(ctx, -1, "val");
				auto val = duk_to_int(ctx, -1);
				duk_push_int(ctx, GetGValue(val));
				return 1;
			}
		);
		duk_property(ctx, "blue",
			[](duk_context *ctx) -> duk_ret_t {
				auto blue = duk_to_int(ctx, 0) & 0xFF;
				duk_push_this(ctx);
				duk_get_prop_string(ctx, -1, "val");
				auto val = duk_to_int(ctx, -1);
				duk_pop(ctx);
				val &= RGB(0xFF, 0xFF, 0x00);
				val |= RGB(0x00, 0x00, blue);
				duk_member_int(ctx, "val", val);
				return 0;
			},
			[](duk_context *ctx) -> duk_ret_t {
				duk_push_this(ctx);
				duk_get_prop_string(ctx, -1, "val");
				auto val = duk_to_int(ctx, -1);
				duk_push_int(ctx, GetBValue(val));
				return 1;
			}
		);
		duk_method(ctx, "valueOf", 0, [](duk_context *ctx) -> duk_ret_t {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "val");
			return 1;
		});
		duk_method(ctx, "toString", 0, [](duk_context *ctx) -> duk_ret_t {
			duk_push_this(ctx);
			duk_get_prop_string(ctx, -1, "val");
			auto val = duk_to_int(ctx, -1);
			push_rgb(ctx, val);
			return 1;
		});
		return 0;
	});
	duk_function_global(ctx, "RGB", [](duk_context *ctx) -> duk_ret_t {
		auto nargs = duk_get_top(ctx);
		if (!duk_is_constructor_call(ctx)) {
			switch (nargs) {
				case 1: {
					auto val = duk_to_int(ctx, 0);
					push_rgb(ctx, val);
					break;
				}
				case 3: {
					auto r = duk_to_int(ctx, 0),
						 g = duk_to_int(ctx, 1),
						 b = duk_to_int(ctx, 2);
					duk_push_int(ctx, RGB(r, g, b));
					break;
				}
				default:
					return DUK_RET_SYNTAX_ERROR;
			}
			return 1;
		}
		duk_int_t val = 0;
		switch (nargs) {
			case 1:
				val = duk_to_int(ctx, 0);
				break;
			case 3: {
				auto r = duk_to_int(ctx, 0),
					 g = duk_to_int(ctx, 1),
					 b = duk_to_int(ctx, 2);
				val = RGB(r, g, b);
				break;
			}
			default:
				return DUK_RET_SYNTAX_ERROR;
		}
		duk_push_this(ctx);
		duk_member_int(ctx, "val", val);
		return 0;
	});
	duk_extends(ctx, "RGB", "RGBObj");
}

static void load_duk_time(duk_context *ctx) {
	static const duk_constant_struct time_formats[] = {
		{ "Default", 0 },
		{ "NoMinutesOrSeconds", TIME_NOMINUTESORSECONDS },
		{ "NoSecond", TIME_NOSECONDS },
		{ "NoTimeMarker", TIME_NOTIMEMARKER },
		{ "Force24H", TIME_FORCE24HOURFORMAT },
	};
	duk_flags(ctx, "EnumObj", "TimeFormat", nullptr, time_formats);
	static const duk_constant_struct date_formats[] = {
		{ "Default", 0 },
		{ "ShortDate", DATE_SHORTDATE },
		{ "LongDate", DATE_LONGDATE },
		{ "CalendarAlt", DATE_USE_ALT_CALENDAR }
	};
	duk_flags(ctx, "EnumObj", "DateFormat", nullptr, date_formats);
	duk_struct_global(ctx, "SysTimeObj", [](duk_context *ctx) -> duk_ret_t {
		//duk_method(ctx, "valueOf", 0, [](duk_context *ctx) -> duk_ret_t {
		//	duk_push_this(ctx);
		//	duk_get_prop_string(ctx, -1, "val");
		//	return 1;
		//});
		duk_method(ctx, "FormatTime", 2, [](duk_context *ctx) -> duk_ret_t {
			auto pobj = (SysTime *)duk_get_buffer(ctx, sizeof(SysTime));
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			auto fmt = duk_to_int(ctx, 0);
			auto &&str = pobj->FormatTimeA(reuse_as<TimeFormat>(fmt));
			duk_push_string(ctx, str);
			return 1;
		});
		duk_method(ctx, "FormatDate", 2, [](duk_context *ctx) -> duk_ret_t {
			auto pobj = (SysTime *)duk_get_buffer(ctx, sizeof(SysTime));
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			auto fmt = duk_to_int(ctx, 0);
			auto &&str = pobj->FormatDateA(reuse_as<DateFormat>(fmt));
			duk_push_string(ctx, str);
			return 1;
		});
		duk_method(ctx, "toString", 0, [](duk_context *ctx) -> duk_ret_t {
			auto pobj = (SysTime *)duk_get_buffer(ctx, sizeof(SysTime));
			if (!pobj)
				return DUK_RET_INTERNAL_ERROR;
			duk_push_string(ctx, (StringA)*pobj);
			return 1;
		});
		return 0;
	});
	duk_function_global(ctx, "SysTime", [](duk_context *ctx) -> duk_ret_t {
		if (duk_reflect_constructor(ctx))
			return 1;
		SysTime st = O;
		switch (duk_get_top(ctx)) {
			case 0:
				st = SysTime();
				break;
			case 1:
				if (duk_is_buffer(ctx, 0)) {
					duk_size_t read_size = 0;
					auto pobj = (SysTime *)duk_get_buffer(ctx, 0, &read_size);
					if (!pobj || read_size != sizeof(SysTime))
						return DUK_RET_INTERNAL_ERROR;
					st = *pobj;
				}
				else if (duk_is_null(ctx, 0))
					break;
				else
					return DUK_RET_TYPE_ERROR;
				break;
			default:
				return DUK_RET_SYNTAX_ERROR;
		}
		duk_push_this(ctx);
		auto pobj = (SysTime *)duk_push_buffer(ctx, sizeof(SysTime), 0);
		new(pobj) SysTime(st);
		duk_put_prop_string(ctx, -2, "__p");
		return 1;
	});
	duk_extends(ctx, "SysTime", "SysTimeObj");
}

void load_duk_types(duk_context *ctx) {
	load_duk_enum(ctx);
	load_duk_point(ctx);
	load_duk_rect(ctx);
	load_duk_color(ctx);
	load_duk_time(ctx);
}
