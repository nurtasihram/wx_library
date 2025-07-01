#pragma once

#include "wx_window.h"

namespace WX {

struct ConsoleCursorInf : public RefStruct<CONSOLE_CURSOR_INFO> {
public:
	ConsoleCursorInf() {}
	ConsoleCursorInf(const CONSOLE_CURSOR_INFO &cci) : RefStruct<CONSOLE_CURSOR_INFO>(cci) {}
public: // Property - Size
	/* W */ inline auto &Size(DWORD dwSize) reflect_to_self(self->dwSize = dwSize);
	/* R */ inline DWORD Size() const reflect_as(self->dwSize);
public: // Property - Visible
	/* W */ inline auto &Visible(BOOL bVisible) reflect_to_self(self->bVisible = bVisible);
	/* W */ inline bool Visible() reflect_as(self->bVisible);
};
struct ConsoleScreenBufferInf : public RefStruct<CONSOLE_SCREEN_BUFFER_INFO> {
public:
	ConsoleScreenBufferInf() {}
	ConsoleScreenBufferInf(const CONSOLE_SCREEN_BUFFER_INFO &csbi) :
		RefStruct<CONSOLE_SCREEN_BUFFER_INFO>(csbi) {}
public: // Property - Size
	/* W */ inline auto &Size(LSize size) reflect_to_self(self->dwSize = size);
	/* R */ inline LSize Size() const reflect_as(self->dwSize);
public: // Property - CursorPosition
	/* W */ inline auto &CursorPosition(LPoint pos) reflect_to_self(self->dwCursorPosition = COORD{ (SHORT)pos.x, (SHORT)pos.y });
	/* R */ inline LPoint CursorPosition() const reflect_as(self->dwCursorPosition);
public: // Property - Attribute
	/* W */ inline auto &Attribute(WORD wAttributes) reflect_to_self(self->wAttributes = wAttributes);
	/* R */ inline WORD Attribute() const reflect_as(self->wAttributes);
public: // Property - WindowRect
	/* W */ inline auto &WindowRect(LRect rc) reflect_to_self(self->srWindow = rc);
	/* R */ inline LRect WindowRect() const reflect_as(self->srWindow);
public: // Property - MaximumWindowSize
	/* W */ inline auto &MaximumWindowSize(LSize size) reflect_to_self(self->dwMaximumWindowSize = size);
	/* R */ inline LSize MaximumWindowSize() const reflect_as(self->dwMaximumWindowSize);
};
struct ConsoleScreenBufferInfEx : public RefStruct<CONSOLE_SCREEN_BUFFER_INFOEX> {
public:
	ConsoleScreenBufferInfEx() {}
	ConsoleScreenBufferInfEx(const CONSOLE_SCREEN_BUFFER_INFOEX &csbiex) :
		RefStruct<CONSOLE_SCREEN_BUFFER_INFOEX>(csbiex) {}
public: // Property - Size
	/* W */ inline auto &Size(LSize size) reflect_to_self(self->dwSize = size);
	/* R */ inline LSize Size() const reflect_as(self->dwSize);
public: // Property - CursorPosition
	/* W */ inline auto &CursorPosition(LPoint pos) reflect_to_self(self->dwCursorPosition = COORD{ (SHORT)pos.x, (SHORT)pos.y });
	/* R */ inline LPoint CursorPosition() const reflect_as(self->dwCursorPosition);
public: // Property - Attribute
	/* W */ inline auto &Attribute(WORD wAttributes) reflect_to_self(self->wAttributes = wAttributes);
	/* R */ inline WORD Attribute() const reflect_as(self->wAttributes);
public: // Property - WindowRect
	/* W */ inline auto &WindowRect(LRect rc) reflect_to_self(self->srWindow = rc);
	/* R */ inline LRect WindowRect() const reflect_as(self->srWindow);
public: // Property - MaximumWindowSize
	/* W */ inline auto &MaximumWindowSize(LSize size) reflect_to_self(self->dwMaximumWindowSize = size);
	/* R */ inline LSize MaximumWindowSize() const reflect_as(self->dwMaximumWindowSize);
public: // Property - PopupAttributes
	/* W */ inline auto &PopupAttributes(WORD wPopupAttributes) reflect_to_self(self->wPopupAttributes = wPopupAttributes);
	/* R */ inline WORD PopupAttributes() const reflect_as(self->wPopupAttributes);
public: // Property - FullscreenSupported
	/* W */ inline auto &FullscreenSupported(BOOL bFullscreenSupported) reflect_to_self(self->bFullscreenSupported = bFullscreenSupported);
	/* R */ inline bool  FullscreenSupported() const reflect_as(self->bFullscreenSupported);
public: // Property - ColorTable
	/* W */ inline auto &ColorTable(const COLORREF *lpColorTable) {
		for (int i = 0; i < 16; ++i)
			self->ColorTable[i] = lpColorTable[i];
		return *this;
	}
	/* R */ inline const COLORREF *ColorTable() const { return self->ColorTable; }
};
template<class AnyChild = void>
class ConsoleItf : public ChainExtend<ConsoleItf<AnyChild>, AnyChild> {
protected:
	HANDLE hInput = O, hOutput = O, hError = O;
public:
	using Child = KChain<ConsoleItf, AnyChild>;
	using CursorInf = ConsoleCursorInf;
	using ScreenBufferInf = ConsoleScreenBufferInf;
	using ScreenBufferInfEx = ConsoleScreenBufferInfEx;
public:
	ConsoleItf(Null) {}
	ConsoleItf() :
		hInput(GetStdHandle(STD_INPUT_HANDLE)),
		hOutput(GetStdHandle(STD_OUTPUT_HANDLE)),
		hError(GetStdHandle(STD_ERROR_HANDLE)) {}
	ConsoleItf(DWORD pid) reflect_to(Attach(pid));

