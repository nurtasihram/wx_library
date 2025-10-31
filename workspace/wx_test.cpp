#include "wx_main"
#include "wx_realtime"
#include "wx_window"
#include "wx_console"

using namespace WX;

struct CommonEvent {
#define MSG_TRANS(msgid, ret, name, ...) \
	def_memberof(On##name);
#include "wx__msg.inl"
};

class BaseOf_Window(TestWindow) {
	SFINAE_Window(TestWindow);
public:
	TestWindow() {}
protected:
	inline bool OnCreate(LPCREATESTRUCT lpCreateStruct) {
		Console.Log(T("Alfa\n"));
		return true;
	}
};

template<class Type1, class Type2>
concept IsConvertibleTo = requires(Type1 a) {
	{ static_cast<Type2>(a) };
};

template<class Type1, class Type2>
	requires IsConvertibleTo<Type1, Type2>
inline auto add_if_convertible(Type1 a, Type2 b) {
	return a + b;
}

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
	auto p = add_if_convertible("A", 2);
	Console.Title("WX - Tests");
	Console.Log(COMPILATION_INFO);
	TestWindow wnd;
	TestWindowMsgProc thd = wnd;
	assertl(thd.Create());
	thd.Wait();
	return thd.ExitCode();
}
