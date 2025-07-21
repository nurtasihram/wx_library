#include "wx_console.h"
#include "wx_realtime.h"
#include "wx_window.h"
#include "wx_control.h"

#include <typeinfo>

#include <regex>

using namespace WX;

//class BaseOf_Window(TestWindow) {
//	SFINAE_Window(TestWindow);
//public:
//	TestWindow() {}
//public:
//};

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
	template<bool IsUnicode = WX::IsUnicode>
	/* R */ inline StringX<IsUnicode> Name() const {
		global_symbolx(GetAtomName);
		auto lpsz = StringX<IsUnicode>::Alloc(MaxLenClass);
		int len;
		assertl((len = GetAtomName(self, lpsz, MaxLenClass)) > 0);
		StringX<IsUnicode>::Resize(lpsz, len);
		return { (size_t)len, lpsz };
	}
	/* R */ inline StringA NameA() const reflect_as(Name<false>());
	/* R */ inline StringW NameW() const reflect_as(Name<true>());
public:
	inline operator bool() const reflect_as(atom);
	inline operator ATOM() const reflect_as(atom);
	inline operator LPCSTR() const reflect_as(MAKEINTRESOURCEA(atom));
	inline operator LPCWSTR() const reflect_as(MAKEINTRESOURCEW(atom));
};

template<class TCHAR, class AnyEnum>
StringBase<TCHAR> EnumFlagsParse(AnyEnum e) {
	using EnumType = typename AnyEnum::EnumType;
	constexpr auto table = EnumTable<EnumType>;
	auto val = e.yield();
	if (val == 0)
		return EnumClassParse(val);
	for (auto i = 0; i < EnumType::Count; ++i)
		if (val == EnumType::__Vals[i])
			return table[i].key;
	if constexpr (EnumType::HasProtoEnum)
		 return EnumClassParse(reuse_as<typename EnumType::ProtoEnum>(e));
	else return format_numeral("d").toString<TCHAR>(val);
}

enum_class(EC1, int,
	Alfa = 1,
	Beta = 2,
	Gamma = 3);
enum_class(EC2, EC1,
	Delta = 4,
	Epsilon = 5,
	Yota = 6);

int main() {
	Console.Log(_T("Compilation Information:\n") COMPILATION_INFO);

	constexpr auto map = EnumTable<EC2>;
	for (size_t i = 0; i < map.Length; ++i)
		Console.Log(map[i].key, ':', map[i].val, '=', nX("08X", EC1::__Vals[i]), '\n');
	EC2 e = reuse_as<EC2>(EC1::Alfa);
	Console.LogA(EnumClassParseA(EC1::Alfa), '\n');
	Console.Log(EnumClassParse(e), '\n');

	//TestWindow wnd;
	//assertl(wnd.Create());
	//wnd.Show();
	//Console.Log(wnd.ModuleFileName());
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
