module;

#define WX_CPPM_CONSOLE
#include "wx_console"

export module wx.console;

import wx.proto;

#pragma region Win32 Prototype Includes
namespace WX {

#pragma region ProcssEnv.h (part)
// GetStdHandle
inline HANDLE GetStdHandle(DWORD nStdHandle)
	assertl_reflect_as(auto h = ::GetStdHandle(nStdHandle); h != INVALID_HANDLE_VALUE, h);
// SetStdHandle
inline void SetStdHandle(DWORD nStdHandle, HANDLE hHandle)
	assertl_reflect_as(::SetStdHandle(nStdHandle, hHandle));
// SetStdHandleEx
inline void SetStdHandle(DWORD nStdHandle, HANDLE hHandle, PHANDLE phPrevValue)
	assertl_reflect_as(::SetStdHandleEx(nStdHandle, hHandle, phPrevValue));
#pragma endregion

#pragma region ConsoleApi.h
// AllocConsole
inline void AllocConsole()
	assertl_reflect_as(::AllocConsole());
// AllocConsoleWithOptions 

// FreeConsole
inline void FreeConsole()
	assertl_reflect_as(::FreeConsole());
// AttachConsole
inline void AttachConsole(DWORD dwProcessId)
	assertl_reflect_as(::AttachConsole(dwProcessId));
// GetConsoleCP
inline UINT GetConsoleCP()
	assertl_reflect_as(auto n = ::GetConsoleCP(), n);
// GetConsoleOutputCP
inline UINT GetConsoleOutputCP()
	assertl_reflect_as(auto n = ::GetConsoleOutputCP(), n);
// GetConsoleMode
inline void GetConsoleMode(HANDLE hConsoleHandle, LPDWORD lpMode)
	assertl_reflect_as(::GetConsoleMode(hConsoleHandle, lpMode));
// SetConsoleMode
inline void SetConsoleMode(HANDLE hConsoleHandle, DWORD dwMode)
	assertl_reflect_as(::SetConsoleMode(hConsoleHandle, dwMode));
// GetNumberOfConsoleInputEvents
inline void GetNumberOfConsoleInputEvents(HANDLE hConsoleInput, LPDWORD lpNumberOfEvents)
	assertl_reflect_as(::GetNumberOfConsoleInputEvents(hConsoleInput, lpNumberOfEvents));
#undef ReadConsoleInput
// ReadConsoleInput
template<bool IsUnicode = WX::IsUnicode>
inline void ReadConsoleInput(HANDLE hConsoleInput, PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsRead) {
	if constexpr (IsUnicode)
		 assertl_reflect_as(::ReadConsoleInputW(hConsoleInput, lpBuffer, nLength, lpNumberOfEventsRead))
	else assertl_reflect_as(::ReadConsoleInputA(hConsoleInput, lpBuffer, nLength, lpNumberOfEventsRead))
}
#undef PeekConsoleInput
// PeekConsoleInput
template<bool IsUnicode = WX::IsUnicode>
inline void PeekConsoleInput(HANDLE hConsoleInput, PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsRead) {
	if constexpr (IsUnicode)
		 assertl_reflect_as(::PeekConsoleInputW(hConsoleInput, lpBuffer, nLength, lpNumberOfEventsRead))
	else assertl_reflect_as(::PeekConsoleInputA(hConsoleInput, lpBuffer, nLength, lpNumberOfEventsRead))
}
#undef ReadConsole
// ReadConsole
template<bool IsUnicode = WX::IsUnicode>
inline void ReadConsole(HANDLE hConsoleInput, LPVOID lpBuffer, DWORD nNumberOfCharsToRead, LPDWORD lpNumberOfCharsRead, PCONSOLE_READCONSOLE_CONTROL pInputControl) {
	if constexpr (IsUnicode)
		 assertl_reflect_as(::ReadConsoleW(hConsoleInput, lpBuffer, nNumberOfCharsToRead, lpNumberOfCharsRead, pInputControl))
	else assertl_reflect_as(::ReadConsoleA(hConsoleInput, lpBuffer, nNumberOfCharsToRead, lpNumberOfCharsRead, pInputControl))
}
#undef WriteConsole
// WriteConsole
inline void WriteConsole(HANDLE hConsoleOutput, LPCSTR lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved)
	assertl_reflect_as(::WriteConsoleA(hConsoleOutput, lpBuffer, nNumberOfCharsToWrite, lpNumberOfCharsWritten, lpReserved));
inline void WriteConsole(HANDLE hConsoleOutput, LPCWSTR lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved)
	assertl_reflect_as(::WriteConsoleW(hConsoleOutput, lpBuffer, nNumberOfCharsToWrite, lpNumberOfCharsWritten, lpReserved));
// SetConsoleCtrlHandler
inline void SetConsoleCtrlHandler(PHANDLER_ROUTINE HandlerRoutine, BOOL Add)
	assertl_reflect_as(::SetConsoleCtrlHandler(HandlerRoutine, Add));
#if (NTDDI_VERSION >= NTDDI_WIN10_RS5)
// CreatePseudoConsole - Deprecated
//inline void CreatePseudoConsole(COORD size, HANDLE hInput, HANDLE self, DWORD dwFlags, HPCON *phPC)
//	assertl_reflect_as(SUCCEEDED(::CreatePseudoConsole(size, hInput, self, dwFlags, phPC)));
// ResizePseudoConsole - Deprecated
//inline void ResizePseudoConsole(HPCON hPC, COORD size)
//	assertl_reflect_as(SUCCEEDED(::ResizePseudoConsole(hPC, size)));
// ClosePseudoConsole - Deprecated
//inline void ClosePseudoConsole(HPCON hPC)
//	reflect_as(::ClosePseudoConsole(hPC));
#endif
#if (NTDDI_VERSION >= NTDDI_WIN11_GE)
// ReleasePseudoConsole - Deprecated
//inline void ReleasePseudoConsole(HPCON hPC)
//	assertl_reflect_as(SUCCEEDED(::ReleasePseudoConsole(hPC)));
#endif
#pragma endregion

#pragma region ConsoleApi2.h
#undef FillConsoleOutputCharacter
// FillConsoleOutputCharacter
inline void FillConsoleOutputCharacter(HANDLE hConsoleOutput, CHAR cCharacter, DWORD nLength, COORD dwWriteCoord, LPDWORD lpNumberOfCharsWritten)
	assertl_reflect_as(::FillConsoleOutputCharacterA(hConsoleOutput, cCharacter, nLength, dwWriteCoord, lpNumberOfCharsWritten));
inline void FillConsoleOutputCharacter(HANDLE hConsoleOutput, WCHAR cCharacter, DWORD nLength, COORD dwWriteCoord, LPDWORD lpNumberOfCharsWritten)
	assertl_reflect_as(::FillConsoleOutputCharacterW(hConsoleOutput, cCharacter, nLength, dwWriteCoord, lpNumberOfCharsWritten));
// FillConsoleOutputAttribute
inline void FillConsoleOutputAttribute(HANDLE hConsoleOutput, WORD wAttribute, DWORD nLength, COORD dwWriteCoord, LPDWORD lpNumberOfAttrsWritten)
	assertl_reflect_as(::FillConsoleOutputAttribute(hConsoleOutput, wAttribute, nLength, dwWriteCoord, lpNumberOfAttrsWritten));
// GenerateConsoleCtrlEvent
inline void GenerateConsoleCtrlEvent(DWORD dwCtrlEvent, DWORD dwProcessGroupId)
	assertl_reflect_as(::GenerateConsoleCtrlEvent(dwCtrlEvent, dwProcessGroupId));
// CreateConsoleScreenBuffer
inline HANDLE CreateConsoleScreenBuffer(DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwFlags, HANDLE *lpBuffer)
	assertl_reflect_as(auto h = ::CreateConsoleScreenBuffer(dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwFlags, lpBuffer); h != INVALID_HANDLE_VALUE, h);
// SetConsoleActiveScreenBuffer
inline void SetConsoleActiveScreenBuffer(HANDLE hConsoleOutput)
	assertl_reflect_as(::SetConsoleActiveScreenBuffer(hConsoleOutput));
// FlushConsoleInputBuffer
inline void FlushConsoleInputBuffer(HANDLE hConsoleInput)
	assertl_reflect_as(::FlushConsoleInputBuffer(hConsoleInput));
// SetConsoleCP
inline void SetConsoleCP(UINT wCodePageID)
	assertl_reflect_as(::SetConsoleCP(wCodePageID));
// SetConsoleOutputCP
inline void SetConsoleOutputCP(UINT wCodePageID)
	assertl_reflect_as(::SetConsoleOutputCP(wCodePageID));
// GetConsoleCursorInfo
inline void GetConsoleCursorInfo(HANDLE hConsoleOutput, PCONSOLE_CURSOR_INFO lpConsoleCursorInfo)
	assertl_reflect_as(::GetConsoleCursorInfo(hConsoleOutput, lpConsoleCursorInfo));
// SetConsoleCursorInfo
inline void SetConsoleCursorInfo(HANDLE hConsoleOutput, const CONSOLE_CURSOR_INFO *lpConsoleCursorInfo)
	assertl_reflect_as(::SetConsoleCursorInfo(hConsoleOutput, lpConsoleCursorInfo));
// GetConsoleScreenBufferInfo
inline void GetConsoleScreenBufferInfo(HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo)
	assertl_reflect_as(::GetConsoleScreenBufferInfo(hConsoleOutput, lpConsoleScreenBufferInfo));
// GetConsoleScreenBufferInfoEx
inline void GetConsoleScreenBufferInfo(HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx)
	assertl_reflect_as(::GetConsoleScreenBufferInfoEx(hConsoleOutput, lpConsoleScreenBufferInfoEx));
// SetConsoleScreenBufferInfoEx
inline void SetConsoleScreenBufferInfo(HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx)
	assertl_reflect_as(::SetConsoleScreenBufferInfoEx(hConsoleOutput, lpConsoleScreenBufferInfoEx));
// SetConsoleScreenBufferSize
inline void SetConsoleScreenBufferSize(HANDLE hConsoleOutput, COORD dwSize)
	assertl_reflect_as(::SetConsoleScreenBufferSize(hConsoleOutput, dwSize));
// SetConsoleCursorPosition
inline void SetConsoleCursorPosition(HANDLE hConsoleOutput, COORD dwCursorPosition)
	assertl_reflect_as(::SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition));
