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

void test_mf() {
	LPCWSTR pMessage = L"%1!*.*s! %4 %5!*s!";
	DWORD_PTR pArgs[] = { (DWORD_PTR)4, (DWORD_PTR)2, (DWORD_PTR)L"Bill",  // %1!*.*s! refers back to the first insertion string in pMessage
		 (DWORD_PTR)L"Bob",                                                // %4 refers back to the second insertion string in pMessage
		 (DWORD_PTR)6, (DWORD_PTR)L"Bill" };                               // %5!*s! refers back to the third insertion string in pMessage
	const DWORD size = 100 + 1;
	WCHAR buffer[size];

	if (!FormatMessage(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY,
					   pMessage,
					   0,
					   0,
					   buffer,
					   size,
					   (va_list *)pArgs)) {
		wprintf(L"Format message failed with 0x%x\n", GetLastError());
		return;
	}
	// Buffer contains "  Bi Bob   Bill".
	wprintf(L"Formatted message: '%s'\n", buffer);
}

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
