#pragma once

#include "wx_type.h"

namespace WX {

#pragma region GObject
template<class AnyChild, class BaseHandle = HGDIOBJ>
class GObjectBase;
using GObject = GObjectBase<void>;
template<class AnyChild, class BaseHandle>
class GObjectBase : public ChainExtender<GObjectBase<AnyChild, BaseHandle>, AnyChild> {
	misuse_assert((std::is_convertible_v<BaseHandle, HGDIOBJ>),
				 "BaseHandle must can be converted to HANDLE");
public:
	using Child = Chain<GObjectBase, AnyChild>;
protected:
	friend class RefAs<GObjectBase>;
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
		if (hobj) {
			assertl(DeleteObject(hobj));
			hobj = O;
		}
	}
public:
	inline operator BaseHandle() const reflect_as(ref_as<BaseHandle>(hobj));
	inline Child &operator=(Child &obj) reflect_to_child(std::swap(obj.hobj, hobj));
	inline Child &operator=(Child &&obj) reflect_to_child(std::swap(obj.hobj, hobj));
	inline const Child &operator=(const Child &obj) const reflect_to_child(std::swap(obj.hobj, hobj));
public:
	static inline auto &Attach(BaseHandle &hObj) reflect_as(ref_as<AnyChild>(hObj));
	static inline const auto &Attach(const BaseHandle &hObj) reflect_as(ref_as<const AnyChild>(hObj));
};
using CGObject = RefAs<GObject>;
#define BaseOf_GDI(name, idt) name : public WX::GObjectBase<name, idt>
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
class FontLogicX : public RefAs<std::conditional_t<IsUnicode, LOGFONTW, LOGFONTA>> {
	using LOGFONT = std::conditional_t<IsUnicode, LOGFONTW, LOGFONTA>;
	using TCHAR = XCHAR<IsUnicode>;
	using String = StringBase<TCHAR>;
public:
	using super = RefAs<LOGFONT>;
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
	/* W */ inline auto &FaceName(String name) assertl_reflect_as_self(SUCCEEDED(AnyX<IsUnicode>(StringCchCopyA, StringCchCopyW)(self->lfFaceName, name.Length() + 1, name)));
	/* R */ inline const String FaceName() const reflect_as(CString(self->lfFaceName, LF_FACESIZE));
};
using FontLogic = FontLogicX<IsUnicode>;
using FontLogicA = FontLogicX<false>;
using FontLogicW = FontLogicX<true>;
using CFontLogic = RefAs<FontLogic>;
using CFontLogicA = RefAs<FontLogicA>;
using CFontLogicW = RefAs<FontLogicW>;
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
	friend class RefAs<Font>;
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
	static inline Font Create(const LogicA &LogFont) assertl_reflect_as(auto hfont = CreateFontIndirectA(&LogFont), hfont);
	static inline Font Create(const LogicW &LogFont) assertl_reflect_as(auto hfont = CreateFontIndirectW(&LogFont), hfont);
public:
	using super::operator=;
};
using CFont = RefAs<Font>;
#pragma endregion

#pragma region Bitmap
enum_class(BitmapCompressions, DWORD,
	RGB         = BI_RGB,
	RLE8        = BI_RLE8,
	RLE4        = BI_RLE4,
	BitFields   = BI_BITFIELDS,
	JPEG        = BI_JPEG,
	PNG         = BI_PNG);