// GetLargestConsoleWindowSize
inline COORD GetLargestConsoleWindowSize(HANDLE hConsoleOutput)
	assertl_reflect_as(auto c = ::GetLargestConsoleWindowSize(hConsoleOutput); c.X && c.Y, c);
// SetConsoleTextAttribute
inline void SetConsoleTextAttribute(HANDLE hConsoleOutput, WORD wAttributes)
	assertl_reflect_as(::SetConsoleTextAttribute(hConsoleOutput, wAttributes));
// SetConsoleWindowInfo
inline void SetConsoleWindowInfo(HANDLE hConsoleOutput, BOOL bAbsolute, const SMALL_RECT *lpConsoleWindow)
	assertl_reflect_as(::SetConsoleWindowInfo(hConsoleOutput, bAbsolute, lpConsoleWindow));
#undef WriteConsoleOutputCharacter
// WriteConsoleOutputCharacter
inline void WriteConsoleOutputCharacter(HANDLE hConsoleOutput, LPCSTR lpCharacter, DWORD nLength, COORD dwWriteCoord, LPDWORD lpNumberOfCharsWritten)
	assertl_reflect_as(::WriteConsoleOutputCharacterA(hConsoleOutput, lpCharacter, nLength, dwWriteCoord, lpNumberOfCharsWritten));
