#include "wx_main"
#include "wx_realtime"
#include "wx_window"
#include "wx_control"
#include "wx_dialog"
#include "wx_console"

using namespace WX;

class BaseOf_Window(TestWindow) {
	SFINAE_Window(TestWindow);
	Button bnOpen, bnPlay, bnStop;
	Animate ani;
public:
	TestWindow() {}
protected:
	enum {
		BID_OPEN = 100,
		BID_PLAY,
		BID_STOP
	};
	inline bool OnCreate(LPCREATESTRUCT lpCreateStruct) {
		bnOpen
			.Create(self)
			.Styles(WS::Child | WS::Visible)
			.Position({ 10, 10 })
			.Size({ 50, 24 })
			.ID(BID_OPEN)
			.Caption(T("Open"));
		bnPlay
			.Create(self)
			.Styles(WS::Child | WS::Visible)
			.Position({ 70, 10 })
			.Size({ 50, 24 })
			.ID(BID_PLAY)
			.Caption(T("Play"));
		bnStop
			.Create(self)
			.Styles(WS::Child | WS::Visible)
			.Position({ 130, 10 })
			.Size({ 50, 24 })
			.ID(BID_STOP)
			.Caption(T("Stop"));
		ani
			.Create(self)
			.Styles(AnimateStyle::Transparent | AnimateStyle::AutoPlay | 
					WS::Child | WS::Visible | WS::Border)
			.Position({ 10, 44 })
			.Size({ 300, 200 });
		//txt.Show();
		return true;
	}
	inline int OnCommand(int id, HWND hwndCtl, UINT codeNotify) {
		switch (id) {
			case BID_OPEN: {
				String file(MaxLenPath);
				if (!DlgFile()
					.Styles(DlgFileStyle::FileMustExist | DlgFileStyle::Explorer)
					.File(file)
					.Owner(self)
					.Title(T("Select a animation file"))
					.Filter(T("AVI video file (*.avi)\0*.avi*\0\0"))
					.OpenFile()) {
					MsgBox(T("Error"), T("File select failed."), MB::IconError);
					return 0;
				}
				Console.Log(T("AVI file: "), file, '\n');
				if (!ani.Open((LPCTSTR)file))
					Console.Log(T("Open failed.\n"));
				break;
			}
			case BID_PLAY:
				if (!ani.Play())
					Console.Log(T("Play failed.\n"));
				break;
			case BID_STOP:
				if (!ani.Stop())
					Console.Log(T("Stop failed.\n"));
				break;
		}
		return 0;
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
		try {
			wnd.Create()
				.Size({ 350, 300 })
				.Caption(T("Common Controls"));
			wnd.Show();
			wnd.Update();
			Msg msg;
			while (msg.Get()) {
				msg.Translate();
				msg.Dispatch();
			}
		} catch (const Exception &err) {
			Console.Log(err, L'\n');
		} catch (...) {
			Console.Log(T("Unknown error\n"));
		}
	}
};

int WxMain() {
	Console.Title("WX - Tests");
	Console.Log(COMPILATION_INFO);
	TestWindow wnd;
	TestWindowMsgProc thd(wnd);
	thd.Create();
	thd.Wait();
	return thd.ExitCode();
}