#pragma pack(2)
struct BitmapHeader : protected BITMAPFILEHEADER, protected BITMAPINFO {
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
struct BitmapLogic : public RefAs<BITMAP> {
	using super = RefAs<BITMAP>;
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
	inline HBITMAP Create() const assertl_reflect_as(auto h = CreateBitmapIndirect(self), h);
	inline operator HBITMAP() const reflect_as(Create());
};
class BaseOf_GDI(Bitmap, HBITMAP) {
public:
	using Header = BitmapHeader;
	using File = BitmapHeader;
	using Logic = BitmapLogic;
	using super = GObjectBase<Bitmap, HBITMAP>;
protected:
	friend class RefAs<Bitmap>;
	Bitmap(HBITMAP h) : super(h) {}
	Bitmap(const Bitmap &b) : super(b) {}
public:
	Bitmap() {}
	Bitmap(Null) {}
	Bitmap(Bitmap &b) : super(b) {}
	Bitmap(Bitmap &&b) : super(b) {}
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
		inline Bitmap Create() const assertl_reflect_as(auto h = CreateBitmap(nWidth, nHeight, nPlanes, nBitsPerPixel, lpBits), h);
		inline operator Bitmap() const reflect_as(Create());
	};
	static inline CreateStruct Create(LSize s = 0) reflect_as(s);
	static inline Bitmap Create(const BITMAPINFO *pbi, void **ppbits, HANDLE hSection = O, DWORD offset = 0) assertl_reflect_as(auto h = CreateDIBSection(O, pbi, DIB_RGB_COLORS, ppbits, hSection, offset), h);
	static inline Bitmap Create(const BITMAPINFO *pbi, HANDLE hSection = O, DWORD offset = 0) assertl_reflect_as(auto h = CreateDIBSection(O, pbi, DIB_RGB_COLORS, O, hSection, offset), h);
	static inline Bitmap From(HDC hDC, LSize s) reflect_as(CreateCompatibleBitmap(hDC, s.cx, s.cy));
public:
	inline auto &Restretch(LSize sz) assertl_reflect_as_self((super::hobj = (HBITMAP)CopyImage(self, IMAGE_BITMAP, sz.cx, sz.cy, LR_DEFAULTSIZE)));
	inline Bitmap StretchNew(LSize sz) const assertl_reflect_as(auto h = (HBITMAP)CopyImage(self, IMAGE_BITMAP, sz.cx, sz.cy, LR_DEFAULTCOLOR), h);
	inline Bitmap Clone() const reflect_as(StretchNew(Size()));
#pragma region Properties
public: // Property - Size
	/* R */ inline LSize Size() const assertl_reflect_to(LSize sz, GetBitmapDimensionEx(self, &sz), sz);
public: // Property - SizeBytes
	/* R */ inline size_t SizeBytes() const {
		auto &&log = Log();
		return (((log.Width() * log.Planes() /* nPlanes */ * log.BitsPerPixel() /* nBitCount */ + 15) >> 4) << 1) * log.Height();
	}
public: // Property - Colors
	/* W */ inline auto &GetColors(void *lpBits, DWORD cb) const assertl_reflect_as_self(GetBitmapBits(self, cb, lpBits));
	/* R */ inline auto &SetColors(const void *lpBits, DWORD cb) assertl_reflect_as_self(SetBitmapBits(self, cb, lpBits));
public: // Property - Log
	inline Logic Log() const reflect_to(Logic log, GetObject(self, sizeof(log), reinterpret_cast<LPSTR>(&log)), log);
#pragma endregion
public:
	using super::operator=;
};
using CBitmap = RefAs<Bitmap>;
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
struct PenLogic : public RefAs<LOGPEN> {
	using super = RefAs<LOGPEN>;
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
	friend class RefAs<Pen>;
	Pen(HPEN h) : super(h) {}
	Pen(const Pen &p) : super(p) {}
public:
	Pen() {}
	Pen(Null) {}
	Pen(Pen &p) : super(p) {}
	Pen(Pen &&p) : super(p) {}
	Pen(const PenLogic &log) : super(Create(log)) {}
public:
	static inline Pen Create(const PenLogic &log) assertl_reflect_as(auto h = CreatePenIndirect(&log), h);
	static inline Pen Create(Styles styles, COLORREF rgb, int nWidth = 0) assertl_reflect_as(auto h = CreatePen(styles.yield(), nWidth, rgb), h);
	static inline Pen CreateSolid(COLORREF rgb, int nWidth = 0)       assertl_reflect_as(auto h = CreatePen(PS_SOLID, nWidth, rgb), h);
	static inline Pen CreateDash(COLORREF rgb, int nWidth = 0)        assertl_reflect_as(auto h = CreatePen(PS_DASH, nWidth, rgb), h);
	static inline Pen CreateDot(COLORREF rgb, int nWidth = 0)         assertl_reflect_as(auto h = CreatePen(PS_DOT, nWidth, rgb), h);
	static inline Pen CreateDashDot(COLORREF rgb, int nWidth = 0)     assertl_reflect_as(auto h = CreatePen(PS_DASHDOT, nWidth, rgb), h);
	static inline Pen CreateDashDotDot(COLORREF rgb, int nWidth = 0)  assertl_reflect_as(auto h = CreatePen(PS_DASHDOTDOT, nWidth, rgb), h);
	static inline Pen CreateNull(COLORREF rgb, int nWidth = 0)        assertl_reflect_as(auto h = CreatePen(PS_NULL, nWidth, rgb), h);
	static inline Pen CreateInsideFrame(COLORREF rgb, int nWidth = 0) assertl_reflect_as(auto h = CreatePen(PS_INSIDEFRAME, nWidth, rgb), h);
	static inline Pen CreateUserStyle(COLORREF rgb, int nWidth = 0)   assertl_reflect_as(auto h = CreatePen(PS_USERSTYLE, nWidth, rgb), h);
	static inline Pen CreateAlternate(COLORREF rgb, int nWidth = 0)   assertl_reflect_as(auto h = CreatePen(PS_ALTERNATE, nWidth, rgb), h);
public:
	static inline Pen White() reflect_as((HPEN)::GetStockObject(WHITE_PEN));
	static inline Pen Black() reflect_as((HPEN)::GetStockObject(BLACK_PEN));
	static inline Pen Null()  reflect_as((HPEN)::GetStockObject(NULL_PEN));
	static inline Pen DC()    reflect_as((HPEN)::GetStockObject(DC_PEN));
public: // Property - Log
	/* R */
public:
	using super::operator=;
};
using CPen = RefAs<Pen>;
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
enum_class(HatchStyle, int,
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
	friend class RefAs<Brush>;
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
	Brush(HatchStyle hs, COLORREF rgb) : super(CreateHatch(rgb, hs)) {}
public:
	static inline Brush CreateSolid(COLORREF rgb)                assertl_reflect_as(auto h = CreateSolidBrush(rgb), h);
	static inline Brush CreatePattern(HBITMAP hbm)               assertl_reflect_as(auto h = CreatePatternBrush(hbm), h);
	static inline Brush CreateHatch(COLORREF rgb, HatchStyle hs) assertl_reflect_as(auto h = CreateHatchBrush(hs.yield(), rgb), h);
public:
	static inline Brush White()   reflect_as((HBRUSH)::GetStockObject(WHITE_BRUSH));
	static inline Brush LitGray() reflect_as((HBRUSH)::GetStockObject(LTGRAY_BRUSH));
	static inline Brush Gray()    reflect_as((HBRUSH)::GetStockObject(GRAY_BRUSH));
	static inline Brush DkGray()  reflect_as((HBRUSH)::GetStockObject(DKGRAY_BRUSH));
	static inline Brush Black()   reflect_as((HBRUSH)::GetStockObject(BLACK_BRUSH));
	static inline Brush Null()    reflect_as((HBRUSH)::GetStockObject(NULL_BRUSH));
	static inline Brush DC()      reflect_as((HBRUSH)::GetStockObject(DC_BRUSH));
public:
	static inline Brush SysColor(WX::SysColor sc) assertl_reflect_as(auto hbr = GetSysColorBrush((int)sc.yield()), hbr);
public:
	using super::operator=;
};
using CBrush = RefAs<Brush>;
#pragma endregion

