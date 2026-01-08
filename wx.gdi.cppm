module;

#define WX_CPPM_GDI
#include "wx_gdi"

export module wx.gdi;

import wx.proto;

#pragma region Win32 Prototype Includes
namespace WX {

#pragma region WinGDI.h
// AddFontResource
#undef AddFontResource
inline int AddFontResource(LPCSTR lpFileName)
	assertl_reflect_as(auto ret = ::AddFontResourceA(lpFileName); ret > 0, ret);
inline int AddFontResource(LPCWSTR lpFileName)
	assertl_reflect_as(auto ret = ::AddFontResourceW(lpFileName); ret > 0, ret);
// AnimatePalette
inline void AnimatePalette(HPALETTE hPal, UINT iStartIndex, UINT cEntries, CONST PALETTEENTRY *ppe)
	assertl_reflect_as(::AnimatePalette(hPal, iStartIndex, cEntries, ppe));
// Arc
inline void Arc(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
	assertl_reflect_as(::Arc(hdc, x1, y1, x2, y2, x3, y3, x4, y4));
// BitBlt
inline void BitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop)
	assertl_reflect_as(::BitBlt(hdc, x, y, cx, cy, hdcSrc, x1, y1, rop));
// CancelDC
inline void CancelDC(HDC hdc)
	assertl_reflect_as(::CancelDC(hdc));
// Chord
inline void Chord(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
	assertl_reflect_as(::Chord(hdc, x1, y1, x2, y2, x3, y3, x4, y4));
// ChoosePixelFormat
inline int ChoosePixelFormat(HDC hdc, CONST PIXELFORMATDESCRIPTOR *ppfd)
	assertl_reflect_as(auto ret = ::ChoosePixelFormat(hdc, ppfd); ret > 0, ret);
// CloseMetaFile
inline HMETAFILE CloseMetaFile(HDC hdc)
	assertl_reflect_as(auto ret = ::CloseMetaFile(hdc), ret);
// CombineRgn
inline int CombineRgn(HRGN hrgnDst, HRGN hrgnSrc1, HRGN hrgnSrc2, int iMode)
	assertl_reflect_as(auto ret = ::CombineRgn(hrgnDst, hrgnSrc1, hrgnSrc2, iMode); ret != ERROR, ret);
// CopyMetaFile
#undef CopyMetaFile
inline HMETAFILE CopyMetaFile(HMETAFILE hMetaFile, LPCSTR lpFileName)
	assertl_reflect_as(auto ret = ::CopyMetaFileA(hMetaFile, lpFileName), ret);
inline HMETAFILE CopyMetaFile(HMETAFILE hMetaFile, LPCWSTR lpFileName)
	assertl_reflect_as(auto ret = ::CopyMetaFileW(hMetaFile, lpFileName), ret);
// CreateBitmap
inline HBITMAP CreateBitmap(int nWidth, int nHeight, UINT nPlanes, UINT nBitCount, CONST VOID *lpBits)
	assertl_reflect_as(auto ret = ::CreateBitmap(nWidth, nHeight, nPlanes, nBitCount, lpBits), ret);
// CreateBitmapIndirect
inline HBITMAP CreateBitmapIndirect(CONST BITMAP *pbm)
	assertl_reflect_as(auto ret = ::CreateBitmapIndirect(pbm), ret);
// CreateBrushIndirect
inline HBRUSH CreateBrushIndirect(CONST LOGBRUSH *plbrush)
	assertl_reflect_as(auto ret = ::CreateBrushIndirect(plbrush), ret);
// CreateCompatibleBitmap
inline HBITMAP CreateCompatibleBitmap(HDC hdc, int cx, int cy)
	assertl_reflect_as(auto ret = ::CreateCompatibleBitmap(hdc, cx, cy), ret);
// CreateDiscardableBitmap
inline HBITMAP CreateDiscardableBitmap(HDC hdc, int cx, int cy)
	assertl_reflect_as(auto ret = ::CreateDiscardableBitmap(hdc, cx, cy), ret);
// CreateCompatibleDC
inline HDC CreateCompatibleDC(HDC hdc)
	assertl_reflect_as(auto ret = ::CreateCompatibleDC(hdc), ret);
// CreateDC
#undef CreateDC
inline HDC CreateDC(LPCSTR pwszDriver, LPCSTR pwszDevice, LPCSTR pszPort, CONST DEVMODEA *pdm)
	assertl_reflect_as(auto ret = ::CreateDCA(pwszDriver, pwszDevice, pszPort, pdm), ret);
inline HDC CreateDC(LPCWSTR pwszDriver, LPCWSTR pwszDevice, LPCWSTR pszPort, CONST DEVMODEW *pdm)
	assertl_reflect_as(auto ret = ::CreateDCW(pwszDriver, pwszDevice, pszPort, pdm), ret);
// CreateDIBitmap
inline HBITMAP CreateDIBitmap(HDC hdc, CONST BITMAPINFOHEADER *pbmih, DWORD flInit, CONST VOID *pjBits, CONST BITMAPINFO *pbmi, UINT iUsage)
	assertl_reflect_as(auto ret = ::CreateDIBitmap(hdc, pbmih, flInit, pjBits, pbmi, iUsage), ret);
// CreateDIBPatternBrush
inline HBRUSH CreateDIBPatternBrush(HGLOBAL h, UINT iUsage)
	assertl_reflect_as(auto ret = ::CreateDIBPatternBrush(h, iUsage), ret);
// CreateDIBPatternBrushPt
inline HBRUSH CreateDIBPatternBrushPt(CONST VOID *lpPackedDIB, UINT iUsage)
	assertl_reflect_as(auto ret = ::CreateDIBPatternBrushPt(lpPackedDIB, iUsage), ret);
// CreateEllipticRgn
inline HRGN CreateEllipticRgn(int x1, int y1, int x2, int y2)
	assertl_reflect_as(auto ret = ::CreateEllipticRgn(x1, y1, x2, y2), ret);
// CreateEllipticRgnIndirect
inline HRGN CreateEllipticRgnIndirect(CONST RECT *lprect)
	assertl_reflect_as(auto ret = ::CreateEllipticRgnIndirect(lprect), ret);
// CreateFontIndirect
#undef CreateFontIndirect
inline HFONT CreateFontIndirect(CONST LOGFONTA *lplf)
	assertl_reflect_as(auto ret = ::CreateFontIndirectA(lplf), ret);
inline HFONT CreateFontIndirect(CONST LOGFONTW *lplf)
	assertl_reflect_as(auto ret = ::CreateFontIndirectW(lplf), ret);
// CreateFont
#undef CreateFont
inline HFONT CreateFont(int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight, DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut, DWORD iCharSet, DWORD iOutPrecision, DWORD iClipPrecision, DWORD iQuality, DWORD iPitchAndFamily, LPCSTR pszFaceName)
	assertl_reflect_as(auto ret = ::CreateFontA(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut, iCharSet, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily, pszFaceName), ret);
inline HFONT CreateFont(int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight, DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut, DWORD iCharSet, DWORD iOutPrecision, DWORD iClipPrecision, DWORD iQuality, DWORD iPitchAndFamily, LPCWSTR pszFaceName)
	assertl_reflect_as(auto ret = ::CreateFontW(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut, iCharSet, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily, pszFaceName), ret);
// CreateHatchBrush
inline HBRUSH CreateHatchBrush(int iHatch, COLORREF color)
	assertl_reflect_as(auto ret = ::CreateHatchBrush(iHatch, color), ret);
// CreateIC
#undef CreateIC
inline HDC CreateIC(LPCSTR pszDriver, LPCSTR pszDevice, LPCSTR pszPort, CONST DEVMODEA *pdm)
	assertl_reflect_as(auto ret = ::CreateICA(pszDriver, pszDevice, pszPort, pdm), ret);
inline HDC CreateIC(LPCWSTR pszDriver, LPCWSTR pszDevice, LPCWSTR pszPort, CONST DEVMODEW *pdm)
	assertl_reflect_as(auto ret = ::CreateICW(pszDriver, pszDevice, pszPort, pdm), ret);
// CreateMetaFile
#undef CreateMetaFile
inline HDC CreateMetaFile(LPCSTR pszFile)
	assertl_reflect_as(auto ret = ::CreateMetaFileA(pszFile), ret);
inline HDC CreateMetaFile(LPCWSTR pszFile)
	assertl_reflect_as(auto ret = ::CreateMetaFileW(pszFile), ret);
// CreatePalette
inline HPALETTE CreatePalette(CONST LOGPALETTE *plpal)
	assertl_reflect_as(auto ret = ::CreatePalette(plpal), ret);
// CreatePen
inline HPEN CreatePen(int iStyle, int cWidth, COLORREF color)
	assertl_reflect_as(auto ret = ::CreatePen(iStyle, cWidth, color), ret);
// CreatePenIndirect
inline HPEN CreatePenIndirect(CONST LOGPEN *plpen)
	assertl_reflect_as(auto ret = ::CreatePenIndirect(plpen), ret);
// CreatePolyPolygonRgn
inline HRGN CreatePolyPolygonRgn(CONST POINT *pptl, CONST INT *pc, int cPoly, int iMode)
	assertl_reflect_as(auto ret = ::CreatePolyPolygonRgn(pptl, pc, cPoly, iMode), ret);
// CreatePatternBrush
inline HBRUSH CreatePatternBrush(HBITMAP hbm)
	assertl_reflect_as(auto ret = ::CreatePatternBrush(hbm), ret);
// CreateRectRgn
inline HRGN CreateRectRgn(int x1, int y1, int x2, int y2)
	assertl_reflect_as(auto ret = ::CreateRectRgn(x1, y1, x2, y2), ret);
// CreateRectRgnIndirect
inline HRGN CreateRectRgnIndirect(CONST RECT *lprect)
	assertl_reflect_as(auto ret = ::CreateRectRgnIndirect(lprect), ret);
// CreateRoundRectRgn
inline HRGN CreateRoundRectRgn(int x1, int y1, int x2, int y2, int w, int h)
	assertl_reflect_as(auto ret = ::CreateRoundRectRgn(x1, y1, x2, y2, w, h), ret);
// CreateScalableFontResource
#undef CreateScalableFontResource
inline void CreateScalableFontResource(DWORD fdwHidden, LPCSTR lpszFont, LPCSTR lpszFile, LPCSTR lpszPath)
	assertl_reflect_as(::CreateScalableFontResourceA(fdwHidden, lpszFont, lpszFile, lpszPath));
inline void CreateScalableFontResource(DWORD fdwHidden, LPCWSTR lpszFont, LPCWSTR lpszFile, LPCWSTR lpszPath)
	assertl_reflect_as(::CreateScalableFontResourceW(fdwHidden, lpszFont, lpszFile, lpszPath));
// CreateSolidBrush
inline HBRUSH CreateSolidBrush(COLORREF color)
	assertl_reflect_as(auto ret = ::CreateSolidBrush(color), ret);
// DeleteDC
inline void DeleteDC(HDC hdc)
	assertl_reflect_as(::DeleteDC(hdc));
// DeleteMetaFile
inline void DeleteMetaFile(HMETAFILE hmf)
	assertl_reflect_as(::DeleteMetaFile(hmf));
// DeleteObject
inline void DeleteObject(HGDIOBJ ho)
	assertl_reflect_as(::DeleteObject(ho));
// DescribePixelFormat
inline int DescribePixelFormat(HDC hdc, int iPixelFormat, UINT nBytes, LPPIXELFORMATDESCRIPTOR ppfd)
	assertl_reflect_as(auto ret = ::DescribePixelFormat(hdc, iPixelFormat, nBytes, ppfd); ret > 0, ret);
// DeviceCapabilities
#undef DeviceCapabilities
inline int DeviceCapabilities(LPCSTR pDevice, LPCSTR pPort, WORD fwCapability, LPSTR pOutput, CONST DEVMODEA *pDevMode)
	assertl_reflect_as(auto ret = ::DeviceCapabilitiesA(pDevice, pPort, fwCapability, pOutput, pDevMode); ret >= 0, ret);
inline int DeviceCapabilities(LPCWSTR pDevice, LPCWSTR pPort, WORD fwCapability, LPWSTR pOutput, CONST DEVMODEW *pDevMode)
	assertl_reflect_as(auto ret = ::DeviceCapabilitiesW(pDevice, pPort, fwCapability, pOutput, pDevMode); ret >= 0, ret);
// DrawEscape
inline int DrawEscape(HDC hdc, int iEscape, int cjIn, LPCSTR lpIn)
	assertl_reflect_as(auto ret = ::DrawEscape(hdc, iEscape, cjIn, lpIn); ret >= 0, ret);
// Ellipse
inline void Ellipse(HDC hdc, int left, int top, int right, int bottom)
	assertl_reflect_as(::Ellipse(hdc, left, top, right, bottom));
// EnumFontFamiliesEx
#undef EnumFontFamiliesEx
inline int EnumFontFamiliesEx(HDC hdc, LPLOGFONTA lpLogfont, FONTENUMPROCA lpProc, LPARAM lParam, DWORD dwFlags)
	reflect_as(::EnumFontFamiliesExA(hdc, lpLogfont, lpProc, lParam, dwFlags));
inline int EnumFontFamiliesEx(HDC hdc, LPLOGFONTW lpLogfont, FONTENUMPROCW lpProc, LPARAM lParam, DWORD dwFlags)
	reflect_as(::EnumFontFamiliesExW(hdc, lpLogfont, lpProc, lParam, dwFlags));
// EnumFontFamilies
#undef EnumFontFamilies
inline int EnumFontFamilies(HDC hdc, LPCSTR lpLogfont, FONTENUMPROCA lpProc, LPARAM lParam)
	reflect_as(::EnumFontFamiliesA(hdc, lpLogfont, lpProc, lParam));
inline int EnumFontFamilies(HDC hdc, LPCWSTR lpLogfont, FONTENUMPROCW lpProc, LPARAM lParam)
	reflect_as(::EnumFontFamiliesW(hdc, lpLogfont, lpProc, lParam));
// EnumFonts
#undef EnumFonts
inline int EnumFonts(HDC hdc, LPCSTR lpLogfont, FONTENUMPROCA lpProc, LPARAM lParam)
	reflect_as(::EnumFontsA(hdc, lpLogfont, lpProc, lParam));
inline int EnumFonts(HDC hdc, LPCWSTR lpLogfont, FONTENUMPROCW lpProc, LPARAM lParam)
	reflect_as(::EnumFontsW(hdc, lpLogfont, lpProc, lParam));
// EnumObjects
inline int EnumObjects(HDC hdc, int nType, GOBJENUMPROC lpFunc, LPARAM lParam)
	reflect_as(::EnumObjects(hdc, nType, lpFunc, lParam));
// EqualRgn
inline bool EqualRgn(HRGN hrgn1, HRGN hrgn2)
	reflect_as(::EqualRgn(hrgn1, hrgn2));
// Escape
inline int Escape(HDC hdc, int iEscape, int cjIn, LPCSTR pvIn, LPVOID pvOut)
	assertl_reflect_as(auto ret = ::Escape(hdc, iEscape, cjIn, pvIn, pvOut); ret > 0, ret);
// ExtEscape
inline int ExtEscape(HDC hdc, int iEscape, int cjInput, LPCSTR lpInData, int cjOutput, LPSTR lpOutData)
	assertl_reflect_as(auto ret = ::ExtEscape(hdc, iEscape, cjInput, lpInData, cjOutput, lpOutData); ret > 0, ret);
// ExcludeClipRect
inline int ExcludeClipRect(HDC hdc, int left, int top, int right, int bottom)
	assertl_reflect_as(auto ret = ::ExcludeClipRect(hdc, left, top, right, bottom); ret != ERROR, ret);
// ExtCreateRegion
inline HRGN ExtCreateRegion(CONST XFORM *lpx, DWORD nCount, CONST RGNDATA *lpData)
	assertl_reflect_as(auto ret = ::ExtCreateRegion(lpx, nCount, lpData), ret);
// ExtFloodFill
inline void ExtFloodFill(HDC hdc, int x, int y, COLORREF color, UINT type)
	assertl_reflect_as(::ExtFloodFill(hdc, x, y, color, type));
// FillRgn
inline void FillRgn(HDC hdc, HRGN hrgn, HBRUSH hbr)
	assertl_reflect_as(::FillRgn(hdc, hrgn, hbr));
// FloodFill
inline void FloodFill(HDC hdc, int x, int y, COLORREF color)
	assertl_reflect_as(::FloodFill(hdc, x, y, color));
// FrameRgn
inline void FrameRgn(HDC hdc, HRGN hrgn, HBRUSH hbr, int w, int h)
	assertl_reflect_as(::FrameRgn(hdc, hrgn, hbr, w, h));
// GetROP2
inline int GetROP2(HDC hdc)
	assertl_reflect_as(auto ret = ::GetROP2(hdc); ret > 0, ret);
// GetAspectRatioFilterEx
inline void GetAspectRatioFilterEx(HDC hdc, LPSIZE lpsize)
	assertl_reflect_as(::GetAspectRatioFilterEx(hdc, lpsize));
// GetBkColor
inline COLORREF GetBkColor(HDC hdc)
	assertl_reflect_as(auto ret = ::GetBkColor(hdc); ret != CLR_INVALID, ret);
// GetDCBrushColor
inline COLORREF GetDCBrushColor(HDC hdc)
	assertl_reflect_as(auto ret = ::GetDCBrushColor(hdc); ret != CLR_INVALID, ret);
// GetDCPenColor
inline COLORREF GetDCPenColor(HDC hdc)
	assertl_reflect_as(auto ret = ::GetDCPenColor(hdc); ret != CLR_INVALID, ret);
// GetBkMode
inline int GetBkMode(HDC hdc)
	assertl_reflect_as(auto ret = ::GetBkMode(hdc); ret > 0, ret);
// GetBitmapBits
inline LONG GetBitmapBits(HBITMAP hbit, LONG cb, LPVOID lpvBits)
	assertl_reflect_as(auto ret = ::GetBitmapBits(hbit, cb, lpvBits), ret);
// GetBitmapDimensionEx
inline void GetBitmapDimensionEx(HBITMAP hbit, LPSIZE lpsize)
	assertl_reflect_as(::GetBitmapDimensionEx(hbit, lpsize));
// GetBoundsRect
inline UINT GetBoundsRect(HDC hdc, LPRECT lprect, UINT flags)
	assertl_reflect_as(auto ret = ::GetBoundsRect(hdc, lprect, flags), ret);
// GetBrushOrgEx
inline void GetBrushOrgEx(HDC hdc, LPPOINT lppt)
	assertl_reflect_as(::GetBrushOrgEx(hdc, lppt));
// GetCharWidth
#undef GetCharWidth
template<bool IsUnicode = WX::IsUnicode>
inline void GetCharWidth(HDC hdc, UINT iFirst, UINT iLast, LPINT lpBuffer) {
	if_c (IsUnicode)
		 assertl_reflect_as(::GetCharWidthA(hdc, iFirst, iLast, lpBuffer))
	else assertl_reflect_as(::GetCharWidthW(hdc, iFirst, iLast, lpBuffer))
}
// GetCharWidth32
#undef GetCharWidth32
template<bool IsUnicode = WX::IsUnicode>
inline void GetCharWidth32(HDC hdc, UINT iFirst, UINT iLast, LPINT lpBuffer) {
	if_c (IsUnicode)
		 assertl_reflect_as(::GetCharWidth32A(hdc, iFirst, iLast, lpBuffer))
	else assertl_reflect_as(::GetCharWidth32W(hdc, iFirst, iLast, lpBuffer))
}
// GetCharWidthFloat
#undef GetCharWidthFloat
template<bool IsUnicode = WX::IsUnicode>
inline void GetCharWidthFloat(HDC hdc, UINT iFirst, UINT iLast, PFLOAT lpBuffer) {
	if_c (IsUnicode)
		 assertl_reflect_as(::GetCharWidthFloatA(hdc, iFirst, iLast, lpBuffer))
	else assertl_reflect_as(::GetCharWidthFloatW(hdc, iFirst, iLast, lpBuffer))
}
// GetCharABCWidths
#undef GetCharABCWidths
template<bool IsUnicode = WX::IsUnicode>
inline void GetCharABCWidths(HDC hdc, UINT wFirst, UINT wLast, LPABC lpABC) {
	if_c (IsUnicode)
		 assertl_reflect_as(::GetCharABCWidthsA(hdc, wFirst, wLast, lpABC))
	else assertl_reflect_as(::GetCharABCWidthsW(hdc, wFirst, wLast, lpABC))
}
// GetCharABCWidthsFloat
#undef GetCharABCWidthsFloat
template<bool IsUnicode = WX::IsUnicode>
inline void GetCharABCWidthsFloat(HDC hdc, UINT iFirst, UINT iLast, LPABCFLOAT lpABC) {
	if_c (IsUnicode)
		 assertl_reflect_as(::GetCharABCWidthsFloatA(hdc, iFirst, iLast, lpABC))
	else assertl_reflect_as(::GetCharABCWidthsFloatW(hdc, iFirst, iLast, lpABC))
}
// GetClipBox
inline int GetClipBox(HDC hdc, LPRECT lprect)
	assertl_reflect_as(auto ret = ::GetClipBox(hdc, lprect); ret != ERROR, ret);
// GetClipRgn
inline int GetClipRgn(HDC hdc, HRGN hrgn)
	assertl_reflect_as(auto ret = ::GetClipRgn(hdc, hrgn); ret > 0, ret);
// GetMetaRgn
inline int GetMetaRgn(HDC hdc, HRGN hrgn)
	assertl_reflect_as(auto ret = ::GetMetaRgn(hdc, hrgn); ret > 0, ret);
// GetCurrentObject
inline HGDIOBJ GetCurrentObject(HDC hdc, UINT type)
	assertl_reflect_as(auto ret = ::GetCurrentObject(hdc, type), ret);
// GetCurrentPositionEx
inline void GetCurrentPositionEx(HDC hdc, LPPOINT lppt)
	assertl_reflect_as(::GetCurrentPositionEx(hdc, lppt));
// GetDeviceCaps
inline int GetDeviceCaps(HDC hdc, int index)
	reflect_as(::GetDeviceCaps(hdc, index));
// GetDIBits
inline int GetDIBits(HDC hdc, HBITMAP hbm, UINT start, UINT cLines, LPVOID lpvBits, LPBITMAPINFO lpbmi, UINT usage)
	assertl_reflect_as(auto ret = ::GetDIBits(hdc, hbm, start, cLines, lpvBits, lpbmi, usage); ret > 0, ret);
// GetFontData
inline DWORD GetFontData(HDC hdc, DWORD dwTable, DWORD dwOffset, PVOID pvBuffer, DWORD cjBuffer)
	assertl_reflect_as(auto ret = ::GetFontData(hdc, dwTable, dwOffset, pvBuffer, cjBuffer); ret != GCP_ERROR, ret);
// GetGlyphOutline
#undef GetGlyphOutline
template<bool IsUnicode = WX::IsUnicode>
inline DWORD GetGlyphOutline(HDC hdc, UINT uChar, UINT fuFormat, LPGLYPHMETRICS lpgm, DWORD cjBuffer, LPVOID pvBuffer, CONST MAT2 *lpmat2) {
	if_c (IsUnicode)
		 reflect_as(::GetGlyphOutlineA(hdc, uChar, fuFormat, lpgm, cjBuffer, pvBuffer, lpmat2))
	else reflect_as(::GetGlyphOutlineW(hdc, uChar, fuFormat, lpgm, cjBuffer, pvBuffer, lpmat2))
}
// GetGraphicsMode
inline int GetGraphicsMode(HDC hdc)
	assertl_reflect_as(auto ret = ::GetGraphicsMode(hdc); ret > 0, ret);
// GetMapMode
inline int GetMapMode(HDC hdc)
	assertl_reflect_as(auto ret = ::GetMapMode(hdc); ret > 0, ret);
// GetMetaFileBitsEx
inline UINT GetMetaFileBitsEx(HMETAFILE hMF, UINT cbBuffer, LPVOID lpData)
	assertl_reflect_as(auto ret = ::GetMetaFileBitsEx(hMF, cbBuffer, lpData), ret);
// GetMetaFile
#undef GetMetaFile
inline HMETAFILE GetMetaFile(LPCSTR lpName)
	assertl_reflect_as(auto ret = ::GetMetaFileA(lpName), ret);
inline HMETAFILE GetMetaFile(LPCWSTR lpName)
	assertl_reflect_as(auto ret = ::GetMetaFileW(lpName), ret);
// GetNearestColor
inline COLORREF GetNearestColor(HDC hdc, COLORREF color)
	assertl_reflect_as(auto ret = ::GetNearestColor(hdc, color); ret != CLR_INVALID, ret);
// GetNearestPaletteIndex
inline UINT GetNearestPaletteIndex(HPALETTE h, COLORREF color)
	assertl_reflect_as(auto ret = ::GetNearestPaletteIndex(h, color); ret != CLR_INVALID, ret);
// GetObjectType
inline DWORD GetObjectType(HGDIOBJ h)
	assertl_reflect_as(auto ret = ::GetObjectType(h), ret);
// GetOutlineTextMetrics
#undef GetOutlineTextMetrics
inline UINT GetOutlineTextMetrics(HDC hdc, UINT cjCopy, LPOUTLINETEXTMETRICA potm)
	assertl_reflect_as(auto ret = ::GetOutlineTextMetricsA(hdc, cjCopy, potm), ret);
inline UINT GetOutlineTextMetrics(HDC hdc, UINT cjCopy, LPOUTLINETEXTMETRICW potm)
	assertl_reflect_as(auto ret = ::GetOutlineTextMetricsW(hdc, cjCopy, potm), ret);
// GetPaletteEntries
inline UINT GetPaletteEntries(HPALETTE hpal, UINT iStart, UINT cEntries, LPPALETTEENTRY pPalEntries)
	assertl_reflect_as(auto ret = ::GetPaletteEntries(hpal, iStart, cEntries, pPalEntries), ret);
// GetPixel
inline COLORREF GetPixel(HDC hdc, int x, int y)
	assertl_reflect_as(auto ret = ::GetPixel(hdc, x, y); ret != CLR_INVALID, ret);
// GetPixelFormat
inline int GetPixelFormat(HDC hdc)
	assertl_reflect_as(auto ret = ::GetPixelFormat(hdc); ret > 0, ret);
// GetPolyFillMode
inline int GetPolyFillMode(HDC hdc)
	assertl_reflect_as(auto ret = ::GetPolyFillMode(hdc); ret > 0, ret);
// GetRasterizerCaps
inline void GetRasterizerCaps(LPRASTERIZER_STATUS lpraststat, UINT cjBytes)
	assertl_reflect_as(::GetRasterizerCaps(lpraststat, cjBytes));
// GetRandomRgn
inline int GetRandomRgn(HDC hdc, HRGN hrgn, INT i)
	assertl_reflect_as(auto ret = ::GetRandomRgn(hdc, hrgn, i); ret > 0, ret);
// GetRegionData
inline DWORD GetRegionData(HRGN hrgn, DWORD nCount, LPRGNDATA lpRgnData)
	assertl_reflect_as(auto ret = ::GetRegionData(hrgn, nCount, lpRgnData), ret);
// GetRgnBox
inline int GetRgnBox(HRGN hrgn, LPRECT lprc)
	assertl_reflect_as(auto ret = ::GetRgnBox(hrgn, lprc); ret > 0, ret);
// GetStockObject
inline HGDIOBJ GetStockObject(int i)
	assertl_reflect_as(auto ret = ::GetStockObject(i), ret);
// GetStretchBltMode
inline int GetStretchBltMode(HDC hdc)
	assertl_reflect_as(auto ret = ::GetStretchBltMode(hdc); ret > 0, ret);
// GetSystemPaletteEntries
inline UINT GetSystemPaletteEntries(HDC hdc, UINT iStart, UINT cEntries, LPPALETTEENTRY pPalEntries)
	assertl_reflect_as(auto ret = ::GetSystemPaletteEntries(hdc, iStart, cEntries, pPalEntries), ret);
// GetSystemPaletteUse
inline UINT GetSystemPaletteUse(HDC hdc)
	assertl_reflect_as(auto ret = ::GetSystemPaletteUse(hdc); ret != SYSPAL_ERROR, ret);
// GetTextCharacterExtra
inline int GetTextCharacterExtra(HDC hdc)
	assertl_reflect_as(auto ret = ::GetTextCharacterExtra(hdc); ret != 0x8000000, ret);
// GetTextAlign
inline UINT GetTextAlign(HDC hdc)
	assertl_reflect_as(auto ret = ::GetTextAlign(hdc); ret != GCP_ERROR, ret);
// GetTextColor
inline COLORREF GetTextColor(HDC hdc)
	assertl_reflect_as(auto ret = ::GetTextColor(hdc); ret != CLR_INVALID, ret);
// GetTextExtentPoint
#undef GetTextExtentPoint
inline void GetTextExtentPoint(HDC hdc, LPCSTR lpString, int c, LPSIZE lpsz)
	assertl_reflect_as(::GetTextExtentPointA(hdc, lpString, c, lpsz));
inline void GetTextExtentPoint(HDC hdc, LPCWSTR lpString, int c, LPSIZE lpsz)
	assertl_reflect_as(::GetTextExtentPointW(hdc, lpString, c, lpsz));
// GetTextExtentPoint32
#undef GetTextExtentPoint32
inline void GetTextExtentPoint32(HDC hdc, LPCSTR lpString, int c, LPSIZE psizl)
	assertl_reflect_as(::GetTextExtentPoint32A(hdc, lpString, c, psizl));
inline void GetTextExtentPoint32(HDC hdc, LPCWSTR lpString, int c, LPSIZE psizl)
	assertl_reflect_as(::GetTextExtentPoint32W(hdc, lpString, c, psizl));
// GetTextExtentExPoint
#undef GetTextExtentExPoint
inline void GetTextExtentExPoint(HDC hdc, LPCSTR lpszString, int cchString, int nMaxExtent, LPINT lpnFit, LPINT lpnDx, LPSIZE lpSize)
	assertl_reflect_as(::GetTextExtentExPointA(hdc, lpszString, cchString, nMaxExtent, lpnFit, lpnDx, lpSize));
inline void GetTextExtentExPoint(HDC hdc, LPCWSTR lpszString, int cchString, int nMaxExtent, LPINT lpnFit, LPINT lpnDx, LPSIZE lpSize)
	assertl_reflect_as(::GetTextExtentExPointW(hdc, lpszString, cchString, nMaxExtent, lpnFit, lpnDx, lpSize));
// GetTextCharset
inline int GetTextCharset(HDC hdc)
	reflect_as(::GetTextCharset(hdc));
// GetTextCharsetInfo
inline int GetTextCharsetInfo(HDC hdc, LPFONTSIGNATURE lpSig, DWORD dwFlags)
	reflect_as(::GetTextCharsetInfo(hdc, lpSig, dwFlags));
// TranslateCharsetInfo
inline void TranslateCharsetInfo(DWORD FAR *lpSrc, LPCHARSETINFO lpCs, DWORD dwFlags)
	assertl_reflect_as(::TranslateCharsetInfo(lpSrc, lpCs, dwFlags));
// GetFontLanguageInfo
inline DWORD GetFontLanguageInfo(HDC hdc)
	assertl_reflect_as(auto ret = ::GetFontLanguageInfo(hdc); ret != GCP_ERROR, ret);
// GetCharacterPlacement
#undef GetCharacterPlacement
inline DWORD GetCharacterPlacement(HDC hdc, LPCSTR lpString, int nCount, int nMexExtent, LPGCP_RESULTSA lpResults, DWORD dwFlags)
	assertl_reflect_as(auto ret = ::GetCharacterPlacementA(hdc, lpString, nCount, nMexExtent, lpResults, dwFlags), ret);
inline DWORD GetCharacterPlacement(HDC hdc, LPCWSTR lpString, int nCount, int nMexExtent, LPGCP_RESULTSW lpResults, DWORD dwFlags)
	assertl_reflect_as(auto ret = ::GetCharacterPlacementW(hdc, lpString, nCount, nMexExtent, lpResults, dwFlags), ret);
// GetFontUnicodeRanges
inline DWORD GetFontUnicodeRanges(HDC hdc, LPGLYPHSET lpgs)
	assertl_reflect_as(auto ret = ::GetFontUnicodeRanges(hdc, lpgs), ret);
// GetGlyphIndices
#undef GetGlyphIndices
inline DWORD GetGlyphIndices(HDC hdc, LPCSTR lpstr, int c, LPWORD pgi, DWORD fl)
	assertl_reflect_as(auto ret = ::GetGlyphIndicesA(hdc, lpstr, c, pgi, fl); ret != GCP_ERROR, ret);
inline DWORD GetGlyphIndices(HDC hdc, LPCWSTR lpstr, int c, LPWORD pgi, DWORD fl)
	assertl_reflect_as(auto ret = ::GetGlyphIndicesW(hdc, lpstr, c, pgi, fl); ret != GCP_ERROR, ret);
// GetTextExtentPointI
inline void GetTextExtentPointI(HDC hdc, LPWORD pgiIn, int cgi, LPSIZE psize)
	assertl_reflect_as(::GetTextExtentPointI(hdc, pgiIn, cgi, psize));
// GetTextExtentExPointI
inline void GetTextExtentExPointI(HDC hdc, LPWORD lpwszString, int cwchString, int nMaxExtent, LPINT lpnFit, LPINT lpnDx, LPSIZE lpSize)
	assertl_reflect_as(::GetTextExtentExPointI(hdc, lpwszString, cwchString, nMaxExtent, lpnFit, lpnDx, lpSize));
// GetCharWidthI
inline void GetCharWidthI(HDC hdc, UINT giFirst, UINT cgi, LPWORD pgi, LPINT piWidths)
	assertl_reflect_as(::GetCharWidthI(hdc, giFirst, cgi, pgi, piWidths));
// GetCharABCWidthsI
inline void GetCharABCWidthsI(HDC hdc, UINT giFirst, UINT cgi, LPWORD pgi, LPABC pabc)
	assertl_reflect_as(::GetCharABCWidthsI(hdc, giFirst, cgi, pgi, pabc));
// AddFontResourceEx
#undef AddFontResourceEx
inline int AddFontResourceEx(LPCSTR name, DWORD fl, PVOID res)
	assertl_reflect_as(auto ret = ::AddFontResourceExA(name, fl, res); ret > 0, ret);
inline int AddFontResourceEx(LPCWSTR name, DWORD fl, PVOID res)
	assertl_reflect_as(auto ret = ::AddFontResourceExW(name, fl, res); ret > 0, ret);
// RemoveFontResourceEx
#undef RemoveFontResourceEx
inline void RemoveFontResourceEx(LPCSTR name, DWORD fl, PVOID pdv)
	assertl_reflect_as(::RemoveFontResourceExA(name, fl, pdv));
inline void RemoveFontResourceEx(LPCWSTR name, DWORD fl, PVOID pdv)
	assertl_reflect_as(::RemoveFontResourceExW(name, fl, pdv));
// AddFontMemResourceEx
inline HANDLE AddFontMemResourceEx(PVOID pFileView, DWORD cjSize, PVOID pvResrved, DWORD *pNumFonts)
	assertl_reflect_as(auto ret = ::AddFontMemResourceEx(pFileView, cjSize, pvResrved, pNumFonts), ret);
// RemoveFontMemResourceEx
inline void RemoveFontMemResourceEx(HANDLE h)
	assertl_reflect_as(::RemoveFontMemResourceEx(h));
// GetViewportExtEx
inline void GetViewportExtEx(HDC hdc, LPSIZE lpsize)
	assertl_reflect_as(::GetViewportExtEx(hdc, lpsize));
// GetViewportOrgEx
inline void GetViewportOrgEx(HDC hdc, LPPOINT lppoint)
	assertl_reflect_as(::GetViewportOrgEx(hdc, lppoint));
// GetWindowExtEx
inline void GetWindowExtEx(HDC hdc, LPSIZE lpsize)
	assertl_reflect_as(::GetWindowExtEx(hdc, lpsize));
// GetWindowOrgEx
inline void GetWindowOrgEx(HDC hdc, LPPOINT lppoint)
	assertl_reflect_as(::GetWindowOrgEx(hdc, lppoint));
// IntersectClipRect
inline int IntersectClipRect(HDC hdc, int left, int top, int right, int bottom)
	assertl_reflect_as(auto ret = ::IntersectClipRect(hdc, left, top, right, bottom); ret != ERROR, ret);
// InvertRgn
inline void InvertRgn(HDC hdc, HRGN hrgn)
	assertl_reflect_as(::InvertRgn(hdc, hrgn));
// LineDDA
inline void LineDDA(int xStart, int yStart, int xEnd, int yEnd, LINEDDAPROC lpProc, LPARAM data)
	assertl_reflect_as(::LineDDA(xStart, yStart, xEnd, yEnd, lpProc, data));
// LineTo
inline void LineTo(HDC hdc, int x, int y)
	assertl_reflect_as(::LineTo(hdc, x, y));
// MaskBlt
inline void MaskBlt(HDC hdcDest, int xDest, int yDest, int width, int height, HDC hdcSrc, int xSrc, int ySrc, HBITMAP hbmMask, int xMask, int yMask, DWORD rop)
	assertl_reflect_as(::MaskBlt(hdcDest, xDest, yDest, width, height, hdcSrc, xSrc, ySrc, hbmMask, xMask, yMask, rop));
// PlgBlt
inline void PlgBlt(HDC hdcDest, CONST POINT *lpPoint, HDC hdcSrc, int xSrc, int ySrc, int width, int height, HBITMAP hbmMask, int xMask, int yMask)
	assertl_reflect_as(::PlgBlt(hdcDest, lpPoint, hdcSrc, xSrc, ySrc, width, height, hbmMask, xMask, yMask));
// OffsetClipRgn
inline int OffsetClipRgn(HDC hdc, int x, int y)
	assertl_reflect_as(auto ret = ::OffsetClipRgn(hdc, x, y); ret != ERROR, ret);
// OffsetRgn
inline int OffsetRgn(HRGN hrgn, int x, int y)
	assertl_reflect_as(auto ret = ::OffsetRgn(hrgn, x, y); ret != ERROR, ret);
// PatBlt
inline void PatBlt(HDC hdc, int x, int y, int w, int h, DWORD rop)
	assertl_reflect_as(::PatBlt(hdc, x, y, w, h, rop));
// Pie
inline void Pie(HDC hdc, int left, int top, int right, int bottom, int xr1, int yr1, int xr2, int yr2)
	assertl_reflect_as(::Pie(hdc, left, top, right, bottom, xr1, yr1, xr2, yr2));
// PlayMetaFile
inline void PlayMetaFile(HDC hdc, HMETAFILE hmf)
	assertl_reflect_as(::PlayMetaFile(hdc, hmf));
// PaintRgn
inline void PaintRgn(HDC hdc, HRGN hrgn)
	assertl_reflect_as(::PaintRgn(hdc, hrgn));
// PolyPolygon
inline void PolyPolygon(HDC hdc, CONST POINT *apt, CONST INT *asz, int csz)
	assertl_reflect_as(::PolyPolygon(hdc, apt, asz, csz));
// PtInRegion
inline bool PtInRegion(HRGN hrgn, int x, int y)
	reflect_as(::PtInRegion(hrgn, x, y));
// PtVisible
inline bool PtVisible(HDC hdc, int x, int y)
	assertl_reflect_as(auto ret = ::PtVisible(hdc, x, y); ret >= 0, ret);
// RectInRegion
inline bool RectInRegion(HRGN hrgn, CONST RECT *lprect)
	reflect_as(::RectInRegion(hrgn, lprect));
// RectVisible
inline int RectVisible(HDC hdc, CONST RECT *lprect)
	reflect_as(::RectVisible(hdc, lprect));
// Rectangle
inline void Rectangle(HDC hdc, int left, int top, int right, int bottom)
	assertl_reflect_as(::Rectangle(hdc, left, top, right, bottom));
// RestoreDC
inline void RestoreDC(HDC hdc, int nSavedDC)
	assertl_reflect_as(::RestoreDC(hdc, nSavedDC));
// ResetDC
#undef ResetDC
inline HDC ResetDC(HDC hdc, CONST DEVMODEA *lpdm)
	assertl_reflect_as(auto ret = ::ResetDCA(hdc, lpdm), ret);
inline HDC ResetDC(HDC hdc, CONST DEVMODEW *lpdm)
	assertl_reflect_as(auto ret = ::ResetDCW(hdc, lpdm), ret);
// RealizePalette
inline UINT RealizePalette(HDC hdc)
	assertl_reflect_as(auto ret = ::RealizePalette(hdc); ret != GCP_ERROR, ret);
// RemoveFontResource
#undef RemoveFontResource
inline void RemoveFontResource(LPCSTR lpFileName)
	assertl_reflect_as(::RemoveFontResourceA(lpFileName));
inline void RemoveFontResource(LPCWSTR lpFileName)
	assertl_reflect_as(::RemoveFontResourceW(lpFileName));
// RoundRect
inline void RoundRect(HDC hdc, int left, int top, int right, int bottom, int width, int height)
	assertl_reflect_as(::RoundRect(hdc, left, top, right, bottom, width, height));
// ResizePalette
inline void ResizePalette(HPALETTE hpal, UINT n)
	assertl_reflect_as(::ResizePalette(hpal, n));
// SaveDC
inline int SaveDC(HDC hdc)
	assertl_reflect_as(auto ret = ::SaveDC(hdc); ret > 0, ret);
// SelectClipRgn
inline int SelectClipRgn(HDC hdc, HRGN hrgn)
	assertl_reflect_as(auto ret = ::SelectClipRgn(hdc, hrgn); ret != ERROR, ret);
// ExtSelectClipRgn
inline int ExtSelectClipRgn(HDC hdc, HRGN hrgn, int mode)
	assertl_reflect_as(auto ret = ::ExtSelectClipRgn(hdc, hrgn, mode); ret != ERROR, ret);
// SetMetaRgn
inline int SetMetaRgn(HDC hdc)
	assertl_reflect_as(auto ret = ::SetMetaRgn(hdc); ret != ERROR, ret);
// SelectObject
static inline HGDIOBJ SelectObject(HDC hdc, HGDIOBJ h)
	assertl_reflect_as(auto ret = ::SelectObject(hdc, h); ret != HGDI_ERROR, ret);
// SelectPalette
inline HPALETTE SelectPalette(HDC hdc, HPALETTE hPal, BOOL bForceBkgd)
	assertl_reflect_as(auto ret = ::SelectPalette(hdc, hPal, bForceBkgd), ret);
// SetBkColor
inline COLORREF SetBkColor(HDC hdc, COLORREF color)
	assertl_reflect_as(auto ret = ::SetBkColor(hdc, color); ret != CLR_INVALID, ret);
// SetDCBrushColor
inline COLORREF SetDCBrushColor(HDC hdc, COLORREF color)
	assertl_reflect_as(auto ret = ::SetDCBrushColor(hdc, color); ret != CLR_INVALID, ret);
// SetDCPenColor
inline COLORREF SetDCPenColor(HDC hdc, COLORREF color)
	assertl_reflect_as(auto ret = ::SetDCPenColor(hdc, color); ret != GCP_ERROR, ret);
// SetBkMode
inline int SetBkMode(HDC hdc, int mode)
	assertl_reflect_as(auto ret = ::SetBkMode(hdc, mode); ret > 0, ret);
// SetBitmapBits
inline LONG SetBitmapBits(HBITMAP hbm, DWORD cb, CONST VOID *pvBits)
	assertl_reflect_as(auto ret = ::SetBitmapBits(hbm, cb, pvBits), ret);
// SetBoundsRect
inline UINT SetBoundsRect(HDC hdc, CONST RECT *lprect, UINT flags)
	assertl_reflect_as(auto ret = ::SetBoundsRect(hdc, lprect, flags), ret);
// SetDIBits
inline int SetDIBits(HDC hdc, HBITMAP hbm, UINT start, UINT cLines, CONST VOID *lpBits, CONST BITMAPINFO *lpbmi, UINT ColorUse)
	assertl_reflect_as(auto ret = ::SetDIBits(hdc, hbm, start, cLines, lpBits, lpbmi, ColorUse); ret > 0, ret);
// SetDIBitsToDevice
inline int SetDIBitsToDevice(HDC hdc, int xDest, int yDest, DWORD w, DWORD h, int xSrc, int ySrc, UINT StartScan, UINT cLines, CONST VOID *lpvBits, CONST BITMAPINFO *lpbmi, UINT ColorUse)
	reflect_as(::SetDIBitsToDevice(hdc, xDest, yDest, w, h, xSrc, ySrc, StartScan, cLines, lpvBits, lpbmi, ColorUse));
// SetMapperFlags
inline DWORD SetMapperFlags(HDC hdc, DWORD flags)
	assertl_reflect_as(auto ret = ::SetMapperFlags(hdc, flags); ret != GCP_ERROR, ret);
// SetGraphicsMode
inline int SetGraphicsMode(HDC hdc, int iMode)
	assertl_reflect_as(auto ret = ::SetGraphicsMode(hdc, iMode); ret > 0, ret);
// SetMapMode
inline int SetMapMode(HDC hdc, int iMode)
	assertl_reflect_as(auto ret = ::SetMapMode(hdc, iMode); ret > 0, ret);
// SetLayout
inline DWORD SetLayout(HDC hdc, DWORD l)
	assertl_reflect_as(auto ret = ::SetLayout(hdc, l); ret != GCP_ERROR, ret);
// GetLayout
inline DWORD GetLayout(HDC hdc)
	assertl_reflect_as(auto ret = ::GetLayout(hdc); ret != GCP_ERROR, ret);
// SetMetaFileBitsEx
inline HMETAFILE SetMetaFileBitsEx(UINT cbBuffer, CONST BYTE *lpData)
	assertl_reflect_as(auto ret = ::SetMetaFileBitsEx(cbBuffer, lpData), ret);
// SetPaletteEntries
inline UINT SetPaletteEntries(HPALETTE hpal, UINT iStart, UINT cEntries, CONST PALETTEENTRY *pPalEntries)
	assertl_reflect_as(auto ret = ::SetPaletteEntries(hpal, iStart, cEntries, pPalEntries), ret);
// SetPixel
inline COLORREF SetPixel(HDC hdc, int x, int y, COLORREF color)
	assertl_reflect_as(auto ret = ::SetPixel(hdc, x, y, color); ret != CLR_INVALID, ret);
// SetPixelV
inline void SetPixelV(HDC hdc, int x, int y, COLORREF color)
	assertl_reflect_as(::SetPixelV(hdc, x, y, color));
// SetPixelFormat
inline void SetPixelFormat(HDC hdc, int format, CONST PIXELFORMATDESCRIPTOR *ppfd)
	assertl_reflect_as(::SetPixelFormat(hdc, format, ppfd));
// SetPolyFillMode
inline int SetPolyFillMode(HDC hdc, int mode)
	assertl_reflect_as(auto ret = ::SetPolyFillMode(hdc, mode); ret > 0, ret);
// StretchBlt
inline void StretchBlt(HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop)
	assertl_reflect_as(::StretchBlt(hdcDest, xDest, yDest, wDest, hDest, hdcSrc, xSrc, ySrc, wSrc, hSrc, rop));
// SetRectRgn
inline void SetRectRgn(HRGN hrgn, int left, int top, int right, int bottom)
	assertl_reflect_as(::SetRectRgn(hrgn, left, top, right, bottom));
// StretchDIBits
inline int StretchDIBits(HDC hdc, int xDest, int yDest, int DestWidth, int DestHeight, int xSrc, int ySrc, int SrcWidth, int SrcHeight, CONST VOID *lpBits, CONST BITMAPINFO *lpbmi, UINT iUsage, DWORD rop)
	reflect_as(::StretchDIBits(hdc, xDest, yDest, DestWidth, DestHeight, xSrc, ySrc, SrcWidth, SrcHeight, lpBits, lpbmi, iUsage, rop));
// SetROP2
inline int SetROP2(HDC hdc, int rop2)
	assertl_reflect_as(auto ret = ::SetROP2(hdc, rop2); ret > 0, ret);
// SetStretchBltMode
inline int SetStretchBltMode(HDC hdc, int mode)
	assertl_reflect_as(auto ret = ::SetStretchBltMode(hdc, mode); ret > 0, ret);
// SetSystemPaletteUse
inline UINT SetSystemPaletteUse(HDC hdc, UINT use)
	assertl_reflect_as(auto ret = ::SetSystemPaletteUse(hdc, use); ret != SYSPAL_ERROR, ret);
// SetTextCharacterExtra
inline int SetTextCharacterExtra(HDC hdc, int extra)
	assertl_reflect_as(auto ret = ::SetTextCharacterExtra(hdc, extra); ret != 0x8000000, ret);
// SetTextColor
inline COLORREF SetTextColor(HDC hdc, COLORREF color)
	assertl_reflect_as(auto ret = ::SetTextColor(hdc, color); ret != CLR_INVALID, ret);
// SetTextAlign
inline UINT SetTextAlign(HDC hdc, UINT align)
	assertl_reflect_as(auto ret = ::SetTextAlign(hdc, align); ret != GCP_ERROR, ret);
// SetTextJustification
inline void SetTextJustification(HDC hdc, int extra, int count)
	assertl_reflect_as(::SetTextJustification(hdc, extra, count));
// UpdateColors
inline void UpdateColors(HDC hdc)
	assertl_reflect_as(::UpdateColors(hdc));
// GdiRegisterDdraw - Undocument
// GdiMarshalSize - Undocument
// GdiMarshal - Undocument
// GdiUnmarshal - Undocument
// AlphaBlend
inline void AlphaBlend(HDC hdcDest, int xoriginDest, int yoriginDest, int wDest, int hDest, HDC hdcSrc, int xoriginSrc, int yoriginSrc, int wSrc, int hSrc, BLENDFUNCTION ftn)
	assertl_reflect_as(::AlphaBlend(hdcDest, xoriginDest, yoriginDest, wDest, hDest, hdcSrc, xoriginSrc, yoriginSrc, wSrc, hSrc, ftn));
// TransparentBlt
inline void TransparentBlt(HDC hdcDest, int xoriginDest, int yoriginDest, int wDest, int hDest, HDC hdcSrc, int xoriginSrc, int yoriginSrc, int wSrc, int hSrc, UINT crTransparent)
	assertl_reflect_as(::TransparentBlt(hdcDest, xoriginDest, yoriginDest, wDest, hDest, hdcSrc, xoriginSrc, yoriginSrc, wSrc, hSrc, crTransparent));
// GradientFill
inline void GradientFill(HDC hdc, PTRIVERTEX pVertex, ULONG nVertex, PVOID pMesh, ULONG nMesh, ULONG ulMode)
	assertl_reflect_as(::GradientFill(hdc, pVertex, nVertex, pMesh, nMesh, ulMode));
// GdiAlphaBlend
inline void GdiAlphaBlend(HDC hdcDest, int xoriginDest, int yoriginDest, int wDest, int hDest, HDC hdcSrc, int xoriginSrc, int yoriginSrc, int wSrc, int hSrc, BLENDFUNCTION ftn)
	assertl_reflect_as(::GdiAlphaBlend(hdcDest, xoriginDest, yoriginDest, wDest, hDest, hdcSrc, xoriginSrc, yoriginSrc, wSrc, hSrc, ftn));
// GdiTransparentBlt
inline void GdiTransparentBlt(HDC hdcDest, int xoriginDest, int yoriginDest, int wDest, int hDest, HDC hdcSrc, int xoriginSrc, int yoriginSrc, int wSrc, int hSrc, UINT crTransparent)
	assertl_reflect_as(::GdiTransparentBlt(hdcDest, xoriginDest, yoriginDest, wDest, hDest, hdcSrc, xoriginSrc, yoriginSrc, wSrc, hSrc, crTransparent));
// GdiGradientFill
inline void GdiGradientFill(HDC hdc, PTRIVERTEX pVertex, ULONG nVertex, PVOID pMesh, ULONG nCount, ULONG ulMode)
	assertl_reflect_as(::GdiGradientFill(hdc, pVertex, nVertex, pMesh, nCount, ulMode));
// PlayMetaFileRecord
inline void PlayMetaFileRecord(HDC hdc, LPHANDLETABLE lpHandleTable, LPMETARECORD lpMR, UINT noObjs)
	assertl_reflect_as(::PlayMetaFileRecord(hdc, lpHandleTable, lpMR, noObjs));
// EnumMetaFile
inline void EnumMetaFile(HDC hdc, HMETAFILE hmf, MFENUMPROC proc, LPARAM param)
	assertl_reflect_as(::EnumMetaFile(hdc, hmf, proc, param));
// CloseEnhMetaFile
inline HENHMETAFILE CloseEnhMetaFile(HDC hdc)
	assertl_reflect_as(auto ret = ::CloseEnhMetaFile(hdc), ret);
// CopyEnhMetaFile
#undef CopyEnhMetaFile
inline HENHMETAFILE CopyEnhMetaFile(HENHMETAFILE hEnh, LPCSTR lpFileName)
	assertl_reflect_as(auto ret = ::CopyEnhMetaFileA(hEnh, lpFileName), ret);
inline HENHMETAFILE CopyEnhMetaFile(HENHMETAFILE hEnh, LPCWSTR lpFileName)
	assertl_reflect_as(auto ret = ::CopyEnhMetaFileW(hEnh, lpFileName), ret);
// CreateEnhMetaFile
#undef CreateEnhMetaFile
inline HDC CreateEnhMetaFile(HDC hdc, LPCSTR lpFilename, CONST RECT *lprc, LPCSTR lpDesc)
	assertl_reflect_as(auto ret = ::CreateEnhMetaFileA(hdc, lpFilename, lprc, lpDesc), ret);
inline HDC CreateEnhMetaFile(HDC hdc, LPCWSTR lpFilename, CONST RECT *lprc, LPCWSTR lpDesc)
	assertl_reflect_as(auto ret = ::CreateEnhMetaFileW(hdc, lpFilename, lprc, lpDesc), ret);
// DeleteEnhMetaFile
inline void DeleteEnhMetaFile(HENHMETAFILE hmf)
	assertl_reflect_as(::DeleteEnhMetaFile(hmf));
// EnumEnhMetaFile
inline void EnumEnhMetaFile(HDC hdc, HENHMETAFILE hmf, ENHMFENUMPROC proc, LPVOID param, CONST RECT *lpRect)
	assertl_reflect_as(::EnumEnhMetaFile(hdc, hmf, proc, param, lpRect));
// GetEnhMetaFile
#undef GetEnhMetaFile
inline HENHMETAFILE GetEnhMetaFile(LPCSTR lpName)
	assertl_reflect_as(auto ret = ::GetEnhMetaFileA(lpName), ret);
inline HENHMETAFILE GetEnhMetaFile(LPCWSTR lpName)
	assertl_reflect_as(auto ret = ::GetEnhMetaFileW(lpName), ret);
// GetEnhMetaFileBits
inline UINT GetEnhMetaFileBits(HENHMETAFILE hEMF, UINT nSize, LPBYTE lpData)
	assertl_reflect_as(auto ret = ::GetEnhMetaFileBits(hEMF, nSize, lpData), ret);
// GetEnhMetaFileDescription
#undef GetEnhMetaFileDescription
inline UINT GetEnhMetaFileDescription(HENHMETAFILE hemf, UINT cchBuffer, LPSTR lpDescription)
	assertl_reflect_as(auto ret = ::GetEnhMetaFileDescriptionA(hemf, cchBuffer, lpDescription); ret != GCP_ERROR, ret);
inline UINT GetEnhMetaFileDescription(HENHMETAFILE hemf, UINT cchBuffer, LPWSTR lpDescription)
	assertl_reflect_as(auto ret = ::GetEnhMetaFileDescriptionW(hemf, cchBuffer, lpDescription); ret != GCP_ERROR, ret);
// GetEnhMetaFileHeader
inline UINT GetEnhMetaFileHeader(HENHMETAFILE hemf, UINT nSize, LPENHMETAHEADER lpEnhMetaHeader)
	assertl_reflect_as(auto ret = ::GetEnhMetaFileHeader(hemf, nSize, lpEnhMetaHeader), ret);
// GetEnhMetaFilePaletteEntries
inline UINT GetEnhMetaFilePaletteEntries(HENHMETAFILE hemf, UINT nNumEntries, LPPALETTEENTRY lpPaletteEntries)
	assertl_reflect_as(auto ret = ::GetEnhMetaFilePaletteEntries(hemf, nNumEntries, lpPaletteEntries); ret != GCP_ERROR, ret);
// GetEnhMetaFilePixelFormat
inline UINT GetEnhMetaFilePixelFormat(HENHMETAFILE hemf, UINT cbBuffer, PIXELFORMATDESCRIPTOR *ppfd)
	assertl_reflect_as(auto ret = ::GetEnhMetaFilePixelFormat(hemf, cbBuffer, ppfd), ret);
// GetWinMetaFileBits
inline UINT GetWinMetaFileBits(HENHMETAFILE hemf, UINT cbData16, LPBYTE pData16, INT iMapMode, HDC hdcRef)
	assertl_reflect_as(auto ret = ::GetWinMetaFileBits(hemf, cbData16, pData16, iMapMode, hdcRef), ret);
// PlayEnhMetaFile
inline void PlayEnhMetaFile(HDC hdc, HENHMETAFILE hmf, CONST RECT *lprect)
	assertl_reflect_as(::PlayEnhMetaFile(hdc, hmf, lprect));
// PlayEnhMetaFileRecord
inline void PlayEnhMetaFileRecord(HDC hdc, LPHANDLETABLE pht, CONST ENHMETARECORD *pmr, UINT cht)
	assertl_reflect_as(::PlayEnhMetaFileRecord(hdc, pht, pmr, cht));
// SetEnhMetaFileBits
inline HENHMETAFILE SetEnhMetaFileBits(UINT nSize, CONST BYTE *pb)
	assertl_reflect_as(auto ret = ::SetEnhMetaFileBits(nSize, pb), ret);
// SetWinMetaFileBits
inline HENHMETAFILE SetWinMetaFileBits(UINT nSize, CONST BYTE *lpMeta16Data, HDC hdcRef, CONST METAFILEPICT *lpMFP)
	assertl_reflect_as(auto ret = ::SetWinMetaFileBits(nSize, lpMeta16Data, hdcRef, lpMFP), ret);
// GdiComment
inline void GdiComment(HDC hdc, UINT nSize, CONST BYTE *lpData)
	assertl_reflect_as(::GdiComment(hdc, nSize, lpData));
// GetTextMetrics
#undef GetTextMetrics
inline void GetTextMetrics(HDC hdc, LPTEXTMETRICA lptm)
	assertl_reflect_as(::GetTextMetricsA(hdc, lptm));
inline void GetTextMetrics(HDC hdc, LPTEXTMETRICW lptm)
	assertl_reflect_as(::GetTextMetricsW(hdc, lptm));
// AngleArc
inline void AngleArc(HDC hdc, int x, int y, DWORD r, FLOAT StartAngle, FLOAT SweepAngle)
	assertl_reflect_as(::AngleArc(hdc, x, y, r, StartAngle, SweepAngle));
// PolyPolyline
inline void PolyPolyline(HDC hdc, CONST POINT *apt, CONST DWORD *asz, DWORD csz)
	assertl_reflect_as(::PolyPolyline(hdc, apt, asz, csz));
// GetWorldTransform
inline void GetWorldTransform(HDC hdc, LPXFORM lpxf)
	assertl_reflect_as(::GetWorldTransform(hdc, lpxf));
// SetWorldTransform
inline void SetWorldTransform(HDC hdc, CONST XFORM *lpxf)
	assertl_reflect_as(::SetWorldTransform(hdc, lpxf));
// ModifyWorldTransform
inline void ModifyWorldTransform(HDC hdc, CONST XFORM *lpxf, DWORD mode)
	assertl_reflect_as(::ModifyWorldTransform(hdc, lpxf, mode));
// CombineTransform
inline void CombineTransform(LPXFORM lpxfOut, CONST XFORM *lpxf1, CONST XFORM *lpxf2)
	assertl_reflect_as(::CombineTransform(lpxfOut, lpxf1, lpxf2));
// CreateDIBSection
inline HBITMAP CreateDIBSection(HDC hdc, CONST BITMAPINFO *pbmi, UINT usage, VOID **ppvBits, HANDLE hSection, DWORD offset)
	assertl_reflect_as(auto ret = ::CreateDIBSection(hdc, pbmi, usage, ppvBits, hSection, offset), ret);
// GetDIBColorTable
inline UINT GetDIBColorTable(HDC hdc, UINT iStart, UINT cEntries, RGBQUAD *prgbq)
	assertl_reflect_as(auto ret = ::GetDIBColorTable(hdc, iStart, cEntries, prgbq), ret);
// SetDIBColorTable
inline UINT SetDIBColorTable(HDC hdc, UINT iStart, UINT cEntries, CONST RGBQUAD *prgbq)
	assertl_reflect_as(auto ret = ::SetDIBColorTable(hdc, iStart, cEntries, prgbq), ret);
// SetColorAdjustment
inline void SetColorAdjustment(HDC hdc, CONST COLORADJUSTMENT *lpca)
	assertl_reflect_as(::SetColorAdjustment(hdc, lpca));
// GetColorAdjustment
inline void GetColorAdjustment(HDC hdc, LPCOLORADJUSTMENT lpca)
	assertl_reflect_as(::GetColorAdjustment(hdc, lpca));
// CreateHalftonePalette
inline HPALETTE CreateHalftonePalette(HDC hdc)
	assertl_reflect_as(auto ret = ::CreateHalftonePalette(hdc), ret);
// StartDoc
#undef StartDoc
inline int StartDoc(HDC hdc, CONST DOCINFOA *lpdi)
	assertl_reflect_as(auto ret = ::StartDocA(hdc, lpdi); ret > 0, ret);
inline int StartDoc(HDC hdc, CONST DOCINFOW *lpdi)
	assertl_reflect_as(auto ret = ::StartDocW(hdc, lpdi); ret > 0, ret);
// EndDoc
inline int EndDoc(HDC hdc)
	assertl_reflect_as(auto ret = ::EndDoc(hdc); ret > 0, ret);
// StartPage
inline int StartPage(HDC hdc)
	assertl_reflect_as(auto ret = ::StartPage(hdc); ret > 0, ret);
// EndPage
inline int EndPage(HDC hdc)
	assertl_reflect_as(auto ret = ::EndPage(hdc); ret > 0, ret);
// AbortDoc
inline int AbortDoc(HDC hdc)
	assertl_reflect_as(auto ret = ::AbortDoc(hdc); ret > 0, ret);
// SetAbortProc
inline int SetAbortProc(HDC hdc, ABORTPROC proc)
	assertl_reflect_as(auto ret = ::SetAbortProc(hdc, proc); ret > 0, ret);
// AbortPath
inline void AbortPath(HDC hdc)
	assertl_reflect_as(::AbortPath(hdc));
// ArcTo
inline void ArcTo(HDC hdc, int left, int top, int right, int bottom, int xr1, int yr1, int xr2, int yr2)
	assertl_reflect_as(::ArcTo(hdc, left, top, right, bottom, xr1, yr1, xr2, yr2));
// BeginPath
inline void BeginPath(HDC hdc)
	assertl_reflect_as(::BeginPath(hdc));
// CloseFigure
inline void CloseFigure(HDC hdc)
	assertl_reflect_as(::CloseFigure(hdc));
// EndPath
inline void EndPath(HDC hdc)
	assertl_reflect_as(::EndPath(hdc));
// FillPath
inline void FillPath(HDC hdc)
	assertl_reflect_as(::FillPath(hdc));
// FlattenPath
inline void FlattenPath(HDC hdc)
	assertl_reflect_as(::FlattenPath(hdc));
// GetPath
inline int GetPath(HDC hdc, LPPOINT apt, LPBYTE aj, int cpt)
	reflect_as(::GetPath(hdc, apt, aj, cpt));
// PathToRegion
inline HRGN PathToRegion(HDC hdc)
	assertl_reflect_as(auto ret = ::PathToRegion(hdc), ret);
// PolyDraw
inline void PolyDraw(HDC hdc, CONST POINT *apt, CONST BYTE *aj, int cpt)
	assertl_reflect_as(::PolyDraw(hdc, apt, aj, cpt));
// SelectClipPath
inline void SelectClipPath(HDC hdc, int mode)
	assertl_reflect_as(::SelectClipPath(hdc, mode));
// SetArcDirection
inline int SetArcDirection(HDC hdc, int dir)
	assertl_reflect_as(auto ret = ::SetArcDirection(hdc, dir); ret > 0, ret);
// SetMiterLimit
inline void SetMiterLimit(HDC hdc, FLOAT limit, PFLOAT old)
	assertl_reflect_as(::SetMiterLimit(hdc, limit, old));
// StrokeAndFillPath
inline void StrokeAndFillPath(HDC hdc)
	assertl_reflect_as(::StrokeAndFillPath(hdc));
// StrokePath
inline void StrokePath(HDC hdc)
	assertl_reflect_as(::StrokePath(hdc));
// WidenPath
inline void WidenPath(HDC hdc)
	assertl_reflect_as(::WidenPath(hdc));
// ExtCreatePen
inline HPEN ExtCreatePen(DWORD iPenStyle, DWORD cWidth, CONST LOGBRUSH *plbrush, DWORD cStyle, CONST DWORD *pstyle)
	assertl_reflect_as(auto ret = ::ExtCreatePen(iPenStyle, cWidth, plbrush, cStyle, pstyle), ret);
// GetMiterLimit
inline void GetMiterLimit(HDC hdc, PFLOAT plimit)
	assertl_reflect_as(::GetMiterLimit(hdc, plimit));
// GetArcDirection
inline int GetArcDirection(HDC hdc)
	assertl_reflect_as(auto ret = ::GetArcDirection(hdc); ret > 0, ret);
// GetObject
#undef GetObject
template<bool IsUnicode = WX::IsUnicode>
inline int GetObject(HANDLE h, int c, LPVOID pv) {
	if_c (IsUnicode)
		 assertl_reflect_as(auto ret = ::GetObjectA(h, c, pv); ret > 0, ret)
	else assertl_reflect_as(auto ret = ::GetObjectW(h, c, pv); ret > 0, ret)
}
// MoveToEx
inline void MoveToEx(HDC hdc, int x, int y, LPPOINT lppt)
	assertl_reflect_as(::MoveToEx(hdc, x, y, lppt));
// TextOut
#undef TextOut
inline void TextOut(HDC hdc, int x, int y, LPCSTR lpString, int c)
	assertl_reflect_as(::TextOutA(hdc, x, y, lpString, c));
inline void TextOut(HDC hdc, int x, int y, LPCWSTR lpString, int c)
	assertl_reflect_as(::TextOutW(hdc, x, y, lpString, c));
// ExtTextOut
#undef ExtTextOut
inline void ExtTextOut(HDC hdc, int x, int y, UINT options, CONST RECT *lprect, LPCSTR lpString, UINT c, CONST INT *lpDx)
	assertl_reflect_as(::ExtTextOutA(hdc, x, y, options, lprect, lpString, c, lpDx));
inline void ExtTextOut(HDC hdc, int x, int y, UINT options, CONST RECT *lprect, LPCWSTR lpString, UINT c, CONST INT *lpDx)
	assertl_reflect_as(::ExtTextOutW(hdc, x, y, options, lprect, lpString, c, lpDx));
// PolyTextOut
#undef PolyTextOut
inline void PolyTextOut(HDC hdc, CONST POLYTEXTA *ppt, int nstrings)
	assertl_reflect_as(::PolyTextOutA(hdc, ppt, nstrings));
inline void PolyTextOut(HDC hdc, CONST POLYTEXTW *ppt, int nstrings)
	assertl_reflect_as(::PolyTextOutW(hdc, ppt, nstrings));
// CreatePolygonRgn
inline HRGN CreatePolygonRgn(CONST POINT *pptl, int cPoint, int iMode)
	assertl_reflect_as(auto ret = ::CreatePolygonRgn(pptl, cPoint, iMode), ret);
// DPtoLP
inline void DPtoLP(HDC hdc, LPPOINT lppt, int c)
	assertl_reflect_as(::DPtoLP(hdc, lppt, c));
// LPtoDP
inline void LPtoDP(HDC hdc, LPPOINT lppt, int c)
	assertl_reflect_as(::LPtoDP(hdc, lppt, c));
// Polygon
inline void Polygon(HDC hdc, CONST POINT *apt, int cpt)
	assertl_reflect_as(::Polygon(hdc, apt, cpt));
// Polyline
inline void Polyline(HDC hdc, CONST POINT *apt, int cpt)
	assertl_reflect_as(::Polyline(hdc, apt, cpt));
// PolyBezier
inline void PolyBezier(HDC hdc, CONST POINT *apt, DWORD cpt)
	assertl_reflect_as(::PolyBezier(hdc, apt, cpt));
// PolyBezierTo
inline void PolyBezierTo(HDC hdc, CONST POINT *apt, DWORD cpt)
	assertl_reflect_as(::PolyBezierTo(hdc, apt, cpt));
// PolylineTo
inline void PolylineTo(HDC hdc, CONST POINT *apt, DWORD cpt)
	assertl_reflect_as(::PolylineTo(hdc, apt, cpt));
// SetViewportExtEx
inline void SetViewportExtEx(HDC hdc, int x, int y, LPSIZE lpsz)
	assertl_reflect_as(::SetViewportExtEx(hdc, x, y, lpsz));
// SetViewportOrgEx
inline void SetViewportOrgEx(HDC hdc, int x, int y, LPPOINT lppt)
	assertl_reflect_as(::SetViewportOrgEx(hdc, x, y, lppt));
// SetWindowExtEx
inline void SetWindowExtEx(HDC hdc, int x, int y, LPSIZE lpsz)
	assertl_reflect_as(::SetWindowExtEx(hdc, x, y, lpsz));
// SetWindowOrgEx
inline void SetWindowOrgEx(HDC hdc, int x, int y, LPPOINT lppt)
	assertl_reflect_as(::SetWindowOrgEx(hdc, x, y, lppt));
// OffsetViewportOrgEx
inline void OffsetViewportOrgEx(HDC hdc, int x, int y, LPPOINT lppt)
	assertl_reflect_as(::OffsetViewportOrgEx(hdc, x, y, lppt));
// OffsetWindowOrgEx
inline void OffsetWindowOrgEx(HDC hdc, int x, int y, LPPOINT lppt)
	assertl_reflect_as(::OffsetWindowOrgEx(hdc, x, y, lppt));
// ScaleViewportExtEx
inline void ScaleViewportExtEx(HDC hdc, int xn, int dx, int yn, int yd, LPSIZE lpsz)
	assertl_reflect_as(::ScaleViewportExtEx(hdc, xn, dx, yn, yd, lpsz));
// ScaleWindowExtEx
inline void ScaleWindowExtEx(HDC hdc, int xn, int xd, int yn, int yd, LPSIZE lpsz)
	assertl_reflect_as(::ScaleWindowExtEx(hdc, xn, xd, yn, yd, lpsz));
// SetBitmapDimensionEx
inline void SetBitmapDimensionEx(HBITMAP hbm, int w, int h, LPSIZE lpsz)
	assertl_reflect_as(::SetBitmapDimensionEx(hbm, w, h, lpsz));
// SetBrushOrgEx
inline void SetBrushOrgEx(HDC hdc, int x, int y, LPPOINT lppt)
	assertl_reflect_as(::SetBrushOrgEx(hdc, x, y, lppt));
// GetTextFace
#undef GetTextFace
inline int GetTextFace(HDC hdc, int c, LPSTR lpName)
	assertl_reflect_as(auto ret = ::GetTextFaceA(hdc, c, lpName); ret > 0, ret);
inline int GetTextFace(HDC hdc, int c, LPWSTR lpName)
	assertl_reflect_as(auto ret = ::GetTextFaceW(hdc, c, lpName); ret > 0, ret);
// GetKerningPairs
#undef GetKerningPairs
template<bool IsUnicode = WX::IsUnicode>
inline DWORD GetKerningPairs(HDC hdc, DWORD nPairs, LPKERNINGPAIR lpKernPair) {
	if_c (IsUnicode)
		 assertl_reflect_as(auto ret = ::GetKerningPairsA(hdc, nPairs, lpKernPair), ret)
	else assertl_reflect_as(auto ret = ::GetKerningPairsW(hdc, nPairs, lpKernPair), ret)
}
// GetDCOrgEx
inline void GetDCOrgEx(HDC hdc, LPPOINT lppt)
	assertl_reflect_as(::GetDCOrgEx(hdc, lppt));
// FixBrushOrgEx - Undocument
// UnrealizeObject
inline void UnrealizeObject(HGDIOBJ h)
	assertl_reflect_as(::UnrealizeObject(h));
// GdiFlush
inline void GdiFlush()
	assertl_reflect_as(::GdiFlush());
// GdiSetBatchLimit
inline DWORD GdiSetBatchLimit(DWORD dw)
	assertl_reflect_as(auto ret = ::GdiSetBatchLimit(dw), ret);
// GdiGetBatchLimit
inline DWORD GdiGetBatchLimit()
	assertl_reflect_as(auto ret = ::GdiGetBatchLimit(), ret);
// SetICMMode
inline int SetICMMode(HDC hdc, int mode)
	assertl_reflect_as(auto ret = ::SetICMMode(hdc, mode); ret > 0, ret);
// CheckColorsInGamut
inline void CheckColorsInGamut(HDC hdc, LPRGBTRIPLE lpRGBTriple, LPVOID dlpBuffer, DWORD nCount)
	assertl_reflect_as(::CheckColorsInGamut(hdc, lpRGBTriple, dlpBuffer, nCount));
// GetColorSpace
inline HCOLORSPACE GetColorSpace(HDC hdc)
	assertl_reflect_as(auto ret = ::GetColorSpace(hdc), ret);
// GetLogColorSpace
#undef GetLogColorSpace
inline void GetLogColorSpace(HCOLORSPACE hColorSpace, LPLOGCOLORSPACEA lpBuffer, DWORD nSize)
	assertl_reflect_as(::GetLogColorSpaceA(hColorSpace, lpBuffer, nSize));
inline void GetLogColorSpace(HCOLORSPACE hColorSpace, LPLOGCOLORSPACEW lpBuffer, DWORD nSize)
	assertl_reflect_as(::GetLogColorSpaceW(hColorSpace, lpBuffer, nSize));
// CreateColorSpace
#undef CreateColorSpace
inline HCOLORSPACE CreateColorSpace(LPLOGCOLORSPACEA lplcs)
	assertl_reflect_as(auto ret = ::CreateColorSpaceA(lplcs), ret);
inline HCOLORSPACE CreateColorSpace(LPLOGCOLORSPACEW lplcs)
	assertl_reflect_as(auto ret = ::CreateColorSpaceW(lplcs), ret);
// SetColorSpace
inline HCOLORSPACE SetColorSpace(HDC hdc, HCOLORSPACE hcs)
	assertl_reflect_as(auto ret = ::SetColorSpace(hdc, hcs), ret);
// DeleteColorSpace
inline void DeleteColorSpace(HCOLORSPACE hcs)
	assertl_reflect_as(::DeleteColorSpace(hcs));
// GetICMProfile
#undef GetICMProfile
inline void GetICMProfile(HDC hdc, LPDWORD pBufSize, LPSTR pszFilename)
	assertl_reflect_as(::GetICMProfileA(hdc, pBufSize, pszFilename));
inline void GetICMProfile(HDC hdc, LPDWORD pBufSize, LPWSTR pszFilename)
	assertl_reflect_as(::GetICMProfileW(hdc, pBufSize, pszFilename));
// SetICMProfile
#undef SetICMProfile
inline void SetICMProfile(HDC hdc, LPSTR lpFileName)
	assertl_reflect_as(::SetICMProfileA(hdc, lpFileName));
inline void SetICMProfile(HDC hdc, LPWSTR lpFileName)
	assertl_reflect_as(::SetICMProfileW(hdc, lpFileName));
// GetDeviceGammaRamp
inline void GetDeviceGammaRamp(HDC hdc, LPVOID lpRamp)
	assertl_reflect_as(::GetDeviceGammaRamp(hdc, lpRamp));
// SetDeviceGammaRamp
inline void SetDeviceGammaRamp(HDC hdc, LPVOID lpRamp)
	assertl_reflect_as(::SetDeviceGammaRamp(hdc, lpRamp));
// ColorMatchToTarget
inline void ColorMatchToTarget(HDC hdc, HDC hdcTarget, DWORD action)
	assertl_reflect_as(::ColorMatchToTarget(hdc, hdcTarget, action));
// EnumICMProfiles
#undef EnumICMProfiles
inline int EnumICMProfiles(HDC hdc, ICMENUMPROCA proc, LPARAM param)
	reflect_as(::EnumICMProfilesA(hdc, proc, param));
inline int EnumICMProfiles(HDC hdc, ICMENUMPROCW proc, LPARAM param)
	reflect_as(::EnumICMProfilesW(hdc, proc, param));
// UpdateICMRegKey - Deprecated
// ColorCorrectPalette
inline void ColorCorrectPalette(HDC hdc, HPALETTE hPal, DWORD deFirst, DWORD num)
	assertl_reflect_as(::ColorCorrectPalette(hdc, hPal, deFirst, num));
#pragma endregion

}
#pragma endregion

export namespace WX {

#pragma region GObject
template<class AnyChild, class BaseHandle = HGDIOBJ>
class GObjectBase;
using GObject = GObjectBase<void>;
template<class AnyChild, class BaseHandle>
class GObjectBase : public ExtendShim<GObjectBase<AnyChild, BaseHandle>, AnyChild> {
	misuse_assert((std::is_convertible_v<BaseHandle, HGDIOBJ>),
				 "BaseHandle must can be converted to HANDLE");
public:
	using Child = Chain<GObjectBase, AnyChild>;
protected:
	PROXY_SHIM(GObjectBase);
	mutable HGDIOBJ hobj = O;
	GObjectBase(HGDIOBJ h) : hobj(h) {}
	GObjectBase(const GObjectBase &h) : hobj(h.hobj) reflect_to(h.hobj = O);
public:
	GObjectBase() {}
	GObjectBase(Null) {}
	GObjectBase(GObjectBase &obj) : hobj(obj.hobj) { obj.hobj = O; }
	GObjectBase(GObjectBase &&obj) : hobj(obj.hobj) { obj.hobj = O; }
	~GObjectBase() reflect_to(Delete());
public:
	inline void Delete() {
		if (hobj)
			WX::DeleteObject(hobj);
		hobj = O;
	}
public:
	inline operator BaseHandle() const reflect_as(ref_as<BaseHandle>(hobj));
	inline Child &operator=(Child &obj) reflect_to_child(std::swap(obj.hobj, hobj));
	inline Child &operator=(Child &&obj) reflect_to_child(std::swap(obj.hobj, hobj));
	inline const Child &operator=(const Child &obj) const reflect_to_child(std::swap(obj.hobj, hobj));
public:
	static inline auto &Attach(BaseHandle &hObj) reflect_as(ref_as<AnyChild>(hObj));
	static inline const auto &Attach(const BaseHandle &hObj) reflect_as(ref_as<const AnyChild>(hObj));
	static inline void AutoDelete(BaseHandle &hObj) reflect_to(if (hObj) (WX::DeleteObject(hObj), hObj = O));
};
using CGObject = ProxyShim<GObject>;
#pragma endregion

#pragma region Bitmap
enum_class(BitmapCompressions, DWORD,
	RGB       = BI_RGB,
	RLE8      = BI_RLE8,
	RLE4      = BI_RLE4,
	BitFields = BI_BITFIELDS,
	JPEG      = BI_JPEG,
	PNG       = BI_PNG);
#pragma pack(2)
class BitmapHeader : protected BITMAPFILEHEADER, protected BITMAPINFO {
public:
	BitmapHeader() : BITMAPFILEHEADER{ 0 }, BITMAPINFO{ { 0 } } {
		this->bfType = *(const WORD *)"BM";
		this->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		this->bmiHeader.biCompression = BI_RGB;
	}
public: // Property - PaletteSize
	/* W */ inline auto &PaletteSize(DWORD dwSize) reflect_to_self(this->bfOffBits = dwSize + sizeof(*this) - 4);
	/* R */ inline DWORD PaletteSize() const reflect_as(this->bfOffBits - sizeof(*this) - 4);
public: // Property - ColorsSize
	/* W */ inline auto &ColorsSize(DWORD dwSize) reflect_to_self(this->bfSize = this->bfOffBits + dwSize);
	/* R */ inline DWORD ColorsSize() const reflect_as(this->bfSize - this->bfOffBits);
public: // Property - FileSize
	/* R */ inline DWORD FileSize() const reflect_as(this->bfSize);
public: // Property - Width
	/* W */ inline auto &Width(LONG biWidth) reflect_to_self(this->bmiHeader.biWidth = biWidth);
	/* R */ inline LONG  Width() const reflect_as(this->bmiHeader.biWidth);
public: // Property - Height
	/* W */ inline auto &Height(LONG biHeight) reflect_to_self(this->bmiHeader.biHeight = biHeight);
	/* R */ inline LONG  Height() const reflect_as(this->bmiHeader.biHeight);
public: // Property - Size
	/* W */ inline auto &Size(LSize sz) reflect_to_self(bmiHeader.biWidth = sz.cx, bmiHeader.biHeight = sz.cy);
	/* R */ inline LSize Size() const reflect_as({ bmiHeader.biWidth, bmiHeader.biHeight });
public: // Property - Compression
	/* W */ inline auto &Compression(BitmapCompressions biCompression) reflect_to_self(this->bmiHeader.biCompression = biCompression.yield());
	/* R */ inline BitmapCompressions Compression() const reflect_as(reuse_as<BitmapCompressions>(this->bmiHeader.biCompression));
public: // Property - SizeImage
	/* R */ inline DWORD SizeImage() const reflect_as(this->bmiHeader.biSizeImage);
public: // Property - PixelsPerMeter
	/* W */ inline auto &PixelsPerMeter(LSize sz) reflect_to_self(bmiHeader.biXPelsPerMeter = sz.cx, bmiHeader.biYPelsPerMeter = sz.cy);
	/* R */ inline LSize PixelsPerMeter() const reflect_as({ bmiHeader.biXPelsPerMeter, bmiHeader.biYPelsPerMeter });
public: // Property - Planes
	/* W */ inline auto &Planes(WORD biPlanes) reflect_to_self(this->bmiHeader.biPlanes = biPlanes);
	/* R */ inline WORD  Planes() const reflect_as(this->bmiHeader.biPlanes);
public: // Property - BitsPerPixel
	/* W */ inline auto &BitsPerPixel(WORD biBitCount) reflect_to_self(this->bmiHeader.biBitCount = biBitCount);
	/* R */ inline WORD  BitsPerPixel() const reflect_as(this->bmiHeader.biBitCount);
public: // Property - ColorUsed
	/* W */ inline auto &ColorUsed(DWORD biClrUsed) reflect_to_self(this->bmiHeader.biClrUsed = biClrUsed);
	/* R */ inline DWORD ColorUsed() const reflect_as(this->bmiHeader.biClrUsed);
public: // Property - ColorImportant
	/* W */ inline auto &ColorImportant(DWORD biClrImportant) reflect_to_self(this->bmiHeader.biClrImportant = biClrImportant);
	/* R */ inline DWORD ColorImportant() const reflect_as(this->bmiHeader.biClrImportant);
public: // Property - PaletteStart
	// /* W */ inline auto PaletteStart() reflect_to_self(this->bmiColors);
	/* R */ inline auto PaletteStart() const reflect_as(this->bmiColors);
public: // Property - Colors
	// /* W */ inline void *ColorsStart() reflect_to_self(((uint8_t *)PaletteStart()) + PaletteSize());
	/* R */ inline void *ColorsStart() const reflect_as(((uint8_t *)PaletteStart()) + PaletteSize());
public:
	inline operator LPBITMAPFILEHEADER() reflect_as(this);
	inline operator const BITMAPFILEHEADER *() const reflect_as(this);
	inline operator LPBITMAPINFO() reflect_as(this);
	inline operator const BITMAPINFO *() const reflect_as(this);
};
#pragma pack()
class BitmapLogic : public StructShim<BITMAP> {
public:
	using super = StructShim<BITMAP>;
public:
	BitmapLogic() {}
public: // Property - Width
	/* W */ inline auto &Width(LONG bmWidth) reflect_to_self(self->bmWidth = bmWidth);
	/* R */ inline LONG  Width() const reflect_as(self->bmWidth);
public: // Property - Height
	/* W */ inline auto &Height(LONG bmHeight) reflect_to_self(self->bmHeight = bmHeight);
	/* R */ inline LONG  Height() const reflect_as(self->bmHeight);
public: // Property - Size
	/* W */ inline auto &Size(LSize sz) reflect_to_self(self->bmWidth = sz.cx, self->bmHeight = sz.cy);
	/* R */ inline LSize Size() const reflect_as({ self->bmWidth, self->bmHeight });
public: // Property - WidthBytes
	/* W */ inline auto &WidthBytes(LONG bmWidthBytes) reflect_to_self(self->bmWidthBytes = bmWidthBytes);
	/* R */ inline LONG  WidthBytes() const reflect_as(self->bmWidthBytes);
public: // Property - Planes
	/* W */ inline auto &Planes(WORD bmPlanes) reflect_to_self(self->bmPlanes = bmPlanes);
	/* R */ inline WORD  Planes() const reflect_as(self->bmPlanes);
public: // Property - BitsPerPixel
	/* W */ inline auto &BitsPerPixel(WORD bmBitsPixel) reflect_to_self(self->bmBitsPixel = bmBitsPixel);
	/* R */ inline WORD  BitsPerPixel() const reflect_as(self->bmBitsPixel);
public: // Property - Colors
	/* W */ inline auto &Colors(LPVOID bmBits) reflect_to_self(self->bmBits = bmBits);
	/* R */ inline LPVOID Colors() const reflect_as(self->bmBits);
public:
	inline HBITMAP Create() const reflect_as(WX::CreateBitmapIndirect(this));
	inline operator HBITMAP() const reflect_as(Create());
};
class BaseOf_GDI(Bitmap, HBITMAP) {
public:
	using Header = BitmapHeader;
	using File = BitmapHeader;
	using Logic = BitmapLogic;
	using super = GObjectBase<Bitmap, HBITMAP>;
protected:
	PROXY_SHIM(Bitmap);
	Bitmap(HBITMAP h) : super(h) {}
	Bitmap(const Bitmap & b) : super(b) {}
public:
	Bitmap() {}
	Bitmap(Null) {}
	Bitmap(Bitmap & b) : super(b) {}
	Bitmap(Bitmap && b) : super(b) {}
public:
	class CreateStruct {
		int nWidth, nHeight;
		UINT nPlanes = 1, nBitsPerPixel = 32;
		LPCVOID lpBits = O;
	public:
		CreateStruct(LSize s) : nWidth(s.cx), nHeight(s.cy) {}
	public: // Property - Width
		/* W */ inline auto &Width(LONG nWidth) reflect_to_self(this->nWidth = nWidth);
		/* R */ inline LONG  Width() const reflect_as(this->nWidth);
	public: // Property - Height
		/* W */ inline auto &Height(LONG nHeight) reflect_to_self(this->nHeight = nHeight);
		/* R */ inline LONG  Height() const reflect_as(this->nHeight);
	public: // Property - Size
		/* W */ inline auto &Size(LSize sz) reflect_to_self(this->nWidth = sz.cx, this->nHeight = sz.cy);
		/* R */ inline LSize Size() const reflect_as({ this->nWidth, this->nHeight });
	public: // Property - Planes
		/* W */ inline auto &Planes(UINT nPlanes) reflect_to_self(this->nPlanes = nPlanes);
		/* R */ inline UINT  Planes() const reflect_as(this->nPlanes);
	public: // Property - BitsPerPixel
		/* W */ inline auto &BitsPerPixel(UINT nBitsPerPixel) reflect_to_self(this->nBitsPerPixel = nBitsPerPixel);
		/* R */ inline UINT  BitsPerPixel() const reflect_as(this->nBitsPerPixel);
	public: // Property - Colors
		/* W */ inline auto &Colors(LPCVOID lpBits) reflect_to_self(this->lpBits = lpBits);
		/* R */ inline LPCVOID Colors() const reflect_as(this->lpBits);
	public:
		inline Bitmap Create() const reflect_as(WX::CreateBitmap(nWidth, nHeight, nPlanes, nBitsPerPixel, lpBits));
		inline operator Bitmap() const reflect_as(Create());
	};
	static inline CreateStruct Create(LSize s = 0) reflect_as(s);
	static inline Bitmap Create(const BITMAPINFO * pbi, void **ppbits, HANDLE hSection = O, DWORD offset = 0) reflect_as(WX::CreateDIBSection(O, pbi, DIB_RGB_COLORS, ppbits, hSection, offset));
	static inline Bitmap Create(const BITMAPINFO * pbi, HANDLE hSection = O, DWORD offset = 0) reflect_as(WX::CreateDIBSection(O, pbi, DIB_RGB_COLORS, O, hSection, offset));
	static inline Bitmap From(HDC hDC, LSize s) reflect_as(WX::CreateCompatibleBitmap(hDC, s.cx, s.cy));
public:
	//inline auto &Restretch(LSize sz) reflect_to_self((super::hobj = (HBITMAP)CopyImage(self, IMAGE_BITMAP, sz.cx, sz.cy, LR_DEFAULTSIZE)));
	//inline Bitmap StretchNew(LSize sz) const reflect_as((HBITMAP)CopyImage(self, IMAGE_BITMAP, sz.cx, sz.cy, LR_DEFAULTCOLOR));
	//inline Bitmap Clone() const reflect_as(StretchNew(Size()));
#pragma region Properties
public: // Property - Size
	/* R */ inline LSize Size() const reflect_to(LSize sz, WX::GetBitmapDimensionEx(self, &sz), sz);
public: // Property - SizeBytes
	/* R */ inline size_t SizeBytes() const {
		auto &&log = Log();
		return (((log.Width() * log.Planes() /* nPlanes */ * log.BitsPerPixel() /* nBitCount */ + 15) >> 4) << 1) * log.Height();
	}
public: // Property - Colors
	/* W */ inline auto &GetColors(void *lpBits, DWORD cb) const reflect_to_self(WX::GetBitmapBits(self, cb, lpBits));
	/* R */ inline auto &SetColors(const void *lpBits, DWORD cb) reflect_to_self(WX::SetBitmapBits(self, cb, lpBits));
public: // Property - Log
	inline Logic Log() const reflect_to(Logic log, GetObject(self, sizeof(log), reinterpret_cast<LPSTR>(&log)), log);
#pragma endregion
public:
	using super::operator=;
};
using CBitmap = ProxyShim<Bitmap>;
#pragma endregion

#pragma region Font
enum_flags(FontType, WORD,
	Simulated    = SIMULATED_FONTTYPE,
	Printer      = PRINTER_FONTTYPE,
	Screen       = SCREEN_FONTTYPE,
	Bold         = BOLD_FONTTYPE,
	Italic       = ITALIC_FONTTYPE,
	Regular      = REGULAR_FONTTYPE/*,
	PS_OpenType  = PS_OPENTYPE_FONTTYPE,
	TT_OpenType  = TT_OPENTYPE_FONTTYPE,
	Type1        = TYPE1_FONTTYPE,
	Symbol       = SYMBOL_FONTTYPE*/);
enum_class(CharSets, BYTE,
	ANSI           = ANSI_CHARSET,
	Default        = DEFAULT_CHARSET,
	Symbol         = SYMBOL_CHARSET,
	ShiftJIS       = SHIFTJIS_CHARSET,
	Hangeul        = HANGEUL_CHARSET,
	Hangul         = HANGUL_CHARSET,
	GB2312         = GB2312_CHARSET,
	ChineseBig5    = CHINESEBIG5_CHARSET,
	OEM            = OEM_CHARSET,
	Johab          = JOHAB_CHARSET,
	Hebrew         = HEBREW_CHARSET,
	Arabic         = ARABIC_CHARSET,
	Greek          = GREEK_CHARSET,
	Turkish        = TURKISH_CHARSET,
	Vietnamese     = VIETNAMESE_CHARSET,
	Thai           = THAI_CHARSET,
	EastEurope     = EASTEUROPE_CHARSET,
	Russian        = RUSSIAN_CHARSET,
	Mac            = MAC_CHARSET,
	Baltic         = BALTIC_CHARSET);
enum_class(OutPrecis, BYTE, 
	Default        = OUT_DEFAULT_PRECIS,
	String         = OUT_STRING_PRECIS,
	Character      = OUT_CHARACTER_PRECIS,
	Stroke         = OUT_STROKE_PRECIS,
	TrueType       = OUT_TT_PRECIS,
	Device         = OUT_DEVICE_PRECIS,
	Raster         = OUT_RASTER_PRECIS,
	TrueTypeOnly   = OUT_TT_ONLY_PRECIS,
	Outline        = OUT_OUTLINE_PRECIS,
	ScreenOutline  = OUT_SCREEN_OUTLINE_PRECIS,
	PostScriptOnly = OUT_PS_ONLY_PRECIS);
enum_flags(ClipPrecis, BYTE,
	Default        = CLIP_DEFAULT_PRECIS,
	Character      = CLIP_CHARACTER_PRECIS,
	Stroke         = CLIP_STROKE_PRECIS,
	Mask           = CLIP_MASK,
	LH_Angles      = CLIP_LH_ANGLES,
	TT_Always      = CLIP_TT_ALWAYS,
	DFA_Disable    = CLIP_DFA_DISABLE,
	Embedded       = CLIP_EMBEDDED);
enum_class(Qualities, BYTE,
	Default          = DEFAULT_QUALITY,
	Draf             = DRAFT_QUALITY,
	Proof            = PROOF_QUALITY,
	NonAntiAliased   = NONANTIALIASED_QUALITY,
	AntiAliased      = ANTIALIASED_QUALITY,
	ClearType        = CLEARTYPE_QUALITY,
	ClearTypeNatural = CLEARTYPE_NATURAL_QUALITY);
enum_class(FontPitches, BYTE,
	Default  = DEFAULT_PITCH,
	Fixed    = FIXED_PITCH,
	Variable = VARIABLE_PITCH,
	Mono     = MONO_FONT);
enum_class(FontFamilies, BYTE,
	DontCare   = FF_DONTCARE,
	Roman      = FF_ROMAN,
	Swiss      = FF_SWISS,
	Modern     = FF_MODERN,
	Script     = FF_SCRIPT,
	Decorative = FF_DECORATIVE);
template<bool IsUnicode>
class FontLogicX : public StructShim<structx(LOGFONT)> {
	using_structx(LOGFONT);
	using TCHAR = XCHAR<IsUnicode>;
	using String = StringBase<TCHAR>;
public:
	using super = StructShim<LOGFONT>;
public:
	FontLogicX() {}
	FontLogicX(const LOGFONT &lf) : super(lf) {}
public: // Properties - Height
	/* W */ inline auto &Height(LONG lfHeight) reflect_to_self(self->lfHeight = lfHeight);
	/* R */ inline LONG  Height() const reflect_as(self->lfHeight);
public: // Properties - Width
	/* W */ inline auto &Width(LONG lfWidth) reflect_to_self(self->lfWidth = lfWidth);
	/* R */ inline LONG  Width() const reflect_as(self->lfWidth);
public: // Properties - Escapement
	/* W */ inline auto &Escapement(LONG lfEscapement) reflect_to_self(self->lfEscapement = lfEscapement);
	/* R */ inline LONG  Escapement() const reflect_as(self->lfEscapement);
public: // Properties - Orientation
	/* W */ inline auto &Orientation(LONG lfOrientation) reflect_to_self(self->lfOrientation = lfOrientation);
	/* R */ inline LONG  Orientation() const reflect_as(self->lfOrientation);
public: // Properties - Weight
	/* W */ inline auto &Weight(LONG lfWeight) reflect_to_self(self->lfWeight = lfWeight);
	/* R */ inline LONG  Weight() const reflect_as(self->lfWeight);
public: // Properties - Italic
	/* W */ inline auto &Italic(bool lfItalic) reflect_to_self(self->lfItalic = lfItalic);
	/* R */ inline bool  Italic() const reflect_as(self->lfItalic);
public: // Properties - Underline
	/* W */ inline auto &Underline(bool lfUnderline) reflect_to_self(self->lfUnderline = lfUnderline);
	/* R */ inline bool  Underline() const reflect_as(self->lfUnderline);
public: // Properties - StrikeOut
	/* W */ inline auto &StrikeOut(bool lfStrikeOut) reflect_to_self(self->lfStrikeOut = lfStrikeOut);
	/* R */ inline bool  StrikeOut() const reflect_as(self->lfStrikeOut);
public: // Properties - CharSet
	/* W */ inline auto    &CharSet(CharSets lfCharSet) reflect_to_self(self->lfCharSet = lfCharSet.yield());
	/* R */ inline CharSets CharSet() const reflect_as(reuse_as<CharSets>(self->lfCharSet));
public: // Properties - OutPrecision
	/* W */ inline auto     &OutPrecision(OutPrecis lfOutPrecision) reflect_to_self(self->lfOutPrecision = lfOutPrecision.yield());
	/* R */ inline OutPrecis OutPrecision() const reflect_as(reuse_as<OutPrecis>(self->lfOutPrecision));
public: // Properties - ClipPrecision
	/* W */ inline auto      &ClipPrecision(ClipPrecis lfClipPrecision) reflect_to_self(self->lfClipPrecision = lfClipPrecision.yield());
	/* R */ inline ClipPrecis ClipPrecision() const reflect_as(reuse_as<ClipPrecis>(self->lfClipPrecision));
public: // Properties - Quality
	/* W */ inline auto     &Quality(Qualities lfQuality) reflect_to_self(self->lfQuality = lfQuality.yield());
	/* R */ inline Qualities Quality() const reflect_as(reuse_as<Qualities>(self->lfQuality));
public: // Properties - Pitch
	/* W */ inline auto&Pitch(FontPitches lfPitch) reflect_to_self(self->lfPitchAndFamily &= 0xF0, self->lfPitchAndFamily |= lfPitch.yield());
	/* R */ inline FontPitches Pitch() const reflect_as(reuse_as<FontPitches>((BYTE)(self->lfPitchAndFamily & 0x0F)));
public: // Properties - Family
	/* W */ inline auto&Family(FontFamilies lfFamily) reflect_to_self(self->lfPitchAndFamily &= 0x0F, self->lfPitchAndFamily |= lfFamily.yield());
	/* R */ inline FontFamilies Family() const reflect_as(reuse_as<FontFamilies>((BYTE)(self->lfPitchAndFamily & 0xF0)));
public: // Properties - FaceName
	/* W */ inline auto &FaceName(String name) reflect_to_self(String(self->lfFaceName).Copy(name));
	/* R */ inline const String FaceName() const reflect_as(CString(self->lfFaceName, LF_FACESIZE));
};
using FontLogic = FontLogicX<IsUnicode>;
using FontLogicA = FontLogicX<false>;
using FontLogicW = FontLogicX<true>;
using CFontLogic = ProxyShim<FontLogic>;
using CFontLogicA = ProxyShim<FontLogicA>;
using CFontLogicW = ProxyShim<FontLogicW>;
using FontLog = FontLogic;
using FontLogA = FontLogicA;
using FontLogW = FontLogicW;
using CFontLog = CFontLogic;
using CFontLogA = CFontLogicA;
using CFontLogW = CFontLogicW;
using LogFont = FontLogic;
using LogFontA = FontLogicA;
using LogFontW = FontLogicW;
using CLogFont = CFontLogic;
using CLogFontA = CFontLogicA;
using CLogFontW = CFontLogicW;
class BaseOf_GDI(Font, HFONT) {
public:
	using super = GObjectBase<Font, HFONT>;
	using Logic = FontLogic;
	using LogicA = FontLogicA;
	using LogicW = FontLogicW;
protected:
	PROXY_SHIM(Font);
	Font(HFONT h) : super(h) {}
	Font(const Font &f) : super(f) {}
public:
	Font() {}
	Font(Null) {}
	Font(Font &f) : super(f) {}
	Font(Font &&f) : super(f) {}
public:
	Font(const LogicA &LogFont) : Font(Create(LogFont)) {}
	Font(const LogicW &LogFont) : Font(Create(LogFont)) {}
public:
	static inline Font Create(const LogicA &LogFont) reflect_as(WX::CreateFontIndirect(&LogFont));
	static inline Font Create(const LogicW &LogFont) reflect_as(WX::CreateFontIndirect(&LogFont));
public:
	using super::operator=;
};
using CFont = ProxyShim<Font>;
#pragma endregion

#pragma region Pen
enum_flags(PenStyles, int,
	Solid       = PS_SOLID,
	Dash        = PS_DASH,
	Dot         = PS_DOT,
	DashDot     = PS_DASHDOT,
	DashDotDot  = PS_DASHDOTDOT,
	Null        = PS_NULL,
	InsideFrame = PS_INSIDEFRAME,
	UserStyle   = PS_USERSTYLE,
	Alternate   = PS_ALTERNATE);
class PenLogic : public StructShim<LOGPEN> {
public:
	using super = StructShim<LOGPEN>;
public:
	PenLogic() {}
public: // Property - Style
	/* W */ inline auto &Style(PenStyles lopnStyle) reflect_to_self(self->lopnStyle = lopnStyle.yield());
	/* R */ inline PenStyles Style() const reflect_as(reuse_as<PenStyles>(self->lopnStyle));
public: // Property - Width
	/* W */ inline auto &Width(POINT lopnWidth) reflect_to_self(self->lopnWidth = lopnWidth);
	/* R */ inline LPoint Width() const reflect_as(reuse_as<POINT>(self->lopnWidth));
public: // Property - Style
	/* W */ inline auto &Color(COLORREF lopnColor) reflect_to_self(self->lopnColor = lopnColor);
	/* R */ inline COLORREF Color() const reflect_as(reuse_as<RGBColor>(self->lopnColor));
};
class BaseOf_GDI(Pen, HPEN) {
public:
	using super = GObjectBase<Pen, HPEN>;
	using Styles = PenStyles;
	using Log = PenLogic;
protected:
	PROXY_SHIM(Pen);
	Pen(HPEN h) : super(h) {}
	Pen(const Pen &p) : super(p) {}
public:
	Pen() {}
	Pen(Null) {}
	Pen(Pen &p) : super(p) {}
	Pen(Pen &&p) : super(p) {}
	Pen(const PenLogic &log) : super(Create(log)) {}
public:
	static inline Pen Create(const PenLogic &log) reflect_as(WX::CreatePenIndirect(&log));
	static inline Pen Create(Styles styles, COLORREF rgb, int nWidth = 0) reflect_as(WX::CreatePen(styles.yield(), nWidth, rgb));
	static inline Pen CreateSolid(COLORREF rgb, int nWidth = 0)       reflect_as(WX::CreatePen(PS_SOLID, nWidth, rgb));
	static inline Pen CreateDash(COLORREF rgb, int nWidth = 0)        reflect_as(WX::CreatePen(PS_DASH, nWidth, rgb));
	static inline Pen CreateDot(COLORREF rgb, int nWidth = 0)         reflect_as(WX::CreatePen(PS_DOT, nWidth, rgb));
	static inline Pen CreateDashDot(COLORREF rgb, int nWidth = 0)     reflect_as(WX::CreatePen(PS_DASHDOT, nWidth, rgb));
	static inline Pen CreateDashDotDot(COLORREF rgb, int nWidth = 0)  reflect_as(WX::CreatePen(PS_DASHDOTDOT, nWidth, rgb));
	static inline Pen CreateNull(COLORREF rgb, int nWidth = 0)        reflect_as(WX::CreatePen(PS_NULL, nWidth, rgb));
	static inline Pen CreateInsideFrame(COLORREF rgb, int nWidth = 0) reflect_as(WX::CreatePen(PS_INSIDEFRAME, nWidth, rgb));
	static inline Pen CreateUserStyle(COLORREF rgb, int nWidth = 0)   reflect_as(WX::CreatePen(PS_USERSTYLE, nWidth, rgb));
	static inline Pen CreateAlternate(COLORREF rgb, int nWidth = 0)   reflect_as(WX::CreatePen(PS_ALTERNATE, nWidth, rgb));
public:
	static inline Pen White() reflect_as((HPEN)WX::GetStockObject(WHITE_PEN));
	static inline Pen Black() reflect_as((HPEN)WX::GetStockObject(BLACK_PEN));
	static inline Pen Null()  reflect_as((HPEN)WX::GetStockObject(NULL_PEN));
	static inline Pen DC()    reflect_as((HPEN)WX::GetStockObject(DC_PEN));
public: // Property - Log
	/* R */
public:
	using super::operator=;
};
using CPen = ProxyShim<Pen>;
#pragma endregion

#pragma region Brush
enum_class(SysColor, intptr_t,
	ScrollBar               = COLOR_SCROLLBAR,
	Background              = COLOR_BACKGROUND,
	ActiveCaption           = COLOR_ACTIVECAPTION,
	InactiveCaption         = COLOR_INACTIVECAPTION,
	Menu                    = COLOR_MENU,
	Window                  = COLOR_WINDOW,
	WindowFrame             = COLOR_WINDOWFRAME,
	MenuText                = COLOR_MENUTEXT,
	WindowText              = COLOR_WINDOWTEXT,
	CaptionText             = COLOR_CAPTIONTEXT,
	ActiveBorder            = COLOR_ACTIVEBORDER,
	InactiveBorder          = COLOR_INACTIVEBORDER,
	AppWorkspace            = COLOR_APPWORKSPACE,
	HighLight               = COLOR_HIGHLIGHT,
	HighLightText           = COLOR_HIGHLIGHTTEXT,
	BtnFace                 = COLOR_BTNFACE,
	BtnShadow               = COLOR_BTNSHADOW,
	GrayText                = COLOR_GRAYTEXT,
	BtnText                 = COLOR_BTNTEXT,
	InactiveCaptionText     = COLOR_INACTIVECAPTIONTEXT,
	BtnHighlight            = COLOR_BTNHIGHLIGHT,
	DkShadow3D              = COLOR_3DDKSHADOW,
	Light3D                 = COLOR_3DLIGHT,
	InfoText                = COLOR_INFOTEXT,
	InfoBk                  = COLOR_INFOBK,
	HotLight                = COLOR_HOTLIGHT,
	GradientActiveCaption   = COLOR_GRADIENTACTIVECAPTION,
	GradientInactiveCaption = COLOR_GRADIENTINACTIVECAPTION,
	MenuHiLight             = COLOR_MENUHILIGHT,
	MenuBar                 = COLOR_MENUBAR);
enum_class(HatchStyles, int,
	Horizontal              = HS_HORIZONTAL,    /* ----- */
	Vertical                = HS_VERTICAL,      /* ||||| */
	FDiagonal               = HS_FDIAGONAL,     /* \\\\\ */
	BDiagonal               = HS_BDIAGONAL,     /* ///// */
	Cross                   = HS_CROSS,         /* +++++ */
	DiagCross               = HS_DIAGCROSS      /* xxxxx */);
class BaseOf_GDI(Brush, HBRUSH) {
public:
	using super = GObjectBase<Brush, HBRUSH>;
protected:
	PROXY_SHIM(Brush);
	Brush(HBRUSH h) : super(h) {}
	Brush(const Brush &b) : super(b) {}
public:
	Brush() {}
	Brush(Null) {}
	Brush(Brush &b) : super(b) {}
	Brush(Brush &&b) : super(b) {}
	Brush(WX::SysColor sc) : super(SysColor(sc)) {}
	Brush(COLORREF rgb) : super(CreateSolid(rgb)) {}
	Brush(HBITMAP hbm) : super(CreatePattern(hbm)) {}
	Brush(HatchStyles hs, COLORREF rgb) : super(CreateHatch(rgb, hs)) {}
public:
	static inline Brush CreateSolid(COLORREF rgb)                reflect_as(WX::CreateSolidBrush(rgb));
	static inline Brush CreatePattern(HBITMAP hbm)               reflect_as(WX::CreatePatternBrush(hbm));
	static inline Brush CreateHatch(COLORREF rgb, HatchStyles hs) reflect_as(WX::CreateHatchBrush(hs.yield(), rgb));
public:
	static inline Brush White()   reflect_as((HBRUSH)WX::GetStockObject(WHITE_BRUSH));
	static inline Brush LitGray() reflect_as((HBRUSH)WX::GetStockObject(LTGRAY_BRUSH));
	static inline Brush Gray()    reflect_as((HBRUSH)WX::GetStockObject(GRAY_BRUSH));
	static inline Brush DkGray()  reflect_as((HBRUSH)WX::GetStockObject(DKGRAY_BRUSH));
	static inline Brush Black()   reflect_as((HBRUSH)WX::GetStockObject(BLACK_BRUSH));
	static inline Brush Null()    reflect_as((HBRUSH)WX::GetStockObject(NULL_BRUSH));
	static inline Brush DC()      reflect_as((HBRUSH)WX::GetStockObject(DC_BRUSH));
public:
	static inline Brush SysColor(WX::SysColor sc) reflect_as(WX::GetSysColorBrush((int)sc.yield()));
public:
	using super::operator=;
};
using CBrush = ProxyShim<Brush>;
#pragma endregion

#pragma region Palette
class PaletteEntry : public StructShim<PALETTEENTRY> {
public:
	using super = StructShim<PALETTEENTRY>;
public:
	PaletteEntry() {}
	PaletteEntry(const PALETTEENTRY &entry) : super(entry) {}
	PaletteEntry(BYTE r, BYTE g, BYTE b, BYTE f = 0) : super(PALETTEENTRY{ r, g, b, f }) {}
	PaletteEntry(RGBColor rgb, BYTE f = 0) : PaletteEntry(rgb.Red(), rgb.Green(), rgb.Blue(), f) {}
	PaletteEntry(COLORREF rgb, BYTE f = 0) : PaletteEntry((RGBColor)rgb, f) {}
public: // Property - Red
	/* W */ inline auto &Red(BYTE bRed) reflect_to_self(self->peRed = bRed);
	/* R */ inline BYTE  Red() const reflect_as(self->peRed);
public: // Property - Green
	/* W */ inline auto &Green(BYTE bGreen) reflect_to_self(self->peGreen = bGreen);
	/* R */ inline BYTE  Green() const reflect_as(self->peGreen);
public: // Property - Blue
	/* W */ inline auto &Blue(BYTE bBlue) reflect_to_self(self->peBlue = bBlue);
	/* R */ inline BYTE  Blue() const reflect_as(self->peBlue);
public:
	inline operator RGBColor() const reflect_as({ Red(), Green(), Blue() });
};
using PalEntry = PaletteEntry;
class BaseOf_GDI(Palette, HPALETTE) { //////////////
public:
	using super = GObjectBase<Palette, HPALETTE>;
	using Entry = PaletteEntry;
protected:
	PROXY_SHIM(Palette);
	Palette(HPALETTE h) : super(h) {}
	Palette(const Palette &p) : super(p) {}
public:
	Palette() {}
	Palette(Null) {}
	Palette(Palette &p) : super(p) {}
	Palette(Palette &&p) : super(p) {}
public:
	Palette(const Entry *lpEntries, UINT nCount) {
		assertl(1 < nCount && nCount <= 256);
		HeapPointer<LOGPALETTE> hPal;
		hPal.Alloc(sizeof(LOGPALETTE) + (nCount - 1) * sizeof(Entry));
		auto pPal = &hPal;
		pPal->palVersion = 0x300;
		pPal->palNumEntries = (WORD)nCount;
		CopyMemory(&pPal->palPalEntry, lpEntries, sizeof(Entry) * nCount);
		this->hobj = WX::CreatePalette(pPal);
	}
	Palette(std::initializer_list<COLORREF> entries) : Palette((const Entry *)entries.begin(), (UINT)entries.size()) {}
	Palette(std::initializer_list<Entry> entries) : Palette(entries.begin(), (UINT)entries.size()) {}
	Palette(const std::vector<Entry> &entries) : Palette(entries.data(), (UINT)entries.size()) {}
public:
//	static inline Palette Create() reflect_as();
	static inline Palette Default() reflect_as((HPALETTE)WX::GetStockObject(DEFAULT_PALETTE));
public:
	inline auto &SetEntries(UINT iStart, const Entry *pPalEntries, UINT cEntries = 1) reflect_to_self(WX::SetPaletteEntries(self, iStart, cEntries, (const PALETTEENTRY *)pPalEntries));
	inline auto &GetEntries(UINT iStart, Entry *pPalEntries, UINT cEntries = 1) const reflect_to_self(WX::GetPaletteEntries(self, iStart, cEntries, (LPPALETTEENTRY)pPalEntries));
	inline UINT NearestIndex(COLORREF cr) const reflect_as(WX::GetNearestPaletteIndex(self, cr));
#pragma region Properties
public: // Property - Entries
	/* W */ inline auto &Entries(std::vector<Entry> entries) {
		auto count = std::min((size_t)Count(), entries.size());
		assertl(count <= 256);
		if (count > 0)
			SetEntries(0, entries.data(), (WORD)(count - 1));
		retself;
	}
	/* R */ inline std::vector<Entry> Entries() const {
		size_t count = Count();
		std::vector<Entry> entries(count);
		if (count > 0)
			GetEntries(0, entries.data(), (WORD)count);
		return entries;
	}
public: // Property - NumEntries
	/* W */ inline auto &Count(WORD nNumEntries) reflect_to_self(WX::ResizePalette(self, nNumEntries));
	/* R */ inline WORD  Count() const reflect_to(WORD w = 0, WX::GetObject(self, sizeof(WORD), &w), w);
public: // Property - Size
	/* R */ inline size_t Size() const reflect_as(Count() * sizeof(Entry));
#pragma endregion
public:
	using super::operator=;
	inline Entry operator[](size_t ind) const reflect_to(Entry entry; GetEntries((UINT)ind, (Entry *)&entry), entry);
};
using CPalette = ProxyShim<Palette>;
#pragma endregion

#pragma region Region
enum_class(PolyFillModes, int,
	Default   = 0,
	Alternate = ALTERNATE,
	Winding   = WINDING);
enum_class(BkModes, int,
	Default     = 0,
	Transparent = TRANSPARENT,
	Opaque      = OPAQUE);
class BaseOf_GDI(Region, HRGN) {
public:
	using super = GObjectBase<Region, HRGN>;
protected:
	PROXY_SHIM(Region);
	Region(HRGN h) : super(h) {}
	Region(const Region &r) : super(r) {}
public:
	Region() {}
	Region(Null) {}
	Region(Region &r) : super(r) {}
	Region(Region &&r) : super(r) {}
public:
//	static inline void Combine() { CombineRgn() }
public:
	static inline Region CreateRect(LRect rc) reflect_as(WX::CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom));
	static inline Region CreateElliptic(LRect rc) reflect_as(WX::CreateEllipticRgn(rc.left, rc.top, rc.right, rc.bottom));
	static inline Region CreateRound(LRect rc, LSize sz) reflect_as(WX::CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, sz.cx, sz.cy));
	static inline Region CreatePolygon(const POINT *ppt1, int cPoint, PolyFillModes mode = PolyFillModes::Winding) reflect_as(WX::CreatePolygonRgn(ppt1, cPoint, mode.yield()));
	static inline Region CreatePolyPolygon(const POINT *ppt1, int cPoint, PolyFillModes mode = PolyFillModes::Winding) reflect_as(WX::CreatePolygonRgn(ppt1, cPoint, mode.yield()));
public:
	inline bool Equal(HRGN hRgn) reflect_as(WX::EqualRgn(self, hRgn));
	inline bool Has(LPoint pt) reflect_as(WX::PtInRegion(self, pt.x, pt.y));
	inline bool Has(LRect rc) reflect_as(WX::RectInRegion(self, &rc));
public:
	inline void And(HRGN hRgn) { WX::CombineRgn(self, self, hRgn, RGN_AND); }
	inline void And(HRGN hRgn1, HRGN hRgn2) { WX::CombineRgn(self, hRgn1, hRgn2, RGN_AND); }
	inline void Or(HRGN hRgn) { WX::CombineRgn(self, self, hRgn, RGN_OR); }
	inline void Or(HRGN hRgn1, HRGN hRgn2) { WX::CombineRgn(self, hRgn1, hRgn2, RGN_OR); }
	inline void Xor(HRGN hRgn) { WX::CombineRgn(self, self, hRgn, RGN_XOR); }
	inline void Xor(HRGN hRgn1, HRGN hRgn2) { WX::CombineRgn(self, hRgn1, hRgn2, RGN_XOR); }
	inline void Diff(HRGN hRgn) { WX::CombineRgn(self, self, hRgn, RGN_DIFF); }
	inline void Diff(HRGN hRgn1, HRGN hRgn2) { WX::CombineRgn(self, hRgn1, hRgn2, RGN_DIFF); }
	inline void Offset(LPoint off) { WX::OffsetRgn(self, off.x, off.y); }
public:
	inline auto &operator&(HRGN hRgn) reflect_to_self(And(hRgn));
	inline auto &operator|(HRGN hRgn) reflect_to_self(Or(hRgn));
	inline auto &operator^(HRGN hRgn) reflect_to_self(Xor(hRgn));
	inline auto &operator-(HRGN hRgn) reflect_to_self(Diff(hRgn));
};
using CRegion = ProxyShim<Region>;
#pragma endregion

