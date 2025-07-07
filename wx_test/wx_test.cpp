#include "wx_console.h"
#include "wx_realtime.h"
#include "wx_window.h"

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
public:
	inline String Name() const {
		auto lpszAtomName = String::Alloc(MaxLenClass);
		int len = 0;
		assertl((len = GetAtomName(self, lpszAtomName, MaxLenClass)) > 0);
		lpszAtomName = String::Realloc(len, lpszAtomName);
		return { (size_t)len, lpszAtomName };
	}
public:
	inline operator ATOM() const reflect_as(atom);
};

template<class AnyClass, class...Args>
constexpr void plist() {
	Console.LogA(CString(typeid(AnyClass).name(), MaxLenClass), '\n');
	if constexpr (sizeof...(Args))
		plist<Args...>();
}

//template<class, class>
//struct Map;

//void test_check() {
//#define _CALL_(name) pThis->name
//#define MSG_TRANS(msgid, ret, name, argslist, args, send, call) \
//	case msgid: \
//		if constexpr (member_##name##_of<Child>::callable) { \
//			using fn_type = ret argslist; \
//			misdef_assert((member_##name##_of<Child>::template compatible_to<fn_type>), \
//							"Member " #name " must be a method compatible to " #ret #argslist); \
//			return call; \
//		} break;
//#include "wx_msg.inl"
//}


#pragma region Reuse & Convert List
template<class AnyProto, class AnyClass>
struct Reusable {
	static constexpr bool usable = false;
};
template<class AnyProto, class AnyClass>
struct Resuage {
	static constexpr bool usable = true;
	static inline AnyClass reuse(AnyProto Proto) reflect_as(reuse_as<AnyClass>(Proto));
	static inline AnyProto reuse(AnyClass Class) reflect_as(reuse_as<AnyClass>(Class));
};
#pragma endregion

template<>
struct Reusable<HWND, Window> : Resuage<HWND, Window> {};

int main() {

//	constexpr const a = std::is_class_v<to_proto<LPCREATESTRUCT>>;

	Console.LogA(typeid(to_proto<LPCREATESTRUCT>).name());

	plist<HDC, HFONT, char>();

	TestWindow wnd;
	assertl(wnd.Create());
	wnd.Show();

	auto &&r = Region::CreateElliptic({ 0, 0, 300, 300 });
	wnd.Region(r);
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
