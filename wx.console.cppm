module;

#define WX_CPPM_CONSOLE
#include "wx_console"

#include <WinCon.h>
#include <stdio.h>

#include "wx__conio.inl"

export module wx.console;

import wx.proto;

export namespace WX {

enum_flags(ConsoleAttribute, WORD,
	ForegroundBlue      = FOREGROUND_BLUE,
	ForegroundGreen     = FOREGROUND_GREEN,
	ForegroundRed       = FOREGROUND_RED,
	ForegroundIntensity = FOREGROUND_INTENSITY,
	BackgroundBlue      = BACKGROUND_BLUE,
	BackgroundGreen     = BACKGROUND_GREEN,
	BackgroundRed       = BACKGROUND_RED,
	BackgroundIntensity = BACKGROUND_INTENSITY,
	// Other Colors //
	ForegroundBlack       = 0,
	ForegroundAqua        = FOREGROUND_GREEN | FOREGROUND_BLUE,
	ForegroundPurple      = FOREGROUND_RED | FOREGROUND_BLUE,
	ForegroundYellow      = FOREGROUND_RED | FOREGROUND_GREEN,
	ForegroundWhite       = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	ForegroundGray        = FOREGROUND_INTENSITY,
	ForegroundLightBlue   = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	ForegroundLightGreen  = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	ForegroundLightAqua   = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	ForegroundLightRed    = FOREGROUND_RED | FOREGROUND_INTENSITY,
	ForegroundLightPurple = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	ForegroundLightYellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	ForegroundBrightWhite = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	BackgroundBlack       = 0,
	BackgroundAqua        = BACKGROUND_GREEN | BACKGROUND_BLUE,
	BackgroundPurple      = BACKGROUND_RED | BACKGROUND_BLUE,
	BackgroundYellow      = BACKGROUND_RED | BACKGROUND_GREEN,
	BackgroundWhite       = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	BackgroundGray        = BACKGROUND_INTENSITY,
	BackgroundLightBlue   = BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BackgroundLightGreen  = BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	BackgroundLightAqua   = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BackgroundLightRed    = BACKGROUND_RED | BACKGROUND_INTENSITY,
	BackgroundLightPurple = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BackgroundLightYellow = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	BackgroundBrightWhite = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
   	// Aliases //
	Blue       = FOREGROUND_BLUE,
	Green      = FOREGROUND_GREEN,
	Red        = FOREGROUND_RED,
	Gray       = FOREGROUND_INTENSITY,
	BkBlue     = BACKGROUND_BLUE,
	BkGreen    = BACKGROUND_GREEN,
	BkRed      = BACKGROUND_RED,
	BkGray     = BACKGROUND_INTENSITY,
	// Aliases Other Colors //
	Black         = 0,
	Aqua          = FOREGROUND_GREEN | FOREGROUND_BLUE,
	Purple        = FOREGROUND_RED | FOREGROUND_BLUE,
	Yellow        = FOREGROUND_RED | FOREGROUND_GREEN,
	White         = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	LightBlue     = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	LightGreen    = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	LightAqua     = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	LightRed      = FOREGROUND_RED | FOREGROUND_INTENSITY,
	LightPurple   = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	LightYellow   = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	BrightWhite   = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	BkBlack       = 0,
	BkAqua        = BACKGROUND_GREEN | BACKGROUND_BLUE,
	BkPurple      = BACKGROUND_RED | BACKGROUND_BLUE,
	BkYellow      = BACKGROUND_RED | BACKGROUND_GREEN,
	BkWhite       = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	BkLightBlue   = BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BkLightGreen  = BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	BkLightAqua   = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BkLightRed    = BACKGROUND_RED | BACKGROUND_INTENSITY,
	BkLightPurple = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BkLightYellow = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	BkBrightWhite = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,	
	// Mask //
	Foreground = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Background = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
using ConsoleColor = ConsoleAttribute;

enum_flags(ConsoleSelectionFlag, DWORD,
	No             = CONSOLE_NO_SELECTION,
	InProgress     = CONSOLE_SELECTION_IN_PROGRESS,
	NotEmpty       = CONSOLE_SELECTION_NOT_EMPTY,
	MouseSelection = CONSOLE_MOUSE_SELECTION,
	MouseDown      = CONSOLE_MOUSE_DOWN);
class ConsoleSelectionInfo : public RefStruct<CONSOLE_SELECTION_INFO> {
public:
	using super = RefStruct<CONSOLE_SELECTION_INFO>;
public:
	ConsoleSelectionInfo() {}
	ConsoleSelectionInfo(const CONSOLE_SELECTION_INFO &csi) : super(csi) {}
public: // Property - Flags
	/* W */ inline auto &Flags(ConsoleSelectionFlag flags) reflect_to_self(self->dwFlags = flags.yield());
	/* R */ inline auto  Flags() const reflect_as(reuse_as<ConsoleSelectionFlag>(self->dwFlags));
public: // Property - Anchor
	/* W */ inline auto &Anchor(LPoint pos) reflect_to_self(self->dwSelectionAnchor = COORD{ (SHORT)pos.x, (SHORT)pos.y });
	/* R */ inline LPoint Anchor() const reflect_as(self->dwSelectionAnchor);
public: // Property - Rect
	/* W */ inline auto &Rect(LRect rc) reflect_to_self(self->srSelection = rc);
	/* R */ inline LRect Rect() const reflect_as(self->srSelection);
};
class ConsoleHistoryInfo : public RefStruct<CONSOLE_HISTORY_INFO> {
public:
	using super = RefStruct<CONSOLE_HISTORY_INFO>;
public:
	ConsoleHistoryInfo() reflect_to(self->cbSize = sizeof(CONSOLE_HISTORY_INFO));
	ConsoleHistoryInfo(const CONSOLE_HISTORY_INFO &chi) : super(chi) {}
public: // Property - BufferSize
	/* W */ inline auto &BufferSize(UINT dwSize) reflect_to_self(self->HistoryBufferSize = dwSize);
	/* R */ inline UINT  BufferSize() const reflect_as(self->HistoryBufferSize);
public: // Property - NumberOfBuffers
	/* W */ inline auto &NumberOfBuffers(UINT dwSize) reflect_to_self(self->HistoryBufferSize = dwSize);
	/* R */ inline UINT  NumberOfBuffers() const reflect_as(self->HistoryBufferSize);
public: // Property - NoDuplication
	/* W */ inline auto &NoDuplication(bool bNoDup) {
		if (bNoDup)
			self->dwFlags |= HISTORY_NO_DUP_FLAG;
		else
			self->dwFlags &= ~HISTORY_NO_DUP_FLAG;
		retself;
	}
	/* R */ inline bool NoDuplication() const reflect_as(self->dwFlags & HISTORY_NO_DUP_FLAG);
};
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
	using Attribute = ConsoleAttribute;
public:
	ConsoleScreenBufferInfo() {}
	ConsoleScreenBufferInfo(const CONSOLE_SCREEN_BUFFER_INFO &csbi) : super(csbi) {}
public: // Property - Size
	/* W */ inline auto &Size(LSize size) reflect_to_self(self->dwSize = size);
	/* R */ inline LSize Size() const reflect_as(self->dwSize);
public: // Property - CursorPosition
	/* W */ inline auto  &CursorPosition(LPoint pos) reflect_to_self(self->dwCursorPosition = COORD{ (SHORT)pos.x, (SHORT)pos.y });
	/* R */ inline LPoint CursorPosition() const reflect_as(self->dwCursorPosition);
public: // Property - Attributes
	/* W */ inline auto&Attributes(Attribute wAttributes) reflect_to_self(self->wAttributes = wAttributes.yield());
	/* R */ inline auto Attributes() const reflect_as(reuse_as<Attribute>(self->wAttributes));
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
	using Attribute = ConsoleAttribute;
public:
	ConsoleScreenBufferInfoEx() reflect_to(self->cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX));
	ConsoleScreenBufferInfoEx(const CONSOLE_SCREEN_BUFFER_INFOEX &csbiex) : super(csbiex) {}
public: // Property - Size
	/* W */ inline auto &Size(LSize size) reflect_to_self(self->dwSize = size);
	/* R */ inline LSize Size() const reflect_as(self->dwSize);
public: // Property - CursorPosition
	/* W */ inline auto  &CursorPosition(LPoint pos) reflect_to_self(self->dwCursorPosition = COORD{ (SHORT)pos.x, (SHORT)pos.y });
	/* R */ inline LPoint CursorPosition() const reflect_as(self->dwCursorPosition);
public: // Property - Attributes
	/* W */ inline auto&Attributes(Attribute wAttributes) reflect_to_self(self->wAttributes = wAttributes.yield());
	/* R */ inline auto Attributes() const reflect_as(reuse_as<Attribute>(self->wAttributes));
public: // Property - WindowRect
	/* W */ inline auto &WindowRect(LRect rc) reflect_to_self(self->srWindow = rc);
	/* R */ inline LRect WindowRect() const reflect_as(self->srWindow);
public: // Property - MaximumWindowSize
	/* W */ inline auto &MaximumWindowSize(LSize size) reflect_to_self(self->dwMaximumWindowSize = size);
	/* R */ inline LSize MaximumWindowSize() const reflect_as(self->dwMaximumWindowSize);
public: // Property - PopupAttributes
	/* W */ inline auto&PopupAttributes(Attribute wPopupAttributes) reflect_to_self(self->wPopupAttributes = wPopupAttributes.yield());
	/* R */ inline auto PopupAttributes() const reflect_as(reuse_as<Attribute>(self->wPopupAttributes));
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

enum_flags(ConsoleMode, DWORD,
	// Input modes
	InputProcessed			 = ENABLE_PROCESSED_INPUT,
	InputLine				 = ENABLE_LINE_INPUT,
	InputEcho				 = ENABLE_ECHO_INPUT,
	InputWindow				 = ENABLE_WINDOW_INPUT,
	InputMouse				 = ENABLE_MOUSE_INPUT,
	InputInsertMode			 = ENABLE_INSERT_MODE,
	InputQuickEdit			 = ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS,
	InputQuickEditDisable	 = ENABLE_EXTENDED_FLAGS,
	AutoPosition			 = ENABLE_AUTO_POSITION,
	// Output modes
	OutputProcessed			 = ENABLE_PROCESSED_OUTPUT,
	OutputWrapAtEol			 = ENABLE_WRAP_AT_EOL_OUTPUT,
	OutputVirtualTerminal	 = ENABLE_VIRTUAL_TERMINAL_PROCESSING,
	OutputLvbGridWorldwide	 = ENABLE_LVB_GRID_WORLDWIDE);
template<class AnyChild = void>
class ConsoleItf : public ChainExtender<ConsoleItf<AnyChild>, AnyChild> {
protected:
	HANDLE hInput = O, hOutput = O, hError = O;
public:
	using Child = Chain<ConsoleItf, AnyChild>;
	using Attribute = ConsoleAttribute;
	using Mode = ConsoleMode;
public:
	ConsoleItf(Null) {}
	ConsoleItf() :
		hInput(WX::GetStdHandle(STD_INPUT_HANDLE)),
		hOutput(WX::GetStdHandle(STD_OUTPUT_HANDLE)),
		hError(WX::GetStdHandle(STD_ERROR_HANDLE)) {}
	ConsoleItf(DWORD pid) reflect_to(Attach(pid));
public:
	static inline void Attach(DWORD pid) reflect_to(WX::AttachConsole(pid));
	static inline void Alloc() reflect_to(WX::AllocConsole());
	static inline void Free() reflect_to(WX::FreeConsole());
public:
	inline auto &Reopen() {
		hInput = WX::GetStdHandle(STD_INPUT_HANDLE);
		hOutput = WX::GetStdHandle(STD_OUTPUT_HANDLE);
		hError = WX::GetStdHandle(STD_ERROR_HANDLE);
		retchild;
	}
	inline auto &Select() {
		static FILE *fout = O, *ferr = O, *fin = O;
		freopen_s(&fout, "CONOUT$", "w+t", stdout);
		freopen_s(&ferr, "CONERR$", "w+t", stderr);
		freopen_s(&fin, "CONIN$", "r+t", stdin);
		retchild;
	}
	inline auto &Clear() reflect_to_self(Fill(T(' '), ScreenBufferInfo().Size().Square()), CursorPosition(0));
	inline auto &Color(WORD wAttributes) reflect_to_self(FillAttributes(wAttributes, ScreenBufferInfo().Size().Square()), Attributes(wAttributes));
	inline auto &Color(Attribute wAttributes) reflect_to_self(Color(wAttributes.yield()));

