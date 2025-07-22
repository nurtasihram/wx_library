#pragma once

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
	if constexpr (IsUnicode)
		 assertl_reflect_as(::GetCharWidthA(hdc, iFirst, iLast, lpBuffer))
	else assertl_reflect_as(::GetCharWidthW(hdc, iFirst, iLast, lpBuffer))
}
// GetCharWidth32
#undef GetCharWidth32
template<bool IsUnicode = WX::IsUnicode>
inline void GetCharWidth32(HDC hdc, UINT iFirst, UINT iLast, LPINT lpBuffer) {
	if constexpr (IsUnicode)
		 assertl_reflect_as(::GetCharWidth32A(hdc, iFirst, iLast, lpBuffer))
	else assertl_reflect_as(::GetCharWidth32W(hdc, iFirst, iLast, lpBuffer))
}
// GetCharWidthFloat
#undef GetCharWidthFloat
template<bool IsUnicode = WX::IsUnicode>
inline void GetCharWidthFloat(HDC hdc, UINT iFirst, UINT iLast, PFLOAT lpBuffer) {
	if constexpr (IsUnicode)
		 assertl_reflect_as(::GetCharWidthFloatA(hdc, iFirst, iLast, lpBuffer))
	else assertl_reflect_as(::GetCharWidthFloatW(hdc, iFirst, iLast, lpBuffer))
}
// GetCharABCWidths
#undef GetCharABCWidths
template<bool IsUnicode = WX::IsUnicode>
inline void GetCharABCWidths(HDC hdc, UINT wFirst, UINT wLast, LPABC lpABC) {
	if constexpr (IsUnicode)
		 assertl_reflect_as(::GetCharABCWidthsA(hdc, wFirst, wLast, lpABC))
	else assertl_reflect_as(::GetCharABCWidthsW(hdc, wFirst, wLast, lpABC))
}
// GetCharABCWidthsFloat
#undef GetCharABCWidthsFloat
template<bool IsUnicode = WX::IsUnicode>
inline void GetCharABCWidthsFloat(HDC hdc, UINT iFirst, UINT iLast, LPABCFLOAT lpABC) {
	if constexpr (IsUnicode)
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
	if constexpr (IsUnicode)
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
inline HGDIOBJ SelectObject(HDC hdc, HGDIOBJ h)
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
	if constexpr (IsUnicode)
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
	if constexpr (IsUnicode)
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
