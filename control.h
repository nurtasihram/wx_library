#pragma once

#include <CommCtrl.h>

#include "./window.h"

namespace WX {

#if 0
#pragma region ImageList
class ImageList : public RefStruct<HIMAGELIST> {
	using super = RefStruct<HIMAGELIST>;
protected:
	friend union RefAs<Bitmap>;
	ImageList(HIMAGELIST h) : super(h) {}
	ImageList(const ImageList &b) : super(b) {}
public:
	ImageList() {}
	ImageList(Null) {}
public:
	~ImageList() reflect_to(Destroy());
public:
	class CreateStruct {
		int cx = 0, cy = 0;
		UINT flags = 0;
		int cInitial = 0;
		int cGrow = 0;
	public:
		CreateStruct(LSize sz) : cx(sz.cx), cy(sz.cy) {}
	public: // Property - Size
		/* W */ inline auto &Size(LSize sz) reflect_to_self(cx = sz.cx, cy = sz.cy);
		/* R */ inline LSize Size() const reflect_as({ cx, cy });
		//	public: // Property - 
	public:
		operator ImageList() const assertl_reflect_as(auto h = ImageList_Create(cx, cy, flags, cInitial, cGrow), h);
	};
	static inline CreateStruct Create(LSize s = 0) reflect_as(s);
	inline void Destroy() {
		if (self) {
			ImageList_Destroy(self);
			(HIMAGELIST &)self = O;
		}
	}
public:
	inline int Add(HBITMAP hbmImage, HBITMAP hbmMask) reflect_as(ImageList_Add(self, hbmImage, hbmMask));
	inline int Add(HICON hicon) reflect_as(ImageList_AddIcon(self, hicon));
	inline int Replace(int i, HICON hicon) reflect_as(ImageList_ReplaceIcon(self, i, hicon));
	inline bool Replace(int i, HBITMAP hbmImage, HBITMAP hbmMask) reflect_as(ImageList_Replace(self, i, hbmImage, hbmMask));
	inline bool Remove(int i) reflect_as(ImageList_Remove(self, i));

	inline bool Overlay(int iImage, int iOverlay) reflect_as(ImageList_SetOverlayImage(self, iImage, iOverlay));

	//inline bool Draw(int i, HDC hdcDst, int x, int y, UINT fStyle) reflect_as(ImageList_Draw(self, i, hdcDst, x, y, fStyle));
	//inline bool ImageList_DrawEx(int i, HDC hdcDst, int x, int y, int dx, int dy, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle);
	//inline bool ImageList_DrawIndirect(IMAGELISTDRAWPARAMS *pimldp);