#pragma region Palette
struct PaletteEntry : public RefAs<PALETTEENTRY> {
	using super = RefAs<PALETTEENTRY>;
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
	friend class RefAs<Palette>;
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
		AutoPointer<Heap, LOGPALETTE> hPal;
		hPal.Alloc(sizeof(LOGPALETTE) + (nCount - 1) * sizeof(Entry));
		auto pPal = &hPal;
		pPal->palVersion = 0x300;
		pPal->palNumEntries = (WORD)nCount;
		CopyMemory(&pPal->palPalEntry, lpEntries, sizeof(Entry) * nCount);
		assertl(this->hobj = CreatePalette(pPal));
	}
	Palette(std::initializer_list<COLORREF> entries) : Palette((const Entry *)entries.begin(), (UINT)entries.size()) {}
	Palette(std::initializer_list<Entry> entries) : Palette(entries.begin(), (UINT)entries.size()) {}
	Palette(const std::vector<Entry> &entries) : Palette(entries.data(), (UINT)entries.size()) {}
public:
//	static inline Palette Create() assertl_reflect_as();
	static inline Palette Default() reflect_as((HPALETTE)GetStockObject(DEFAULT_PALETTE));
public:
	inline auto &SetEntries(UINT iStart, const Entry *pPalEntries, UINT cEntries = 1) assertl_reflect_as_self(SetPaletteEntries(self, iStart, cEntries, (const PALETTEENTRY *)pPalEntries));
	inline auto &GetEntries(UINT iStart, Entry *pPalEntries, UINT cEntries = 1) const assertl_reflect_as_self(GetPaletteEntries(self, iStart, cEntries, (LPPALETTEENTRY)pPalEntries));
	inline UINT NearestIndex(COLORREF cr) const reflect_as(GetNearestPaletteIndex(self, cr));
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
	/* W */ inline auto &Count(WORD nNumEntries) assertl_reflect_as_self(ResizePalette(self, nNumEntries));
	/* R */ inline WORD  Count() const assertl_reflect_to(WORD w = 0, GetObject(self, sizeof(WORD), &w), w);
