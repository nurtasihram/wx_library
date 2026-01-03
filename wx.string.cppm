module;

#define WX_CPPM_STRING
#include "wx_string"

export module wx.string;

import wx.proto;

#pragma region Win32 Prototype Includes
namespace WX {

#pragma region StringApiSet.h
// CompareStringEx
inline int CompareStringEx(LPCWSTR lpLocaleName, DWORD dwCmpFlags, LPCWCH lpString1, int cchCount1, LPCWCH lpString2, int cchCount2, LPNLSVERSIONINFO lpVersionInformation, LPVOID lpReserved, LPARAM lParam)
	assertl_reflect_as(auto h = ::CompareStringEx(lpLocaleName, dwCmpFlags, lpString1, cchCount1, lpString2, cchCount2, lpVersionInformation, lpReserved, lParam); h != 0, h);
// CompareStringOrdinal
inline int CompareStringOrdinal(LPCWCH lpString1, int cchCount1, LPCWCH lpString2, int cchCount2, BOOL bIgnoreCase)
	assertl_reflect_as(auto h = ::CompareStringOrdinal(lpString1, cchCount1, lpString2, cchCount2, bIgnoreCase); h != 0, h);
#undef CompareString
// from WinNls.h
inline int CompareString(LCID Locale, DWORD dwCmpFlags, PCNZCH lpString1, int cchCount1, PCNZCH lpString2, int cchCount2)
	assertl_reflect_as(auto h = ::CompareStringA(Locale, dwCmpFlags, lpString1, cchCount1, lpString2, cchCount2); h != 0, h);
inline int CompareString(LCID Locale, DWORD dwCmpFlags, PCNZWCH lpString1, int cchCount1, PCNZWCH lpString2, int cchCount2)
	assertl_reflect_as(auto h = ::CompareStringW(Locale, dwCmpFlags, lpString1, cchCount1, lpString2, cchCount2); h != 0, h);
#undef FoldString
// from WinNls.h
inline int FoldString(DWORD dwMapFlags, LPCCH lpSrcStr, int cchSrc, LPSTR lpDestStr, int cchDest)
	assertl_reflect_as(auto h = ::FoldStringA(dwMapFlags, lpSrcStr, cchSrc, lpDestStr, cchDest); h > 0, h);
inline int FoldString(DWORD dwMapFlags, LPCWCH lpSrcStr, int cchSrc, LPWSTR lpDestStr, int cchDest)
	assertl_reflect_as(auto h = ::FoldStringW(dwMapFlags, lpSrcStr, cchSrc, lpDestStr, cchDest); h > 0, h);
#undef GetStringTypeEx
// from WinNls.h
inline void GetStringType(LCID Locale, DWORD dwInfoType, LPCCH lpSrcStr, int cchSrc, LPWORD lpCharType)
	assertl_reflect_as(::GetStringTypeExA(Locale, dwInfoType, lpSrcStr, cchSrc, lpCharType));
inline void GetStringType(LCID Locale, DWORD dwInfoType, LPCWCH lpSrcStr, int cchSrc, LPWORD lpCharType)
	assertl_reflect_as(::GetStringTypeExW(Locale, dwInfoType, lpSrcStr, cchSrc, lpCharType));
// GetStringTypeW
inline void GetStringType(DWORD dwInfoType, LPCWCH lpSrcStr, int cchSrc, LPWORD lpCharType)
	assertl_reflect_as(::GetStringTypeW(dwInfoType, lpSrcStr, cchSrc, lpCharType));
// MultiByteToWideChar
inline int MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCCH lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar)
	assertl_reflect_as(auto h = ::MultiByteToWideChar(CodePage, dwFlags, lpMultiByteStr, cbMultiByte, lpWideCharStr, cchWideChar); h > 0, h);
// WideCharToMultiByte
inline int WideCharToMultiByte(UINT CodePage, DWORD dwFlags, LPCWCH lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar)
	assertl_reflect_as(auto h = ::WideCharToMultiByte(CodePage, dwFlags, lpWideCharStr, cchWideChar, lpMultiByteStr, cbMultiByte, lpDefaultChar, lpUsedDefaultChar); h > 0, h);
#pragma endregion

#pragma region StrSafe.h
#undef StringCchCopy
inline void StringCchCopy(LPSTR pszDest, size_t cchDest, LPCSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyA(pszDest, cchDest, pszSrc)));
inline void StringCchCopy(LPWSTR pszDest, size_t cchDest, LPCWSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyW(pszDest, cchDest, pszSrc)));
#undef StringCbCopy
inline void StringCbCopy(LPSTR pszDest, size_t cbDest, LPCSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyA(pszDest, cbDest, pszSrc)));
inline void StringCbCopy(LPWSTR pszDest, size_t cbDest, LPCWSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyW(pszDest, cbDest, pszSrc)));
#undef StringCchCopyEx
inline void StringCchCopy(LPSTR pszDest, size_t cchDest, LPCSTR pszSrc,
						  LPSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyExA(pszDest, cchDest, pszSrc, ppszDestEnd, pcchRemaining, dwFlags)));
inline void StringCchCopy(LPWSTR pszDest, size_t cchDest, LPCWSTR pszSrc,
						  LPWSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyExW(pszDest, cchDest, pszSrc, ppszDestEnd, pcchRemaining, dwFlags)));
#undef StringCbCopyEx
inline void StringCbCopy(LPSTR pszDest, size_t cbDest, LPCSTR pszSrc,
						 LPSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyExA(pszDest, cbDest, pszSrc, ppszDestEnd, pcbRemaining, dwFlags)));
inline void StringCbCopy(LPWSTR pszDest, size_t cbDest, LPCWSTR pszSrc,
						 LPWSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyExW(pszDest, cbDest, pszSrc, ppszDestEnd, pcbRemaining, dwFlags)));
