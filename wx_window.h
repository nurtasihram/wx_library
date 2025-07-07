#pragma once

#include <unordered_map>
#include <typeinfo>

#include "wx_resource.h"

namespace WX {

template<class AnyChild>
class WindowBase;
using Window = WindowBase<void>;
using CWindow = RefAs<Window>;
template<class AnyChild>
using WindowShim = RefAs<WindowBase<AnyChild>>;

#pragma region Misc
struct KEY_FLAGS {
	uint16_t wScanCode : 8;
	uint16_t bExtend : 1;
	uint16_t ___reserved : 4;
	uint16_t bContext : 1;
	uint16_t bPrevious : 1;
	uint16_t bTranslated : 1;
};

#pragma region Window Styles
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

enum_class(WindowShowFlags, int,
	Hide             = SW_HIDE,
	ShowNormal       = SW_SHOWNORMAL,
	Normal           = SW_NORMAL,
	ShowMinimized    = SW_SHOWMINIMIZED,
	ShowMaximized    = SW_SHOWMAXIMIZED,
	Maximize         = SW_MAXIMIZE,
	ShowNoActivate   = SW_SHOWNOACTIVATE,
	Show             = SW_SHOW,
	Minimize         = SW_MINIMIZE,
	ShowMinNoActive  = SW_SHOWMINNOACTIVE,
	ShowNA           = SW_SHOWNA,
	Restore          = SW_RESTORE,
	ShowDefault      = SW_SHOWDEFAULT,
	ForceMinimize    = SW_FORCEMINIMIZE,
	Max              = SW_MAX);
using SW = WindowShowFlags;

enum_flags(WindowPosFlag, UINT,
	NoSize          = SWP_NOSIZE,
	NoMove          = SWP_NOMOVE,
	NoZOrder        = SWP_NOZORDER,
	NoRedraw        = SWP_NOREDRAW,
	NoActivate      = SWP_NOACTIVATE,
	FrameChanged    = SWP_FRAMECHANGED,
	ShowWindow      = SWP_SHOWWINDOW,
	HideWindow      = SWP_HIDEWINDOW,
	NoCopyBits      = SWP_NOCOPYBITS,
	NoOwnerZOrder   = SWP_NOOWNERZORDER,
	NoSendChanging  = SWP_NOSENDCHANGING,
	DeferErase      = SWP_DEFERERASE,
	AsyncWindowPos  = SWP_ASYNCWINDOWPOS,
	DrawFrame       = SWP_DRAWFRAME,
	NoReposition    = SWP_NOREPOSITION);
using SWP = WindowPosFlag;

struct WindowPosition : public RefAs<WINDOWPOS> {
	using super = RefAs<WINDOWPOS>;
	using Flag = WindowPosFlag;
public:
	WindowPosition() {}
	WindowPosition(const WINDOWPOS &w) : super(w) {}
public: // Property - Window
	/* W */ inline auto &Window(HWND hwnd) reflect_as(self->hwnd = hwnd);
	template<class AnyChild>
	/* R */ inline WindowBase<AnyChild> Window() const reflect_as(self->hwnd);
public: // Property - WindowInsertAfter
	/* W */ inline auto &WindowInsertAfter(HWND hwndInsertAfter) reflect_to_self(self->hwndInsertAfter = hwndInsertAfter);
	template<class AnyChild>
	/* R */ inline WindowBase<AnyChild> WindowInsertAfter() const reflect_as(self->hwndInsertAfter);
public: // Property - Position
	/* W */ inline auto &Position(LPoint p) reflect_to_self(self->x = p.x, self->y = p.y);
	/* R */ inline LPoint Position() const reflect_as({ self->x, self->y });
public: // Property - Size
	/* W */ inline auto &Size(LSize s) reflect_to_self(self->cx = s.cx, self->cy = s.cy);
	/* R */ inline LSize Size() const reflect_as({ self->cx, self->cy });
public: // Property - Rect
	/* W */ inline auto &Rect(LRect r) reflect_to_self(Size(r), Position(r.left_top()));
	/* R */ inline LRect Rect() const reflect_as(LRect(Position(), Size()));
public: // Property - Flags
	/* W */ inline auto &Flags(Flag flags) reflect_to_self(self->flags = flags.yield());
	/* R */ inline Flag Flags() const reflect_as(reuse_as<Flag>(self->flags));
public:
} ;
using WndPos = WindowPosition;
using WindowPos = WindowPosition;

struct WindowPlacement : public RefAs<WINDOWPLACEMENT> {
	using super = RefAs<WINDOWPLACEMENT>;
public:
	WindowPlacement() reflect_to(self->length = sizeof(WINDOWPLACEMENT));
public:// Property - SetMinPosition
	/* W */ inline auto &SetMinPosition(bool bEnabled) reflect_to_self(if (bEnabled) self->flags |= WPF_SETMINPOSITION; else self->flags &= ~WPF_SETMINPOSITION);
	/* R */ inline bool  SetMinPosition() const reflect_as(self->flags & WPF_SETMINPOSITION);
public:// Property - RestoreToMaximized
	/* W */ inline auto &RestoreToMaximized(bool bEnabled) reflect_to_self(if (bEnabled) self->flags |= WPF_RESTORETOMAXIMIZED; else self->flags &= ~WPF_RESTORETOMAXIMIZED);
	/* R */ inline bool  RestoreToMaximized() const reflect_as(self->flags & WPF_RESTORETOMAXIMIZED);
public:// Property - Async
	/* W */ inline auto &Async(bool bEnabled) reflect_to_self(if (bEnabled) self->flags |= WPF_ASYNCWINDOWPLACEMENT; else self->flags &= ~WPF_ASYNCWINDOWPLACEMENT);
	/* R */ inline bool  Async() const reflect_as(self->flags & WPF_ASYNCWINDOWPLACEMENT);
public: // Property - ShowFlags
	/* W */ inline auto &ShowFlags(SW flags) reflect_to_self(self->showCmd = flags.yield());
	/* S */ inline SW   &ShowFlags() reflect_as(ref_as<SW>(self->showCmd));
	/* R */ inline SW    ShowFlags() const reflect_as(reuse_as<SW>(self->showCmd));
public: // Property - MinPosition
	/* W */ inline auto   &MinPosition(LPoint ptMinPosition) reflect_to_self(self->ptMinPosition = ptMinPosition);
	/* S */ inline LPoint &MinPosition() reflect_as(ref_as<LPoint>(self->ptMinPosition));
	/* R */ inline LPoint  MinPosition() const reflect_as(self->ptMinPosition);
public: // Property - MaxPosition
	/* W */ inline auto &MaxPosition(LPoint ptMaxPosition) reflect_to_self(self->ptMaxPosition = ptMaxPosition);
	/* S */ inline LPoint &MaxPosition() reflect_as(ref_as<LPoint>(self->ptMaxPosition));
	/* R */ inline LPoint MaxPosition() const reflect_as(self->ptMaxPosition);
public: // Property - NormalPosition
	/* W */ inline auto &NormalPosition(LRect rcNormalPosition) reflect_to_self(self->rcNormalPosition = rcNormalPosition);
	/* S */ inline LRect &NormalPosition() reflect_as(ref_as<LRect>(self->rcNormalPosition));
	/* R */ inline LRect NormalPosition() const reflect_as(self->rcNormalPosition);
};

struct WindowInformation : public RefAs<WINDOWINFO> {
	using super = RefAs<WINDOWINFO>;
public:
	WindowInformation() reflect_to(self->cbSize = sizeof(WINDOWINFO));
public: // Property - Rect
	/* W */ inline auto &Rect(LRect rc) reflect_to_self(self->rcWindow = rc);
	/* R */ inline LRect Rect() const reflect_as(self->rcWindow);
public: // Property - Client
	/* W */ inline auto &ClientRect(LRect rc) reflect_to_self(self->rcClient = rc);
	/* R */ inline LRect ClientRect() const reflect_as(self->rcClient);
public: // Property - Styles
	template<class AnyFlags = WS>
	/* R */ inline auto &Styles(AnyFlags styles) reflect_to_self(self->dwStyle = styles.yield());
	template<class AnyFlags = WS>
	/* R */ inline AnyFlags Styles() const reflect_as(reuse_as<AnyFlags>(self->dwStyle));
public: // Property - StylesEx
	template<class AnyFlags = WSEX>
	/* W */ inline auto &StylesEx(AnyFlags styles) reflect_to_self(self->dwExStyle = styles.yield());
	template<class AnyFlags = WSEX>
	/* R */ inline AnyFlags StylesEx() const reflect_as(reuse_as<AnyFlags>(self->dwExStyle));
public: // Property - Status
	/* W */ inline auto &Status(DWORD dwStatus) reflect_to_self(self->dwWindowStatus = dwStatus);
	/* R */ inline DWORD Status() const reflect_as(self->dwWindowStatus);
public: // Property - Borders
	/* W */ inline auto &Borders(LPoint border) reflect_to_self(self->cxWindowBorders = border.x, self->cyWindowBorders = border.y);
	/* R */ inline LPoint Borders() const reflect_as({ (LONG)self->cxWindowBorders, (LONG)self->cyWindowBorders });
public: // Property - ClassAtom
	/* W */ inline auto &ClassAtom(ATOM atom) reflect_to_self(self->atomWindowType = atom);
	/* R */ inline ATOM ClassAtom() const reflect_as(self->atomWindowType);
public: // Property - CreatorVersion
	/* W */ inline auto &CreatorVersion(WORD wCreatorVersion) reflect_to_self(self->wCreatorVersion = wCreatorVersion);
	/* R */ inline WORD CreatorVersion() const reflect_as(self->wCreatorVersion);
};
using WindowInfo = WindowInformation;

class WindowProcedure {
	WNDPROC pfnWndProc = O;
public:
	WindowProcedure() {}
	WindowProcedure(WNDPROC pfnWndProc) : pfnWndProc(pfnWndProc) {}
public:
	inline LRESULT Call(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) const reflect_as(CallWindowProc(pfnWndProc, hWnd, Msg, wParam, lParam));
	inline LRESULT CallA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) const reflect_as(CallWindowProcA(pfnWndProc, hWnd, Msg, wParam, lParam));
	inline LRESULT CallW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) const reflect_as(CallWindowProcW(pfnWndProc, hWnd, Msg, wParam, lParam));