#pragma region MetaFile
class BaseOf_GDI(MetaFile, HMETAFILE) {
public:
	using super = GObjectBase<MetaFile, HMETAFILE>;
protected:
	PROXY_SHIM(Region);
	MetaFile(HMETAFILE h) : super(h) {}
	MetaFile(const MetaFile &m) : super(m) {}
public:
	MetaFile() {}
	MetaFile(Null) {}
	MetaFile(MetaFile &m) : super(m) {}
	MetaFile(MetaFile &&m) : super(m) {}
	~MetaFile() reflect_to(Delete());
public:

public:
	inline void Delete() {
		if (self)
			WX::DeleteMetaFile(self);
		this->hobj = O;
	}
};
using CMetaFile = ProxyShim<MetaFile>;
#pragma endregion

#pragma region DevCap

#pragma region ColorSpace
enum_class(MapModes, int,
	Text           = MM_TEXT,
	LoMetric       = MM_LOMETRIC,
	HiMetric       = MM_HIMETRIC,
	LoEnglish      = MM_LOENGLISH,
	HiEnglish      = MM_HIENGLISH,
	Twips          = MM_TWIPS,
	Isotropic      = MM_ISOTROPIC,
	Anisotropic    = MM_ANISOTROPIC);
enum_flags(Rop, DWORD,
	SrcCopy        = SRCCOPY,     /* dest = source                   */
	SrcPaint       = SRCPAINT,    /* dest = source OR dest           */
	SrcAnd         = SRCAND,      /* dest = source AND dest          */
	SrcInvert      = SRCINVERT,   /* dest = source XOR dest          */
	SrcErase       = SRCERASE,    /* dest = source AND (NOT dest )   */
	SrcCopyNot     = NOTSRCCOPY,  /* dest = (NOT source)             */
	SrcEraseNot    = NOTSRCERASE, /* dest = (NOT src) AND (NOT dest) */
	MergeCopy      = MERGECOPY,   /* dest = (source AND pattern)     */
	MergePaint     = MERGEPAINT,  /* dest = (NOT source) OR dest     */
	PatCopy        = PATCOPY,     /* dest = pattern                  */
	PatPaint       = PATPAINT,    /* dest = DPSnoo                   */
	PatInvert      = PATINVERT,   /* dest = pattern XOR dest         */
	DstInvert      = DSTINVERT,   /* dest = (NOT dest)               */
	Blackness      = BLACKNESS,   /* dest = BLACK                    */
	Whiteness      = WHITENESS,   /* dest = WHITE                    */
	NoMirrorBitmap = NOMIRRORBITMAP,  /* Do not Mirror the bitmap in this call */
	CaptureBlt     = CAPTUREBLT       /* Include layered windows */);