	inline auto &Reopen() {
		hInput = GetStdHandle(STD_INPUT_HANDLE);
		hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		hError = GetStdHandle(STD_ERROR_HANDLE);
		retchild;
	}
	inline auto &Select() {
		static FILE *fout = O, *ferr = O, *fin = O;
		freopen_s(&fout, "CONOUT$", "w+t", stdout);
		freopen_s(&ferr, "CONERR$", "w+t", stderr);
		freopen_s(&fin, "CONIN$", "r+t", stdin);
		retchild;
	}
	inline auto &Clear() reflect_to_self(FillCharacter(_T(' '), ScreenBufferInfo().Size().Square()), CursorPosition(0));

#pragma region Allocator
	static inline void Attach(DWORD pid) assertl_reflect_as(AttachConsole(pid));
	static inline void Alloc() assertl_reflect_as(AllocConsole());
	static inline void Free() assertl_reflect_as(FreeConsole());
	static inline CWindow Window() reflect_as(GetConsoleWindow());
#pragma endregion

	inline void ActiveScreenBuffer() assertl_reflect_as(SetConsoleActiveScreenBuffer(hOutput));
	inline void FlushInputBuffer() assertl_reflect_as(FlushConsoleInputBuffer(hInput));

#pragma region Constants
	inline DWORD FillCharacter(TCHAR cCharacter, DWORD nLength, LPoint dwWriteCoord = 0) assertl_reflect_to(DWORD written = 0, FillConsoleOutputCharacter(hOutput, cCharacter, nLength, dwWriteCoord, &written), written);
	inline DWORD FillCharacterA(CHAR cCharacter, DWORD nLength, LPoint dwWriteCoord = 0) assertl_reflect_to(DWORD written = 0, FillConsoleOutputCharacterA(hOutput, cCharacter, nLength, dwWriteCoord, &written), written);
	inline DWORD FillCharacterW(WCHAR cCharacter, DWORD nLength, LPoint dwWriteCoord = 0) assertl_reflect_to(DWORD written = 0, FillConsoleOutputCharacterW(hOutput, cCharacter, nLength, dwWriteCoord, &written), written);
	inline DWORD FillAttribute(WORD wAttribute, DWORD nLength, LPoint dwWriteCoord = 0) assertl_reflect_to(DWORD written = 0, FillConsoleOutputAttribute(hOutput, wAttribute, nLength, dwWriteCoord, &written), written);
	inline DWORD WriteCharacter(LPCTSTR lpCharacters, DWORD nLength, LPoint dwWriteCoord = 0) assertl_reflect_to(DWORD written = 0, WriteConsoleOutputCharacter(hOutput, lpCharacters, nLength, dwWriteCoord, &written), written);
	inline DWORD WriteCharacterA(LPCSTR lpCharacters, DWORD nLength, LPoint dwWriteCoord = 0) assertl_reflect_to(DWORD written = 0, WriteConsoleOutputCharacterA(hOutput, lpCharacters, nLength, dwWriteCoord, &written), written);
	inline DWORD WriteCharacterW(LPCWSTR lpCharacters, DWORD nLength, LPoint dwWriteCoord = 0) assertl_reflect_to(DWORD written = 0, WriteConsoleOutputCharacterW(hOutput, lpCharacters, nLength, dwWriteCoord, &written), written);
	inline DWORD WriteAttribute(const WORD *lpAttributes, DWORD nLength, LPoint dwWriteCoord = 0) assertl_reflect_to(DWORD written = 0, WriteConsoleOutputAttribute(hOutput, lpAttributes, nLength, dwWriteCoord, &written), written);
//	inline String ReadCharacter(LPoint pos, LSize size) assertl_reflect_to(String s, ReadConsoleOutputCharacter(hOutput, s, size.Area(), pos, &size), s);
#pragma endregion

#pragma region Read Write
protected:
	inline DWORD _Write(HANDLE hOutput, LPCSTR lpszString, DWORD uLength) assertl_reflect_as(WriteConsoleA(hOutput, lpszString, uLength, &uLength, O), uLength);
	inline DWORD _Write(HANDLE hOutput, LPCWSTR lpszString, DWORD uLength) assertl_reflect_as(WriteConsoleW(hOutput, lpszString, uLength, &uLength, O), uLength);
public:
	inline DWORD Log(const String &s) reflect_as(_Write(hOutput, s, (DWORD)s.Length()));
	inline DWORD LogA(const StringA &s) reflect_as(_Write(hOutput, s, (DWORD)s.Length()));
	inline DWORD LogW(const StringW &s) reflect_as(_Write(hOutput, s, (DWORD)s.Length()));
public:
	template<class... Args>
	inline DWORD Log(const Args& ...args) reflect_as(Log(Cats(args...)));
	template<class... Args>
	inline DWORD LogA(const Args& ...args) reflect_as(LogA(CatsA(args...)));
	template<class... Args>
	inline DWORD LogW(const Args& ...args) reflect_as(LogW(CatsW(args...)));
public:
	inline DWORD Err(const String &s) reflect_as(_Write(hError, s, (DWORD)s.Length()));
	inline DWORD ErrA(const StringA &s) reflect_as(_Write(hError, s, (DWORD)s.Length()));
	inline DWORD ErrW(const StringW &s) reflect_as(_Write(hError, s, (DWORD)s.Length()));
public:
	template<class... Args>
	inline DWORD Err(const Args& ...args) reflect_as(Err(Cats(args...)));
	template<class... Args>
	inline DWORD ErrA(const Args& ...args) reflect_as(ErrA(CatsA(args...)));
	template<class... Args>
	inline DWORD ErrW(const Args& ...args) reflect_as(ErrW(CatsW(args...)));
public:
	inline auto &operator[](LPoint p) reflect_as(CursorPosition(p));
	inline auto &operator[](bool bCurVis) reflect_as(CursorVisible(bCurVis));
	template<class... Args>
	inline auto &operator()(const Args& ...args) reflect_to_child(Log(Cats(args...)));
#pragma endregion

#pragma region Properties
public: // Property - Title
	/* W */ inline auto  &Title(LPCSTR lpTitle) assertl_reflect_as_child(SetConsoleTitleA(lpTitle));
	/* W */ inline auto  &Title(LPCWSTR lpTitle) assertl_reflect_as_child(SetConsoleTitleW(lpTitle));
	/* R */ inline String Title() const {
		String title((size_t)MaxLenTitle);
		int len = GetConsoleTitle(title, MaxLenTitle + 1);
		if (len <= 0) return O;
		title.Resize(len);
		return title;
	}
	/* R */ inline StringA TitleA() const {
		StringA title((size_t)MaxLenTitle);
		int len = GetConsoleTitleA(title, MaxLenTitle + 1);
		if (len <= 0) return O;
		title.Resize(len);
		return title;
	}
	/* R */ inline StringW TitleW() const {
		StringW title((size_t)MaxLenTitle);
		int len = GetConsoleTitleW(title, MaxLenTitle + 1);
		if (len <= 0) return O;
		title.Resize(len);
		return title;
	}
public: // Property - OriginalTitle
	/* R */ inline StringA OriginalTitleA() const {
		StringA title((size_t)MaxLenTitle);
		int len = GetConsoleOriginalTitleA(title, MaxLenTitle + 1);
		if (len <= 0) return O;
		title.Resize(len);
		return title;
	}
	/* R */ inline StringW OriginalTitleW() const {
		StringW title((size_t)MaxLenTitle);
		int len = GetConsoleOriginalTitleW(title, MaxLenTitle + 1);
		if (len <= 0) return O;
		title.Resize(len);
		return title;
	}
	/* R */ inline String OriginalTitle() const {
		String title((size_t)MaxLenTitle);
		int len = GetConsoleOriginalTitle(title, MaxLenTitle + 1);
		if (len <= 0) return O;
		title.Resize(len);
		return title;
	}
public: // Property - CodePage
	/* W */ inline auto &CodePage(UINT uCodePage) assertl_reflect_as_child(SetConsoleOutputCP(uCodePage));
	/* R */ inline UINT  CodePage() const reflect_as(GetConsoleOutputCP());
public: // Property - ScreenBufferInfo
	/* R */ inline auto ScreenBufferInfo() const assertl_reflect_to(ScreenBufferInf sbi, GetConsoleScreenBufferInfo(hOutput, &sbi), sbi);
public: // Property - ScreenBufferInfoEx
	/* R */ inline auto ScreenBufferInfoEx() const assertl_reflect_to(ScreenBufferInfEx sbiex, GetConsoleScreenBufferInfoEx(hOutput, &sbiex), sbiex);
public: // Property - ScreenBufferSize
	/* W */ inline auto &ScreenBufferSize(LSize size) assertl_reflect_as_child(SetConsoleScreenBufferSize(hOutput, size));
	/* R */ inline LSize ScreenBufferSize() const reflect_as(ScreenBufferInfo().Size());
public: // Property - WindowSize
//	/* W */ inline auto &WindowSize(LRect rect) assertl_reflect_as_child(SetConsoleWindowInfo(hOutput, TRUE, ));
	/* R */ inline auto  WindowSize() const reflect_as(ScreenBufferInfo().WindowRect().size());
public: // Property - Attribute
	/* W */ inline auto &Attribute(WORD wAttr) assertl_reflect_as_child(SetConsoleTextAttribute(hOutput, wAttr));
	/* R */ inline WORD  Attribute() const reflect_as(ScreenBufferInfo().Attribute());
public: // Property - CursorInfo
	/* W */ inline auto &CursorInfo(const CONSOLE_CURSOR_INFO &cci) assertl_reflect_as_child(SetConsoleCursorInfo(hOutput, &cci));
	/* R */ inline auto  CursorInfo() const assertl_reflect_to(CursorInf ci, GetConsoleCursorInfo(hOutput, &ci), ci);
public: // Property - CursorPosition
	/* W */ inline auto &CursorPosition(LPoint p) assertl_reflect_as_child(SetConsoleCursorPosition(hOutput, COORD({ (short)p.x, (short)p.y })));
	/* R */ inline auto  CursorPosition() const reflect_as(ScreenBufferInfo().CursorPosition());
public: // Property - CurVis
	/* W */ inline auto &CursorVisible(bool bVisible) reflect_to_child(CursorInfo(*CursorInfo().Visible(bVisible)));
	/* R */ inline bool  CursorVisible() const reflect_as(CursorInfo().Visible());
#pragma endregion

};
static inline ConsoleItf<> Console;

class ConsoleCtl : public ConsoleItf<ConsoleCtl> {
public:
	~ConsoleCtl() reflect_to(Free());
};

}
