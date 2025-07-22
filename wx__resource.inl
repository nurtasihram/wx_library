#pragma once

namespace WX {

#pragma region libloaderapi.h
// DisableThreadLibraryCalls
inline void DisableThreadLibraryCalls(HMODULE hLibModule)
	assertl_reflect_as(::DisableThreadLibraryCalls(hLibModule));
// #N/A
// FindStringOrdinal
inline int FindStringOrdinal(DWORD dwFindStringOrdinalFlags, LPCWSTR lpStringSource, int cchSource, LPCWSTR lpStringValue, int cchValue, BOOL bIgnoreCase)
	assertl_reflect_as(auto ret = ::FindStringOrdinal(dwFindStringOrdinalFlags, lpStringSource, cchSource, lpStringValue, cchValue, bIgnoreCase); ret >= 0, ret);
// FreeLibrary
inline void FreeLibrary(HMODULE hLibModule)
	assertl_reflect_as(::FreeLibrary(hLibModule));
// FreeLibraryAndExitThread
inline void FreeLibraryAndExitThread(HMODULE hLibModule, DWORD dwExitCode)
	reflect_as(::FreeLibraryAndExitThread(hLibModule, dwExitCode));
// FreeResource
inline void FreeResource(HGLOBAL hResData)
	assertl_reflect_as(auto ret = ::FreeResource(hResData); ret == 0);
// GetModuleFileName
#undef GetModuleFileName
inline DWORD GetModuleFileName(HMODULE hModule, LPSTR lpFilename, DWORD nSize)
	assertl_reflect_as(auto ret = ::GetModuleFileNameA(hModule, lpFilename, nSize), ret);
inline DWORD GetModuleFileName(HMODULE hModule, LPWSTR lpFilename, DWORD nSize)
	assertl_reflect_as(auto ret = ::GetModuleFileNameW(hModule, lpFilename, nSize), ret);
// GetModuleHandle
#undef GetModuleHandle
inline HMODULE GetModuleHandle(LPCSTR lpModuleName)
	assertl_reflect_as(auto ret = ::GetModuleHandleA(lpModuleName), ret);
inline HMODULE GetModuleHandle(LPCWSTR lpModuleName)
	assertl_reflect_as(auto ret = ::GetModuleHandleW(lpModuleName), ret);
// GetModuleHandleEx
#undef GetModuleHandleEx
inline void GetModuleHandleEx(DWORD dwFlags, LPCSTR lpModuleName, HMODULE* phModule)
	assertl_reflect_as(::GetModuleHandleExA(dwFlags, lpModuleName, phModule));
inline void GetModuleHandleEx(DWORD dwFlags, LPCWSTR lpModuleName, HMODULE* phModule)
	assertl_reflect_as(::GetModuleHandleExW(dwFlags, lpModuleName, phModule));
// GetProcAddress
inline FARPROC GetProcAddress(HMODULE hModule, LPCSTR lpProcName)
	assertl_reflect_as(auto ret = ::GetProcAddress(hModule, lpProcName), ret);
// LoadLibraryEx
#undef LoadLibraryEx
inline HMODULE LoadLibraryEx(LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
	assertl_reflect_as(auto ret = ::LoadLibraryExA(lpLibFileName, hFile, dwFlags), ret);
inline HMODULE LoadLibraryEx(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
	assertl_reflect_as(auto ret = ::LoadLibraryExW(lpLibFileName, hFile, dwFlags), ret);
// LoadResource
inline HGLOBAL LoadResource(HMODULE hModule, HRSRC hResInfo)
	assertl_reflect_as(auto ret = ::LoadResource(hModule, hResInfo), ret);
// LoadString
#undef LoadString
inline int LoadString(HINSTANCE hInstance, UINT uID, LPSTR lpBuffer, int cchBufferMax)
	assertl_reflect_as(auto ret = ::LoadStringA(hInstance, uID, lpBuffer, cchBufferMax); ret >= 0, ret);
inline int LoadString(HINSTANCE hInstance, UINT uID, PWSTR lpBuffer, int cchBufferMax)
	assertl_reflect_as(auto ret = ::LoadStringW(hInstance, uID, lpBuffer, cchBufferMax); ret >= 0, ret);
// LockResource
inline LPVOID LockResource(HGLOBAL hResData)
	assertl_reflect_as(auto ret = ::LockResource(hResData), ret);
// SizeofResource
inline DWORD SizeofResource(HMODULE hModule, HRSRC hResInfo)
	assertl_reflect_as(auto ret = ::SizeofResource(hModule, hResInfo), ret);
// AddDllDirectory
inline DLL_DIRECTORY_COOKIE AddDllDirectory(PCWSTR NewDirectory)
	assertl_reflect_as(auto ret = ::AddDllDirectory(NewDirectory), ret);
// RemoveDllDirectory
inline void RemoveDllDirectory(DLL_DIRECTORY_COOKIE Cookie)
	assertl_reflect_as(::RemoveDllDirectory(Cookie));
// SetDefaultDllDirectories
inline void SetDefaultDllDirectories(DWORD DirectoryFlags)
	assertl_reflect_as(::SetDefaultDllDirectories(DirectoryFlags));
// EnumResourceLanguagesEx
#undef EnumResourceLanguagesEx
inline void EnumResourceLanguagesEx(HMODULE hModule, LPCSTR lpType, LPCSTR lpName, ENUMRESLANGPROCA lpEnumFunc, LONG_PTR lParam, DWORD dwFlags, LANGID LangId)
	assertl_reflect_as(::EnumResourceLanguagesExA(hModule, lpType, lpName, lpEnumFunc, lParam, dwFlags, LangId));
inline void EnumResourceLanguagesEx(HMODULE hModule, LPCWSTR lpType, LPCWSTR lpName, ENUMRESLANGPROCW lpEnumFunc, LONG_PTR lParam, DWORD dwFlags, LANGID LangId)
	assertl_reflect_as(::EnumResourceLanguagesExW(hModule, lpType, lpName, lpEnumFunc, lParam, dwFlags, LangId));
// EnumResourceNamesEx
#undef EnumResourceNamesEx
inline void EnumResourceNamesEx(HMODULE hModule, LPCSTR lpType, ENUMRESNAMEPROCA lpEnumFunc, LONG_PTR lParam, DWORD dwFlags, LANGID LangId)
	assertl_reflect_as(::EnumResourceNamesExA(hModule, lpType, lpEnumFunc, lParam, dwFlags, LangId));
inline void EnumResourceNamesEx(HMODULE hModule, LPCWSTR lpType, ENUMRESNAMEPROCW lpEnumFunc, LONG_PTR lParam, DWORD dwFlags, LANGID LangId)
	assertl_reflect_as(::EnumResourceNamesExW(hModule, lpType, lpEnumFunc, lParam, dwFlags, LangId));
// EnumResourceTypesEx
#undef EnumResourceTypesEx
inline void EnumResourceTypesEx(HMODULE hModule, ENUMRESTYPEPROCA lpEnumFunc, LONG_PTR lParam, DWORD dwFlags, LANGID LangId)
	assertl_reflect_as(::EnumResourceTypesExA(hModule, lpEnumFunc, lParam, dwFlags, LangId));
inline void EnumResourceTypesEx(HMODULE hModule, ENUMRESTYPEPROCW lpEnumFunc, LONG_PTR lParam, DWORD dwFlags, LANGID LangId)
	assertl_reflect_as(::EnumResourceTypesExW(hModule, lpEnumFunc, lParam, dwFlags, LangId));
// #N/A
// LoadLibrary
#undef LoadLibrary
inline HMODULE LoadLibrary(LPCSTR lpLibFileName)
	assertl_reflect_as(auto ret = ::LoadLibraryA(lpLibFileName), ret);
inline HMODULE LoadLibrary(LPCWSTR lpLibFileName)
	assertl_reflect_as(auto ret = ::LoadLibraryW(lpLibFileName), ret);
inline void EnumResourceNames(HMODULE hModule, LPCWSTR lpType, ENUMRESNAMEPROCW lpEnumFunc, LONG_PTR lParam)
	assertl_reflect_as(::EnumResourceNamesW(hModule, lpType, lpEnumFunc, lParam));
// EnumResourceNames
#undef EnumResourceNames
inline void EnumResourceNames(HMODULE hModule, LPCSTR lpType, ENUMRESNAMEPROCA lpEnumFunc, LONG_PTR lParam)
	assertl_reflect_as(::EnumResourceNamesA(hModule, lpType, lpEnumFunc, lParam));
#pragma endregion

}