public: // Property - Size
	/* R */ inline size_t Size() const reflect_as(Count() * sizeof(Entry));
#pragma endregion
public:
	using super::operator=;
	inline Entry operator[](size_t ind) const reflect_to(Entry entry; GetEntries((UINT)ind, (Entry *)&entry), entry);
};
using CPalette = RefAs<Palette>;
#pragma endregion

#pragma region Region
enum_class(PolyFills, int,
	Alternate = ALTERNATE,
	Winding   = WINDING);
class BaseOf_GDI(Region, HRGN) {
public:
	using super = GObjectBase<Region, HRGN>;
protected:
	friend class RefAs<Region>;
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
	static inline Region CreateRect(LRect rc) assertl_reflect_as(auto h = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom), h);
	static inline Region CreateElliptic(LRect rc) assertl_reflect_as(auto h = CreateEllipticRgn(rc.left, rc.top, rc.right, rc.bottom), h);
	static inline Region CreateRound(LRect rc, LSize sz) assertl_reflect_as(auto h = CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, sz.cx, sz.cy), h);
	static inline Region CreatePolygon(const POINT *ppt1, int cPoint, PolyFills mode = PolyFills::Winding) assertl_reflect_as(auto h = CreatePolygonRgn(ppt1, cPoint, mode.yield()), h);
	static inline Region CreatePolyPolygon(const POINT *ppt1, int cPoint, PolyFills mode = PolyFills::Winding) assertl_reflect_as(auto h = CreatePolygonRgn(ppt1, cPoint, mode.yield()), h);
public:
	inline bool Equal(HRGN hRgn) reflect_as(EqualRgn(self, hRgn));
	inline bool Has(LPoint pt) reflect_as(PtInRegion(self, pt.x, pt.y));
	inline bool Has(LRect rc) reflect_as(RectInRegion(self, &rc));
public:
	inline void And(HRGN hRgn) { CombineRgn(self, self, hRgn, RGN_AND); }
	inline void And(HRGN hRgn1, HRGN hRgn2) { CombineRgn(self, hRgn1, hRgn2, RGN_AND); }
	inline void Or(HRGN hRgn) { CombineRgn(self, self, hRgn, RGN_OR); }
	inline void Or(HRGN hRgn1, HRGN hRgn2) { CombineRgn(self, hRgn1, hRgn2, RGN_OR); }
	inline void Xor(HRGN hRgn) { CombineRgn(self, self, hRgn, RGN_XOR); }
	inline void Xor(HRGN hRgn1, HRGN hRgn2) { CombineRgn(self, hRgn1, hRgn2, RGN_XOR); }
	inline void Diff(HRGN hRgn) { CombineRgn(self, self, hRgn, RGN_DIFF); }
	inline void Diff(HRGN hRgn1, HRGN hRgn2) { CombineRgn(self, hRgn1, hRgn2, RGN_DIFF); }
	inline void Offset(LPoint off) { OffsetRgn(self, off.x, off.y); }