enum_flags(Rop2, int,
	Black          = R2_BLACK,
	NotMergePen    = R2_NOTMERGEPEN,
	MaskNotPen     = R2_MASKNOTPEN,
	NotCopyPen     = R2_NOTCOPYPEN,
	MaskPenNot     = R2_MASKPENNOT,
	Not            = R2_NOT,
	XorPen         = R2_XORPEN,
	NotMaskPen     = R2_NOTMASKPEN,
	MaskPen        = R2_MASKPEN,
	NotXorPen      = R2_NOTXORPEN,
	Nop            = R2_NOP,
	MergeNotPen    = R2_MERGENOTPEN,
	CopyPen        = R2_COPYPEN,
	MergePenNot    = R2_MERGEPENNOT,
	MergePen       = R2_MERGEPEN,
	White          = R2_WHITE);
enum_class(StretcheModes, int,
	And            = BLACKONWHITE,
	Or             = WHITEONBLACK,
	Del            = COLORONCOLOR,
	Half           = HALFTONE);
enum_flags(TextAlign, UINT, 
	NoUpDateCP     = TA_NOUPDATECP,
	UpDateCP       = TA_UPDATECP,
	Left           = TA_LEFT,
	Right          = TA_RIGHT,
	Center         = TA_CENTER,
	Top            = TA_TOP,
	Bottom         = TA_BOTTOM,
	Baseline       = TA_BASELINE,
	RTLReading     = TA_RTLREADING);