#undef StringCchCopyN
inline void StringCchCopyN(LPSTR pszDest, size_t cchDest, LPCSTR pszSrc, size_t cchToCopy)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyNA(pszDest, cchDest, pszSrc, cchToCopy)));
inline void StringCchCopyN(LPWSTR pszDest, size_t cchDest, LPCWSTR pszSrc, size_t cchToCopy)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyNW(pszDest, cchDest, pszSrc, cchToCopy)));
#undef StringCbCopyN
inline void StringCbCopyN(LPSTR pszDest, size_t cbDest, LPCSTR pszSrc, size_t cbToCopy)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyNA(pszDest, cbDest, pszSrc, cbToCopy)));
inline void StringCbCopyN(LPWSTR pszDest, size_t cbDest, LPCWSTR pszSrc, size_t cbToCopy)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyNW(pszDest, cbDest, pszSrc, cbToCopy)));
#undef StringCchCopyNEx
inline void StringCchCopyN(LPSTR pszDest, size_t cchDest,
						   LPCSTR pszSrc, size_t cchToCopy,
						   LPSTR *ppszDestEnd, size_t *pcchRemaining,
						   DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyNExA(pszDest, cchDest, pszSrc, cchToCopy, ppszDestEnd, pcchRemaining, dwFlags)));
inline void StringCchCopyN(LPWSTR pszDest, size_t cchDest,
						   LPCWSTR pszSrc, size_t cchToCopy,
						   LPWSTR *ppszDestEnd, size_t *pcchRemaining,
						   DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyNExW(pszDest, cchDest, pszSrc, cchToCopy, ppszDestEnd, pcchRemaining, dwFlags)));
#undef StringCbCopyNEx
inline void StringCbCopyN(LPSTR pszDest, size_t cbDest,
						  LPCSTR pszSrc, size_t cbToCopy,
						  LPSTR *ppszDestEnd, size_t *pcbRemaining,
						  DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyNExA(pszDest, cbDest, pszSrc, cbToCopy, ppszDestEnd, pcbRemaining, dwFlags)));
inline void StringCbCopyN(LPWSTR pszDest, size_t cbDest,
						  LPCWSTR pszSrc, size_t cbToCopy,
						  LPWSTR *ppszDestEnd, size_t *pcbRemaining,
						  DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyNExW(pszDest, cbDest, pszSrc, cbToCopy, ppszDestEnd, pcbRemaining, dwFlags)));
#undef StringCchCat
inline void StringCchCat(LPSTR pszDest, size_t cchDest, LPCSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCchCatA(pszDest, cchDest, pszSrc)));
inline void StringCchCat(LPWSTR pszDest, size_t cchDest, LPCWSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCchCatW(pszDest, cchDest, pszSrc)));
#undef StringCbCat
inline void StringCbCat(LPSTR pszDest, size_t cbDest, LPCSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCbCatA(pszDest, cbDest, pszSrc)));
inline void StringCbCat(LPWSTR pszDest, size_t cbDest, LPCWSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCbCatW(pszDest, cbDest, pszSrc)));
#undef StringCchCatEx
inline void StringCchCat(LPSTR pszDest, size_t cchDest, LPCSTR pszSrc,
						 LPSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCatExA(pszDest, cchDest, pszSrc, ppszDestEnd, pcchRemaining, dwFlags)));
inline void StringCchCat(LPWSTR pszDest, size_t cchDest, LPCWSTR pszSrc,
						 LPWSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCatExW(pszDest, cchDest, pszSrc, ppszDestEnd, pcchRemaining, dwFlags)));
#undef StringCbCatEx
inline void StringCbCat(LPSTR pszDest, size_t cbDest, LPCSTR pszSrc,
						LPSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCatExA(pszDest, cbDest, pszSrc, ppszDestEnd, pcbRemaining, dwFlags)));
inline void StringCbCat(LPWSTR pszDest, size_t cbDest, LPCWSTR pszSrc,
						LPWSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCatExW(pszDest, cbDest, pszSrc, ppszDestEnd, pcbRemaining, dwFlags)));
#undef StringCchCatN
inline void StringCchCatN(LPSTR pszDest, size_t cchDest, LPCSTR pszSrc, size_t cchToAppend)
	assertl_reflect_as(SUCCEEDED(::StringCchCatNA(pszDest, cchDest, pszSrc, cchToAppend)));
inline void StringCchCatN(LPWSTR pszDest, size_t cchDest, LPCWSTR pszSrc, size_t cchToAppend)
	assertl_reflect_as(SUCCEEDED(::StringCchCatNW(pszDest, cchDest, pszSrc, cchToAppend)));
#undef StringCbCatN
inline void StringCbCatN(LPSTR pszDest, size_t cbDest, LPCSTR pszSrc, size_t cbToAppend)
	assertl_reflect_as(SUCCEEDED(::StringCbCatNA(pszDest, cbDest, pszSrc, cbToAppend)));
inline void StringCbCatN(LPWSTR pszDest, size_t cbDest, LPCWSTR pszSrc, size_t cbToAppend)
	assertl_reflect_as(SUCCEEDED(::StringCbCatNW(pszDest, cbDest, pszSrc, cbToAppend)));
#undef StringCchCatNEx
inline void StringCchCatN(LPSTR pszDest, size_t cchDest,
						  LPCSTR pszSrc, size_t cchToAppend,
						  LPSTR *ppszDestEnd, size_t *pcchRemaining,
						  DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCatNExA(pszDest, cchDest, pszSrc, cchToAppend, ppszDestEnd, pcchRemaining, dwFlags)));