public:
	inline auto &operator&(HRGN hRgn) reflect_to_self(And(hRgn));
	inline auto &operator|(HRGN hRgn) reflect_to_self(Or(hRgn));
	inline auto &operator^(HRGN hRgn) reflect_to_self(Xor(hRgn));
	inline auto &operator-(HRGN hRgn) reflect_to_self(Diff(hRgn));
};
using CRegion = RefAs<Region>;
#pragma endregion

#pragma region MetaFile
class BaseOf_GDI(MetaFile, HMETAFILE) {
public:
	using super = GObjectBase<MetaFile, HMETAFILE>;
protected:
	friend class RefAs<Region>;
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
			assertl(DeleteMetaFile(self));
		this->hobj = O;
	}
};
using CMetaFile = RefAs<MetaFile>;
#pragma endregion

#pragma region DevCap
enum_class(MapModes, int,
	Text             = MM_TEXT,
	LoMetric         = MM_LOMETRIC,
	HiMetric         = MM_HIMETRIC,
	LoEnglish        = MM_LOENGLISH,
	HiEnglish        = MM_HIENGLISH,
	Twips            = MM_TWIPS,
	Isotropic        = MM_ISOTROPIC,
	Anisotropic      = MM_ANISOTROPIC);
enum_flags(Rop, DWORD,
	SrcCopy              = SRCCOPY,     /* dest = source                   */
	SrcPaint             = SRCPAINT,    /* dest = source OR dest           */
	SrcAnd               = SRCAND,      /* dest = source AND dest          */
	SrcInvert            = SRCINVERT,   /* dest = source XOR dest          */
	SrcErase             = SRCERASE,    /* dest = source AND (NOT dest )   */
	SrcCopyNot           = NOTSRCCOPY,  /* dest = (NOT source)             */
	SrcEraseNot          = NOTSRCERASE, /* dest = (NOT src) AND (NOT dest) */
	MergeCopy            = MERGECOPY,   /* dest = (source AND pattern)     */
	MergePaint           = MERGEPAINT,  /* dest = (NOT source) OR dest     */
	PatCopy              = PATCOPY,     /* dest = pattern                  */
	PatPaint             = PATPAINT,    /* dest = DPSnoo                   */
	PatInvert            = PATINVERT,   /* dest = pattern XOR dest         */
	DstInvert            = DSTINVERT,   /* dest = (NOT dest)               */
	Blackness            = BLACKNESS,   /* dest = BLACK                    */
	Whiteness            = WHITENESS,   /* dest = WHITE                    */
	NoMirrorBitmap       = NOMIRRORBITMAP, /* Do not Mirror the bitmap in this call */
	CaptureBlt           = CAPTUREBLT/* Include layered windows */);
enum_class(Stretches, int,
	And  = BLACKONWHITE,
	Or   = WHITEONBLACK,
	Del  = COLORONCOLOR,
	Half = HALFTONE);
enum_flags(TextAlign, UINT, 
	NoUpDateCP = TA_NOUPDATECP,
	UpDateCP   = TA_UPDATECP,
	Left       = TA_LEFT,
	Right      = TA_RIGHT,
	Center     = TA_CENTER,
	Top        = TA_TOP,
	Bottom     = TA_BOTTOM,
	Baseline   = TA_BASELINE,
	RTLReading = TA_RTLREADING);