enum_flags(Illuminants, WORD,
	Default        = ILLUMINANT_DEVICE_DEFAULT,
	A              = ILLUMINANT_A,
	B              = ILLUMINANT_B,
	C              = ILLUMINANT_C,
	D50            = ILLUMINANT_D50,
	D55            = ILLUMINANT_D55,
	D65            = ILLUMINANT_D65,
	D75            = ILLUMINANT_D75,
	F2             = ILLUMINANT_F2,
	Tungsten       = ILLUMINANT_TUNGSTEN,
	DayLight       = ILLUMINANT_DAYLIGHT,
	Fluorescent    = ILLUMINANT_FLUORESCENT,
	NTSC           = ILLUMINANT_NTSC);
class ColorAdjustment : public StructShim<COLORADJUSTMENT> {
public:
	using super = StructShim<COLORADJUSTMENT>;
public:
	ColorAdjustment() reflect_to(self->caSize = sizeof(COLORADJUSTMENT));
	ColorAdjustment(const COLORADJUSTMENT &ca) : super(ca) {}
public: // Property - Illuminant
	/* W */ inline auto &Illuminant(Illuminants caIlluminantIndex) reflect_to_self(self->caIlluminantIndex = caIlluminantIndex.yield());
	/* R */ inline auto  Illuminant() const reflect_as(reuse_as<Illuminants>(self->caIlluminantIndex));
public: // Property - RedGamma
	/* W */ inline auto &RedGamma(WORD caRedGamma) reflect_to_self(self->caRedGamma = caRedGamma);
	/* R */ inline WORD  RedGamma() const reflect_as(self->caRedGamma);
public: // Property - GreenGamma
	/* W */ inline auto &GreenGamma(WORD caGreenGamma) reflect_to_self(self->caGreenGamma = caGreenGamma);
	/* R */ inline WORD  GreenGamma() const reflect_as(self->caGreenGamma);
public: // Property - BlueGamma
	/* W */ inline auto &BlueGamma(WORD caBlueGamma) reflect_to_self(self->caBlueGamma = caBlueGamma);
	/* R */ inline WORD  BlueGamma() const reflect_as(self->caBlueGamma);
public: // Property - ReferenceBlack
	/* W */ inline auto &ReferenceBlack(WORD caReferenceBlack) reflect_to_self(self->caReferenceBlack = caReferenceBlack);
	/* R */ inline WORD  ReferenceBlack() const reflect_as(self->caReferenceBlack);
public: // Property - ReferenceWhite
	/* W */ inline auto &ReferenceWhite(WORD caReferenceWhite) reflect_to_self(self->caReferenceWhite = caReferenceWhite);
	/* R */ inline WORD  ReferenceWhite() const reflect_as(self->caReferenceWhite);
public: // Property - Contrast
	/* W */ inline auto &Contrast(SHORT caContrast) reflect_to_self(self->caContrast = caContrast);
	/* R */ inline SHORT Contrast() const reflect_as(self->caContrast);
public: // Property - Brightness
	/* W */ inline auto &Brightness(SHORT caBrightness) reflect_to_self(self->caBrightness = caBrightness);
	/* R */ inline SHORT Brightness() const reflect_as(self->caBrightness);
public: // Property - Colorfulness
	/* W */ inline auto &Colorfulness(SHORT caColorfulness) reflect_to_self(self->caColorfulness = caColorfulness);
	/* R */ inline SHORT Colorfulness() const reflect_as(self->caColorfulness);
public: // Property - RedGreenTint
	/* W */ inline auto &RedGreenTint(SHORT caRedGreenTint) reflect_to_self(self->caRedGreenTint = caRedGreenTint);
	/* R */ inline SHORT RedGreenTint() const reflect_as(self->caRedGreenTint);
};
class RGBIndex : public StructShim<CIEXYZ> {
public:
	using super = StructShim<CIEXYZ>;
public:
	RGBIndex() {}
	RGBIndex(const CIEXYZ &xyz) : super(xyz) {}
	RGBIndex(FXPT2DOT30 ciexyzX, FXPT2DOT30 ciexyzY, FXPT2DOT30 ciexyzZ) : 
		super(CIEXYZ{ ciexyzX, ciexyzY, ciexyzZ }) {}
public: // Property - X
	/* W */ inline auto&X(FXPT2DOT30 ciexyzX) reflect_to_self(self->ciexyzX = ciexyzX);
	/* R */ inline auto X() const reflect_as(self->ciexyzX);
public: // Property - Y
	/* W */ inline auto&Y(FXPT2DOT30 ciexyzY) reflect_to_self(self->ciexyzY = ciexyzY);
	/* R */ inline auto Y() const reflect_as(self->ciexyzY);
public: // Property - Z
	/* W */ inline auto&Z(FXPT2DOT30 ciexyzZ) reflect_to_self(self->ciexyzZ = ciexyzZ);
	/* R */ inline auto Z() const reflect_as(self->ciexyzZ);
};
class RGBTriple : public StructShim<CIEXYZTRIPLE> {
public:
	using super = StructShim<CIEXYZTRIPLE>;
public:
	RGBTriple() {}
	RGBTriple(const CIEXYZTRIPLE &xyzTriple) : super(xyzTriple) {}
	RGBTriple(CIEXYZ ciexyzR, CIEXYZ ciexyzG, CIEXYZ ciexyzB) : super(CIEXYZTRIPLE{ ciexyzR, ciexyzG, ciexyzB }) {}
public: // Property - Red
	/* W */ inline auto&Red(RGBIndex ciexyzRed) reflect_to_self(self->ciexyzRed = *ciexyzRed);
	/* R */ inline auto Red() const reflect_as(reuse_as<RGBIndex>(self->ciexyzRed));
public: // Property - Green
	/* W */ inline auto&Green(RGBIndex ciexyzGreen) reflect_to_self(self->ciexyzGreen = *ciexyzGreen);
	/* R */ inline auto Green() const reflect_as(reuse_as<RGBIndex>(self->ciexyzGreen));
public: // Property - Blue
	/* W */ inline auto&Blue(RGBIndex ciexyzBlue) reflect_to_self(self->ciexyzBlue = *ciexyzBlue);
	/* R */ inline auto Blue() const reflect_as(reuse_as<RGBIndex>(self->ciexyzBlue));
};
enum_flags(ColorType, LCSCSTYPE,
	CalibratedRGB     = LCS_CALIBRATED_RGB,
	sRGB              = LCS_sRGB,
	Default           = LCS_WINDOWS_COLOR_SPACE);
