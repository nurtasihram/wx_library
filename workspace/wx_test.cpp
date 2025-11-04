#include "wx_main"
#include "wx_realtime"
#include "wx_window"
//#include "wx_control"
#include "wx_console"

using namespace WX;

class BaseOf_Window(TestWindow) {
	SFINAE_Window(TestWindow);
//	Static txt;
public:
	TestWindow() {}
protected:
	inline bool OnCreate(LPCREATESTRUCT lpCreateStruct) {
		//txt.Create(self)
		//	.Styles(WS::Child | WS::Visible)
		//	.Position(10, 10)
		//	.Size(200, 20)
		//	.Text("Hello, WX!");
		return true;
	}
};

class BaseOf_Thread(TestWindowMsgProc) {
	SFINAE_Thread(TestWindowMsgProc);
private:
	TestWindow &wnd;
public:
	TestWindowMsgProc(TestWindow &window) : wnd(window) {}
protected:
	inline void OnRun() {
		wnd.Create();
		wnd.Show();
		wnd.Update();
		Msg msg;
		while (msg.Get()) {
			msg.Translate();
			msg.Dispatch();
		}
	}
};

int WxMain() {
	Console.Title("WX - Tests");
	Console.Log(COMPILATION_INFO);
	TestWindow wnd;
	TestWindowMsgProc thd = wnd;
	thd.Create();
	thd.Wait();
	return thd.ExitCode();
}