inline void StringCchCatN(LPWSTR pszDest, size_t cchDest,
						  LPCWSTR pszSrc, size_t cchToAppend,
						  LPWSTR *ppszDestEnd, size_t *pcchRemaining,
						  DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCatNExW(pszDest, cchDest, pszSrc, cchToAppend, ppszDestEnd, pcchRemaining, dwFlags)));
#undef StringCbCatNEx
inline void StringCbCatN(LPSTR pszDest, size_t cbDest,
						 LPCSTR pszSrc, size_t cbToAppend,
						 LPSTR *ppszDestEnd, size_t *pcbRemaining,
						 DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCatNExA(pszDest, cbDest, pszSrc, cbToAppend, ppszDestEnd, pcbRemaining, dwFlags)));
inline void StringCbCatN(LPWSTR pszDest, size_t cbDest,
						 LPCWSTR pszSrc, size_t cbToAppend,
						 LPWSTR *ppszDestEnd, size_t *pcbRemaining,
						 DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCatNExW(pszDest, cbDest, pszSrc, cbToAppend, ppszDestEnd, pcbRemaining, dwFlags)));
#undef StringCchVPrintf
inline void StringCchVPrintf(LPSTR pszDest, size_t cchDest, LPCSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCchVPrintfA(pszDest, cchDest, pszFormat, argList)));
inline void StringCchVPrintf(LPWSTR pszDest, size_t cchDest, LPCWSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCchVPrintfW(pszDest, cchDest, pszFormat, argList)));
#undef StringCbVPrintf
inline void StringCbVPrintf(LPSTR pszDest, size_t cbDest, LPCSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCbVPrintfA(pszDest, cbDest, pszFormat, argList)));
inline void StringCbVPrintf(LPWSTR pszDest, size_t cbDest, LPCWSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCbVPrintfW(pszDest, cbDest, pszFormat, argList)));
#undef StringCchPrintf
inline void StringCchPrintf(LPSTR pszDest, size_t cchDest, LPCSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCchPrintfA(pszDest, cchDest, pszFormat)));
inline void StringCchPrintf(LPWSTR pszDest, size_t cchDest, LPCWSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCchPrintfW(pszDest, cchDest, pszFormat)));
#undef StringCbPrintf
inline void StringCbPrintf(LPSTR pszDest, size_t cbDest, LPCSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCbPrintfA(pszDest, cbDest, pszFormat)));
inline void StringCbPrintf(LPWSTR pszDest, size_t cbDest, LPCWSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCbPrintfW(pszDest, cbDest, pszFormat)));
#undef StringCchPrintfEx
inline void StringCchPrintf(LPSTR pszDest, size_t cchDest, LPSTR *ppszDestEnd,
							size_t *pcchRemaining, DWORD dwFlags, LPCSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCchPrintfExA(pszDest, cchDest, ppszDestEnd, pcchRemaining, dwFlags, pszFormat)));
inline void StringCchPrintf(LPWSTR pszDest, size_t cchDest, LPWSTR *ppszDestEnd,
							size_t *pcchRemaining, DWORD dwFlags, LPCWSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCchPrintfExW(pszDest, cchDest, ppszDestEnd, pcchRemaining, dwFlags, pszFormat)));
#undef StringCbPrintfEx
inline void StringCbPrintf(LPSTR pszDest, size_t cbDest, LPSTR *ppszDestEnd,
						   size_t *pcbRemaining, DWORD dwFlags, LPCSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCbPrintfExA(pszDest, cbDest, ppszDestEnd, pcbRemaining, dwFlags, pszFormat)));
inline void StringCbPrintf(LPWSTR pszDest, size_t cbDest, LPWSTR *ppszDestEnd,
						   size_t *pcbRemaining, DWORD dwFlags, LPCWSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCbPrintfExW(pszDest, cbDest, ppszDestEnd, pcbRemaining, dwFlags, pszFormat)));
#undef StringCchVPrintfEx
inline void StringCchVPrintf(LPSTR pszDest, size_t cchDest, LPSTR *ppszDestEnd,
							 size_t *pcchRemaining, DWORD dwFlags, LPCSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCchVPrintfExA(pszDest, cchDest, ppszDestEnd, pcchRemaining, dwFlags, pszFormat, argList)));
inline void StringCchVPrintf(LPWSTR pszDest, size_t cchDest, LPWSTR *ppszDestEnd,
							 size_t *pcchRemaining, DWORD dwFlags, LPCWSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCchVPrintfExW(pszDest, cchDest, ppszDestEnd, pcchRemaining, dwFlags, pszFormat, argList)));
#undef StringCbVPrintfEx
inline void StringCbVPrintf(LPSTR pszDest, size_t cbDest, LPSTR *ppszDestEnd,
							size_t *pcbRemaining, DWORD dwFlags, LPCSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCbVPrintfExA(pszDest, cbDest, ppszDestEnd, pcbRemaining, dwFlags, pszFormat, argList)));
inline void StringCbVPrintf(LPWSTR pszDest, size_t cbDest, LPWSTR *ppszDestEnd,
							size_t *pcbRemaining, DWORD dwFlags, LPCWSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCbVPrintfExW(pszDest, cbDest, ppszDestEnd, pcbRemaining, dwFlags, pszFormat, argList)));
#undef StringCchGets
inline void StringCchGets(LPSTR pszDest, size_t cchDest)
	assertl_reflect_as(SUCCEEDED(::StringCchGetsA(pszDest, cchDest)));
inline void StringCchGets(LPWSTR pszDest, size_t cchDest)
	assertl_reflect_as(SUCCEEDED(::StringCchGetsW(pszDest, cchDest)));
#undef StringCbGets
inline void StringCbGets(LPSTR pszDest, size_t cbDest)
	assertl_reflect_as(SUCCEEDED(::StringCbGetsA(pszDest, cbDest)));
