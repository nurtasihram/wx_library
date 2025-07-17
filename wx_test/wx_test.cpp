#include "wx_console.h"
#include "wx_realtime.h"
#include "wx_window.h"
#include "wx_control.h"

#include <typeinfo>

#include <regex>

using namespace WX;

class BaseOf_Window(TestWindow) {
	SFINAE_Window(TestWindow);
public:
	TestWindow() {}
public:
};

class Atom {
	ATOM atom = 0;
public:
	Atom() {}
	Atom(Null) {}
	Atom(LPCSTR lpString) : atom(FindAtomA(lpString)) {}
	Atom(LPCWSTR lpString) : atom(FindAtomW(lpString)) {}
	Atom(ATOM atom) : atom(atom) {}
public:
	static inline Atom Find(LPCSTR lpString) assertl_reflect_as(auto atom = FindAtomA(lpString), atom);
	static inline Atom Find(LPCWSTR lpString) assertl_reflect_as(auto atom = FindAtomW(lpString), atom);
	inline void Delete() {
		if (atom)
			assertl_reflect_as(DeleteAtom(atom));
		atom = 0;
	}
public: // Property - Name
	/* R */ inline String Name() const {
		auto lpszAtomName = String::Alloc(MaxLenClass);
		int len = 0;
		assertl((len = GetAtomName(self, lpszAtomName, MaxLenClass)) > 0);
		lpszAtomName = String::Realloc(len, lpszAtomName);
		return { (size_t)len, lpszAtomName };
	}
	/* R */ inline StringA NameA() const {
		auto lpszAtomName = StringA::Alloc(MaxLenClass);
		int len = 0;
		assertl((len = GetAtomNameA(self, lpszAtomName, MaxLenClass)) > 0);
		lpszAtomName = StringA::Realloc(len, lpszAtomName);
		return { (size_t)len, lpszAtomName };
	}
	/* R */ inline StringW NameW() const {
		auto lpszAtomName = StringW::Alloc(MaxLenClass);
		int len = 0;
		assertl((len = GetAtomNameW(self, lpszAtomName, MaxLenClass)) > 0);
		lpszAtomName = StringW::Realloc(len, lpszAtomName);
		return { (size_t)len, lpszAtomName };
	}
public:
	inline operator bool() const reflect_as(atom);
	inline operator ATOM() const reflect_as(atom);
	inline operator LPCSTR() const reflect_as(MAKEINTRESOURCEA(atom));
	inline operator LPCWSTR() const reflect_as(MAKEINTRESOURCEW(atom));
};

template<class AnyClass, class...Args>
constexpr void plist() {
	Console.LogA(CString(typeid(AnyClass).name(), MaxLenClass), '\n');
	if constexpr (sizeof...(Args))
		plist<Args...>();
}

int main() {
	TestWindow wnd;
	assertl(wnd.Create());
	wnd.Show();
	Console.Log(wnd.ModuleFileName());
	Msg msg;
	while (msg.Get()) {
		msg.Translate();
		msg.Dispatch();
	}
	system("pause");
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					  _In_opt_ HINSTANCE hPrevInstance,
					  _In_ LPTSTR    lpCmdLine,
					  _In_ int       nCmdShow) {
	Console.Alloc();
	Console.Select();
	Console.Reopen();
	Console.Title(_T("Window X"));
	return main();
}