inline void WriteConsoleOutputCharacter(HANDLE hConsoleOutput, LPCWSTR lpCharacter, DWORD nLength, COORD dwWriteCoord, LPDWORD lpNumberOfCharsWritten)
	assertl_reflect_as(::WriteConsoleOutputCharacterW(hConsoleOutput, lpCharacter, nLength, dwWriteCoord, lpNumberOfCharsWritten));
// WriteConsoleOutputAttribute
inline void WriteConsoleOutputAttribute(HANDLE hConsoleOutput, const WORD *lpAttribute, DWORD nLength, COORD dwWriteCoord, LPDWORD lpNumberOfAttrsWritten)
	assertl_reflect_as(::WriteConsoleOutputAttribute(hConsoleOutput, lpAttribute, nLength, dwWriteCoord, lpNumberOfAttrsWritten));
#undef ReadConsoleOutputCharacter
inline void ReadConsoleOutputCharacter(HANDLE hConsoleOutput, LPSTR lpCharacter, DWORD nLength, COORD dwReadCoord, LPDWORD lpNumberOfCharsRead)
	assertl_reflect_as(::ReadConsoleOutputCharacterA(hConsoleOutput, lpCharacter, nLength, dwReadCoord, lpNumberOfCharsRead));
inline void ReadConsoleOutputCharacter(HANDLE hConsoleOutput, LPWSTR lpCharacter, DWORD nLength, COORD dwReadCoord, LPDWORD lpNumberOfCharsRead)
	assertl_reflect_as(::ReadConsoleOutputCharacterW(hConsoleOutput, lpCharacter, nLength, dwReadCoord, lpNumberOfCharsRead));
// ReadConsoleOutputAttribute
inline void ReadConsoleOutputAttribute(HANDLE hConsoleOutput, LPWORD lpAttribute, DWORD nLength, COORD dwReadCoord, LPDWORD lpNumberOfAttrsRead)
	assertl_reflect_as(::ReadConsoleOutputAttribute(hConsoleOutput, lpAttribute, nLength, dwReadCoord, lpNumberOfAttrsRead));