	///int         WINAPI ImageList_AddMasked(_In_ HIMAGELIST himl, _In_ HBITMAP hbmImage, _In_ COLORREF crMask);
	//HIMAGELIST  WINAPI ImageList_LoadImageA(HINSTANCE hi, LPCSTR lpbmp, int cx, int cGrow, COLORREF crMask, UINT uType, UINT uFlags);
	//HIMAGELIST  WINAPI ImageList_LoadImageW(HINSTANCE hi, LPCWSTR lpbmp, int cx, int cGrow, COLORREF crMask, UINT uType, UINT uFlags);


#define     ImageList_AddIcon(himl, hicon) ImageList_ReplaceIcon(himl, -1, hicon)

public: // Property - Count
	/* W */ inline auto &Count(UINT nNewCount) assertl_reflect_as_self(ImageList_SetImageCount(self, nNewCount));
	/* R */ inline UINT Count() const reflect_as(ImageList_GetImageCount(self));
public: // Property - BkColor
	/* W */ inline auto &BkColor(COLORREF clrBk) reflect_to_self(ImageList_SetBkColor(self, clrBk));
	/* R */ inline auto BkColor() reflect_as(ImageList_GetBkColor(self));
public: // Property - Icon
//	/* R */ inline ::CIcon Icon(int i, UINT flags) reflect_as(ImageList_GetIcon(self, i, flags));
public:
	inline operator HIMAGELIST() const reflect_to_self();
};
#pragma endregion
#endif

#pragma region CommCtl
template<class AnyChild>
class CommCtl : public ChainExtend<CommCtl<AnyChild>, AnyChild>,
	public WindowBase<AnyChild> {
public:
	using super = WindowBase<AnyChild>;
protected:
	SFINAE_Window(AnyChild);
	def_memberof(CtlClassName);
	subtype_branch(xCreate);
public:
	CommCtl() { static_assert(!std::is_void_v<AnyChild>); }
protected:
	static WndProc DefProc;
	struct xClass : super::template ClassBase<xClass> {
		xClass() {
			self->lpszClassName = AnyChild::CtlClassName;
			this->GetInfo();
			self->lpszClassName = AnyChild::_ClassName;
			DefProc = self->lpfnWndProc;
			self->lpfnWndProc = AnyChild::template MainProc<GWLP_USERDATA>;
		}
	};
public:
	template<class _AnyChild, class Style, class StyleEx>
	struct XCreate :
		public WindowBase<AnyChild>::template XCreate<KChain<XCreate<_AnyChild, Style, StyleEx>, _AnyChild>, Style, StyleEx> {
		using super = typename WindowBase<AnyChild>::template XCreate<KChain<XCreate, _AnyChild>, Style, StyleEx>;
		XCreate(CommCtl &ctl) : super(ctl) reflect_to(self->style |= WS_CHILD | WS_VISIBLE);
	};
	inline auto Create() = delete;
	inline auto Create(HWND hParent) {
		super::Register();
		using CreateX = XCreate<void, typename AnyChild::Style, typename AnyChild::StyleEx>;
		return subtype_branchof_xCreate<AnyChild, CreateX>(self).Parent(hParent);
	}
};
template<class AnyChild>
WndProc CommCtl<AnyChild>::DefProc;
#define BaseOf_CommCtl(name) template<class AnyChild> name : public WX::ChainExtend<name<AnyChild>, AnyChild>, public CommCtl<KChain<name<AnyChild>, AnyChild>>
#define SFINAE_CommCtl(name) friend class CommCtl<name>
#pragma endregion

#pragma region Static
template<class AnyChild>
class StaticBase;
using Static = StaticBase<void>;
enum_flags(StaticStyle, WStyle,
	Left            = SS_LEFT,
	Center          = SS_CENTER,
	Right           = SS_RIGHT,
	Icon            = SS_ICON,
	BlackRect       = SS_BLACKRECT,
	GrayRect        = SS_GRAYRECT,
	WhiteRect       = SS_WHITERECT,
	BlackFrame      = SS_BLACKFRAME,
	GrayFrame       = SS_GRAYFRAME,
	WhiteFrame      = SS_WHITEFRAME,
	UserItem        = SS_USERITEM,
	Simple          = SS_SIMPLE,
	LeftNoWordWrap  = SS_LEFTNOWORDWRAP,
	OwnerDraw       = SS_OWNERDRAW,
	Bitmap          = SS_BITMAP,
	EnhMetaFile     = SS_ENHMETAFILE,
	EtchedHorz      = SS_ETCHEDHORZ,
	EtchedVert      = SS_ETCHEDVERT,
	EtchedFrame     = SS_ETCHEDFRAME,
	TypeMask        = SS_TYPEMASK,
	RealSizeControl = SS_REALSIZECONTROL,
	NoPrefix        = SS_NOPREFIX,
	Notify          = SS_NOTIFY,
	CenterImage     = SS_CENTERIMAGE,
	RightJust       = SS_RIGHTJUST,
	RealSizeImage   = SS_REALSIZEIMAGE,
	Sunken          = SS_SUNKEN,
	EditControl     = SS_EDITCONTROL,
	EndEllipsis     = SS_ENDELLIPSIS,
	PathEllipsis    = SS_PATHELLIPSIS,
	WordEllipsis    = SS_WORDELLIPSIS,
	EllipsisMask    = SS_ELLIPSISMASK);
BaseOf_CommCtl(class StaticBase) {
protected:
	SFINAE_CommCtl(StaticBase);
	static constexpr auto CtlClassName = WC_STATIC;
public:
	using Child = KChain<StaticBase<AnyChild>, AnyChild>;
	using super = CommCtl<Child>;
	using Style = StaticStyle;
public:
	StaticBase() {}
#pragma region Properties
public: // Property - Icon
	/* W */ inline auto &Icon(HICON hIcon) reflect_to_child(super::Send(STM_SETICON, hIcon));
	/* R */ inline CIcon Icon() const reflect_as(super::template Send<HICON>(STM_GETICON));
public: // Property - ImageBitmap
	/* W */ inline auto    &ImageBitmap() reflect_to_child(super::Send(STM_SETIMAGE, IMAGE_BITMAP));
	/* R */ inline CBitmap  ImageBitmap() const reflect_as(super::template Send<HBITMAP>(STM_GETIMAGE, IMAGE_BITMAP));
public: // Property - ImageIcon
	/* W */ inline auto &ImageIcon(HICON hIcon) reflect_to_child(super::Send(STM_SETIMAGE, IMAGE_BITMAP));
	/* R */ inline CIcon ImageIcon() const reflect_as(super::template Send<HICON>(STM_GETIMAGE, IMAGE_BITMAP));
public: // Property - ImageCursor
	/* W */ inline auto   &ImageCursor(HCURSOR hCursor) reflect_to_child(super::Send(STM_SETIMAGE, IMAGE_CURSOR, hCursor));
	/* R */ inline CCursor ImageCursor() const reflect_as(super::template Send<HCURSOR>(STM_GETIMAGE, IMAGE_CURSOR));
//public: // Property - EnhMetaFile
//	/* W */ inline auto &EnhMetaFile(HENHMETAFILE hEnhMetaFile) reflect_to_child(super::Send(STM_SETIMAGE, IMAGE_CURSOR, hCursor));
//	/* R */ inline EnhMetaFile() const reflect_as(super::Send<HCURSOR>(STM_GETIMAGE, IMAGE_CURSOR));
//	HENHMETAFILE
#pragma endregion
};
#pragma endregion

#pragma region Button
template<class AnyChild>
class ButtonBase;
using Button = ButtonBase<void>;
enum_flags(ButtonStyle, WStyle,
	PushButton       = BS_PUSHBUTTON,
	DefPushButton    = BS_DEFPUSHBUTTON,
	CheckBox         = BS_CHECKBOX,
	AutoCheckBox     = BS_AUTOCHECKBOX,
	RadioButton      = BS_RADIOBUTTON,
	State3           = BS_3STATE,
	AutoState3       = BS_AUTO3STATE,
	GroupBox         = BS_GROUPBOX,
	UserButton       = BS_USERBUTTON,
	AutoRadioButton  = BS_AUTORADIOBUTTON,
	PushBox          = BS_PUSHBOX,
	OwnerDraw        = BS_OWNERDRAW,
	TypeMask         = BS_TYPEMASK,
	LeftText         = BS_LEFTTEXT,
	Text             = BS_TEXT,
	Icon             = BS_ICON,
	Bitmap           = BS_BITMAP,
	Left             = BS_LEFT,
	Right            = BS_RIGHT,
	Center           = BS_CENTER,
	Top              = BS_TOP,
	Bottom           = BS_BOTTOM,
	VCenter          = BS_VCENTER,
	PushLike         = BS_PUSHLIKE,
	MultiLine        = BS_MULTILINE,
	Notify           = BS_NOTIFY,
	Flat             = BS_FLAT);
enum_flags(ButtonState, SHORT,
	Unchecked     = BST_UNCHECKED,
	Checked       = BST_CHECKED,
	Indeterminate = BST_INDETERMINATE,
	Pushed        = BST_PUSHED,
	Focus         = BST_FOCUS);
class ButtonSplitInfo : public RefStruct<BUTTON_SPLITINFO> {
public:
	ButtonSplitInfo() {}
	ButtonSplitInfo(const BUTTON_SPLITINFO &bs) : RefStruct<BUTTON_SPLITINFO>(bs) {}
public: // mask
	// MKAS BCSIF_GLYPH 
public: // Property - Glyph
//		HIMAGELIST  himlGlyph;
public: // Property - Styles
	enum_flags(Style, UINT,
		NoSplit   = BCSS_NOSPLIT,
		Stretch   = BCSS_STRETCH,
		AlignLeft = BCSS_ALIGNLEFT,
		Image     = BCSS_IMAGE);
	/* W */ inline auto &Styles(Style style) reflect_to_self(self->uSplitStyle = style.yield());
	/* R */ inline Style Styles() const reflect_as(reuse_as<Style>(self->uSplitStyle));
public: // Property - Size
	/* W */ inline auto &Size(SIZE size) reflect_to_self(self->size = size);
	/* R */ inline LSize Size() const reflect_as(reuse_as<LSize>(self->size));
};
class ButtonImageList : public RefStruct<BUTTON_IMAGELIST> {
public:
	ButtonImageList() {}
public: // Property - Margin
	/* W */ inline auto &Margin(LRect margin) reflect_to_self(self->margin = margin);
	/* R */ inline LRect Margin() const reflect_as(self->margin);
public: // Property - Align
	enum_class(Aligns, UINT, 
		Left     = BUTTON_IMAGELIST_ALIGN_LEFT,
		Right    = BUTTON_IMAGELIST_ALIGN_RIGHT,
		Top      = BUTTON_IMAGELIST_ALIGN_TOP,
		Bottom   = BUTTON_IMAGELIST_ALIGN_BOTTOM,
		Center   = BUTTON_IMAGELIST_ALIGN_CENTER);
	/* W */ inline auto   &Align(Aligns align) reflect_to_self(self->uAlign = align.yield());
	/* R */ inline Aligns  Align() const reflect_as(reuse_as<Aligns>(self->uAlign));
public:
	inline BUTTON_IMAGELIST *operator&() reflect_as(self);
	inline const BUTTON_IMAGELIST *operator&() const reflect_as(self);
};
BaseOf_CommCtl(class ButtonBase) {
protected:
	SFINAE_CommCtl(ButtonBase);
	def_memberof(wmailBox);
	static constexpr auto CtlClassName = WC_BUTTON;
public:
	using Child = KChain<ButtonBase<AnyChild>, AnyChild>;
	using super = CommCtl<Child>;
	using Style = ButtonStyle;
	using State = ButtonState;
	using BSplitInfo = ButtonSplitInfo;
	using BImageList = ButtonImageList;
public:
	ButtonBase() {}

#pragma region Callback
protected:
#define MSG_TRANS(msgid, ret, name, ...) \
	def_memberof(name);
#define WX_BUTTON
#include "msg_ctl.inl"
	inline LRESULT Callback(UINT msgid, WPARAM wParam, LPARAM lParam) {
		switch (msgid) {
			case WM_NULL:
				break;
#define _CALL_(name) child.name
#define MSG_TRANS(msgid, ret, name, argslist, args, send, call) \
			case msgid: \
				if constexpr (member_##name##_of<AnyChild>::callable) { \
					using fn_type = ret argslist; \
					misdef_assert(member_##name##_of<AnyChild>:: \
						template compatible_to<fn_type>, \
						"Member " #name " must be a method compatible to " #ret #argslist); \
					return call; \
				} break;
#define WX_BUTTON
#include "msg_ctl.inl"
		}
		if constexpr (member_wmailBox_of<AnyChild>::callable) {
			LRESULT res;
			if (static_cast<AnyChild * >(this)->wmailBox(res, msgid, wParam, lParam))
				return res;
		}
		return super::HandleNext();
	}
#pragma endregion

#pragma region Properties
public: // Property - IdealSize
	/* R */ inline LSize IdealSize() const assertl_reflect_to(LSize sz, Button_GetIdealSize(self, &sz), sz);
public: // Property - Note // style with BS_COMMANDLINK only
	/* W */ inline auto  &Note(LPCTSTR lpszNote) assertl_reflect_as_self(Button_SetNote(self, lpszNote));
	/* R */ inline String Note() const {
		auto len = Button_GetNoteLength(self);
		if (len <= 0) return O;
		String note = len;
		assertl(Button_GetNote(self, note, len + 1));
		return note;
	}
public: // Property - TextMargin
	/* W */ inline auto &TextMargin(RECT margin) assertl_reflect_as_self(Button_SetTextMargin(self, &margin));
	/* R */ inline LRect TextMargin() const assertl_reflect_to(LRect rc, Button_GetTextMargin(self, &rc), rc);
public: // Property - SplitInfo
	/* W */ inline auto      &SplitInfo(BUTTON_SPLITINFO bsp) assertl_reflect_as_self(Button_SetSplitInfo(self, &bsp));
	/* R */ inline BSplitInfo SplitInfo() const assertl_reflect_to(BSplitInfo bsp, Button_GetSplitInfo(self, &bsp), bsp);
public: // Property - ImageList
	/* W */ inline auto      &ImageList(BUTTON_IMAGELIST &iml) assertl_reflect_as_self(Button_SetImageList(self, &iml));
	/* R */ inline BImageList ImageList() const assertl_reflect_to(BImageList iml, Button_GetImageList(self, &iml), iml);
//public: // Property - Image
//	/* W */ inline auto &Image() reflect_to_self(super::Send(BM_SETIMAGE));
//	/* R */ inline auto &Image() const {}
public: // Property - Check
	/* W */ inline auto &Check(State s) reflect_to_self(super::Send(BM_SETCHECK, s.yield()));
	/* R */ inline State Check() const reflect_as(super::template Send<State>(BM_GETCHECK));
public: // Property - States
	/* W */ inline auto &States(State s) reflect_to_self(super::Send(BM_SETSTATE, s.yield()));
	/* R */ inline State States() const reflect_as(super::template Send<State>(BM_GETSTATE));
public: // Property - Styles
	/* W */ inline auto &Styles(Style style, bool bRedraw = true) reflect_to_self(super::Send(BM_SETSTYLE, style.yield(), bRedraw));
public: // Property - DontClick
	/* W */ inline auto &DontClick(bool bDontClick) reflect_to_self(super::Send(BM_SETDONTCLICK, bDontClick));
#pragma endregion
};
#pragma endregion

#pragma region ScrollBar
template<class AnyChild = void>
class ScrollBarBase;
using ScrollBar = ScrollBarBase<>;
enum_flags(ScrollBarStyle, WStyle,
	Horz                    = SBS_HORZ,
	Vert                    = SBS_VERT,
	TopAlign                = SBS_TOPALIGN,
	LeftAlign               = SBS_LEFTALIGN,
	BottomAlign             = SBS_BOTTOMALIGN,
	RightAlign              = SBS_RIGHTALIGN,
	SizeBoxTopLeftAlign     = SBS_SIZEBOXTOPLEFTALIGN,
	SizeBoxBottomRightAlign = SBS_SIZEBOXBOTTOMRIGHTALIGN,
	SizeBox                 = SBS_SIZEBOX,
	SizeGrip                = SBS_SIZEGRIP);
class ScrollInfo : public RefStruct<SCROLLINFO> {
public:
	ScrollInfo() reflect_to(self->cbSize = sizeof(SCROLLINFO));
public:
	//	UINT    fMask;
public: // Property - Range
	//int     nMin;
	//int     nMax;
public: // Property - Page
	//UINT    nPage;
public: // Property - Pos
	//int     nPos;
public: // Property - TrackPos
	//int     nTrackPos;
};
class ScrollBarInfo : public RefStruct<SCROLLBARINFO> {
public:
	ScrollBarInfo() reflect_to(self->cbSize = sizeof(SCROLLBARINFO));
public: // Property - Rect
	/* W */ inline auto &Rect(LRect rc) reflect_to_self(self->rcScrollBar = rc);
	/* R */ inline LRect Rect() const reflect_as(self->rcScrollBar);
public: // Property - LineButton
	/* W */ inline auto &LineButton(int dxyLineButton) reflect_to_self(self->dxyLineButton = dxyLineButton);
	/* R */ inline int   LineButton() const reflect_as(self->dxyLineButton);
public: // Property - ThumbTop
	/* W */ inline auto &ThumbTop(int xyThumbTop) reflect_to_self(self->xyThumbTop = xyThumbTop);
	/* R */ inline int   ThumbTop() const reflect_as(self->xyThumbTop);
public: // Property - ThumbBottom
	/* W */ inline auto &ThumbBottom(int xyThumbBottom) reflect_to_self(self->xyThumbBottom = xyThumbBottom);
	/* R */ inline int   ThumbBottom() const reflect_as(self->xyThumbBottom);
public: // Property - 
	//DWORD rgstate[CCHILDREN_SCROLLBAR + 1];
};
BaseOf_CommCtl(class ScrollBarBase) {
protected:
	SFINAE_CommCtl(ScrollBarBase);
	static constexpr auto CtlClassName = WC_SCROLLBAR;
public:
	using super = CommCtl<KChain<ScrollBarBase<AnyChild>, AnyChild>>;
	using Style = ScrollBarStyle;
	using SInfo = ScrollInfo;
	using SBarInfo = ScrollBarInfo;
public:
	ScrollBarBase() {}

#pragma region Properties
public:
//	ESB_DISABLE_RIGHT
// #define SBM_ENABLE_ARROWS           0x00E4 /*not in win3.1 */
public: // Property - Position
	/* W */ inline auto &Position(int Pos, bool bRedraw = true) reflect_to_child(super::Send(SBM_SETPOS, Pos, bRedraw));
	/* R */ inline int   Position() const reflect_as(super::Send(SBM_GETPOS));
public: // Property - Range
	/* W */ inline auto &Range(int MinPos, int MaxPos, bool bRedraw = true) reflect_to_child(super::Send(bRedraw ? SBM_SETRANGEREDRAW : SBM_SETRANGE, MinPos, MaxPos));
	/* R */ inline auto  Range() const assertl_reflect_to(struct{ _M_(int Min, Max); } rgn, super::Send(SBM_GETRANGE, &rgn.Min, &rgn.Max), rgn);
public: // Property - ScrollInfo
	/* W */ inline auto  &Info(const SInfo &i, bool bRedraw = true) reflect_to_self(super::Send(SBM_SETSCROLLINFO, bRedraw, &i));
	/* R */ inline SInfo  Info() const assertl_reflect_to(SInfo i, super::Send(SBM_GETSCROLLINFO, 0, &i), i);
public:
	/* R */ inline SBarInfo BarInfo() const assertl_reflect_to(SBarInfo i, super::Send(SBM_GETSCROLLBARINFO, 0, &i), i);
#pragma endregion
};
#pragma endregion

#pragma region StatusBar
template<class AnyChild>
class StatusBarBase;
using StatusBar = StatusBarBase<void>;
enum_flags(StatusBarTexts, uint16_t,
	Default      = 0,
	OwnerDraw    = SBT_OWNERDRAW,
	NoBorders    = SBT_NOBORDERS,
	PopOut       = SBT_POPOUT,
	RTLReading   = SBT_RTLREADING,
	NoTabParsing = SBT_NOTABPARSING);
BaseOf_CommCtl(class StatusBarBase) {
protected:
	SFINAE_CommCtl(StatusBarBase);
	static constexpr LPCTSTR CtlClassName = STATUSCLASSNAME;
public:
	using super = CommCtl<KChain<StatusBarBase<AnyChild>, AnyChild>>;
	using Style = WStyle;
	using StyleEx = WStyleEx;
	using Texts = StatusBarTexts;
public:
	StatusBarBase() {}

	inline void FixSize() reflect_to(super::Send(WM_SIZE));

#pragma region Properties
public: // Property - Parts
	template<size_t Len>
	/* W */ inline bool SetParts(const int (&Slice)[Len]) reflect_as(super::Send(SB_SETPARTS, Len, Slice));
	/* W */ inline bool SetParts(const int *pSlices, int Len) reflect_as(super::Send(SB_SETPARTS, Len, pSlices));
	template<size_t Len>
	/* R */ inline bool GetParts(int (&Slice)[Len]) const reflect_as(super::Send(SB_GETPARTS, Len, Slice));
	/* R */ inline bool GetParts(int *pSlices, int Len) const reflect_as(super::Send(SB_GETPARTS, Len, pSlices));
public: // Property - Borders
	/* R */ inline auto Borders() const assertl_reflect_to(struct { int _M_(BorderH, BorderV, GapH); } borders, super::Send(SB_GETBORDERS, 0, &borders), borders);
public: // Property - MinHeight
	/* W */ inline auto&MinHeight(int MinHeight) reflect_to_self(super::Send(SB_SETMINHEIGHT, MinHeight));
public: // Property - Simple
	/* W */ inline auto&Simple(bool bSimple) reflect_to_self(super::Send(SB_SIMPLE, bSimple));
	/* R */ inline bool Simple() const reflect_as(super::Send(SB_SIMPLE));
public: // Property - Rect
	/* W */ inline LRect Rect(uint8_t nPart) assertl_reflect_to(LRect rc, super::Send(SB_GETRECT, nPart, &rc), rc);
public: // Property - Icon
	/* W */ inline auto &Icon(uint8_t nPart, HICON hIcon) reflect_to_self(super::Send(SB_SETICON, nPart, hIcon));
	/* R */ inline CIcon Icon(uint8_t nPart) const reflect_as((HICON)super::Send(SB_GETICON, nPart));
public: // Property - TextLength
	/* R */ inline uint16_t TextLength(uint8_t nPart) const reflect_as(super::template Send<uint16_t>(SB_GETTEXTLENGTH, nPart));
public: // Property - TextStyle
	/* R */ inline Texts    TextStyle(uint8_t nPart) const reflect_as(super::template Send<Texts>(SB_GETTEXTLENGTH, nPart) >> 16);
public: // Property - String
	/* W */ inline bool   Text(uint8_t nPart, LPCTSTR text, Texts style = Texts::Default) reflect_as(super::Send(SB_SETTEXT, nPart | style.yield(), (LPARAM)(LPCTSTR)text));
	/* R */ inline String Text(uint8_t nPart) const {
		auto len = TextLength(nPart);
		if (len <= 0) return O;
		String str = len;
		if (super::Send(SB_GETTEXT, nPart, str))
			return str;
		return O;
	}
public: // Property - TipText
	/* W */ inline auto  &TipText(WORD id, LPCTSTR tip) reflect_to_self(super::Send(SB_SETTIPTEXT, id, (LPARAM)(LPCTSTR)tip));
	/* R */ inline String TipText(WORD id) const {
		String str = MaxLenNotice;
		if (super::Send(SB_GETTIPTEXT, MAKEWPARAM(id, MaxLenNotice + 1), str))
			return str.Trunc();
		return O;
	}
public: // Property - UnicodeFormat
	/* W */ inline auto &UnicodeFormat(bool bUnicode) reflect_to_self(super::Send(SB_SETUNICODEFORMAT, bUnicode));
	/* R */ inline bool  UnicodeFormat() const reflect_as(super::Send(SB_GETUNICODEFORMAT));
public: // Property - BkColor
	/* R */ inline RGBColor BkColor() const reflect_as(super::template Send<RGBColor>(SB_SETBKCOLOR));
#pragma endregion
};
#pragma endregion

#pragma region ToolBar
enum_flags(ToolBarStyle, WStyle,
	Button          = TBSTYLE_BUTTON,
	Sep             = TBSTYLE_SEP,
	Check           = TBSTYLE_CHECK,
	Group           = TBSTYLE_GROUP,
	DropDown        = TBSTYLE_DROPDOWN,
	AutoSize        = TBSTYLE_AUTOSIZE,
	NoPrefix        = TBSTYLE_NOPREFIX,
	ToolTips        = TBSTYLE_TOOLTIPS,
	Wrapable        = TBSTYLE_WRAPABLE,
	AltDrag         = TBSTYLE_ALTDRAG,
	Flat            = TBSTYLE_FLAT,
	List            = TBSTYLE_LIST,
	CustomErase     = TBSTYLE_CUSTOMERASE,
	RegisterDrop    = TBSTYLE_REGISTERDROP,
	Transparent     = TBSTYLE_TRANSPARENT,
	enum_complex CheckGroup = TBSTYLE_CHECKGROUP);
enum_flags(ToolBarStyleEx, WStyleEx,
	DrawDDArrows              = TBSTYLE_EX_DRAWDDARROWS,
	MultiColumn               = TBSTYLE_EX_MULTICOLUMN,
	Vertical                  = TBSTYLE_EX_VERTICAL,
	MixedButtons              = TBSTYLE_EX_MIXEDBUTTONS,
	DoubleBuffer              = TBSTYLE_EX_DOUBLEBUFFER,
	HideClippedButtons        = TBSTYLE_EX_HIDECLIPPEDBUTTONS);
enum_flags(ToolBarState, BYTE,
	Checked         = TBSTATE_CHECKED,
	Pressed         = TBSTATE_PRESSED,
	Enabled         = TBSTATE_ENABLED,
	Hidden          = TBSTATE_HIDDEN,
	Indeterminate   = TBSTATE_INDETERMINATE,
	Wrap            = TBSTATE_WRAP,
	Ellipses        = TBSTATE_ELLIPSES,
	Marked          = TBSTATE_MARKED);
enum_flags(ToolBarButtonStyle, BYTE,
	Button          = BTNS_BUTTON,
	Sep             = BTNS_SEP,
	Check           = BTNS_CHECK,
	Group           = BTNS_GROUP,
	CheckGroup      = BTNS_CHECKGROUP,
	DropDown        = BTNS_DROPDOWN,
	AutoSize        = BTNS_AUTOSIZE,
	NoPrefix        = BTNS_NOPREFIX,
	ShowText        = BTNS_SHOWTEXT,
	WholeDropDown   = BTNS_WHOLEDROPDOWN);
struct ToolBarButton : public RefStruct<TBBUTTON> {
public:
	ToolBarButton() {}
	ToolBarButton(const TBBUTTON &t) : RefStruct<TBBUTTON>(t) {}
public: // Property - BitmapIndex
	/* W */ inline auto &BitmapIndex(int iBitmap) reflect_to_self(self->iBitmap = iBitmap);
	/* R */ inline int BitmapIndex() const reflect_as(self->iBitmap);
public: // Property - ID
	/* W */ inline auto &ID(int idCommand) reflect_to_self(self->idCommand = idCommand);
	/* R */ inline int ID() const reflect_as(self->idCommand);
public: // Property - States
	/* W */ inline auto &States(ToolBarState tbs) reflect_to_self(self->fsState = tbs.yield());
	/* R */ inline ToolBarState States() const reflect_as(force_cast<ToolBarState>(self->fsState));
public: // Property - Styles
	/* W */ inline auto &Styles(ToolBarButtonStyle tbbs) reflect_to_self(self->fsStyle = tbbs.yield());
	/* R */ inline ToolBarButtonStyle Styles() const reflect_as(force_cast<ToolBarButtonStyle>(self->fsStyle));
public: // Property - Data
	template<class AnyType>
	/* W */ inline auto &Data(AnyType *ptr) reflect_to_self(self->dwData = (DWORD_PTR)ptr);
	template<class AnyType>
	/* R */ inline AnyType *Data() reflect_as(force_cast<AnyType *>(self->dwData));
	template<class AnyType>
	/* R */ inline const AnyType *Data() const reflect_as(force_cast<const AnyType *>(self->dwData));
public: // Property - String
	/* W */ inline auto &String(INT_PTR iString) reflect_to_self(self->iString = iString);
	/* W */ inline auto &String(LPCTSTR lpString) reflect_to_self(self->iString = (INT_PTR)lpString);
	/* R */ inline INT_PTR StringIndex() const reflect_as(self->iString);
	/* R */ inline const WX::String String() const reflect_as(CString((LPCTSTR)self->iString, MaxLenNotice));
};
template<class AnyChild = void>
class ToolBarBase;
using ToolBar = ToolBarBase<>;
BaseOf_CommCtl(class ToolBarBase) {
protected:
	SFINAE_CommCtl(ToolBarBase);
	static constexpr LPCTSTR CtlClassName = TOOLBARCLASSNAME;
public:
	using super = CommCtl<KChain<ToolBarBase<AnyChild>, AnyChild>>;
	using Style = ToolBarStyle;
	using StyleEx = ToolBarStyleEx;
	using Button = ToolBarButton;
	class IButton {
		ToolBarBase &tb;
		int idCommand;
	public:
		IButton(ToolBarBase &tb, int idCommand) : tb(tb), idCommand(idCommand) {}
	public: // Property - Enable
		/* W */ inline auto&Enable(bool bEnable) assertl_reflect_as_self(tb.Send(TB_ENABLEBUTTON, idCommand, bEnable));
		/* R */ inline bool Enable() const reflect_as(tb.Send(TB_ISBUTTONENABLED, idCommand));
	public: // Property - Check
		/* W */ inline auto&Check(bool bCheck) assertl_reflect_as_self(tb.Send(TB_CHECKBUTTON, idCommand, bCheck));
		/* R */ inline bool Check() const reflect_as(tb.Send(TB_ISBUTTONCHECKED, idCommand));
	public: // Property - Press
		/* W */ inline auto&Press(bool bPress) assertl_reflect_as_self(tb.Send(TB_PRESSBUTTON, idCommand, bPress));
		/* R */ inline bool Press() const reflect_as(tb.Send(TB_ISBUTTONPRESSED, idCommand));
	public: // Property - Hide
		/* W */ inline auto&Hide(bool bPress) assertl_reflect_as_self(tb.Send(TB_HIDEBUTTON, idCommand, bPress));
		/* R */ inline bool Hide() const reflect_as(tb.Send(TB_ISBUTTONHIDDEN, idCommand));
	public: // Property - HighLighted
		/* R */ inline bool HighLighted() const reflect_as(tb.Send(TB_ISBUTTONHIGHLIGHTED, idCommand));
	public: // Property - Indeterminate
		/* W */ inline auto&Indeterminate(bool bEnable) assertl_reflect_as_self(tb.Send(TB_INDETERMINATE, idCommand, bEnable));
		/* R */ inline bool Indeterminate() const reflect_as(tb.Send(TB_ISBUTTONINDETERMINATE, idCommand));
	public: // Property - Text
		/* R */ inline String Text() const {
			auto len = tb.Send<size_t>(TB_GETBUTTONTEXT, idCommand);
			String text(len);
			tb.Send<size_t>(TB_GETBUTTONTEXT, idCommand, (LPTSTR)text);
			return text;
		}
	public: // Property - Mark
		/* W */ inline auto&Mark(bool bMark) assertl_reflect_as_self(tb.Send(TB_MARKBUTTON, idCommand, bMark));
	public: // Property - Index
		/* R */ inline int Index() assertl_reflect_to(int index, (index = tb.Send(TB_COMMANDTOINDEX, idCommand)) > 0, index);
	public: // Property - ID
		inline auto &ID(int idCommand) {
			assertl(Send(TB_SETCMDID, this->idCommand, idCommand));
			this->idCommand = idCommand;
			retself;
		}
		inline int ID() const reflect_as(idCommand);
	public: // Property - 
	public:
		inline void Delete() assertl_reflect_as_self(tb.Send(TB_DELETEBUTTON, idCommand));

	};
public:
	ToolBarBase() {}
//#define TB_SETSTATE             (WM_USER + 17)
//#define TB_GETSTATE             (WM_USER + 18)
//#define TB_ADDBITMAP            (WM_USER + 19)

	template<size_t nCount>
	inline auto &Add(const Button(&buttons)[nCount]) assertl_reflect_as(super::Send(TB_ADDBUTTONS, nCount, buttons));
	inline auto &Add(std::initializer_list<Button> buttons) assertl_reflect_as(super::Send(TB_ADDBUTTONS, buttons.size(), buttons.begin()));
	inline auto &Add(LPCTBBUTTON lpButtons, UINT nCount) assertl_reflect_as(super::Send(TB_ADDBUTTONS, nCount, lpButtons));
	inline auto &Add(const Button *lpButtons, UINT nCount) assertl_reflect_as(super::Send(TB_ADDBUTTONS, nCount, lpButtons));
	inline auto &Add(const TBBUTTON &button) assertl_reflect_as(super::Send(TB_ADDBUTTONS, 1, &button));
	inline auto &Add(const Button &button) assertl_reflect_as(super::Send(TB_ADDBUTTONS, 1, &button));
	inline auto &Insert(const Button &button, int idBefore) assertl_reflect_as(super::Send(TB_INSERTBUTTON, idBefore, &button));
//	inline Button Get(int id) assertl_reflect_as(Send(TB_GETBUTTON, ));

#define TB_GETBUTTON            (WM_USER + 23)

public: // Property - Count
	/* R */ inline UINT Count() const reflect_as(super::Send(TB_BUTTONCOUNT));
};
#pragma endregion

#pragma region ListView
enum_flags(ListViewStyle, WStyle,
	Icon                = LVS_ICON,
	Report              = LVS_REPORT,
	SmallIcon           = LVS_SMALLICON,
	List                = LVS_LIST,
	TypeMask            = LVS_TYPEMASK,
	SingleSel           = LVS_SINGLESEL,
	ShowSelAlways       = LVS_SHOWSELALWAYS,
	SortAscending       = LVS_SORTASCENDING,
	SortDescending      = LVS_SORTDESCENDING,
	ShareImageLists     = LVS_SHAREIMAGELISTS,
	NoLabelWrap         = LVS_NOLABELWRAP,
	AutoArrange         = LVS_AUTOARRANGE,
	EditLabels          = LVS_EDITLABELS,
	OwnerData           = LVS_OWNERDATA,
	NoScroll            = LVS_NOSCROLL,
	TypeStyleMask       = LVS_TYPESTYLEMASK,
	AlignTop            = LVS_ALIGNTOP,
	AlignLeft           = LVS_ALIGNLEFT,
	AlignMask           = LVS_ALIGNMASK,
	OwnerDrawFixed      = LVS_OWNERDRAWFIXED,
	NoColumnHeader      = LVS_NOCOLUMNHEADER,
	NoSortHeader        = LVS_NOSORTHEADER);
struct ListViewIndex : LVFINDINFO {
	UINT flags;
	LPCSTR psz;
	LPARAM lParam;
	POINT pt;
	UINT vkDirection;
};
struct ListViewItem : public RefStruct<LVITEM> {
public:
	ListViewItem() {}
	ListViewItem(const LVITEM &lvi) : RefStruct<LVITEM>(lvi) {}
public: // mask;
public: // iItem;
public: // iSubItem;
public: // state;
public: // stateMask;
public: // pszText; cchTextMax;
public: // iImage;
public: // lParam;
public: // iIndent;
public: // iGroupId;
public: // cColumns; // tile view columns
public: // puColumns;
public: // piColFmt;
public: // iGroup; RO
};
struct ListViewColumn : public RefStruct<LVCOLUMNW> {
public:
	ListViewColumn() {}
	ListViewColumn(const LVCOLUMNW &lvc) : RefStruct<LVCOLUMNW>(lvc) {}
public: // mask;
public: // fmt;
public: // cx;
public: // pszText; cchTextMax;
public: // iSubItem;
public: // iImage;
public: // iOrder;
public: // cxMin; // min snap point
public: // cxDefault; // default snap point
public: // cxIdeal; // read only. ideal may not eqaul current width if auto sized (LVS_EX_AUTOSIZECOLUMNS) to a lesser width.
};
template<class AnyChild>
class ListViewBase;
using ListView = ListViewBase<void>;
BaseOf_CommCtl(class ListViewBase) {
	protected:
	SFINAE_CommCtl(ListViewBase);
	def_memberof(wmailBox);
	static constexpr auto CtlClassName = WC_LISTVIEW;
public:
	using super = CommCtl<KChain<ListViewBase<AnyChild>, AnyChild>>;
	using Style = ListViewStyle;
public:
	ListViewBase() {}

//#pragma region Callback
//protected:
//#define MSG_TRANS(msgid, ret, name, ...) \
//	def_memberof(name);
//#define WX_BUTTON
//#include "msg_ctl.inl"
//	inline LRESULT Callback(UINT msgid, WPARAM wParam, LPARAM lParam) {
//		switch (msgid) {
//			case WM_NULL:
//				break;
//#define _CALL_(name) child.name
//#define MSG_TRANS(msgid, ret, name, argslist, args, send, call) \
//			case msgid: \
//				if constexpr (member_##name##_of<AnyChild>::callable) { \
//					using fn_type = ret argslist; \
//					misdef_assert(member_##name##_of<AnyChild>:: \
//						template compatible_to<fn_type>, \
//						"Member " #name " must be a method compatible to " #ret #argslist); \
//					return call; \
//				} break;
//#define WX_LISTVIEW
//#include "msg_ctl.inl"
//		}
//		if constexpr (member_wmailBox_of<AnyChild>::callable) {
//			LRESULT res;
//			if (static_cast<AnyChild * >(this)->wmailBox(res, msgid, wParam, lParam))
//				return res;
//		}
//		return super::HandleNext();
//	}
//#pragma endregion

public:

	inline void InsertItem(const ListViewItem &lvi) assertl_reflect_as(ListView_InsertItem(self, &lvi));
	inline void DeleteItem(int i) assertl_reflect_as(ListView_DeleteItem(self, i));
	inline void DeleteAllItem()  assertl_reflect_as(ListView_DeleteAllItems(self));

#pragma region Properties
public: // Property - UnicodeFormat
	/* W */ inline bool UnicodeFormat() const reflect_as(ListView_GetUnicodeFormat(self));
	/* R */ inline auto &UnicodeFormat(bool bUnicode) assertl_reflect_as_self(ListView_SetUnicodeFormat(self, bUnicode));
public: // Property - BkColor
	/* W */ inline auto &BkColor(DWORD rgb) assertl_reflect_as_self(ListView_SetBkColor(self, rgb));
	/* R */ inline bool BkColor() const reflect_as(ListView_GetBkColor(self));
public: // Property - ImageList
public: // Property - ItemCount
	/* R */ inline auto ItemCount() const reflect_as(ListView_GetItemCount(self));
public: // Property - Item
	/* W */ inline auto &Item(const ListViewItem &lvi) assertl_reflect_as_self(ListView_SetItem(self, &lvi));
	/* R */ inline auto Item() const assertl_reflect_to(ListViewItem lvi, ListView_GetItem(self, &lvi), lvi);
#pragma endregion
};
#pragma endregion

#if 0
#pragma region ToolTip
template<class AnyChild = void>
class ToolTipCtl;
enum_flags(ToolTipStyle, WStyle,
	AlwaysTip           = TTS_ALWAYSTIP,
	NoPrefix            = TTS_NOPREFIX,
	NoAnimate           = TTS_NOANIMATE,
	NoFade              = TTS_NOFADE,
	Balloon             = TTS_BALLOON,
	Close               = TTS_CLOSE,
	UseVisualStyle      = TTS_USEVISUALSTYLE);
struct ToolTipInfo : protected TTTOOLINFO {
	ToolTipInfo() : TTTOOLINFO{ 0 } { this->cbSize = sizeof(TTTOOLINFO); }
};
using ToolTip = ToolTipCtl<>;
BaseOf_CommCtl(class ToolTipCtl) {
public:
	static constexpr auto CtlClassName = TOOLTIPS_CLASS;
	using super = CommCtl<KChain<ToolTipCtl<AnyChild>, AnyChild>>;

	ToolTipCtl() {}

	using Style = ToolTipStyle;
	using CInfo = ToolTipInfo;

#pragma region Methods
	inline auto&Activate(bool bActivate = false) reflect_to_child(super::Send(TTM_ACTIVATE, bActivate));
	inline bool Add(const CInfo &i) reflect_as(super::Send(TTM_ADDTOOL, 0, &i));
	inline void Del(const CInfo &i) { super::Send(TTM_DELTOOL, 0, &i); }
	inline void UpdateTip(const CInfo &i) { super::Send(TTM_UPDATETIPTEXT, 0, &i); }
	//inline CInfo HitTest(HWND hwnd, POINT pt) {
	//	TTHITTESTINFO tti = { 0 };
	//	tti.hwnd = hwnd, tti.pt = pt;
	//	if (super::Send(TTM_HITTEST))
	//		return tti.ti;
	//	return {};
	//}
//#define TTM_ENUMTOOLSW          (WM_USER +58)
//#define TTM_NEWTOOLRECTA        (WM_USER + 6)
//#define TTM_RELAYEVENT          (WM_USER + 7) // Win7: wParam = GetMessageExtraInfo() when relaying WM_MOUSEMOVE
//#define TTM_POP                 (WM_USER + 28)
//#define TTM_POPUP               (WM_USER + 34)
//#define TTM_UPDATE              (WM_USER + 29)
//#define TTM_ADJUSTRECT          (WM_USER + 31)
//#define TTM_WINDOWFROMPOINT     (WM_USER + 16)
//#define TTM_TRACKACTIVATE       (WM_USER + 17)  // wParam = TRUE/FALSE start end  lparam = LPTOOLINFO
//#define TTM_TRACKPOSITION       (WM_USER + 18)  // lParam = dwPos
#pragma endregion

#pragma region Properties
//public: // Property - Info
//	/* W */ inline auto &Info(CInfo i) { super::Send(TTM_SETTOOLINFO, 0, &i); retchild; }
//	/* R */ inline CInfo Info() const {
//		CInfo i;
//		super::Send(TTM_GETTOOLINFO);
//		return i;
//	}
//public: // Property - String
//	/* R */ inline String Text() const {
//		String str;
//		super::Send(TTM_GETTEXT, str);
//		return str;
//	}
//public: // Property - ToolCount
//	/* R */ inline int ToolCount() const reflect_as(super::Send(TTM_GETTOOLCOUNT));
//public: // Property - CurrentTool
//	/* R */ inline CInfo CurrentTool() const { CInfo i; assertl(super::Send(TTM_GETCURRENTTOOL, 0, &i)); return i; }
//public: // Property - DelayTime
//	/* W */ inline auto &DelayTime(CInfo i) { super::Send(TTM_SETDELAYTIME); retchild; }
//	/* R */ inline CInfo DelayTime() const { CInfo i; super::Send(TTM_GETDELAYTIME); return i; }
//public: // Property - TipBkColor
//	/* W */ inline auto    &TipBkColor(RGBColor rgb) { super::Send(TTM_SETTIPBKCOLOR); retchild; }
//	/* R */ inline RGBColor TipBkColor() const reflect_as(super::Send(TTM_GETTIPBKCOLOR));
//public: // Property - TipTextColor
//	/* W */ inline auto &TipTextColor(int width) { super::Send(TTM_SETTIPTEXTCOLOR); retchild; }
//	/* R */ inline int   TipTextColor() const reflect_as(super::Send(TTM_GETTIPTEXTCOLOR));
//public: // Property - MaxTipWidth
//	/* W */ inline auto &MaxTipWidth(int width) { super::Send(TTM_SETMAXTIPWIDTH); retchild; }
//	/* R */ inline int   MaxTipWidth() const reflect_as(super::Send(TTM_GETMAXTIPWIDTH));
//public: // Property - Margin
//	/* W */ inline auto &Margin(int width) { super::Send(TTM_SETMARGIN); retchild; }
//	/* R */ inline int   Margin() const reflect_as(super::Send(TTM_GETMARGIN));
//public: // Property - Title
//	/* W */ inline auto &Title(LPCTSTR lpString) { super::Send(TTM_SETTITLE); retchild; }
//	/* R */ inline int   Title() const {
//		super::Send(TTM_GETTITLE);
//	}
//public: // Property - BubbleSize
//	/* R */ inline int BubbleSize() const { super::Send(TTM_GETBUBBLESIZE); }
//public: // Property - WindowThem
//	/* W */ inline auto &WindowTheme() { super::Send(TTM_SETWINDOWTHEME); retchild; }
#pragma endregion
};
#pragma endregion

#pragma region ReBar
struct ColorScheme : protected COLORSCHEME {
	ColorScheme() : COLORSCHEME{ 0 } { this->dwSize = sizeof(self); }
public: // Property - Highlight
	/* W */ inline auto &Highlight(COLORREF cr) reflect_to_self(this->clrBtnHighlight = clrBtnHighlight);
	/* R */ inline RGBColor Highlight() const reflect_as(this->clrBtnHighlight);
public: // Property - Shadow
	/* W */ inline auto &Shadow(COLORREF cr) reflect_to_self(this->clrBtnShadow = clrBtnShadow);
	/* R */ inline RGBColor Shadow() const reflect_as(this->clrBtnShadow);
public:
	inline operator COLORSCHEME&() reflect_to_self();
	inline operator const COLORSCHEME &() const reflect_to_self();
	inline LPCOLORSCHEME operator&() reflect_as(this);
	inline const COLORSCHEME *operator&() const reflect_as(this);
};
template<class AnyChild>
class ReBarCtl;
using ReBar = ReBarCtl<void>;
enum_flags(ReBarBandStyle, UINT,
	Break          = RBBS_BREAK,
	FixedSize      = RBBS_FIXEDSIZE,
	ChildEdge      = RBBS_CHILDEDGE,
	Hidden         = RBBS_HIDDEN,
	NoVert         = RBBS_NOVERT,
	FixedBmp       = RBBS_FIXEDBMP,
	VariableHeight = RBBS_VARIABLEHEIGHT,
	GripperAlways  = RBBS_GRIPPERALWAYS,
	NoGripper      = RBBS_NOGRIPPER,
	UseChevron     = RBBS_USECHEVRON,
	HideTitle      = RBBS_HIDETITLE,
	TopAlign       = RBBS_TOPALIGN);
struct ReBarBandInfo : protected REBARBANDINFO {
	ReBarBandInfo() : REBARBANDINFO{ 0 } { this->cbSize = sizeof(REBARBANDINFO); }
	using Style = ReBarBandStyle;
public:
	UINT        fMask;
public: // Property - Styles
	/* W */ inline auto &Styles(Style style) reflect_to_self(this->fStyle = style.yield());
	/* R */ inline Style Styles() const reflect_as(force_cast<Style>(this->fStyle));
public: // Property - Foreground
	/* W */ inline auto    &Foreground(COLORREF clrFore) reflect_to_self(this->clrFore = clrFore);
	/* R */ inline RGBColor Foreground() const reflect_as(this->clrFore);
public: // Property - Background
	/* W */ inline auto    &Background(COLORREF clrBack) reflect_to_self(this->clrBack = clrBack);
	/* R */ inline RGBColor Background() const reflect_as(this->clrBack);
//public: // Property - Text
//	LPWSTR      lpText;
//	UINT        cch;
public:
	int         iImage;
public: // Property - Child
	/* W */ inline auto  &Child(HWND hwndChild) reflect_to_self(this->hwndChild = hwndChild);
	/* R */ inline Window Child() const reflect_as(this->hwndChild);
public:
	UINT        cxMinChild;
	UINT        cyMinChild;
	UINT        cx;
	HBITMAP     hbmBack;
	UINT        wID;
	UINT        cyChild;
	UINT        cyMaxChild;
	UINT        cyIntegral;
	UINT        cxIdeal;
	LPARAM      lParam;
	UINT        cxHeader;
	RECT        rcChevronLocation;    // the rect is in client co-ord wrt hwndChild
	UINT        uChevronState; // STATE_SYSTEM_*
public:
	inline operator REBARBANDINFO &() reflect_to_self();
	inline operator const REBARBANDINFO &() const reflect_to_self();
	inline REBARBANDINFO *operator&() reflect_as(this);
	inline const REBARBANDINFO *operator&() const reflect_as(this);
};
enum_flags(ReBarStyle, WStyle,
	ToolTips                  = RBS_TOOLTIPS,
	VarHeight                 = RBS_VARHEIGHT,
	BandBorders               = RBS_BANDBORDERS,
	FixedOrder                = RBS_FIXEDORDER,
	RegisterDrop              = RBS_REGISTERDROP,
	AutoSize                  = RBS_AUTOSIZE,
	VerticalGripper           = RBS_VERTICALGRIPPER,
	DblClkToggle              = RBS_DBLCLKTOGGLE);
BaseOf_CommCtl(class ReBarCtl) {
public:
	static constexpr auto CtlClassName = REBARCLASSNAME;
	using super = CommCtl<KChain<ReBarCtl<AnyChild>, AnyChild>>;

	ReBarCtl() {}

	using Style = ReBarStyle;
	using BandInfo = ReBarBandInfo;

#define RB_INSERTBAND  (WM_USER +  1)

#define RB_MOVEBAND     (WM_USER + 39)

#define RB_SIZETORECT   (WM_USER +  23) // resize the rebar/break bands and such to this rect (lparam)
#define RB_BEGINDRAG    (WM_USER + 24)
#define RB_ENDDRAG      (WM_USER + 25)
#define RB_DRAGMOVE     (WM_USER + 26)

#define RB_IDTOINDEX    (WM_USER +  16) // wParam == id

#define RB_PUSHCHEVRON      (WM_USER + 43)

#define RB_HITTEST      (WM_USER +  8)

public: // Property - BandCount
	/* R */ inline UINT  BandCount() const reflect_as(super::template Send<UINT>(RB_GETBANDCOUNT));

#pragma region Band
	inline void  BandDelete(UINT ind) assertl_reflect_as_self(super::Send(RB_DELETEBAND, ind));
	inline auto &BandMinimize(UINT ind) reflect_to_child(super::Send(RB_MINIMIZEBAND, ind));
	inline auto &BandMaximize(UINT ind) reflect_to_child(super::Send(RB_MAXIMIZEBAND, ind));
public: // Property - BandVisible
	/* R */ inline auto &BandVisible(UINT ind, bool bVisible) assertl_reflect_as_self(super::template Send<bool>(RB_SHOWBAND, ind, bVisible));
//public: // Property - BandInfo
//	/* W */ inline bool  BandInfo(UINT ind); // RB_SETBANDINFO
//	/* R */ inline bool  BandInfo(UINT ind) const; // RB_GETBANDINFO
public: // Property - BandBorders
	/* R */ inline LRect BandBorders(UINT ind) const reflect_to(LRect rc; super::Send(RB_GETBANDBORDERS, ind, &rc), rc);
public: // Property - BandMargins
	/* R */ inline LRect BandMargins(UINT ind) const reflect_to(LRect rc; super::Send(RB_GETBANDMARGINS, ind, &rc), rc);
public: // Property - BandWidth
	/* W */ inline auto &BandWidth(UINT ind, UINT width) assertl_reflect_as_self(super::template Send<bool>(RB_SETBANDWIDTH, ind, width));
public: // Property - BandRect
	/* R */ inline bool  BandRect(UINT ind) const assertl_reflect_to(LRect rc, super::template Send<bool>(RB_GETRECT, ind, &rc), rc);
public: // Property - BandRowHeight
	/* R */ inline UINT  BandRowHeight(UINT ind) const reflect_as(super::template Send<UINT>(RB_GETROWHEIGHT, ind));
#pragma endregion

#pragma region Properties
//public: // Property - 
//	/* W */ inline auto &Info(); // RB_GETBARINFO
//	/* R */ inline bool  Info() const; // RB_SETBARINFO
public: // Property - Parent
	/* R */ inline auto &Parent(HWND hParent) const reflect_to_child(super::Send(RB_SETPARENT, hParent));
public: // Property - RowCount
	/* R */ inline UINT  RowCount() const reflect_as(super::template Send<UINT>(RB_GETROWCOUNT));
public: // Property - ToolTips
//	/* W */ inline auto   &ToolTips() reflect_as(super::Send(RB_SETTOOLTIPS));
	/* R */ inline ToolTip ToolTips() const reflect_as(super::template Send<HWND>(RB_GETTOOLTIPS));
public: // Property - BkColor
	/* W */ inline auto    &BkColor(COLORREF cr) reflect_to_child(super::Send(RB_SETBKCOLOR, 0, cr));
	/* R */ inline COLORREF BkColor() const reflect_as(super::template Send<COLORREF>(RB_GETBKCOLOR));
public: // Property - TextColor
	/* W */ inline auto    &TextColor(COLORREF cr) reflect_to_child(super::Send(RB_SETTEXTCOLOR, 0, cr));
	/* R */ inline COLORREF TextColor() const reflect_as(super::template Send<COLORREF>(RB_GETTEXTCOLOR));
public: // Property - BarHeight
	/* R */ inline UINT  BarHeight() const reflect_as(super::template Send<UINT>(RB_GETBARHEIGHT));
public: // Property - Palette
	/* W */ inline auto    &Palette(HPALETTE hPal) reflect_to_child(super::Send(RB_SETPALETTE, 0, hPal));
	/* R */ inline CPalette Palette() const reflect_as(super::template Send<HPALETTE>(RB_GETPALETTE));
public: // Property - ColorScheme
	/* W */ inline auto &ColorScheme(COLORSCHEME cs) reflect_to_child(super::Send(RB_SETCOLORSCHEME, 0, &cs));
	/* R */ inline ::ColorScheme ColorScheme() const assertl_reflect_to(::ColorScheme cs, super::template Send<bool>(RB_GETCOLORSCHEME, 0, &cs), cs);
//public: // Property - DropTarget
//	/* R */ inline auto DropTarget(IDropTarget); // RB_GETDROPTARGET
public: // Property - UnicodeFormat
	/* W */ inline auto &UnicodeFormat(bool bUnicode) reflect_to_child(Send(RB_SETUNICODEFORMAT, bUnicode));
	/* R */ inline bool  UnicodeFormat() const assertl_reflect_as(Send<bool>(RB_SETUNICODEFORMAT));
//public: // Property - WindowTheme
//	/* W */ inline auto &WindowTheme(); // RB_SETWINDOWTHEME
#pragma endregion
};
#pragma endregion
#endif

enum_flags(ToolTipIcons, INT,
	None  = TTI_NONE,
	Info  = TTI_INFO,
	Warn  = TTI_WARNING,
	Error = TTI_ERROR,
	InfoLarge  = TTI_INFO_LARGE,
	WarnLarge  = TTI_WARNING_LARGE,
	ErrorLarge = TTI_ERROR_LARGE);

#pragma region Edit
template<class AnyChild = void>
class EditBase;
using Edit = EditBase<>;
enum_flags(EditStyle, WStyle,
	Left        = ES_LEFT,
	Center      = ES_CENTER,
	Right       = ES_RIGHT,
	MultiLine   = ES_MULTILINE,
	UpperCase   = ES_UPPERCASE,
	LowerCase   = ES_LOWERCASE,
	Password    = ES_PASSWORD,
	AutoVScroll = ES_AUTOVSCROLL,
	AutoHScroll = ES_AUTOHSCROLL,
	NoHideSel   = ES_NOHIDESEL,
	OEMConvert  = ES_OEMCONVERT,
	ReadOnly    = ES_READONLY,
	WantReturn  = ES_WANTRETURN,
	Number      = ES_NUMBER);
enum_flags(EditMargin, UINT,
	Left     = EC_LEFTMARGIN,
	Right    = EC_RIGHTMARGIN,
	FontInfo = EC_USEFONTINFO);
class EditBalloonTip : private EDITBALLOONTIP {
public:
	EditBalloonTip() : EDITBALLOONTIP{ 0 } reflect_to(this->cbStruct = sizeof(EDITBALLOONTIP));
public: // Property - Title
	/* W */ inline auto &Title(LPCTSTR lpszTitle) reflect_to_self(this->pszTitle = lpszTitle);
	/* R */ inline const String Title() const reflect_as(CString(this->pszTitle, MaxLenTitle));
public: // Property - String
	/* W */ inline auto &Text(LPCTSTR lpszText) reflect_to_self(this->pszText = lpszText);
	/* R */ inline const String Text() const reflect_as(CString(this->pszText, MaxLenNotice));
public: // Property - Icon
	/* W */ inline auto &Icon(ToolTipIcons tti) reflect_to_self(this->ttiIcon = tti.yield());
	/* R */ inline ToolTipIcons Icon()const reflect_as(force_cast<ToolTipIcons>(this->ttiIcon));
public:
	inline PEDITBALLOONTIP operator&() reflect_as(this);
	inline const EDITBALLOONTIP *operator&() const reflect_as(this);
};
BaseOf_CommCtl(class EditBase) {
protected:
	SFINAE_CommCtl(EditBase);
	static constexpr auto CtlClassName = WC_EDIT;
public:
	using super = CommCtl<KChain<EditBase<AnyChild>, AnyChild>>;
	using Style = EditStyle;
	using Balloon = EditBalloonTip;
public:
	EditBase() {}

#pragma region Methods
///#define EM_SCROLL               0x00B5
	inline auto &ScrollCaret() reflect_to_child(super::Send(EM_SCROLLCARET));
	inline bool  LineScroll(int nLines) reflect_as(super::Send(EM_LINESCROLL, 0, nLines));
	inline auto &ReplaceSel(LPCTSTR lpString, bool bUndo = false) reflect_to_child(super::Send(EM_REPLACESEL, bUndo, lpString));
	inline bool  Undo() reflect_as(super::Send(EM_UNDO));
	inline auto &EmptyUndoBuffer() reflect_to_child(super::Send(EM_EMPTYUNDOBUFFER));
//#define EM_LINEFROMCHAR         0x00C9
//#define EM_POSFROMCHAR          0x00D6
//#define EM_CHARFROMPOS          0x00D7
	inline auto&BalloonTip(const Balloon &tip) const assertl_reflect_as_self(Edit_ShowBalloonTip(self, &tip));
	inline auto&BalloonTip() const assertl_reflect_as_self(Edit_HideBalloonTip(self));
//#define Edit_GetFileLineFromChar(hwndCtl, characterIndex) \
//        (DWORD)SNDMSG((hwndCtl), EM_FILELINEFROMCHAR, (WPARAM)(characterIndex), 0)
#pragma endregion

#pragma region Properties
public: // Property - uSel
	/* W */ inline auto &uSel(int to, int from) reflect_to_child(super::Send(EM_SETSEL, to, from));
	/* R */ inline auto  uSel() const reflect_to(struct { _M_(int to = 0, from = 0); } r; super::Send(EM_GETSEL, &r.from, &r.to), r);
public: // Property - Rect
	/* W */ inline auto &Rect(LRect rc) reflect_to_child(super::Send(EM_SETRECT, O, rc));
	/* R */ inline LRect Rect() const assertl_reflect_to(LRect rc, super::Send(EM_GETRECT, O, &rc), rc);
public: // Property - RectNp
	/* W */ inline auto &RectNp(LRect rc) reflect_to_child(super::Send(EM_SETRECTNP, O, rc));
public: // Property - Modify
	/* W */ inline auto &Modify(bool bModified) reflect_to_child(super::Send(EM_SETMODIFY, bModified));
	/* R */ inline bool  Modify() const reflect_as(super::Send(EM_GETMODIFY));
public: // Property - Handle
	/* W */ inline auto  &Handle(HLOCAL hLocal) reflect_to_child(super::Send(EM_SETHANDLE, hLocal));
	/* R */ inline HLOCAL Handle() const reflect_as(super::template Send<HLOCAL>(EM_GETHANDLE));
public: // Property - Thumb
	/* R */ inline int Thumb() const reflect_as(super::Send(EM_GETTHUMB));
public: // Property - LineCount
	/* R */ inline UINT LineCount() const reflect_as(super::Send(EM_GETLINECOUNT));
public: // Property - LineIndex
	/* R */ inline int LineIndex(int index) reflect_as(super::Send(EM_LINEINDEX, index));
public: // Property - LineLength
	/* R */ inline int LineLength(int nLine) reflect_as(super::Send(EM_LINELENGTH, nLine));
public: // Property - Line
	/* W */ inline String Line(int nLine) const {
		auto len = LineLength(nLine);
		assertl(len > 0);
		if (len == 0) return O;
		String line(len);
		assertl(super::Send(EM_GETLINE, nLine, line));
		return line;
	}
public: // Property - FmtLines
	/* W */ inline auto &FmtLines(bool bFmtLines) reflect_to_child(assertl(super::Send(EM_FMTLINES, bFmtLines) == bFmtLines));
public: // Property - LimitText
	/* W */ inline auto &LimitText(UINT limit) reflect_to_child(super::Send(EM_SETLIMITTEXT, limit));
	/* R */ inline UINT  LimitText() const reflect_as(super::Send(EM_GETLIMITTEXT));
public: // Property - CanUndo
	/* R */ inline bool CanUndo() const reflect_as(super::Send(EM_CANUNDO));
public: // Property - TabStops
//	/* W */ inline auto &TabStops() reflect_to_child(super::Send(EM_SETTABSTOPS));
public: // Property - FirstVisibleLine
	/* R */ inline int FirstVisibleLine() const reflect_as(super::Send(EM_GETFIRSTVISIBLELINE));
public: // Property - ReadOnly
	/* W */ inline auto &ReadOnly(bool bReadOnly) reflect_to_child(assertl(super::Send(EM_SETREADONLY, bReadOnly)));
//public: // Property - WordBreakProc
//	/* W */ inline auto &WordBreakProc() reflect_to_child(super::Send(EM_SETWORDBREAKPROC));
//	/* R */ inline auto &WordBreakProc() const reflect_as(super::Send(EM_GETWORDBREAKPROC));
public: // Property - PasswordChar
	/* W */ inline auto &PasswordChar(TCHAR chr) reflect_to_child(super::Send(EM_SETPASSWORDCHAR, chr));
	/* R */ inline TCHAR PasswordChar() const reflect_as(super::Send(EM_GETPASSWORDCHAR));
//public: // Property - Margins
//	using Margin = EditMargin;
//	/* W */ inline auto &Margins(Margin m) reflect_to_child(super::Send(EM_SETMARGINS, m.yield(), ));
//	/* R */ inline auto &Margins() const reflect_as(super::Send(EM_GETMARGINS));
//public: // Property - ImeStatus
//	/* W */ inline auto &ImeStatus() reflect_to_child(super::Send(EM_SETIMESTATUS));
//	/* R */ inline auto &ImeStatus() const reflect_as(super::Send(EM_GETIMESTATUS));
public: // Property - CueBanner
	/* W */ inline auto  &CueBanner(LPCTSTR lpString, bool bFocused = false) reflect_to_child(Edit_SetCueBannerTextFocused(self, lpString, bFocused));
	/* R */ inline String CueBanner() const assertl_reflect_to(String cbt = MaxLenNotice, Edit_GetCueBannerText(self, cbt, MaxLenNotice + 1), cbt.Trunc());
//public: // Property - ExtendedStyle
//	/* W */ inline auto &ExtendedStyle(TCHAR chr) reflect_to_child(Edit_SetExtendedStyle(self, ));
//	/* R */ inline TCHAR ExtendedStyle() const reflect_as(Edit_GetExtendedStyle(self));
public: // Property - SearchWeb
	/* W */ inline auto &SearchWeb(bool bSearchWeb) reflect_to_child(Edit_EnableSearchWeb(self, bSearchWeb));
public: // Property - CaretIndex
	/* W */ inline auto &CaretIndex(DWORD newCaretIndex) reflect_to_child(Edit_SetCaretIndex(self, newCaretIndex));
	/* R */ inline DWORD CaretIndex() const reflect_as(Edit_GetCaretIndex(self));
public: // Property - Zoom
	/* W */ inline auto &Zoom(int Numerator, int Denominator) reflect_to_child(Edit_SetZoom(self, Numerator, Denominator));
	/* R */ inline auto  Zoom() const assertl_reflect_to(struct { _M_(int Numerator, Denominator); } z, Edit_GetZoom(self, &z.Numerator, &z.Denominator), z);
public: // Property - FileLineIndex
	/* R */ inline int FileLineIndex(int index) const reflect_as(Edit_GetFileLineIndex(self, index));
public: // Property - FileLineLength
	/* R */ inline int FileLineLength(int nLine) const reflect_as(Edit_GetFileLineLength(self, nLine));
public: // Property - FileLine
	/* R */ inline String FileLine(int nLine) const {
		auto len = FileLineLength(nLine);
		assertl(len > 0);
		if (len == 0) return O;
		String line(len);
		assertl(Edit_GetFileLine(self, nLine, line));
		return line;
	}
public: // Property - FileLineCount
	/* R */ inline DWORD FileLineCount() const reflect_as(Edit_GetFileLineCount(self));
#pragma endregion
};
#pragma endregion

}