enum_flags(ColorIntents, DWORD,
	Perceptual        = LCS_GM_BUSINESS,
	Relative          = LCS_GM_GRAPHICS,
	Saturation        = LCS_GM_IMAGES,
	Absolute          = LCS_GM_ABS_COLORIMETRIC);
template<bool IsUnicode>
class ColorSpaceX : public StructShim<std::conditional_t<IsUnicode, LOGCOLORSPACEW, LOGCOLORSPACEA>> {
public:
	using LOGCOLORSPACE = std::conditional_t<IsUnicode, LOGCOLORSPACEW, LOGCOLORSPACEA>;
	using super = StructShim<LOGCOLORSPACE>;
	using String = StringX<IsUnicode>;
public:
	ColorSpaceX() reflect_to(self->lcsSize = sizeof(LOGCOLORSPACE);
							 self->lcsSignature = LCS_SIGNATURE;
							 self->lcsVersion = 0x400);
	ColorSpaceX(const LOGCOLORSPACE &cs) : super(cs) {}
public: // Property - Type
	/* W */ inline auto&Type(ColorType lcsCSType) reflect_to_self(self->lcsCSType = lcsCSType.yield());
	/* R */ inline auto Type() const reflect_as(reuse_as<ColorType>(self->lcsCSType));
public: // Property - Intent
	/* W */ inline auto&Intent(ColorIntents lcsIntent) reflect_to_self(self->lcsIntent = lcsIntent.yield());
	/* R */ inline auto Intent() const reflect_as(reuse_as<ColorIntents>(self->lcsIntent));
public: // Property - Endpoints
	/* W */ inline auto&Endpoints(RGBTriple lcsEndpoints) reflect_to_self(self->lcsEndpoints = *lcsEndpoints);
	/* R */ inline auto Endpoints() const reflect_as(reuse_as<RGBTriple>(self->lcsEndpoints));
public: // Property - GammaRed
	/* W */ inline auto&GammaRed(RGBIndex lcsGammaRed) reflect_to_self(self->lcsGammaRed = *lcsGammaRed);
	/* R */ inline auto GammaRed() const reflect_as(reuse_as<RGBIndex>(self->lcsGammaRed));
public: // Property - GammaGreen
	/* W */ inline auto&GammaGreen(RGBIndex lcsGammaGreen) reflect_to_self(self->lcsGammaGreen = *lcsGammaGreen);
	/* R */ inline auto GammaGreen() const reflect_as(reuse_as<RGBIndex>(self->lcsGammaGreen));
public: // Property - GammaBlue
	/* W */ inline auto &GammaBlue(RGBIndex lcsGammaBlue) reflect_to_self(self->lcsGammaBlue = *lcsGammaBlue);
	/* R */ inline auto  GammaBlue() const reflect_as(reuse_as<RGBIndex>(self->lcsGammaBlue));
public: // Property - Filename
	/* W */ inline auto &Filename(const String &strFilename) reflect_to_self(strFilename.CopyTo(self->lcsFilename, MAX_PATH));
	/* R */ inline const String Filename() const reflect_to(CString(MAX_PATH, self->lcsFilename));
};
using ColorSpace = ColorSpaceX<IsUnicode>;
using ColorSpaceA = ColorSpaceX<false>;
using ColorSpaceW = ColorSpaceX<true>;
#pragma endregion

