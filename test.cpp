#include "window.h"
#include "control.h"

using namespace WX;

ConsoleCtl con;

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
	ListView lv;
	inline bool OnCreate(RefAs<CreateStruct *> pCreate) {
		assertl(lv.Create(self).Size({ Size().cx, 400 }));
		return true;
	}
};

void test_wnd() {
	Wnd win;
	assertl(win.Create().Size({ 80, 500 }));
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
