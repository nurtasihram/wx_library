module;

#define WX_CPPM_GDI
#include "wx_gdi"
#include "wx__gdi.inl"

export module wx.gdi;

import wx.proto;

namespace WX {

export {

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
	INNER_USE(GObjectBase);
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
};
using CGObject = RefAs<GObject>;
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
class BitmapLogic : public RefStruct<BITMAP> {
public:
	using super = RefStruct<BITMAP>;
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
	INNER_USE(Bitmap);
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
using CBitmap = RefAs<Bitmap>;
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
class FontLogicX : public RefStruct<switch_structx(LOGFONT)> {
	using_structx(LOGFONT);
	using TCHAR = XCHAR<IsUnicode>;
	using String = StringBase<TCHAR>;
public:
	using super = RefStruct<LOGFONT>;
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
	INNER_USE(Font);
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
using CFont = RefAs<Font>;
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
class PenLogic : public RefStruct<LOGPEN> {
public:
	using super = RefStruct<LOGPEN>;
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
	INNER_USE(Pen);
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
	INNER_USE(Brush);
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
	static inline Brush CreateSolid(COLORREF rgb)                reflect_as(WX::CreateSolidBrush(rgb));
	static inline Brush CreatePattern(HBITMAP hbm)               reflect_as(WX::CreatePatternBrush(hbm));
	static inline Brush CreateHatch(COLORREF rgb, HatchStyle hs) reflect_as(WX::CreateHatchBrush(hs.yield(), rgb));
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
using CBrush = RefAs<Brush>;
#pragma endregion

#pragma region Palette
class PaletteEntry : public RefStruct<PALETTEENTRY> {
public:
	using super = RefStruct<PALETTEENTRY>;
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
	INNER_USE(Palette);
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
using CPalette = RefAs<Palette>;
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
	INNER_USE(Region);
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
using CRegion = RefAs<Region>;
#pragma endregion

#pragma region MetaFile
class BaseOf_GDI(MetaFile, HMETAFILE) {
public:
	using super = GObjectBase<MetaFile, HMETAFILE>;
protected:
	INNER_USE(Region);
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
using CMetaFile = RefAs<MetaFile>;
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
class ColorAdjustment : public RefStruct<COLORADJUSTMENT> {
public:
	using super = RefStruct<COLORADJUSTMENT>;
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
class RGBIndex : public RefStruct<CIEXYZ> {
public:
	using super = RefStruct<CIEXYZ>;
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
class RGBTriple : public RefStruct<CIEXYZTRIPLE> {
public:
	using super = RefStruct<CIEXYZTRIPLE>;
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
class ColorSpaceX : public RefStruct<std::conditional_t<IsUnicode, LOGCOLORSPACEW, LOGCOLORSPACEA>> {
public:
	using LOGCOLORSPACE = std::conditional_t<IsUnicode, LOGCOLORSPACEW, LOGCOLORSPACEA>;
	using super = RefStruct<LOGCOLORSPACE>;
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

class XForm : public RefStruct<XFORM> {
public:
	using super = RefStruct<XFORM>;
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
	INNER_USE(DevCap);
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

//	inline auto &BltStretch(LPoint dstStart, LSize dstSize, Rop rop = Rop::SrcCopy)
	inline auto &BltStretch(LPoint dstStart, LSize dstSize, HDC hdcSrc, LPoint srcStart, LSize srcSize, Rop rop = Rop::SrcCopy) reflect_to_self(WX::StretchBlt(self, dstStart.x, dstStart.y, dstSize.cx, dstSize.cy, hdcSrc, srcStart.x, srcStart.y, srcSize.cx, srcSize.cy, rop.yield()));
	inline auto &BltStretch(LRect dst, HDC hdcSrc, LRect src, Rop rop = Rop::SrcCopy) reflect_to_self(BltStretch(dst.left_top(), dst.size(), hdcSrc, src.left_top(), src.size(), rop));
	inline auto &BltBit(LPoint dstStart, LSize dstSize, HDC hdcSrc, LPoint srcStart = 0, Rop rop = Rop::SrcCopy) reflect_to_self(WX::BitBlt(self, dstStart.x, dstStart.y, dstSize.cx, dstSize.cy, hdcSrc, srcStart.x, srcStart.y, rop.yield()));
	inline auto &BltBit(LRect rc, HDC hdcSrc, LPoint srcStart = 0, Rop rop = Rop::SrcCopy) reflect_to_self(BltBit(rc.left_top(), rc.size(), hdcSrc, srcStart, rop));

	inline CGObject Select(HGDIOBJ ho) reflect_as(::SelectObject(self, ho));
	inline CPalette Palette(HPALETTE hPal, bool bForceBkgd = false) reflect_to(hPal = WX::SelectPalette(self, hPal, bForceBkgd), hPal);
	inline UINT PaletteRealize() const reflect_as(WX::RealizePalette(self));

	inline void DrawIcon(HICON hIcon, LPoint p = 0) reflect_to(WX::DrawIcon(self, p.x, p.y, hIcon));
	inline int  DrawText(String text, LRect r = 0, TextDraw format = TextDraw::Left) reflect_as(WX::DrawText(self, text, (int)text.Length(), r, format.yield()));
	inline void DrawPixel(COLORREF rgb, LPoint p) reflect_to(WX::SetPixel(self, p.x, p.y, rgb));
	template<size_t len>
	inline void DrawPolyline(const LPoint(&pts)[len]) reflect_to(WX::Polyline(self, (CONST POINT *)&pts, len));
	inline void DrawPie(LRect rc, LPoint start, LPoint end) reflect_to(WX::Pie(self, rc.left, rc.top, rc.right, rc.bottom, start.x, start.y, end.x, end.y));
	inline void DrawEllipse(LRect rc) reflect_to(Ellipse(self, rc.left, rc.top, rc.right, rc.bottom));
	inline void DrawFrame(LRect rc) reflect_to(WX::InvertRect(self, rc));
	inline void Invert(LRect rc) reflect_to(WX::InvertRect(self, rc));
	inline void DrawFocus(HBRUSH hbr, LRect rc) reflect_to(WX::FrameRect(self, &rc, hbr));
	inline void Fill(HBRUSH hbr, LRect rc) reflect_to(WX::FillRect(self, rc, hbr));
	inline void Fill(HBRUSH hbr) reflect_as(Fill(hbr, Size()));

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
		DWORD szBuf = 0;
		WX::GetICMProfile(self, &szBuf, (LPXSTR<IsUnicode>)O);
		auto lpsz = StringX<IsUnicode>::Alloc(szBuf);
		WX::GetICMProfile(self, O, lpsz);
		return{ lpsz, szBuf };
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
using CDevCap = RefAs<DevCap>;
using DC = DevCap;
using CDC = RefAs<DevCap>;
#pragma endregion

}

}