class XForm : public StructShim<XFORM> {
public:
	using super = StructShim<XFORM>;
public:
	XForm() {}
	XForm(const XFORM &xf) : super(xf) {}
	XForm(FLOAT eM11, FLOAT eM12, FLOAT eM21, FLOAT eM22, FLOAT eDx = 0, FLOAT eDy = 0) :
		super(XFORM{ eM11, eM12, eM21, eM22, eDx, eDy }) {}
public: // Property - M11
	/* W */ inline auto&M11(FLOAT eM11) reflect_to_self(self->eM11 = eM11);
	/* R */ inline auto M11() const reflect_as(self->eM11);
public: // Property - M12
	/* W */ inline auto&M12(FLOAT eM12) reflect_to_self(self->eM12 = eM12);
	/* R */ inline auto M12() const reflect_as(self->eM12);
public: // Property - M21
	/* W */ inline auto&M21(FLOAT eM21) reflect_to_self(self->eM21 = eM21);
	/* R */ inline auto M21() const reflect_as(self->eM21);
public: // Property - M22
	/* W */ inline auto&M22(FLOAT eM22) reflect_to_self(self->eM22 = eM22);
	/* R */ inline auto M22() const reflect_as(self->eM22);
public: // Property - Dx
	/* W */ inline auto&Dx(FLOAT eDx) reflect_to_self(self->eDx = eDx);
	/* R */ inline auto Dx() const reflect_as(self->eDx);
public: // Property - Dy
	/* W */ inline auto&Dy(FLOAT eDy) reflect_to_self(self->eDy = eDy);
	/* R */ inline auto Dy() const reflect_as(self->eDy);
//public: // Property - Offset
//	/* W */ inline auto&Offset(LPoint off) reflect_to_self(self->eDx = off.x, self->eDy = off.y);
//	/* R */ inline auto Offset() const reflect_as(LPoint{ self->eDx, self->eDy });
public:
	class IFloat {
		friend class XForm;
		FLOAT &f;
	private:
		IFloat(const IFloat &) = delete;
		IFloat(FLOAT &f) : f(f) {}
	public:
		IFloat(IFloat &&) = default;
	public:
		inline operator FLOAT&() const reflect_as(f);
		inline operator FLOAT() const reflect_as(f);
	};
	inline IFloat operator[](LPoint pt) {
		if (pt.x == 0 && pt.y == 0) return self->eM11;
		if (pt.x == 1 && pt.y == 0) return self->eM12;
		if (pt.x == 0 && pt.y == 1) return self->eM21;
		if (pt.x == 1 && pt.y == 1) return self->eM22;
		assertl(false);
	}
	inline FLOAT operator[](LPoint pt) const {
		if (pt.x == 0 && pt.y == 0) return self->eM11;
		if (pt.x == 1 && pt.y == 0) return self->eM12;
		if (pt.x == 0 && pt.y == 1) return self->eM21;
		if (pt.x == 1 && pt.y == 1) return self->eM22;
		assertl(false);
	}
};