	inline void ActiveScreenBuffer() reflect_to(WX::SetConsoleActiveScreenBuffer(hOutput));
	inline void FlushInputBuffer() reflect_to(WX::FlushConsoleInputBuffer(hInput));

	inline DWORD Fill(CHAR cCharacter, DWORD nLength, LPoint dwWriteCoord = 0)
		reflect_as(WX::FillConsoleOutputCharacter(hOutput, cCharacter, nLength, dwWriteCoord, &nLength), nLength);
	inline DWORD Fill(WCHAR cCharacter, DWORD nLength, LPoint dwWriteCoord = 0)
		reflect_as(WX::FillConsoleOutputCharacter(hOutput, cCharacter, nLength, dwWriteCoord, &nLength), nLength);

	inline DWORD FillAttributes(WORD wAttributes, DWORD nLength, LPoint dwWriteCoord = 0)
		reflect_as(WX::FillConsoleOutputAttribute(hOutput, wAttributes, nLength, dwWriteCoord, &nLength), nLength);
	inline DWORD FillAttributes(Attribute wAttributes, DWORD nLength, LPoint dwWriteCoord = 0)
		reflect_as(FillAttributes(wAttributes.yield(), nLength, dwWriteCoord));

	inline DWORD Write(LPCSTR lpszString, DWORD nLength)
		reflect_as(WriteConsole<false>(hOutput, lpszString, nLength, &nLength, O), nLength);
	inline DWORD Write(LPCWSTR lpszString, DWORD nLength)
		reflect_as(WriteConsole<true>(hOutput, lpszString, nLength, &nLength, O), nLength);

