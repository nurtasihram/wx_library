#pragma once

#include <unordered_map>
#include <typeinfo>

#include "./resource.h"

namespace WX {

struct KEY_FLAGS {
	uint16_t wScanCode : 8;
	uint16_t bExtend : 1;
	uint16_t ___reserved : 4;
	uint16_t bContext : 1;
	uint16_t bPrevious : 1;
	uint16_t bTranslated : 1;
};

#pragma region WindowBase

template<class AnyChild>
class WindowBase;
using Window = WindowBase<void>;
using CWindow = RefAs<Window>;
template<class AnyChild>
using WindowShim = RefAs<WindowBase<AnyChild>>;

#pragma region Misc
enum_flags(TrackMouseFlag, DWORD,
	Hover    = TME_HOVER,
	Leave    = TME_LEAVE,
	NoClient = TME_NONCLIENT,
	Query    = TME_QUERY,
	Cancel   = TME_CANCEL);
struct TrackMouseEventBox : public RefStruct<TRACKMOUSEEVENT> {
public:
	using Flag = TrackMouseFlag;
public:
	TrackMouseEventBox(HWND hWnd) {
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
	inline operator bool() reflect_as(TrackMouseEvent(self));
};
using TME = TrackMouseEventBox;

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
	enum_alias DrawFrame       = SWP_DRAWFRAME,
	enum_alias NoReposition    = SWP_NOREPOSITION);
using SWP = WindowPosFlag;
struct WindowPos : public RefStruct<WINDOWPOS> {
public:
	using Flag = WindowPosFlag;
public:
	WindowPos() {}
	WindowPos(const WINDOWPOS &w) : RefStruct<WINDOWPOS>(w) {}
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
	/* W */ inline auto &Rect(LRect r) reflect_to_self(Size(r), Position(r));
	/* R */ inline LRect Rect() const reflect_as({ Position(), Size() });
public: // Property - Flags
	/* W */ inline auto &Flags(Flag flags) reflect_to_self(self->flags = flags.yield());
	/* R */ inline Flag Flags() const reflect_as(reuse_as<Flag>(self->flags));
public:
} ;

struct PaintStruct : public RefStruct<PAINTSTRUCT> {
public:
	PaintStruct() {}
	PaintStruct(const PAINTSTRUCT &ps) : RefStruct<PAINTSTRUCT>(ps) {}
public: // Property - DC
	/* R */ inline CDC DC() reflect_as(self->hdc);
public: // Property - Erase
	/* W */ inline auto&Erase(bool fErase) reflect_to_self(self->fErase = fErase);
	/* R */ inline bool Erase() const reflect_as(self->fErase);
public: // Property - Rect
	/* W */ inline auto &Rect(LRect rcPaint) reflect_to_self(self->rcPaint = rcPaint);
	/* R */ inline LRect Rect() const reflect_as(self->rcPaint);
};

class WindowProcedure {
	WNDPROC pfnWndProc = O;
	HWND hWnd = O;
public:
	WindowProcedure() {}
	WindowProcedure(HWND hWnd, WNDPROC pfnWndProc = O) : pfnWndProc(pfnWndProc), hWnd(hWnd) {}
	WindowProcedure(WNDPROC pfnWndProc, HWND hWnd = O) : pfnWndProc(pfnWndProc), hWnd(hWnd) {}

	inline LRESULT Call(UINT Msg, WPARAM wParam, LPARAM lParam) const reflect_as(CallWindowProc(pfnWndProc, hWnd, Msg, wParam, lParam));
	inline LRESULT Call(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) const reflect_as(CallWindowProc(pfnWndProc, hWnd, Msg, wParam, lParam));
	