#if(WINVER >= 0x0400)
#define DRAWTEXT_1 \
	, EditControl          = DT_EDITCONTROL   \
	, PathEllipsis         = DT_PATH_ELLIPSIS \
	, EndEllipsis          = DT_END_ELLIPSIS  \
	, ModifyString         = DT_MODIFYSTRING  \
	, RTLReading           = DT_RTLREADING    \
	, WordEllipsis         = DT_WORD_ELLIPSIS
#if(WINVER >= 0x0500)
#define DRAWTEXT_2 \
	, NoFullWidthCharBreak = DT_NOFULLWIDTHCHARBREAK
#if(_WIN32_WINNT >= 0x0500)
#define DRAWTEXT_3 \
	, HidePrefix           = DT_HIDEPREFIX \
	, PrefixOnly           = DT_PREFIXONLY
#endif
#endif
#endif

enum_flags(TextDraw, UINT,
	  Top               = DT_TOP
	, Left              = DT_LEFT
	, Center            = DT_CENTER
	, Right             = DT_RIGHT
	, VCenter           = DT_VCENTER
	, Bottom            = DT_BOTTOM
	, WordBreak         = DT_WORDBREAK
	, SingleLine        = DT_SINGLELINE
	, ExpandTabs        = DT_EXPANDTABS
	, TabStop           = DT_TABSTOP
	, NoClip            = DT_NOCLIP
	, ExternalLeading   = DT_EXTERNALLEADING
	, CalcRect          = DT_CALCRECT
	, NoPrefix          = DT_NOPREFIX
	, Internal          = DT_INTERNAL
	DRAWTEXT_1
	DRAWTEXT_2
	DRAWTEXT_3);

