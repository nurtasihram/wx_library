#pragma once

namespace WX {

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
template<bool IsUnicode = WX::IsUnicode>
inline void WriteConsole(HANDLE hConsoleOutput, const void *lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved) {
	if constexpr (IsUnicode)
		 assertl_reflect_as(::WriteConsoleW(hConsoleOutput, lpBuffer, nNumberOfCharsToWrite, lpNumberOfCharsWritten, lpReserved))
	else assertl_reflect_as(::WriteConsoleA(hConsoleOutput, lpBuffer, nNumberOfCharsToWrite, lpNumberOfCharsWritten, lpReserved))
}
// SetConsoleCtrlHandler
inline void SetConsoleCtrlHandler(PHANDLER_ROUTINE HandlerRoutine, BOOL Add)
	assertl_reflect_as(::SetConsoleCtrlHandler(HandlerRoutine, Add));
#if (NTDDI_VERSION >= NTDDI_WIN10_RS5)
// CreatePseudoConsole - Deprecated
//inline void CreatePseudoConsole(COORD size, HANDLE hInput, HANDLE hOutput, DWORD dwFlags, HPCON *phPC)
//	assertl_reflect_as(SUCCEEDED(::CreatePseudoConsole(size, hInput, hOutput, dwFlags, phPC)));
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
inline void ReadConsoleOutputCharacter(HANDLE hConsoleInput, LPSTR lpCharacter, DWORD nLength, COORD dwReadCoord, LPDWORD lpNumberOfCharsRead)
	assertl_reflect_as(::ReadConsoleOutputCharacterA(hConsoleInput, lpCharacter, nLength, dwReadCoord, lpNumberOfCharsRead));
inline void ReadConsoleOutputCharacter(HANDLE hConsoleInput, LPWSTR lpCharacter, DWORD nLength, COORD dwReadCoord, LPDWORD lpNumberOfCharsRead)
	assertl_reflect_as(::ReadConsoleOutputCharacterW(hConsoleInput, lpCharacter, nLength, dwReadCoord, lpNumberOfCharsRead));
// ReadConsoleOutputAttribute
inline void ReadConsoleOutputAttribute(HANDLE hConsoleInput, LPWORD lpAttribute, DWORD nLength, COORD dwReadCoord, LPDWORD lpNumberOfAttrsRead)
	assertl_reflect_as(::ReadConsoleOutputAttribute(hConsoleInput, lpAttribute, nLength, dwReadCoord, lpNumberOfAttrsRead));
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
inline void ReadConsoleOutput(HANDLE hConsoleInput, CHAR_INFO *lpBuffer, COORD dwBufferSize, COORD dwBufferCoord,
							  PSMALL_RECT lpReadRegion) {
	if constexpr (IsUnicode)
		 assertl_reflect_as(::ReadConsoleOutputW(hConsoleInput, lpBuffer, dwBufferSize, dwBufferCoord, lpReadRegion))
	else assertl_reflect_as(::ReadConsoleOutputA(hConsoleInput, lpBuffer, dwBufferSize, dwBufferCoord, lpReadRegion))
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
