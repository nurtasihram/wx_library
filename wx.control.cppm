module;

#include <Windows.h>
#include <CommCtrl.h>

#define WX_CPPM_CONTROL
#include "wx_control"

export module wx.control;

import wx.proto;

export namespace WX {

enum_flags(SystemState, DWORD,
	Unavailable       = STATE_SYSTEM_UNAVAILABLE,
	Selected          = STATE_SYSTEM_SELECTED,
	Focused           = STATE_SYSTEM_FOCUSED,
	Pushed            = STATE_SYSTEM_PRESSED,
	Checked           = STATE_SYSTEM_CHECKED,
	Mixed             = STATE_SYSTEM_MIXED,
	ReadOnly          = STATE_SYSTEM_READONLY,
	HotTracked        = STATE_SYSTEM_HOTTRACKED,
	Defaulted         = STATE_SYSTEM_DEFAULT,
	Expanded          = STATE_SYSTEM_EXPANDED,
	Collapsed         = STATE_SYSTEM_COLLAPSED,
	Busy              = STATE_SYSTEM_BUSY,
	Floating          = STATE_SYSTEM_FLOATING,
	Marqueed          = STATE_SYSTEM_MARQUEED,
	Animated          = STATE_SYSTEM_ANIMATED,
	Invisible         = STATE_SYSTEM_INVISIBLE,
	Offscreen         = STATE_SYSTEM_OFFSCREEN,
	Sizeable          = STATE_SYSTEM_SIZEABLE,
	Moveable          = STATE_SYSTEM_MOVEABLE,
	SelfVoicing       = STATE_SYSTEM_SELFVOICING,
	Focusable         = STATE_SYSTEM_FOCUSABLE,
	Selectable        = STATE_SYSTEM_SELECTABLE,
	Linked            = STATE_SYSTEM_LINKED,
	Traversed         = STATE_SYSTEM_TRAVERSED,
	MultiSelectable   = STATE_SYSTEM_MULTISELECTABLE,
	ExtSelectable     = STATE_SYSTEM_EXTSELECTABLE,
	AlertLow          = STATE_SYSTEM_ALERT_LOW,
	AlertMedium       = STATE_SYSTEM_ALERT_MEDIUM,
	AlertHigh         = STATE_SYSTEM_ALERT_HIGH,
	Protected         = STATE_SYSTEM_PROTECTED);

#pragma region ImageList
class ImageList {
protected:
	mutable HIMAGELIST hImageList = O;
	INNER_USE(ImageList);
	ImageList(HIMAGELIST h) : hImageList(h) {}
public:
	ImageList() {}
	ImageList(Null) {}
public:
	inline operator bool() const reflect_as(hImageList);
	inline operator HIMAGELIST() const reflect_as(hImageList);
};
using CImageList = RefAs<ImageList>;
#pragma endregion

#pragma region ControlCommon
enum_flags(ControlCommonStyle, WStyle,
	Top                     = CCS_TOP,
	NoMoveY                 = CCS_NOMOVEY,
	Bottom                  = CCS_BOTTOM,
	NoResize                = CCS_NORESIZE,
	NoParentAlign           = CCS_NOPARENTALIGN,
	Adjustable              = CCS_ADJUSTABLE,
	NoDivider               = CCS_NODIVIDER,
	Vert                    = CCS_VERT,
	Left                    = CCS_LEFT,
	Right                   = CCS_RIGHT,
	NoMoveX                 = CCS_NOMOVEX);
using CCStyle = ControlCommonStyle;
template<class AnyChild>
class ControlCommon : public WindowBase<AnyChild> {
public:
	using super = WindowBase<AnyChild>;
protected:
	SFINAE_Window(AnyChild);
	use_member(CtlClassName);
	template<bool IsUnicode, class Style, class StyleEx>
	using CreateStructX = super::template CreateStructX<IsUnicode, Style, StyleEx>;
	template<class Style, class StyleEx>
	using CreateStruct = super::template CreateStructX<IsUnicode, Style, StyleEx>;
	template<class Style, class StyleEx>
	using CreateStructA = super::template CreateStructX<false, Style, StyleEx>;
	template<class Style, class StyleEx>
	using CreateStructW = super::template CreateStructX<true, Style, StyleEx>;
public:
	ControlCommon() { misuse_assert(!std::is_void_v<AnyChild>, "Base of class ControlCommon cannot be void"); }
protected:
	static WindowClass DefClass;
	static WndProc DefProc;
	struct xClass : public super::XClass {
		xClass() {
			this->Name(AnyChild::CtlClassName);
			this->GetInfo();
			this->Name(AnyChild::CClassName());
			DefProc = this->lpfnWndProc;
			this->lpfnWndProc = AnyChild::MainProc;
		}
	};
public:
	static inline ATOM Register() {
		static ATOM atom = 0;
		if (atom) return atom;
		auto cw = WX::CreateStruct().Class(AnyChild::CtlClassName).Create();
		atom = cw->Class().Atom();
		cw->Destroy();
		return atom;
	}
public:
	inline auto Create(HWND hParent = O) reflect_as(CreateStruct<typename AnyChild::Style, typename AnyChild::StyleEx>(child, hParent));
	inline auto CreateA(HWND hParent = O) reflect_as(CreateStructA<typename AnyChild::Style, typename AnyChild::StyleEx>(child, hParent));
	inline auto CreateW(HWND hParent = O) reflect_as(CreateStructW<typename AnyChild::Style, typename AnyChild::StyleEx>(child, hParent));
};
template<class AnyChild>
WndProc ControlCommon<AnyChild>::DefProc;
#define BaseOf_CommCtl(name) template<class AnyChild> name : public ControlCommon<Chain<name<AnyChild>, AnyChild>>
#define SFINAE_CommCtl(name) friend class ControlCommon<name>
#pragma endregion

#pragma region Control Header
enum_flags(HeaderStyle, CCStyle,
	Horz            = HDS_HORZ,
	Buttons         = HDS_BUTTONS,
	HotTrack        = HDS_HOTTRACK,
	Hidden          = HDS_HIDDEN,
	DragDrop        = HDS_DRAGDROP,
	FullDrag        = HDS_FULLDRAG,
	FilterBar       = HDS_FILTERBAR,
	Flat            = HDS_FLAT,
	CheckBoxes      = HDS_CHECKBOXES,
	NoSizing        = HDS_NOSIZING,
	Overflow        = HDS_OVERFLOW);
enum_flags(HeaderFormat, int,
	Left            = HDF_LEFT,
	Right           = HDF_RIGHT,
	Center          = HDF_CENTER,
	JustifyMask     = HDF_JUSTIFYMASK,
	RTLReading      = HDF_RTLREADING,
	Bitmap          = HDF_BITMAP,
	String          = HDF_STRING,
	OwnerDraw       = HDF_OWNERDRAW,
	Image           = HDF_IMAGE,
	BitmapOnRight   = HDF_BITMAP_ON_RIGHT,
	SortUp          = HDF_SORTUP,
	SortDown        = HDF_SORTDOWN,
	CheckBox        = HDF_CHECKBOX,
	Checked         = HDF_CHECKED,
	FixedWidth      = HDF_FIXEDWIDTH,
	SplitButton     = HDF_SPLITBUTTON);
enum_class(HeaderFilterType, UINT,
	String  = HDFT_ISSTRING,
	Number  = HDFT_ISNUMBER,
	Date    = HDFT_ISDATE,
	NoValue = HDFT_HASNOVALUE);
enum_flags(HeaderItemState, UINT,
	Focussed = HDIS_FOCUSED);
template<bool IsUnicode>
class HeaderItemX : public RefStruct<switch_structx(HDITEM)> {
	using_structx(HDITEM);
	using_structx(HD_TEXTFILTER);
public:
	using super = RefStruct<switch_structx(HDITEM)>;
public:
	HeaderItemX() reflect_to(self->mask = HDI_WIDTH | HDI_HEIGHT |
		HDI_TEXT | HDI_FORMAT | HDI_LPARAM |
		HDI_BITMAP | HDI_IMAGE | HDI_ORDER |
		HDI_FILTER | HDI_STATE)
	HeaderItemX(Null) {}
	HeaderItemX(const HDITEM &hdi) : super(hdi) {}
public: // Property - Width
	/* W */ inline auto &Width(int cx) reflect_to_self(self->cxy = cx, self->mask |= HDI_WIDTH);
	/* R */ inline auto  Width() const reflect_as(self->cxy);
public: // Property - Height
	/* W */ inline auto &Height(int cy) reflect_to_self(self->cxy = cy, self->mask |= HDI_HEIGHT);
	/* R */ inline auto  Height() const reflect_as(self->cxy);
public: // Property - Text
	/* R */ inline const String Text() const reflect_as(CString(self->pszText, self->cchTextMax));
public: // Property - Bitmap
	/* W */ inline auto &Bitmap(HBITMAP hBitmap) reflect_to_self(self->hbm = hBitmap, self->mask |= HDI_BITMAP);
	/* R */ inline CBitmap Bitmap() const reflect_as(self->hbm);
public: // Property - Format
	/* W */ inline auto &Format(HeaderFormat fmt) reflect_to_self(self->fmt = fmt.yield(), self->mask |= HDI_FORMAT);
	/* R */ inline auto  Format() const reflect_as(ref_as<HeaderFormat>(self->fmt));
public: // Property - Param
	/* W */ inline auto &Param(LPARAM lParam) reflect_to_self(self->lParam = lParam, self->mask |= HDI_LPARAM);
	/* R */ inline LPARAM Param() const reflect_as(self->lParam);
public: // Property - Image
	/* W */ inline auto &Image(int iImage) reflect_to_self(self->iImage = iImage, self->mask |= HDI_IMAGE);
	/* R */ inline auto  Image() const reflect_as(self->iImage);
public: // Property - Order
	/* W */ inline auto &Order(int iOrder) reflect_to_self(self->iOrder = iOrder, self->mask |= HDI_ORDER);
	/* R */ inline auto  Order() const reflect_as(self->iOrder);
public: // Property - FilterType
	/* R */ inline auto FilterType() const reflect_as(ref_as<HeaderFilterType>(self->type));
public: // Property - Filter
	//void *pvFilter;       // [in] filter data see above
public: // Property - States
	/* W */ inline auto &States(HeaderItemState state) reflect_to_self(self->state = state.yield(), self->mask |= HDI_STATE);
	/* R */ inline auto  States() const reflect_as(ref_as<HeaderItemState>(self->state));
};
using HeaderItem = HeaderItemX<IsUnicode>;
using HeaderItemA = HeaderItemX<false>;
using HeaderItemW = HeaderItemX<true>;
class HeaderIItem {
	template<class>
	friend class HeaderBase;
	CWindow header;
	int index;
public:
	HeaderIItem(HWND hHeader, int index) : header(hHeader), index(index) {}
public:
	inline void Remove() assertl_reflect_as(header->Send(HDM_DELETEITEM, index));
public:
	inline operator HeaderItemA() const;
	inline operator HeaderItemW() const;
	inline auto &operator=(const HDITEMA &hdi) assertl_reflect_as_self(header->Send(HDM_SETITEMA, index, (LPARAM)&hdi));
	inline auto &operator=(const HDITEMW &hdi) assertl_reflect_as_self(header->Send(HDM_SETITEMW, index, (LPARAM)&hdi));
};
BaseOf_CommCtl(class HeaderBase) {
	SFINAE_CommCtl(HeaderBase);
public:
	static constexpr TCHAR CtlClassName[] = WC_HEADER;
	using super = ControlCommon<Chain<HeaderBase<AnyChild>, AnyChild>>;
	using Style = HeaderStyle;
public:
	HeaderBase() {}
public:
	inline int Insert(const HDITEMA &hdi, int index) reflect_as(super::template Send<int>(HDM_INSERTITEMA, index, (LPARAM)&hdi));
	inline int Insert(const HDITEMW &hdi, int index) reflect_as(super::template Send<int>(HDM_INSERTITEMW, index, (LPARAM)&hdi));
	inline void Remove(int index) assertl_reflect_as(super::Send(HDM_DELETEITEM, index));
#pragma region Properties
public: // Property - Count
	/* R */ inline int Count() const reflect_as(super::template Send<int>(HDM_GETITEMCOUNT));
#pragma endregion
};
using Header = HeaderBase<void>;
#pragma endregion

#pragma region Control ToolBar
enum_flags(ToolBarStyle, CCStyle,
	Buttons         = TBSTYLE_BUTTON,
	Sep             = TBSTYLE_SEP,
	Check           = TBSTYLE_CHECK,
	Group           = TBSTYLE_GROUP,
	CheckGroup      = TBSTYLE_CHECKGROUP,
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
	Transparent     = TBSTYLE_TRANSPARENT);
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
class ToolBarButton : public RefStruct<TBBUTTON> {
public:
	using super = RefStruct<TBBUTTON>;
public:
	ToolBarButton() {}
	ToolBarButton(const TBBUTTON &t) : super(t) {}
public: 
	/* W */ inline auto &BitmapIndex(int iBitmap) reflect_to_self(self->iBitmap = iBitmap);
	/* R */ inline int BitmapIndex() const reflect_as(self->iBitmap);
public: 
	/* W */ inline auto &ID(int idCommand) reflect_to_self(self->idCommand = idCommand);
	/* R */ inline int ID() const reflect_as(self->idCommand);
public: 
	/* W */ inline auto &States(ToolBarState tbs) reflect_to_self(self->fsState = tbs.yield());
	/* R */ inline ToolBarState States() const reflect_as(reuse_as<ToolBarState>(self->fsState));
public: 
	/* W */ inline auto &Styles(ToolBarButtonStyle tbbs) reflect_to_self(self->fsStyle = tbbs.yield());
	/* R */ inline ToolBarButtonStyle Styles() const reflect_as(reuse_as<ToolBarButtonStyle>(self->fsStyle));
public: 
	template<class AnyType>
	/* W */ inline auto &Data(AnyType *ptr) reflect_to_self(self->dwData = (DWORD_PTR)ptr);
	template<class AnyType>
	/* R */ inline AnyType *Data() reflect_as(reuse_as<AnyType *>(self->dwData));
	template<class AnyType>
	/* R */ inline const AnyType *Data() const reflect_as(reuse_as<const AnyType *>(self->dwData));
public: 
	/* W */ inline auto &String(INT_PTR iString) reflect_to_self(self->iString = iString);
	/* W */ inline auto &String(LPCTSTR lpString) reflect_to_self(self->iString = (INT_PTR)lpString);
	/* R */ inline INT_PTR StringIndex() const reflect_as(self->iString);
	/* R */ inline const WX::String String() const reflect_as(CString((LPCTSTR)self->iString, MaxLenNotice));
};
BaseOf_CommCtl(class ToolBarBase) {
	SFINAE_CommCtl(ToolBarBase);
public:
	static constexpr TCHAR CtlClassName[] = TOOLBARCLASSNAME;
	using super = ControlCommon<Chain<ToolBarBase<AnyChild>, AnyChild>>;
	using Style = ToolBarStyle;
	using StyleEx = ToolBarStyleEx;
	using Button = ToolBarButton;
public:
	ToolBarBase() {}
};
using ToolBar = ToolBarBase<void>;
#pragma endregion

#pragma region Control ReBar
enum_flags(ReBarStyle, CCStyle,
	ToolTips          = RBS_TOOLTIPS,
	VarHeight         = RBS_VARHEIGHT,
	NoBorders         = RBS_BANDBORDERS,
	FixedOrder        = RBS_FIXEDORDER,
	RegisterDrop      = RBS_REGISTERDROP,
	AutoSize          = RBS_AUTOSIZE,
	VerticalGripper   = RBS_VERTICALGRIPPER,
	DoubleClickToggle = RBS_DBLCLKTOGGLE);
#pragma endregion

#pragma region Control ToolTips
enum_flags(ToolTipStyle, CCStyle,
	AlwaysTip        = TTS_ALWAYSTIP,
	NoPrefix         = TTS_NOPREFIX,
	NoAnimate        = TTS_NOANIMATE,
	NoFade           = TTS_NOFADE,
	Balloon          = TTS_BALLOON,
	Close            = TTS_CLOSE,
	UseVisualStyle   = TTS_USEVISUALSTYLE);
#pragma endregion

#pragma region Control StatusBar
enum_flags(StatusBarTextStyle, uint16_t,
	Default      = 0,
	OwnerDraw    = SBT_OWNERDRAW,
	NoBorders    = SBT_NOBORDERS,
	PopOut       = SBT_POPOUT,
	RTLReading   = SBT_RTLREADING,
	NoTabParsing = SBT_NOTABPARSING);
BaseOf_CommCtl(class StatusBarBase) {
	SFINAE_CommCtl(StatusBarBase);
public:
	static constexpr TCHAR CtlClassName[] = STATUSCLASSNAME;
	using super = ControlCommon<Chain<StatusBarBase<AnyChild>, AnyChild>>;
	using Style = WStyle;
	using StyleEx = WStyleEx;
	using TextStyle = StatusBarTextStyle;
public:
	StatusBarBase() {}
public:
	inline void FixSize() reflect_to(super::Send(WM_SIZE));

#pragma region Properties
public: 
	template<size_t Len>
	/* W */ inline bool SetParts(const int (&Slice)[Len]) reflect_as(super::Send(SB_SETPARTS, Len, Slice));
	/* W */ inline bool SetParts(const int *pSlices, int Len) reflect_as(super::Send(SB_SETPARTS, Len, pSlices));
	template<size_t Len>
	/* R */ inline bool GetParts(int (&Slice)[Len]) const reflect_as(super::Send(SB_GETPARTS, Len, Slice));
	/* R */ inline bool GetParts(int *pSlices, int Len) const reflect_as(super::Send(SB_GETPARTS, Len, pSlices));
public: 
	/* R */ inline auto Borders() const assertl_reflect_to(struct { int _M_(BorderH, BorderV, GapH); } borders, super::Send(SB_GETBORDERS, 0, &borders), borders);
public: 
	/* W */ inline auto&MinHeight(int MinHeight) reflect_to_self(super::Send(SB_SETMINHEIGHT, MinHeight));
public: 
	/* W */ inline auto&Simple(bool bSimple) reflect_to_self(super::Send(SB_SIMPLE, bSimple));
	/* R */ inline bool Simple() const reflect_as(super::Send(SB_SIMPLE));
public: 
	/* W */ inline LRect Rect(uint8_t nPart) assertl_reflect_to(LRect rc, super::Send(SB_GETRECT, nPart, &rc), rc);
public: 
	/* W */ inline auto &Icon(uint8_t nPart, HICON hIcon) reflect_to_self(super::Send(SB_SETICON, nPart, hIcon));
	/* R */ inline CIcon Icon(uint8_t nPart) const reflect_as((HICON)super::Send(SB_GETICON, nPart));
public: 
	/* R */ inline uint16_t TextLength(uint8_t nPart) const reflect_as(super::template Send<uint16_t>(SB_GETTEXTLENGTH, nPart));
public: 
	/* R */ inline TextStyle TextStyles(uint8_t nPart) const reflect_as(super::template Send<TextStyle>(SB_GETTEXTLENGTH, nPart) >> 16);
public: 
	/* W */ inline bool Text(uint8_t nPart, LPCTSTR text, TextStyle style = TextStyle::Default) reflect_as(super::Send(SB_SETTEXT, nPart | style.yield(), (LPARAM)(LPCTSTR)text));
	/* R */ inline String Text(uint8_t nPart) const {
		auto len = TextLength(nPart);
		if (len <= 0) return O;
		String str = len;
		if (super::Send(SB_GETTEXT, nPart, str))
			return str;
		return O;
	}
public: 
	/* W */ inline auto  &TipText(WORD id, LPCTSTR tip) reflect_to_self(super::Send(SB_SETTIPTEXT, id, (LPARAM)(LPCTSTR)tip));
	///* R */ inline String TipText(WORD id) const {
	//	String str = MaxLenNotice;
	//	if (super::Send(SB_GETTIPTEXT, MAKEWPARAM(id, MaxLenNotice + 1), str))
	//		return str.Shrink();
	//	return O;
	//}
public: 
	/* W */ inline auto &UnicodeFormat(bool bUnicode) reflect_to_self(super::Send(SB_SETUNICODEFORMAT, bUnicode));
	/* R */ inline bool  UnicodeFormat() const reflect_as(super::Send(SB_GETUNICODEFORMAT));
public: 
	/* R */ inline RGBColor BkColor() const reflect_as(super::template Send<RGBColor>(SB_SETBKCOLOR));
#pragma endregion
};
using StatusBar = StatusBarBase<void>;
#pragma endregion

#pragma region Control TrackBar
enum_flags(TrackBarStyle, CCStyle,
	AutoTicks          = TBS_AUTOTICKS,
	Vert               = TBS_VERT,
	Horz               = TBS_HORZ,
	Top                = TBS_TOP,
	Bottom             = TBS_BOTTOM,
	Left               = TBS_LEFT,
	Right              = TBS_RIGHT,
	Both               = TBS_BOTH,
	NoTicks            = TBS_NOTICKS,
	EnableSelRange     = TBS_ENABLESELRANGE,
	FixedLength        = TBS_FIXEDLENGTH,
	NoThumb            = TBS_NOTHUMB,
	ToolTips           = TBS_TOOLTIPS,
	Reversed           = TBS_REVERSED,
	DownIsLeft         = TBS_DOWNISLEFT,
//	NotifyBeforeMove   = TBS_NOTIFYBEFOREMOVE,
	TransparentBkgnd   = TBS_TRANSPARENTBKGND);
#pragma endregion

#pragma region Control DragList
#pragma endregion

#pragma region Control UpDown
enum_flags(UpDownStyle, CCStyle,
	Wrap                = UDS_WRAP,
	SetBuddyInt         = UDS_SETBUDDYINT,
	AlignRight          = UDS_ALIGNRIGHT,
	AlignLeft           = UDS_ALIGNLEFT,
	AutoBuddy           = UDS_AUTOBUDDY,
	ArrowKeys           = UDS_ARROWKEYS,
	Horz                = UDS_HORZ,
	NoThousands         = UDS_NOTHOUSANDS,
	HotTrack            = UDS_HOTTRACK);
BaseOf_CommCtl(class UpDownBase) {
	SFINAE_CommCtl(UpDownBase);
public:
	static constexpr TCHAR CtlClassName[] = UPDOWN_CLASS;
	using super = ControlCommon<Chain<UpDownBase<AnyChild>, AnyChild>>;
	using Style = UpDownStyle;
public:
	UpDownBase() {}
};
using UpDown = UpDownBase<void>;
using CUpDown = RefAs<UpDown>;
#pragma endregion

#pragma region Control Progress
enum_flags(ProgressStyle, CCStyle, 
	Smooth              = PBS_SMOOTH,
	Vertical            = PBS_VERTICAL,
	Marquee             = PBS_MARQUEE,
	SmoothReverse       = PBS_SMOOTHREVERSE);
#pragma endregion

#pragma region Control HotKey
enum_flags(HotKeyFlag, BYTE,
	None                = 0,
	Shift               = HOTKEYF_SHIFT,
	Control             = HOTKEYF_CONTROL,
	Alt                 = HOTKEYF_ALT,
	Ext                 = HOTKEYF_EXT);
enum_flags(HotKeyRule, WORD,
	None                = HKCOMB_NONE,
	Shift               = HKCOMB_S,
	Control             = HKCOMB_C,
	Alt                 = HKCOMB_A,
	ShiftControl        = HKCOMB_SC,
	ShiftAlt            = HKCOMB_SA,
	ControlAlt          = HKCOMB_CA,
	ShiftControlAlt     = HKCOMB_SCA);
class HotKeyInfo {
	HotKeyFlag mod;
	BYTE vk;
public:
	HotKeyInfo(WORD LoWord = 0) : mod(reuse_as<HotKeyFlag>(LOBYTE(LoWord))), vk(HIBYTE(LoWord)) {}
	HotKeyInfo(WPARAM wParam) : HotKeyInfo(LOWORD(wParam)) {}
public: // Property - Modifiers
//	/* W */ inline auto &Modifiers(HotKeyFlag mod) reflect_to_self(this->mod = mod.yield());
	/* R */ inline HotKeyFlag Modifiers() const reflect_as(this->mod);
public: // Property - VirtualKey
	/* W */ inline auto &VirtualKey(BYTE vk) reflect_to_self(this->vk = vk);
	/* R */ inline BYTE VirtualKey() const reflect_as(this->vk);
public:
	inline operator WPARAM() const reflect_as(MAKEWPARAM(MAKEWORD(mod.yield(), vk), 0));
};
BaseOf_CommCtl(class HotKeyBase) {
	SFINAE_CommCtl(HotKeyBase);
public:
	static constexpr TCHAR CtlClassName[] = HOTKEY_CLASS;
	using super = ControlCommon<Chain<HotKeyBase<AnyChild >, AnyChild >>;
	using Info = HotKeyInfo;
	using Rule = HotKeyRule;
public:
	HotKeyBase() {}
public:
#pragma region Properties
public: // Property - HotKey
	/* W */ inline auto &HotKey(Info inf) reflect_to_self(super::Send(HKM_SETHOTKEY, inf));
	/* R */ inline Info  HotKey() const reflect_as(super::Send(HKM_GETHOTKEY));
public: // Property - Rules
	/* W */ inline auto &Rules(Rule rules) reflect_to_self(super::Send(HKM_SETRULES, rules.yield()));
#pragma endregion
};
using HotKey = HotKeyBase<void>;
using CHotKey = RefAs<HotKey>;
#pragma endregion

#pragma region Control SysLink
enum_flags(SysLinkStyle, CCStyle,
	Transparent         = LWS_TRANSPARENT,
	IgnoreReturn        = LWS_IGNORERETURN,
	NoPrefix            = LWS_NOPREFIX,
	UseVisualStyle      = LWS_USEVISUALSTYLE,
	UseCustomText       = LWS_USECUSTOMTEXT,
	Right               = LWS_RIGHT);
BaseOf_CommCtl(class SysLinkBase) {
	SFINAE_CommCtl(SysLinkBase);
public:
	static constexpr TCHAR CtlClassName[] = WC_LINK;
	using super = ControlCommon<Chain<SysLinkBase<AnyChild>, AnyChild>>;
	using Style = SysLinkStyle;
public:
	SysLinkBase() {}
public:

};
#pragma endregion

#pragma region Control ListView
enum_flags(ListViewStyle, CCStyle,
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
class ListViewItem : public RefStruct<LVITEM> {
public:
	using super = RefStruct<LVITEM>;
public:
	ListViewItem() {}
	ListViewItem(const LVITEM &lvi) : super(lvi) {}
};
class ListViewColumn : public RefStruct<LVCOLUMNW> {
public:
	using super = RefStruct<LVCOLUMNW>;
public:
	ListViewColumn() {}
	ListViewColumn(const LVCOLUMNW &lvc) : super(lvc) {}
};
BaseOf_CommCtl(class ListViewBase) {
	SFINAE_CommCtl(ListViewBase);
public:
	static constexpr TCHAR CtlClassName[] = WC_LISTVIEW;
	using super = ControlCommon<Chain<ListViewBase<AnyChild>, AnyChild>>;
	using Style = ListViewStyle;
public:
	ListViewBase() {}
public:
	//inline void InsertItem(const ListViewItem &lvi) assertl_reflect_as(ListView_InsertItem(self, &lvi));
	//inline void DeleteItem(int i) assertl_reflect_as(ListView_DeleteItem(self, i));
	//inline void DeleteAllItem()  assertl_reflect_as(ListView_DeleteAllItems(self));

#pragma region Properties
public: 
//	/* W */ inline bool UnicodeFormat() const reflect_as(ListView_GetUnicodeFormat(self));
//	/* R */ inline auto &UnicodeFormat(bool bUnicode) assertl_reflect_as_self(ListView_SetUnicodeFormat(self, bUnicode));
//public: 
//	/* W */ inline auto &BkColor(DWORD rgb) assertl_reflect_as_self(ListView_SetBkColor(self, rgb));
//	/* R */ inline bool BkColor() const reflect_as(ListView_GetBkColor(self));
//public: 
//public: 
//	/* R */ inline auto ItemCount() const reflect_as(ListView_GetItemCount(self));
//public: 
//	/* W */ inline auto &Item(const ListViewItem &lvi) assertl_reflect_as_self(ListView_SetItem(self, &lvi));
//	/* R */ inline auto Item() const assertl_reflect_to(ListViewItem lvi, ListView_GetItem(self, &lvi), lvi);
#pragma endregion
};
using ListView = ListViewBase<void>;
using CListView = RefAs<ListView>;
#pragma endregion

#pragma region Control TreeView
enum_flags(TreeViewStyle, CCStyle,
	HasButtons          = TVS_HASBUTTONS,
	HasLines            = TVS_HASLINES,
	LinesAtRoot         = TVS_LINESATROOT,
	EditLabels          = TVS_EDITLABELS,
	DisabledDragDrop    = TVS_DISABLEDRAGDROP,
	ShowSelAlways       = TVS_SHOWSELALWAYS,
	RTLReading          = TVS_RTLREADING,
	NoToolTips          = TVS_NOTOOLTIPS,
	CheckBoxes          = TVS_CHECKBOXES,
	TrackSelect         = TVS_TRACKSELECT,
	SingleExpand        = TVS_SINGLEEXPAND,
	InfoTip             = TVS_INFOTIP,
	FullRowSelect       = TVS_FULLROWSELECT,
	NoScroll            = TVS_NOSCROLL,
	NoEvenHeight        = TVS_NONEVENHEIGHT,
	NoHScroll           = TVS_NOHSCROLL);
enum_flags(TreeViewStyleEx, WStyleEx,
	NoSingleCollapse     = TVS_EX_NOSINGLECOLLAPSE,
	MultiSelect          = TVS_EX_MULTISELECT,
	DoubleBuffer         = TVS_EX_DOUBLEBUFFER,
	NoIndentState        = TVS_EX_NOINDENTSTATE,
	RichToolTip          = TVS_EX_RICHTOOLTIP,
	AutoHScroll          = TVS_EX_AUTOHSCROLL,
	FadeInOutExpandos    = TVS_EX_FADEINOUTEXPANDOS,
	PartialCheckBoxes    = TVS_EX_PARTIALCHECKBOXES,
	ExclusionCheckBoxes  = TVS_EX_EXCLUSIONCHECKBOXES,
	DimmedCheckBoxes     = TVS_EX_DIMMEDCHECKBOXES,
	DrawImageAsync       = TVS_EX_DRAWIMAGEASYNC);
BaseOf_CommCtl(class TreeViewBase) {
	SFINAE_CommCtl(TreeViewBase);
public:
	static constexpr TCHAR CtlClassName[] = WC_TREEVIEW;
	using super = ControlCommon<Chain<TreeViewBase<AnyChild>, AnyChild>>;
	using Style = TreeViewStyle;
	using StyleEx = TreeViewStyleEx;
public:
	TreeViewBase() {}
};
using TreeView = TreeViewBase<void>;
using CTreeView = RefAs<TreeView>;
#pragma endregion

#pragma region Control TabControl
enum_flags(TabControlStyle, CCStyle,
	ScrollOpposite      = TCS_SCROLLOPPOSITE,
	Bottom              = TCS_BOTTOM,
	Right               = TCS_RIGHT,
	MultiSelect         = TCS_MULTISELECT,
	FlatButtons         = TCS_FLATBUTTONS,
	ForceIconLeft       = TCS_FORCEICONLEFT,
	ForceLabelLeft      = TCS_FORCELABELLEFT,
	HotTrack            = TCS_HOTTRACK,
	Vertical            = TCS_VERTICAL,
	Tabs                = TCS_TABS,
	Buttons             = TCS_BUTTONS,
	SingleLine          = TCS_SINGLELINE,
	MultiLine           = TCS_MULTILINE,
	RightJustify        = TCS_RIGHTJUSTIFY,
	FixedWidth          = TCS_FIXEDWIDTH,
	RaggedRight         = TCS_RAGGEDRIGHT,
	FocusOnButtonDown   = TCS_FOCUSONBUTTONDOWN,
	OwnerDrawFixed      = TCS_OWNERDRAWFIXED,
	ToolTips            = TCS_TOOLTIPS,
	FocusNever          = TCS_FOCUSNEVER);
BaseOf_CommCtl(class TabControlBase) {
	SFINAE_CommCtl(TabControlBase);
public:
	static constexpr TCHAR CtlClassName[] = WC_TABCONTROL;
	using super = ControlCommon<Chain<TabControlBase<AnyChild>, AnyChild>>;
	using Style = TabControlStyle;
public:
	TabControlBase() {}
};
using TabControl = TabControlBase<void>;
using CTabControl = RefAs<TabControl>;
#pragma endregion

#pragma region Control Animate
enum_flags(AnimateStyle, CCStyle,
	Center              = ACS_CENTER,
	Transparent         = ACS_TRANSPARENT,
	AutoPlay            = ACS_AUTOPLAY,
	Timer               = ACS_TIMER);
BaseOf_CommCtl(class AnimateBase) {
	SFINAE_CommCtl(AnimateBase);
public:
	static constexpr TCHAR CtlClassName[] = ANIMATE_CLASS;
	using super = ControlCommon<Chain<AnimateBase<AnyChild>, AnyChild>>;
	using Style = AnimateStyle;
public:
	AnimateBase() {}
public:
	inline bool Open(LPCSTR lpszAVIPath, HINSTANCE hInst = O) reflect_as(super::Send(ACM_OPENA, hInst, lpszAVIPath));
	inline bool Open(LPCWSTR lpszAVIPath, HINSTANCE hInst = O) reflect_as(super::Send(ACM_OPENW, hInst, lpszAVIPath));
	inline bool Open(WORD resid, HINSTANCE hInst = O) reflect_as(super::Send(ACM_OPEN, hInst, MAKEINTRESOURCE(resid)));
	inline bool Play(UINT rept = (UINT)-1, SHORT start = -1, SHORT end = -1) reflect_as(super::Send(ACM_PLAY, rept, MAKEWPARAM(start, end)));
	inline bool Stop() reflect_as(super::Send(ACM_STOP));
	inline bool IsPlaying() const reflect_as(super::Send(ACM_ISPLAYING));
};
using Animate = AnimateBase<void>;
using CAnimate = RefAs<Animate>;
#pragma endregion

#pragma region Control MonthCal
enum_flags(MonthCalStyle, CCStyle,
	DayState          = MCS_DAYSTATE,
	MultiSelect       = MCS_MULTISELECT,
	WeekNumbers       = MCS_WEEKNUMBERS,
	NoTodayCircle     = MCS_NOTODAYCIRCLE,
	NoToday           = MCS_NOTODAY,
	NoTrailingDates   = MCS_NOTRAILINGDATES,
	ShortDaysOfWeek   = MCS_SHORTDAYSOFWEEK,
	NoSelChangeOnNav  = MCS_NOSELCHANGEONNAV);
BaseOf_CommCtl(class MonthCalBase) {
	SFINAE_CommCtl(MonthCalBase);
public:
	static constexpr TCHAR CtlClassName[] = MONTHCAL_CLASS;
	using super = ControlCommon<Chain<MonthCalBase<AnyChild>, AnyChild>>;
	using Style = MonthCalStyle;
public:
	MonthCalBase() {}
};
using MonthCal = MonthCalBase<void>;
using CMonthCal = RefAs<MonthCal>;
#pragma endregion

#pragma region Control Pager
enum_flags(PagerStyle, CCStyle,
	Vert                = PGS_VERT,
	Horz                = PGS_HORZ,
	AutoScroll          = PGS_AUTOSCROLL,
	DragNDrop           = PGS_DRAGNDROP);
#pragma endregion

#pragma region Control NativeFont
enum_flags(NativeFontStyle, CCStyle,
	Edit                = NFS_EDIT,
	Static              = NFS_STATIC,
	ListCombo           = NFS_LISTCOMBO,
	Button              = NFS_BUTTON,
	All                 = NFS_ALL,
	UseFontAssoc        = NFS_USEFONTASSOC);
#pragma endregion

#pragma region Control Button
enum_flags(ButtonStyle, CCStyle,
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
enum_flags(ButtonSplitStyle, UINT,
	NoSplit   = BCSS_NOSPLIT,
	Stretch   = BCSS_STRETCH,
	AlignLeft = BCSS_ALIGNLEFT,
	Image     = BCSS_IMAGE);
class ButtonSplitInfo : public RefStruct<BUTTON_SPLITINFO> {
public:
	using super = RefStruct<BUTTON_SPLITINFO>;
	using Style = ButtonSplitStyle;
public:
	ButtonSplitInfo() reflect_to(self->mask = BCSIF_GLYPH | BCSIF_IMAGE | BCSIF_STYLE | BCSIF_SIZE);
	ButtonSplitInfo(Null) {}
	ButtonSplitInfo(const BUTTON_SPLITINFO &bs) : super(bs) {}
public: // Property - Styles
	/* W */ inline auto &Styles(Style style) reflect_to_self(self->uSplitStyle = style.yield());
	/* R */ inline Style Styles() const reflect_as(ref_as<Style>(self->uSplitStyle));
public: // Property - Size
	/* W */ inline auto &Size(LSize size) reflect_to_self(self->size = size);
	/* R */ inline LSize Size() const reflect_as(ref_as<LSize>(self->size));
public: // Property - Glyph
	/* W */ inline auto &Glyph(HIMAGELIST glyph) reflect_to_self(self->himlGlyph = glyph);
	/* R */ inline CImageList Glyph() const reflect_as(self->himlGlyph);
};
class ButtonImageList : public RefStruct<BUTTON_IMAGELIST> {
public:
	using super = RefStruct<BUTTON_IMAGELIST>;
public:
	ButtonImageList() {}
public: 
	/* W */ inline auto &Margin(LRect margin) reflect_to_self(self->margin = margin);
	/* R */ inline LRect Margin() const reflect_as(self->margin);
public: 
	//enum_class(Aligns, UINT, 
	//	Left     = BUTTON_IMAGELIST_ALIGN_LEFT,
	//	Right    = BUTTON_IMAGELIST_ALIGN_RIGHT,
	//	Top      = BUTTON_IMAGELIST_ALIGN_TOP,
	//	Bottom   = BUTTON_IMAGELIST_ALIGN_BOTTOM,
	//	Center   = BUTTON_IMAGELIST_ALIGN_CENTER);
	///* W */ inline auto   &Align(Aligns align) reflect_to_self(self->uAlign = align.yield());
	///* R */ inline Aligns  Align() const reflect_as(ref_as<Aligns>(self->uAlign));
};
BaseOf_CommCtl(class ButtonBase) {
	SFINAE_CommCtl(ButtonBase);
public:
	static constexpr TCHAR CtlClassName[] = WC_BUTTON;
	using Child = Chain<ButtonBase<AnyChild>, AnyChild>;
	using super = ControlCommon<Child>;
	using Style = ButtonStyle;
	using State = ButtonState;
public:
	ButtonBase() {}
public:
	void Click() const reflect_to(super::Send(BM_CLICK));

#pragma region Properties
public: // Property - IdealSize
	/* R */ inline LSize IdealSize() const reflect_to(LSize sz, super::Send(BCM_GETIDEALSIZE, 0, &sz), sz);
public: // Property - NoteLength
	/* R */ inline auto NoteLength() const reflect_as(super::template Send<int>(BCM_GETNOTELENGTH));
public: // Property - Note
	/* W */ inline auto &Note(LPCTSTR lpszNote) reflect_to(super::Send(BCM_SETNOTE, 0, lpszNote));
	/* R */ inline String Note() const {
		auto len = NoteLength();
		if (len <= 0) return O;
		auto lpsz = String::Alloc(len);
		super::Send(BCM_GETNOTE, len + 1, lpsz);
		return{ len, lpsz };
	}
public: // Property - TextMargin
	/* W */ inline auto &TextMargin(RECT margin) reflect_to_child(super::Send(BCM_SETTEXTMARGIN, 0, &margin));
	/* R */ inline LRect TextMargin() const reflect_to(LRect margin, super::Send(BCM_GETTEXTMARGIN, 0, &margin), margin);
public: // Property - SplitInfo
	/* W */ inline auto&SplitInfo(const BUTTON_SPLITINFO &bsi) reflect_to_child(super::Send(BCM_SETSPLITINFO, 0, &bsi));
	/* R */ inline auto SplitInfo() const reflect_to(ButtonSplitInfo bsi, super::Send(BCM_GETSPLITINFO, 0, &bsi), bsi);
public: // Property - Shield
	/* W */ inline auto &Shield(bool bShield) reflect_to_self(super::Send(BCM_SETSHIELD, 0, bShield));
public: // Property - DropdownState
	/* W */ inline auto &DropdownState(bool bDropped) reflect_to_self(super::Send(BCM_SETDROPDOWNSTATE, bDropped));
public: // Property - Icon
	/* W */ inline auto &Icon(HICON hIcon) reflect_to_child(super::Send(BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon));
	/* R */ inline CIcon Icon() const reflect_as((HICON)super::Send(BM_GETIMAGE, IMAGE_ICON));
public: // Property - Bitmap
	/* W */ inline auto &Bitmap(HBITMAP hBitmap) reflect_to_child(super::Send(BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap));
	/* R */ inline CBitmap Bitmap() const reflect_as((HBITMAP)super::Send(BM_GETIMAGE, IMAGE_BITMAP));
public: // Property - ImageList
	/* W */ inline auto &ImageList(const BUTTON_IMAGELIST &iml) reflect_to_child(super::Send(BCM_SETIMAGELIST, 0, &iml));
	/* R */ inline auto ImageList() const assertl_reflect_to(ButtonImageList iml, super::Send(BCM_GETTEXTMARGIN, 0, &iml), iml);
public: // Property - CheckStates
	/* W */ inline auto &CheckStates(State s) reflect_to_self(super::Send(BM_SETCHECK, s.yield()));
	/* R */ inline State CheckStates() const reflect_as(super::template Send<State>(BM_GETCHECK));
public:  // Property - States
	/* W */ inline auto &States(State s) reflect_to_self(super::Send(BM_SETSTATE, s.yield()));
	/* R */ inline State States() const reflect_as(super::template Send<State>(BM_GETSTATE));
public: // Property - Styles
	/* W */ inline auto &Styles(Style style, bool bRedraw = true) reflect_to_self(super::Send(BM_SETSTYLE, style.yield(), bRedraw));
public: // Property - DontClick
	/* W */ inline auto &DontClick(bool bDontClick) reflect_to_self(super::Send(BM_SETDONTCLICK, bDontClick));
#pragma endregion
};
using Button = ButtonBase<void>;
#pragma endregion

#pragma region Control Static
enum_flags(StaticStyle, CCStyle,
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
	SFINAE_CommCtl(StaticBase);
public:
	static constexpr TCHAR CtlClassName[] = WC_STATIC;
	using Child = Chain<StaticBase<AnyChild>, AnyChild>;
	using super = ControlCommon<Child>;
	using Style = StaticStyle;
public:
	StaticBase() {}
#pragma region Properties
public: // Property - Icon
	/* W */ inline auto &Icon(HICON hIcon) reflect_to_child(super::Send(STM_SETICON, hIcon));
	/* R */ inline CIcon Icon() const reflect_as(super::template Send<HICON>(STM_GETICON));
public: // Property - ImageBitmap
	/* W */ inline auto &ImageBitmap(HBITMAP hBitmap) reflect_to_child(super::Send(STM_SETIMAGE, IMAGE_BITMAP, hBitmap));
	/* R */ inline CBitmap ImageBitmap() const reflect_as(super::template Send<HBITMAP>(STM_GETIMAGE, IMAGE_BITMAP));
public: // Property - ImageIcon
	/* W */ inline auto &ImageIcon(HICON hIcon) reflect_to_child(super::Send(STM_SETIMAGE, IMAGE_ICON, hIcon));
	/* R */ inline CIcon ImageIcon() const reflect_as(super::template Send<HICON>(STM_GETIMAGE, IMAGE_ICON));
public: // Property - ImageCursor
	/* W */ inline auto &ImageCursor(HCURSOR hCursor) reflect_to_child(super::Send(STM_SETIMAGE, IMAGE_CURSOR, hCursor));
	/* R */ inline CCursor ImageCursor() const reflect_as(super::template Send<HCURSOR>(STM_GETIMAGE, IMAGE_CURSOR));
public: // Property - ImageEnhMeta
	/* W */ inline auto &ImageEnhMeta(HENHMETAFILE hMeta) reflect_to_child(super::Send(STM_SETIMAGE, IMAGE_ENHMETAFILE, hMeta));
//	/* R */ inline CEnhMeta ImageEnhMeta() const reflect_as(super::template Send<HENHMETAFILE>(STM_GETIMAGE, IMAGE_ENHMETAFILE));
#pragma endregion
};
using Static = StaticBase<void>;
#pragma endregion

#pragma region Control Edit
enum_flags(EditStyle, CCStyle,
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
class EditBalloonTip : public RefStruct<EDITBALLOONTIP> {
public:
	using super = RefStruct<EDITBALLOONTIP>;
};
BaseOf_CommCtl(class EditBase) {
	SFINAE_CommCtl(EditBase);
public:
	static constexpr TCHAR CtlClassName[] = WC_EDIT;
	using super = ControlCommon<Chain<EditBase<AnyChild>, AnyChild>>;
	using Style = EditStyle;
	using Balloon = EditBalloonTip;
public:
	EditBase() {}
public:
#pragma region Methods
	inline auto &ScrollCaret() reflect_to_child(super::Send(EM_SCROLLCARET));
	inline bool  LineScroll(int nLines) reflect_as(super::Send(EM_LINESCROLL, 0, nLines));
	inline auto &ReplaceSel(LPCTSTR lpString, bool bUndo = false) reflect_to_child(super::Send(EM_REPLACESEL, bUndo, lpString));
	inline bool  Undo() reflect_as(super::Send(EM_UNDO));
	inline auto &EmptyUndoBuffer() reflect_to_child(super::Send(EM_EMPTYUNDOBUFFER));

//	inline auto&BalloonTip(const Balloon &tip) const assertl_reflect_as_self(Edit_ShowBalloonTip(self, &tip));
//	inline auto&BalloonTip() const assertl_reflect_as_self(Edit_HideBalloonTip(self));
#pragma endregion

#pragma region Properties
public: 
	/* W */ inline auto &Sel(int to, int from) reflect_to_child(super::Send(EM_SETSEL, to, from));
	/* R */ inline auto  Sel() const reflect_to(struct { _M_(int to = 0, from = 0); } r; super::Send(EM_GETSEL, &r.from, &r.to), r);
public: 
	/* W */ inline auto &Rect(LRect rc) reflect_to_child(super::Send(EM_SETRECT, O, rc));
	/* R */ inline LRect Rect() const assertl_reflect_to(LRect rc, super::Send(EM_GETRECT, O, &rc), rc);
public: 
	/* W */ inline auto &RectNp(LRect rc) reflect_to_child(super::Send(EM_SETRECTNP, O, rc));
public: 
	/* W */ inline auto &Modify(bool bModified) reflect_to_child(super::Send(EM_SETMODIFY, bModified));
	/* R */ inline bool  Modify() const reflect_as(super::Send(EM_GETMODIFY));
public: 
	/* W */ inline auto  &Handle(HLOCAL hLocal) reflect_to_child(super::Send(EM_SETHANDLE, hLocal));
	/* R */ inline HLOCAL Handle() const reflect_as(super::template Send<HLOCAL>(EM_GETHANDLE));
public:
	/* R */ inline int Thumb() const reflect_as(super::Send(EM_GETTHUMB));
public:
	/* R */ inline UINT LineCount() const reflect_as(super::Send(EM_GETLINECOUNT));
public: 
	/* R */ inline int LineIndex(int index) reflect_as(super::Send(EM_LINEINDEX, index));
public:
	/* R */ inline int LineLength(int nLine) reflect_as(super::Send(EM_LINELENGTH, nLine));
public: 
	/* W */ inline String Line(int nLine) const {
		auto len = LineLength(nLine);
		assertl(len > 0);
		if (len == 0) return O;
		String line(len);
		assertl(super::Send(EM_GETLINE, nLine, line));
		return line;
	}
public: 
	/* W */ inline auto &FmtLines(bool bFmtLines) reflect_to_child(assertl(super::Send(EM_FMTLINES, bFmtLines) == bFmtLines));
public: 
	/* W */ inline auto &LimitText(UINT limit) reflect_to_child(super::Send(EM_SETLIMITTEXT, limit));
	/* R */ inline UINT  LimitText() const reflect_as(super::Send(EM_GETLIMITTEXT));
public: 
	/* R */ inline bool CanUndo() const reflect_as(super::Send(EM_CANUNDO));
public: 
public: 
	/* R */ inline int FirstVisibleLine() const reflect_as(super::Send(EM_GETFIRSTVISIBLELINE));
public: 
	/* W */ inline auto &ReadOnly(bool bReadOnly) reflect_to_child(assertl(super::Send(EM_SETREADONLY, bReadOnly)));public: 
	/* W */ inline auto &PasswordChar(TCHAR chr) reflect_to_child(super::Send(EM_SETPASSWORDCHAR, chr));
	/* R */ inline TCHAR PasswordChar() const reflect_as(super::Send(EM_GETPASSWORDCHAR));
//public: 
//	/* W */ inline auto  &CueBanner(LPCTSTR lpString, bool bFocused = false) reflect_to_child(Edit_SetCueBannerTextFocused(self, lpString, bFocused));
//	/* R */ inline String CueBanner() const assertl_reflect_to(String cbt = MaxLenNotice, Edit_GetCueBannerText(self, cbt, MaxLenNotice + 1), cbt.Shrink());
//public: 
//	/* W */ inline auto &SearchWeb(bool bSearchWeb) reflect_to_child(Edit_EnableSearchWeb(self, bSearchWeb));
//public: 
//	/* W */ inline auto &CaretIndex(DWORD newCaretIndex) reflect_to_child(Edit_SetCaretIndex(self, newCaretIndex));
//	/* R */ inline DWORD CaretIndex() const reflect_as(Edit_GetCaretIndex(self));
//public: 
//	/* W */ inline auto &Zoom(int Numerator, int Denominator) reflect_to_child(Edit_SetZoom(self, Numerator, Denominator));
//	/* R */ inline auto  Zoom() const assertl_reflect_to(struct { _M_(int Numerator, Denominator); } z, Edit_GetZoom(self, &z.Numerator, &z.Denominator), z);
//public: 
//	/* R */ inline int FileLineIndex(int index) const reflect_as(Edit_GetFileLineIndex(self, index));
//public: 
//	/* R */ inline int FileLineLength(int nLine) const reflect_as(Edit_GetFileLineLength(self, nLine));
//public: 
//	/* R */ inline String FileLine(int nLine) const {
//		auto len = FileLineLength(nLine);
//		assertl(len > 0);
//		if (len == 0) return O;
//		String line(len);
//		assertl(Edit_GetFileLine(self, nLine, line));
//		return line;
//	}
//public: 
//	/* R */ inline DWORD FileLineCount() const reflect_as(Edit_GetFileLineCount(self));
#pragma endregion
};
using Edit = EditBase<void>;
using CEdit = RefAs<Edit>;
#pragma endregion

#pragma region Control ListBox
enum_flags(ListBoxStyle, CCStyle,
	Notify            = LBS_NOTIFY,
	Sort              = LBS_SORT,
	NoRedraw          = LBS_NOREDRAW,
	MultipleSel       = LBS_MULTIPLESEL,
	OwnerDrawFixed    = LBS_OWNERDRAWFIXED,
	OwnerDrawVariable = LBS_OWNERDRAWVARIABLE,
	HasStrings        = LBS_HASSTRINGS,
	UseTabStops       = LBS_USETABSTOPS,
	NoIntegralHeight  = LBS_NOINTEGRALHEIGHT,
	MultiColumn       = LBS_MULTICOLUMN,
	WantKeyboardInput = LBS_WANTKEYBOARDINPUT,
	ExtendedSel       = LBS_EXTENDEDSEL,
	DisableNoScroll   = LBS_DISABLENOSCROLL,
	NoData            = LBS_NODATA,
	NoSel             = LBS_NOSEL,
	ComboBox          = LBS_COMBOBOX,
	Standard          = LBS_STANDARD);
//#define LB_OKAY             0
//#define LB_ERR              (-1)
//#define LB_ERRSPACE         (-2)

//class ListBoxIItem {
//	CWindow listbox;
//	int index;
//public:
//	ListBoxIItem(CWindow listbox, int index) : listbox(listbox), index(index) {}
//public: // Property - Data
//	/* W */ inline auto &Data(LPARAM data) reflect_to_self(listbox->Send(LB_SETITEMDATA, index, data));
//	/* R */ inline LPARAM Data() const reflect_as(listbox->Send<LPARAM>(LB_GETITEMDATA, index)); // LB_ERRxxx
//public: // Property - Text
//	/* W */ inline auto &Text(LPCTSTR lpszString) reflect_to_self(listbox->Send(LB_SETITEMDATA, index, lpszString));
//	/* R */ inline String Text() const {
//		auto len = listbox->Send<int>(LB_GETTEXTLEN, index);
//		if (len == LB_ERR || len <= 0) return O;
//		String str(len｝;
//		listbox->Send(LB_GETTEXT, index, str);
//		return str;
//	}
//public: // Property - Selected
//	/* W */ inline auto &Selected(bool bSelected) reflect_to_self(listbox->Send(LB_SETSEL, bSelected, index));
//	/* R */ inline bool Selected() const reflect_as(listbox->Send<int>(LB_GETSEL, index) != 0); // LB_ERRxxx
//};
BaseOf_CommCtl(class ListBoxBase) {
	SFINAE_CommCtl(ListBoxBase);
public:
	static constexpr TCHAR CtlClassName[] = WC_LISTBOX;
	using super = ControlCommon<Chain<ListBoxBase<AnyChild>, AnyChild>>;
	using Style = ListBoxStyle;
public:
	ListBoxBase() {}

public:
	inline void Add(LPCTSTR lpszString) assertl_reflect_as(super::Send(LB_ADDSTRING, O, lpszString)); // LB_ERRxxx
	inline void Insert(LPCTSTR lpszString, int index = -1) assertl_reflect_as(super::Send(LB_INSERTSTRING, index, lpszString)); // LB_ERRxxx
	inline void Delete(int index) assertl_reflect_as(super::Send(LB_DELETESTRING, index)); // LB_ERRxxx
	inline void ResetContent() assertl_reflect_as(super::Send(LB_RESETCONTENT));

	inline void SelItemRange(int start, int end, bool bSelect) const assertl_reflect_as(super::Send(LB_SELITEMRANGE, bSelect, MAKELPARAM(start, end))); // CB_ERRxxx
	inline void SelItemRange(int start, int end) const assertl_reflect_as(super::Send(LB_SELITEMRANGEEX, start, end)); // LB_ERRxxx

public: // Property - Count
	/* W */ inline auto&Count(int count) reflect_to_self(super::Send(LB_SETCOUNT, count)); // LB_ERRxxx
	/* R */ inline auto Count() const reflect_as(super::template Send<int>(LB_GETCOUNT)); // LB_ERRxxx
public: // 
};
#pragma endregion

#pragma region Control ComboBox
enum_flags(ComboBoxStyle, CCStyle,
	Simple             = CBS_SIMPLE,
	DropDown           = CBS_DROPDOWN,
	DropDownList       = CBS_DROPDOWNLIST,
	OwnerDrawFixed     = CBS_OWNERDRAWFIXED,
	OwnerDrawVariable  = CBS_OWNERDRAWVARIABLE,
	AutoHScroll        = CBS_AUTOHSCROLL,
	OEMConvert         = CBS_OEMCONVERT,
	Sort               = CBS_SORT,
	HasStrings         = CBS_HASSTRINGS,
	NoIntegralHeight   = CBS_NOINTEGRALHEIGHT,
	DisableNoScroll    = CBS_DISABLENOSCROLL,
	UpperCase          = CBS_UPPERCASE,
	LowerCase          = CBS_LOWERCASE);
BaseOf_CommCtl(class ComboBoxBase) {
	SFINAE_CommCtl(ComboBoxBase);
public:
	static constexpr TCHAR CtlClassName[] = WC_COMBOBOX;
	using super = ControlCommon<Chain<ComboBoxBase<AnyChild>, AnyChild>>;
	using Style = ComboBoxStyle;
public:
	ComboBoxBase() {}
};
using ComboBox = ComboBoxBase<void>;
using CComboBox = RefAs<ComboBox>;
#pragma endregion

#pragma region Control DateTimePick
enum_flags(DateTimePickStyle, CCStyle,
	UpDown                 = DTS_UPDOWN,
	ShowNone               = DTS_SHOWNONE,
	ShortDateFormat        = DTS_SHORTDATEFORMAT,
	LongDateFormat         = DTS_LONGDATEFORMAT,
	ShortDateCenturyFormat = DTS_SHORTDATECENTURYFORMAT,
	TimeFormat             = DTS_TIMEFORMAT,
	AppCanParse            = DTS_APPCANPARSE,
	RightAlign             = DTS_RIGHTALIGN);
enum_class(DateTimePickFlags, DWORD,
	Error = GDT_ERROR,
	Valid = GDT_VALID,
	None  = GDT_NONE);
struct DateTimePickInfo : public RefStruct<DATETIMEPICKERINFO> {
	using super = RefStruct<DATETIMEPICKERINFO>;
public:
	DateTimePickInfo() reflect_to(self->cbSize = sizeof(DATETIMEPICKERINFO));
	DateTimePickInfo(const DATETIMEPICKERINFO &dtpi) : super(dtpi) {}
public: // Property - CheckRect
	/* W */ inline auto &CheckRect(LRect rc) reflect_to_self(self->rcCheck = rc);
	/* R */ inline LRect CheckRect() const reflect_as(self->rcCheck);
public: // Property - CheckState
	/* W */ inline auto &CheckState(SystemState state) reflect_to_self(self->stateCheck = state.yield());
	/* R */ inline auto  CheckState() const reflect_as(reuse_as<SystemState>(self->stateCheck));
public: // Property - ButtonRect
	/* W */ inline auto &ButtonRect(LRect rc) reflect_to_self(self->rcButton = rc);
	/* R */ inline LRect ButtonRect() const reflect_as(self->rcButton);
public: // Property - ButtonState
	/* W */ inline auto &ButtonState(SystemState state) reflect_to_self(self->stateButton = state.yield());
	/* R */ inline auto  ButtonState() const reflect_as(reuse_as<SystemState>(self->stateButton));
//public: // Property - Edit
//	/* W */ inline auto &Edit(HWND hEdit) reflect_to_self(self->hwndEdit = hEdit);
//	/* R */ inline CEdit Edit() const reflect_as(self->hwndEdit);
//public: // Property - UpDown
//	/* W */ inline auto &UpDown(HWND hUpDown) reflect_to_self(self->hwndUD = hUpDown);
//	/* R */ inline CUpDown UpDown() const reflect_as(self->hwndUD);
//public: // Property - DropDown
//	/* W */ inline auto &DropDown(HWND hDropDown) reflect_to_self(self->hwndDropDown = hDropDown);
//	/* R */ inline CComboBox DropDown() const reflect_as(self->hwndDropDown);
};
BaseOf_CommCtl(class DateTimePickBase) {
	SFINAE_CommCtl(DateTimePickBase);
public:
	static constexpr TCHAR CtlClassName[] = DATETIMEPICK_CLASS;
	using super = ControlCommon<Chain<DateTimePickBase<AnyChild>, AnyChild>>;
	using Style = DateTimePickStyle;
	using Flags = DateTimePickFlags;
	using Info = DateTimePickInfo;
public:
	DateTimePickBase() {}
public:
#pragma region Properties
//public: // Property - SystemTime
//	/* W */ inline auto &SystemTime(const SYSTEMTIME &st) assertl_reflect_as_self(Send(DTM_GETSYSTEMTIME, &st));
//	/* R */ inline auto  SystemTime() const assertl_reflect_to(SysTime st, Send(self, DTM_SETSYSTEMTIME, &st), st);
//public: // Property - Range
//	/* W */ inline auto &Range(const SYSTEMTIME &st) assertl_reflect_as_self(DateTime_SetRange(self, GD_DEFAULT, &st));
//	/* R */ inline auto  Range() const assertl_reflect_to(SysTime st, DateTime_GetRange(self, &st), st);
//public: // Property - Format
//public: // Property - MonthCalColor
//	/* W */ inline auto &MonthCalColor(int iColor, COLORREF clr) assertl_reflect_as_self(DateTime_SetMonthCalColor(self, iColor, clr));
//	/* R */ inline auto  MonthCalColor(int iColor) const assertl_reflect_as(DateTime_GetMonthCalColor(self, iColor));
//public: // Property - MonthCal
//	/* R */ 
//public: // 
#pragma endregion

};
using DateTimePick = DateTimePickBase<void>;
using CDateTimePick = RefAs<DateTimePick>;
#pragma endregion

#pragma region Control ScrollBar
enum_flags(ScrollBarStyle, CCStyle,
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
class ScrollBarInfo : public RefStruct<SCROLLBARINFO> {
public:
	using super = RefStruct<SCROLLBARINFO>;
public:
	ScrollBarInfo() reflect_to(self->cbSize = sizeof(SCROLLBARINFO));
public: 
	/* W */ inline auto &Rect(LRect rc) reflect_to_self(self->rcScrollBar = rc);
	/* R */ inline LRect Rect() const reflect_as(self->rcScrollBar);
public: 
	/* W */ inline auto &LineButton(int dxyLineButton) reflect_to_self(self->dxyLineButton = dxyLineButton);
	/* R */ inline int   LineButton() const reflect_as(self->dxyLineButton);
public: 
	/* W */ inline auto &ThumbTop(int xyThumbTop) reflect_to_self(self->xyThumbTop = xyThumbTop);
	/* R */ inline int   ThumbTop() const reflect_as(self->xyThumbTop);
public: 
	/* W */ inline auto &ThumbBottom(int xyThumbBottom) reflect_to_self(self->xyThumbBottom = xyThumbBottom);
	/* R */ inline int   ThumbBottom() const reflect_as(self->xyThumbBottom);
public: 
	
};
BaseOf_CommCtl(class ScrollBarBase) {
	SFINAE_CommCtl(ScrollBarBase);
public:
	static constexpr TCHAR CtlClassName[] = WC_SCROLLBAR;
	using super = ControlCommon<Chain<ScrollBarBase<AnyChild>, AnyChild>>;
	using Style = ScrollBarStyle;
	using SInfo = ScrollInfo;
	using SBarInfo = ScrollBarInfo;
public:
	ScrollBarBase() {}

#pragma region Properties
public:

public: 
	/* W */ inline auto &Position(int Pos, bool bRedraw = true) reflect_to_child(super::Send(SBM_SETPOS, Pos, bRedraw));
	/* R */ inline int   Position() const reflect_as(super::Send(SBM_GETPOS));
public: 
	/* W */ inline auto &Range(int MinPos, int MaxPos, bool bRedraw = true) reflect_to_child(super::Send(bRedraw ? SBM_SETRANGEREDRAW : SBM_SETRANGE, MinPos, MaxPos));
	/* R */ inline auto  Range() const assertl_reflect_to(struct{ _M_(int Min, Max); } rgn, super::Send(SBM_GETRANGE, &rgn.Min, &rgn.Max), rgn);
public: 
	/* W */ inline auto  &Info(const SInfo &i, bool bRedraw = true) reflect_to_self(super::Send(SBM_SETSCROLLINFO, bRedraw, &i));
	/* R */ inline SInfo  Info() const assertl_reflect_to(SInfo i, super::Send(SBM_GETSCROLLINFO, 0, &i), i);
public:
	/* R */ inline SBarInfo BarInfo() const assertl_reflect_to(SBarInfo i, super::Send(SBM_GETSCROLLBARINFO, 0, &i), i);
#pragma endregion
};
using ScrollBar = ScrollBarBase<void>;
#pragma endregion

}