#undef WriteConsoleInput
// WriteConsoleInput
template<bool IsUnicode = WX::IsUnicode>
inline void WriteConsoleInput(HANDLE hConsoleInput, const INPUT_RECORD *lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsWritten) {
	if constexpr (IsUnicode)
		 assertl_reflect_as(::WriteConsoleInputW(hConsoleInput, lpBuffer, nLength, lpNumberOfEventsWritten))
	else assertl_reflect_as(::WriteConsoleInputA(hConsoleInput, lpBuffer, nLength, lpNumberOfEventsWritten))
}
#undef ScrollConsoleScreenBuffer
// ScrollConsoleScreenBuffer
template<bool IsUnicode = WX::IsUnicode>
inline void ScrollConsoleScreenBuffer(HANDLE hConsoleOutput, const SMALL_RECT *lpScrollRectangle, const SMALL_RECT *lpClipRectangle,
									  COORD dwDestinationOrigin, const CHAR_INFO *lpFill) {
	if constexpr (IsUnicode)
		 assertl_reflect_as(::ScrollConsoleScreenBufferW(hConsoleOutput, lpScrollRectangle, lpClipRectangle, dwDestinationOrigin, lpFill))
	else assertl_reflect_as(::ScrollConsoleScreenBufferA(hConsoleOutput, lpScrollRectangle, lpClipRectangle, dwDestinationOrigin, lpFill))
}
#undef WriteConsoleOutput
// WriteConsoleOutput
template<bool IsUnicode = WX::IsUnicode>
inline void WriteConsoleOutput(HANDLE hConsoleOutput, const CHAR_INFO *lpBuffer, COORD dwBufferSize, COORD dwBufferCoord,
							   PSMALL_RECT lpWriteRegion) {
	if constexpr (IsUnicode)
		 assertl_reflect_as(::WriteConsoleOutputW(hConsoleOutput, lpBuffer, dwBufferSize, dwBufferCoord, lpWriteRegion))
	else assertl_reflect_as(::WriteConsoleOutputA(hConsoleOutput, lpBuffer, dwBufferSize, dwBufferCoord, lpWriteRegion))
}
#undef ReadConsoleOutput
// ReadConsoleOutput
template<bool IsUnicode = WX::IsUnicode>
inline void ReadConsoleOutput(HANDLE hConsoleOutput, CHAR_INFO *lpBuffer, COORD dwBufferSize, COORD dwBufferCoord,
							  PSMALL_RECT lpReadRegion) {
	if constexpr (IsUnicode)
		 assertl_reflect_as(::ReadConsoleOutputW(hConsoleOutput, lpBuffer, dwBufferSize, dwBufferCoord, lpReadRegion))
	else assertl_reflect_as(::ReadConsoleOutputA(hConsoleOutput, lpBuffer, dwBufferSize, dwBufferCoord, lpReadRegion))
}
#undef GetConsoleTitle
// GetConsoleTitle
inline DWORD GetConsoleTitle(LPSTR lpConsoleTitle, DWORD nSize)
	assertl_reflect_as(auto n = ::GetConsoleTitleA(lpConsoleTitle, nSize), n);
inline DWORD GetConsoleTitle(LPWSTR lpConsoleTitle, DWORD nSize)
	assertl_reflect_as(auto n = ::GetConsoleTitleW(lpConsoleTitle, nSize), n);
#undef GetConsoleOriginalTitle
// GetConsoleOriginalTitle
inline DWORD GetConsoleOriginalTitle(LPSTR lpConsoleTitle, DWORD nSize)
	assertl_reflect_as(auto n = ::GetConsoleOriginalTitleA(lpConsoleTitle, nSize), n);
inline DWORD GetConsoleOriginalTitle(LPWSTR lpConsoleTitle, DWORD nSize)
	assertl_reflect_as(auto n = ::GetConsoleOriginalTitleW(lpConsoleTitle, nSize), n);
#undef SetConsoleTitle
// SetConsoleTitle
inline void SetConsoleTitle(LPCSTR lpConsoleTitle)
	assertl_reflect_as(::SetConsoleTitleA(lpConsoleTitle));
inline void SetConsoleTitle(LPCWSTR lpConsoleTitle)
	assertl_reflect_as(::SetConsoleTitleW(lpConsoleTitle));
#pragma endregion

#pragma region ConsoleApi3.h
// GetNumberOfConsoleMouseButtons
inline UINT GetNumberOfConsoleMouseButtons(LPDWORD lpNumberOfMouseButtons)
	assertl_reflect_as(auto n = ::GetNumberOfConsoleMouseButtons(lpNumberOfMouseButtons), n);
// GetConsoleFontSize
inline COORD GetConsoleFontSize(HANDLE hConsoleOutput, DWORD nFont)
	assertl_reflect_as(auto c = ::GetConsoleFontSize(hConsoleOutput, nFont); c.X && c.Y, c);
// GetCurrentConsoleFont
inline void GetCurrentConsoleFont(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFO lpConsoleCurrentFont)
	assertl_reflect_as(::GetCurrentConsoleFont(hConsoleOutput, bMaximumWindow, lpConsoleCurrentFont));
// GetCurrentConsoleFontEx
inline void GetCurrentConsoleFont(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFont)
	assertl_reflect_as(::GetCurrentConsoleFontEx(hConsoleOutput, bMaximumWindow, lpConsoleCurrentFont));
// SetCurrentConsoleFontEx
inline void SetCurrentConsoleFont(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFont)
	assertl_reflect_as(::SetCurrentConsoleFontEx(hConsoleOutput, bMaximumWindow, lpConsoleCurrentFont));
// GetConsoleSelectionInfo
inline void GetConsoleSelectionInfo(PCONSOLE_SELECTION_INFO lpConsoleSelectionInfo)
	assertl_reflect_as(::GetConsoleSelectionInfo(lpConsoleSelectionInfo));
// GetConsoleHistoryInfo
inline void GetConsoleHistoryInfo(PCONSOLE_HISTORY_INFO lpConsoleHistoryInfo)
	assertl_reflect_as(::GetConsoleHistoryInfo(lpConsoleHistoryInfo));
