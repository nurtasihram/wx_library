#include "wx_main"
#include "wx_realtime"

using namespace WX;

//class BaseOf_Window(TestWindow) {
//	SFINAE_Window(TestWindow);
//public:
//	TestWindow() {}
//public:
//	inline bool OnCreate(LPCREATESTRUCT lpCreateStruct) {
//		return true;
//	}
//};
//int WxMain() {
//	TestWindow wnd;
//	wnd.Create();
//	wnd.Show();
//	wnd.Update();
//	Msg msg;
//	while (msg.Get()) {
//		msg.Translate();
//		msg.Dispatch();
//	}
//	rerurn 0;
//}

class BaseOf_Thread(TestThread) {
	SFINAE_Thread(TestThread);
public:
	TestThread() {}
protected:
	inline void OnRun() {
		for (int i = 0; i < 10; i++) {
			Console.Format(T("Thread running: %d\n"), i);
			Sleep(500);
		}
	}
};
int WxMain() {
	Console.Title("WX - Tests");
	Console.Log(COMPILATION_INFO);
	TestThread thd;
	assertl(thd.Create());
	thd.Wait();
	return 0;
}

//int WxMain() {
//	Console.Title("WX - Tests");
//	Console.Log(T("Hello world!\n"));
//	system("pause");
//	return 0;
//}