inline void StringCbGets(LPWSTR pszDest, size_t cbDest)
	assertl_reflect_as(SUCCEEDED(::StringCbGetsW(pszDest, cbDest)));
#undef StringCchGetsEx
inline void StringCchGets(LPSTR pszDest, size_t cchDest,
						  LPSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchGetsExA(pszDest, cchDest, ppszDestEnd, pcchRemaining, dwFlags)));
inline void StringCchGets(LPWSTR pszDest, size_t cchDest,
						  LPWSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchGetsExW(pszDest, cchDest, ppszDestEnd, pcchRemaining, dwFlags)));
#undef StringCbGetsEx
inline void StringCbGets(LPSTR pszDest, size_t cbDest,
						 LPSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbGetsExA(pszDest, cbDest, ppszDestEnd, pcbRemaining, dwFlags)));
inline void StringCbGets(LPWSTR pszDest, size_t cbDest,
						 LPWSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbGetsExW(pszDest, cbDest, ppszDestEnd, pcbRemaining, dwFlags)));
#undef StringCchLength
inline void StringCchLength(LPCSTR psz, size_t cchMax, size_t *pcchLength)
	assertl_reflect_as(SUCCEEDED(::StringCchLengthA(psz, cchMax, pcchLength)));
inline void StringCchLength(LPCWSTR psz, size_t cchMax, size_t *pcchLength)
	assertl_reflect_as(SUCCEEDED(::StringCchLengthW(psz, cchMax, pcchLength)));
#undef StringCbLength
inline void StringCbLength(LPCSTR psz, size_t cbMax, size_t *pcbLength)
	assertl_reflect_as(SUCCEEDED(::StringCbLengthA(psz, cbMax, pcbLength)));
inline void StringCbLength(LPCWSTR psz, size_t cbMax, size_t *pcbLength)
	assertl_reflect_as(SUCCEEDED(::StringCbLengthW(psz, cbMax, pcbLength)));
#pragma endregion

}
#pragma endregion