// SetConsoleHistoryInfo
inline void SetConsoleHistoryInfo(PCONSOLE_HISTORY_INFO lpConsoleHistoryInfo)
	assertl_reflect_as(::SetConsoleHistoryInfo(lpConsoleHistoryInfo));
// GetConsoleDisplayMode
inline void GetConsoleDisplayMode(LPDWORD lpModeFlags)
	assertl_reflect_as(::GetConsoleDisplayMode(lpModeFlags));
// SetConsoleDisplayMode
inline void SetConsoleDisplayMode(HANDLE hConsoleOutput, DWORD dwFlags, PCOORD lpNewScreenBufferDimensions)
	assertl_reflect_as(::SetConsoleDisplayMode(hConsoleOutput, dwFlags, lpNewScreenBufferDimensions));
// GetConsoleWindow
inline HWND GetConsoleWindow()
	reflect_as(::GetConsoleWindow());
#undef AddConsoleAlias
// AddConsoleAlias
inline void AddConsoleAlias(LPSTR Source, LPSTR Target, LPSTR ExeName)
	assertl_reflect_as(::AddConsoleAliasA(Source, Target, ExeName));
inline void AddConsoleAlias(LPWSTR Source, LPWSTR Target, LPWSTR ExeName)
	assertl_reflect_as(::AddConsoleAliasW(Source, Target, ExeName));
#undef GetConsoleAlias
// GetConsoleAlias
inline DWORD GetConsoleAlias(LPSTR Source, LPSTR TargetBuffer, DWORD TargetBufferLength, LPSTR ExeName)
	assertl_reflect_as(auto n = ::GetConsoleAliasA(Source, TargetBuffer, TargetBufferLength, ExeName), n);
inline DWORD GetConsoleAlias(LPWSTR Source, LPWSTR TargetBuffer, DWORD TargetBufferLength, LPWSTR ExeName)
	assertl_reflect_as(auto n = ::GetConsoleAliasW(Source, TargetBuffer, TargetBufferLength, ExeName), n);
#undef GetConsoleAliasesLength
// GetConsoleAliasesLength
inline DWORD GetConsoleAliasesLength(LPSTR ExeName)
	reflect_as(::GetConsoleAliasesLengthA(ExeName));
inline DWORD GetConsoleAliasesLength(LPWSTR ExeName)
	reflect_as(::GetConsoleAliasesLengthW(ExeName));
#undef GetConsoleAliasExesLength
// GetConsoleAliasExesLength
template<bool IsUnicode = WX::IsUnicode>
inline DWORD GetConsoleAliasExesLength() {
	if constexpr (IsUnicode)
		 reflect_as(::GetConsoleAliasExesLengthA())
	else reflect_as(::GetConsoleAliasExesLengthA())
}
#undef GetConsoleAliases
// GetConsoleAliases
inline DWORD GetConsoleAliases(LPSTR AliasBuffer, DWORD AliasBufferLength, LPSTR ExeName)
	assertl_reflect_as(auto n = ::GetConsoleAliasesA(AliasBuffer, AliasBufferLength, ExeName), n);
inline DWORD GetConsoleAliases(LPWSTR AliasBuffer, DWORD AliasBufferLength, LPWSTR ExeName)
	assertl_reflect_as(auto n = ::GetConsoleAliasesW(AliasBuffer, AliasBufferLength, ExeName), n);
#undef GetConsoleAliasExes
// GetConsoleAliasExes
inline DWORD GetConsoleAliasExes(LPSTR ExeNameBuffer, DWORD ExeNameBufferLength)
	assertl_reflect_as(auto n = ::GetConsoleAliasExesA(ExeNameBuffer, ExeNameBufferLength), n);
inline DWORD GetConsoleAliasExes(LPWSTR ExeNameBuffer, DWORD ExeNameBufferLength)
	assertl_reflect_as(auto n = ::GetConsoleAliasExesW(ExeNameBuffer, ExeNameBufferLength), n);
// GetConsoleProcessList
inline DWORD GetConsoleProcessList(LPDWORD lpdwProcessList, DWORD dwProcessCount)
	assertl_reflect_as(auto n = ::GetConsoleProcessList(lpdwProcessList, dwProcessCount), n);