	inline auto &operator*=(HWND hWnd) reflect_to_self(this->hWnd = hWnd);
	inline LRESULT operator()(UINT Msg, WPARAM wParam, LPARAM lParam) const reflect_as(Call(Msg, wParam, lParam));
	inline LRESULT operator()(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) const reflect_as(Call(hWnd, Msg, wParam, lParam));
	inline bool operator<=(HWND hWnd) {
		if (auto lpfnWndProc = GetWindowLongPtr(hWnd, GWLP_WNDPROC)) {
			this->hWnd = hWnd;
			this->pfnWndProc = reuse_as<WNDPROC>(lpfnWndProc);
			return true;
		}
		return false;
	}

public:
#define _SEND_(ret, msgid, wparam, lparam) \
	ret(Call(msgid, wparam, lparam))
#define MSG_TRANS(msgid, ret, name, argslist, args, send, call) \
	inline ret name argslist reflect_as(send);
#include "msg.inl"

public:
	inline operator bool() const reflect_as(pfnWndProc);
	inline operator WNDPROC() const reflect_as(pfnWndProc);
	inline operator HWND() const reflect_as(hWnd);
};
using WndProc = WindowProcedure;

class Message : public RefStruct<MSG> {
public:
	Message() {}
public: // Property - Window
	/* W */ inline auto &Window(HWND hwnd) reflect_as(self->hwnd);
	template<class Child = void>
	/* S */ inline WindowBase<Child> &Window() reflect_as(WindowBase<Child>::Attach(self->hwnd));
	template<class Child = void>
	/* R */ inline WindowBase<Child> Window() const reflect_as(reuse_as<WX::WindowBase<Child>>(self->hwnd));
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
	inline bool Get(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_to(auto res = GetMessage(self, O, wMsgFilterMin, wMsgFilterMax), res);
	inline bool Get(HWND hwnd, UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_to(auto res = GetMessage(self, hwnd, wMsgFilterMin, wMsgFilterMax), res);
	inline bool GetThread(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_to(auto res = GetMessage(self, (HWND)-1, wMsgFilterMin, wMsgFilterMax), res);

	inline bool GetSafe(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) nt_assertl_reflect_to(auto res = GetMessage(self, O, wMsgFilterMin, wMsgFilterMax), res);
	inline bool GetSafe(HWND hwnd, UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) nt_assertl_reflect_to(auto res = GetMessage(self, hwnd, wMsgFilterMin, wMsgFilterMax), res);
	inline bool GetThreadSafe(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) nt_assertl_reflect_to(auto res = GetMessage(self, (HWND)-1, wMsgFilterMin, wMsgFilterMax), res);

	inline bool Translate() const reflect_as(TranslateMessage(self));
	template<class RetType = LRESULT>
	inline RetType Dispatch() const reflect_as((RetType)DispatchMessage(self));

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
	inline Peeks Peek(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_as({ self, O, wMsgFilterMin, wMsgFilterMax });
	inline Peeks Peek(HWND hwnd, UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_as({ self, hwnd, wMsgFilterMin, wMsgFilterMax });
	inline Peeks PeekThread(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_as({ self, (HWND)-1, wMsgFilterMin, wMsgFilterMax });
};
using Msg = Message;

enum_class(ShowWindowFlags, int,
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
using SW = ShowWindowFlags;
#pragma endregion

#pragma region Class
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
template<class = void>
class ClassBase;
using Class = ClassBase<>;
template<class AnyChild>
class ClassBase : public RefStruct<WNDCLASS>,
	public ChainExtend<ClassBase<AnyChild>, AnyChild> {
public:
	using Child = KChain<ClassBase, AnyChild>;
	using Style = CStyle;
public:
	ClassBase() reflect_to(self->cbClsExtra = sizeof(Child) - sizeof(WNDCLASS));
public: // Property - Styles
	/* W */ inline auto  &Styles(Style style) reflect_to_child(self->style = style.yield());
	/* S */ inline Style &Styles() reflect_as(ref_as<Style>(self->style));
	/* R */ inline Style  Styles() const reflect_as(ref_as<Style>(self->style));
public: // Property - WndProc
	/* W */ inline auto       &WndProc(WNDPROC lpfnWndProc) reflect_to_child(self->lpfnWndProc = lpfnWndProc);
	/* R */ inline WX::WndProc WndProc() const reflect_as(self->lpfnWndProc);
public: // Property - WndExtra
	/* W */ inline auto &WndExtra(int cbWndExtra) reflect_to_child(self->cbWndExtra = cbWndExtra);
	/* S */ inline int  &WndExtra() reflect_as(self->cbWndExtra);
	/* R */ inline int   WndExtra() const reflect_as(self->cbWndExtra);
public: // Property - Module
	/* W */ inline auto       &Module(HINSTANCE hModule) reflect_to_child(self->hInstance = hModule);
	/* S */ inline WX::Module &Module() reflect_as(WX::Module::Attach(self->hInstance));
	/* R */ inline CModule     Module() const reflect_as(self->hInstance);
public: // Property - Icon
	/* W */ inline auto     &Icon(LPCTSTR lpszName) reflect_to_child(self->hIcon = Module().Icon(lpszName));
	/* W */ inline auto     &Icon(CIcon icon) reflect_to_child(self->hIcon = icon);
	/* W */ inline auto     &Icon(WORD wID) reflect_to_child(self->hIcon = Module().Icon(wID));
	/* S */ inline WX::Icon &Icon() reflect_as(WX::Icon::Attach(self->hIcon));
	/* R */ inline CIcon     Icon() const reflect_as(self->hIcon);
public: // Property - Cursor
	/* W */ inline auto       &Cursor(LPCTSTR lpszName) reflect_to_child(self->hCursor = Module().Cursor(lpszName));
	/* W */ inline auto       &Cursor(HCURSOR hCursor) reflect_to_child(self->hCursor = hCursor);
	/* W */ inline auto       &Cursor(WORD wID) reflect_to_child(self->hCursor = Module().Cursor(wID));
	/* S */ inline WX::Cursor &Cursor() reflect_as(WX::Cursor::Attach(self->hCursor));
	/* R */ inline CCursor     Cursor() const reflect_as(self->hCursor);
public: // Property - Background
	/* W */ inline auto  &Background(HBRUSH hbrBackground) reflect_to_child(self->hbrBackground = hbrBackground);
	/* W */ inline auto  &Background(SysColor sc) reflect_to_child(self->hbrBackground = reuse_as<HBRUSH>(sc.yield()));
	/* S */ inline Brush &Background() reflect_as(Brush::Attach(self->hbrBackground));
	/* R */ inline CBrush Background() const reflect_as(self->hbrBackground);
public: // Property - Menu
	/* W */ inline auto    &Menu(LPCTSTR lpszMenuName) reflect_to_child(self->lpszMenuName = lpszMenuName);
	/* W */ inline auto    &Menu(WORD wID) reflect_to_child(self->lpszMenuName = MAKEINTRESOURCE(wID));
	/* S */ inline LPCTSTR &MenuName() reflect_as(self->lpszMenuName);
	/* R */ inline LPCTSTR  MenuName() const reflect_as(self->lpszMenuName);
	/* R */ inline CMenu    Menu() const reflect_as(Module().Menu(self->lpszMenuName));
public: // Property - Name
	/* W */ inline auto        &Name(LPCTSTR lpszClassName) reflect_to_child(self->lpszClassName = lpszClassName);
	/* S */ inline LPCTSTR     &Name() reflect_as(self->lpszClassName);
	/* R */ inline const String Name() const reflect_as(CString(self->lpszClassName, MaxLenClass));
public:
	inline ATOM Register() const assertl_reflect_as(auto atom = RegisterClass(self), atom);
	inline void Unregister() const assertl_reflect_as(UnregisterClass(self->lpszClassName, self->hInstance));
	inline void Unregister(ATOM classAtom) const reflect_as(UnregisterClass(MAKEINTRESOURCE(classAtom), self->hInstance));
	inline auto&GetInfo() assertl_reflect_as_self(GetClassInfo(self->hInstance, self->lpszClassName, self));
	inline auto&GetInfo(ATOM classAtom) assertl_reflect_as_self(GetClassInfo(self->hInstance, MAKEINTRESOURCE(classAtom), self));
};
#pragma region ClassEx
template<class = void>
class ClassExBase;
using ClassEx = ClassExBase<>;
template<class AnyChild>
class ClassExBase :
	public RefStruct<WNDCLASSEX>,
	public ChainExtend<ClassExBase<AnyChild>, AnyChild> {
public:
	using Child = KChain<ClassExBase, AnyChild>;
public:
	ClassExBase() {
		self->cbSize = sizeof(WNDCLASSEX);
		self->cbClsExtra = sizeof(Child) - sizeof(WNDCLASSEX);
	}
public: // Property - Styles
	/* W */ inline auto   &Styles(CStyle style) reflect_to_child(self->style = style.yield());
	/* S */ inline CStyle &Styles() reflect_as(ref_as<CStyle>(self->style));
	/* R */ inline CStyle  Styles() const reflect_as(ref_as<CStyle>(self->style));
public: // Property - WndProc
	/* W */ inline auto       &WndProc(WNDPROC lpfnWndProc) reflect_to_child(self->lpfnWndProc = lpfnWndProc);
	/* R */ inline WX::WndProc WndProc() const reflect_as(self->lpfnWndProc);
public: // Property - WndExtra
	/* W */ inline auto &WndExtra(int cbWndExtra) reflect_to_child(self->cbWndExtra = cbWndExtra);
	/* S */ inline int  &WndExtra() reflect_as(self->cbWndExtra);
	/* R */ inline int   WndExtra() const reflect_as(self->cbWndExtra);
public: // Property - Module
	/* W */ inline auto       &Module(HINSTANCE hModule) reflect_to_child(self->hInstance = hModule);
	/* S */ inline WX::Module &Module() reflect_as(WX::Module::Attach(self->hInstance));
	/* R */ inline CModule     Module() const reflect_as(self->hInstance);
public: // Property - Icon
	/* W */ inline auto     &Icon(LPCTSTR lpszName) reflect_to_child(self->hIcon = Module().Icon(lpszName));
	/* W */ inline auto     &Icon(CIcon icon) reflect_to_child(self->hIcon = icon);
	/* W */ inline auto     &Icon(WORD wID) reflect_to_child(self->hIcon = Module().Icon(wID));
	/* S */ inline WX::Icon &Icon() reflect_as(WX::Icon::Attach(self->hIcon));
	/* R */ inline CIcon     Icon() const reflect_as(self->hIcon);
public: // Property - Cursor
	/* W */ inline auto       &Cursor(LPCTSTR lpszName) reflect_to_child(self->hCursor = Module().Cursor(lpszName));
	/* W */ inline auto       &Cursor(HCURSOR hCursor) reflect_to_child(self->hCursor = hCursor);
	/* W */ inline auto       &Cursor(WORD wID) reflect_to_child(self->hCursor = Module().Cursor(wID));
	/* S */ inline WX::Cursor &Cursor() reflect_as(WX::Cursor::Attach(self->hCursor));
	/* R */ inline CCursor     Cursor() const reflect_as(self->hCursor);
public: // Property - Background
	/* W */ inline auto  &Background(HBRUSH hbrBackground) reflect_to_child(self->hbrBackground = hbrBackground);
	/* W */ inline auto  &Background(SysColor sc) reflect_to_child(self->hbrBackground = reuse_as<HBRUSH>((uintptr_t)sc.yield()));
	/* S */ inline Brush &Background() reflect_as(Brush::Attach(self->hbrBackground));
	/* R */ inline CBrush Background() const reflect_as(self->hbrBackground);
public: // Property - Menu
	/* W */ inline auto    &Menu(LPCTSTR lpszMenuName) reflect_to_child(self->lpszMenuName = lpszMenuName);
	/* W */ inline auto    &Menu(WORD wID) reflect_to_child(self->lpszMenuName = MAKEINTRESOURCE(wID));
	/* S */ inline LPCTSTR &MenuName() reflect_as(self->lpszMenuName);
	/* R */ inline LPCTSTR  MenuName() const reflect_as(self->lpszMenuName);
	/* R */ inline CMenu    Menu() const reflect_as(Module().Menu(self->lpszMenuName));
public: // Property - Name
	/* W */ inline auto        &Name(LPCTSTR lpszClassName) reflect_to_child(self->lpszClassName = lpszClassName);
	/* S */ inline LPCTSTR     &Name() reflect_as(self->lpszClassName);
	/* R */ inline const String Name() const reflect_as(CString(self->lpszClassName, MaxLenClass));
public: // Property - IconSm
	/* W */ inline auto     &IconSm(LPCTSTR lpszName) reflect_to_child(self->hIcon = Module().Icon(lpszName));
	/* W */ inline auto     &IconSm(CIcon iconSm) reflect_to_child(self->hIconSm = iconSm);
	/* W */ inline auto     &IconSm(WORD wID) reflect_to_child(self->hIconSm = Module().Icon(wID));
	/* S */ inline WX::Icon &IconSm() reflect_as(WX::Icon::Attach(self->hIconSm));
	/* R */ inline CIcon     IconSm() const reflect_as(self->hIconSm);
public:
	inline ATOM Register() const reflect_as(RegisterClassEx(self));
	inline void Unregister() const assertl_reflect_as(UnregisterClass(lpszClassName, hInstance));
	inline void Unregister(ATOM classAtom) const assertl_reflect_as(UnregisterClass(MAKEINTRESOURCE(classAtom), hInstance));
	inline bool GetInfo() reflect_as(GetClassInfoEx(hInstance, lpszClassName, self));
	inline bool GetInfo(ATOM classAtom) reflect_as(GetClassInfoEx(hInstance, MAKEINTRESOURCE(classAtom), self));
public:
	inline WNDCLASSEX        operator&()         reflect_as(self);
	inline const WNDCLASSEX *operator&()   const reflect_as(self);
};
#pragma endregion
#pragma endregion

#pragma region Styles
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

template<class AnyChild = void, class Style = WStyle, class StyleEx = WStyleEx>
class CreateStructBase : public RefStruct<CREATESTRUCT>,
	public ChainExtend<CreateStructBase<AnyChild, Style, StyleEx>, AnyChild> {
public:
	CreateStructBase() {}
	CreateStructBase(const CREATESTRUCT &cs) : RefStruct<CREATESTRUCT>(cs) {}
public: // Property - Param
	/* W */ inline auto &Param(LPVOID lpCreateParams) reflect_to_child(self->lpCreateParams = lpCreateParams);
	template<class AnyType = void>
	/* R */ inline AnyType *Param() reflect_as((AnyType *)self->lpCreateParams);
public: // Property - Module
	/* W */ inline auto       &Module(HINSTANCE hInstance) reflect_to_child(self->hInstance = hInstance);
	/* S */ inline WX::Module &Module() reflect_as(Module::Attach(self->hInstance));
	/* R */ inline CModule     Module() const reflect_as(self->hInstance);
public: // Property - Menu
	/* W */ inline auto     &Menu(HMENU hMenu) reflect_to_child(self->hMenu = hMenu);
	/* S */ inline WX::Menu &Menu() reflect_as(Menu::Attach(self->hMenu));
	/* R */ inline CMenu     Menu() const reflect_as(self->hMenu);
public: // Property - Parent
	/* W */ inline auto &Parent(HWND hwndParent) reflect_to_child(self->hwndParent = hwndParent);
	template<class _AnyChild = void>
	/* S */ inline WindowBase<_AnyChild> &Parent() reflect_as(WindowBase<_AnyChild>::Attach(self->hwndParent));
	template<class _AnyChild = void>
	/* R */ inline WindowBase<_AnyChild> Parent() const reflect_as(self->hwndParent);
public: // Property - Styles
	/* W */ inline auto  &Styles(Style style) reflect_to_child(self->style = style.yield());
	/* S */ inline Style &Styles() reflect_as(ref_as<Style>(self->style));
	/* R */ inline Style  Styles() const reflect_as(ref_as<Style>(self->style));
public: // Property - Caption
	/* W */ inline auto        &Caption(LPCTSTR name) reflect_to_child(self->lpszName = name);
	/* S */ inline LPCTSTR     &Caption() reflect_as(self->lpszName);
	/* R */ inline const String Caption() const reflect_as(CString(self->lpszName, MaxLenTitle));
public: // Property - Class
	/* W */ inline auto        &Class(LPCTSTR name) reflect_to_child(self->lpszClass = name);
	/* W */ inline auto        &Class(ATOM wClassAtom) reflect_to_child(self->lpszClass = MAKEINTATOM(wClassAtom));
	/* S */ inline LPCTSTR     &Class() reflect_as(self->lpszClass);
	/* R */ inline const String Class() const reflect_as(CString(self->lpszClass, MaxLenClass));
public: // Property - StylesEx
	/* W */ inline auto    &StylesEx(StyleEx dwExStyle) reflect_to_child(self->dwExStyle = dwExStyle.yield());
	/* S */ inline StyleEx &StylesEx() reflect_as(ref_as<StyleEx>(self->dwExStyle));
	/* R */ inline StyleEx  StylesEx() const reflect_as(ref_as<StyleEx>(self->dwExStyle));
public: // Property - Size
	/* W */ inline auto &Size(LSize size) reflect_to_child(self->cx = size.cx, self->cy = size.cy);
	/* R */ inline LSize Size() const reflect_as({ self->cx, self->cy });
public: // Property - Position
	/* W */ inline auto  &Position(LPoint pos) reflect_to_child(self->x = pos.x, self->y = pos.y);
	/* R */ inline LPoint Position() const reflect_as({ self->x, self->y });
public: // Property - Rect
	/* W */ inline auto &Rect(LRect rc) reflect_to_child(auto &&sz = rc.size(); auto &&pt = rc.left_bottom(); self->x = pt.x, self->y = pt.y, self->cx = sz.cx, self->cy = sz.cy);
	/* R */ inline LRect Rect() const reflect_as({ Position(), Size() });
public: // Property - ClientRect
	/* W */ inline auto &ClientRect(LRect rc) assertl_reflect_as(AdjustWindowRectEx(rc, self->style, self->hMenu, self->dwExStyle), self->Rect(rc));
	/* W */ inline auto &ClientRect(LRect rc, UINT dpi) assertl_reflect_as(AdjustWindowRectExForDpi(rc, self->style, self->hMenu, self->dwExStyle, dpi), self->Rect(rc));
public: // Property - ClientSize
	/* W */ inline auto &ClientSize(LSize sz) reflect_as(ClientRect({ Position(), sz }));
	/* W */ inline auto &ClientSize(LSize sz, UINT dpi) reflect_as(ClientRect({ Position(), sz }, dpi));
public:
	template <class _AnyChild = void>
	inline WindowShim<_AnyChild> Create() const assertl_reflect_as(auto h = CreateWindowEx(
		self->dwExStyle, self->lpszClass, self->lpszName, self->style,
		self->x, self->y, self->cx, self->cy,
		self->hwndParent, self->hMenu, self->hInstance,
		self->lpCreateParams), h);
	template <class _AnyChild = void>
	inline WindowShim<_AnyChild> CreateMDI() const assertl_reflect_as(auto h = CreateMDIWindow(
		self->dwExStyle, self->lpszClass, self->lpszName, self->style,
		self->x, self->y, self->cx, self->cy,
		self->hwndParent, self->hMenu, self->hInstance,
		self->lpCreateParams), h);
};
using CreateStruct = CreateStructBase<>;

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
	friend union RefAs<WindowBase>;
	template<class _AnyChild, class Style, class StyleEx>
	friend class CreateStructBase;
	WindowBase(const WindowBase &w) : hWnd(w.hWnd) reflect_to(w.hWnd = O);
	WindowBase(HWND hWnd) : hWnd(hWnd) {}
public:
	WindowBase() {}
	WindowBase(Null) {}
	WindowBase(WindowBase &w) : hWnd(w.hWnd) reflect_to(w.hWnd = O);
	WindowBase(WindowBase &&w) : hWnd(w.hWnd) reflect_to(w.hWnd = O);
	~WindowBase() reflect_to(Delete());

	inline void Delete() {
		if (self)
			this->Message().OnDestroy().Send();
	}

#pragma region Classes
protected:
	static ATOM _ClassAtom;
	static HINSTANCE _hClassModule;
	static const String &&_ClassName;
protected:
	template<class = void>
	class ClassBase;
	using  Class = ClassBase<>;
	template<class _AnyChild>
	class ClassBase : public ChainExtend<ClassBase<_AnyChild>, _AnyChild>,
		public WX::ClassBase<KChain<ClassBase<_AnyChild>, _AnyChild>> {
	public:
		using Child = KChain<ClassBase<_AnyChild>, _AnyChild>;
		using super = WX::ClassBase<Child>;
	public:
		ClassBase() {
			super::WndProc(MainProc<0>);
			super::WndExtra(sizeof(Child));
			super::Name(_ClassName);
		}
	public: // Property - WndExtra (deleted)
		/* W */ inline auto &WndExtra(int) = delete;
	public: // Property - Name (deleted)
		/* W */ inline auto &Name(LPCTSTR) = delete;
	public: // Property - WndProc (deleted)
		/* W */ inline auto &WndProc(WNDPROC) = delete;
	};
protected:
	template<class = void>
	class ClassExBase;
	using ClassEx = ClassExBase<>;
	template<class _AnyChild>
	class ClassExBase : public ChainExtend<ClassExBase<_AnyChild>, _AnyChild>,
		public WX::ClassExBase<KChain<ClassExBase<_AnyChild>, _AnyChild>> {
	public:
		using Child = KChain<ClassExBase, _AnyChild>;
		using super = WX::ClassExBase<Child>;
	public:
		ClassExBase() {
			super::WndProc(MainProc<0>);
			super::WndExtra(sizeof(Child));
			super::Name(_ClassName);
		}
	public: // Property - WndExtra (deleted)
		/* W */ inline auto &WndExtra(int) = delete;
	public: // Property - Name (deleted)
		/* W */ inline auto &Name(LPCTSTR) = delete;
	public: // Property - WndProc (deleted)
		/* W */ inline auto &WndProc(WNDPROC) = delete;
	};
	subtype_branch(xClass);
public:
	inline ATOM Register() {
		if (_ClassAtom) return _ClassAtom;
		subtype_branchof_xClass<Child, ClassEx> cs;
		if constexpr (std::is_same_v<decltype(cs), ClassEx>)
			cs
			.Cursor(IDC_ARROW)
			.Styles(Class::Style::Redraw)
			.Background(SysColor::WindowFrame);
		return _ClassAtom = cs.Register();
	}
	inline void Unregister() {
		if (_ClassAtom)
			assertl(UnregisterClass(MAKEINTRESOURCE(_ClassAtom), _hClassModule));
		_ClassAtom = 0;
	}
#pragma endregion

#pragma region Creature
protected:
	subtype_branch(xCreate);
public:
	using CreateStruct = WX::CreateStructBase<void, Style, StyleEx>;
	template<class _AnyChild = void, class Style = WStyle, class StyleEx = WStyleEx>
	class XCreate : public WX::CreateStructBase<KChain<XCreate<_AnyChild, Style, StyleEx>, _AnyChild>, Style, StyleEx> {
		WindowBase &_this;
	public:
		using Child = KChain<XCreate, _AnyChild>;
		using super = WX::CreateStructBase<Child, Style, StyleEx>;
	public:
		XCreate(WindowBase &_this) : _this(_this) {
			super::Class(_ClassAtom);
			super::Param(&_this);
		}
	public: // Property - Param (deleted)
		/* W */ inline auto &Param(LPVOID) = delete;
		template<class AnyType>
		/* R */ inline AnyType *Param() = delete;
	public: // Property - Class (deleted)
		/* W */ inline auto &Class(String) = delete;
		/* W */ inline auto &Class(ATOM) = delete;
		/* R */ inline const String Class() const = delete;
	public:
		inline void Create() reflect_to(this->_this = super::template Create<AnyChild>());
	public:
		inline operator bool() reflect_as(this->_this ? false : (bool)super::template Create<AnyChild>());
	};
	inline auto Create() {
		Register();
		if constexpr (std::is_void_v<subtype_branchof_xCreate<Child, void>>)
			return XCreate<>(self)
				.Size(CW_USEDEFAULT)
				.Position(CW_USEDEFAULT)
				.Styles(WS::OverlappedWindow)
				.Caption(_ClassName);
		else
			return typename Child::xCreate(self);
	}
	inline void Destroy() {
		if (self) {
			assertl(DestroyWindow(self));
			hWnd = O;
		}
	}
	inline void Close() assertl_reflect_as(CloseWindow(self));
#pragma endregion

#pragma region Messages Procedure
protected:
	def_memberof(DefProc);
	def_memberof(Callback);
#define MSG_TRANS(msgid, ret, name, ...) \
	def_memberof(name);
#include "msg.inl"
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
	template<int index = 0>
	static LRESULT CALLBACK MainProc(HWND hWnd, UINT msgid, WPARAM wParam, LPARAM lParam) {
		auto &Wnd = WindowBase::Attach(hWnd);
		auto pThis = (Child *)Wnd.HeapPtr(index);
	retry:
		try {
			switch (msgid) {
				case WM_CREATE: {
					auto lpCreate = (LPCREATESTRUCT)lParam;
					if ((pThis = (Child *)lpCreate->lpCreateParams))
						if (Wnd.HeapPtr(pThis, index)) {
							(HWND &)*reuse_as<Window *>(pThis) = hWnd;
							break;
						}
					return -1;
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
#include "msg.inl"
				}
			if constexpr (member_Callback_of<Child>::callable)
				return pThis->Callback(msgid, wParam, lParam);
		} catch (MSG msg) {
			if (msg.message)
				return CallDefProc(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		} catch (Exception err) {
			if (pThis->Catch(err))
				goto retry;
			return pThis->Final();
		}
		return CallDefProc(hWnd, msgid, wParam, lParam);
	}
protected:
	inline void OnDestroy() reflect_to(PostQuitMessage(0));
protected:
	def_memberof(OnCatch);
	inline wx_answer Catch(const Exception &err) const {
		if constexpr (member_OnCatch_of<AnyChild>::template compatible_to<wx_answer(Exception)>)
			reflect_as(child.OnCatch(err))
		else if constexpr (member_OnCatch_of<AnyChild>::template compatible_to<wx_answer()>)
			reflect_as(child.OnCatch())
		else if constexpr (member_OnCatch_of<AnyChild>::template compatible_to<void(Exception)>)
			reflect_to(child.OnCatch(err), false)
		else if constexpr (member_OnCatch_of<AnyChild>::template compatible_to<void()>)
			reflect_to(child.OnCatch(), false)
		else {
			static_assert(!member_OnCatch_of<AnyChild>::callable, "OnCatch uncompatible");
			switch (MsgBox(S("Window Error"), err.toString(), MB::IconError | MB::AbortRetryIgnore)) {
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
	inline LRESULT Final() {
		if constexpr (member_OnFinal_of<AnyChild>::template compatible_to<LRESULT()>)
			reflect_as(child.OnFinal())
		else if constexpr (member_OnFinal_of<AnyChild>::template compatible_to<void()>)
			reflect_to(child.OnFinal(), -1)
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
#include "msg.inl"
	};
	inline CallPack DefProcOf() reflect_as((HWND)self);
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
#include "msg.inl"
	};
	inline MessageSwitch Message() reflect_as(hWnd);
#pragma endregion

#pragma region Methods
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

	inline int MsgBox(LPCTSTR lpCaption = O, LPCTSTR lpText = O, MB uType = MB::Ok) const reflect_as(WX::MsgBox(lpCaption, lpText, uType, self));
	inline int MsgBox(LPCTSTR lpCaption, const Exception &err) reflect_as(WX::MsgBox(lpCaption, err, self));

	inline auto &Focus() reflect_to_child(SetFocus(self));
	inline bool IsFocus() const reflect_as(GetFocus() == self);

	static inline Window Find(LPCTSTR lpszClass, LPCTSTR lpszName) reflect_as(FindWindow(lpszClass, lpszName));
	static inline WindowBase Find(LPCTSTR lpszName) reflect_as(FindWindow(MAKEINTRESOURCE(_ClassAtom), lpszName));

	inline LPoint ScreenToClient(LPoint pt) const assertl_reflect_as(::ScreenToClient(self, &pt), pt);
	inline LPoint ClientToScreen(LPoint pt) const assertl_reflect_as(::ClientToScreen(self, &pt), pt);
	inline LRect AdjustRect(LRect rc) const assertl_reflect_as(::AdjustWindowRect(&rc, Styles().yield(), this->Menu()), rc);
	inline LRect AdjustRect() const reflect_to(LRect rc, AdjustRect(rc), rc);

	inline void Validate(LPCRECT lpRect = O) const assertl_reflect_as(ValidateRect(self, lpRect));
	inline void Invalidate(LPCRECT lpRect = O, bool fErase = false) const assertl_reflect_as(InvalidateRect(self, lpRect, fErase));

	inline UINT_PTR SetTimer(UINT uElapse, UINT_PTR nIDEvent = 0) assertl_reflect_as((nIDEvent = ::SetTimer(self, nIDEvent, uElapse, O)), nIDEvent);
	inline void KillTimer(UINT_PTR nIDEvent) assertl_reflect_as(::KillTimer(self, nIDEvent));

	inline void Move(LRect rc, bool bRedraw = true) const assertl_reflect_as(::MoveWindow(self, rc.top, rc.left, rc.xsize(), rc.ysize(), bRedraw));

	inline auto &Update() assertl_reflect_as_child(UpdateWindow(self));
	inline CDC DC() const reflect_as(GetDC(self));

	inline auto &RegisterTouch(bool bFine = true, bool bWantPalm = false) assertl_reflect_as_child(RegisterTouchWindow(self, (bFine *TWF_FINETOUCH) | (bWantPalm * TWF_WANTPALM)));
	inline auto &UnregisterTouch() assertl_reflect_as_child(UnregisterTouchWindow(self));

	inline auto &Invalidate(LPCRECT lpRect = O, bool bErase = false) assertl_reflect_as_child(InvalidateRect(self, lpRect, bErase));

	inline TrackMouseEventBox TrackMouse() const reflect_as((HWND)self);

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

	inline auto &EnumChilds(Function<bool(HWND)> foreach) {
		EnumChildWindows(self, [](HWND hwnd, LPARAM lParam) -> BOOL {
			auto &foreach = *(Function<bool(HWND)> *)lParam;
			return foreach(hwnd);
		}, (LPARAM)std::addressof(foreach));
		retchild;
	}
#pragma endregion

#pragma region Properties
public: // Property - Iconic
	/* R */ inline bool Iconic() const reflect_as(IsIconic(self));
public: // Property - Visible
	/* W */ inline auto &Visible(bool bVisible) assertl_reflect_as_child(ShowWindow(self, SW_SHOW));
	/* R */ inline bool Visible() const reflect_as(IsWindowVisible(self));
public: // Proterty - Enabled
	/* W */ inline auto &Enabled(bool bEnable) assertl_reflect_as_child(EnableWindow(self, bEnable));
	/* R */ inline bool Enabled() const reflect_as(IsWindowEnabled(self));
public: // Property - TextLength
	/* R */ inline int TextLength() const reflect_as(GetWindowTextLength(self));
public: // Property - String
	/* W */ inline auto &Text(LPCTSTR lpString) assertl_reflect_as_child(SetWindowText(self, lpString) >= 0);
	/* R */ inline String Text() const {
		auto len = TextLength();
		if (len <= 0) return O;
		auto lpszName = String::Alloc(len);
		assertl(len == GetWindowText(self, lpszName, len + 1));
		return{ (size_t)len, lpszName };
	}
public: // Property - Parent
	/* W */ inline auto  &Parent(HWND hParent) nt_assertl_reflect_to_child(SetParent(self, hParent));
	/* R */ inline Window Parent() const reflect_as(Parent(self));
public: // Property - Menu
	/* W */ inline auto &Menu(HMENU hMenu) assertl_reflect_as_child(SetMenu(self, hMenu));
	/* R */ inline CMenu Menu() const reflect_as(GetMenu(self));
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
public: // Property - IconBig
	/* W */ inline auto &IconBig(HICON hIcon) reflect_to_child(Send<HICON>(WM_SETICON, ICON_BIG, hIcon));
	/* R */ inline CIcon IconBig() const reflect_as(Send<HICON>(WM_GETICON, ICON_BIG));
public: // Property - IconSmall
	/* W */ inline auto &IconSmall(HICON hIcon) reflect_to_child(Send<HICON>(WM_SETICON, ICON_SMALL, hIcon));
	/* R */ inline CIcon IconSmall() const reflect_as(Send<HICON>(WM_GETICON, ICON_SMALL));
public: // Property - Styles
	/* W */ inline auto &Styles(Style style) nt_assertl_reflect_to_child(SetWindowLongPtr(self, GWL_STYLE, style.yield()));
	/* R */ inline Style Styles() const reflect_as(reuse_as<Style>((LONG)GetWindowLongPtr(self, GWL_STYLE)));
public: // Property - StylesEx 
	/* W */ inline auto   &StylesEx(StyleEx styleEx) nt_assertl_reflect_to_child(SetWindowLongPtr(self, GWL_EXSTYLE, styleEx.yield()));
	/* R */ inline StyleEx StylesEx() const reflect_as(reuse_as<StyleEx>((DWORD)GetWindowLongPtr(self, GWL_EXSTYLE)));
public: // Property - ID
	/* W */ inline auto    &ID(LONG_PTR uId) nt_assertl_reflect_to_child(SetWindowLongPtr(self, GWLP_ID, uId));
	/* R */ inline LONG_PTR ID() const reflect_as(reuse_as<LONG_PTR>(GetWindowLongPtr(self, GWLP_ID)));
public: // Property - Module
	/* W */ inline auto   &Module(HINSTANCE hInstance) nt_assertl_reflect_to_child(SetWindowLongPtr(self, GWLP_HINSTANCE, reuse_as<LONG_PTR>(hInstance)));
	/* R */ inline CModule Module() const reflect_as(reuse_as<HINSTANCE>(GetWindowLongPtr(self, GWLP_HINSTANCE)));
public: // Property - UserData
	/* W */ inline auto &UserData(void *pData) nt_assertl_reflect_to_child(SetWindowLongPtr(self, GWLP_USERDATA, reuse_as<LONG_PTR>(pData)));
	/* R */ inline void *UserData() const reflect_as(reuse_as<void *>(GetWindowLongPtr(self, GWLP_USERDATA)));
public: // Property - Long 0
	/* W */ inline auto &HeapPtr(void *lpHeap, int nIndex) nt_assertl_reflect_to_child(SetWindowLongPtr(self, nIndex, (LONG_PTR)lpHeap));
	template<class AnyType = void>
	/* R */ inline AnyType *HeapPtr(int nIndex) const reflect_as(reuse_as<AnyType *>(GetWindowLongPtr(self, nIndex)));
public: // Property - ClassName
	/* R */ inline String ClassName() const {
		auto lpszClassName = String::Alloc(MaxLenClass);
		int len = GetClassName(self, lpszClassName, MaxLenClass);
		if (len <= 0) return O;
		lpszClassName = String::Realloc(len, lpszClassName);
		return { (size_t)len, lpszClassName };
	}
public: // Property - ClassMenuName
	/* W */ inline auto   &ClassMenuName(UINT uID) nt_assertl_reflect_to_child(SetClassLongPtr(self, GCLP_MENUNAME, (LONG_PTR)MAKEINTRESOURCE(uID)));
	/* W */ inline auto   &ClassMenuName(LPCTSTR lpMenuName) nt_assertl_reflect_to_child(SetClassLongPtr(self, GCLP_MENUNAME, (LONG_PTR)lpMenuName));
	/* R */ inline LPCTSTR ClassMenuName() const reflect_as(reuse_as<LPCTSTR>(GetClassLongPtr(self, GCLP_MENUNAME)));
public: // Property - ClassBackground
	/* W */ inline auto  &ClassBackground(HBRUSH hBrush) nt_assertl_reflect_to_child(SetClassLongPtr(self, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush));
	/* R */ inline CBrush ClassBackground() const reflect_as(reuse_as<HBRUSH>(GetClassLongPtr(self, GCLP_HBRBACKGROUND)));
public: // Property - ClassCursor
	/* W */ inline auto   &ClassCursor(HCURSOR hCursor) nt_assertl_reflect_to_child(SetClassLongPtr(self, GCLP_HCURSOR, (LONG_PTR)hCursor));
	/* R */ inline CCursor ClassCursor() const reflect_as(reuse_as<HCURSOR>(GetClassLongPtr(self, GCLP_HCURSOR)));
public: // Property - ClassIcon
	/* W */ inline auto &ClassIcon(HICON hIcon) nt_assertl_reflect_to_child(SetClassLongPtr(self, GCLP_HICON, (LONG_PTR)hIcon));
	/* R */ inline CIcon ClassIcon() const reflect_as(reuse_as<HICON>(GetClassLongPtr(self, GCLP_HICON)));
public: // Property - ClassModule
	/* W */ inline auto   &ClassModule(HINSTANCE hModule) nt_assertl_reflect_to_child(SetClassLongPtr(self, GCLP_HMODULE, (LONG_PTR)hModule));
	/* R */ inline CModule ClassModule() const reflect_as(reuse_as<HINSTANCE>(GetClassLongPtr(self, GCLP_HMODULE)));
public: // Property - ClassWndExtra
	/* W */ inline auto     &ClassWndExtra(ULONG_PTR hModule) nt_assertl_reflect_to_child(SetClassLongPtr(self, GCL_CBWNDEXTRA, (LONG_PTR)hModule));
	/* R */ inline ULONG_PTR ClassWndExtra() const reflect_as(GetClassLongPtr(self, GCL_CBWNDEXTRA));
public: // Property - ClassClsExtra
	/* W */ inline auto     &ClassClsExtra(ULONG_PTR hModule) nt_assertl_reflect_to_child(SetClassLongPtr(self, GCL_CBCLSEXTRA, (LONG_PTR)hModule));
	/* R */ inline ULONG_PTR ClassClsExtra() const reflect_as(GetClassLongPtr(self, GCL_CBCLSEXTRA));
public: // Property - ClassWndProc
	/* W */ inline auto   &ClassWndProc(WNDPROC WndProc) nt_assertl_reflect_to_child(SetClassLongPtr(self, GCLP_WNDPROC, (LONG_PTR)WndProc));
	/* R */ inline WndProc ClassWndProc() const reflect_as({ reuse_as<WNDPROC>(GetClassLongPtr(self, GCLP_WNDPROC)), self });
public: // Property - ClassIconSm
	/* W */ inline auto &ClassIconSm(HICON hIcon) nt_assertl_reflect_to_child(SetClassLongPtr(self, GCLP_HICONSM, (LONG_PTR)hIcon));
	/* R */ inline CIcon ClassIconSm() const reflect_as(reuse_as<HICON>(GetClassLongPtr(self, GCLP_HICONSM)));
public: // Property - ClassAtom
	/* W */ inline auto &ClassAtom(ATOM atom) nt_assertl_reflect_to_child(SetClassWord(self, GCW_ATOM, atom));
	/* R */ inline ATOM  ClassAtom() const reflect_as(GetClassWord(self, GCW_ATOM));
public: // Property - Handle
	inline WX::Handle &Handle() reflect_as(WX::Handle::Attach(hWnd));
	inline const WX::Handle &Handle() const reflect_as(WX::Handle::Attach(hWnd));
#pragma endregion

	inline void *operator new(size_t uSize, void *ptr) reflect_as(ptr);
	inline void *operator new(size_t uSize) assertl_reflect_as(auto lpHeap = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(Child)), lpHeap);
	inline void operator delete(void *ptr) reflect_to(HeapFree(GetProcessHeap(), 0, ptr));

	static inline Window &Attach(HWND &hWnd) reflect_as(ref_as<Window>(hWnd));

	inline auto &operator=(WindowBase &w) reflect_to_child(std::swap(this->hWnd, w.hWnd));
	inline auto &operator=(const WindowBase &w) const reflect_to_child(std::swap(this->hWnd, w.hWnd));

	inline operator bool() const reflect_as(IsWindow(hWnd));
	inline operator HWND() const reflect_as(hWnd);
	inline operator Window &() reflect_as(ref_as<Window>(hWnd));
	inline operator const Window() const reflect_as(hWnd);

	inline operator WX::Handle &() reflect_as(WX::Handle::Attach(hWnd));
	inline operator const WX::Handle &() const reflect_as(WX::Handle::Attach(hWnd));

	inline AnyChild *operator*() reflect_as(HeapPtr());
	inline const AnyChild *operator*() const reflect_as(HeapPtr());
	inline AnyChild *operator->() reflect_as(HeapPtr());
	inline const AnyChild *operator->() const reflect_as(HeapPtr());
};
template<class AnyChild, class SubXCreate, class Style, class StyleEx>
using WXCreate = typename WindowBase<AnyChild>::template XCreate<SubXCreate, Style, StyleEx>;
template<class AnyChild> ATOM WindowBase<AnyChild>::_ClassAtom = 0;
template<class AnyChild> HINSTANCE WindowBase<AnyChild>::_hClassModule = O;
template<class AnyChild> const String &&WindowBase<AnyChild>::_ClassName = Fits(typeid(typename WindowBase<AnyChild>::Child).name(), MaxLenClass);
#define SFINAE_Window(name) friend class WX::WindowBase<name>
#define BaseOf_Window(name) name : public WX::WindowBase<name>
#define WxCreate() public: struct xCreate : XCreate<xCreate>
#define WxClass() public: struct xClass : ClassExBase<xClass>
#pragma endregion

template<class AnyChild = void>
class ConsoleItf : public ChainExtend<ConsoleItf<AnyChild>, AnyChild> {
protected:
	HANDLE hIn = O, hOut = O, hErr = O;
public:
	ConsoleItf(Null) {}
	ConsoleItf() :
		hIn(GetStdHandle(STD_INPUT_HANDLE)),
		hOut(GetStdHandle(STD_OUTPUT_HANDLE)),
		hErr(GetStdHandle(STD_ERROR_HANDLE)) {}
	ConsoleItf(DWORD pid) reflect_to(Attach(pid));

	inline void Select() {
		hIn = reuse_as<File>(GetStdHandle(STD_INPUT_HANDLE));
		hOut = reuse_as<File>(GetStdHandle(STD_OUTPUT_HANDLE));
		hErr = reuse_as<File>(GetStdHandle(STD_ERROR_HANDLE));
	}
	inline void Reopen() {
		static FILE *fout = O, *ferr = O, *fin = O;
		freopen_s(&fout, "CONOUT$", "w+t", stdout);
		freopen_s(&ferr, "CONERR$", "w+t", stderr);
		freopen_s(&fin, "CONIN$", "r+t", stdin);
	}

#pragma region Allocator
	static inline void Attach(DWORD pid) assertl_reflect_as(AttachConsole(pid));
	static inline void Alloc() assertl_reflect_as(AllocConsole());
	static inline void Free() assertl_reflect_as(FreeConsole());
	inline operator Window() { return reuse_as<Window>(GetConsoleWindow()); }
#pragma endregion

#pragma region Properties
public: // Property - Attr
	/* W */ inline auto &Attr(WORD wAttr) assertl_reflect_as_self(SetConsoleTextAttribute(hOut, wAttr));
	/* R */ inline WORD  Attr() const assertl_reflect_to(CONSOLE_SCREEN_BUFFER_INFO csbi, GetConsoleScreenBufferInfo(hOut, &csbi), csbi.wAttributes);
public: // Property - Title
	/* W */ inline auto &Title(LPCTSTR lpTitle) assertl_reflect_as_self(SetConsoleTitle(lpTitle));
	/* R */ inline String Title() const {
		String title((size_t)MaxLenTitle);
		int len = GetConsoleTitle(title, MaxLenTitle + 1);
		if (len <= 0) return O;
		title.Resize(len);
		return title;
	}
public: // Property - CurPos
	/* W */ inline auto &CurPos(LPoint p) assertl_reflect_as_self(SetConsoleCursorPosition(hOut, COORD({ (short)p.x, (short)p.y })));
	/* R */ inline LPoint CurPos() const assertl_reflect_to(CONSOLE_SCREEN_BUFFER_INFO csbi, GetConsoleScreenBufferInfo(hOut, &csbi), { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y });
public: // Property - CurVis
	/* W */ inline auto &CurVis(bool bVisible) assertl_reflect_to_self(CONSOLE_CURSOR_INFO cci({ 0 }); cci.bVisible = bVisible, SetConsoleCursorInfo(hOut, &cci));
	/* R */ inline bool  CurVis() const assertl_reflect_to(CONSOLE_CURSOR_INFO cci({ 0 }), GetConsoleCursorInfo(hOut, &cci), cci.bVisible);
#pragma endregion

#pragma region Read Write
protected:
	inline DWORD _Write(HANDLE hOut, LPCWSTR lpszString, DWORD uLength) assertl_reflect_as(WriteConsoleW(hOut, lpszString, uLength, &uLength, O), uLength);
	inline DWORD _Write(HANDLE hOut, LPCSTR lpszString, DWORD uLength) assertl_reflect_as(WriteConsoleA(hOut, lpszString, uLength, &uLength, O), uLength);
public:
	inline DWORD Log(const String &s) reflect_as(_Write(hOut, s, (DWORD)s.Length()));
	template<class... Args>
	inline DWORD Log(const Args& ...args) reflect_as(Log(Cats(args...)));
public:
	inline DWORD Err(const String &s) reflect_as(_Write(hErr, s, (DWORD)s.Length()));
	template<class... Args>
	inline DWORD Err(const Args& ...args) reflect_as(Err(Cats(args...)));
public:
	inline auto &operator[](LPoint p) reflect_as(CurPos(p));
	inline auto &operator[](bool bCurVis) reflect_as(CurVis(bCurVis));
	template<class... Args>
	inline auto &operator()(const Args& ...args) reflect_to_self(Log(Cats(args...)));
#pragma endregion

};

static inline ConsoleItf<> Console;

class ConsoleCtl : public ConsoleItf<ConsoleCtl> {
public:
	~ConsoleCtl() reflect_to(Free());
};

}