	inline DWORD Write(const StringA &str)
		reflect_as(Write((LPCSTR)str, (DWORD)str.Length()));
	inline DWORD Write(const StringW &str)
		reflect_as(Write((LPCWSTR)str, (DWORD)str.Length()));

	inline DWORD Write(LPCSTR lpszString, DWORD nLength, LPoint dwWriteCoord)
		reflect_as(WX::WriteConsoleOutputCharacter(hOutput, lpszString, nLength, dwWriteCoord, &nLength), nLength);
	inline DWORD Write(LPCWSTR lpszString, DWORD nLength, LPoint dwWriteCoord)
		reflect_as(WX::WriteConsoleOutputCharacter(hOutput, lpszString, nLength, dwWriteCoord, &nLength), nLength);

	template<size_t len>
	inline DWORD Write(const CHAR (&lpszString)[len], LPoint dwWriteCoord)
		reflect_as(Write(lpszString, (DWORD)(len - 1), dwWriteCoord));
	template<size_t len>
	inline DWORD Write(const WCHAR (&lpszString)[len], LPoint dwWriteCoord)
		reflect_as(Write(lpszString, (DWORD)(len - 1), dwWriteCoord));

	inline DWORD Write(const StringA &str, LPoint dwWriteCoord)
		reflect_as(Write((LPCSTR)str, (DWORD)str.Length(), dwWriteCoord));
	inline DWORD Write(const StringW &str, LPoint dwWriteCoord)
		reflect_as(Write((LPCWSTR)str, (DWORD)str.Length(), dwWriteCoord));