public:
	inline LRESULT operator()(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) const reflect_as(Call(hWnd, Msg, wParam, lParam));
	inline bool operator<=(HWND hWnd) {
		if (auto lpfnWndProc = GetWindowLongPtr(hWnd, GWLP_WNDPROC)) {
			this->pfnWndProc = reuse_as<WNDPROC>(lpfnWndProc);
			return true;
		}
		return false;
	}
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
struct TrackMouseEventBox : public RefAs<TRACKMOUSEEVENT> {
	using super = RefAs<TRACKMOUSEEVENT>;
	using Flag = TrackMouseFlag;
public:
	TrackMouseEventBox(HWND hWnd) : super(TRACKMOUSEEVENT{ 0 }) {
		self->cbSize = sizeof(TRACKMOUSEEVENT);
		self->hwndTrack = hWnd;
	}
public: // Property - HoverTime
	/* W */ inline auto &HoverTime(DWORD dwHoverTime) reflect_to_self(self->dwHoverTime = dwHoverTime);
	/* R */ inline DWORD HoverTime() const reflect_as(self->dwHoverTime);
public: // Property - Flags
	/* W */ inline auto &Flags(Flag flag) reflect_to_self(self->dwFlags = flag.yield());
	/* R */ inline Flag  Flags() const reflect_as(ref_as<Flag>(self->dwFlags));
public:
	inline operator bool() reflect_as(TrackMouseEvent(&self));
};
using TME = TrackMouseEventBox;

struct PaintStruct : public RefAs<PAINTSTRUCT> {
	using super = RefAs<PAINTSTRUCT>;
public:
	PaintStruct() {}
	PaintStruct(const PAINTSTRUCT &ps) : super(ps) {}
public: // Property - DC
	/* R */ inline CDC DC() reflect_as(self->hdc);
public: // Property - Erase
	/* W */ inline auto&Erase(bool fErase) reflect_to_self(self->fErase = fErase);
	/* R */ inline bool Erase() const reflect_as(self->fErase);
public: // Property - Rect
	/* W */ inline auto &Rect(LRect rcPaint) reflect_to_self(self->rcPaint = rcPaint);
	/* R */ inline LRect Rect() const reflect_as(self->rcPaint);
};