class BaseOf_GDI(DevCap, HDC) {
public:
	using super = GObjectBase<DevCap, HDC>;
protected:
	PROXY_SHIM(DevCap);
	DevCap(HDC h) : super(h) {}
	DevCap(const DevCap &d) : super(d) {}
public:
	DevCap() {}
	DevCap(Null) {}
	DevCap(DevCap &d) : super(d) {}
	DevCap(DevCap &&d) : super(d) {}
	~DevCap() reflect_to(Delete());
public:
	static inline DevCap CreateCompatible(HDC hdc = O) reflect_as(WX::CreateCompatibleDC(hdc));
public:
	//inline void Delete() {
	//	if (self)
	//		assertl(DeleteDC(self));
	//	this->hobj = O;
	//}
	inline auto Release(HWND hWnd) reflect_as(WX::ReleaseDC(hWnd, self));

	inline CGObject Select(HGDIOBJ ho) reflect_as(::SelectObject(self, ho));
	inline CPalette Palette(HPALETTE hPal, bool bForceBkgd = false) reflect_to(hPal = WX::SelectPalette(self, hPal, bForceBkgd), hPal);
	inline UINT PaletteRealize() const reflect_as(WX::RealizePalette(self));

//	inline auto &BltStretch(LPoint dstStart, LSize dstSize, Rop rop = Rop::SrcCopy)
	inline auto &BltStretch(LPoint dstStart, LSize dstSize, HDC hdcSrc, LPoint srcStart, LSize srcSize, Rop rop = Rop::SrcCopy) reflect_to_self(WX::StretchBlt(self, dstStart.x, dstStart.y, dstSize.cx, dstSize.cy, hdcSrc, srcStart.x, srcStart.y, srcSize.cx, srcSize.cy, rop.yield()));
	inline auto &BltStretch(LRect dst, HDC hdcSrc, LRect src, Rop rop = Rop::SrcCopy) reflect_to_self(BltStretch(dst.left_top(), dst.size(), hdcSrc, src.left_top(), src.size(), rop));
	inline auto &BltBit(LPoint dstStart, LSize dstSize, HDC hdcSrc, LPoint srcStart = 0, Rop rop = Rop::SrcCopy) reflect_to_self(WX::BitBlt(self, dstStart.x, dstStart.y, dstSize.cx, dstSize.cy, hdcSrc, srcStart.x, srcStart.y, rop.yield()));
	inline auto &BltBit(LRect rc, HDC hdcSrc, LPoint srcStart = 0, Rop rop = Rop::SrcCopy) reflect_to_self(BltBit(rc.left_top(), rc.size(), hdcSrc, srcStart, rop));

	template<size_t len>
	inline auto &DrawPolyline(const POINT(&pts)[len]) reflect_to_self(WX::Polyline(self, &pts, len));
	template<size_t len>
	inline auto &DrawPolyline(const LPoint(&pts)[len]) reflect_to_self(WX::Polyline(self, (CONST POINT *)&pts, len));
	inline auto &DrawPolyline(const LPoint *pts, int len) reflect_to_self(WX::Polyline(self, (CONST POINT *)pts, len));
	inline auto &DrawPolyline(const POINT *pts, int len) reflect_to_self(WX::Polyline(self, pts, len));
	inline auto &DrawIcon(HICON hIcon, LPoint p = 0) reflect_to_self(WX::DrawIcon(self, p.x, p.y, hIcon));
	inline int  DrawText(String text, LRect r = 0, TextDraw format = TextDraw::Left) reflect_as(WX::DrawText(self, text, (int)text.Length(), r, format.yield()));
	inline auto &DrawPixel(COLORREF rgb, LPoint p) reflect_to_self(WX::SetPixel(self, p.x, p.y, rgb));
	inline auto &DrawPie(LRect rc, LPoint start, LPoint end) reflect_to_self(WX::Pie(self, rc.left, rc.top, rc.right, rc.bottom, start.x, start.y, end.x, end.y));
	inline auto &DrawEllipse(LRect rc) reflect_to_self(Ellipse(self, rc.left, rc.top, rc.right, rc.bottom));
	inline auto &DrawFrame(LRect rc) reflect_to_self(WX::InvertRect(self, rc));
	inline auto &DrawFocus(HBRUSH hbr, LRect rc) reflect_to_self(WX::FrameRect(self, &rc, hbr));
	inline auto &Invert(LRect rc) reflect_to_self(WX::InvertRect(self, rc));
	inline auto &Fill(HBRUSH hbr, LRect rc) reflect_to_self(WX::FillRect(self, rc, hbr));
	inline auto &Fill(HBRUSH hbr) reflect_as(Fill(hbr, Size()));
public:
	class IPixel {
		friend class DevCap;
		HDC hdc;
		POINT pt;
	private:
		IPixel(const IPixel &) = delete;
		IPixel(HDC hdc, POINT pt) : hdc(hdc), pt(pt) {}
	public:
		IPixel(IPixel &&) = default;
	public:
		inline operator RGBColor() const reflect_as(WX::GetPixel(hdc, pt.x, pt.y));
		inline operator COLORREF() const reflect_as(WX::GetPixel(hdc, pt.x, pt.y));
		inline void operator=(COLORREF clr) reflect_to(WX::SetPixel(hdc, pt.x, pt.y, clr));
	};
	inline IPixel Pixel(LPoint pt) reflect_as({ self, pt });
	inline const IPixel Pixel(LPoint pt) const reflect_as({ self, pt });

#pragma region Properties
public: // Property - BkColor
	/* W */ inline auto&BkColor(COLORREF rgb) reflect_to_self(WX::SetBkColor(self, rgb));
	/* R */ inline auto BkColor() const reflect_as((RGBColor)WX::GetBkColor(self));
public: // Property - PenColor
	/* W */ inline auto&PenColor(COLORREF rgb) reflect_to_self(WX::SetDCPenColor(self, rgb));
	/* R */ inline auto PenColor() const reflect_as((RGBColor)WX::GetDCPenColor(self));
public: // Property - TextColor
	/* W */ inline auto&TextColor(COLORREF color) reflect_to_self(SetTextColor(self, color));
	/* R */ inline auto TextColor() const reflect_as((RGBColor)WX::GetTextColor(self));
public: // Property - BrushColor
	/* W */ inline auto&BrushColor(COLORREF rgb) reflect_to_self(WX::SetDCBrushColor(self, rgb));
	/* R */ inline auto BrushColor() const reflect_as((RGBColor)WX::GetDCBrushColor(self));
public: // Property - BrushOrg
	/* W */ inline auto&BrushOrg(LPoint pt) reflect_to_self(WX::SetBrushOrgEx(self, pt.x, pt.y, O));
	/* R */ inline auto BrushOrg() const reflect_to(LPoint pt, WX::GetBrushOrgEx(self, &pt), pt);
public: // Property - BkMode
public: // Property - ViewOrg
	/* W */ inline auto&ViewOrg(LPoint pt) reflect_to_self(WX::SetViewportOrgEx(self, pt.x, pt.y, O));
	/* R */ inline auto ViewOrg() const reflect_to(LPoint pt, WX::GetViewportOrgEx(self, &pt), pt);
public: // Property - ViewExt
	/* W */ inline auto&ViewExt(LSize sz) reflect_to_self(WX::SetViewportExtEx(self, sz.cx, sz.cy, O));
	/* R */ inline auto ViewExt() const reflect_to(LSize sz, WX::GetViewportExtEx(self, &sz), sz);
public: // Property - WindowOrg
	/* W */ inline auto&WindowOrg(LPoint pt) reflect_to_self(WX::SetWindowOrgEx(self, pt.x, pt.y, O));
	/* R */ inline auto WindowOrg() const reflect_to(LPoint pt, WX::GetWindowOrgEx(self, &pt), pt);
public: // Property - WindowExt
	/* W */ inline auto&WindowExt(LSize sz) reflect_to_self(WX::SetWindowExtEx(self, sz.cx, sz.cy, O));
	/* R */ inline auto WindowExt() const reflect_to(LSize sz, WX::GetWindowExtEx(self, &sz), sz);
public: // Property - Size
	/* R */ inline LSize Size() const reflect_as({ WX::GetDeviceCaps(self, HORZRES), WX::GetDeviceCaps(self, VERTRES) });
public: // Property - WorldTransform
	/* W */ inline auto&WorldTransform(const XForm &xf) reflect_to_self(WX::SetWorldTransform(self, &xf));
	/* R */ inline auto WorldTransform() const reflect_to(XForm xf; WX::GetWorldTransform(self, &xf), xf);
public: // Property - MapMode
	/* W */ inline auto&MapMode(MapModes mode) reflect_to_self(WX::SetMapMode(self, mode.yield()));
	/* R */ inline auto MapMode() const reflect_as(reuse_as<MapModes>(WX::GetMapMode(self)));
public: // Property - TextAligns
	/* W */ inline auto&TextAligns(TextAlign align) reflect_to_self(WX::SetTextAlign(self, align.yield()));
	/* R */ inline auto TextAligns() const reflect_as(reuse_as<TextAlign>(WX::GetTextAlign(self)));
public: // Property - StretchMode
	/* W */ inline auto&StretchMode(StretcheModes mode) reflect_to_self(WX::SetStretchBltMode(self, mode.yield()));
	/* R */ inline auto StretchMode() const reflect_as(reuse_as<StretcheModes>(WX::GetStretchBltMode(self)));
public: // Property - PolyFillMode
	/* W */ inline auto&PolyFillMode(PolyFillModes mode) reflect_to_self(WX::SetPolyFillMode(self, mode.yield()));
	/* W */ inline auto PolyFillMode() const reflect_as(reuse_as<PolyFillModes>(WX::GetPolyFillMode(self)));
public: // Property - Rop2
	/* W */ inline auto&Rop2(WX::Rop2 rop2) reflect_to_self(WX::SetROP2(self, rop2.yield()));
	/* R */ inline auto Rop2() const reflect_as(reuse_as<WX::Rop2>(WX::GetROP2(self)));
public: // Property - MiterLimit
	/* W */ inline auto&MiterLimit(FLOAT limit) reflect_to_self(WX::SetMiterLimit(self, limit, O));
	/* R */ inline auto MiterLimit() const reflect_to(FLOAT f = 0, WX::GetMiterLimit(self, &f), f);
public: // Property - ColorAdjustment
	/* W */ inline auto&ColorAdjustment(const WX::ColorAdjustment &ca) reflect_to_self(WX::SetColorAdjustment(self, &ca));
	/* R */ inline auto ColorAdjustment() const reflect_to(WX::ColorAdjustment ca; WX::GetColorAdjustment(self, &ca), ca);
public: // Property - ICMProfile
	/* W */ inline auto &ICMProfile(const StringA &str) reflect_to_self(WX::SetICMProfile(self, const_cast<LPSTR>(str.c_str())));
	/* W */ inline auto &ICMProfile(const StringW &str) reflect_to_self(WX::SetICMProfile(self, const_cast<LPWSTR>(str.c_str())));
	template<bool IsUnicode = WX::IsUnicode>
	/* R */ inline StringX<IsUnicode> ICMProfile() const {
		DWORD len = 0;
		WX::GetICMProfile(self, &len, (LPXSTR<IsUnicode>)O);
		StringX<IsUnicode> str((size_t)len);
		WX::GetICMProfile(self, O, str);
		return to_right_hand(str);
	}
#pragma endregion
public:
	using super::operator=;
	inline auto&operator()(HGDIOBJ ho) reflect_to_self(Select(ho));
	inline auto&operator()(Bitmap &ho) reflect_to_self(Select(ho));
	inline auto&operator()(const Pen &ho) reflect_to_self(Select(ho));
	inline auto&operator()(const Brush &ho) reflect_to_self(Select(ho));
	inline auto&operator()(const WX::Palette hPal, bool bForceBkgd = false) reflect_to_self(Palette(hPal, bForceBkgd));
};
using CDevCap = ProxyShim<DevCap>;
using DC = DevCap;
using CDC = ProxyShim<DevCap>;
#pragma endregion

}
