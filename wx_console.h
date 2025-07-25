#pragma once

#include "wx_window.h"

namespace WX {

class ConsoleCursorInfo : public RefStruct<CONSOLE_CURSOR_INFO> {
public:
	using super = RefStruct<CONSOLE_CURSOR_INFO>;
public:
	ConsoleCursorInfo() {}
	ConsoleCursorInfo(const CONSOLE_CURSOR_INFO &cci) : super(cci) {}
public: // Property - Size
	/* W */ inline auto &Size(DWORD dwSize) reflect_to_self(self->dwSize = dwSize);
	/* R */ inline DWORD Size() const reflect_as(self->dwSize);
public: // Property - Visible
	/* W */ inline auto &Visible(BOOL bVisible) reflect_to_self(self->bVisible = bVisible);
	/* W */ inline bool Visible() reflect_as(self->bVisible);
};
class ConsoleScreenBufferInfo : public RefStruct<CONSOLE_SCREEN_BUFFER_INFO> {
public:
	using super = RefStruct<CONSOLE_SCREEN_BUFFER_INFO>;
public:
	ConsoleScreenBufferInfo() {}
	ConsoleScreenBufferInfo(const CONSOLE_SCREEN_BUFFER_INFO &csbi) : super(csbi) {}
public: // Property - Size
	/* W */ inline auto &Size(LSize size) reflect_to_self(self->dwSize = size);
	/* R */ inline LSize Size() const reflect_as(self->dwSize);
public: // Property - CursorPosition
	/* W */ inline auto &CursorPosition(LPoint pos) reflect_to_self(self->dwCursorPosition = COORD{ (SHORT)pos.x, (SHORT)pos.y });
	/* R */ inline LPoint CursorPosition() const reflect_as(self->dwCursorPosition);
public: // Property - Attributes
	/* W */ inline auto &Attributes(WORD wAttributes) reflect_to_self(self->wAttributes = wAttributes);
	/* R */ inline WORD Attributes() const reflect_as(self->wAttributes);
public: // Property - WindowRect
	/* W */ inline auto &WindowRect(LRect rc) reflect_to_self(self->srWindow = rc);
	/* R */ inline LRect WindowRect() const reflect_as(self->srWindow);
public: // Property - MaximumWindowSize
	/* W */ inline auto &MaximumWindowSize(LSize size) reflect_to_self(self->dwMaximumWindowSize = size);
	/* R */ inline LSize MaximumWindowSize() const reflect_as(self->dwMaximumWindowSize);
};
class ConsoleScreenBufferInfoEx : public RefStruct<CONSOLE_SCREEN_BUFFER_INFOEX> {
public:
	using super = RefStruct<CONSOLE_SCREEN_BUFFER_INFOEX>;
public:
	ConsoleScreenBufferInfoEx() reflect_to(self->cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX));
	ConsoleScreenBufferInfoEx(const CONSOLE_SCREEN_BUFFER_INFOEX &csbiex) : super(csbiex) {}
public: // Property - Size
	/* W */ inline auto &Size(LSize size) reflect_to_self(self->dwSize = size);
	/* R */ inline LSize Size() const reflect_as(self->dwSize);
public: // Property - CursorPosition
	/* W */ inline auto &CursorPosition(LPoint pos) reflect_to_self(self->dwCursorPosition = COORD{ (SHORT)pos.x, (SHORT)pos.y });
	/* R */ inline LPoint CursorPosition() const reflect_as(self->dwCursorPosition);
public: // Property - Attributes
	/* W */ inline auto &Attributes(WORD wAttributes) reflect_to_self(self->wAttributes = wAttributes);
	/* R */ inline WORD Attributes() const reflect_as(self->wAttributes);
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
class ConsoleItf : public ChainExtender<ConsoleItf<AnyChild>, AnyChild> {
protected:
	HANDLE hInput = O, hOutput = O, hError = O;
public:
	using Child = Chain<ConsoleItf, AnyChild>;
public:
	ConsoleItf(Null) {}
	ConsoleItf() :
		hInput(GetStdHandle(STD_INPUT_HANDLE)),
		hOutput(GetStdHandle(STD_OUTPUT_HANDLE)),
		hError(GetStdHandle(STD_ERROR_HANDLE)) {}
	ConsoleItf(DWORD pid) reflect_to(Attach(pid));
public:
	static inline void Attach(DWORD pid) assertl_reflect_as(AttachConsole(pid));
	static inline void Alloc() assertl_reflect_as(AllocConsole());
	static inline void Free() assertl_reflect_as(FreeConsole());
public:
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
	inline auto &Clear() reflect_to_self(Fill(_T(' '), ScreenBufferInfo().Size().Square()), CursorPosition(0));
	inline auto &Color(WORD wAttributes) reflect_to_self(FillAttributes(wAttributes, ScreenBufferInfo().Size().Square()), Attributes(wAttributes));
public:
	inline void ActiveScreenBuffer() assertl_reflect_as(SetConsoleActiveScreenBuffer(hOutput));
	inline void FlushInputBuffer() assertl_reflect_as(FlushConsoleInputBuffer(hInput));
public:
	template<class TCHAR>
	inline DWORD Fill(TCHAR cCharacter, DWORD nLength, LPoint dwWriteCoord = 0) {
		constexpr bool IsUnicode = IsCharW<TCHAR>;
		global_symbolx(FillConsoleOutputCharacter);
		assertl_reflect_to(DWORD written = 0, FillConsoleOutputCharacter(hOutput, cCharacter, nLength, dwWriteCoord, &written), written);
	}
	inline DWORD FillAttributes(WORD wAttributes, DWORD nLength, LPoint dwWriteCoord = 0) assertl_reflect_to(DWORD written = 0, FillConsoleOutputAttribute(hOutput, wAttributes, nLength, dwWriteCoord, &written), written);
	template<class TCHAR>
	inline DWORD Write(const TCHAR *lpszString, DWORD nLength) {
		constexpr bool IsUnicode = IsCharW<TCHAR>;
		global_symbolx(WriteConsole);
		assertl_reflect_as(WriteConsole(hOutput, lpszString, nLength, &nLength, O), nLength);
	}
	template<class TCHAR>
	inline DWORD Write(const StringBase<TCHAR> &str) reflect_as(Write((const TCHAR *)str, (DWORD)str.Length()));
	template<class TCHAR>
	inline DWORD Write(const TCHAR *lpszString, DWORD nLength, LPoint dwWriteCoord) {
		constexpr bool IsUnicode = IsCharW<TCHAR>;
		global_symbolx(WriteConsoleOutputCharacter);
		assertl_reflect_to(DWORD written = 0, WriteConsoleOutputCharacter(hOutput, lpszString, nLength, dwWriteCoord, &written), written);
	}
	template<class TCHAR>
	inline DWORD Write(const StringBase<TCHAR> &str, LPoint dwWriteCoord) reflect_as(Write((const TCHAR *)str, (DWORD)str.Length(), dwWriteCoord));
	inline DWORD WriteAttributes(const WORD *lpAttributes, DWORD nLength, LPoint dwWriteCoord = 0) assertl_reflect_to(DWORD written = 0, WriteConsoleOutputAttribute(hOutput, lpAttributes, nLength, dwWriteCoord, &written), written);
//	inline String ReadCharacter(LPoint pos, LSize size) assertl_reflect_to(String s, ReadConsoleOutputCharacter(hOutput, s, size.Area(), pos, &size), s);
public:
	template<class... Args>
	inline DWORD Log(const Args& ...args) reflect_as(Write(Cats(args...)));
	template<class... Args>
	inline DWORD LogA(const Args& ...args) reflect_as(Write<CHAR>(CatsA(args...)));
	template<class... Args>
	inline DWORD LogW(const Args& ...args) reflect_as(Write<WCHAR>(CatsW(args...)));
public:
	template<class... Args>
	inline DWORD Err(const Args& ...args) reflect_as(Write(Cats(args...)));
	template<class... Args>
	inline DWORD ErrA(const Args& ...args) reflect_as(Write<CHAR>(CatsA(args...)));
	template<class... Args>
	inline DWORD ErrW(const Args& ...args) reflect_as(Write<WCHAR>(CatsW(args...)));
#pragma region Properties
public: // Property - Title
	template<class TCHAR>
	/* W */ inline auto &Title(const TCHAR *lpTitle) {
		constexpr bool IsUnicode = IsCharW<TCHAR>;
		global_symbolx(SetConsoleTitle);
		assertl_reflect_as_child(SetConsoleTitle(lpTitle));
	}
	template<bool IsUnicode = WX::IsUnicode>
	/* R */ inline StringX<IsUnicode> Title() const {
		global_symbolx(GetConsoleTitle);
		auto lpsz = StringX<IsUnicode>::Alloc(MaxLenTitle);
		int len;
		assertl((len = GetConsoleTitle(lpsz, MaxLenTitle)) > 0);
		StringX<IsUnicode>::Resize(lpsz, len);
		return{ (size_t)len, lpsz };
	}
	/* R */ inline StringA TitleA() const reflect_as(Title<false>());
	/* R */ inline StringW TitleW() const reflect_as(Title<true>());
public: // Property - OriginalTitle
	template<bool IsUnicode = WX::IsUnicode>
	/* R */ inline StringX<IsUnicode> OriginalTitle() const {
		global_symbolx(GetConsoleOriginalTitle);
		auto lpsz = StringX<IsUnicode>::Alloc(MaxLenTitle);
		int len;
		assertl((len = GetConsoleOriginalTitle(lpsz, MaxLenTitle)) > 0);
		StringX<IsUnicode>::Resize(lpsz, len);
		return{ (size_t)len, lpsz };
	}
	/* R */ inline StringA OriginalTitleA() const reflect_as(OriginalTitle<false>());
	/* R */ inline StringW OriginalTitleW() const reflect_as(OriginalTitle<true>());
public: // 
	static inline CWindow Window() reflect_as(GetConsoleWindow());
public: // Property - CodePage
	/* W */ inline auto &CodePage(UINT uCodePage) assertl_reflect_as_child(SetConsoleOutputCP(uCodePage));
	/* R */ inline UINT  CodePage() const reflect_as(GetConsoleOutputCP());
public: // Property - ScreenBufferInfo
	/* R */ inline auto ScreenBufferInfo() const assertl_reflect_to(ConsoleScreenBufferInfo sbi, GetConsoleScreenBufferInfo(hOutput, &sbi), sbi);
public: // Property - ScreenBufferInfoEx
	/* R */ inline auto ScreenBufferInfoEx() const assertl_reflect_to(ConsoleScreenBufferInfoEx sbiex, GetConsoleScreenBufferInfoEx(hOutput, &sbiex), sbiex);
public: // Property - ScreenBufferSize
	/* W */ inline auto &ScreenBufferSize(LSize size) assertl_reflect_as_child(SetConsoleScreenBufferSize(hOutput, size));
	/* R */ inline LSize ScreenBufferSize() const reflect_as(ScreenBufferInfo().Size());
public: // Property - WindowSize
//	/* W */ inline auto &WindowSize(LRect rect) assertl_reflect_as_child(SetConsoleWindowInfo(hOutput, TRUE, ));
	/* R */ inline auto  WindowSize() const reflect_as(ScreenBufferInfo().WindowRect().size());
public: // Property - Attributes
	/* W */ inline auto &Attributes(WORD wAttributes) assertl_reflect_as_child(SetConsoleTextAttribute(hOutput, wAttributes));
	/* R */ inline WORD  Attributes() const reflect_as(ScreenBufferInfo().Attributes());
public: // Property - CursorInfo
	/* W */ inline auto &CursorInfo(const CONSOLE_CURSOR_INFO &cci) assertl_reflect_as_child(SetConsoleCursorInfo(hOutput, &cci));
	/* R */ inline auto  CursorInfo() const assertl_reflect_to(ConsoleCursorInfo ci, GetConsoleCursorInfo(hOutput, &ci), ci);
public: // Property - CursorPosition
	/* W */ inline auto &CursorPosition(LPoint p) assertl_reflect_as_child(SetConsoleCursorPosition(hOutput, COORD({ (short)p.x, (short)p.y })));
	/* R */ inline auto  CursorPosition() const reflect_as(ScreenBufferInfo().CursorPosition());
public: // Property - CurVis
	/* W */ inline auto &CursorVisible(bool bVisible) reflect_to_child(CursorInfo(*CursorInfo().Visible(bVisible)));
	/* R */ inline bool  CursorVisible() const reflect_as(CursorInfo().Visible());
#pragma endregion
public:
	inline auto &operator[](LPoint p) reflect_as(CursorPosition(p));
	inline auto &operator[](bool bCurVis) reflect_as(CursorVisible(bCurVis));
	template<class... Args>
	inline auto &operator()(const Args& ...args) reflect_to_child(Log(Cats(args...)));
};
static inline ConsoleItf<> Console;
class ConsoleCtl : public ConsoleItf<ConsoleCtl> {
public:
	~ConsoleCtl() reflect_to(Free());
};

}
