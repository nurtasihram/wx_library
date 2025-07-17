#include "wx_control.h"

#include "wx_duk.h"

static void load_duk_header(duk_context *ctx) {
}
static void load_duk_toolbar(duk_context *ctx) {}
static void load_duk_rebar(duk_context *ctx) {}
static void load_duk_tooltip(duk_context *ctx) {}
static void load_duk_statusbar(duk_context *ctx) {}
static void load_duk_trackbar(duk_context *ctx) {}
static void load_duk_draglist(duk_context *ctx) {}
static void load_duk_updown(duk_context *ctx) {}
static void load_duk_progress(duk_context *ctx) {}
static void load_duk_hotkey(duk_context *ctx) {}
static void load_duk_syslink(duk_context *ctx) {}
static void load_duk_listview(duk_context *ctx) {}
static void load_duk_treeview(duk_context *ctx) {}
static void load_duk_tab(duk_context *ctx) {}
static void load_duk_animate(duk_context *ctx) {}
static void load_duk_monthcal(duk_context *ctx) {}
static void load_duk_datetimepick(duk_context *ctx) {}
static void load_duk_pager(duk_context *ctx) {}
static void load_duk_nativefont(duk_context *ctx) {}
static void load_duk_button(duk_context *ctx) {}
static void load_duk_static(duk_context *ctx) {}
static void load_duk_edit(duk_context *ctx) {}
static void load_duk_listbox(duk_context *ctx) {}
static void load_duk_combobox(duk_context *ctx) {}
static void load_duk_scrollbar(duk_context *ctx) {}

void load_duk_control(duk_context *ctx) {
	load_duk_header(ctx);
	load_duk_toolbar(ctx);
	load_duk_rebar(ctx);
	load_duk_tooltip(ctx);
	load_duk_statusbar(ctx);
	load_duk_trackbar(ctx);
	load_duk_draglist(ctx);
	load_duk_updown(ctx);
	load_duk_progress(ctx);
	load_duk_hotkey(ctx);
	load_duk_syslink(ctx);
	load_duk_listview(ctx);
	load_duk_treeview(ctx);
	load_duk_tab(ctx);
	load_duk_animate(ctx);
	load_duk_monthcal(ctx);
	load_duk_datetimepick(ctx);
	load_duk_pager(ctx);
	load_duk_nativefont(ctx);
	load_duk_button(ctx);
	load_duk_static(ctx);
	load_duk_edit(ctx);
	load_duk_listbox(ctx);
	load_duk_combobox(ctx);
	load_duk_scrollbar(ctx);
}