struct Message : public RefAs<MSG> {
	using super = RefAs<MSG>;
public:
	Message() {}
	Message(const MSG &msg) : super(msg) {}
	Message(HWND hwnd, UINT  message, WPARAM wParam, LPARAM lParam) : super(MSG{ hwnd, message, wParam, lParam }) {}
public: // Property - Window
	/* W */ inline auto &Window(HWND hwnd) reflect_as(self->hwnd);
	template<class Child = void>
	/* R */ inline RefAs<WindowBase<Child>> Window() const reflect_as(reuse_as<WX::WindowBase<Child>>(self->hwnd));
public: // Property - ID
	/* W */ inline auto &ID(UINT msgid) reflect_to_self(self->message = msgid);
	template<class AnyEnum = UINT>
	/* R */ inline AnyEnum ID() const reflect_as(reuse_as<AnyEnum>(self->message));
public: // Property - ParamW
	template<class AnyType = WPARAM>
	/* W */ inline auto  &ParamW(AnyType wParam) reflect_to_self(self->wParam = small_cast<WPARAM>(wParam));
	template<class AnyType = WPARAM>
	/* R */ inline AnyType ParamW() const reflect_as(big_cast<AnyType>(self->wParam));
public: // Property - ParamL
	template<class AnyType = WPARAM>
	/* W */ inline auto &ParamL(AnyType lParam) reflect_to_self(self->lParam = small_cast<LPARAM>(lParam));
	template<class AnyType = WPARAM>
	/* R */ inline AnyType ParamL() const reflect_as(big_cast<AnyType>(self->lParam));
public: // Property - Param
	template<class WParam = WPARAM, class LParam = LPARAM>
	/* W */ inline auto &Param(WParam wParam, LParam lParam) reflect_to_self(self->wParam = small_cast<WPARAM>(wParam), self->lParam = small_cast<LPARAM>(lParam));
public: // Property - Time
	/* W */ inline auto &Time(DWORD time) reflect_to_self(self->time = time);
	/* R */ inline DWORD Time() const reflect_as(self->time);
public: // Property - Point
	/* W */ inline auto &Point(POINT pt) reflect_to_self(self->pt = pt);
	/* R */ inline LPoint Point() const reflect_as(self->pt);
public:
	inline bool Translate() const reflect_as(TranslateMessage(&self));
public:
	template<class RetType = LRESULT>
	inline RetType Dispatch() const reflect_as((RetType)DispatchMessage(&self));
	template<class RetType = LRESULT>
	inline RetType DispatchA() const reflect_as((RetType)DispatchMessageA(&self));
	template<class RetType = LRESULT>
	inline RetType DispatchW() const reflect_as((RetType)DispatchMessageW(&self));
public:
	template<class RetType = LRESULT>
	inline RetType Send() const reflect_as((RetType)SendMessage(self->hwnd, self->message, self->wParam, self->lParam));
	template<class RetType = LRESULT>
	inline RetType SendA() const reflect_as((RetType)SendMessageA(self->hwnd, self->message, self->wParam, self->lParam));
	template<class RetType = LRESULT>
	inline RetType SendW() const reflect_as((RetType)SendMessageW(self->hwnd, self->message, self->wParam, self->lParam));
public:
	inline void Post() assertl_reflect_as(PostMessage(self->hwnd, self->message, self->wParam, self->lParam));
	inline void PostA() assertl_reflect_as(PostMessageA(self->hwnd, self->message, self->wParam, self->lParam));
	inline void PostW() assertl_reflect_as(PostMessageW(self->hwnd, self->message, self->wParam, self->lParam));
public:
	inline bool Get(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_to(auto res = GetMessage(&self, O, wMsgFilterMin, wMsgFilterMax), res);
	inline bool Get(HWND hwnd, UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_to(auto res = GetMessage(&self, hwnd, wMsgFilterMin, wMsgFilterMax), res);
	inline bool GetThread(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_to(auto res = GetMessage(&self, (HWND)-1, wMsgFilterMin, wMsgFilterMax), res);
public:
	inline bool GetSafe(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) nt_assertl_reflect_to(auto res = GetMessage(&self, O, wMsgFilterMin, wMsgFilterMax), res);
	inline bool GetSafe(HWND hwnd, UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) nt_assertl_reflect_to(auto res = GetMessage(&self, hwnd, wMsgFilterMin, wMsgFilterMax), res);
	inline bool GetThreadSafe(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) nt_assertl_reflect_to(auto res = GetMessage(&self, (HWND)-1, wMsgFilterMin, wMsgFilterMax), res);
public:
	class Peeks {
		LPMSG lpMsg;
		HWND hwnd;
		UINT wMsgFilterMin;
		UINT wMsgFilterMax;
		UINT wRemoveMsg = PM_NOREMOVE;
	public:
		Peeks(LPMSG lpMsg, HWND hwnd, UINT wMsgFilterMin, UINT wMsgFilterMax) :
			lpMsg(lpMsg), hwnd(hwnd), wMsgFilterMin(wMsgFilterMin), wMsgFilterMax(wMsgFilterMax) {}
	public:
		inline auto &Remove() reflect_to_self(this->wRemoveMsg |= PM_REMOVE);
		inline auto &NoYield() reflect_to_self(this->wRemoveMsg |= PM_NOYIELD);
		inline auto &Input() reflect_to_self(this->wRemoveMsg |= PM_QS_INPUT);
		inline auto &Paint() reflect_to_self(this->wRemoveMsg |= PM_QS_PAINT);
		inline auto &MessagePost() reflect_to_self(this->wRemoveMsg |= PM_QS_POSTMESSAGE);
		inline auto &MessageSend() reflect_to_self(this->wRemoveMsg |= PM_QS_SENDMESSAGE);
	public:
		inline operator bool() reflect_as(PeekMessage(lpMsg, hwnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg));
	};
	inline Peeks Peek(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_as({ &self, O, wMsgFilterMin, wMsgFilterMax });
	inline Peeks Peek(HWND hwnd, UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_as({ &self, hwnd, wMsgFilterMin, wMsgFilterMax });
	inline Peeks PeekThread(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_as({ &self, (HWND)-1, wMsgFilterMin, wMsgFilterMax });
};
using Msg = Message;
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
template<bool IsUnicode, class AnyChild = void>
class WindowClassBaseX : public RefAs<std::conditional_t<IsUnicode, WNDCLASSW, WNDCLASSA>>,
	public ChainExtend<WindowClassBaseX<IsUnicode, AnyChild>, AnyChild> {
	using WNDCLASS = std::conditional_t<IsUnicode, WNDCLASSW, WNDCLASSA>;
	using LPCTSTR = LPCXSTR<IsUnicode>;
	using String = StringX<IsUnicode>;
public:
	using super = RefAs<WNDCLASS>;
	using Child = KChain<WindowClassBaseX, AnyChild>;
	using Style = CStyle;
public:
	WindowClassBaseX() reflect_to(self->cbClsExtra = (int)sizeof(Child) - (int)sizeof(WNDCLASS));
public: // Property - Styles
	/* W */ inline auto &Styles(Style style) reflect_to_child(self->style = style.yield());
	/* R */ inline Style Styles() const reflect_as(ref_as<Style>(self->style));
public: // Property - WndProc
	/* W */ inline auto &WndProc(WNDPROC lpfnWndProc) reflect_to_child(self->lpfnWndProc = lpfnWndProc);
	/* R */ inline WX::WndProc WndProc() const reflect_as(self->lpfnWndProc);
public: // Property - ClsExtra
	/* W */ inline auto &ClsExtra(int cbClsExtra) reflect_to_child(self->cbClsExtra = cbClsExtra);
	/* R */ inline auto  ClsExtra() const reflect_as(self->cbClsExtra);
public: // Property - WndExtra
	/* W */ inline auto &WndExtra(int cbWndExtra) reflect_to_child(self->cbWndExtra = cbWndExtra);
	/* R */ inline auto  WndExtra() const reflect_as(self->cbWndExtra);
public: // Property - Module
	/* W */ inline auto &Module(HINSTANCE hModule) reflect_to_child(self->hInstance = hModule);
	/* R */ inline CModule Module() const reflect_as(self->hInstance);
public: // Property - Icon
	/* W */ inline auto &Icon(CIcon icon) reflect_to_child(self->hIcon = icon);
	/* W */ inline auto &Icon(LPCTSTR lpszName) reflect_to_child(self->hIcon = Module()->Icon(lpszName));
	/* W */ inline auto &Icon(WORD wID) reflect_to_child(self->hIcon = Module()->Icon(wID));
	/* R */ inline CIcon Icon() const reflect_as(self->hIcon);
public: // Property - Cursor
	/* W */ inline auto &Cursor(CCursor cursor) reflect_to_child(self->hCursor = cursor);
	/* W */ inline auto &Cursor(LPCTSTR lpszName) reflect_to_child(self->hCursor = Module()->Cursor(lpszName));
	/* W */ inline auto &Cursor(WORD wID) reflect_to_child(self->hCursor = Module()->Cursor(wID));
	/* R */ inline CCursor Cursor() const reflect_as(self->hCursor);
public: // Property - Background
	/* W */ inline auto &Background(CBrush brush) reflect_to_child(self->hbrBackground = brush);
	/* R */ inline CBrush Background() const reflect_as(self->hbrBackground);
public: // Property - Menu
	/* W */ inline auto &Menu(LPCTSTR lpszMenuName) reflect_to_child(self->lpszMenuName = lpszMenuName);
	/* W */ inline auto &Menu(WORD wID) reflect_to_child(self->lpszMenuName = (LPCTSTR)MAKEINTRESOURCE(wID));
	/* R */ inline CMenu Menu() const reflect_as(Module()->Menu(self->lpszMenuName));
public: // Property - Name
	/* W */ inline auto &Name(LPCTSTR lpszClassName) reflect_to_child(self->lpszClassName = lpszClassName);
	/* R */ inline String Name() const {
		if (!self->lpszClassName)
			return O;
		if (IS_INTRESOURCE(self->lpszClassName))
			return format("#%d", (ATOM)(ULONG_PTR)self->lpszClassName);
		return CString(self->lpszClassName, MaxLenClass);
	}
public: // Property - Atom
	/* W */ inline auto &Atom(ATOM classAtom) reflect_to_child(self->lpszClassName = (LPCTSTR)MAKEINTRESOURCE(classAtom));
	/* R */ inline ATOM  Atom() const reflect_as(IS_INTRESOURCE(self->lpszClassName) ? (ATOM)(ULONG_PTR)self->lpszClassName : 0);
public:
	inline ATOM Register() const assertl_reflect_as(auto atom = AnyX<IsUnicode>(RegisterClassA, RegisterClassW)(&self), atom);
	inline ATOM Unregister() const assertl_reflect_as(auto atom = AnyX<IsUnicode>(UnregisterClassA, UnregisterClassW)(self->lpszClassName, self->hInstance), atom);
	inline auto &GetInfo() assertl_reflect_as_self(AnyX<IsUnicode>(GetClassInfoA, GetClassInfoW)(self->hInstance, self->lpszClassName, &self))
};
using WindowClass = WindowClassBaseX<IsUnicode>;
using WindowClassA = WindowClassBaseX<false>;
using WindowClassW = WindowClassBaseX<true>;
template<bool IsUnicode, class AnyChild = void>
class WindowClassExBaseX : public RefAs<std::conditional_t<IsUnicode, WNDCLASSEXW, WNDCLASSEXA>>,
	public ChainExtend<WindowClassExBaseX<IsUnicode, AnyChild>, AnyChild> {
	using WNDCLASSEX = std::conditional_t<IsUnicode, WNDCLASSEXW, WNDCLASSEXA>;
	using LPCTSTR = LPCXSTR<IsUnicode>;
	using String = StringX<IsUnicode>;
public:
	using super = RefAs<WNDCLASSEX>;
	using Child = KChain<WindowClassExBaseX, AnyChild>;
	using Style = CStyle;
public:
	WindowClassExBaseX() {
		self->cbClsExtra = (int)sizeof(Child) - (int)sizeof(WNDCLASSEX);
		self->cbSize = (int)sizeof(WNDCLASSEX);
	}
public: // Property - Styles
	/* W */ inline auto &Styles(Style style) reflect_to_child(self->style = style.yield());
	/* R */ inline Style Styles() const reflect_as(ref_as<Style>(self->style));
public: // Property - WndProc
	/* W */ inline auto &WndProc(WNDPROC lpfnWndProc) reflect_to_child(self->lpfnWndProc = lpfnWndProc);
	/* R */ inline WX::WndProc WndProc() const reflect_as(self->lpfnWndProc);
public: // Property - ClsExtra
	/* W */ inline auto &ClsExtra(int cbClsExtra) reflect_to_child(self->cbClsExtra = cbClsExtra);
	/* R */ inline auto  ClsExtra() const reflect_as(self->cbClsExtra);
public: // Property - WndExtra
	/* W */ inline auto &WndExtra(int cbWndExtra) reflect_to_child(self->cbWndExtra = cbWndExtra);
	/* R */ inline auto  WndExtra() const reflect_as(self->cbWndExtra);
public: // Property - Module
	/* W */ inline auto &Module(HINSTANCE hModule) reflect_to_child(self->hInstance = hModule);
	/* R */ inline CModule Module() const reflect_as(self->hInstance);
public: // Property - Icon
	/* W */ inline auto &Icon(CIcon icon) reflect_to_child(self->hIcon = icon);
	/* W */ inline auto &Icon(LPCTSTR lpszName) reflect_to_child(self->hIcon = Module()->Icon(lpszName));
	/* W */ inline auto &Icon(WORD wID) reflect_to_child(self->hIcon = Module()->Icon(wID));
	/* R */ inline CIcon Icon() const reflect_as(self->hIcon);
public: // Property - Cursor
	/* W */ inline auto &Cursor(CCursor cursor) reflect_to_child(self->hCursor = cursor);
	/* W */ inline auto &Cursor(LPCTSTR lpszName) reflect_to_child(self->hCursor = Module()->Cursor(lpszName));
	/* W */ inline auto &Cursor(WORD wID) reflect_to_child(self->hCursor = Module()->Cursor(wID));
	/* R */ inline CCursor Cursor() const reflect_as(self->hCursor);
public: // Property - Background
	/* W */ inline auto &Background(CBrush brush) reflect_to_child(self->hbrBackground = brush);
	/* R */ inline CBrush Background() const reflect_as(self->hbrBackground);
public: // Property - Menu
	/* W */ inline auto &Menu(LPCTSTR lpszMenuName) reflect_to_child(self->lpszMenuName = lpszMenuName);
	/* W */ inline auto &Menu(WORD wID) reflect_to_child(self->lpszMenuName = (LPCTSTR)MAKEINTRESOURCE(wID));
	/* R */ inline CMenu Menu() const reflect_as(Module()->Menu(self->lpszMenuName));
public: // Property - Name
	/* W */ inline auto &Name(LPCTSTR lpszClassName) reflect_to_child(self->lpszClassName = lpszClassName);
	/* R */ inline String Name() const {
		if (!self->lpszClassName)
			return O;
		if (IS_INTRESOURCE(self->lpszClassName))
			return format("#%d", (ATOM)(ULONG_PTR)self->lpszClassName);
		return CString(self->lpszClassName, MaxLenClass);
	}
public: // Property - Atom
	/* W */ inline auto &Atom(ATOM classAtom) reflect_to_child(self->lpszClassName = (LPCTSTR)MAKEINTRESOURCE(classAtom));
	/* R */ inline ATOM  Atom() const reflect_as(IS_INTRESOURCE(self->lpszClassName) ? (ATOM)(ULONG_PTR)self->lpszClassName : 0);
public: // Property - IconSmall
	/* W */ inline auto &IconSmall(HICON hIconSm) reflect_to_child(self->hIconSm = hIconSm);
	/* W */ inline auto &IconSmall(LPCTSTR lpszName) reflect_to_child(self->hIconSm = Module()->Icon(lpszName));
	/* W */ inline auto &IconSmall(WORD wID) reflect_to_child(self->hIconSm = Module()->Icon(wID));
	/* R */ inline CIcon IconSmall() const reflect_as(self->hIconSm);
public:
	inline ATOM Register() const assertl_reflect_as(auto atom = AnyX<IsUnicode>(RegisterClassExA, RegisterClassExW)(self), atom);
	inline ATOM Unregister() const assertl_reflect_as(auto atom = AnyX<IsUnicode>(UnregisterClassA, UnregisterClassW)(self->lpszClassName, self->hInstance), atom);
	inline auto &GetInfo() assertl_reflect_as_self(AnyX<IsUnicode>(GetClassInfoExA, GetClassInfoExW)(self->hInstance, self->lpszClassName, self))
};
using WindowClassEx = WindowClassExBaseX<IsUnicode>;
using WindowClassExA = WindowClassExBaseX<false>;
using WindowClassExW = WindowClassExBaseX<true>;
#pragma endregion

#pragma region CreateStruct
static inline HWND WindowCreate(const CREATESTRUCTA &cs) assertl_reflect_as(
	auto h = CreateWindowExA(
		cs.dwExStyle, cs.lpszClass, cs.lpszName, cs.style,
		cs.x, cs.y, cs.cx, cs.cy,
		cs.hwndParent, cs.hMenu, cs.hInstance,
		cs.lpCreateParams), h);
static inline HWND WindowCreate(const CREATESTRUCTW &cs) assertl_reflect_as(
	auto h = CreateWindowExW(
		cs.dwExStyle, cs.lpszClass, cs.lpszName, cs.style,
		cs.x, cs.y, cs.cx, cs.cy,
		cs.hwndParent, cs.hMenu, cs.hInstance,
		cs.lpCreateParams), h);
static inline HWND WindowCreateMDI(const CREATESTRUCTA &cs) assertl_reflect_as(
	auto h = CreateMDIWindowA(
		cs.lpszClass, cs.lpszName, cs.style,
		cs.x, cs.y, cs.cx, cs.cy,
		cs.hwndParent, cs.hInstance,
		(LPARAM)cs.lpCreateParams), h);
static inline HWND WindowCreateMDI(const CREATESTRUCTW &cs) assertl_reflect_as(
	auto h = CreateMDIWindowW(
		cs.lpszClass, cs.lpszName, cs.style,
		cs.x, cs.y, cs.cx, cs.cy,
		cs.hwndParent, cs.hInstance,
		(LPARAM)cs.lpCreateParams), h);
template<bool IsUnicode, class AnyChild = void, class Style = WStyle, class StyleEx = WStyleEx>
class CreateStructBaseX : public RefAs<std::conditional_t<IsUnicode, CREATESTRUCTW, CREATESTRUCTA>>,
	public ChainExtend<CreateStructBaseX<IsUnicode, AnyChild, Style, StyleEx>, AnyChild> {
	using CREATESTRUCT = std::conditional_t<IsUnicode, CREATESTRUCTW, CREATESTRUCTA>;
	using LPCTSTR = LPCXSTR<IsUnicode>;
	using String = StringX<IsUnicode>;
public:
	using super = RefAs<CREATESTRUCT>;
public:
	CreateStructBaseX() {}
	CreateStructBaseX(const CREATESTRUCT &cs) : super(cs) {}
public: // Property - Param
	/* W */ inline auto &Param(LPVOID lpCreateParams) reflect_to_child(self->lpCreateParams = lpCreateParams);
	template<class AnyType = void>
	/* R */ inline AnyType *Param() reflect_as((AnyType *)self->lpCreateParams);
public: // Property - Module
	/* W */ inline auto   &Module(HINSTANCE hInstance) reflect_to_child(self->hInstance = hInstance);
	/* R */ inline CModule Module() const reflect_as(self->hInstance);
public: // Property - Menu
	/* W */ inline auto &Menu(HMENU hMenu) reflect_to_child(self->hMenu = hMenu);
	/* R */ inline CMenu Menu() const reflect_as(self->hMenu);
public: // Property - Parent
	/* W */ inline auto &Parent(HWND hwndParent) reflect_to_child(self->hwndParent = hwndParent);
	template<class _AnyChild = void>
	/* R */ inline WindowBase<_AnyChild> Parent() const reflect_as(self->hwndParent);
public: // Property - Styles
	/* W */ inline auto &Styles(Style style) reflect_to_child(self->style = style.yield());
	/* R */ inline Style Styles() const reflect_as(ref_as<Style>(self->style));
public: // Property - Caption
	/* W */ inline auto  &Caption(LPCTSTR name) reflect_to_child(self->lpszName = name);
	/* R */ inline String Caption() const reflect_as(CString(self->lpszName, MaxLenTitle));
public: // Property - Class
	/* W */ inline auto &Class(LPCTSTR lpszClassName) reflect_to_child(self->lpszClass = lpszClassName);
	/* W */ inline auto &Class(ATOM classAtom) reflect_to_child(self->lpszClass = (LPCTSTR)MAKEINTRESOURCE(classAtom));
	/* R */ inline String ClassName() const {
		if (!self->lpszClass)
			return O;
		if (IS_INTRESOURCE(self->lpszClass))
			return format("#%d", (ATOM)(ULONG_PTR)self->lpszClass);
		return CString(self->lpszClass, MaxLenClass);
	}
	/* R */ inline ATOM   ClassAtom() const reflect_as(IS_INTRESOURCE(self->lpszClass) ? (ATOM)(ULONG_PTR)self->lpszClass : 0);
public: // Property - StylesEx
	/* W */ inline auto   &StylesEx(StyleEx dwExStyle) reflect_to_child(self->dwExStyle = dwExStyle.yield());
	/* R */ inline StyleEx StylesEx() const reflect_as(ref_as<StyleEx>(self->dwExStyle));
public: // Property - Size
	/* W */ inline auto &Size(LSize size) reflect_to_child(self->cx = size.cx, self->cy = size.cy);
	/* R */ inline LSize Size() const reflect_as({ self->cx, self->cy });
public: // Property - Position
	/* W */ inline auto  &Position(LPoint pos) reflect_to_child(self->x = pos.x, self->y = pos.y);
	/* R */ inline LPoint Position() const reflect_as({ self->x, self->y });
public: // Property - Rect
	/* W */ inline auto &Rect(LRect r) reflect_to_child(Size(r), Position(r.left_top()));
	/* R */ inline LRect Rect() const reflect_as(LRect(Position(), Size()));
public: // Property - ClientRect
	/* W */ inline auto &ClientRect(LRect rc) assertl_reflect_as(AdjustWindowRectEx(rc, self->style, self->hMenu ? TRUE : FALSE, self->dwExStyle), Rect(rc));
	/* W */ inline auto &ClientRect(LRect rc, UINT dpi) assertl_reflect_as(AdjustWindowRectExForDpi(rc, self->style, self->hMenu ? TRUE : FALSE, self->dwExStyle, dpi), Rect(rc));
public: // Property - ClientSize
	/* W */ inline auto &ClientSize(LSize sz) reflect_as(ClientRect({ Position(), sz }));
	/* W */ inline auto &ClientSize(LSize sz, UINT dpi) reflect_as(ClientRect({ Position(), sz }, dpi));
public:
	template <class _AnyChild = void>
	inline WindowShim<_AnyChild> Create() const reflect_as(WindowCreate(self));
	template <class _AnyChild = void>
	inline WindowShim<_AnyChild> CreateMDI() const reflect_as(WindowCreateMDI(self));
};
using CreateStruct = CreateStructBaseX<IsUnicode>;
using CreateStructA = CreateStructBaseX<false>;
using CreateStructW = CreateStructBaseX<true>;
#pragma endregion

#pragma region WindowBase
//class WindowProp {
//	HWND hWnd;
//	template<class LPCTSTR>
//	class Prop {
//		HWND hWnd;
//		LPCTSTR lpString;
//	public:
//		Prop(HWND hWnd, LPCTSTR lpString) : hWnd(hWnd), lpString(lpString) {}
////		inline void operator=(HANDLE hData) assertl_reflect_as(SetProp(hWnd, lpString, str.yield()));
//
//	};
//public:
//	WindowProp(HWND hWnd) : hWnd(hWnd) {}
//	inline auto operator[](LPCSTR lpString) {}
//	inline auto operator[](LPCWSTR lpString) {}
//};
template<class AnyChild>
class WindowBase : public ChainExtend<WindowBase<AnyChild>, AnyChild> {
	mutable HWND hWnd = O;
public:
	using Child = KChain<WindowBase, AnyChild>;
	using super = WindowBase;
	using Shim = WindowShim<AnyChild>;
	using Style = WStyle;
	using StyleEx = WStyleEx;
protected:
	friend class RefAs<WindowBase>;
	template<bool IsUnicode, class _AnyChild, class Style, class StyleEx>
	friend class CreateStructBaseX;
	WindowBase(HWND h) : hWnd(h) {}
	WindowBase(const WindowBase &w) : hWnd(w.hWnd) reflect_to(w.hWnd = O);
public:
	WindowBase() {}
	WindowBase(Null) {}
	WindowBase(WindowBase &w) : hWnd(w.hWnd) reflect_to(w.hWnd = O);
	WindowBase(WindowBase &&w) : hWnd(w.hWnd) reflect_to(w.hWnd = O);
	~WindowBase() reflect_to(Delete());
public:
	template<class AnyClass = AnyChild>
	static inline RefAs<WindowBase<AnyChild>> Find(LPCSTR lpszName, LPCSTR lpszClass) assertl_reflect_as(auto h = FindWindowA(lpszClass, lpszName), h);
	template<class AnyClass = AnyChild>
	static inline RefAs<WindowBase<AnyChild>> Find(LPCWSTR lpszName, LPCWSTR lpszClass) assertl_reflect_as(auto h = FindWindowW(lpszClass, lpszName), h);
	template<class AnyClass = AnyChild>
	static inline RefAs<WindowBase<AnyChild>> Find(LPCSTR lpszName) assertl_reflect_as(auto h = FindWindowA(MAKEINTRESOURCEA(WindowBase::_ClassAtom), lpszName), h);
	template<class AnyClass = AnyChild>
	static inline RefAs<WindowBase<AnyChild>> Find(LPCWSTR lpszName) assertl_reflect_as(auto h = FindWindowW(MAKEINTRESOURCEW(WindowBase::_ClassAtom), lpszName), h);
	template<class AnyClass = AnyChild>
	static inline RefAs<WindowBase<AnyChild>> Focussed() reflect_as(GetFocus());
	template<class AnyClass = AnyChild>
	static inline RefAs<WindowBase<AnyChild>> Active() reflect_as(GetActiveWindow());
	template<class AnyClass = AnyChild>
	static inline RefAs<WindowBase<AnyChild>> Desktop() reflect_as(GetDesktopWindow());
	template<class AnyClass = AnyChild>
	static inline RefAs<WindowBase<AnyChild>> Foreground() reflect_as(GetForegroundWindow());
	static inline void Foreground(HWND hWnd) assertl_reflect_as(SetForegroundWindow(hWnd));
public:
	inline void Delete() {
		if (self)
			this->Message().OnDestroy().Send();
	}
public:
	inline auto &Show(SW nShow)     reflect_to_child(ShowWindow(self, nShow.yield()));
	inline auto &Hide()             reflect_as(Show(SW::Hide));
	inline auto &Normal()           reflect_as(Show(SW::Normal));
	inline auto &ShowNormal()       reflect_as(Show(SW::ShowNormal));
	inline auto &ShowMinimized()    reflect_as(Show(SW::ShowMinimized));
	inline auto &ShowMaximized()    reflect_as(Show(SW::ShowMaximized));
	inline auto &ShowNoActivate()   reflect_as(Show(SW::ShowNoActivate));
	inline auto &Show()             reflect_as(Show(SW::Show));
	inline auto &Maximize()         reflect_as(Show(SW::Maximize));
	inline auto &Minimize()         reflect_as(Show(SW::Minimize));
	inline auto &ForceMinimize()    reflect_as(Show(SW::ForceMinimize));
	inline auto &ShowMinNoActive()  reflect_as(Show(SW::ShowMinNoActive));
	inline auto &ShowDefault()      reflect_as(Show(SW::ShowDefault));
	inline auto &ShowNA()           reflect_as(Show(SW::ShowNA));
	inline auto &Restore()          reflect_as(Show(SW::Restore));
	inline auto &Max()              reflect_as(Show(SW::Max));

	inline auto &BringToTop()       assertl_reflect_as_child(::BringWindowToTop(self));

	inline int MsgBox(LPCSTR lpCaption, LPCSTR lpText = O, MB uType = MB::Ok) const reflect_as(WX::MsgBox(lpCaption, lpText, uType, self));
	inline int MsgBox(LPCWSTR lpCaption, LPCWSTR lpText = O, MB uType = MB::Ok) const reflect_as(WX::MsgBox(lpCaption, lpText, uType, self));
	inline int MsgBox(LPCSTR lpCaption, const Exception &err) const reflect_as(WX::MsgBox(lpCaption, err, self));
	inline int MsgBox(LPCWSTR lpCaption, const Exception &err) const reflect_as(WX::MsgBox(lpCaption, err, self));

	inline auto &Focus() reflect_to_child(SetFocus(self));
	inline bool IsFocus() const reflect_as(GetFocus() == self);

	inline LPoint ScreenToClient(LPoint pt) const assertl_reflect_as(::ScreenToClient(self, &pt), pt);
	inline LPoint ClientToScreen(LPoint pt) const assertl_reflect_as(::ClientToScreen(self, &pt), pt);
	inline LRect AdjustRect(LRect rc) const assertl_reflect_as(::AdjustWindowRect(&rc, Styles().yield(), this->Menu()), rc);
	inline LRect AdjustRect() const reflect_to(LRect rc, AdjustRect(rc), rc);

	inline void Validate(LPCRECT lpRect = O) const assertl_reflect_as(ValidateRect(self, lpRect));
	inline void Invalidate(LPCRECT lpRect = O, bool fErase = false) const assertl_reflect_as(InvalidateRect(self, lpRect, fErase));

	inline UINT_PTR SetTimer(UINT uElapse, UINT_PTR nIDEvent = 0) assertl_reflect_as((nIDEvent = ::SetTimer(self, nIDEvent, uElapse, O)), nIDEvent);
	inline void KillTimer(UINT_PTR nIDEvent) assertl_reflect_as(::KillTimer(self, nIDEvent));

	inline void Move(LRect rc, bool bRedraw = true) const assertl_reflect_as(::MoveWindow(self, rc.top, rc.left, rc.xsize(), rc.ysize(), bRedraw));

	inline void Update() assertl_reflect_as(UpdateWindow(self));

	inline void RegisterTouch(bool bFine = true, bool bWantPalm = false) assertl_reflect_as(RegisterTouchWindow(self, (bFine *TWF_FINETOUCH) | (bWantPalm * TWF_WANTPALM)));
	inline void UnregisterTouch() assertl_reflect_as(UnregisterTouchWindow(self));

	class PaintBox : public PaintStruct {
		HWND hwnd;
		HDC hdc1;
	public:
		PaintBox(HWND hwnd) : hwnd(hwnd), hdc1(::BeginPaint(hwnd, self)) {}
		~PaintBox() reflect_to(End());
		inline CDC DDC() const reflect_as(hdc1);
		inline void End() const assertl_reflect_as(EndPaint(hwnd, self));
	};
	inline PaintBox BeginPaint() reflect_as((HWND)self);

	inline TrackMouseEventBox TrackMouse() const reflect_as((HWND)self);

	inline bool HasChild(HWND hWnd) reflect_as(IsChild(self, hWnd));

public:
	using FnEnumWindow = Function<bool(HWND)>;
	using FnEnumProp = Function<bool(HWND, LPTSTR, HANDLE)>;
	using FnEnumPropA = Function<bool(HWND, LPSTR, HANDLE)>;
	using FnEnumPropW = Function<bool(HWND, LPWSTR, HANDLE)>;
private:
	static BOOL EnumWindowProc(HWND hWnd, LPARAM lParam) reflect_as((*(FnEnumWindow *)lParam)(hWnd));
	static BOOL EnumPropProc(HWND hWnd, LPSTR lpString, HANDLE hData, ULONG_PTR lParam) reflect_as((*(FnEnumPropA *)lParam)(hWnd, lpString, hData));
	static BOOL EnumPropProc(HWND hWnd, LPWSTR lpString, HANDLE hData, ULONG_PTR lParam) reflect_as((*(FnEnumPropW *)lParam)(hWnd, lpString, hData));
public:
	template<class AnyFunc>
	static inline void Enum(AnyFunc fnEnum) {
		FnEnumWindow fnEnumWindows([&](HWND hWnd) {
			if constexpr (static_compatible<AnyFunc, bool(HWND)>)
				return fnEnum(hWnd);
			else {
				static_assert(static_compatible<AnyFunc, void(HWND)>, "Invalid function type for Enum");
				fnEnum(hWnd);
				return true;
			}
		});
		EnumWindows(EnumWindowProc, (LPARAM)std::addressof(fnEnumWindows));
	}
	template<class AnyFunc>
	inline void EnumChild(AnyFunc fnEnum) {
		FnEnumWindow fnEnumChildren([&](HWND hWnd) {
			if constexpr (static_compatible<AnyFunc, bool(HWND)>)
				return fnEnum(hWnd);
			else {
				static_assert(static_compatible<AnyFunc, void(HWND)>, "Invalid function type for EnumChild");
				fnEnum(hWnd);
				return true;
			}
		});
		EnumChildWindows(self, EnumWindowProc, (LPARAM)std::addressof(fnEnumChildren));
	}
	template<class AnyFunc>
	inline int EnumProp(AnyFunc fnEnum) {
		if constexpr (static_compatible<AnyFunc, bool(HWND, LPSTR, HANDLE)>) {
			FnEnumPropA fnEnumProps{
				[&](HWND hWnd, LPSTR lpString, HANDLE hData) {
					return fnEnum(hWnd, lpString, hData);
				}
			};
			return EnumPropsExA(self, EnumPropProc, (LPARAM)std::addressof(fnEnumProps));
		}
		elif  constexpr (static_compatible<AnyFunc, bool(HWND, LPWSTR, HANDLE)>) {
			FnEnumPropW fnEnumProps{
				[&](HWND hWnd, LPWSTR lpString, HANDLE hData) {
					return fnEnum(hWnd, lpString, hData);
				}
			};
			return EnumPropsExW(self, EnumPropProc, (LPARAM)std::addressof(fnEnumProps));
		}
		elif  constexpr (static_compatible<AnyFunc, void(HWND, LPSTR, HANDLE)>) {
			FnEnumPropA fnEnumProps{
				[&](HWND hWnd, LPSTR lpString, HANDLE hData) {
					fnEnum(hWnd, lpString, hData);
					return true;
				}
			};
			return EnumPropsExA(self, EnumPropProc, (LPARAM)std::addressof(fnEnumProps));
		}
		else {
			static_assert(static_compatible<AnyFunc, void(HWND, LPWSTR, HANDLE)>, "Invalid function type for EnumProp");
			FnEnumPropW fnEnumProps{
				[&](HWND hWnd, LPWSTR lpString, HANDLE hData) {
					return fnEnum(hWnd, lpString, hData);
					return true;
			}
			};
			return EnumPropsExW(self, EnumPropProc, (LPARAM)std::addressof(fnEnumProps));
		}
	}

	inline HANDLE PropRemove(LPCSTR lpString) nt_assertl_reflect_to(auto hData = RemovePropA(self, lpString), hData);
	inline HANDLE PropRemove(LPCWSTR lpString) nt_assertl_reflect_to(auto hData = RemovePropW(self, lpString), hData);

#pragma region Message Procedure
protected:
	def_memberof(DefProc);
	def_memberof(Callback);
#define MSG_TRANS(msgid, ret, name, ...) \
	def_memberof(name);
#include "wx_msg.inl"
	static LRESULT CallDefProc(HWND hWnd, UINT msgid, WPARAM wParam, LPARAM lParam) {
		if constexpr (member_DefProc_of<Child>::callable) {
			misdef_assert((!std::is_member_pointer_v<decltype(&Child::DefProc)>),
						  "DefProc must be a static method.");
			using tfn_WndProc = LRESULT(HWND, UINT, WPARAM, LPARAM);
			misdef_assert((member_DefProc_of<Child>::template compatible_to<tfn_WndProc>),
						  "DefProc must be compatible to LRESULT(HWND, UINT, WPARAM, LPARAM)");
			return Child::DefProc(hWnd, msgid, wParam, lParam);
		}
		else
			return DefWindowProc(hWnd, msgid, wParam, lParam);
	}
	inline LRESULT HandleNext() const { throw MSG{ 0 }; }
	static LRESULT CALLBACK MainProc(HWND hWnd, UINT msgid, WPARAM wParam, LPARAM lParam) {
		auto &Wnd = WindowBase::Attach(hWnd);
		auto pThis = Wnd.UserData<Child *>();
	retry:
		try {
			switch (msgid) {
				case WM_NCCREATE: {
					auto lpCreate = (LPCREATESTRUCT)lParam;
					pThis = (Child *)lpCreate->lpCreateParams;
					Wnd.UserData(pThis);
					(HWND &)*reuse_as<Window *>(pThis) = hWnd;
					break;
				}
				case WM_COMMAND:
					if (auto wnd = reuse_as<Window>(lParam))
						wnd.Send(WM_USER + (UINT)HIWORD(wParam));
					break;
			}
			if (pThis)
				switch (msgid) {
					case WM_NULL:
						break;
#define _CALL_(name) pThis->name
#define MSG_TRANS(msgid, ret, name, argslist, args, send, call) \
				case msgid: \
					if constexpr (member_##name##_of<Child>::callable) { \
						using fn_type = ret argslist; \
						misdef_assert((member_##name##_of<Child>::template compatible_to<fn_type>), \
										"Member " #name " must be a method compatible to " #ret #argslist); \
						return call; \
					} break;
#include "wx_msg.inl"
				}
			if constexpr (member_Callback_of<Child>::callable)
				return pThis->Callback(msgid, wParam, lParam);
		} catch (MSG msg) {
			if (msg.message)
				return CallDefProc(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		} catch (Exception err) {
			Msg msg{ hWnd, msgid, wParam, lParam };
			if (!pThis)
				throw err;
			if (pThis->Catch(msg, err))
				goto retry;
			return pThis->Final(msg);
		}
		return CallDefProc(hWnd, msgid, wParam, lParam);
	}
protected:
	inline void OnDestroy() reflect_to(PostQuitMessage(0));
protected:
	def_memberof(OnCatch);
	static inline wx_answer Catch(Msg msg, const Exception &err) {
		if constexpr (member_OnCatch_of<AnyChild>::template compatible_to<wx_answer(Msg, Exception)>)
			reflect_as(Child::OnCatch(msg, err))
		elif  constexpr (member_OnCatch_of<AnyChild>::template compatible_to<void(Msg, Exception)>)
			reflect_to(Child::OnCatch(msg, err), false)
		else {
			static_assert(!member_OnCatch_of<AnyChild>::callable, "OnCatch uncompatible");
			switch (msg.Window()->MsgBox(_T("Window Error"), err)) {
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
	def_memberof(OnFinal);
	static inline LRESULT Final(Msg msg) {
		if constexpr (member_OnFinal_of<AnyChild>::template compatible_to<LRESULT(Msg)>)
			reflect_as(Child::OnFinal(msg))
		elif  constexpr (member_OnFinal_of<AnyChild>::template compatible_to<void(Msg)>)
			reflect_to(Child::OnFinal(msg), -1)
		else {
			static_assert(!member_OnFinal_of<AnyChild>::callable, "OnFinal uncallable");
			return -3;
		}
	}
public:
	class CallPack {
		HWND hwnd;
	public:
		CallPack(HWND hwnd) : hwnd(hwnd) {}
#define MSG_TRANS(msgid, ret, name, argslist, args, send, call) \
			inline ret name argslist reflect_as(send);
#define _SEND_(ret, msgid, wparam, lparam) \
			ret(CallDefProc(hwnd, msgid, wparam, lparam))
#include "wx_msg.inl"
	};
	inline CallPack DefProcOf() reflect_as((HWND)self);
#pragma endregion

#pragma region Classes
protected:
	static ATOM _ClassAtom;
	static HINSTANCE _hClassModule;
public:
	static inline auto &CClassNameA() {
		static const StringA _ClassNameA = CString(typeid(Child).name(), MaxLenClass);
		return _ClassNameA;
	}
	static inline auto &CClassNameW() {
		static const StringW _ClassNameW = FitsW(CString(typeid(Child).name(), MaxLenClass));
		return _ClassNameW;
	}
	template<bool IsUnicode>
	static inline auto &CClassName() reflect_as(AnyX<IsUnicode>(CClassNameA, CClassNameW)());
	static inline auto &CClassName() reflect_as(CClassName<IsUnicode>());
protected:
	template<bool IsUnicode, class SubClass = void>
	class XClassBase : public WindowClassBaseX<IsUnicode, KChain<XClassBase<IsUnicode, SubClass>, SubClass>> {
		using LPCTSTR = LPCXSTR<IsUnicode>;
	public:
		using Child = KChain<XClassBase<IsUnicode, SubClass>, SubClass>;
		using super = WindowClassBaseX<IsUnicode, Child>;
	public:
		XClassBase() {
			super::WndProc(MainProc);
			super::Name(CClassName<IsUnicode>());
			this->Cursor(IDC_ARROW);
			this->Styles(ClassStyle::Redraw);
			this->Background(SysColor::Window);
		}
	};
	template<class SubClass = void>
	using XClass = XClassBase<IsUnicode, SubClass>;
	template<class SubClass = void>
	using XClassA = XClassBase<false, SubClass>;
	template<class SubClass = void>
	using XClassW = XClassBase<true, SubClass>;
protected:
	template<bool IsUnicode, class SubClass = void>
	class XClassExBase : public WindowClassExBaseX<IsUnicode, KChain<XClassExBase<IsUnicode, SubClass>, SubClass>> {
		using LPCTSTR = LPCXSTR<IsUnicode>;
	public:
		using Child = KChain<XClassExBase, SubClass>;
		using super = WindowClassExBaseX<IsUnicode, Child>;
	public:
		XClassExBase() {
			super::WndProc(MainProc);
			super::Name(CClassName<IsUnicode>());
			this->Cursor(IDC_ARROW);
			this->Styles(ClassStyle::Redraw);
			this->Background(SysColor::Window);
		}
	};
	template<class SubClass = void>
	using XClassEx = XClassExBase<IsUnicode, SubClass>;
	template<class SubClass = void>
	using XClassExA = XClassExBase<false, SubClass>;
	template<class SubClass = void>
	using XClassExW = XClassExBase<true, SubClass>;
protected:
	subtype_branch(xClass);
public:
	static inline ATOM Register() {
		if (_ClassAtom) return _ClassAtom;
		using ClassReg = subtype_branchof_xClass<Child, XClassEx<>>;
		static ClassReg _Class;
		return _ClassAtom = _Class.Register();
	}
	static inline void Unregister() {
		if (_ClassAtom)
			assertl(UnregisterClass(MAKEINTRESOURCE(_ClassAtom), _hClassModule));
		_ClassAtom = 0;
	}
#pragma endregion

#pragma region Creature
protected:
	template<bool IsUnicode, class SubCreate = void, class Style = WStyle, class StyleEx = WStyleEx>
	class XCreateBase : public WX::CreateStructBaseX<IsUnicode, KChain<XCreateBase<IsUnicode, SubCreate, Style, StyleEx>, SubCreate>, Style, StyleEx>  {
		using LPCTSTR = LPCXSTR<IsUnicode>;
	public:
		using Child = KChain<XCreateBase, SubCreate>;
		using super = WX::CreateStructBaseX<IsUnicode, Child, Style, StyleEx>;
	public:
		XCreateBase() {
			this->Size(CW_USEDEFAULT);
			this->Position(CW_USEDEFAULT);
			this->Styles(WS::OverlappedWindow);
			this->Caption(CClassName());
			super::Class(_ClassAtom);
		}
	public: // Deleted properties
		/* W */ inline auto &Class(LPCTSTR) = delete;
		/* W */ inline auto &Class(ATOM) = delete;
	public:
		inline void Create() reflect_to(this->_this = super::template Create<AnyChild>());
	public:
		inline operator bool() reflect_as((bool)super::template Create<AnyChild>());
	};
	template<class SubCreate = void, class Style = WStyle, class StyleEx = WStyleEx>
	using XCreate = XCreateBase<IsUnicode, SubCreate, Style, StyleEx>;
	template<class SubCreate = void, class Style = WStyle, class StyleEx = WStyleEx>
	using XCreateA = XCreateBase<false, SubCreate, Style, StyleEx>;
	template<class SubCreate = void, class Style = WStyle, class StyleEx = WStyleEx>
	using XCreateW = XCreateBase<true, SubCreate, Style, StyleEx>;
protected:
	subtype_branch(xCreate);
public:
	inline auto Create() {
		Register();
		using CreateDefault = XCreate<void,
			typename Child::Style,
			typename Child::StyleEx>;
		using CreateReg = subtype_branchof_xCreate<AnyChild, CreateDefault>;
		CreateReg cs;
		cs.Param(this);
		return cs;
	}
	inline void Destroy() assertl_reflect_as(DestroyWindow(self));
	inline void Close() assertl_reflect_as(CloseWindow(self));
#pragma endregion

#pragma region Message System
public:
	template<class RetType = LRESULT, class MsgType = UINT, class WParam = WPARAM, class LParam = LPARAM>
	inline RetType Send(MsgType msgid, WParam wParam = 0, LParam lParam = 0) const
		nt_assertl_reflect_to(auto res = SendMessage(self, (UINT)(msgid), small_cast<WPARAM>(wParam), small_cast<LPARAM>(lParam)), small_cast<RetType>(res));
	//template<class WParam = WPARAM, class LParam = LPARAM>
	//inline auto &SendTimeout(UINT msgid, WParam wParam = 0, LParam lParam = 0) {
	//	SendMessageTimeoutW(self, msgid, wParam, lParam, )
	//}
	template<class MsgType = UINT, class WParam = WPARAM, class LParam = LPARAM>
	inline auto &Post(MsgType msgid, WParam wParam = 0, LParam lParam = 0) const assertl_reflect_as_child(PostMessage(self, reuse_as<UINT>(msgid), reuse_as<WPARAM>(wParam), reuse_as<LPARAM>(lParam)));
public:
	class MessageSwitch {
	protected:
		friend MessageSwitch WindowBase<AnyChild>::Message();
		HWND hwnd;
		MessageSwitch(HWND hwnd) : hwnd(hwnd) {}
	public:
		template<class RetType>
		class Indirect {
		protected:
			friend class MessageSwitch;
			HWND hwnd;
			UINT msgid;
			WPARAM wParam;
			LPARAM lParam;
			Indirect(HWND hwnd, UINT msgid, WPARAM wParam, LPARAM lParam) :
				hwnd(hwnd), msgid(msgid), wParam(wParam), lParam(lParam) {}
		public:
			inline RetType Send() nt_assertl_reflect_to(auto res = SendMessage(hwnd, msgid, wParam, lParam), (RetType)res);
			template<class AnyCallback>
			inline void SendCallback(AnyCallback cb) {
				struct AsyncProc {
					AnyCallback cb;
					AsyncProc(AnyCallback &cb) : cb(cb) {}
					static void lpfnCallback(HWND hwnd, UINT msgid, ULONG_PTR ulpThis, LRESULT res) {
						auto lpThis = (AsyncProc *)ulpThis;
						lpThis->cb();
						delete lpThis;
					}
				};
				assertl(SendMessageCallback(hwnd, msgid, wParam, lParam, AsyncProc::lpfnCallback, (ULONG_PTR)(new AsyncProc(cb))));
			}
			inline void Post() assertl_reflect_as(PostMessage(hwnd, msgid, wParam, lParam));
		};
#define MSG_TRANS(msgid, ret, name, argslist, args, send, call) \
		inline Indirect<ret> name argslist send
#define _SEND_(ret, msgid, wparam, lparam) \
			reflect_as({ hwnd, msgid, wparam, lparam });
#include "wx_msg.inl"
	};
	inline MessageSwitch Message() reflect_as(hWnd);
#pragma endregion

#pragma region Properties
public: // Property - Iconic
	/* R */ inline bool Iconic() const reflect_as(IsIconic(self));
public: // Property - Zoomed
	/* R */ inline bool Zoomed() const reflect_as(IsZoomed(self));
public: // Property - Visible
	/* W */ inline auto &Visible(bool bVisible) reflect_to_child(ShowWindow(self, bVisible ? SW_SHOW : SW_HIDE));
	/* R */ inline bool Visible() const reflect_as(IsWindowVisible(self));
public: // Proterty - Enabled
	/* W */ inline auto &Enabled(bool bEnable) assertl_reflect_as_child(EnableWindow(self, bEnable));
	/* R */ inline bool Enabled() const reflect_as(IsWindowEnabled(self));
public: // Property - ClientRect
	/* R */ inline LRect ClientRect() const assertl_reflect_to(LRect rc, GetClientRect(self, &rc), rc);
public: // Property - ClientSize
	/* R */ inline LSize ClientSize() const assertl_reflect_to(LRect rc, GetClientRect(self, &rc), rc.right_bottom());
public: // Property - Position
	/* W */ inline auto  &Position(LPoint ptPosition) assertl_reflect_as_child(SetWindowPos(self, O, ptPosition.x, ptPosition.y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE));
	/* R */ inline LPoint Position() const assertl_reflect_to(LRect rc, GetWindowRect(self, &rc), rc.left_top());
public: // Property - Size
	/* W */ inline auto &Size(LSize szWin) assertl_reflect_as_child(SetWindowPos(self, O, 0, 0, szWin.cx - 1, szWin.cy - 1, SWP_NOMOVE | SWP_NOACTIVATE));
	/* R */ inline LSize Size() const assertl_reflect_to(LRect rc, GetWindowRect(self, &rc), rc.size());
public: // Property - Rect
	/* W */ inline auto &Rect(LRect rWin) assertl_reflect_to_child(LSize sz = rWin.size(), SetWindowPos(self, O, rWin.top, rWin.left, sz.cx, sz.cy, SWP_NOZORDER | SWP_NOACTIVATE));
	/* R */ inline LRect Rect() const assertl_reflect_to(LRect rWin, GetWindowRect(self, rWin), rWin);
public: // Property - Placement
	/* W */ inline auto &Placement(const WINDOWPLACEMENT &wp) assertl_reflect_as_child(SetWindowPlacement(self, &wp));
	/* R */ inline WindowPlacement Placement() const assertl_reflect_to(WindowPlacement wp, GetWindowPlacement(self, &wp), wp);
public: // Property - Info
	/* R */ inline WindowInfo Info() const assertl_reflect_to(WindowInfo wi, GetWindowInfo(self, &wi), wi);
public: // Property - TextLength
	/* R */ inline int TextLength() const nt_assertl_reflect_to(auto len = GetWindowTextLength(self), len);
	/* R */ inline int TextLengthA() const nt_assertl_reflect_to(auto len = GetWindowTextLengthA(self), len);
	/* R */ inline int TextLengthW() const nt_assertl_reflect_to(auto len = GetWindowTextLengthW(self), len);
public: // Property - String
	/* W */ inline auto &Text(LPCSTR lpString) assertl_reflect_as_child(SetWindowTextA(self, lpString) >= 0);
	/* W */ inline auto &Text(LPCWSTR lpString) assertl_reflect_as_child(SetWindowTextW(self, lpString) >= 0);
	/* R */ inline String Text() const {
		if constexpr (IsUnicode) return TextW();
		else return TextA();
	}
	/* R */ inline StringA TextA() const {
		auto len = TextLengthA();
		if (len <= 0) return O;
		auto lpszName = StringA::Alloc(len);
		assertl(len == GetWindowTextA(self, lpszName, len + 1));
		return{ (size_t)len, lpszName };
	}
	/* R */ inline StringW TextW() const {
		auto len = TextLengthW();
		if (len <= 0) return O;
		auto lpszName = StringW::Alloc(len);
		assertl(len == GetWindowTextW(self, lpszName, len + 1));
		return{ (size_t)len, lpszName };
	}
public: // Property - ModuleFileName
	/* R */ inline String ModuleFileName() const {
		if constexpr (IsUnicode) return ModuleFileNameW();
		else return ModuleFileNameA();
	}
	/* R */ inline StringA ModuleFileNameA() const {
		auto lpszName = StringA::Alloc(MaxLenPath);
		int len = 0;
		assertl((len = GetWindowModuleFileNameA(self, lpszName, MaxLenPath)) > 0);
		lpszName = StringA::Realloc(len, lpszName);
		return { (size_t)len, lpszName };
	}
	/* R */ inline StringW ModuleFileNameW() const {
		auto lpszName = StringW::Alloc(MaxLenPath);
		int len = 0;
		assertl((len = GetWindowModuleFileNameW(self, lpszName, MaxLenPath)) > 0);
		lpszName = StringW::Realloc(len, lpszName);
		return { (size_t)len, lpszName };
	}
public: // Property - Parent
	/* W */ inline auto &Parent(HWND hParent) nt_assertl_reflect_to_child(SetParent(self, hParent));
	template<class AnyClass = void>
	/* R */ inline RefAs<WindowBase<AnyClass>> Parent() const nt_assertl_reflect_to(auto hParent = GetParent(self), reuse_as<RefAs<WindowBase<AnyClass>>>(hParent));
public: // Property - Next
	template<class AnyClass = void>
	/* R */ inline RefAs<WindowBase<AnyClass>> Next() const nt_assertl_reflect_to(auto hWnd = GetNextWindow(self, GW_HWNDNEXT), hWnd);
public: // Property - Prev
	template<class AnyClass = void>
	/* R */ inline RefAs<WindowBase<AnyClass>> Prev() const nt_assertl_reflect_to(auto hWnd = GetNextWindow(self, GW_HWNDPREV), hWnd);
public: // Property - Menu
	/* W */ inline auto &Menu(HMENU hMenu) assertl_reflect_as_child(SetMenu(self, hMenu));
	/* R */ inline CMenu Menu() const reflect_as(GetMenu(self));
public: // Property - SysMenu
	/* R */ inline CMenu SysMenu() const reflect_as(GetSystemMenu(self, false));
public: // Property - Region
	/* W */ inline auto &Region(HRGN hRgn) assertl_reflect_as_child(SetWindowRgn(self, hRgn, true));
///	/* R */ inline void Region() const { GetWindowRgn() }
public: // Property - Icon
	/* W */ inline auto &Icon(HICON hIcon) reflect_to_child(Send<HICON>(WM_SETICON, ICON_BIG, hIcon));
	/* R */ inline CIcon Icon() const reflect_as(Send<HICON>(WM_GETICON, ICON_BIG));
public: // Property - IconSmall
	/* W */ inline auto &IconSmall(HICON hIcon) reflect_to_child(Send<HICON>(WM_SETICON, ICON_SMALL, hIcon));
	/* R */ inline CIcon IconSmall() const reflect_as(Send<HICON>(WM_GETICON, ICON_SMALL));
public: // Property - IconSmall2
	/* W */ inline auto &IconSmall2(HICON hIcon) reflect_to_child(Send<HICON>(WM_SETICON, ICON_SMALL2, hIcon));
	/* R */ inline CIcon IconSmall2() const reflect_as(Send<HICON>(WM_GETICON, ICON_SMALL2));
#pragma region Window Extra
public: // Property - Word
	/* W */ inline auto &Word(int nIndex, WORD wNewWord) nt_assertl_reflect_to_child(SetWindowWord(self, nIndex, wNewWord));
	/* R */ inline WORD Word(int nIndex) const nt_assertl_reflect_to(auto word = GetWindowWord(self, nIndex), word);
public: // Property - Long
	template<class AnyType = LONG_PTR>
	/* W */ inline auto &Long(int nIndex, AnyType dwNewLong) nt_assertl_reflect_to_child(SetWindowLongPtr(self, nIndex, small_cast<LONG_PTR>(dwNewLong)));
	template<class AnyType = LONG_PTR>
	/* R */ inline AnyType Long(int nIndex) const nt_assertl_reflect_to(auto dwLong = GetWindowLongPtr(self, nIndex), big_cast<AnyType>(dwLong));
public: // Property - WndProc
	/* W */ inline auto &WndProc(WNDPROC lpfnWndProc) reflect_as(Long(GWLP_WNDPROC, lpfnWndProc));
	/* R */ inline WX::WndProc WndProc() const reflect_as(Long<WX::WndProc>(GWLP_WNDPROC));
public: // Property - Module
	/* W */ inline auto &Module(HINSTANCE hInstance) reflect_as(Long(GWLP_HINSTANCE, hInstance));
	/* R */ inline CModule Module() const reflect_as(Long<HINSTANCE>(GWLP_HINSTANCE));
public: // Property - HwndParent
	/* W */ inline auto &HwndParent(HWND hHwndParent) reflect_as(Long(GWLP_HWNDPARENT, hHwndParent));
	template<class AnyClass = void>
	/* R */ inline RefAs<WindowBase<AnyClass>> HwndParent() const reflect_as(Long<RefAs<WindowBase<AnyClass>>>(GWLP_HWNDPARENT));
public: // Property - Styles
	/* W */ inline auto &Styles(Style style) reflect_as(Long(GWL_STYLE, style));
	/* R */ inline Style Styles() const reflect_as(Long<Style>(GWL_STYLE));
public: // Property - StylesEx 
	/* W */ inline auto &StylesEx(StyleEx styleEx) reflect_as(Long(GWL_EXSTYLE, styleEx));
	/* R */ inline StyleEx StylesEx() const reflect_as(Long<StyleEx>(GWL_EXSTYLE));
public: // Property - UserData
	template<class AnyType = LONG_PTR>
	/* W */ inline auto &UserData(AnyType data) reflect_as(Long(GWLP_USERDATA, data));
	template<class AnyType = LONG_PTR>
	/* R */ inline AnyType UserData() const reflect_as(Long<AnyType>(GWLP_USERDATA));
public: // Property - ID
	/* W */ inline auto &ID(LONG_PTR uId) reflect_as(Long(GWLP_ID, uId));
	/* R */ inline LONG_PTR ID() const reflect_as(Long(GWLP_ID));
#pragma endregion
public: // Property - ClassName
	/* R */ inline String ClassName() const {
		auto lpszName = String::Alloc(MaxLenClass);
		int len = 0;
		assertl((len = GetClassName(self, lpszName, MaxLenClass)) > 0);
		lpszName = String::Realloc(len, lpszName);
		return { (size_t)len, lpszName };
	}
	/* R */ inline StringA ClassNameA() const {
		auto lpszName = StringA::Alloc(MaxLenClass);
		int len = 0;
		assertl((len = GetClassNameA(self, lpszName, MaxLenClass)) > 0);
		lpszName = StringA::Realloc(len, lpszName);
		return { (size_t)len, lpszName };
	}
	/* R */ inline StringW ClassNameW() const {
		auto lpszName = StringW::Alloc(MaxLenClass);
		int len = 0;
		assertl((len = GetClassNameW(self, lpszName, MaxLenClass)) > 0);
		lpszName = StringW::Realloc(len, lpszName);
		return { (size_t)len, lpszName };
	}
#pragma region Window Class Extra
public: // Property - ClassWord
	/* W */ inline auto &ClassWord(int nIndex, WORD wNewWord) nt_assertl_reflect_to_child(SetClassWord(self, nIndex, wNewWord));
	/* R */ inline WORD ClassWord(int nIndex) const nt_assertl_reflect_to(auto word = GetClassWord(self, nIndex), word);
public: // Property - ClassAtom
	/* W */ inline auto &ClassAtom(ATOM atom) reflect_as(ClassWord(GCW_ATOM, atom));
	/* R */ inline ATOM  ClassAtom() const reflect_as(ClassWord(GCW_ATOM)); 
public: // Property - ClassLong
	template<class AnyType = void *>
	/* W */ inline auto &ClassLong(int nIndex, AnyType dwNewLong) nt_assertl_reflect_to_child(SetClassLongPtr(self, nIndex, small_cast<LONG_PTR>(dwNewLong)));
	template<class AnyType = LONG_PTR>
	/* R */ inline AnyType ClassLong(int nIndex) const nt_assertl_reflect_to(auto dwLong = GetClassLongPtr(self, nIndex), big_cast<AnyType>(dwLong));
public: // Property - ClassMenuName
	/* W */ inline auto   &ClassMenuName(UINT uID) reflect_as(ClassLong(GCLP_MENUNAME, MAKEINTRESOURCE(uID)));
	/* W */ inline auto   &ClassMenuName(LPCSTR lpMenuName) reflect_as(ClassLong(GCLP_MENUNAME, lpMenuName));
	/* W */ inline auto   &ClassMenuName(LPCWSTR lpMenuName) reflect_as(ClassLong(GCLP_MENUNAME, lpMenuName));
	/* R */ inline LPCTSTR ClassMenuName() const reflect_as(ClassLong<LPCTSTR>(GCLP_MENUNAME));
	/* R */ inline LPCSTR  ClassMenuNameA() const reflect_as(ClassLong<LPCSTR>(GCLP_MENUNAME));
	/* R */ inline LPCWSTR ClassMenuNameW() const reflect_as(ClassLong<LPCWSTR>(GCLP_MENUNAME));
public: // Property - ClassStyles
	/* W */ inline auto      &ClassStyles(ClassStyle style) reflect_as(ClassLong(GCL_STYLE, style));
	/* R */ inline ClassStyle ClassStyles() const reflect_as(ClassLong<ClassStyle>(GCL_STYLE));
public: // Property - ClassBackground
	/* W */ inline auto  &ClassBackground(HBRUSH hBrush) reflect_as(ClassLong(GCLP_HBRBACKGROUND, hBrush));
	/* R */ inline CBrush ClassBackground() const reflect_as(ClassLong<HBRUSH>(GCLP_HBRBACKGROUND));
public: // Property - ClassCursor
	/* W */ inline auto   &ClassCursor(HCURSOR hCursor) reflect_as(ClassLong(GCLP_HCURSOR, (LONG_PTR)hCursor));
	/* R */ inline CCursor ClassCursor() const reflect_as(reuse_as<HCURSOR>(GetClassLongPtr(self, GCLP_HCURSOR)));
public: // Property - ClassIcon
	/* W */ inline auto &ClassIcon(HICON hIcon) reflect_as(ClassLong(GCLP_HICON, hIcon));
	/* R */ inline CIcon ClassIcon() const reflect_as(reuse_as<HICON>(GetClassLongPtr(self, GCLP_HICON)));
public: // Property - ClassModule
	/* W */ inline auto   &ClassModule(HINSTANCE hModule) reflect_as(ClassLong(GCLP_HMODULE, hModule));
	/* R */ inline CModule ClassModule() const reflect_as(reuse_as<HINSTANCE>(GetClassLongPtr(self, GCLP_HMODULE)));
public: // Property - ClassWndExtra
	/* W */ inline auto     &ClassWndExtra(ULONG_PTR hModule) reflect_as(ClassLong(GCL_CBWNDEXTRA, hModule));
	/* R */ inline ULONG_PTR ClassWndExtra() const reflect_as(GetClassLongPtr(self, GCL_CBWNDEXTRA));
public: // Property - ClassClsExtra
	/* W */ inline auto     &ClassClsExtra(ULONG_PTR hModule) reflect_as(ClassLong(GCL_CBCLSEXTRA, hModule));
	/* R */ inline ULONG_PTR ClassClsExtra() const reflect_as(GetClassLongPtr(self, GCL_CBCLSEXTRA));
public: // Property - ClassWndProc
	/* W */ inline auto   &ClassWndProc(WNDPROC WndProc) reflect_as(ClassLong(GCLP_WNDPROC, WndProc));
	/* R */ inline WX::WndProc ClassWndProc() const reflect_as(ClassLong<WNDPROC>(GCLP_WNDPROC));
public: // Property - ClassIconSmall
	/* W */ inline auto &ClassIconSmall(HICON hIcon) reflect_as(ClassLong(GCLP_HICONSM, hIcon));
	/* R */ inline CIcon ClassIconSmall() const reflect_as(ClassLong<HICON>(GCLP_HICONSM));
public: // Property - Class
	/* R */ inline auto Class() const reflect_as(WindowClass().Module(ClassModule()).Atom(ClassAtom()).GetInfo());
	/* R */ inline auto ClassA() const reflect_as(WindowClassA().Module(ClassModule()).Atom(ClassAtom()).GetInfo());
	/* R */ inline auto ClassW() const reflect_as(WindowClassW().Module(ClassModule()).Atom(ClassAtom()).GetInfo());
public: // Property - ClassEx
	/* R */ inline auto ClassEx() const reflect_as(WindowClassEx().Module(ClassModule()).Atom(ClassAtom()).GetInfo());
	/* R */ inline auto ClassExA() const reflect_as(WindowClassExA().Module(ClassModule()).Atom(ClassAtom()).GetInfo());
	/* R */ inline auto ClassExW() const reflect_as(WindowClassExW().Module(ClassModule()).Atom(ClassAtom()).GetInfo());
#pragma endregion
public: // Property - DC
	/* R */ inline CDC DC() const reflect_as(GetDC(self));
public: // Property - ProcessId
	/* R */ inline DWORD ProcessId() const reflect_to(DWORD dwProcessId = 0, GetWindowThreadProcessId(self, &dwProcessId), dwProcessId);
public: // Property - ThreadId
	/* R */ inline DWORD ThreadId() const reflect_as(GetWindowThreadProcessId(self, O));
public: // Property - Prop
	/* W */ inline auto &Prop(ATOM globalAtom, HANDLE hData) assertl_reflect_as_child(SetProp(self, MAKEINTATOM(globalAtom), hData));
	/* W */ inline auto &Prop(LPCSTR lpString, HANDLE hData) assertl_reflect_as_child(SetPropA(self, lpString, hData));
	/* W */ inline auto &Prop(LPCWSTR lpString, HANDLE hData) assertl_reflect_as_child(SetPropW(self, lpString, hData));
	/* R */ inline HANDLE Prop(ATOM globalAtom) const nt_assertl_reflect_to(auto hData = GetProp(self, MAKEINTATOM(globalAtom)), hData);
	/* R */ inline HANDLE Prop(LPCSTR lpString) const assertl_reflect_to(auto hData = GetPropA(self, lpString), hData);
	/* R */ inline HANDLE Prop(LPCWSTR lpString) const assertl_reflect_to(auto hData = GetPropW(self, lpString), hData);
#pragma endregion
public:
	inline operator bool() const reflect_as(IsWindow(hWnd));
	inline operator HWND() const reflect_as(hWnd);
public:
	inline AnyChild *operator&() reflect_as(UserData<AnyChild *>());
	inline AnyChild *operator->() reflect_as(UserData<AnyChild *>());
	inline const AnyChild *operator&() const reflect_as(UserData<const AnyChild *>());
	inline const AnyChild *operator->() const reflect_as(UserData<const AnyChild *>());
public:
	inline auto &operator=(WindowBase &w) reflect_to_child(std::swap(this->hWnd, w.hWnd));
	inline auto &operator=(const WindowBase &w) const reflect_to_child(std::swap(this->hWnd, w.hWnd));
public:
	static inline Window &Attach(HWND &hWnd) reflect_as(ref_as<Window>(hWnd));
};
template<class AnyChild, class SubXCreate, class Style, class StyleEx>
using WXCreate = typename WindowBase<AnyChild>::template XCreate<SubXCreate, Style, StyleEx>;
template<class AnyChild> ATOM WindowBase<AnyChild>::_ClassAtom = 0;
template<class AnyChild> HINSTANCE WindowBase<AnyChild>::_hClassModule = O;
#define SFINAE_Window(name) friend class WX::WindowBase<name>
#define BaseOf_Window(name) name : public WX::WindowBase<name>
#define WxCreate() struct xCreate : XCreate<xCreate>
#define WxCreateA() struct xCreate : XCreateA<xCreate>
#define WxCreateW() struct xCreate : XCreateW<xCreate>
#define WxClass() struct xClass : XClass<xClass>
#define WxClassEx() struct xClass : XClassEx<xClass>
#define WxClassExA() struct xClass : XClassExA<xClass>
#define WxClassExW() struct xClass : XClassExW<xClass>
#pragma endregion

}