	inline DWORD WriteAttributes(const WORD *lpAttributes, DWORD nLength, LPoint dwWriteCoord = 0)
		reflect_as(WX::WriteConsoleOutputAttribute(hOutput, lpAttributes, nLength, dwWriteCoord, &nLength), nLength);
	inline DWORD WriteAttributes(const Attribute *lpAttributes, DWORD nLength, LPoint dwWriteCoord = 0)
		reflect_as(WriteAttributes((const WORD *)lpAttributes, nLength, dwWriteCoord));

	template<size_t len>
	inline DWORD WriteAttributes(const WORD(&lpAttributes)[len], LPoint dwWriteCoord = 0)
		reflect_as(WriteAttributes(lpAttributes, (DWORD)len, dwWriteCoord));
	template<size_t len>
	inline DWORD WriteAttributes(const Attribute (&lpAttributes)[len], LPoint dwWriteCoord = 0)
		reflect_as(WriteAttributes((const WORD *)lpAttributes, (DWORD)len, dwWriteCoord));
public:
	template<class... Args>
	inline DWORD Log(const Args& ...args) reflect_as(Write(Cats(args...)));
	template<class... Args>
	inline DWORD LogA(const Args& ...args) reflect_as(Write(CatsA(args...)));
	template<class... Args>
	inline DWORD LogW(const Args& ...args) reflect_as(Write(CatsW(args...)));
public:
	template<class... Args>
	inline DWORD Err(const Args& ...args) reflect_as(Write(Cats(args...)));
	template<class... Args>
	inline DWORD ErrA(const Args& ...args) reflect_as(Write(CatsA(args...)));
	template<class... Args>
	inline DWORD ErrW(const Args& ...args) reflect_as(Write(CatsW(args...)));
public:
	inline DWORD Format(LPCSTR lpFormat, ...) {
		va_list argList;
		va_start(argList, lpFormat);
		auto bytes = Write(format(lpFormat, argList));
		va_end(argList);
		return bytes;
	}
	inline DWORD Format(LPCWSTR lpFormat, ...) {
		va_list argList;
		va_start(argList, lpFormat);
		auto bytes = Write(format(lpFormat, argList));
		va_end(argList);
		return bytes;
	}
#pragma region Properties
public: // Property - Title
	template<class TCHAR>
	/* W */ static inline void Title(const TCHAR *lpTitle) reflect_to(WX::SetConsoleTitle(lpTitle));
	template<bool IsUnicode = WX::IsUnicode>
	/* R */ static inline StringX<IsUnicode> Title() {
		auto lpsz = StringX<IsUnicode>::Alloc(MaxLenTitle);
		auto len = WX::GetConsoleTitle(lpsz, MaxLenTitle);
		StringX<IsUnicode>::Resize(lpsz, len);
		return{ (size_t)len, lpsz };
	}
	/* R */ static inline StringA TitleA() reflect_as(Title<false>());
	/* R */ static inline StringW TitleW() reflect_as(Title<true>());
public: // Property - OriginalTitle
	template<bool IsUnicode = WX::IsUnicode>
	/* R */ static inline StringX<IsUnicode> OriginalTitle() {
		auto lpsz = StringX<IsUnicode>::Alloc(MaxLenTitle);
		auto len = WX::GetConsoleOriginalTitle(lpsz, MaxLenTitle);
		StringX<IsUnicode>::Resize(lpsz, len);
		return{ (size_t)len, lpsz };
	}
	/* R */ static inline StringA OriginalTitleA() reflect_as(OriginalTitle<false>());
	/* R */ static inline StringW OriginalTitleW() reflect_as(OriginalTitle<true>());
//public: // Property - Window
//	static inline CWindow Window() reflect_as(WX::GetConsoleWindow());
public: // Property - CodePage
	/* W */ static inline void CodePage(UINT uCodePage) reflect_to(WX::SetConsoleCP(uCodePage));
	/* R */ static inline UINT CodePage() reflect_as(WX::GetConsoleCP());
public: // Property - OutputCodePage
	/* W */ static inline void OutputCodePage(UINT uCodePage) reflect_to(WX::SetConsoleOutputCP(uCodePage));
	/* R */ static inline UINT OutputCodePage() reflect_as(WX::GetConsoleOutputCP());
public: // Property - SelectionInfo
	/* R */ static inline auto  SelectionInfo() reflect_to(ConsoleSelectionInfo csi, WX::GetConsoleSelectionInfo(&csi), csi);
public: // Property - HistoryInfo
	/* W */ static inline void HistoryInfo(CONSOLE_HISTORY_INFO chi) reflect_to(WX::SetConsoleHistoryInfo(&chi));
	/* R */ static inline auto HistoryInfo() reflect_to(ConsoleHistoryInfo chi, WX::GetConsoleHistoryInfo(&chi), chi);
public: // Property - FullScreen
	/* W */ inline auto &FullScreen(bool bFullScreen) reflect_to_child(WX::SetConsoleDisplayMode(hOutput, bFullScreen ? CONSOLE_FULLSCREEN_MODE : CONSOLE_WINDOWED_MODE, O));
	/* A */ inline auto &FullScreenHardware() reflect_to_child(WX::SetConsoleDisplayMode(hOutput, CONSOLE_FULLSCREEN_HARDWARE, O));
	/* R */ static inline bool FullScreen() reflect_to(DWORD mode = 0; WX::GetConsoleDisplayMode(&mode), mode == CONSOLE_FULLSCREEN_MODE);
public: // Property - Mode
	/* W */ inline void Modes(Mode modes) reflect_to(WX::SetConsoleMode(hOutput, modes.yield()));
	/* R */ inline auto Modes() const reflect_to(DWORD modes, WX::GetConsoleMode(hOutput, &modes), reuse_as<Mode>(modes));
public: // Property - ScreenBufferInfo
	/* W */ inline auto &ScreenBufferInfo(CONSOLE_SCREEN_BUFFER_INFOEX sbiex) reflect_to_child(WX::SetConsoleScreenBufferInfo(hOutput, &sbiex));
	/* R */ inline auto  ScreenBufferInfo() const reflect_to(ConsoleScreenBufferInfo sbi, WX::GetConsoleScreenBufferInfo(hOutput, &sbi), sbi);
public: // Property - ScreenBufferInfoEx
	/* R */ inline auto  ScreenBufferInfoEx() const reflect_to(ConsoleScreenBufferInfoEx sbiex, WX::GetConsoleScreenBufferInfo(hOutput, &sbiex), sbiex);
public: // Property - ScreenBufferSize
	/* W */ inline auto &ScreenBufferSize(LSize size) reflect_to_child(WX::SetConsoleScreenBufferSize(hOutput, size));
	/* R */ inline LSize ScreenBufferSize() const reflect_as(ScreenBufferInfo().Size());
public: // Property - WindowSize
//	/* W */ inline auto&WindowSize(LRect rect) reflect_to_child(SetConsoleWindowInfo(hOutput, TRUE, ));
	/* R */ inline auto WindowSize() const reflect_as(ScreenBufferInfo().WindowRect().size());
public: // Property - Attributes
	/* W */ inline auto&Attributes(Attribute wAttributes) reflect_to_child(WX::SetConsoleTextAttribute(hOutput, wAttributes.yield()));
	/* R */ inline auto Attributes() const reflect_as(ScreenBufferInfo().Attributes());
public: // Property - CursorInfo
	/* W */ inline auto&CursorInfo(CONSOLE_CURSOR_INFO cci) reflect_to_child(WX::SetConsoleCursorInfo(hOutput, &cci));
	/* R */ inline auto CursorInfo() const reflect_to(ConsoleCursorInfo cci, WX::GetConsoleCursorInfo(hOutput, &cci), cci);
public: // Property - CursorPosition
	/* W */ inline auto&CursorPosition(LPoint p) reflect_to_child(WX::SetConsoleCursorPosition(hOutput, COORD({ (short)p.x, (short)p.y })));
	/* R */ inline auto CursorPosition() const reflect_as(ScreenBufferInfo().CursorPosition());
public: // Property - CurVis
	/* W */ inline auto&CursorVisible(bool bVisible) reflect_to_child(CursorInfo(*CursorInfo().Visible(bVisible)));
	/* R */ inline bool CursorVisible() const reflect_as(CursorInfo().Visible());
#pragma endregion
public:
	inline auto &operator[](LPoint p) reflect_as(CursorPosition(p));
	inline auto &operator[](bool bCurVis) reflect_as(CursorVisible(bCurVis));
	template<class... Args>
	inline auto &operator()(const Args& ...args) reflect_to_child(Log(Cats(args...)));
};
ConsoleItf<> Console;
class ConsoleCtl : public ConsoleItf<ConsoleCtl> {
public:
	~ConsoleCtl() reflect_to(Free());
};

}