export namespace WX {

template<bool IsUnicode>
using XCHAR = std::conditional_t<IsUnicode, WCHAR, CHAR>;
template<bool IsUnicode>
using LPXSTR = std::conditional_t<IsUnicode, LPWSTR, LPSTR>;
template<bool IsUnicode>
using LPCXSTR = std::conditional_t<IsUnicode, LPCWSTR, LPCSTR>;

template<class TCHAR>
concept IsCharA = std::is_same_v<TCHAR, CHAR> || std::is_same_v<TCHAR, LPSTR> || std::is_same_v<TCHAR, LPCSTR>;
template<class TCHAR>
concept IsCharW = std::is_same_v<TCHAR, WCHAR> || std::is_same_v<TCHAR, LPWSTR> || std::is_same_v<TCHAR, LPCWSTR>;

template<bool IsUnicode, class AnyTypeW, class AnyTypeA>
constexpr auto AnyX(AnyTypeW *w, AnyTypeA *a) {
	if_c(IsUnicode)
		 return w;
	else return a;
}
template<bool IsUnicode, class AnyTypeW, class AnyTypeA>
constexpr auto &AnyX(AnyTypeW &w, AnyTypeA &a) {
	if_c(IsUnicode)
		 return w;
	else return a;
}
template<bool IsUnicode, class AnyTypeW, class AnyTypeA>
constexpr auto AnyX(AnyTypeW &&w, AnyTypeA &&a) {
	if_c(IsUnicode)
		 return w;
	else return a;
}

constexpr size_t MaxLenPath = MAX_PATH;
constexpr size_t MaxLenTitle = MaxLenPath * 3;
constexpr size_t MaxLenClass = 256;
constexpr size_t MaxLenNotice = 32767;

#pragma region Strings
enum_class(CodePages, UINT,
	Active       = CP_ACP,
	OEM          = CP_OEMCP,
	Macintosh    = CP_MACCP,
	ThreadActive = CP_THREAD_ACP,
	Symbol       = CP_SYMBOL,
	UTF7         = CP_UTF7,
	UTF8         = CP_UTF8);
template<class TCHAR>
class StringBase;
template<class CharType = TCHAR> const StringBase<CharType> CString(size_t uLen, const CharType *lpString);
template<class CharType = TCHAR> const StringBase<CharType> CString(const CharType *lpString, size_t maxLen);
template<class CharType>
inline size_t Length(const CharType *lpString, size_t MaxLen) {
	WX::StringCchLength(lpString, MaxLen, &MaxLen);
	return MaxLen;
}
template<class TCHAR>
class StringBase {
	using LPTSTR = TCHAR *;
	using LPCTSTR = const TCHAR *;
	enum StrFlags : size_t {
		STR_REF = 0,
		STR_READONLY = 1,
		STR_MUTABLE = 2,
		STR_RELEASE = 4
	};
	mutable LPTSTR lpsz = O;
	mutable size_t Len : sizeof(void *) * 8 - 3;
	mutable size_t Flags : 3;
private:
	template<class _TCHAR> friend const StringBase<_TCHAR> CString(size_t, const _TCHAR *);
	template<class _TCHAR> friend const StringBase<_TCHAR> CString(const _TCHAR *, size_t );
	StringBase(const StringBase &) = delete;
	StringBase(LPTSTR lpBuffer, size_t len, UINT flags) :
		lpsz(lpBuffer), Len((UINT)len), Flags(flags) {
		if (len <= 0 || !lpBuffer) {
			Len = 0;
			lpsz = O;
		}
	}
	StringBase(size_t len, LPCTSTR lpString) : StringBase(const_cast<LPTSTR>(lpString), len, STR_READONLY) {}
public:
	StringBase() : Len(0), Flags(0) {}
	StringBase(Null) : Len(0), Flags(0) {}
	StringBase(StringBase &&str) : StringBase(str.lpsz, str.Len, str.Flags) { str.lpsz = O, str.Len = 0, str.Flags = STR_REF; }
	explicit StringBase(size_t Len) : lpsz(Alloc(Len)), Len(Len), Flags(STR_MUTABLE | STR_RELEASE) {}
	StringBase(size_t Len, LPTSTR lpBuffer) : StringBase(lpBuffer, Len, STR_MUTABLE | STR_RELEASE) {}
	StringBase(TCHAR ch) : lpsz(Alloc(1)), Len(1), Flags(STR_MUTABLE | STR_RELEASE) reflect_to(lpsz[0] = ch);
	template<size_t len> StringBase(TCHAR(&str)[len]) : StringBase(str, len - 1, STR_REF) {}
	template<size_t len> StringBase(const TCHAR(&str)[len]) : StringBase(const_cast<LPTSTR>(str), len - 1, STR_READONLY) {}
	~StringBase() reflect_to(Free());
public: // Memories Management
	static inline LPTSTR Realloc(size_t len, LPTSTR lpsz) {
		if (!lpsz && len <= 0) return O;
		if (lpsz && len <= 0) {
			Free(lpsz);
			return O;
		}
		if (!lpsz) return Alloc(len);
		return (LPTSTR)realloc(lpsz, (len + 1) * sizeof(TCHAR));
	}
	static inline LPTSTR Alloc(size_t len) {
		if (len == 0) return O;
		auto nlen = (len + 1) * sizeof(TCHAR);
		auto lpsz = (LPTSTR)malloc(nlen);
		ZeroMemory(lpsz, nlen);
		return lpsz;
	}
	static inline void Free(void *lpsz) reflect_to(if (lpsz) free(lpsz));
	static inline LPTSTR Resize(LPTSTR &lpsz, size_t len) reflect_as(lpsz = Realloc(len, lpsz));
	static inline void AutoFree(LPTSTR &lpsz) reflect_to(Free(lpsz); lpsz = O);
	static inline void AutoCopy(LPTSTR &lpsz, const StringBase &str) {
		Resize(lpsz, str.Length());
		str.CopyTo(lpsz, str.Length() + 1);
	}
public:
	inline bool IsAlloced() const reflect_as(lpsz && (Flags &STR_RELEASE));
	inline void Free() {
		if (IsAlloced()) {
			Free(lpsz);
			lpsz = O;
		}
		Len = 0;
	}
	inline bool IsReadOnly() const reflect_as(Flags & STR_READONLY);
	inline bool IsMutable() const reflect_as(Flags & STR_MUTABLE);
	inline auto&ToMutable() {
		if (!IsMutable())
			self = +self;
		retself;
	}
	inline auto&Shrink() {
		Len = (UINT)WX::Length(lpsz, Len + 1);
		if (IsMutable())
			lpsz = Realloc(Len, lpsz);
		retself;
	}
	inline auto&Resize(size_t NewLen) {
		if (NewLen <= 0) retself;
		Len = (UINT)NewLen;
		if (IsReadOnly()) retself;
		if (!IsMutable()) retself;
		auto OldLen = WX::Length(lpsz, Len + 1);
		lpsz = Realloc(NewLen, lpsz);
		if (NewLen < OldLen)
			lpsz[OldLen] = 0;
		retself;
	}
	inline auto&Copy(LPCTSTR lpSrc)
		reflect_to_self(WX::StringCchCopy(lpsz, Length(), lpSrc));
	inline auto&CopyTo(LPTSTR lpDst, size_t lenDst) const {
		if (!lpDst && lenDst) retself;
		if (auto len = Length())
			WX::StringCchCopy(lpDst, lenDst, lpsz);
		else
			lpDst[0] = '\0';
		retself;
	}
public:
	inline LPTSTR str() {
		if (!lpsz || !Len) return O;
		assertl(!IsReadOnly());
		return lpsz;
	}
	inline LPCTSTR c_str() const reflect_as(lpsz && Len ? lpsz : O);
	inline LPCTSTR c_str_safe() const {
		if (Len && lpsz) 
			return lpsz;
		if_c (IsCharW<TCHAR>)
			 return L"";
		else return "";
	}
public:
	inline size_t Length() const reflect_as(lpsz ? Len : 0);
	inline size_t Size() const reflect_as(lpsz ? (Len + 1) * sizeof(TCHAR) : 0);
public:
	inline LPTSTR begin() reflect_as(Len ? lpsz : O);
	inline LPTSTR end() reflect_as(Len && lpsz ? lpsz + Len : O);
	inline LPCTSTR begin() const reflect_as(Len ? lpsz : O);
	inline LPCTSTR end() const reflect_as(Len &&lpsz ? lpsz + Len : O);
public:
	inline operator LPTSTR () reflect_as(str());
	inline operator bool() const reflect_as(lpsz && Len);
	inline operator LPCTSTR () const reflect_as(Len ? lpsz : O);
	inline StringBase operator&() reflect_as({ Len, 0, lpsz });
	inline const StringBase operator&() const reflect_as({ Len, lpsz });
	inline LPTSTR operator*() const {
		if (!lpsz || !Len) return O;
		auto lpsz = StringBase::Alloc(Len);
		CopyMemory(lpsz, this->lpsz, (Len + 1) * sizeof(TCHAR));
		lpsz[Len] = '\0';
		return lpsz;
	}
	inline StringBase operator+() const {
		if (!lpsz || !Len) return O;
		auto lpsz = StringBase::Alloc(Len);
		CopyMemory(lpsz, this->lpsz, (Len + 1) * sizeof(TCHAR));
		lpsz[Len] = '\0';
		return { Len, lpsz };
	}
	inline StringBase operator-() const {
		size_t nLen = WX::Length(lpsz, Len + 1);
		if (nLen <= 0) return O;
		auto lpsz = StringBase::Alloc(nLen);
		CopyMemory(lpsz, this->lpsz, (nLen + 1) * sizeof(TCHAR));
		lpsz[nLen] = '\0';
		return{ nLen, lpsz };
	}
public:
	auto operator=(const StringBase &str) = delete;
	inline auto &operator=(const StringBase &str) const noexcept {
		lpsz = str.lpsz;
		Len = str.Len;
		Flags = STR_READONLY;
		retself;
	}
	inline auto &operator=(StringBase &&str) noexcept {
		lpsz = str.lpsz, str.lpsz = O;
		Len = str.Len, str.Len = 0;
		Flags = str.Flags, str.Flags = STR_REF;
		retself;
	}
	inline auto &operator=(StringBase &str) noexcept {
		lpsz = str.lpsz;
		Len = str.Len;
		Flags = STR_REF;
		retself;
	}
	inline auto &operator+=(const StringBase &str) {
		if (!str.lpsz || !str.Len) retself;
		if (!lpsz || !Len) return self = +str;
		auto nLen = Len + str.Len;
		if (!IsMutable() || IsReadOnly()) {
			auto lpsz = StringBase::Alloc(Len);
			CopyMemory(lpsz, this->lpsz, (Len + 1) * sizeof(TCHAR));
			if (!(Flags & STR_RELEASE))
				Free(this->lpsz);
			this->lpsz = lpsz;
		}
		else lpsz = Realloc(nLen, lpsz);
		CopyMemory(lpsz + Len, str.lpsz, (str.Len + 1) * sizeof(TCHAR));
		Len = nLen;
		retself;
	}
};
using String = StringBase<TCHAR>;
using StringA = StringBase<CHAR>;
using StringW = StringBase<WCHAR>;
template<bool IsUnicode>
using StringX = structx(String);
/* CString */
template<class CharType>
inline const StringBase<CharType> CString(size_t Len, const CharType *lpString) {
	if (Len == 0 || !*lpString) return O;
	return { Len, lpString };
}
template<class CharType>
inline const StringBase<CharType> CString(const CharType *lpString, size_t MaxLen) {
	if (!lpString) return O;
	return { WX::Length(lpString, MaxLen), lpString };
}	 
/* Literal operator of String  */
inline const StringA operator ""_A(LPCSTR lpString, size_t uLen) {
	if (uLen == 0 || !*lpString) return O;
	return CString(uLen, lpString);
}
inline const StringW operator ""_W(LPCWSTR lpString, size_t uLen) {
	if (uLen == 0 || !*lpString) return O;
	return CString(uLen, lpString);
}
inline const String operator ""_S(LPCTSTR lpString, size_t uLen) {
	if (uLen == 0 || !*lpString) return O;
	return CString(uLen, lpString);
}
/* Fits */
inline StringA FitsA(const StringW &str, CodePages cp = CodePages::Active) {
	if (!str) return O;
	int tLen, uLen = (int)str.Length();
	LPCWSTR lpString = str;
	assertl((tLen = WideCharToMultiByte(cp.yield(), 0, lpString, (int)uLen, O, 0, O, O)) > 0);
	// if (tLen != uLen) warnning glyphs missing 
	auto lpsz = StringA::Alloc(tLen);
	assertl(tLen == WideCharToMultiByte(cp.yield(), 0, lpString, (int)uLen, lpsz, tLen, O, O));
	lpsz[tLen] = 0;
	return{ (size_t)tLen, lpsz };
}
inline StringW FitsW(const StringA &str, CodePages cp = CodePages::Active) {
	if (!str) return O;
	int tLen, uLen = (int)str.Length();
	LPCSTR lpString = str;
	assertl((tLen = MultiByteToWideChar(cp.yield(), 0, lpString, (int)uLen, O, 0)) > 0);
	// if (tLen != uLen) warnning glyphs missing 
	auto lpsz = StringW::Alloc(tLen);
	assertl(tLen == MultiByteToWideChar(cp.yield(), 0, lpString, (int)uLen, lpsz, tLen));
	lpsz[tLen] = 0;
	return{ (size_t)tLen, lpsz };
}
template<bool IsUnicode = WX::IsUnicode, class TCHAR = ::TCHAR>
inline auto Fits(StringBase<TCHAR> str) {
	if_c (std::is_same_v<XCHAR<IsUnicode>, TCHAR>)
		 reflect_as(str)
	elif_c (IsUnicode)
		 reflect_as(FitsW(str))
	else reflect_as(FitsA(str))
}
template<class CharType>
inline String Fits(const CharType *lpString, size_t MaxLen, CodePages cp = CodePages::Active) {
	if (!lpString || !MaxLen) return O;
	auto uLen = WX::Length(lpString, MaxLen);
	if (!uLen) return O;
	if_c (std::is_same_v<CharType, TCHAR>) {
		auto lpsz = String::Alloc(uLen);
		CopyMemory(lpsz, lpString, (uLen + 1) * sizeof(TCHAR));
		return{ uLen, lpsz };
	}
	else {
		int tLen;
		if_c (IsUnicode)
			assertl((tLen = MultiByteToWideChar(cp.yield(), 0, lpString, (int)uLen, O, 0)) > 0)
		else assertl((tLen = WideCharToMultiByte(cp.yield(), 0, lpString, (int)uLen, O, 0, O, O)) > 0)
			// if (tLen != uLen) warnning glyphs missing 
			auto lpsz = String::Alloc(tLen);
		if_c (IsUnicode)
			assertl(tLen == MultiByteToWideChar(cp.yield(), 0, lpString, (int)uLen, lpsz, tLen))
		else assertl(tLen == WideCharToMultiByte(cp.yield(), 0, lpString, (int)uLen, lpsz, tLen, O, O))
			lpsz[tLen] = 0;
		return{ (size_t)tLen, lpsz };
	}
}
/* Misc */
inline size_t LengthOf(const StringBase<TCHAR> &str) reflect_as(str.Length());
template<class TCHAR, class... Args>
inline size_t LengthOf(const StringBase<TCHAR> &str, const Args&... args) reflect_as(str.Length() + (LengthOf((const StringBase<TCHAR> &)args) + ...));
template<class TCHAR>
inline TCHAR *Copies(TCHAR *lpBuffer) reflect_as(lpBuffer);
template<class TCHAR, class... Args>
inline TCHAR *Copies(TCHAR *lpBuffer, const StringBase<TCHAR> &str, const Args &... args) {
	auto uLen = str.Length();
	if (uLen > 0) CopyMemory(lpBuffer, str, uLen * sizeof(TCHAR));
	return Copies(lpBuffer + uLen, args...);
}
template<class TCHAR>
inline void Copy(StringBase<TCHAR> &str, const TCHAR *lpSrc)
	reflect_to(StringCchCopy(str, str.Length(), lpSrc));
template<class TCHAR, size_t len>
inline void Copy(TCHAR(&str)[len], const StringBase<TCHAR> &src)
	reflect_to(StringCchCopy(str, len, src));
template<class TCHAR, class... Args>
inline StringBase<TCHAR> Concat(const StringBase<TCHAR> &str, const Args &... args) {
	size_t totalLen = LengthOf(str, args...);
	auto lpsz = StringBase<TCHAR>::Alloc(totalLen);
	Copies(lpsz, str, args...);
	return{ totalLen, lpsz };
}
template<class AnyType>
inline void Fill(AnyType *lpArray, const AnyType &Sample, size_t Len) {
	while (Len--)
		CopyMemory(lpArray++, &Sample, sizeof(AnyType));
}
/* format */
constexpr size_t Len_sprintf_buff = 1024;
template<class TCHAR = ::TCHAR>
inline StringBase<TCHAR> format(const TCHAR *lpFormat, va_list argList) {
	TCHAR buff[Len_sprintf_buff];
	size_t remain = 0;
	StringCchVPrintf(buff, Len_sprintf_buff, O, &remain, STRSAFE_NULL_ON_FAILURE, lpFormat, argList);
	return +CString(buff, Len_sprintf_buff - remain + 1);
}
template<class TCHAR = ::TCHAR>
inline StringBase<TCHAR> format(const TCHAR *lpFormat, ...) {
	va_list argList;
	va_start(argList, lpFormat);
	auto &&str = format(lpFormat, argList);
	va_end(argList);
	return str;
}
#pragma endregion

/* toString - format_numeral */
template<bool IsUnicode = WX::IsUnicode>
inline StringX<IsUnicode> toString(const format_numeral &fn, IsNumber auto i) {
	XCHAR<IsUnicode> pBuffer[format_numeral::MaxLen];
	auto len = fn.push(i, pBuffer);
	return +CString(len, pBuffer);
}
template<bool IsUnicode = WX::IsUnicode>
inline auto toString(IsIntager auto i) reflect_as(toString<IsUnicode>(DEC, i));
template<bool IsUnicode = WX::IsUnicode>
inline auto toString(IsFloat auto f) reflect_as(toString<IsUnicode>(FPT, f));

/* toString - Exception */
template<bool IsUnicode>
inline auto ErrorMessage(DWORD dwErrorCode) {
	using LPTSTR = LPXSTR<IsUnicode>;
	LPTSTR lpsz;
	auto len = WX::FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		O, dwErrorCode, 0, (LPTSTR)&lpsz, 0, O);
	auto &&msg = CString(lpsz, len);
	LocalFree(lpsz);
	return +msg;
}
inline auto ErrorMessageA(DWORD dwErrorCode) reflect_as(ErrorMessage<false>(dwErrorCode));
inline auto ErrorMessageW(DWORD dwErrorCode) reflect_as(ErrorMessage<true>(dwErrorCode));
inline StringA toStringA(const Exception& err) {
	auto &&str = format(
		"File:          %s\n"
		"Function:      %s\n"
		"Sentence:      %s\n"
		"Line:          %d\n",
		err.File(),
		err.Function(),
		err.Sentence(),
		err.Line());
	if (auto dwError = err.ErrorCode())
		str += format(
			"Error Code:    %d\n"
			"Error Message: %s\n",
			dwError,
			(LPCSTR)ErrorMessageA(dwError));
	return str;
}
inline StringW toStringW(const Exception &err) reflect_as(FitsW(toStringA(err)));
template<bool IsUnicode = WX::IsUnicode>
inline auto toString(const Exception &err) {
	if_c (IsUnicode)
		 reflect_as(toStringW(err))
	else reflect_as(toStringA(err));
}

