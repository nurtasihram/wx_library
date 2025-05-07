#include "wx_window.h"
#include "wx_control.h"

using namespace WX;

class BaseOf_Window(Wnd) {
	SFINAE_Window(Wnd);
private:
	WxClass() {
		xClass() {
			Styles(CStyle::Redraw);
			Cursor(IDC_ARROW);
			Background(SysColor::Window);
		}
	};
	inline auto Create() {
		return super::Create()
			.Styles(WS::OverlappedWindow)
			.Size(500)
			.Position(100);
	}
private:
	inline bool OnCreate(RefAs<CreateStruct *> pCreate) {
		return true;
	}
	inline void OnPaint() {
	}
};

void test_wnd() {
	Wnd win;
	assertl(win.Create().Size({ 500, 350 }));
	win.Show();
	Msg msg;
_ret:
	try {
		while (msg.Get()) {
			msg.Translate();
			msg.Dispatch();
		}
	}
	catch (...) {
		goto _ret;
	}
}

int main() {
	test_wnd();
	return 0;
}
