module;

#define WX_CPPM_WINDOW
#include "wx_window"

export module wx.window;

import wx.proto;
import wx.gdi;
import wx.resource;

export namespace WX {

#pragma region Atoms
class Atom {
	ATOM atom = 0;
public:
	Atom() {}
	Atom(Null) {}
	Atom(LPCSTR lpString) : atom(WX::AddAtom(lpString)) {}
	Atom(LPCWSTR lpString) : atom(WX::AddAtom(lpString)) {}
	Atom(ATOM atom) : atom(atom) {}
	~Atom() reflect_to(Delete());
public:
	static inline Atom Find(LPCSTR lpString) reflect_as(WX::FindAtom(lpString));
	static inline Atom Find(LPCWSTR lpString) reflect_as(WX::FindAtom(lpString));
	inline void Delete() reflect_to(if (atom) (WX::DeleteAtom(atom), atom = 0));
public: // Property - Name
	template<size_t MaxLen = MaxLenClass, bool IsUnicode = WX::IsUnicode>
	/* R */ inline StringX<IsUnicode> Name() const {
		StringX<IsUnicode> str(MaxLen);
		auto len = WX::GetAtomName(self, str, (int)MaxLen);
		return inject(str.Resize(len));
	}
	template<size_t MaxLen = MaxLenClass>
	/* R */ inline StringA NameA() const reflect_as(Name<MaxLen, false>());
	template<size_t MaxLen = MaxLenClass>
	/* R */ inline StringW NameW() const reflect_as(Name<MaxLen, true>());
public:
	inline operator bool() const reflect_as(atom);
	inline operator ATOM() const reflect_as(atom);
	inline operator LPCSTR() const reflect_as(MAKEINTRESOURCEA(atom));
	inline operator LPCWSTR() const reflect_as(MAKEINTRESOURCEW(atom));
};
using CAtom = RefAs<Atom>;
class GlobalAtom {
	ATOM atom = 0;
public:
	GlobalAtom() {}
	GlobalAtom(Null) {}
	GlobalAtom(LPCSTR lpString) : atom(Find(lpString)) {}
	GlobalAtom(LPCWSTR lpString) : atom(Find(lpString)) {}
	GlobalAtom(ATOM atom) : atom(atom) {}
	~GlobalAtom() reflect_to(Delete());
public:
	static inline RefAs<GlobalAtom> Find(LPCSTR lpString) reflect_as(WX::GlobalFindAtom(lpString));
	static inline RefAs<GlobalAtom> Find(LPCWSTR lpString) reflect_as(WX::GlobalFindAtom(lpString));
	inline void Delete() {
		if (atom)
			WX::GlobalDeleteAtom(atom);
		atom = 0;
	}
public: // Property - Name
	template<size_t MaxLen = MaxLenClass, bool IsUnicode = WX::IsUnicode>
	/* R */ inline StringX<IsUnicode> Name() const {
		StringX<IsUnicode> str(MaxLen);
		auto len = WX::GetAtomName(self, str, (int)MaxLen);
		return inject(str.Resize(len));
	}
	template<size_t MaxLen = MaxLenClass>
	/* R */ inline StringA NameA() const reflect_as(Name<MaxLen, false>());
	template<size_t MaxLen = MaxLenClass>
	/* R */ inline StringW NameW() const reflect_as(Name<MaxLen, true>());
public:
	inline operator bool() const reflect_as(atom);
	inline operator ATOM() const reflect_as(atom);
	inline operator LPCSTR() const reflect_as(MAKEINTRESOURCEA(atom));
	inline operator LPCWSTR() const reflect_as(MAKEINTRESOURCEW(atom));
};
using CGlobalAtom = RefAs<GlobalAtom>;
#pragma endregion

#pragma region Monitor
class MonitorInformations : public RefStruct<MONITORINFO> {
public:
	using super = RefStruct<MONITORINFO>;
public:
	MonitorInformations() reflect_to(self->cbSize = sizeof(MONITORINFO));
	MonitorInformations(const MONITORINFO &mi) : super(mi) {}
public: // Property - Rect
	/* W */ inline auto &Rect(const LRect &rc) reflect_to_self(self->rcMonitor = rc);
	/* R */ inline LRect Rect() const reflect_as(self->rcMonitor);
public: // Property - WorkRect
	/* W */ inline auto &WorkRect(const LRect &rc) reflect_to_self(self->rcWork = rc);
	/* R */ inline LRect WorkRect() const reflect_as(self->rcWork);
public: // Property - Primary
	/* W */ inline auto &Primary(bool bPrimary) reflect_to_self(self->dwFlags = bPrimary ? self->dwFlags | MONITORINFOF_PRIMARY : self->dwFlags & ~MONITORINFOF_PRIMARY);
	/* R */ inline bool  Primary() const reflect_as((self->dwFlags & MONITORINFOF_PRIMARY) != 0);
};
using MonitorInfo = MonitorInformations;
template<bool IsUnicode = WX::IsUnicode>
class MonitorInformationsExX : public RefStruct<structx(MONITORINFOEX)> {
	using MONITORINFOEX = std::conditional_t<IsUnicode, MONITORINFOEXW, MONITORINFOEXA>;
	using String = StringX<IsUnicode>;
public:
	using super = RefStruct<MONITORINFOEX>;
public:
	MonitorInformationsExX() reflect_to(self->cbSize = sizeof(MONITORINFOEX));
	MonitorInformationsExX(const MONITORINFOEX &mie) : super(mie) {}
public: // Property - Rect
	/* W */ inline auto &Rect(const LRect &rc) reflect_to_self(self->rcMonitor = rc);
	/* R */ inline LRect Rect() const reflect_as(self->rcMonitor);
public: // Property - WorkRect
	/* W */ inline auto &WorkRect(const LRect &rc) reflect_to_self(self->rcWork = rc);
	/* R */ inline LRect WorkRect() const reflect_as(self->rcWork);
public: // Property - Primary
	/* W */ inline auto &Primary(bool bPrimary) reflect_to_self(self->dwFlags = bPrimary ? self->dwFlags | MONITORINFOF_PRIMARY : self->dwFlags & ~MONITORINFOF_PRIMARY);
	/* R */ inline bool  Primary() const reflect_as((self->dwFlags &MONITORINFOF_PRIMARY) != 0);
public: // Property - DeviceName
	/* W */ inline auto &DeviceName(const String &name) reflect_to_self(WX::Copy(self->szDevice, name));
	/* R */ inline String DeviceName() const reflect_as(+CString(self->szDevice, CountOf(self->szDevice)));
public:
	inline operator MONITORINFO &() reflect_as(*(MONITORINFO *)this);
	inline operator MonitorInfo &() reflect_as(*(MonitorInfo *)this);
	inline operator MONITORINFO() const reflect_as(*(MONITORINFO *)this);
	inline operator MonitorInfo() const reflect_as(*(MonitorInfo *)this);
};
template<bool IsUnicode = WX::IsUnicode>
using MonitorInfoExX = MonitorInformationsExX<IsUnicode>;
using MonitorInformationsEx = MonitorInformationsExX<>;
using MonitorInformationsExA = MonitorInformationsExX<false>;
using MonitorInformationsExW = MonitorInformationsExX<true>;
using MonitorInfoEx = MonitorInformationsExX<>;
using MonitorInfoExA = MonitorInformationsExX<false>;
using MonitorInfoExW = MonitorInformationsExX<true>;
class Monitor {
	mutable HMONITOR hMonitor = O;
protected:
	INNER_USE(Monitor);
	Monitor(HMONITOR h) : hMonitor(h) {}
	Monitor(const Monitor &m) = delete;
public:
	Monitor() {}
	Monitor(Null) {}
public: // Property - Info
	/* R */ inline MonitorInfo Info() const reflect_to(MonitorInfo mi; WX::GetMonitorInfo(hMonitor, &mi), mi);
public: // Property - InfoEx
	template<bool IsUnicode = WX::IsUnicode>
	/* R */ inline MonitorInfoExX<IsUnicode> InfoEx() const reflect_to(MonitorInfoExX<IsUnicode> mie; WX::GetMonitorInfo<IsUnicode>(hMonitor, &mie), mie);
	/* R */ inline MonitorInfoExA InfoExA() const reflect_as(InfoEx<false>());
	/* R */ inline MonitorInfoExW InfoExW() const reflect_as(InfoEx<true>());
public:
	inline operator HMONITOR() const reflect_as(hMonitor);
};
#pragma endregion

#pragma region Desktop
class Desktop {
	mutable HDESK hDesk = O;
protected:
	INNER_USE(Desktop);
	Desktop(HDESK h) : hDesk(h) {}
	Desktop(const Desktop &d) = delete;
public:
	Desktop() {}
	Desktop(Null) {}
public:
	inline operator HDESK() const reflect_as(hDesk);
};
#pragma endregion

#pragma region WindowStation
class WindowStation {
	mutable HWINSTA hWinSta = O;
protected:
	INNER_USE(WindowStation);
	WindowStation(HWINSTA h) : hWinSta(h) {}
	WindowStation(const WindowStation &w) = delete;
public:
	WindowStation() {}
	WindowStation(Null) {}
public:
	inline operator HWINSTA() const reflect_as(hWinSta);
};
#pragma endregion

template<class AnyChild>
class WindowBase;
using Window = WindowBase<void>;
using CWindow = RefAs<Window>;
template<class AnyChild>
using WindowShim = RefAs<WindowBase<AnyChild>>;
template<class AnyChild>
using CWindowShim = RefAs<const WindowBase<AnyChild>>;

#pragma region Misc

struct KEY_FLAGS {
	uint16_t wScanCode : 8;
	uint16_t bExtend : 1;
	uint16_t ___reserved : 4;
	uint16_t bContext : 1;
	uint16_t bPrevious : 1;
	uint16_t bTranslated : 1;
};

class ScrollInfo : public RefStruct<SCROLLINFO> {
public:
	using super = RefStruct<SCROLLINFO>;
public:
	ScrollInfo() reflect_to(self.cbSize = sizeof(SCROLLINFO); self.fMask = SIF_ALL);
	ScrollInfo(const SCROLLINFO &si) : super(si) {}
public: // Property - Mask
	/* W */ inline auto&Mask(UINT fMask) reflect_to_self(self.fMask = fMask);
	/* R */ inline UINT Mask() const reflect_as(self.fMask);
public: // Property - Range
	/* W */ inline auto &Range(int nMin, int nMax) reflect_to_self(self.nMin = nMin, self.nMax = nMax, self.fMask = SIF_RANGE);
	/* R */ inline LSize Range() const reflect_as(LSize{ self.nMin, self.nMax });
public: // Property - Page
	/* W */ inline auto&Page(UINT nPage) reflect_to_self(self.nPage = nPage, self.fMask = SIF_PAGE);
	/* R */ inline UINT Page() const reflect_as(self.nPage);
public: // Property - Position
	/* W */ inline auto&Position(int nPos) reflect_to_self(self.nPos = nPos, self.fMask = SIF_POS);
	/* R */ inline int  Position() const reflect_as(self.nPos);
public: // Property - TrackPosition
	/* W */ inline auto&TrackPosition(int nTrackPos) reflect_to_self(self.nTrackPos = nTrackPos, self.fMask = SIF_TRACKPOS);
	/* R */ inline int  TrackPosition() const reflect_as(self.nTrackPos);
};

enum_class(DPIHostingBehavior, DPI_HOSTING_BEHAVIOR,
	Invalid = DPI_HOSTING_BEHAVIOR_INVALID,
	Default = DPI_HOSTING_BEHAVIOR_DEFAULT,
	Mixed   = DPI_HOSTING_BEHAVIOR_MIXED);

#pragma region Window Styles
enum_class(DisplayAffinities, DWORD,
	None           = WDA_NONE,
	Monitor        = WDA_MONITOR,
	Exclusion      = WDA_EXCLUDEFROMCAPTURE);

enum_flags(WindowStyle, LONG,
	Overlapped          = WS_OVERLAPPED,
	Popup               = WS_POPUP,
	Child               = WS_CHILD,
	Minimize            = WS_MINIMIZE,
	Maximize            = WS_MAXIMIZE,
	MinimizeBox         = WS_MINIMIZEBOX,
	MaximizeBox         = WS_MAXIMIZEBOX,
	SizeBox             = WS_SIZEBOX,
	Visible             = WS_VISIBLE,
	Disabled            = WS_DISABLED,
	ClipSiblings        = WS_CLIPSIBLINGS,
	ClipChildren        = WS_CLIPCHILDREN,
	Caption             = WS_CAPTION,
	Border              = WS_BORDER,
	DlgFrame            = WS_DLGFRAME,
	VScroll             = WS_VSCROLL,
	HScroll             = WS_HSCROLL,
	SysMenu             = WS_SYSMENU,
	ThickFrame          = WS_THICKFRAME,
	Group               = WS_GROUP,
	TabStop             = WS_TABSTOP,
	Tiled               = WS_TILED,
	Iconic              = WS_ICONIC,
	TiledWindow         = WS_TILEDWINDOW,
	PopupWindow         = WS_POPUPWINDOW,
	OverlappedWindow    = WS_OVERLAPPEDWINDOW);
using WS = WindowStyle;
using WStyle = WindowStyle;
enum_flags(WindowStyleEx, DWORD,
	No                  = 0,
	DlgModalFrame       = WS_EX_DLGMODALFRAME,
	NoParentNotify      = WS_EX_NOPARENTNOTIFY,
	TopMost             = WS_EX_TOPMOST,
	AcceptFiles         = WS_EX_ACCEPTFILES,
	Transparent         = WS_EX_TRANSPARENT,
	MdiChild            = WS_EX_MDICHILD,
	ToolWindow          = WS_EX_TOOLWINDOW,
	WindowEdge          = WS_EX_WINDOWEDGE,
	ClientEdge          = WS_EX_CLIENTEDGE,
	ContextHelp         = WS_EX_CONTEXTHELP,
	Right               = WS_EX_RIGHT,
	Left                = WS_EX_LEFT,
	ReadingR2L          = WS_EX_RTLREADING,
	ReadingL2R          = WS_EX_LTRREADING,
	LeftScrollBar       = WS_EX_LEFTSCROLLBAR,
	RightScrollBar      = WS_EX_RIGHTSCROLLBAR,
	ControlParent       = WS_EX_CONTROLPARENT,
	StaticEdge          = WS_EX_STATICEDGE,
	AppWindow           = WS_EX_APPWINDOW,
	Layered             = WS_EX_LAYERED,
	NoInheritLayout     = WS_EX_NOINHERITLAYOUT,
	NoRedirectionBitmap = WS_EX_NOREDIRECTIONBITMAP,
	LayoutR2L           = WS_EX_LAYOUTRTL,
	Composited          = WS_EX_COMPOSITED,
	NoActivate          = WS_EX_NOACTIVATE,
	OverlappedWindow    = WS_EX_OVERLAPPEDWINDOW,
	PaletteWindow       = WS_EX_PALETTEWINDOW);
using WSEX = WindowStyleEx;
using WStyleEx = WindowStyleEx;
#pragma endregion

enum_flags(WindowPosFlag, UINT,
	NoSize              = SWP_NOSIZE,
	NoMove              = SWP_NOMOVE,
	NoZOrder            = SWP_NOZORDER,
	NoRedraw            = SWP_NOREDRAW,
	NoActivate          = SWP_NOACTIVATE,
	FrameChanged        = SWP_FRAMECHANGED,
	ShowWindow          = SWP_SHOWWINDOW,
	HideWindow          = SWP_HIDEWINDOW,
	NoCopyBits          = SWP_NOCOPYBITS,
	NoOwnerZOrder       = SWP_NOOWNERZORDER,
	NoSendChanging      = SWP_NOSENDCHANGING,
	DeferErase          = SWP_DEFERERASE,
	AsyncWindowPos      = SWP_ASYNCWINDOWPOS,
	DrawFrame           = SWP_DRAWFRAME,
	NoReposition        = SWP_NOREPOSITION);
using SWP = WindowPosFlag;

class FlashInfo : public RefStruct<FLASHWINFO> {
public:
	using super = RefStruct<FLASHWINFO>;
public:
	FlashInfo(HWND hwnd = O) reflect_to(self.cbSize = sizeof(cbSize); self.hwnd = hwnd);
	FlashInfo(const FLASHWINFO &f) : super(f) {}
public: // Property - Window
	/* W */ inline auto&Window(HWND hwnd) reflect_to_self(self.hwnd = hwnd);
public: // Flags
	inline auto &Stop() reflect_to_self(self.dwFlags  = FLASHW_STOP);
	inline auto &Caption() reflect_to_self(self.dwFlags |= FLASHW_CAPTION);
	inline auto &Tray() reflect_to_self(self.dwFlags |= FLASHW_TRAY);
	inline auto &All() reflect_to_self(self.dwFlags |= FLASHW_ALL);
	inline auto &Timer() reflect_to_self(self.dwFlags |= FLASHW_TIMER);
	inline auto &TillForeground() reflect_to_self(self.dwFlags |= FLASHW_TIMERNOFG);
public: // Property - Count
	/* W */ inline auto&Count(UINT uCount) reflect_to_self(self.uCount = uCount);
	/* R */ inline auto Count() const reflect_as(self.uCount);
public: // Property - Timeout
	/* W */ inline auto&Timeout(DWORD dwTimeout) reflect_to_self(self.dwTimeout = dwTimeout);
	/* R */ inline auto Timeout() const reflect_as(self.dwTimeout);
};

enum_flags(SysState, DWORD,
	Unavailable         = STATE_SYSTEM_UNAVAILABLE,
	Selected            = STATE_SYSTEM_SELECTED,
	Focused             = STATE_SYSTEM_FOCUSED,
	Pressed             = STATE_SYSTEM_PRESSED,
	Checked             = STATE_SYSTEM_CHECKED,
	Mixed               = STATE_SYSTEM_MIXED,
	Indeterminate       = STATE_SYSTEM_INDETERMINATE,
	ReadOnly            = STATE_SYSTEM_READONLY,
	HotTracked          = STATE_SYSTEM_HOTTRACKED,
	Default             = STATE_SYSTEM_DEFAULT,
	Expanded            = STATE_SYSTEM_EXPANDED,
	Collapsed           = STATE_SYSTEM_COLLAPSED,
	Busy                = STATE_SYSTEM_BUSY,
	Floating            = STATE_SYSTEM_FLOATING,
	Marqueed            = STATE_SYSTEM_MARQUEED,
	Animated            = STATE_SYSTEM_ANIMATED,
	Invisible           = STATE_SYSTEM_INVISIBLE,
	OffScreen           = STATE_SYSTEM_OFFSCREEN,
	Sizeable            = STATE_SYSTEM_SIZEABLE,
	Moveable            = STATE_SYSTEM_MOVEABLE,
	SelfVoicing         = STATE_SYSTEM_SELFVOICING,
	Focusable           = STATE_SYSTEM_FOCUSABLE,
	Selectable          = STATE_SYSTEM_SELECTABLE,
	Linked              = STATE_SYSTEM_LINKED,
	Traversed           = STATE_SYSTEM_TRAVERSED,
	MultiSelectable     = STATE_SYSTEM_MULTISELECTABLE,
	ExtSelectable       = STATE_SYSTEM_EXTSELECTABLE,
	AlertLow            = STATE_SYSTEM_ALERT_LOW,
	AlertMedium         = STATE_SYSTEM_ALERT_MEDIUM,
	AlertHigh           = STATE_SYSTEM_ALERT_HIGH,
	Protected           = STATE_SYSTEM_PROTECTED,
	Valid               = STATE_SYSTEM_VALID);

class TitleBarInfo : public RefStruct<TITLEBARINFO> {
public:
	using super = RefStruct<TITLEBARINFO>;
public:
	TitleBarInfo() reflect_to(self.cbSize = sizeof(TITLEBARINFO));
	TitleBarInfo(const TITLEBARINFO &t) : super(t) {}
public: // Property - Rect
	/* W */ inline auto& Rect(const LRect &r) reflect_to_self(self.rcTitleBar = r);
	/* R */ inline LRect Rect() reflect_as(self.rcTitleBar);
public: // Property - TitleState
	/* W */ inline auto&TitleState(SysState state) reflect_to_self(self.rgstate[0] = state.yield());
	/* R */ inline auto TitleState() const reflect_as(reuse_as<SysState>(self.rgstate[0]));
public: // Property - MinButtonState
	/* W */ inline auto&MinButtonState(SysState state) reflect_to_self(self.rgstate[2] = state.yield());
	/* R */ inline auto MinButtonState() const reflect_as(reuse_as<SysState>(self.rgstate[2]));
public: // Property - MaxButtonState
	/* W */ inline auto&MaxButtonState(SysState state) reflect_to_self(self.rgstate[3] = state.yield());
	/* R */ inline auto MaxButtonState() const reflect_as(reuse_as<SysState>(self.rgstate[3]));
public: // Property - HelpButtonState
	/* W */ inline auto&HelpButtonState(SysState state) reflect_to_self(self.rgstate[4] = state.yield());
	/* R */ inline auto HelpButtonState() const reflect_as(reuse_as<SysState>(self.rgstate[4]));
public: // Property - CloseButtonState
	/* W */ inline auto&CloseButtonState(SysState state) reflect_to_self(self.rgstate[5] = state.yield());
	/* R */ inline auto CloseButtonState() const reflect_as(reuse_as<SysState>(self.rgstate[5]));
};

class WindowPosition : public RefStruct<WINDOWPOS> {
public:
	using super = RefStruct<WINDOWPOS>;
	using Flag = WindowPosFlag;
public:
	WindowPosition() {}
	WindowPosition(const WINDOWPOS &w) : super(w) {}
public: // Property - Window
	/* W */ inline auto&Window(HWND hwnd) reflect_as(self->hwnd = hwnd);
	template<class AnyChild = void>
	/* R */ inline WindowShim<AnyChild> Window() reflect_as(self->hwnd);
	template<class AnyChild = void>
	/* R */ inline CWindowShim<AnyChild> Window() const reflect_as(self->hwnd);
public: // Property - WindowInsertAfter
	/* W */ inline auto &WindowInsertAfter(HWND hwndInsertAfter) reflect_to_self(self->hwndInsertAfter = hwndInsertAfter);
	template<class AnyChild = void>
	/* R */ inline WindowShim<AnyChild> WindowInsertAfter() reflect_as(self->hwndInsertAfter);
	template<class AnyChild = void>
	/* R */ inline CWindowShim<AnyChild> WindowInsertAfter() const reflect_as(self->hwndInsertAfter);
public: // Property - Position
	/* W */ inline auto  &Position(LPoint p) reflect_to_self(self->x = p.x, self->y = p.y);
	/* R */ inline LPoint Position() const reflect_as({ self->x, self->y });
public: // Property - Size
	/* W */ inline auto &Size(LSize s) reflect_to_self(self->cx = s.cx, self->cy = s.cy);
	/* R */ inline LSize Size() const reflect_as({ self->cx, self->cy });
public: // Property - Rect
	/* W */ inline auto &Rect(const LRect &r) reflect_to_self(Size(r), Position(r.left_top()));
	/* R */ inline LRect Rect() const reflect_as(LRect::left_top(Position(), Size()));
public: // Property - Flags
	/* W */ inline auto&Flags(Flag flags) reflect_to_self(self->flags = flags.yield());
	/* R */ inline Flag Flags() const reflect_as(reuse_as<Flag>(self->flags));
public:
} ;
using WndPos = WindowPosition;
using WindowPos = WindowPosition;

class WindowPlacement : public RefStruct<WINDOWPLACEMENT> {
public:
	using super = RefStruct<WINDOWPLACEMENT>;
public:
	WindowPlacement() reflect_to(self->length = sizeof(WINDOWPLACEMENT));
public:// Property - SetMinPosition
	/* W */ inline auto&SetMinPosition(bool bEnabled) reflect_to_self(if (bEnabled) self->flags |= WPF_SETMINPOSITION; else self->flags &= ~WPF_SETMINPOSITION);
	/* R */ inline bool SetMinPosition() const reflect_as(self->flags & WPF_SETMINPOSITION);
public:// Property - RestoreToMaximized
	/* W */ inline auto&RestoreToMaximized(bool bEnabled) reflect_to_self(if (bEnabled) self->flags |= WPF_RESTORETOMAXIMIZED; else self->flags &= ~WPF_RESTORETOMAXIMIZED);
	/* R */ inline bool RestoreToMaximized() const reflect_as(self->flags & WPF_RESTORETOMAXIMIZED);
public:// Property - Async
	/* W */ inline auto&Async(bool bEnabled) reflect_to_self(if (bEnabled) self->flags |= WPF_ASYNCWINDOWPLACEMENT; else self->flags &= ~WPF_ASYNCWINDOWPLACEMENT);
	/* R */ inline bool Async() const reflect_as(self->flags & WPF_ASYNCWINDOWPLACEMENT);
public: // Property - ShowFlags
	/* W */ inline auto&ShowFlags(SW flags) reflect_to_self(self->showCmd = flags.yield());
	/* S */ inline auto&ShowFlags() reflect_as(ref_as<SW>(self->showCmd));
	/* R */ inline auto ShowFlags() const reflect_as(reuse_as<SW>(self->showCmd));
public: // Property - MinPosition
	/* W */ inline auto&MinPosition(LPoint ptMinPosition) reflect_to_self(self->ptMinPosition = ptMinPosition);
	/* S */ inline auto&MinPosition() reflect_as(ref_as<LPoint>(self->ptMinPosition));
	/* R */ inline LPoint MinPosition() const reflect_as(self->ptMinPosition);
public: // Property - MaxPosition
	/* W */ inline auto&MaxPosition(LPoint ptMaxPosition) reflect_to_self(self->ptMaxPosition = ptMaxPosition);
	/* S */ inline auto&MaxPosition() reflect_as(ref_as<LPoint>(self->ptMaxPosition));
	/* R */ inline LPoint MaxPosition() const reflect_as(self->ptMaxPosition);
public: // Property - NormalPosition
	/* W */ inline auto&NormalPosition(LRect rcNormalPosition) reflect_to_self(self->rcNormalPosition = rcNormalPosition);
	/* S */ inline auto&NormalPosition() reflect_as(ref_as<LRect>(self->rcNormalPosition));
	/* R */ inline LRect NormalPosition() const reflect_as(self->rcNormalPosition);
};

class WindowInformation : public RefStruct<WINDOWINFO> {
public:
	using super = RefStruct<WINDOWINFO>;
public:
	WindowInformation() reflect_to(self->cbSize = sizeof(WINDOWINFO));
public: // Property - Rect
	/* W */ inline auto&Rect(LRect rc) reflect_to_self(self->rcWindow = rc);
	/* R */ inline LRect Rect() const reflect_as(self->rcWindow);
public: // Property - Client
	/* W */ inline auto&ClientRect(LRect rc) reflect_to_self(self->rcClient = rc);
	/* R */ inline LRect ClientRect() const reflect_as(self->rcClient);
public: // Property - Styles
	template<class AnyFlags = WS>
	/* R */ inline auto&Styles(AnyFlags styles) reflect_to_self(self->dwStyle = styles.yield());
	template<class AnyFlags = WS>
	/* R */ inline AnyFlags Styles() const reflect_as(reuse_as<AnyFlags>(self->dwStyle));
public: // Property - StylesEx
	template<class AnyFlags = WSEX>
	/* W */ inline auto&StylesEx(AnyFlags styles) reflect_to_self(self->dwExStyle = styles.yield());
	template<class AnyFlags = WSEX>
	/* R */ inline AnyFlags StylesEx() const reflect_as(reuse_as<AnyFlags>(self->dwExStyle));
public: // Property - Status
	/* W */ inline auto &Status(DWORD dwStatus) reflect_to_self(self->dwWindowStatus = dwStatus);
	/* R */ inline DWORD Status() const reflect_as(self->dwWindowStatus);
public: // Property - Borders
	/* W */ inline auto  &Borders(LPoint border) reflect_to_self(self->cxWindowBorders = border.x, self->cyWindowBorders = border.y);
	/* R */ inline LPoint Borders() const reflect_as({ (LONG)self->cxWindowBorders, (LONG)self->cyWindowBorders });
public: // Property - ClassAtom
	/* W */ inline auto&ClassAtom(ATOM atom) reflect_to_self(self->atomWindowType = atom);
	/* R */ inline ATOM ClassAtom() const reflect_as(self->atomWindowType);
public: // Property - CreatorVersion
	/* W */ inline auto&CreatorVersion(WORD wCreatorVersion) reflect_to_self(self->wCreatorVersion = wCreatorVersion);
	/* R */ inline WORD CreatorVersion() const reflect_as(self->wCreatorVersion);
};
using WindowInfo = WindowInformation;

class WindowProcedure {
	WNDPROC pfnWndProc = O;
public:
	WindowProcedure() {}
	WindowProcedure(WNDPROC pfnWndProc) : pfnWndProc(pfnWndProc) {}
public:
	template<bool IsUnicode = WX::IsUnicode>
	inline LRESULT Call(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) const reflect_as(CallWindowProc<IsUnicode>(pfnWndProc, hWnd, Msg, wParam, lParam));
public:
	inline LRESULT operator()(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) const reflect_as(Call(hWnd, Msg, wParam, lParam));
public:
	inline operator bool() const reflect_as(pfnWndProc);
	inline operator WNDPROC() const reflect_as(pfnWndProc);
};
using WndProc = WindowProcedure;

enum_flags(TrackMouseFlag, DWORD,
	Hover    = TME_HOVER,
	Leave    = TME_LEAVE,
	NoClient = TME_NONCLIENT,
	Query    = TME_QUERY,
	Cancel   = TME_CANCEL);
class TrackMouseEventBox : public RefStruct<TRACKMOUSEEVENT> {
public:
	using super = RefStruct<TRACKMOUSEEVENT>;
	using Flag = TrackMouseFlag;
public:
	TrackMouseEventBox(HWND hWnd) reflect_to(
		self->cbSize = sizeof(TRACKMOUSEEVENT);
		self->hwndTrack = hWnd);
public: // Property - HoverTime
	/* W */ inline auto &HoverTime(DWORD dwHoverTime) reflect_to_self(self->dwHoverTime = dwHoverTime);
	/* R */ inline DWORD HoverTime() const reflect_as(self->dwHoverTime);
public: // Property - Flags
	/* W */ inline auto&Flags(Flag flag) reflect_to_self(self->dwFlags = flag.yield());
	/* R */ inline Flag Flags() const reflect_as(ref_as<Flag>(self->dwFlags));
public:
	inline void Track() reflect_to(WX::TrackMouseEvent(this));
};
using TME = TrackMouseEventBox;

#pragma endregion

#pragma region WindowClass
enum_flags(ClassStyle, UINT,
	VRedraw            = CS_VREDRAW,
	HRedraw            = CS_HREDRAW,
	Redraw             = CS_VREDRAW | CS_HREDRAW,
	DoubleClick        = CS_DBLCLKS,
	OwnDC              = CS_OWNDC,
	ClassDC            = CS_CLASSDC,
	ParentDC           = CS_PARENTDC,
	NoClose            = CS_NOCLOSE,
	SaveBits           = CS_SAVEBITS,
	ByteAlignClient    = CS_BYTEALIGNCLIENT,
	ByteAlignWindow    = CS_BYTEALIGNWINDOW,
	GlobalClass        = CS_GLOBALCLASS,
	IME                = CS_IME,
	DropShadow         = CS_DROPSHADOW);
using CStyle = ClassStyle;
template<class WNDCLASS, class AnyChild>
class WindowClassBase : public RefStruct<WNDCLASS>,
	public ChainExtender<WindowClassBase<WNDCLASS, AnyChild>, AnyChild> {
	locale_charmode(std::is_same_v<_M_(WNDCLASS, WNDCLASSW)> || std::is_same_v<_M_(WNDCLASS, WNDCLASSEXW)>);
	using LPCTSTR = LPCXSTR<IsUnicode>;
	using String = StringX<IsUnicode>;
public:
	using super = RefStruct<WNDCLASS>;
	using Child = AnyChild;
	using Style = CStyle;
public:
	WindowClassBase() {}
	WindowClassBase(const WNDCLASS &wc) : super(wc) {}
public: // Property - Styles
	/* W */ inline auto&Styles(Style style) reflect_to_child(self->style = style.yield());
	/* R */ inline auto Styles() const reflect_as(ref_as<Style>(self->style));
public: // Property - WndProc
	/* W */ inline auto&WndProc(WNDPROC lpfnWndProc) reflect_to_child(self->lpfnWndProc = lpfnWndProc);
	/* R */ inline WX::WndProc WndProc() const reflect_as(self->lpfnWndProc);
public: // Property - ClsExtra
	/* W */ inline auto&ClsExtra(int cbClsExtra) reflect_to_child(self->cbClsExtra = cbClsExtra);
	/* R */ inline auto ClsExtra() const reflect_as(self->cbClsExtra);
public: // Property - WndExtra
	/* W */ inline auto&WndExtra(int cbWndExtra) reflect_to_child(self->cbWndExtra = cbWndExtra);
	/* R */ inline auto WndExtra() const reflect_as(self->cbWndExtra);
public: // Property - Module
	/* W */ inline auto&Module(HINSTANCE hModule) reflect_to_child(self->hInstance = hModule);
	/* R */ inline CModule Module() const reflect_as(self->hInstance);
public: // Property - Icon
	/* W */ inline auto&Icon(CIcon icon) reflect_to_child(self->hIcon = icon);
	/* W */ inline auto&Icon(LPCTSTR lpszName) reflect_to_child(self->hIcon = Module()->Icon(lpszName));
	/* W */ inline auto&Icon(WORD wID) reflect_to_child(self->hIcon = Module()->Icon(wID));
	/* R */ inline CIcon Icon() const reflect_as(self->hIcon);
public: // Property - Cursor
	/* W */ inline auto&Cursor(CCursor cursor) reflect_to_child(self->hCursor = cursor);
	/* W */ inline auto&Cursor(LPCTSTR lpszName) reflect_to_child(self->hCursor = Module()->Cursor(lpszName));
	/* W */ inline auto&Cursor(WORD wID) reflect_to_child(self->hCursor = Module()->Cursor(wID));
	/* R */ inline CCursor Cursor() const reflect_as(self->hCursor);
public: // Property - Background
	/* W */ inline auto&Background(CBrush brush) reflect_to_child(self->hbrBackground = brush);
	/* R */ inline CBrush Background() const reflect_as(self->hbrBackground);
public: // Property - Menu
	/* W */ inline auto&Menu(LPCTSTR lpszMenuName) reflect_to_child(self->lpszMenuName = lpszMenuName);
	/* W */ inline auto&Menu(WORD wID) reflect_to_child(self->lpszMenuName = (LPCTSTR)MAKEINTRESOURCE(wID));
public: // Property - MenuName
	template<size_t MaxLen = MaxLenPath>
	/* R */ inline const String MenuName() const reflect_as(CString(self->lpszMenuName, MaxLen));
public: // Property - Name
	/* W */ inline auto&Name(LPCTSTR lpszClassName) reflect_to_child(self->lpszClassName = lpszClassName);
	template<size_t MaxLen = MaxLenClass>
	/* R */ inline String Name() const {
		auto_stringx(fmt, "#%d");
		if (!self->lpszClassName)
			return O;
		if (IS_INTRESOURCE(self->lpszClassName))
			return format(fmt, (ATOM)(ULONG_PTR)self->lpszClassName);
		return CString(self->lpszClassName, MaxLen);
	}
public: // Property - Atom
	/* W */ inline auto&Atom(ATOM classAtom) reflect_to_child(self->lpszClassName = (LPCTSTR)MAKEINTRESOURCE(classAtom));
	/* R */ inline ATOM Atom() const reflect_as(IS_INTRESOURCE(self->lpszClassName) ? (ATOM)(ULONG_PTR)self->lpszClassName : 0);
public:
	inline ATOM Register() const reflect_as(WX::RegisterClass(&self));
	inline void Unregister() const reflect_as(WX::UnregisterClass(self->lpszClassName, self->hInstance));
};
template<bool IsUnicode>
class WindowClassX : public WindowClassBase<structx(WNDCLASS), WindowClassX<IsUnicode>> {
	using WNDCLASS = structx(WNDCLASS);
public:
	using super = WindowClassBase<WNDCLASS, WindowClassX>;
public:
	WindowClassX() {}
	WindowClassX(const WindowClassX &wc) : super(wc) {}
	WindowClassX(const WNDCLASS &wc) : super(wc) {}
};
using WindowClass = WindowClassX<IsUnicode>;
using WindowClassA = WindowClassX<false>;
using WindowClassW = WindowClassX<true>;
template<bool IsUnicode>
class WindowClassExX : public WindowClassBase<structx(WNDCLASSEX), WindowClassExX<IsUnicode>> {
	using_structx(WNDCLASSEX);
	using LPCTSTR = LPCXSTR<IsUnicode>;
	using String = StringX<IsUnicode>;
public:
	using super = WindowClassBase<WNDCLASSEX, WindowClassExX>;
public:
	WindowClassExX() reflect_to(self->cbSize = (int)sizeof(WNDCLASSEX));
	WindowClassExX(const WindowClassExX &wc) : super(wc) {}
	WindowClassExX(const WNDCLASSEX &wc) : super(wc) {}
public: // Property - IconSmall
	/* W */ inline auto &IconSmall(HICON hIconSm) reflect_to_self(self->hIconSm = hIconSm);
	/* W */ inline auto &IconSmall(LPCTSTR lpszName) reflect_to_self(self->hIconSm = this->Module()->Icon(lpszName));
	/* W */ inline auto &IconSmall(WORD wID) reflect_to_self(self->hIconSm = this->Module()->Icon(wID));
	/* R */ inline CIcon IconSmall() const reflect_as(self->hIconSm);
};
using WindowClassEx = WindowClassExX<IsUnicode>;
using WindowClassExA = WindowClassExX<false>;
using WindowClassExW = WindowClassExX<true>;
#pragma endregion

#pragma region CreateStruct
template<bool IsUnicode, class Style = WStyle, class StyleEx = WStyleEx>
class CreateStructX : public RefStruct<structx(CREATESTRUCT)> {
	using_structx(CREATESTRUCT);
	using_structx(WNDCLASS);
	using_structx(WNDCLASSEX);
	using LPCTSTR = LPCXSTR<IsUnicode>;
	using String = StringX<IsUnicode>;
public:
	using super = RefStruct<CREATESTRUCT>;
public:
	CreateStructX() {}
	CreateStructX(const CREATESTRUCT &cs) : super(cs) {}
public: // Property - Param
	/* W */ inline auto&Param(LPVOID lpCreateParams) reflect_to_self(self->lpCreateParams = lpCreateParams);
	template<class AnyType = void>
	/* R */ inline AnyType *Param() const reflect_as((AnyType *)self->lpCreateParams);
public: // Property - Module
	/* W */ inline auto   &Module(HINSTANCE hInstance) reflect_to_self(self->hInstance = hInstance);
	/* R */ inline CModule Module() const reflect_as(self->hInstance);
public: // Property - Menu
	/* W */ inline auto &Menu(HMENU hMenu) reflect_to_self(self->hMenu = hMenu);
	/* R */ inline CMenu Menu() const reflect_as(self->hMenu);
public: // Property - ID
	/* W */ inline auto &ID(UINT uID) reflect_to_self(self->hMenu = small_cast<HMENU>(uID));
	/* R */ inline UINT ID() const reflect_as(small_cast<HMENU>(self->hMenu));
public: // Property - Parent
	/* W */ inline auto&Parent(HWND hwndParent) reflect_to_self(self->hwndParent = hwndParent);
	template<class AnyChild = void>
	/* R */ inline WindowShim<AnyChild> Parent() reflect_as(self->hwndParent);
	template<class AnyChild = void>
	/* R */ inline CWindowShim<AnyChild> Parent() const reflect_as(self->hwndParent);
public: // Property - Styles
	/* W */ inline auto &Styles(Style style) reflect_to_self(self->style = style.yield());
	/* R */ inline Style Styles() const reflect_as(ref_as<Style>(self->style));
public: // Property - Caption
	/* W */ inline auto  &Caption(LPCTSTR name) reflect_to_self(self->lpszName = name);
	/* R */ inline String Caption() const reflect_as(CString(self->lpszName, MaxLenTitle));
public: // Property - Class
	/* W */ inline auto&Class(LPCTSTR lpszClassName) reflect_to_self(self->lpszClass = lpszClassName);
	/* W */ inline auto&Class(ATOM classAtom) reflect_to_self(self->lpszClass = (LPCTSTR)MAKEINTRESOURCE(classAtom));
	/* W */ inline auto&Class(const WNDCLASS &wc) reflect_to_self(self->lpszClass = wc.lpszClassName);
public: // Property - ClassName
	/* W */ inline auto &ClassName(LPCTSTR lpszClassName) reflect_to_self(self->lpszClass = lpszClassName);
	template<size_t MaxLen = MaxLenClass>
	/* R */ inline String ClassName() const {
		if (!self->lpszClass)
			return O;
		if (IS_INTRESOURCE(self->lpszClass))
			return format("#%d", (ATOM)(ULONG_PTR)self->lpszClass);
		return CString(self->lpszClass, MaxLen);
	}
public: // Property - ClassAtom
	/* W */ inline auto&ClassAtom(ATOM classAtom) reflect_to_self(self->lpszClass = (LPCTSTR)MAKEINTRESOURCE(classAtom));
	/* R */ inline ATOM ClassAtom() const reflect_as(IS_INTRESOURCE(self->lpszClass) ? (ATOM)(ULONG_PTR)self->lpszClass : 0);
public: // Property - StylesEx
	/* W */ inline auto   &StylesEx(StyleEx dwExStyle) reflect_to_self(self->dwExStyle = dwExStyle.yield());
	/* R */ inline StyleEx StylesEx() const reflect_as(ref_as<StyleEx>(self->dwExStyle));
public: // Property - Size
	/* W */ inline auto &Size(LSize size) reflect_to_self(self->cx = size.cx, self->cy = size.cy);
	/* R */ inline LSize Size() const reflect_as({ self->cx, self->cy });
public: // Property - Position
	/* W */ inline auto  &Position(LPoint pos) reflect_to_self(self->x = pos.x, self->y = pos.y);
	/* R */ inline LPoint Position() const reflect_as({ self->x, self->y });
public: // Property - Rect
	/* W */ inline auto &Rect(LRect r) reflect_to_self(Size(r), Position(r.left_top()));
	/* R */ inline LRect Rect() const reflect_as(LRect::left_top(Position(), Size()));
public: // Property - ClientRect
	/* W */ inline auto&ClientRect(LRect rc) reflect_to_self(WX::AdjustWindowRect(&rc, self->style, self->hMenu, self->dwExStyle), Rect(rc));
	/* W */ inline auto&ClientRect(LRect rc, UINT dpi) reflect_to_self(WX::AdjustWindowRectForDpi(&rc, self->style, self->hMenu, self->dwExStyle, dpi), Rect(rc));
public: // Property - ClientSize
	/* W */ inline auto&ClientSize(LSize sz) reflect_as(ClientRect(LRect::left_top(Position(), sz)));
	/* W */ inline auto&ClientSize(LSize sz, UINT dpi) reflect_as(ClientRect(LRect::left_top(Position(), sz), dpi));
public:
	template <class AnyChild = void>
	inline WindowShim<AnyChild> Create() const reflect_as(
		WX::CreateWindow(
			self->dwExStyle, self->lpszClass, self->lpszName, self->style,
			self->x, self->y, self->cx, self->cy,
			self->hwndParent, self->hMenu, self->hInstance,
			self->lpCreateParams));
	template <class AnyChild = void>
	inline WindowShim<AnyChild> CreateMDI() const reflect_as(WX::CreateMDIWindow(
		self->dwExStyle, self->lpszClass, self->lpszName, self->style,
		self->x, self->y, self->cx, self->cy,
		self->hwndParent, self->hMenu, self->hInstance,
		self->lpCreateParams));
};
using CreateStruct = CreateStructX<IsUnicode>;
using CreateStructA = CreateStructX<false>;
using CreateStructW = CreateStructX<true>;
#pragma endregion

#pragma region WindowBase

#pragma region Misc
class LayeredDisplayAffinity {
	template<class>
	friend class WindowBase;
	COLORREF crKey = 0;
	BYTE bAlpha = 0;
	DWORD dwFlags = 0;
public:
	LayeredDisplayAffinity() {}
	LayeredDisplayAffinity(Null) {}
	LayeredDisplayAffinity(const LayeredDisplayAffinity &) = default;
public: // Property - Key
	/* W */ inline auto &Key(COLORREF key) reflect_to_self(crKey = key);
	/* R */ inline RGBColor Key() const reflect_as(crKey);
public: // Property - Alpha
	/* W */ inline auto &Alpha(BYTE alpha) reflect_to_self(bAlpha = alpha);
	/* R */ inline BYTE Alpha() const reflect_as(bAlpha);
};
template<class TCHAR>
class WindowIProps {
	template<class>
	friend class WindowBase;
	using LPCTSTR = const TCHAR *;
	mutable HWND hWnd;
	mutable LPCTSTR lpString;
private:
	WindowIProps(HWND hWnd, LPCTSTR lpString = O) : hWnd(hWnd), lpString(lpString) {}
	WindowIProps(const WindowIProps &) = delete;
public:
	WindowIProps(WindowIProps &wip) : hWnd(wip.hWnd) {}
public:
	inline void Remove() reflect_to(WX::RemoveProp(hWnd, lpString));
private:
	using FnEnumProp = Function<bool(HWND, LPTSTR, HANDLE)>;
	using FnEnumPropA = Function<bool(HWND, LPSTR, HANDLE)>;
	using FnEnumPropW = Function<bool(HWND, LPWSTR, HANDLE)>;
private:
	static BOOL _EnumPropA(HWND hWnd, LPSTR lpString, HANDLE hData, ULONG_PTR lParam) reflect_as((*(FnEnumPropA *)lParam)(hWnd, lpString, hData));
	static BOOL _EnumPropW(HWND hWnd, LPWSTR lpString, HANDLE hData, ULONG_PTR lParam) reflect_as((*(FnEnumPropW *)lParam)(hWnd, lpString, hData));
public:
	template<class AnyFunc>
	inline int Enum(AnyFunc fnEnum) {
		if_c (static_compatible<AnyFunc, bool(HWND, LPSTR, HANDLE)>) {
			FnEnumPropA fnEnumProps{
				[&](HWND hWnd, LPSTR lpString, HANDLE hData) {
					return fnEnum(hWnd, lpString, hData);
				}
			};
			return WX::EnumProps(hWnd, _EnumPropA, (LPARAM)std::addressof(fnEnumProps));
		}
		elif_c (static_compatible<AnyFunc, bool(HWND, LPWSTR, HANDLE)>) {
			FnEnumPropW fnEnumProps{
				[&](HWND hWnd, LPWSTR lpString, HANDLE hData) {
					return fnEnum(hWnd, lpString, hData);
				}
			};
			return WX::EnumProps(hWnd, _EnumPropW, (LPARAM)std::addressof(fnEnumProps));
		}
		elif_c (static_compatible<AnyFunc, void(HWND, LPSTR, HANDLE)>) {
			FnEnumPropA fnEnumProps{
				[&](HWND hWnd, LPSTR lpString, HANDLE hData) {
					fnEnum(hWnd, lpString, hData);
					return true;
				}
			};
			return WX::EnumProps(hWnd, _EnumPropA, (LPARAM)std::addressof(fnEnumProps));
		} else {
			misuse_assert((static_compatible<AnyFunc, void(HWND, LPWSTR, HANDLE)>),
						  "Enumeration function must compatible to bool(HWND, LPTSTR, HANDLE) or void(HWND, LPTSTR, HANDLE)");
			FnEnumPropW fnEnumProps{
				[&](HWND hWnd, LPWSTR lpString, HANDLE hData) {
					fnEnum(hWnd, lpString, hData);
					return true;
				}
			};
			return WX::EnumProps(hWnd, _EnumPropW, (LPARAM)std::addressof(fnEnumProps));
		}
	}
public:
	inline operator HANDLE() const reflect_as(WX::GetProp(hWnd, lpString));
	inline void operator=(HANDLE hData) reflect_as(WX::SetProp(hWnd, lpString, hData));
};
class WindowIWords {
	template<class>
	friend class WindowBase;
	mutable HWND hWnd;
	mutable int nIndex;
private:
	WindowIWords(HWND hWnd, int nIndex) : hWnd(hWnd), nIndex(nIndex) {}
	WindowIWords(const WindowIWords &) = delete;
public:
	WindowIWords(WindowIWords &wiw) : hWnd(wiw.hWnd), nIndex(wiw.nIndex) {}
public:
	inline operator WORD() const reflect_as(WX::GetWindowWord(hWnd, nIndex));
	inline void operator=(WORD wNewWord) reflect_to(WX::SetWindowWord(hWnd, nIndex, wNewWord));
};
template<bool IsUnicode = WX::IsUnicode>
class WindowILongsX {
	template<class>
	friend class WindowBase;
	mutable HWND hWnd;
	mutable int nIndex;
private:
	WindowILongsX(HWND hWnd, int nIndex) : hWnd(hWnd), nIndex(nIndex) {}
	WindowILongsX(const WindowILongsX &) = delete;
public:
	WindowILongsX(WindowILongsX &wic) : hWnd(wic.hWnd), nIndex(wic.nIndex) {}
public:
	inline operator LONG_PTR() const reflect_as(WX::GetWindowLongPtr<IsUnicode>(hWnd, nIndex));
	template<class AnyType>
	inline operator AnyType() const reflect_as(big_cast<AnyType>(WX::GetWindowLongPtr<IsUnicode>(hWnd, nIndex)));
	inline void operator=(LONG_PTR dwNewLong) reflect_to(WX::SetWindowLongPtr<IsUnicode>(hWnd, nIndex, dwNewLong));
	template<class AnyType>
	inline void operator=(AnyType dwNewLong) reflect_to(WX::SetWindowLongPtr<IsUnicode>(hWnd, nIndex, small_cast<LONG_PTR>(dwNewLong)));
};
using WindowILongs = WindowILongsX<IsUnicode>;
using WindowILongsA = WindowILongsX<false>;
using WindowILongsW = WindowILongsX<true>;
template<bool IsUnicode = WX::IsUnicode>
class WindowIClassX {
	mutable HWND hWnd;
	class Word {
		friend class WindowIClassX;
		mutable HWND hWnd;
		mutable int nIndex;
		Word(HWND hWnd, int nIndex) : hWnd(hWnd), nIndex(nIndex) {}
	public:
		inline operator WORD() const reflect_as(WX::GetClassWord(hWnd, nIndex));
		inline void operator=(WORD word) reflect_to(WX::SetClassWord(hWnd, nIndex, word));
	};
	class Long {
		friend class WindowIClassX;
		mutable HWND hWnd;
		mutable int nIndex;
		Long(HWND hWnd, int nIndex) : hWnd(hWnd), nIndex(nIndex) {} 
	public:
		inline operator LONG_PTR() const reflect_as(WX::GetClassLongPtr<IsUnicode>(hWnd, nIndex));
		template<class AnyType>
		inline operator AnyType() const reflect_as(big_cast<AnyType>(WX::GetClassLongPtr<IsUnicode>(hWnd, nIndex)));
		inline void operator=(LONG_PTR dwNewLong) reflect_to(WX::GetClassLongPtr<IsUnicode>(hWnd, nIndex, dwNewLong));
		template<class AnyType>
		inline void operator=(AnyType dwNewLong) reflect_to(WX::GetClassLongPtr<IsUnicode>(hWnd, nIndex, small_cast<AnyType>(dwNewLong)));
	};
private:
	template<class>
	friend class WindowBase;
	WindowIClassX(HWND hWnd) : hWnd(hWnd) {}
	WindowIClassX(const WindowIClassX &) = delete;
public:
	WindowIClassX(WindowIClassX &wic) : hWnd(wic.hWnd) {}
public: // Property - Words
	/* W */ inline Word Words(int nIndex) reflect_as({ hWnd, nIndex });
	/* W */ inline const Word Words(int nIndex) const reflect_as({ hWnd, nIndex });
public: // Property - Longs
	/* W */ inline Long Longs(int nIndex) reflect_as({ hWnd, nIndex });
	/* W */ inline const Long Longs(int nIndex) const reflect_as({ hWnd, nIndex });
public: // Property - Styles
	/* W */ inline auto&Styles(ClassStyle style) reflect_to_self(Longs(GCL_STYLE) = style.yield());
	/* R */ inline auto Styles() const reflect_as((ClassStyle)Longs(GCL_STYLE));
public: // Property - WndProc
	/* W */ inline auto&WndProc(WNDPROC lpfnWndProc) reflect_to_self(Longs(GCLP_WNDPROC) = lpfnWndProc);
//	/* R */ inline WX::WndProc WndProc() const reflect_as({ hWnd, (WNDPROC)Longs(GCLP_WNDPROC)));
public: // Property - ClsExtra
	/* W */ inline auto&ClsExtra(int cbClsExtra) reflect_to_self(Longs(GCL_CBCLSEXTRA) = cbClsExtra);
	/* R */ inline auto ClsExtra() const reflect_as((int)Longs(GCL_CBCLSEXTRA));
public: // Property - WndExtra
	/* W */ inline auto&WndExtra(int cbWndExtra) reflect_to_self(Longs(GCL_CBWNDEXTRA) = cbWndExtra);
	/* R */ inline auto WndExtra() const reflect_as((int)Longs(GCL_CBWNDEXTRA));
public: // Property - Module
	/* W */ inline auto&Module(HINSTANCE hModule) reflect_to_self(Longs(GCLP_HMODULE) = hModule);
	/* R */ inline CModule Module() const reflect_as((HMODULE)Longs(GCLP_HMODULE));
public: // Property - Icon
	/* W */ inline auto &Icon(CIcon icon) reflect_to_self(Longs(GCLP_HICON) = icon);
	/* R */ inline CIcon Icon() const reflect_as((HICON)Longs(GCLP_HICON));
public: // Property - Cursor
	/* W */ inline auto   &Cursor(CCursor cursor) reflect_to_self(Longs(GCLP_HCURSOR) = cursor);
	/* R */ inline CCursor Cursor() const reflect_as((HCURSOR)Longs(GCLP_HCURSOR));
public: // Property - Background
	/* W */ inline auto  &Background(CBrush brush) reflect_to_self(Longs(GCLP_HBRBACKGROUND) = brush);
	/* R */ inline CBrush Background() const reflect_as((HBRUSH)Longs(GCLP_HBRBACKGROUND));
public: // Property - Menu
	/* W */ inline auto&Menu(LPCTSTR lpszName) reflect_to_self(Longs(GCLP_MENUNAME) = lpszName);
	/* W */ inline auto&Menu(WORD wID) reflect_to_self(Longs(GCLP_MENUNAME) = (LPCTSTR)MAKEINTRESOURCE(wID));
// 	template<size_t MaxLen = MaxLenPath>
//	/* R */ inline const String MenuName() const reflect_as(CString((LPCTSTR)Longs(GCLP_MENUNAME), MaxLen));
public: // Property - Name
	template<size_t MaxLen = MaxLenClass>
	/* R */ inline StringX<IsUnicode> Name() const {
		StringX<IsUnicode> str(MaxLen);
		auto len = WX::GetClassName(hWnd, str, (int)MaxLen);
		return inject(str.Resize(len));
	}
public: // Property - Atom
	/* W */ inline auto &Atom(ATOM classAtom) reflect_to_self(Words(GCW_ATOM) = classAtom);
	/* R */ inline CAtom Atom() const reflect_as(Words(GCW_ATOM));
public:
	inline operator WindowClassX<IsUnicode>() const reflect_to(WindowClassX<IsUnicode> wc; WX::GetClassInfo(Module(), (ATOM)Atom(), &wc), wc);
	inline auto&operator=(const WindowIClassX &wic) reflect_to_self(hWnd = wic.hWnd);
};
using WindowIClass = WindowIClassX<IsUnicode>;
using WindowIClassA = WindowIClassX<false>;
using WindowIClassW = WindowIClassX<true>;
#pragma endregion

template<class AnyChild>
class WindowBase : 
	public ChainExtender<WindowBase<AnyChild>, AnyChild> {
	template<bool, class, class>
	friend class CreateStructX;
	mutable HWND hWnd = O;
public:
	using Child = Chain<WindowBase, AnyChild>;
	using super = WindowBase;
	using Shim = WindowShim<AnyChild>;
	using Style = WStyle;
	using StyleEx = WStyleEx;
protected:
	INNER_USE(WindowBase);
	WindowBase(HWND h) : hWnd(h) {}
	WindowBase(const WindowBase &w) : hWnd(w.hWnd) reflect_to(w.hWnd = O);
public:
	WindowBase(Null) {}
	WindowBase() {}
	WindowBase(WindowBase &w) : hWnd(w.hWnd) reflect_to(w.hWnd = O);
	WindowBase(WindowBase &&w) : hWnd(w.hWnd) reflect_to(w.hWnd = O);
	~WindowBase() reflect_to(Delete());
public:
	//static inline WindowShim<AnyClass> Find(LPCSTR lpName, LPCSTR lpClass) reflect_as(WX::FindWindow(lpClass, lpName));
	//static inline WindowShim<AnyClass> Find(LPCWSTR lpName, LPCWSTR lpClass) reflect_as(WX::FindWindow(lpClass, lpName));
	static inline Shim Find(LPCSTR lpName) reflect_as(WX::FindWindow((LPCSTR)(ULONG_PTR)WindowBase::_ClassAtom, lpName));
	static inline Shim Find(LPCWSTR lpName) reflect_as(WX::FindWindow((LPCWSTR)(ULONG_PTR)WindowBase::_ClassAtom, lpName));
	static inline Shim Active() reflect_as(WX::GetActiveWindow());
	static inline Shim Desktop() reflect_as(WX::GetDesktopWindow());
	static inline Shim Foreground() reflect_as(WX::GetForegroundWindow());
	static inline void Foreground(HWND hWnd) reflect_to(WX::SetForegroundWindow(hWnd));
public:
	inline void Delete() {
		if (self)
			Send(WM_DESTROY);
	}
public: // MsgBox
	inline int MsgBox(LPCSTR lpCaption, LPCSTR lpText = O, MB uType = MB::Ok) const reflect_as(WX::MsgBox(lpCaption, lpText, uType, self));
	inline int MsgBox(LPCWSTR lpCaption, LPCWSTR lpText = O, MB uType = MB::Ok) const reflect_as(WX::MsgBox(lpCaption, lpText, uType, self));
	inline int MsgBox(LPCSTR lpCaption, const Exception &err) const reflect_as(WX::MsgBox(lpCaption, err, self));
	inline int MsgBox(LPCWSTR lpCaption, const Exception &err) const reflect_as(WX::MsgBox(lpCaption, err, self));
public: // Show
	inline auto&Show(SW nShow)     reflect_to_child(WX::ShowWindow(self, nShow.yield()));
	inline auto&Hide()             reflect_as(Show(SW::Hide));
	inline auto&Normal()           reflect_as(Show(SW::Normal));
	inline auto&ShowNormal()       reflect_as(Show(SW::ShowNormal));
	inline auto&ShowMinimized()    reflect_as(Show(SW::ShowMinimized));
	inline auto&ShowMaximized()    reflect_as(Show(SW::ShowMaximized));
	inline auto&ShowNoActivate()   reflect_as(Show(SW::ShowNoActivate));
	inline auto&Show()             reflect_as(Show(SW::Show));
	inline auto&Maximize()         reflect_as(Show(SW::Maximize));
	inline auto&Minimize()         reflect_as(Show(SW::Minimize));
	inline auto&ForceMinimize()    reflect_as(Show(SW::ForceMinimize));
	inline auto&ShowMinNoActive()  reflect_as(Show(SW::ShowMinNoActive));
	inline auto&ShowDefault()      reflect_as(Show(SW::ShowDefault));
	inline auto&ShowNA()           reflect_as(Show(SW::ShowNA));
	inline auto&Restore()          reflect_as(Show(SW::Restore));
	inline auto&Max()              reflect_as(Show(SW::Max));
public: // Flash
	inline bool Flash(bool bInvert) const reflect_as(WX::FlashWindow(self, bInvert));
	inline bool Flash(FlashInfo fi) const reflect_as(WX::FlashWindow(&fi));
public: // Focus
	inline void Focus() const reflect_to(SetFocus(self));
	inline bool Focussed() const reflect_as(GetFocus() == self);
public: // Capture
	inline void Capture() const reflect_to(WX::SetCapture(self));
	inline bool Captured() const reflect_as(WX::GetCapture() == self);
public: // Rect & Point
	inline auto Screen2Client(LPoint pt) const reflect_to(WX::ScreenToClient(self, &pt), pt);
	inline auto Client2Screen(LPoint pt) const reflect_to(WX::ClientToScreen(self, &pt), pt);
	inline auto Log2Phy(LPoint pt) const reflect_to(WX::LogicalToPhysicalPoint(self, &pt), pt);
	inline auto Phy2Log(LPoint pt) const reflect_to(WX::PhysicalToLogicalPoint(self, &pt), pt);
	inline auto Logical2Physical(LPoint pt) const reflect_to(WX::LogicalToPhysicalPoint(self, &pt), pt);
	inline auto Physical2Logical(LPoint pt) const reflect_to(WX::PhysicalToLogicalPoint(self, &pt), pt);
	inline auto Log2PhyDPI(LPoint pt) const reflect_to(WX::LogicalToPhysicalPointForPerMonitorDPI(self, &pt), pt);
	inline auto Phy2LogDPI(LPoint pt) const reflect_to(WX::PhysicalToLogicalPointForPerMonitorDPI(self, &pt), pt);
	inline auto Logical2PhysicalDPI(LPoint pt) const reflect_to(WX::LogicalToPhysicalPointForPerMonitorDPI(self, &pt), pt);
	inline auto Physical2LogicalDPI(LPoint pt) const reflect_to(WX::PhysicalToLogicalPointForPerMonitorDPI(self, &pt), pt);
	inline auto AdjRect(LRect rc) const reflect_to(WX::AdjustWindowRect(&rc, Styles().yield(), this->Menu(), this->StylesEx().yield()), rc);
	inline auto AdjustRect(LRect rc) const reflect_to(WX::AdjustWindowRect(&rc, Styles().yield(), this->Menu(), this->StylesEx().yield()), rc);
	inline auto AdjRectDPI(LRect rc, UINT dpi) const reflect_to(WX::AdjustWindowRectForDpi(&rc, Styles().yield(), this->Menu(), this->StylesEx().yield(), dpi), rc);
	inline auto AdjustRectDPI(LRect rc, UINT dpi) const reflect_to(WX::AdjustWindowRectForDpi(&rc, Styles().yield(), this->Menu(), this->StylesEx().yield(), dpi), rc);
public: // Position
	inline void BringToTop() const reflect_to_child(WX::BringWindowToTop(self));
	inline void Move(LRect rc, bool bRedraw = true) const reflect_to(WX::MoveWindow(self, rc.top, rc.left, rc.xsize(), rc.ysize(), bRedraw));
public: // Timer
	inline auto SetTimer(UINT uElapse, UINT_PTR nIDEvent = 0, TIMERPROC lpTimerFunc = O) reflect_as(WX::SetTimer(self, nIDEvent, uElapse, lpTimerFunc));
	inline void KillTimer(UINT_PTR nIDEvent) reflect_to(WX::KillTimer(self, nIDEvent));
public: // Touch & Mouse
	inline void RegisterTouch(bool bFine = true, bool bWantPalm = false) reflect_to(WX::RegisterTouchWindow(self, (bFine * TWF_FINETOUCH) | (bWantPalm * TWF_WANTPALM)));
	inline void UnregisterTouch() reflect_to(WX::UnregisterTouchWindow(self));
	inline TrackMouseEventBox TrackMouse() const reflect_as((HWND)self);
public: // Draw & Paint
	inline void Update() reflect_to(WX::UpdateWindow(self));
	inline void Validate(LPCRECT lpRect = O) const reflect_to(WX::ValidateRect(self, lpRect));
	inline void Invalidate(LPCRECT lpRect = O, bool fErase = false) const reflect_to(WX::InvalidateRect(self, lpRect, fErase));
	inline void LockUpdate() const reflect_to(WX::LockWindowUpdate(self));
	//inline PaintBox BeginPaint() reflect_as((HWND)self);
public: // Child & Parent
	inline bool HasChild(HWND hWnd) reflect_as(WX::IsChild(self, hWnd));
public: // Message Senders
	template<class RetType = LRESULT, class MsgType = UINT, class WParam = WPARAM, class LParam = LPARAM>
	inline RetType Send(MsgType msgid, WParam wParam = 0, LParam lParam = 0) const reflect_as(big_cast<RetType>(WX::SendMessage(self, (UINT)(msgid), small_cast<WPARAM>(wParam), small_cast<LPARAM>(lParam))));
	//template<class WParam = WPARAM, class LParam = LPARAM>
	//inline auto&SendTimeout(UINT msgid, WParam wParam = 0, LParam lParam = 0) {
	//	WX::SendMessageTimeout(self, msgid, wParam, lParam, )
	//}
	template<class MsgType = UINT, class WParam = WPARAM, class LParam = LPARAM>
	inline auto&Post(MsgType msgid, WParam wParam = 0, LParam lParam = 0) const reflect_to_child(WX::PostMessage(self, reuse_as<UINT>(msgid), reuse_as<WPARAM>(wParam), reuse_as<LPARAM>(lParam)));

#pragma region Enum
public:
	using FnEnumWindow = Function<bool(HWND)>;
private:
	static BOOL EnumWindowProc(HWND hWnd, LPARAM lParam) reflect_as((*(FnEnumWindow *)lParam)(hWnd));
public:
	template<class AnyFunc>
	static inline void Enum(AnyFunc fnEnum) {
		FnEnumWindow fnEnumWindows([&](HWND hWnd) {
			if_c (static_compatible<AnyFunc, bool(HWND)>)
				return fnEnum(hWnd);
			else {
				misuse_assert((static_compatible<AnyFunc, void(HWND)>),
							  "Enumeration function must compatible to bool(HWND) or void(HWND)");
				fnEnum(hWnd);
				return true;
			}
		});
		WX::EnumWindows(EnumWindowProc, (LPARAM)std::addressof(fnEnumWindows));
	}
	template<class AnyFunc>
	inline void EnumChild(AnyFunc fnEnum) {
		FnEnumWindow fnEnumChildren([&](HWND hWnd) {
			if_c (static_compatible<AnyFunc, bool(HWND)>)
				return fnEnum(hWnd);
			else {
				misuse_assert((static_compatible<AnyFunc, void(HWND)>),
							  "Enumeration function must compatible to bool(HWND) or void(HWND)");
				fnEnum(hWnd);
				return true;
			}
		});
		EnumChildWindows(self, EnumWindowProc, (LPARAM)std::addressof(fnEnumChildren));
	}
#pragma endregion

#pragma region Message Procedure Reflect System
protected: // Default Message Procedure
	use_member(DefProc);
	static LRESULT CallDefProc(HWND hWnd, UINT msgid, WPARAM wParam, LPARAM lParam) {
		if_c (member_DefProc_of<Child>::is_addressable) {
			misdef_assert((!std::is_member_pointer_v<decltype(&Child::DefProc)>),
						  "DefProc must be a static method.");
			using tfn_WndProc = LRESULT(HWND, UINT, WPARAM, LPARAM);
			misdef_assert((member_DefProc_of<Child>::template compatible_to<tfn_WndProc>),
						  "DefProc must be compatible to LRESULT(HWND, UINT, WPARAM, LPARAM)");
			return Child::DefProc(hWnd, msgid, wParam, lParam);
		}
		else return WX::DefWindowProc(hWnd, msgid, wParam, lParam);
	}
public: // Reflectors management
	class Reflectors {
		Child *pChild;
	public:
		Reflectors(Child *pChild) : pChild(pChild) {}
#define CALL(name) pChild->On##name
#define SEND(ret, msgid, wparam, lparam) pChild->On##name(wparam, lparam)
#define MSG_TRANS(msgid, ret, name, argslist, args, send, call) \
		private: use_member(On##name); \
		public: static constexpr bool User##name = member_On##name##_of<Child>::is_addressable; \
		inline LRESULT CallOn##name argslist { \
			using fn_type = ret argslist; \
			if_c (member_On##name##_of<Child>::template compatible_to<ret()>) \
				if_c (std::is_void_v<ret>) \
					 reflect_as((pChild->On##name(), 0L)) \
				else reflect_as((LRESULT)pChild->name()) \
			elif_c (member_On##name##_of<Child>::template compatible_to<LRESULT()>) \
				reflect_as(pChild->On##name()) \
			elif_c (member_On##name##_of<Child>::template compatible_to<void(WPARAM, LPARAM)>) \
				reflect_as((send, 0L)) \
			elif_c (member_On##name##_of<Child>::template compatible_to<LRESULT(WPARAM, LPARAM)>) \
				reflect_as(send) \
			elif_c (member_On##name##_of<Child>::template compatible_to<fn_type>) { \
				misdef_assert((member_On##name##_of<Child>::template compatible_to<fn_type>), \
							  "Member On" #name " must be a method compatible to " #ret #argslist ", " #ret "(), void(WPARAM, LPARAM) or LRESULT(WPARAM, LPARAM)" ); \
				reflect_as(pChild->On##name args); \
			} \
		}
#include "wx__msg.inl"
	public:
		inline operator bool() const reflect_as(pChild);
	};
protected: // Message Procedure
	use_member(Callback);
	static LRESULT CALLBACK MainProc(HWND hWnd, UINT msgid, WPARAM wParam, LPARAM lParam) {
		auto&Wnd = WindowBase::Attach(hWnd);
		auto pChild = Wnd.UserData<Child *>();
	retry:
		try {
			switch (msgid) {
				case WM_NCCREATE: {
					auto lpCreate = (LPCREATESTRUCT)lParam;
					pChild = (Child *)lpCreate->lpCreateParams;
					Wnd.UserData(pChild);
					(*(WindowBase *)pChild).hWnd = hWnd;
					break;
				}
				case WM_COMMAND:
					if (auto wnd = ref_as<Window>(lParam))
						wnd.Send(WM_USER + (UINT)HIWORD(wParam));
					break;
			}
			if (Reflectors ref = pChild) {
				switch (msgid) {
					case WM_NULL:
						break;
#define CALL(name) ref.CallOn##name
#define MSG_TRANS(msgid, ret, name, argslist, args, send, call) \
					case msgid: \
						if_c (Reflectors::User##name) { \
							return call; \
						} break;
#include "wx__msg.inl"
				}
			}
			if_c (member_Callback_of<Child>::is_addressable) {
				misdef_assert(member_Callback_of<Child>::template compatible_to<LRESULT(WPARAM, LPARAM)>, 
							  "Member Callback must be a method compatible to LRESULT(WPARAM, LPARAM)");
				return pChild->Callback(msgid, wParam, lParam);
			}
		} catch (MSG msg) {
			if (msg.message)
				return CallDefProc(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		} catch (Exception err) {
			MsgException msgErr{ err, Msg{ hWnd, msgid, wParam, lParam } };
			if (Catch(pChild, msgErr))
				goto retry;
			return Final(pChild, msgErr);
		}
		return CallDefProc(hWnd, msgid, wParam, lParam);
	}
protected: // Default Message Definitions
	inline void OnDestroy() reflect_to(WX::PostQuitMessage(0));
protected: // Message Procedure Exception System
	use_member(OnCatch);
	static inline wx_answer Catch(Child *pChild, const MsgException &err) {
		if_c (member_OnCatch_of<AnyChild>::template compatible_to<wx_answer(MsgException)>)
			reflect_as(pChild->OnCatch(err))
		elif_c (member_OnCatch_of<AnyChild>::template compatible_to<wx_answer()>)
			reflect_as(pChild->OnCatch())
		elif_c (member_OnCatch_of<AnyChild>::template compatible_to<void(MsgException)>)
			reflect_as((pChild->OnCatch(err), false))
		elif_c (member_OnCatch_of<AnyChild>::template compatible_to<void()>)
			reflect_as((pChild->OnCatch(), false))
		else {
			misdef_assert(!member_OnCatch_of<AnyChild>::is_addressable,
						  "Member OnCatch must be compatible to wx_answer(Exception), wx_answer(), void(MsgException) or void()");
			switch (WX::MsgBox(T("Window Error"), err, err.Msg().Window())) {
				case IDRETRY:
					wx_answer_retry;
				case IDIGNORE:
					wx_answer_ignore;
				case IDABORT:
					break;
			}
			wx_answer_abort(err);
		}
	}
	use_member(OnFinal);
	static inline LRESULT Final(Child *pChild, const MsgException &err) {
		if_c (member_OnFinal_of<AnyChild>::template compatible_to<LRESULT(MsgException)>)
			reflect_as(pChild->OnFinal(err))
		elif_c (member_OnFinal_of<AnyChild>::template compatible_to<LRESULT()>)
			reflect_as(pChild->OnFinal())
		elif_c (member_OnFinal_of<AnyChild>::template compatible_to<void(MsgException)>)
			reflect_as((pChild->OnFinal(err), -1))
		elif_c (member_OnFinal_of<AnyChild>::template compatible_to<void()>)
			reflect_as((pChild->OnFinal(), -1))
		else {
			misdef_assert(!member_OnFinal_of<AnyChild>::is_addressable,
						  "Member OnFinal must be compatible to LRESULT(MsgException), LRESULT(), void(MsgException), void()");
			reflect_as(-3)
		}
	}
public:
	class CallPack {
		HWND hwnd;
	public:
		CallPack(HWND hwnd) : hwnd(hwnd) {}
#define SEND(ret, msgid, wparam, lparam) \
			(ret)(CallDefProc(hwnd, msgid, wparam, lparam))
#define MSG_TRANS(msgid, ret, name, argslist, args, send, call) \
			inline ret name argslist reflect_as(send);
#include "wx__msg.inl"
	};
	inline CallPack DefProcCall() reflect_as((HWND)self);
#pragma endregion

#pragma region Class Management
protected:
	static ATOM _ClassAtom;
	use_member(CClassNameA);
	use_member(CClassNameW);
public:
	static inline auto&CClassNameA() {
		if_c (member_CClassNameA_of<AnyChild>::template compatible_to<StringA(AnyChild:: *)()>)
			reflect_as(AnyChild::CClassNameA())
		else {
			misdef_assert(!member_CClassNameA_of<AnyChild>::is_existed,
						  "Member CClassNameA must be compatible to StringA()");
			static const StringA _ClassNameA = CString(typeid(Child).name(), MaxLenClass);
			return _ClassNameA;
		}
	}
	static inline auto&CClassNameW() {
		if_c (member_CClassNameW_of<AnyChild>::template compatible_to<StringW(AnyChild:: *)()>)
			reflect_as(AnyChild::CClassNameW())
		else {
			misdef_assert(!member_CClassNameW_of<AnyChild>::is_existed,
						  "Member CClassNameA must be compatible to StringW()");
			static const StringW _ClassNameW = FitsW(CClassNameA());
			return _ClassNameW;
		}
	}
	template<bool IsUnicode = WX::IsUnicode>
	static inline auto&CClassName() {
		if_c (IsUnicode)
			 reflect_as(CClassNameW())
		else reflect_as(CClassNameA())
	}
protected:
	template<bool IsUnicode>
	class XClassX : public WindowClassX<IsUnicode> {
		using LPCTSTR = LPCXSTR<IsUnicode>;
	public:
		using super = WindowClassX<IsUnicode>;
	public:
		XClassX() {
			super::WndProc(MainProc);
			super::Name(CClassName<IsUnicode>());
			super::Cursor(IDC_ARROW);
			super::Styles(ClassStyle::Redraw);
			super::Background(SysColor::Window);
		}
	};
	using XClass = XClassX<IsUnicode>;
	using XClassA = XClassX<false>;
	using XClassW = XClassX<true>;
protected:
	template<bool IsUnicode>
	class XClassExX : public WindowClassExX<IsUnicode> {
		using LPCTSTR = LPCXSTR<IsUnicode>;
	public:
		using super = WindowClassExX<IsUnicode>;
	public:
		XClassExX() {
			super::WndProc(MainProc);
			super::Name(CClassName<IsUnicode>());
			super::Cursor(IDC_ARROW);
			super::Styles(ClassStyle::Redraw);
			super::Background(SysColor::Window);
		}
	};
	using XClassEx = XClassExX<IsUnicode>;
	using XClassExA = XClassExX<false>;
	using XClassExW = XClassExX<true>;
private:
	static inline const auto &DefCClass() {
		static XClassEx _Class;
		reflect_as(_Class)
	}
private:
	use_member(Register);
	static inline ATOM DefRegister() {
		if (_ClassAtom) return _ClassAtom;
		return _ClassAtom = DefCClass().Register();
	}
public:
	static inline auto Register() {
		if_c (member_Register_of<AnyChild>::is_addressable)
			 reflect_as(AnyChild::Register())
		else reflect_as(DefRegister())
	}
private:
	static inline void DefUnregister() {
		if (_ClassAtom)
			DefCClass().Unregister();
		_ClassAtom = 0;
	}
public:
	static inline void Unregister() {
		if_c (!IsEqual(AnyChild::Unregister, Unregister)) 
			 reflect_as(AnyChild::Unregister())
		elif_c (AnyChild::Unregister != Unregister)
			 reflect_as(AnyChild::Unregister())
		else reflect_as(DefUnregister())
	}
#pragma endregion

#pragma region Creature Management
protected:
	template<bool IsUnicode, class Style = WStyle, class StyleEx = WStyleEx>
	class CreateStructX : public WX::CreateStructX<IsUnicode, Style, StyleEx> {
		friend class WindowBase;
		using_structx(CREATESTRUCT);
		using LPCTSTR = LPCXSTR<IsUnicode>;
	public:
		using super = WX::CreateStructX<IsUnicode, Style, StyleEx>;
	public:
		CreateStructX(CreateStructX &cs) : super(cs) {
			cs.Param(O);
		}
		CreateStructX(Child &c, HWND hParent) {
			super::Parent(hParent);
			super::Class(Register());
			super::Param(std::addressof(c));
			super::Size(CW_USEDEFAULT);
			super::Position(CW_USEDEFAULT);
			super::Styles(WS::OverlappedWindow);
		}
		CreateStructX(const CREATESTRUCT &lpCreate, Child &c) : super(lpCreate) {
			super::Class(Register());
			super::Param(std::addressof(c));
		}
		~CreateStructX() reflect_to(AutoCreate());
	public:
		inline void AutoCreate() const {
			if (auto pChild = super::template Param<Child>(); !*pChild)
				pChild->hWnd = super::Create();
		}
		inline void AutoCreateMDI() const {
			if (auto pChild = super::template Param<Child>(); !*pChild)
				pChild->hWnd = super::CreateMDI();
		}
	private: // Remove properties
		/* W */ using super::Param;
	public: // Deleted properties
		/* W */ inline auto&Class(LPCTSTR) = delete;
		/* W */ inline auto&Class(ATOM) = delete;
	};
	template<class Style = WStyle, class StyleEx = WStyleEx>
	using CreateStruct = CreateStructX<IsUnicode, Style, StyleEx>;
	template<class Style = WStyle, class StyleEx = WStyleEx>
	using CreateStructA = CreateStructX<false, Style, StyleEx>;
	template<class Style = WStyle, class StyleEx = WStyleEx>
	using CreateStructW = CreateStructX<true, Style, StyleEx>;
public:
	inline auto Create(HWND hParent = O) reflect_as(CreateStruct(child, hParent));
	inline auto CreateA(HWND hParent = O) reflect_as(CreateStructA(child, hParent));
	inline auto CreateW(HWND hParent = O) reflect_as(CreateStructW(child, hParent));
	inline void Create(const CREATESTRUCTA &cs) reflect_to(Create(CreateStructA(cs, child).Class(Register())));
	inline void Create(const CREATESTRUCTW &cs) reflect_to(Create(CreateStructW(cs, child).Class(Register())));
	inline void Create(CreateStructA<> cs) reflect_to(hWnd = cs.Param(pchild).Class(Register()).Create());
	inline void Create(CreateStructW<> cs) reflect_to(hWnd = cs.Param(pchild).Class(Register()).Create());
	inline void Destroy() reflect_to(WX::DestroyWindow(self));
	inline void Close() reflect_to(WX::CloseWindow(self));
#pragma endregion

#pragma region Properties
public: // Property - Iconic
	/* W */ inline auto&Iconic(bool bIconic) reflect_to_child(if (bIconic) WX::OpenIcon(self));
	/* R */ inline bool Iconic() const reflect_as(WX::IsIconic(self));
public: // Property - Zoomed
	/* R */ inline bool Zoomed() const reflect_as(WX::IsZoomed(self));
public: // Property - Visible
	/* W */ inline auto&Visible(bool bVisible) reflect_to_child(WX::ShowWindow(self, bVisible ? SW_SHOW : SW_HIDE));
	/* R */ inline bool Visible() const reflect_as(WX::IsWindowVisible(self));
public: // Proterty - Enabled
	/* W */ inline auto&Enabled(bool bEnable) reflect_to_child(WX::EnableWindow(self, bEnable));
	/* R */ inline bool Enabled() const reflect_as(WX::IsWindowEnabled(self));
public: // Property - Unicode
	/* R */ inline bool Unicode() const reflect_as(WX::IsWindowUnicode(self));
public: // Property - ClientRect
	/* R */ inline LRect ClientRect() const reflect_to(LRect r; WX::GetClientRect(self, &r), r);
public: // Property - ClientSize
	/* R */ inline LSize ClientSize() const reflect_to(LRect r; WX::GetClientRect(self, &r), r.size());
public: // Property - Position
	/* W */ inline auto&Position(LPoint ptPosition) reflect_to_child(WX::SetWindowPos(self, O, ptPosition.x, ptPosition.y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE));
	/* R */ inline LPoint Position() const reflect_to(LRect r; WX::GetWindowRect(self, &r), r.left_top());
public: // Property - Size
	/* W */ inline auto&Size(LSize szWin) reflect_to_child(WX::SetWindowPos(self, O, 0, 0, szWin.cx - 1, szWin.cy - 1, SWP_NOMOVE | SWP_NOACTIVATE));
	/* R */ inline LSize Size() const reflect_to(LRect r; WX::GetWindowRect(self, &r), r.size());
public: // Property - Rect
	/* W */ inline auto&Rect(LRect rWin) reflect_to_child(LSize sz = rWin.size(); WX::SetWindowPos(self, O, rWin.top, rWin.left, sz.cx, sz.cy, SWP_NOZORDER | SWP_NOACTIVATE));
	/* R */ inline LRect Rect() const reflect_to(LRect r; WX::GetWindowRect(self, &r), r);
public: // Property - DPI
	/* R */ inline UINT DPI() const reflect_as(WX::GetDpiForWindow(self));
public: // Property - DPIHostingBehavior
	/* R */ inline WX::DPIHostingBehavior DPIHostingBehavior() const reflect_as(WX::GetWindowDpiHostingBehavior(self));
public: // Property - Placement
	/* W */ inline auto&Placement(const WINDOWPLACEMENT &wp) reflect_to_child(WX::SetWindowPlacement(self, &wp));
	/* R */ inline WindowPlacement Placement() const reflect_to(WindowPlacement wp; WX::GetWindowPlacement(self, &wp), wp);
public: // Property - Info
	/* R */ inline WindowInfo Info() const reflect_to(WindowInfo wi; WX::GetWindowInfo(self, &wi), wi);
public: // Property - TextLength
	template<bool IsUnicode = WX::IsUnicode>
	/* R */ inline int TextLength() const reflect_as(WX::GetWindowTextLength<IsUnicode>(self));
	/* R */ inline int TextLengthA() const reflect_as(TextLength<false>());
	/* R */ inline int TextLengthW() const reflect_as(TextLength<true>());
public: // Property - String
	/* W */ inline auto&Text(LPCSTR lpString) reflect_to_child(WX::SetWindowText(self, lpString));
	/* W */ inline auto&Text(LPCWSTR lpString) reflect_to_child(WX::SetWindowText(self, lpString));
	template<bool IsUnicode>
	/* R */ inline StringX<IsUnicode> Text() const {
		auto len = TextLength<IsUnicode>();
		if (len <= 0) return O;
		StringX<IsUnicode> str((size_t)len);
		WX::GetWindowText(self, str, len);
		return inject(str);
	}
	/* R */ inline StringA TextA() const reflect_as(Text<false>());
	/* R */ inline StringW TextW() const reflect_as(Text<true>());
public: // Property - ModuleFileName
	template<size_t MaxLen = MaxLenPath, bool IsUnicode = WX::IsUnicode>
	/* R */ inline StringX<IsUnicode> ModuleFileName() const {
		StringX<IsUnicode> str(MaxLen);
		int len = WX::GetWindowModuleFileName(self, str, (int)MaxLen);
		return inject(str.Resize(len));
	}
	template<size_t MaxLen = MaxLenPath>
	/* R */ inline StringA ModuleFileNameA() const reflect_as(ModuleFileName<MaxLen, false>());
	template<size_t MaxLen = MaxLenPath>
	/* R */ inline StringW ModuleFileNameW() const reflect_as(ModuleFileName<MaxLen, true>());
public: // Property - Parent
	/* W */ inline auto&Parent(HWND hParent) reflect_to_child(WX::SetParent(self, hParent));
	template<class AnyClass = void>
	/* R */ inline WindowShim<AnyClass> Parent() reflect_as(WX::GetParent(self));
	template<class AnyClass = void>
	/* R */ inline CWindowShim<AnyClass> Parent() const reflect_as(WX::GetParent(self));
//public: // Property - Next
//	template<class AnyClass = void>
//	/* R */ inline WindowShim<AnyClass> Next() const reflect_as(WX::GetNextWindow(self, GW_HWNDNEXT));
//public: // Property - Prev
//	template<class AnyClass = void>
//	/* R */ inline WindowShim<AnyClass> Prev() const reflect_as(WX::GetNextWindow(self, GW_HWNDPREV));
public: // Property - ScrollPositionH
	/* W */ inline auto&ScrollPositionH(int nPos) reflect_to_child(WX::SetScrollPos(self, SB_HORZ, nPos, true));
	/* R */ inline auto ScrollPositionH() const reflect_as(WX::GetScrollPos(self, SB_HORZ));
public: // Property - ScrollPositionV
	/* W */ inline auto&ScrollPositionV(int nPos) reflect_to_child(WX::SetScrollPos(self, SB_VERT, nPos, true));
	/* R */ inline auto ScrollPositionV() const reflect_as(WX::GetScrollPos(self, SB_VERT));
public: // Property - ScrollVisible
	/* W */ inline auto&ScrollVisible(bool bShow) reflect_to_child(WX::ShowScrollBar(self, SB_BOTH, bShow));
public: // Property - ScrollVisibleH
	/* W */ inline auto&ScrollVisibleH(bool bShow) reflect_to_child(WX::ShowScrollBar(self, SB_HORZ, bShow));
public: // Property - ScrollVisibleV
	/* W */ inline auto&ScrollVisibleV(bool bShow) reflect_to_child(WX::ShowScrollBar(self, SB_VERT, bShow));
public: // Property - ScrollInfoH
	/* W */ inline auto&ScrollInfoH(const SCROLLINFO &si, bool bRedraw = true) reflect_to_child(WX::SetScrollInfo(self, SB_HORZ, &si, bRedraw));
	/* R */ inline ScrollInfo ScrollInfoH() const reflect_to(ScrollInfo si; WX::GetScrollInfo(self, SB_HORZ, &si), si);
public: // Property - ScrollInfoV
	/* W */ inline auto&ScrollInfoV(const SCROLLINFO &si, bool bRedraw = true) reflect_to_child(WX::SetScrollInfo(self, SB_VERT, &si, bRedraw));
	/* R */ inline ScrollInfo ScrollInfoV() const reflect_to(ScrollInfo si; WX::GetScrollInfo(self, SB_VERT, &si), si);
public: // Property - TitleBarInfo
	/* W */ inline WX::TitleBarInfo TitleBarInfo() const reflect_to(WX::TitleBarInfo tbi; WX::GetTitleBarInfo(self, &tbi), tbi);
public: // Property - Menu
	/* W */ inline auto&Menu(HMENU hMenu) reflect_to_child(WX::SetMenu(self, hMenu));
	/* R */ inline CMenu Menu() const reflect_as(WX::GetMenu(self));
public: // Property - SysMenu
	/* R */ inline CMenu SysMenu() const reflect_as(WX::GetSystemMenu(self, false));
public: // Property - Region
	/* W */ inline auto&Region(HRGN hRgn) reflect_to_child(WX::SetWindowRgn(self, hRgn, true));
///	/* R */ inline void Region() const { WX::GetWindowRgn() }
public: // Property - RegionBox
	/* R */ inline LRect RegionBox() const reflect_to(LRect rc;  WX::GetWindowRgnBox(self, &rc), rc);
public: // Property - DisplayAffinity
	/* W */ inline auto&DisplayAffinity(DisplayAffinities dwAffinity) reflect_to_child(WX::SetWindowDisplayAffinity(self, dwAffinity.yield()));
	/* R */ inline auto DisplayAffinity() const reflect_to(DWORD dwAffinity = 0; WX::GetWindowDisplayAffinity(self, &dwAffinity), reuse_as<DisplayAffinities>(dwAffinity));
public: // Property - LayeredDisplayAffinity
	/* W */ inline auto &LayeredDisplayAffinity(WX::LayeredDisplayAffinity lda) reflect_to_child(WX::SetLayeredWindowAttributes(self, lda.crKey, lda.bAlpha, lda.dwFlags));
	/* R */ inline auto LayeredDisplayAffinity() const reflect_to(WX::LayeredDisplayAffinity lda; WX::GetLayeredWindowAttributes(self, &lda.crKey, &lda.bAlpha, &lda.dwFlags), lda);
public: // Property - Icon
	/* W */ inline auto&Icon(HICON hIcon) reflect_to_child(Send<HICON>(WM_SETICON, ICON_BIG, hIcon));
	/* R */ inline CIcon Icon() const reflect_as(Send<HICON>(WM_GETICON, ICON_BIG));
public: // Property - IconSmall
	/* W */ inline auto&IconSmall(HICON hIcon) reflect_to_child(Send<HICON>(WM_SETICON, ICON_SMALL, hIcon));
	/* R */ inline CIcon IconSmall() const reflect_as(Send<HICON>(WM_GETICON, ICON_SMALL));
public: // Property - IconSmall2
	/* W */ inline auto&IconSmall2(HICON hIcon) reflect_to_child(Send<HICON>(WM_SETICON, ICON_SMALL2, hIcon));
	/* R */ inline CIcon IconSmall2() const reflect_as(Send<HICON>(WM_GETICON, ICON_SMALL2));
#pragma region Window Extra
public: // Property - Words
	/* R */ inline WindowIWords Words(int nIndex) reflect_as({ (HWND)self, nIndex });
	/* R */ inline const WindowIWords Words(int nIndex) const reflect_as({ (HWND)self, nIndex });
public: // Property - Longs
	template<bool IsUnicode = WX::IsUnicode>
	/* R */ inline WindowILongsX<IsUnicode> Longs(int nIndex) reflect_as({ (HWND)self, nIndex });
	/* R */ inline WindowILongsA LongsA(int nIndex) reflect_as({ (HWND)self, nIndex });
	/* R */ inline WindowILongsW LongsW(int nIndex) reflect_as({ (HWND)self, nIndex });
	template<bool IsUnicode = WX::IsUnicode>
	/* R */ inline const WindowILongsX<IsUnicode> Longs(int nIndex) const reflect_as({ (HWND)self, nIndex });
	/* R */ inline const WindowILongsA LongsA(int nIndex) const reflect_as({ (HWND)self, nIndex });
	/* R */ inline const WindowILongsW LongsW(int nIndex) const reflect_as({ (HWND)self, nIndex });
public: // Property - WndProc
	/* W */ inline auto&WndProc(WNDPROC lpfnWndProc) reflect_to_child(Longs(GWLP_WNDPROC) = lpfnWndProc);
	/* R */ inline WX::WndProc WndProc() const reflect_as((WX::WndProc)Longs(GWLP_WNDPROC));
public: // Property - Module
	/* W */ inline auto&Module(HINSTANCE hInstance) reflect_to_child(Longs(GWLP_HINSTANCE) = hInstance);
	/* R */ inline CModule Module() const reflect_as((HINSTANCE)Longs(GWLP_HINSTANCE));
public: // Property - HwndParent
	/* W */ inline auto&HwndParent(HWND hHwndParent) reflect_to_child(Longs(GWLP_HWNDPARENT) = hHwndParent);
	template<class AnyClass = void>
	/* R */ inline WindowShim<AnyClass> HwndParent() reflect_as(Longs(GWLP_HWNDPARENT));
	template<class AnyClass = void>
	/* R */ inline CWindowShim<AnyClass> HwndParent() const reflect_as(Longs(GWLP_HWNDPARENT));
public: // Property - Styles
	/* W */ inline auto&Styles(Style style) reflect_to_child(Longs(GWL_STYLE) = style);
	/* R */ inline Style Styles() const reflect_as((Style)Longs(GWL_STYLE));
public: // Property - StylesEx 
	/* W */ inline auto&StylesEx(StyleEx styleEx) reflect_to_child(Longs(GWL_EXSTYLE) = styleEx);
	/* R */ inline StyleEx StylesEx() const reflect_as((StyleEx)Longs(GWL_EXSTYLE));
public: // Property - UserData
	template<class AnyType = LONG_PTR>
	/* W */ inline auto&UserData(AnyType data) reflect_to_child(Longs(GWLP_USERDATA) = data);
	template<class AnyType = LONG_PTR>
	/* R */ inline AnyType UserData() const reflect_as((AnyType)Longs(GWLP_USERDATA));
public: // Property - ID
	/* W */ inline auto&ID(LONG_PTR uId) reflect_to_child(Longs(GWLP_ID) = uId);
	/* R */ inline LONG_PTR ID() const reflect_as(Longs(GWLP_ID));
#pragma endregion
public: // Property - Class
	template<bool IsUnicode = WX::IsUnicode>
	/* R */ inline WindowIClassX<IsUnicode> Class() reflect_as(hWnd);
	/* R */ inline WindowIClassA ClassA() reflect_to_self();
	/* R */ inline WindowIClassW ClassW() reflect_to_self();
	template<bool IsUnicode = WX::IsUnicode>
	/* R */ inline const WindowIClassX<IsUnicode> Class() const reflect_to_self();
	/* R */ inline const WindowIClassA ClassA() const reflect_to_self();
	/* R */ inline const WindowIClassW ClassW() const reflect_to_self();
public: // Property - DC
	/* R */ inline CDC DC() const reflect_as(WX::GetDC(self));
public: // Property - ContextHelpID
	/* W */ inline auto &ContextHelpID(DWORD dwContextHelpID) reflect_to_child(WX::SetWindowContextHelpId(self, dwContextHelpID));
	/* R */ inline DWORD ContextHelpID() const reflect_as(WX::GetWindowContextHelpId(self));
public: // Property - ProcessID
	/* R */ inline DWORD ProcessID() const reflect_to(DWORD dwProcessId = 0; WX::GetWindowThreadProcessId(self, &dwProcessId), dwProcessId);
public: // Property - ThreadID
	/* R */ inline DWORD ThreadID() const reflect_as(WX::GetWindowThreadProcessId(self, O));
//public: // Property - Prop
//	/* W */ inline auto&Prop(ATOM globalAtom, HANDLE hData) assertl_reflect_as_child(SetProp(self, MAKEINTATOM(globalAtom), hData));
//	/* W */ inline auto&Prop(LPCSTR lpString, HANDLE hData) assertl_reflect_as_child(SetPropA(self, lpString, hData));
//	/* W */ inline auto&Prop(LPCWSTR lpString, HANDLE hData) assertl_reflect_as_child(SetPropW(self, lpString, hData));
//	/* R */ inline HANDLE Prop(ATOM globalAtom) const nt_assertl_reflect_to(auto hData = GetProp(self, MAKEINTATOM(globalAtom)), hData);
//	/* R */ inline HANDLE Prop(LPCSTR lpString) const assertl_reflect_to(auto hData = GetPropA(self, lpString), hData);
//	/* R */ inline HANDLE Prop(LPCWSTR lpString) const assertl_reflect_to(auto hData = GetPropW(self, lpString), hData);
#pragma endregion

public:
	inline operator bool() const reflect_as(WX::IsWindow(hWnd));
	inline operator HWND() const reflect_as(hWnd);
	inline AnyChild *operator&() reflect_as(UserData<AnyChild *>());
	inline AnyChild *operator->() reflect_as(UserData<AnyChild *>());
	inline const AnyChild *operator&() const reflect_as(UserData<const AnyChild *>());
	inline const AnyChild *operator->() const reflect_as(UserData<const AnyChild *>());
	inline auto&operator=(WindowBase &w) reflect_to_child(std::swap(this->hWnd, w.hWnd));
	inline auto&operator=(const WindowBase &w) const reflect_to_child(std::swap(this->hWnd, w.hWnd));
public:
	static inline Window &Attach(HWND &hWnd) reflect_as(ref_as<Window>(hWnd));
};
template<class AnyChild, class SubXCreate, class Style, class StyleEx>
using WXCreate = typename WindowBase<AnyChild>::template XCreate<SubXCreate, Style, StyleEx>;
template<class AnyChild> ATOM WindowBase<AnyChild>::_ClassAtom = 0;
#pragma endregion

#pragma region Clipboard

enum_class(ClipboardStandardFormats, UINT,
	Text           = CF_TEXT,
	Bitmap         = CF_BITMAP,
	MetafilePict   = CF_METAFILEPICT,
	Sylk           = CF_SYLK,
	Dif            = CF_DIF,
	Tiff           = CF_TIFF,
	OemText        = CF_OEMTEXT,
	Dib            = CF_DIB,
	Palette        = CF_PALETTE,
	PenData        = CF_PENDATA,
	Riff           = CF_RIFF,
	Wave           = CF_WAVE,
	UnicodeText    = CF_UNICODETEXT,
	EnhMetaFile    = CF_ENHMETAFILE,
	HDrop          = CF_HDROP,
	Locale         = CF_LOCALE,
	BitmapV5Header = CF_DIBV5);

class ClipboardIFormat {
	mutable UINT uFormat;
protected:
	ClipboardIFormat(UINT uFormat) : uFormat(uFormat) {}
	ClipboardIFormat(const ClipboardIFormat &f) : uFormat(f.uFormat) {}
public:
	ClipboardIFormat(ClipboardIFormat &f) : uFormat(f.uFormat) {}
	ClipboardIFormat(ClipboardIFormat &&f) : uFormat(f.uFormat) {}
public:
	//inline void Register() const reflect_to(WX::RegisterClipboardFormat(uFormat));
	inline bool Available() const reflect_as(WX::IsClipboardFormatAvailable(uFormat));
	inline ClipboardIFormat Next() reflect_as(WX::EnumClipboardFormats(uFormat));
	//inline void AddListener(HWND hwnd) reflect_to(WX::AddClipboardFormatListener(hwnd));
	//inline void RemoveListener(HWND hwnd) reflect_to(WX::RemoveClipboardFormatListener(hwnd));
public: // Property - Count
	/* R */ inline int Count() const reflect_as(WX::CountClipboardFormats());
public: // Property - Name
	template<size_t MaxLen = MaxLenClass, bool IsUnicode = WX::IsUnicode>
	/* R */ inline StringX<IsUnicode> Name() const {
		StringX<IsUnicode> str(MaxLen);
		auto len = WX::GetClipboardFormatName(uFormat, str, (int)MaxLen);
		return inject(str.Resize(len));
	}
	template<size_t MaxLen = MaxLenClass>
	/* R */ inline StringA NameA() const reflect_as(Name<MaxLen, false>());
	template<size_t MaxLen = MaxLenClass>
	/* R */ inline StringW NameW() const reflect_as(Name<MaxLen, true>());
public:
	inline operator bool() const reflect_as(WX::IsClipboardFormatAvailable(uFormat));
	inline operator HANDLE() const reflect_as(WX::GetClipboardData(uFormat));
	inline void operator=(HANDLE hMem) reflect_to(WX::SetClipboardData(uFormat, hMem));
	inline auto &operator++() reflect_to_self(uFormat = WX::EnumClipboardFormats(uFormat));
	inline auto &operator++() const reflect_to_self(uFormat = WX::EnumClipboardFormats(uFormat));
	inline ClipboardIFormat operator++(int) reflect_to(auto f = uFormat; uFormat = WX::EnumClipboardFormats(uFormat), f);
	inline const ClipboardIFormat operator++(int) const reflect_to(auto f = uFormat; uFormat = WX::EnumClipboardFormats(uFormat), f);
};
class ClipboardItf {
public:
	using IFormat = ClipboardIFormat;
public:
	static inline void Open(HWND hWnd) reflect_to(WX::OpenClipboard(hWnd));
	static inline void Close() reflect_to(WX::CloseClipboard());
public:
	static inline bool ChangeChain(HWND hWndRemove, HWND hWndNewNext) reflect_as(WX::ChangeClipboardChain(hWndRemove, hWndNewNext));
	static inline void Empty() reflect_to(WX::EmptyClipboard());

public: // Formats
	static inline UINT RegisterFormat(LPCSTR lpszFormat) reflect_as(WX::RegisterClipboardFormat(lpszFormat));
#pragma region Properties
public: // Property - SequenceNumber
	/* R */ inline DWORD SequenceNumber() const reflect_as(WX::GetClipboardSequenceNumber());
public: // Property - Owner
	template<class AnyChild = void>
	/* R */ inline WindowShim<AnyChild> Owner() reflect_as(WX::GetClipboardOwner());
	template<class AnyChild = void>
	/* R */ inline CWindowShim<AnyChild> Owner() const reflect_as(WX::GetClipboardOwner());
public: // Property - Viewer
	/* W */ inline auto &Viewer(HWND hWnd) reflect_to_self(WX::SetClipboardViewer(hWnd));
	template<class AnyChild = void>
	/* R */ inline WindowShim<AnyChild> Viewer() reflect_as(WX::GetClipboardViewer());
	template<class AnyChild = void>
	/* R */ inline CWindowShim<AnyChild> Viewer() const reflect_as(WX::GetClipboardViewer());
public: // Property - Opener
	template<class AnyChild = void>
	/* R */ inline WindowShim<AnyChild> Opener() reflect_as(WX::GetOpenClipboardWindow());
	template<class AnyChild = void>
	/* R */ inline CWindowShim<AnyChild> Opener() const reflect_as(WX::GetOpenClipboardWindow());
public: // Property - Format
//	/* W */ inline auto &Format()
#pragma endregion
} Clipboard;
#pragma endregion

}