/* toString - char */
inline StringA toStringA(CHAR ch) {
	CHAR buff[2] = { ch, '\0' };
	return +CString(1, buff);
}
inline StringW toStringW(WCHAR ch) {
	WCHAR buff[2] = { ch, L'\0' };
	return +CString(1, buff);
}

/* toString - bool */
template<bool IsUnicode = WX::IsUnicode>
inline const auto &toString(bool b) {
	static const auto trueStrA = "true"_A;
	static const auto falseStrA = "false"_A;
	static const auto trueStrW = L"true"_W;
	static const auto falseStrW = L"false"_W;
	if_c (IsUnicode)
		 reflect_as(b ? trueStrW : falseStrW)
	else reflect_as(b ? trueStrA : falseStrA)
}

#pragma region Enumerator

#pragma region Enum
template<class TCHAR>
class SimpleRegex {
	using LPCTSTR = const TCHAR *;
	using String = StringBase<TCHAR>;
	static constexpr bool __a_z(TCHAR w) reflect_as('a' <= w && w <= 'z');
	static constexpr bool __A_Z(TCHAR w) reflect_as('A' <= w && w <= 'Z');
	static constexpr bool __0_9(TCHAR w) reflect_as('0' <= w && w <= '9');
	static constexpr bool __A_z(TCHAR w) reflect_as(__a_z(w) || __A_Z(w));
	static constexpr bool _word(TCHAR w) reflect_as(__A_z(w) || __0_9(w));
	static constexpr bool _Word(TCHAR w) reflect_as(_word(w) || w == '_');
	static constexpr bool __s(TCHAR w) reflect_as(w == '\n' || w == '\r' || w == '\t' || w == ' ');
	struct Token {
		friend class SimpleRegex;
		LPCTSTR lpsz;
		size_t len;
	public:
		constexpr Token() : lpsz(O), len(0) {}
		constexpr Token(LPCTSTR lpsz, LPCTSTR hpsz) : lpsz(lpsz), len(hpsz - lpsz) {}
		constexpr operator LPCTSTR() const reflect_as(lpsz);
		operator const String() const;
	};
	struct Map { Token key, val; };
	template<size_t len>
	class Maps {
		friend class SimpleRegex;
		Map map[len];
	public:
		static constexpr size_t Length = len;
		constexpr Map operator[](size_t ind) const { return map[ind]; }
	};
	struct MapN { Map map; LPCTSTR hpsz; };
	static constexpr MapN _GetMap(LPCTSTR lpsz) {
		LPCTSTR hpsz = lpsz;
		// skip blank
		while (auto ch = hpsz[0])
			if (__s(hpsz[0]))
				++hpsz;
			else
				break;
		// get key
		lpsz = hpsz;
		while (auto ch = hpsz[0])
			if (_Word(hpsz[0]))
				++hpsz;
			else
				break;
		Token key{ lpsz, hpsz };
		// skip blank
		while (auto ch = hpsz[0])
			if (__s(hpsz[0]))
				++hpsz;
			else
				break;
		// get equal
		if (hpsz[0] != '=')
			return{ {}, {} };
		++hpsz;
		// skip blank
		while (auto ch = hpsz[0])
			if (__s(hpsz[0]))
				++hpsz;
			else
				break;
		// get val
		lpsz = hpsz;
		while (auto ch = hpsz[0])
			if (hpsz[0] != ',')
				++hpsz;
			else
				break;
		Token val{ lpsz, hpsz };
		if (hpsz[0] == ',')
			++hpsz;
		return{ { key, val }, hpsz };
	}
	template<size_t count>
	static constexpr Maps<count> GetMaps(LPCTSTR lpsz) {
		Maps<count> maps;
		for (size_t i = 0; i < count; ++i) {
			auto map = _GetMap(lpsz);
			lpsz = map.hpsz;
			maps.map[i] = map.map;
		}
		return maps;
	}
public:
	template<IsEnum AnyEnum>
	static constexpr auto Table() {
		if_c (IsEnum<AnyEnum>) {
			if_c (IsCharW<TCHAR>)
				 reflect_as(GetMaps<AnyEnum::Count>(AnyEnum::__EntriesW))
			else reflect_as(GetMaps<AnyEnum::Count>(AnyEnum::__EntriesA))
		}
	}
};
/* EnumTableX */
template<IsEnum AnyEnum, class TCHAR = ::TCHAR>
constexpr auto EnumTable = SimpleRegex<TCHAR>::template Table<AnyEnum>();
template<IsEnum AnyEnum>
constexpr auto EnumTableA = EnumTable<AnyEnum, CHAR>;
template<IsEnum AnyEnum>
constexpr auto EnumTableW = EnumTable<AnyEnum, WCHAR>;
#pragma endregion

