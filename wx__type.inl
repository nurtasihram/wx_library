#pragma once

namespace WX {

#pragma region datetimeapi.h
#undef GetDateFormat
// GetDateFormat
inline int GetDateFormat(LCID Locale, DWORD dwFlags, const SYSTEMTIME *lpDate, LPCSTR lpFormat, LPSTR lpDateStr, int cchDate)
	assertl_reflect_as(auto res = ::GetDateFormatA(Locale, dwFlags, lpDate, lpFormat, lpDateStr, cchDate); res > 0, res);
inline int GetDateFormat(LCID Locale, DWORD dwFlags, const SYSTEMTIME *lpDate, LPCWSTR lpFormat, LPWSTR lpDateStr, int cchDate)
	assertl_reflect_as(auto res = ::GetDateFormatW(Locale, dwFlags, lpDate, lpFormat, lpDateStr, cchDate); res > 0, res);
#undef GetTimeFormat
// GetTimeFormat
inline int GetTimeFormat(LCID Locale, DWORD dwFlags, const SYSTEMTIME *lpTime, LPCSTR lpFormat, LPSTR lpTimeStr, int cchTime)
	assertl_reflect_as(auto res = ::GetTimeFormatA(Locale, dwFlags, lpTime, lpFormat, lpTimeStr, cchTime); res > 0, res);
inline int GetTimeFormat(LCID Locale, DWORD dwFlags, const SYSTEMTIME *lpTime, LPCWSTR lpFormat, LPWSTR lpTimeStr, int cchTime)
	assertl_reflect_as(auto res = ::GetTimeFormatW(Locale, dwFlags, lpTime, lpFormat, lpTimeStr, cchTime); res > 0, res);
#undef GetTimeFormatEx
// GetTimeFormatEx
inline int GetTimeFormat(LPCWSTR lpLocaleName, DWORD dwFlags, const SYSTEMTIME *lpTime, LPCWSTR lpFormat, LPWSTR lpTimeStr, int cchTime)
	assertl_reflect_as(auto res = ::GetTimeFormatEx(lpLocaleName, dwFlags, lpTime, lpFormat, lpTimeStr, cchTime); res > 0, res);
#undef GetDateFormatEx
// GetDateFormatEx
inline int GetDateFormat(LPCWSTR lpLocaleName, DWORD dwFlags, const SYSTEMTIME *lpDate, LPCWSTR lpFormat, LPWSTR lpDateStr, int cchDate, LPCWSTR lpCalendar)
	assertl_reflect_as(auto res = ::GetDateFormatEx(lpLocaleName, dwFlags, lpDate, lpFormat, lpDateStr, cchDate, lpCalendar); res > 0, res);
// GetDurationFormatEx - Deprecated
#pragma endregion

#pragma region handleapi.h
// CloseHandle
inline void CloseHandle(HANDLE hObject)
	assertl_reflect_as(::CloseHandle(hObject));
// DuplicateHandle
inline void DuplicateHandle(HANDLE hSourceProcessHandle, HANDLE hSourceHandle,
							HANDLE hTargetProcessHandle, LPHANDLE lpTargetHandle,
							DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwOptions)
	assertl_reflect_as(::DuplicateHandle(hSourceProcessHandle, hSourceHandle,
										 hTargetProcessHandle, lpTargetHandle,
										 dwDesiredAccess, bInheritHandle, dwOptions));
// CompareObjectHandles
inline bool CompareObjectHandles(HANDLE hObject1, HANDLE hObject2)
	reflect_as(::CompareObjectHandles(hObject1, hObject2));
// GetHandleInformation
inline void GetHandleInformation(HANDLE hObject, LPDWORD lpdwFlags)
	assertl_reflect_as(::GetHandleInformation(hObject, lpdwFlags));
// SetHandleInformation
inline void SetHandleInformation(HANDLE hObject, DWORD dwMask, DWORD dwFlags)
	assertl_reflect_as(::SetHandleInformation(hObject, dwMask, dwFlags));
#pragma endregion

}