class BaseOf_GDI(DevCap, HDC) {
public:
	using super = GObjectBase<DevCap, HDC>;
protected:
	friend class RefAs<DevCap>;
	DevCap(HDC h) : super(h) {}
	DevCap(const DevCap &d) : super(d) {}
public:
	DevCap() {}
	DevCap(Null) {}
	DevCap(DevCap &d) : super(d) {}
	DevCap(DevCap &&d) : super(d) {}
	~DevCap() reflect_to(Delete());
public:
	static inline DevCap CreateCompatible(HDC hdc = O) assertl_reflect_as(auto hobj = CreateCompatibleDC(hdc), hobj);
public:
	inline void Delete() {
		if (self)
			assertl(DeleteDC(self));
		this->hobj = O;
	}
	inline auto Release(HWND hWnd) reflect_as(ReleaseDC(hWnd, self));

//	inline auto &BltStretch(LPoint dstStart, LSize dstSize, Rop rop = Rop::SrcCopy)
	inline auto &BltStretch(LPoint dstStart, LSize dstSize, HDC hdcSrc, LPoint srcStart, LSize srcSize, Rop rop = Rop::SrcCopy) assertl_reflect_as_self(::StretchBlt(self, dstStart.x, dstStart.y, dstSize.cx, dstSize.cy, hdcSrc, srcStart.x, srcStart.y, srcSize.cx, srcSize.cy, rop.yield()));
	inline auto &BltStretch(LRect dst, HDC hdcSrc, LRect src, Rop rop = Rop::SrcCopy) reflect_to_self(BltStretch(dst.left_top(), dst.size(), hdcSrc, src.left_top(), src.size(), rop));
	inline auto &BltBit(LPoint dstStart, LSize dstSize, HDC hdcSrc, LPoint srcStart = 0, Rop rop = Rop::SrcCopy) assertl_reflect_as_self(::BitBlt(self, dstStart.x, dstStart.y, dstSize.cx, dstSize.cy, hdcSrc, srcStart.x, srcStart.y, rop.yield()));
	inline auto &BltBit(LRect rc, HDC hdcSrc, LPoint srcStart = 0, Rop rop = Rop::SrcCopy) reflect_to_self(BltBit(rc.left_top(), rc.size(), hdcSrc, srcStart, rop));

	inline CGObject Select(HGDIOBJ ho) assertl_reflect_as((ho = SelectObject(self, ho)) != HGDI_ERROR, ho);
	inline CPalette Palette(HPALETTE hPal, bool bForceBkgd = false) nt_assertl_reflect_to(hPal = SelectPalette(self, hPal, bForceBkgd), hPal);