#pragma endregion

}
#pragma endregion

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
class ConsoleHandleOutput :
	public HandleBase< ConsoleHandleOutput> {
public:
	using super = HandleBase<ConsoleHandleOutput>;
	using Attribute = ConsoleAttribute;
	using Mode = ConsoleMode;
protected:
	INNER_USE(ConsoleHandleOutput);
	ConsoleHandleOutput(HANDLE h) : super(h) {}
public:
	ConsoleHandleOutput() : super(WX::GetStdHandle(STD_OUTPUT_HANDLE)) {}
	ConsoleHandleOutput(Null) {}
public:
	inline void ActiveScreenBuffer() reflect_to(WX::SetConsoleActiveScreenBuffer(self));
public:
	inline DWORD Fill(CHAR cCharacter, DWORD nLength, LPoint dwWriteCoord = 0)
		reflect_as(WX::FillConsoleOutputCharacter(self, cCharacter, nLength, dwWriteCoord, &nLength), nLength);
	inline DWORD Fill(WCHAR cCharacter, DWORD nLength, LPoint dwWriteCoord = 0)
		reflect_as(WX::FillConsoleOutputCharacter(self, cCharacter, nLength, dwWriteCoord, &nLength), nLength);

	inline DWORD FillAttributes(WORD wAttributes, DWORD nLength, LPoint dwWriteCoord = 0)
		reflect_as(WX::FillConsoleOutputAttribute(self, wAttributes, nLength, dwWriteCoord, &nLength), nLength);
	inline DWORD FillAttributes(Attribute wAttributes, DWORD nLength, LPoint dwWriteCoord = 0)
		reflect_as(FillAttributes(wAttributes.yield(), nLength, dwWriteCoord));

	inline DWORD Write(LPCSTR lpszString, DWORD nLength)
		reflect_as(WX::WriteConsole(self, lpszString, nLength, &nLength, O), nLength);
	inline DWORD Write(LPCWSTR lpszString, DWORD nLength)
		reflect_as(WX::WriteConsole(self, lpszString, nLength, &nLength, O), nLength);
	inline DWORD Write(const StringA& str)
		reflect_as(Write((LPCSTR)str, (DWORD)str.Length()));
	inline DWORD Write(const StringW& str)
		reflect_as(Write((LPCWSTR)str, (DWORD)str.Length()));
	template<size_t len>
	inline DWORD Write(const CHAR(&lpszString)[len])
		reflect_as(Write(lpszString, (DWORD)(len - 1)));
	template<size_t len>
	inline DWORD Write(const WCHAR(&lpszString)[len])
		reflect_as(Write(lpszString, (DWORD)(len - 1)));

	inline DWORD Write(LPCSTR lpszString, DWORD nLength, LPoint dwWriteCoord)
		reflect_as(WX::WriteConsoleOutputCharacter(self, lpszString, nLength, dwWriteCoord, &nLength), nLength);
	inline DWORD Write(LPCWSTR lpszString, DWORD nLength, LPoint dwWriteCoord)
		reflect_as(WX::WriteConsoleOutputCharacter(self, lpszString, nLength, dwWriteCoord, &nLength), nLength);
	inline DWORD Write(const StringA& str, LPoint dwWriteCoord)
		reflect_as(Write((LPCSTR)str, (DWORD)str.Length(), dwWriteCoord));
	inline DWORD Write(const StringW& str, LPoint dwWriteCoord)
		reflect_as(Write((LPCWSTR)str, (DWORD)str.Length(), dwWriteCoord));
	template<size_t len>
	inline DWORD Write(const CHAR(&lpszString)[len], LPoint dwWriteCoord)
		reflect_as(Write(lpszString, (DWORD)(len - 1), dwWriteCoord));
	template<size_t len>
	inline DWORD Write(const WCHAR(&lpszString)[len], LPoint dwWriteCoord)
		reflect_as(Write(lpszString, (DWORD)(len - 1), dwWriteCoord));

	inline DWORD WriteAttributes(const WORD* lpAttributes, DWORD nLength, LPoint dwWriteCoord = 0)
		reflect_as(WX::WriteConsoleOutputAttribute(self, lpAttributes, nLength, dwWriteCoord, &nLength), nLength);
	inline DWORD WriteAttributes(const Attribute* lpAttributes, DWORD nLength, LPoint dwWriteCoord = 0)
		reflect_as(WriteAttributes((const WORD*)lpAttributes, nLength, dwWriteCoord));
	template<size_t len>
	inline DWORD WriteAttributes(const WORD(&lpAttributes)[len], LPoint dwWriteCoord = 0)
		reflect_as(WriteAttributes(lpAttributes, (DWORD)len, dwWriteCoord));
	template<size_t len>
	inline DWORD WriteAttributes(const Attribute(&lpAttributes)[len], LPoint dwWriteCoord = 0)
		reflect_as(WriteAttributes((const WORD*)lpAttributes, (DWORD)len, dwWriteCoord));

	inline DWORD Read(LPSTR lpszBuffer, DWORD nLength, LPoint dwReadCoord = 0)
		reflect_as(WX::ReadConsoleOutputCharacter(self, lpszBuffer, nLength, dwReadCoord, &nLength), nLength);
	inline DWORD Read(LPWSTR lpszBuffer, DWORD nLength, LPoint dwReadCoord = 0)
		reflect_as(WX::ReadConsoleOutputCharacter(self, lpszBuffer, nLength, dwReadCoord, &nLength), nLength);
	inline DWORD Read(StringA& str, LPoint dwReadCoord = 0) reflect_as(Read(str, (DWORD)str.Length(), dwReadCoord));
	inline DWORD Read(StringW& str, LPoint dwReadCoord = 0) reflect_as(Read(str, (DWORD)str.Length(), dwReadCoord));
	template<size_t len>
	inline DWORD Read(CHAR(&lpszBuffer)[len], LPoint dwReadCoord = 0)
		reflect_as(Read(lpszBuffer, (DWORD)(len - 1), dwReadCoord));
	template<size_t len>
	inline DWORD Read(WCHAR(&lpszBuffer)[len], LPoint dwReadCoord = 0)
		reflect_as(Read(lpszBuffer, (DWORD)(len - 1), dwReadCoord));

	inline String Read(DWORD nLength, LPoint dwReadCoord = 0)
		reflect_to(String buf{ (size_t)nLength }; buf.Resize(Read(buf, dwReadCoord)), std::move(buf));
	inline StringA ReadA(DWORD nLength, LPoint dwReadCoord = 0)
		reflect_to(StringA buf{ (size_t)nLength }; buf.Resize(Read(buf, dwReadCoord)), std::move(buf));
	inline StringW ReadW(DWORD nLength, LPoint dwReadCoord = 0)
		reflect_to(StringW buf{ (size_t)nLength }; buf.Resize(Read(buf, dwReadCoord)), std::move(buf));

	inline DWORD Read(WORD* lpAttributes, DWORD nLength, LPoint dwReadCoord = 0)
		reflect_as(WX::ReadConsoleOutputAttribute(self, lpAttributes, nLength, dwReadCoord, &nLength), nLength);
	inline DWORD Read(Attribute* lpAttributes, DWORD nLength, LPoint dwReadCoord = 0)
		reflect_as(Read((WORD*)lpAttributes, nLength, dwReadCoord));
	template<size_t len>
	inline DWORD Read(WORD(&lpAttributes)[len], LPoint dwReadCoord = 0)
		reflect_as(Read(lpAttributes, (DWORD)len, dwReadCoord));
	template<size_t len>
	inline DWORD Read(Attribute(&lpAttributes)[len], LPoint dwReadCoord = 0)
		reflect_as(Read((WORD*)lpAttributes, (DWORD)len, dwReadCoord));
#pragma region Properties
public: // Property - FullScreen
	/* W */ inline auto& FullScreen(bool bFullScreen) reflect_to_self(WX::SetConsoleDisplayMode(self, bFullScreen ? CONSOLE_FULLSCREEN_MODE : CONSOLE_WINDOWED_MODE, O));
	//	/* A */ inline auto&FullScreenHardware() reflect_to_self(WX::SetConsoleDisplayMode(self, CONSOLE_FULLSCREEN_HARDWARE, O));
	/* R */ inline bool FullScreen() const reflect_to(DWORD mode = 0; WX::GetConsoleDisplayMode(&mode), mode == CONSOLE_FULLSCREEN_MODE);
public: // Property - Mode
	/* W */ inline auto& Modes(Mode modes) reflect_to_self(WX::SetConsoleMode(self, modes.yield()));
	/* R */ inline auto Modes() const reflect_to(DWORD modes, WX::GetConsoleMode(self, &modes), reuse_as<Mode>(modes));
public: // Property - ScreenBufferInfo
	/* W */ inline auto& ScreenBufferInfo(CONSOLE_SCREEN_BUFFER_INFOEX sbiex) reflect_to_self(WX::SetConsoleScreenBufferInfo(self, &sbiex));
	/* R */ inline auto ScreenBufferInfo() const reflect_to(ConsoleScreenBufferInfo sbi, WX::GetConsoleScreenBufferInfo(self, &sbi), sbi);
public: // Property - ScreenBufferInfoEx
	/* R */ inline auto ScreenBufferInfoEx() const reflect_to(ConsoleScreenBufferInfoEx sbiex, WX::GetConsoleScreenBufferInfo(self, &sbiex), sbiex);
public: // Property - ScreenBufferSize
	/* W */ inline auto& ScreenBufferSize(LSize size) reflect_to_self(WX::SetConsoleScreenBufferSize(self, size));
	/* R */ inline LSize ScreenBufferSize() const reflect_as(ScreenBufferInfo().Size());
public: // Property - WindowSize
	//	/* W */ inline auto&WindowSize(LRect rect) reflect_to_self(SetConsoleWindowInfo(self, TRUE, ));
	/* R */ inline auto WindowSize() const reflect_as(ScreenBufferInfo().WindowRect().size());
public: // Property - Attributes
	/* W */ inline auto& Attributes(Attribute wAttributes) reflect_to_self(WX::SetConsoleTextAttribute(self, wAttributes.yield()));
	/* R */ inline auto Attributes() const reflect_as(ScreenBufferInfo().Attributes());
public: // Property - CursorInfo
	/* W */ inline auto& CursorInfo(CONSOLE_CURSOR_INFO cci) reflect_to_self(WX::SetConsoleCursorInfo(self, &cci));
	/* R */ inline auto CursorInfo() const reflect_to(ConsoleCursorInfo cci, WX::GetConsoleCursorInfo(self, &cci), cci);
public: // Property - CursorPosition
	/* W */ inline auto& CursorPosition(LPoint p) reflect_to_self(WX::SetConsoleCursorPosition(self, p));
	/* R */ inline auto CursorPosition() const reflect_as(ScreenBufferInfo().CursorPosition());
public: // Property - CurVis
	/* W */ inline auto& CursorVisible(bool bVisible) reflect_to_self(CursorInfo(*CursorInfo().Visible(bVisible)));
	/* R */ inline bool CursorVisible() const reflect_as(CursorInfo().Visible());
#pragma endregion
};
class ConsoleHandleInput :
	public HandleBase<ConsoleHandleInput> {
public:
	using super = HandleBase<ConsoleHandleInput>;
protected:
	INNER_USE(ConsoleHandleInput);
	ConsoleHandleInput(HANDLE h) : super(h) {}
public:
	ConsoleHandleInput() : super(WX::GetStdHandle(STD_INPUT_HANDLE)) {}
	ConsoleHandleInput(Null) {}
public:
	inline void FlushInputBuffer() reflect_to(WX::FlushConsoleInputBuffer(self));
};
class IConsole : 
	public ConsoleHandleOutput {
protected:
	HANDLE hError = O;
public:
public:
	IConsole(Null) {}
	IConsole() :
		hError(WX::GetStdHandle(STD_ERROR_HANDLE)) {}
	IConsole(DWORD pid) reflect_to(Attach(pid));
public:
	inline void Attach(DWORD pid) reflect_to(WX::AttachConsole(pid));
	inline void Alloc() reflect_to(WX::AllocConsole());
	inline void Free() reflect_to(WX::FreeConsole());

	inline void Select() {
		static FILE* fout = O, * ferr = O, * fin = O;
		freopen_s(&fout, "CONOUT$", "w+t", stdout);
		freopen_s(&ferr, "CONERR$", "w+t", stderr);
		freopen_s(&fin, "CONIN$", "r+t", stdin);
	}
public:
	inline void Clear() reflect_to(Fill(T(' '), ScreenBufferInfo().Size().Square()); CursorPosition(0));
	inline void Color(WORD wAttributes) reflect_to(FillAttributes(wAttributes, ScreenBufferInfo().Size().Square()); Attributes(wAttributes));
	inline void Color(Attribute wAttributes) reflect_to(Color(wAttributes.yield()));
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
	/* W */ inline auto&Title(const TCHAR *lpTitle) reflect_to_self(WX::SetConsoleTitle(lpTitle));
	template<size_t MaxLen = MaxLenTitle, bool IsUnicode = WX::IsUnicode>
	/* R */ inline StringX<IsUnicode> Title() const {
		StringX<IsUnicode> str(MaxLen);
		auto len = WX::GetConsoleTitle(str, (int)MaxLen);
		return inject(str.Resize(len));
	}
	template<size_t MaxLen = MaxLenTitle>
	/* R */ inline StringA TitleA() const reflect_as(Title<MaxLen, false>());
	template<size_t MaxLen = MaxLenTitle>
	/* R */ inline StringW TitleW() const reflect_as(Title<MaxLen, true>());
public: // Property - OriginalTitle
	template<size_t MaxLen = MaxLenTitle, bool IsUnicode = WX::IsUnicode>
	/* R */ inline StringX<IsUnicode> OriginalTitle() const {
		StringX<IsUnicode> str(MaxLen);
		auto len = WX::GetConsoleOriginalTitle(str, (int)MaxLen);
		return inject(str.Resize(len));
	}
	template<size_t MaxLen = MaxLenTitle>
	/* R */ inline StringA OriginalTitleA() const reflect_as(OriginalTitle<MaxLen, false>());
	template<size_t MaxLen = MaxLenTitle>
	/* R */ inline StringW OriginalTitleW() const reflect_as(OriginalTitle<MaxLen, true>());
//public: // Property - Window
//	inline CWindow Window() const reflect_as(WX::GetConsoleWindow());
public: // Property - CodePage
	/* W */ inline auto&CodePage(UINT uCodePage) reflect_to_self(WX::SetConsoleCP(uCodePage));
	/* R */ inline UINT CodePage() const reflect_as(WX::GetConsoleCP());
public: // Property - OutputCodePage
	/* W */ inline auto&OutputCodePage(UINT uCodePage) reflect_to_self(WX::SetConsoleOutputCP(uCodePage));
	/* R */ inline UINT OutputCodePage() const reflect_as(WX::GetConsoleOutputCP());
public: // Property - SelectionInfo
	/* R */ inline auto SelectionInfo() const reflect_to(ConsoleSelectionInfo csi, WX::GetConsoleSelectionInfo(&csi), csi);
public: // Property - HistoryInfo
	/* W */ inline auto&HistoryInfo(CONSOLE_HISTORY_INFO chi) reflect_to_self(WX::SetConsoleHistoryInfo(&chi));
	/* R */ inline auto HistoryInfo() const reflect_to(ConsoleHistoryInfo chi, WX::GetConsoleHistoryInfo(&chi), chi);
#pragma endregion
public:
	inline auto &operator[](LPoint p) reflect_as(CursorPosition(p));
	inline auto &operator[](bool bCurVis) reflect_as(CursorVisible(bCurVis));
} Console;

}
