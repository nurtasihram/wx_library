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

class Rx {
	static constexpr bool __a_z(TCHAR w) reflect_as('a' <= w && w <= 'z');
	static constexpr bool __A_Z(TCHAR w) reflect_as('A' <= w && w <= 'Z');
	static constexpr bool __0_9(TCHAR w) reflect_as('0' <= w && w <= '9');
	static constexpr bool __A_z(TCHAR w) reflect_as(__a_z(w) || __A_Z(w));
	static constexpr bool _word(TCHAR w) reflect_as(__A_z(w) || __0_9(w));
	static constexpr bool _Word(TCHAR w) reflect_as(_word(w) || w == '_');
	static constexpr bool __s(TCHAR w) reflect_as(w == '\n' || w == '\r' || w == '\t' || w == ' ');
	class Token {
		friend class Rx;
		LPCTSTR lpsz;
		size_t len;
	public:
		constexpr Token() : lpsz(O), len(0) {}
		constexpr Token(LPCTSTR lpsz, LPCTSTR hpsz) : lpsz(lpsz), len(hpsz - lpsz) {}
		operator const String() const reflect_as(CString(len, lpsz));
	};
	struct Map { Token key, val; };
	template<size_t len>
	class Maps {
		friend class Rx;
		Map map[len];
	public:
		static constexpr size_t Length = len;
		constexpr Map operator[](size_t ind) const { return map[ind]; }
	};
	struct MapN { Map map; LPCTSTR hpsz; };
	static constexpr MapN _GetMap(LPCTSTR lpsz, size_t len) {
		LPCTSTR hpsz = lpsz;
		// skip blank
		for (; len; --len)
			if (__s(hpsz[0]))
				++hpsz;
			else
				break;
		// get key
		lpsz = hpsz;
		for (; len; --len)
			if (_Word(hpsz[0]))
				++hpsz;
			else
				break;
		Token key{ lpsz, hpsz };
		// skip blank
		for (; len; --len)
			if (__s(hpsz[0]))
				++hpsz;
			else
				break;
		// get equal
		if (hpsz[0] != '=')
			return{ {}, {} };
		++hpsz;
		// skip blank
		for (; len; --len)
			if (__s(hpsz[0]))
				++hpsz;
			else
				break;
		// get val
		lpsz = hpsz;
		for (; len; --len)
			if (_Word(hpsz[0]))
				++hpsz;
			else
				break;
		Token val{ lpsz, hpsz };
		// skip blank
		for (; len; --len)
			if (__s(hpsz[0]))
				++hpsz;
			else
				break;
		if (hpsz[0] == ',')
			++hpsz;
		return{ { key, val }, hpsz };
	}
	template<size_t count>
	static constexpr Maps<count> GetMaps(LPCTSTR lpsz, size_t len) {
		Maps<count> maps;
		for (size_t i = 0; i < count; ++i) {
			auto map = _GetMap(lpsz, len);
			len -= map.hpsz - lpsz;
			lpsz = map.hpsz;
			maps.map[i] = map.map;
		}
		return maps;
	}
public:
	template<class AnyEnum>
	static constexpr auto Maps = Rx::GetMaps<AnyEnum::Count>(AnyEnum::__Entries, CountOf(AnyEnum::__Entries));
	template<class AnyEnum>
	static constexpr auto Name = AnyEnum::__Name;
	template<class AnyEnum>
	static constexpr auto BaseName = AnyEnum::__BaseName;
};


int main() {
	constexpr auto map = Rx::Maps<WS>;
	for (size_t i = 0; i < map.Length; ++i)
		Console.Log(map[i].key, ':', map[i].val, '=', nX("08X", WS::__Vals(i)), '\n');
	//TestWindow wnd;
	//assertl(wnd.Create());
	//wnd.Show();
	//Console.Log(wnd.ModuleFileName());
	//Msg msg;
	//while (msg.Get()) {
	//	msg.Translate();
	//	msg.Dispatch();
	//}
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