	inline auto&DrawIcon(HICON hIcon, LPoint p = 0) assertl_reflect_as_self(::DrawIcon(self, p.x, p.y, hIcon));
//	inline bool DrawText(String text, Rect r = 0) reflect_as(DrawText(self, text.c_str(), text.size(), r, ));
	inline auto&DrawPixel(COLORREF rgb, LPoint p) assertl_reflect_as_self(SetPixel(self, p.x, p.y, rgb) != -1);
	template<size_t len>
	inline auto&DrawPolyline(const LPoint(&pts)[len]) assertl_reflect_as_self(Polyline(self, pts, len));
	inline auto&DrawPie(LRect rc, LPoint start, LPoint end) assertl_reflect_as_self(Pie(self, rc.left, rc.top, rc.right, rc.bottom, start.x, start.y, end.x, end.y));
	inline auto&DrawEllipse(LRect rc) assertl_reflect_as_self(Ellipse(self, rc.left, rc.top, rc.right, rc.bottom));
	inline auto&DrawFocus(LRect rc) assertl_reflect_as_self(DrawFocusRect(self, rc));
	inline auto&Invert(LRect rc) assertl_reflect_as_self(InvertRect(self, rc));
	inline auto&Fill(HBRUSH hbr, LRect rc) assertl_reflect_as_self(FillRect(self, rc, hbr));
	inline auto&Fill(HBRUSH hbr) reflect_as(Fill(hbr, Size()));
#pragma region Properties
public: // Property - PenColor
	/* W */ inline auto    &PenColor(COLORREF rgb) assertl_reflect_as_self(SetDCPenColor(self, rgb));
	/* R */ inline RGBColor PenColor() const reflect_as(GetDCPenColor(self));
public: // Property - BkColor
	/* W */ inline auto    &BkColor(COLORREF rgb) assertl_reflect_as_self(SetBkColor(self, rgb));
	/* R */ inline RGBColor BkColor() const reflect_as(GetBkColor(self));
public: // Property - TextColor
	/* W */ inline auto &TextColor(COLORREF color) reflect_to_self(SetTextColor(self, color));
	/* R */ inline RGBColor TextColor() const reflect_as(GetTextColor(self));
public: // Property - TextAligns
	/* W */ inline auto &TextAligns(TextAlign align) reflect_to_self(SetTextAlign(self, align.yield()));
	/* R */ inline auto  TextAligns() const reflect_as(reuse_as<TextAlign>(GetTextAlign(self)));
public: // Property - ViewOrg
	/* W */ inline auto  &ViewOrg(LPoint pt) assertl_reflect_as_self(SetViewportOrgEx(self, pt.x, pt.y, O));
	/* R */ inline LPoint ViewOrg() const assertl_reflect_to(LPoint pt, GetViewportOrgEx(self, &pt), pt);
public: // Property - ViewExt
	/* W */ inline auto &ViewExt(LSize sz) assertl_reflect_as_self(SetViewportExtEx(self, sz.cx, sz.cy, O));
	/* R */ inline LSize ViewExt() const assertl_reflect_to(LSize sz, GetViewportExtEx(self, &sz), sz);
public: // Property - WindowOrg
	/* W */ inline auto  &WindowOrg(LPoint pt) assertl_reflect_as_self(SetWindowOrgEx(self, pt.x, pt.y, O));
	/* R */ inline LPoint WindowOrg() const assertl_reflect_to(LPoint pt, GetWindowOrgEx(self, &pt), pt);
public: // Property - WindowExt
	/* W */ inline auto &WindowExt(LSize sz) assertl_reflect_as_self(SetWindowExtEx(self, sz.cx, sz.cy, O));
	/* R */ inline LSize WindowExt() const assertl_reflect_to(LSize sz, GetWindowExtEx(self, &sz), sz);
public: // Property - MapMode
	/* W */ inline auto &MapMode(MapModes mode) assertl_reflect_as_self(SetMapMode(self, mode.yield()));
	/* R */ inline auto MapMode() const reflect_as(reuse_as<MapModes>(GetMapMode(self)));
public: // Property - StretchMode
	/* W */ inline auto &StretchMode(Stretches mode) assertl_reflect_as_self(SetStretchBltMode(self, mode.yield()));
	/* R */ inline auto  StretchMode() const assertl_reflect_as(auto mode = GetStretchBltMode(self), reuse_as<Stretches>(mode));
public: // Property - PolyFillMode
	/* W */ inline auto &PolyFill(PolyFills mode) assertl_reflect_as_self(SetPolyFillMode(self, mode.yield()));
	/* W */ inline auto  PolyFill() const reflect_as(reuse_as<PolyFills>(GetPolyFillMode(self)));
public: // Property - Size
	/* R */ inline LSize Size() const reflect_as({ GetDeviceCaps(self, HORZRES), GetDeviceCaps(self, VERTRES) });
public: // Property - PaletteRealize
	/* R */ inline UINT PaletteRealize() const reflect_as(RealizePalette(self));
#pragma endregion
public:
	using super::operator=;
	inline auto&operator()(HGDIOBJ ho) reflect_to_self(Select(ho));
	inline auto&operator()(Bitmap &ho) reflect_to_self(Select(ho));
	inline auto&operator()(const Pen &ho) reflect_to_self(Select(ho));
	inline auto&operator()(const Brush &ho) reflect_to_self(Select(ho));
	inline auto&operator()(const WX::Palette hPal, bool bForceBkgd = false) reflect_to_self(Palette(hPal, bForceBkgd));
};
using CDevCap = RefAs<DevCap>;
using DC = DevCap;
using CDC = RefAs<DevCap>;
#pragma endregion

}
