#pragma once

#include <CommCtrl.h>

#include "wx_window.h"

namespace WX {

#pragma region ImageList
#pragma endregion

#pragma region ControlCommon
template<class AnyChild>
class ControlCommon : public WindowBase<AnyChild> {
public:
	using super = WindowBase<AnyChild>;
protected:
	SFINAE_Window(AnyChild);
	def_memberof(CtlClassName);
	subtype_branch(xCreate);
public:
	ControlCommon() { static_assert(!std::is_void_v<AnyChild>); }
protected:
	static WindowClass DefClass;
	static WndProc DefProc;
	struct xClass : super::template XClass<xClass> {
		xClass() {
			this->Name(AnyChild::CtlClassName);
			this->GetInfo();
			this->Name(AnyChild::CClassName());
			DefProc = self->lpfnWndProc;
			self->lpfnWndProc = AnyChild::MainProc;
			
		}
	};
public:
	inline auto Create() = delete;
	inline auto Create(HWND hParent) reflect_as(super::Create().Styles(WS::Child).Parent(hParent));
};
template<class AnyChild>
WndProc ControlCommon<AnyChild>::DefProc;
#define BaseOf_CommCtl(name) template<class AnyChild> name : public ControlCommon<KChain<name<AnyChild>, AnyChild>>
#define SFINAE_CommCtl(name) friend class ControlCommon<name>
#pragma endregion

#pragma region Control Header
enum_flags(HeaderStyle, WStyle,
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

#pragma endregion

#pragma region Control ToolBar
enum_flags(ToolBarStyle, WStyle,
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
struct ToolBarButton : public RefAs<TBBUTTON> {
	using super = RefAs<TBBUTTON>;
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
template<class AnyChild = void>
class ToolBarBase;
using ToolBar = ToolBarBase<>;
BaseOf_CommCtl(class ToolBarBase) {
protected:
	SFINAE_CommCtl(ToolBarBase);
public:
	static constexpr LPCTSTR CtlClassName = TOOLBARCLASSNAME;
	using super = ControlCommon<KChain<ToolBarBase<AnyChild>, AnyChild>>;
	using Style = ToolBarStyle;
	using StyleEx = ToolBarStyleEx;
	using Button = ToolBarButton;
	class IButton {
		ToolBarBase &tb;
		int idCommand;
	public:
		IButton(ToolBarBase &tb, int idCommand) : tb(tb), idCommand(idCommand) {}
	public: 
		/* W */ inline auto&Enable(bool bEnable) assertl_reflect_as_self(tb.Send(TB_ENABLEBUTTON, idCommand, bEnable));
		/* R */ inline bool Enable() const reflect_as(tb.Send(TB_ISBUTTONENABLED, idCommand));
	public: 
		/* W */ inline auto&Check(bool bCheck) assertl_reflect_as_self(tb.Send(TB_CHECKBUTTON, idCommand, bCheck));
		/* R */ inline bool Check() const reflect_as(tb.Send(TB_ISBUTTONCHECKED, idCommand));
	public: 
		/* W */ inline auto&Press(bool bPress) assertl_reflect_as_self(tb.Send(TB_PRESSBUTTON, idCommand, bPress));
		/* R */ inline bool Press() const reflect_as(tb.Send(TB_ISBUTTONPRESSED, idCommand));
	public: 
		/* W */ inline auto&Hide(bool bPress) assertl_reflect_as_self(tb.Send(TB_HIDEBUTTON, idCommand, bPress));
		/* R */ inline bool Hide() const reflect_as(tb.Send(TB_ISBUTTONHIDDEN, idCommand));
	public: 
		/* R */ inline bool HighLighted() const reflect_as(tb.Send(TB_ISBUTTONHIGHLIGHTED, idCommand));
	public: 
		/* W */ inline auto&Indeterminate(bool bEnable) assertl_reflect_as_self(tb.Send(TB_INDETERMINATE, idCommand, bEnable));
		/* R */ inline bool Indeterminate() const reflect_as(tb.Send(TB_ISBUTTONINDETERMINATE, idCommand));
	public: 
		/* R */ inline String Text() const {
			auto len = tb.Send<size_t>(TB_GETBUTTONTEXT, idCommand);
			String text(len);
			tb.Send<size_t>(TB_GETBUTTONTEXT, idCommand, (LPTSTR)text);
			return text;
		}
	public: 
		/* W */ inline auto&Mark(bool bMark) assertl_reflect_as_self(tb.Send(TB_MARKBUTTON, idCommand, bMark));
	public: 
		/* R */ inline int Index() assertl_reflect_to(int index, (index = tb.Send(TB_COMMANDTOINDEX, idCommand)) > 0, index);
	public: 
		inline auto &ID(int idCommand) {
			assertl(Send(TB_SETCMDID, this->idCommand, idCommand));
			this->idCommand = idCommand;
			retself;
		}
		inline int ID() const reflect_as(idCommand);
	public: 
	public:
		inline void Delete() assertl_reflect_as_self(tb.Send(TB_DELETEBUTTON, idCommand));

	};
public:
	ToolBarBase() {}

	template<size_t nCount>
	inline auto &Add(const Button(&buttons)[nCount]) assertl_reflect_as(super::Send(TB_ADDBUTTONS, nCount, buttons));
	inline auto &Add(std::initializer_list<Button> buttons) assertl_reflect_as(super::Send(TB_ADDBUTTONS, buttons.size(), buttons.begin()));
	inline auto &Add(LPCTBBUTTON lpButtons, UINT nCount) assertl_reflect_as(super::Send(TB_ADDBUTTONS, nCount, lpButtons));
	inline auto &Add(const Button *lpButtons, UINT nCount) assertl_reflect_as(super::Send(TB_ADDBUTTONS, nCount, lpButtons));
	inline auto &Add(const TBBUTTON &button) assertl_reflect_as(super::Send(TB_ADDBUTTONS, 1, &button));
	inline auto &Add(const Button &button) assertl_reflect_as(super::Send(TB_ADDBUTTONS, 1, &button));
	inline auto &Insert(const Button &button, int idBefore) assertl_reflect_as(super::Send(TB_INSERTBUTTON, idBefore, &button));

TB_GETBUTTON            = TB_GETBUTTON,

public: 
	/* R */ inline UINT Count() const reflect_as(super::Send(TB_BUTTONCOUNT));
};
#pragma endregion

#pragma region Control ReBar
enum_flags(ReBarStyle, WStyle,
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
enum_flags(ToolTipStyle, WStyle,
	AlwaysTip        = TTS_ALWAYSTIP,
	NoPrefix         = TTS_NOPREFIX,
	NoAnimate        = TTS_NOANIMATE,
	NoFade           = TTS_NOFADE,
	Balloon          = TTS_BALLOON,
	Close            = TTS_CLOSE,
	UseVisualStyle   = TTS_USEVISUALSTYLE);
#pragma endregion

#pragma region Control StatusBar
enum_flags(StatusBarTexts, uint16_t,
	OwnerDraw    = SBT_OWNERDRAW,
	NoBorders    = SBT_NOBORDERS,
	PopOut       = SBT_POPOUT,
	RTLReading   = SBT_RTLREADING,
	NoTabParsing = SBT_NOTABPARSING);
BaseOf_CommCtl(class StatusBarBase) {
protected:
	SFINAE_CommCtl(StatusBarBase);
public:
	static constexpr LPCTSTR CtlClassName = STATUSCLASSNAME;
	using super = ControlCommon<KChain<StatusBarBase<AnyChild>, AnyChild>>;
	using Style = WStyle;
	using StyleEx = WStyleEx;
	using Texts = StatusBarTexts;
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
	/* R */ inline Texts    TextStyle(uint8_t nPart) const reflect_as(super::template Send<Texts>(SB_GETTEXTLENGTH, nPart) >> 16);
public: 
	/* W */ inline bool   Text(uint8_t nPart, LPCTSTR text, Texts style = Texts::Default) reflect_as(super::Send(SB_SETTEXT, nPart | style.yield(), (LPARAM)(LPCTSTR)text));
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
	/* R */ inline String TipText(WORD id) const {
		String str = MaxLenNotice;
		if (super::Send(SB_GETTIPTEXT, MAKEWPARAM(id, MaxLenNotice + 1), str))
			return str.Trunc();
		return O;
	}
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
enum_flags(TrackBarStyle, WStyle,
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
enum_flags(UpDownStyle, WStyle,
	Wrap                = UDS_WRAP,
	SetBuddyInt         = UDS_SETBUDDYINT,
	AlignRight          = UDS_ALIGNRIGHT,
	AlignLeft           = UDS_ALIGNLEFT,
	AutoBuddy           = UDS_AUTOBUDDY,
	ArrowKeys           = UDS_ARROWKEYS,
	Horz                = UDS_HORZ,
	NoThousands         = UDS_NOTHOUSANDS,
	HotTrack            = UDS_HOTTRACK);
#pragma endregion

#pragma region Control Progress
#define PBS_SMOOTH              0x01
#define PBS_VERTICAL            0x04
#define PBS_MARQUEE             0x08
#define PBS_SMOOTHREVERSE       0x10
enum_flags(ProgressStyle, WStyle, 
	Smooth              = PBS_SMOOTH,
	Vertical            = PBS_VERTICAL,
	Marquee             = PBS_MARQUEE,
	SmoothReverse       = PBS_SMOOTHREVERSE);
#pragma endregion

#pragma region Control HotKey

#pragma endregion

#pragma region Control SysLink
#pragma endregion

#pragma region Control ListView
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
struct ListViewItem : public RefAs<LVITEM> {
	using super = RefAs<LVITEM>;
public:
	ListViewItem() {}
	ListViewItem(const LVITEM &lvi) : super(lvi) {}
};
struct ListViewColumn : public RefAs<LVCOLUMNW> {
	using super = RefAs<LVCOLUMNW>;
public:
	ListViewColumn() {}
	ListViewColumn(const LVCOLUMNW &lvc) : super(lvc) {}
};
BaseOf_CommCtl(class ListViewBase) {
	protected:
	SFINAE_CommCtl(ListViewBase);
	def_memberof(wmailBox);
public:
	static constexpr auto CtlClassName = WC_LISTVIEW;
	using super = ControlCommon<KChain<ListViewBase<AnyChild>, AnyChild>>;
	using Style = ListViewStyle;
public:
	ListViewBase() {}
public:
	inline void InsertItem(const ListViewItem &lvi) assertl_reflect_as(ListView_InsertItem(self, &lvi));
	inline void DeleteItem(int i) assertl_reflect_as(ListView_DeleteItem(self, i));
	inline void DeleteAllItem()  assertl_reflect_as(ListView_DeleteAllItems(self));

#pragma region Properties
public: 
	/* W */ inline bool UnicodeFormat() const reflect_as(ListView_GetUnicodeFormat(self));
	/* R */ inline auto &UnicodeFormat(bool bUnicode) assertl_reflect_as_self(ListView_SetUnicodeFormat(self, bUnicode));
public: 
	/* W */ inline auto &BkColor(DWORD rgb) assertl_reflect_as_self(ListView_SetBkColor(self, rgb));
	/* R */ inline bool BkColor() const reflect_as(ListView_GetBkColor(self));
public: 
public: 
	/* R */ inline auto ItemCount() const reflect_as(ListView_GetItemCount(self));
public: 
	/* W */ inline auto &Item(const ListViewItem &lvi) assertl_reflect_as_self(ListView_SetItem(self, &lvi));
	/* R */ inline auto Item() const assertl_reflect_to(ListViewItem lvi, ListView_GetItem(self, &lvi), lvi);
#pragma endregion
};
using ListView = ListViewBase<void>;
#pragma endregion

#pragma region Control TreeView
enum_flags(TreeViewStyle, WStyle,
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
#pragma endregion

#pragma region Control TabControl
enum_flags(TabControlStyle, WStyle,
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
#pragma endregion

#pragma region Control Animate
enum_flags(AnimateStyle, WStyle,
	Center              = ACS_CENTER,
	Transparent         = ACS_TRANSPARENT,
	AutoPlay            = ACS_AUTOPLAY,
	Timer               = ACS_TIMER);
#pragma endregion

#pragma region Control MonthCal
enum_flags(MonthCalStyle, WStyle,
	DayState          = MCS_DAYSTATE,
	MultiSelect       = MCS_MULTISELECT,
	WeekNumbers       = MCS_WEEKNUMBERS,
	NoTodayCircle     = MCS_NOTODAYCIRCLE,
	NoToday           = MCS_NOTODAY,
	NoTrailingDates   = MCS_NOTRAILINGDATES,
	ShortDaysOfWeek   = MCS_SHORTDAYSOFWEEK,
	NoSelChangeOnNav  = MCS_NOSELCHANGEONNAV);
#pragma endregion

#pragma region Control DateTimePick
enum_flags(DateTimePickStyle, WStyle,
	UpDown                 = DTS_UPDOWN,
	ShowNone               = DTS_SHOWNONE,
	ShortDateFormat        = DTS_SHORTDATEFORMAT,
	LongDateFormat         = DTS_LONGDATEFORMAT,
	ShortDateCenturyFormat = DTS_SHORTDATECENTURYFORMAT,
	TimeFormat             = DTS_TIMEFORMAT,
	AppCanParse            = DTS_APPCANPARSE,
	RightAlign             = DTS_RIGHTALIGN);
#pragma endregion

#pragma region Control Pager
enum_flags(PagerStyle, WStyle,
	Vert                = PGS_VERT,
	Horz                = PGS_HORZ,
	AutoScroll          = PGS_AUTOSCROLL,
	DragNDrop           = PGS_DRAGNDROP);
#pragma endregion

#pragma region Control NativeFont
enum_flags(NativeFontStyle, WStyle,
	Edit                = NFS_EDIT,
	Static              = NFS_STATIC,
	ListCombo           = NFS_LISTCOMBO,
	Button              = NFS_BUTTON,
	All                 = NFS_ALL,
	UseFontAssoc        = NFS_USEFONTASSOC);
#pragma endregion

#pragma region Control Button
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
	Flat             = BS_FLAT)
enum_flags(ButtonState, SHORT,
	Unchecked     = BST_UNCHECKED,
	Checked       = BST_CHECKED,
	Indeterminate = BST_INDETERMINATE,
	Pushed        = BST_PUSHED,
	Focus         = BST_FOCUS);
struct ButtonSplitInfo : public RefAs<BUTTON_SPLITINFO> {
	using super = RefAs<BUTTON_SPLITINFO>;
public:
	ButtonSplitInfo(){}
	ButtonSplitInfo(const BUTTON_SPLITINFO &bs) : super(bs) {}
public: 
	
public: 

public: 
	enum_flags(Style, UINT,
		NoSplit   = BCSS_NOSPLIT,
		Stretch   = BCSS_STRETCH,
		AlignLeft = BCSS_ALIGNLEFT,
		Image     = BCSS_IMAGE);
	/* W */ inline auto &Styles(Style style) reflect_to_self(self->uSplitStyle = style.yield());
	/* R */ inline Style Styles() const reflect_as(ref_as<Style>(self->uSplitStyle));
public: 
	/* W */ inline auto &Size(SIZE size) reflect_to_self(self->size = size);
	/* R */ inline LSize Size() const reflect_as(ref_as<LSize>(self->size));
};
struct ButtonImageList : public RefAs<BUTTON_IMAGELIST> {
	using super = RefAs<BUTTON_IMAGELIST>;
public:
	ButtonImageList() {}
public: 
	/* W */ inline auto &Margin(LRect margin) reflect_to_self(self->margin = margin);
	/* R */ inline LRect Margin() const reflect_as(self->margin);
public: 
	enum_class(Aligns, UINT, 
		Left     = BUTTON_IMAGELIST_ALIGN_LEFT,
		Right    = BUTTON_IMAGELIST_ALIGN_RIGHT,
		Top      = BUTTON_IMAGELIST_ALIGN_TOP,
		Bottom   = BUTTON_IMAGELIST_ALIGN_BOTTOM,
		Center   = BUTTON_IMAGELIST_ALIGN_CENTER);
	/* W */ inline auto   &Align(Aligns align) reflect_to_self(self->uAlign = align.yield());
	/* R */ inline Aligns  Align() const reflect_as(ref_as<Aligns>(self->uAlign));
};
BaseOf_CommCtl(class CtlBuuton) {
protected:
	SFINAE_CommCtl(CtlBuuton);
	def_memberof(wmailBox);
public:
	static constexpr auto CtlClassName = WC_BUTTON;
	using Child = KChain<CtlBuuton<AnyChild>, AnyChild>;
	using super = ControlCommon<Child>;
	using Style = ButtonStyle;
	using State = ButtonState;
	using BSplitInfo = ButtonSplitInfo;
	using BImageList = ButtonImageList;
public:
	CtlBuuton() {}

#pragma region Callback
protected:
#define MSG_TRANS(msgid, ret, name, ...) \
	def_memberof(name);
#define WX_BUTTON
#include "wx_msg_ctl.inl"
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
#include "wx_msg_ctl.inl"
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
public: 
	/* R */ inline LSize IdealSize() const assertl_reflect_to(LSize sz, Button_GetIdealSize(self, &sz), sz);
public: 
	/* W */ inline auto  &Note(LPCTSTR lpszNote) assertl_reflect_as_self(Button_SetNote(self, lpszNote));
	/* R */ inline String Note() const {
		auto len = Button_GetNoteLength(self);
		if (len <= 0) return O;
		String note = len;
		assertl(Button_GetNote(self, note, len + 1));
		return note;
	}
public: 
	/* W */ inline auto &TextMargin(RECT margin) assertl_reflect_as_self(Button_SetTextMargin(self, &margin));
	/* R */ inline LRect TextMargin() const assertl_reflect_to(LRect rc, Button_GetTextMargin(self, &rc), rc);
public: 
	/* W */ inline auto      &SplitInfo(BUTTON_SPLITINFO bsp) assertl_reflect_as_self(Button_SetSplitInfo(self, &bsp));
	/* R */ inline BSplitInfo SplitInfo() const assertl_reflect_to(BSplitInfo bsp, Button_GetSplitInfo(self, &bsp), bsp);
public: 
	/* W */ inline auto      &ImageList(BUTTON_IMAGELIST &iml) assertl_reflect_as_self(Button_SetImageList(self, &iml));
	/* R */ inline BImageList ImageList() const assertl_reflect_to(BImageList iml, Button_GetImageList(self, &iml), iml);



public: 
	/* W */ inline auto &Check(State s) reflect_to_self(super::Send(BM_SETCHECK, s.yield()));
	/* R */ inline State Check() const reflect_as(super::template Send<State>(BM_GETCHECK));
public: 
	/* W */ inline auto &States(State s) reflect_to_self(super::Send(BM_SETSTATE, s.yield()));
	/* R */ inline State States() const reflect_as(super::template Send<State>(BM_GETSTATE));
public: 
	/* W */ inline auto &Styles(Style style, bool bRedraw = true) reflect_to_self(super::Send(BM_SETSTYLE, style.yield(), bRedraw));
public: 
	/* W */ inline auto &DontClick(bool bDontClick) reflect_to_self(super::Send(BM_SETDONTCLICK, bDontClick));
#pragma endregion
};
#pragma endregion

#pragma region Static
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
public:
	static constexpr auto CtlClassName = WC_STATIC;
	using Child = KChain<StaticBase<AnyChild>, AnyChild>;
	using super = ControlCommon<Child>;
	using Style = StaticStyle;
public:
	StaticBase() {}
#pragma region Properties
public: 
	/* W */ inline auto &Icon(HICON hIcon) reflect_to_child(super::Send(STM_SETICON, hIcon));
	/* R */ inline CIcon Icon() const reflect_as(super::template Send<HICON>(STM_GETICON));
public: 
	/* W */ inline auto    &ImageBitmap() reflect_to_child(super::Send(STM_SETIMAGE, IMAGE_BITMAP));
	/* R */ inline CBitmap  ImageBitmap() const reflect_as(super::template Send<HBITMAP>(STM_GETIMAGE, IMAGE_BITMAP));
public: 
	/* W */ inline auto &ImageIcon(HICON hIcon) reflect_to_child(super::Send(STM_SETIMAGE, IMAGE_BITMAP));
	/* R */ inline CIcon ImageIcon() const reflect_as(super::template Send<HICON>(STM_GETIMAGE, IMAGE_BITMAP));
public: 
	/* W */ inline auto   &ImageCursor(HCURSOR hCursor) reflect_to_child(super::Send(STM_SETIMAGE, IMAGE_CURSOR, hCursor));
	/* R */ inline CCursor ImageCursor() const reflect_as(super::template Send<HCURSOR>(STM_GETIMAGE, IMAGE_CURSOR));
#pragma endregion
};
using Static = StaticBase<void>;
#pragma endregion

#pragma region Control Edit
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
public: 
	/* W */ inline auto &Title(LPCTSTR lpszTitle) reflect_to_self(this->pszTitle = lpszTitle);
	/* R */ inline const String Title() const reflect_as(CString(this->pszTitle, MaxLenTitle));
public: 
	/* W */ inline auto &Text(LPCTSTR lpszText) reflect_to_self(this->pszText = lpszText);
	/* R */ inline const String Text() const reflect_as(CString(this->pszText, MaxLenNotice));
public: 
	/* W */ inline auto &Icon(ToolTipIcons tti) reflect_to_self(this->ttiIcon = tti.yield());
	/* R */ inline ToolTipIcons Icon()const reflect_as(reuse_as<ToolTipIcons>(this->ttiIcon));
public:
	inline PEDITBALLOONTIP operator&() reflect_as(this);
	inline const EDITBALLOONTIP *operator&() const reflect_as(this);
};
BaseOf_CommCtl(class EditBase) {
protected:
	SFINAE_CommCtl(EditBase);
public:
	static constexpr auto CtlClassName = WC_EDIT;
	using super = ControlCommon<KChain<EditBase<AnyChild>, AnyChild>>;
	using Style = EditStyle;
	using Balloon = EditBalloonTip;
public:
	EditBase() {}

#pragma region Methods

	inline auto &ScrollCaret() reflect_to_child(super::Send(EM_SCROLLCARET));
	inline bool  LineScroll(int nLines) reflect_as(super::Send(EM_LINESCROLL, 0, nLines));
	inline auto &ReplaceSel(LPCTSTR lpString, bool bUndo = false) reflect_to_child(super::Send(EM_REPLACESEL, bUndo, lpString));
	inline bool  Undo() reflect_as(super::Send(EM_UNDO));
	inline auto &EmptyUndoBuffer() reflect_to_child(super::Send(EM_EMPTYUNDOBUFFER));

	inline auto&BalloonTip(const Balloon &tip) const assertl_reflect_as_self(Edit_ShowBalloonTip(self, &tip));
	inline auto&BalloonTip() const assertl_reflect_as_self(Edit_HideBalloonTip(self));

#pragma endregion

#pragma region Properties
public: 
	/* W */ inline auto &uSel(int to, int from) reflect_to_child(super::Send(EM_SETSEL, to, from));
	/* R */ inline auto  uSel() const reflect_to(struct { _M_(int to = 0, from = 0); } r; super::Send(EM_GETSEL, &r.from, &r.to), r);
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
public: 
	/* W */ inline auto  &CueBanner(LPCTSTR lpString, bool bFocused = false) reflect_to_child(Edit_SetCueBannerTextFocused(self, lpString, bFocused));
	/* R */ inline String CueBanner() const assertl_reflect_to(String cbt = MaxLenNotice, Edit_GetCueBannerText(self, cbt, MaxLenNotice + 1), cbt.Trunc());
public: 
	/* W */ inline auto &SearchWeb(bool bSearchWeb) reflect_to_child(Edit_EnableSearchWeb(self, bSearchWeb));
public: 
	/* W */ inline auto &CaretIndex(DWORD newCaretIndex) reflect_to_child(Edit_SetCaretIndex(self, newCaretIndex));
	/* R */ inline DWORD CaretIndex() const reflect_as(Edit_GetCaretIndex(self));
public: 
	/* W */ inline auto &Zoom(int Numerator, int Denominator) reflect_to_child(Edit_SetZoom(self, Numerator, Denominator));
	/* R */ inline auto  Zoom() const assertl_reflect_to(struct { _M_(int Numerator, Denominator); } z, Edit_GetZoom(self, &z.Numerator, &z.Denominator), z);
public: 
	/* R */ inline int FileLineIndex(int index) const reflect_as(Edit_GetFileLineIndex(self, index));
public: 
	/* R */ inline int FileLineLength(int nLine) const reflect_as(Edit_GetFileLineLength(self, nLine));
public: 
	/* R */ inline String FileLine(int nLine) const {
		auto len = FileLineLength(nLine);
		assertl(len > 0);
		if (len == 0) return O;
		String line(len);
		assertl(Edit_GetFileLine(self, nLine, line));
		return line;
	}
public: 
	/* R */ inline DWORD FileLineCount() const reflect_as(Edit_GetFileLineCount(self));
#pragma endregion
};
#pragma endregion

#pragma region Control ListBox
enum_flags(ListBoxStyle, WStyle,
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
#pragma endregion

#pragma region Control ComboBox
enum_flags(ComboBoxStyle, WStyle,
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
#pragma endregion

#pragma region Control ScrollBar
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
struct ScrollInfo : public RefAs<SCROLLINFO> {
	using super = RefAs<SCROLLINFO>;
public:
	ScrollInfo() reflect_to(self->cbSize = sizeof(SCROLLINFO));
public:
};
struct ScrollBarInfo : public RefAs<SCROLLBARINFO> {
	using super = RefAs<SCROLLBARINFO>;
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
protected:
	SFINAE_CommCtl(ScrollBarBase);
public:
	static constexpr auto CtlClassName = WC_SCROLLBAR;
	using super = ControlCommon<KChain<ScrollBarBase<AnyChild>, AnyChild>>;
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