/* SimpleRegex::Token */
template<class TCHAR>
inline SimpleRegex<TCHAR>::Token::operator const StringBase<TCHAR>() const reflect_as(CString(len, lpsz));
/* EnumClassParsers */
template<class TCHAR, IsEnum AnyEnum>
StringBase<TCHAR> EnumClassParseX(AnyEnum e) {
	using EnumType = typename AnyEnum::EnumType;
	misuse_assert(IsEnum<EnumType>, "template type must be based on EnumBase");
	constexpr auto table = EnumTable<EnumType, TCHAR>;
	auto val = e.yield();
	for (auto i = 0; i < EnumType::Count; ++i)
		if (val == EnumType::__Vals[i])
			return table[i].key;
	if_c (EnumType::HasProtoEnum)
		 return EnumClassParseX<TCHAR>(reuse_as<typename EnumType::ProtoEnum>(e));
	else return toString<TCHAR>(format_numeral("d"), val);
}
template<IsEnum AnyEnum>
inline auto EnumClassParse(AnyEnum e) reflect_as(EnumClassParseX<TCHAR>(e));
template<IsEnum AnyEnum>
inline auto EnumClassParseA(AnyEnum e) reflect_as(EnumClassParseX<CHAR>(e));
template<IsEnum AnyEnum>
inline auto EnumClassParseW(AnyEnum e) reflect_as(EnumClassParseX<WCHAR>(e));
#pragma endregion
/* toString - Enum */
template<bool IsUnicode = WX::IsUnicode>
inline auto toString(IsEnum auto e) reflect_as(EnumClassParseX<XCHAR<IsUnicode>>(e));
inline auto toStringA(IsEnum auto e) reflect_as(EnumClassParseA(e));
inline auto toStringW(IsEnum auto e) reflect_as(EnumClassParseW(e));

/* Q - Quick Concatenate */
template<bool IsUnicode = WX::IsUnicode, class ...AnyType>
inline StringX<IsUnicode> Q(const AnyType & ... args) 
	reflect_as(Concat(toString<IsUnicode>(args)...));

}
