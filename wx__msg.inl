//
//		From Windowsx.h
// 
// --- Find With RegExp ---
// /\* (?<ret>\w+) (?<name>\w+)(?<arglist>\(.*?\)) \*/\r\n#define HANDLE_(?<msgid>\w+).+?\) \\\r\n\s*(?<unpack>.+\))\r\n#define FORWARD_\w+(?<args>\(.+?\)) \\\r\n\s*(?<pack>.+?)\r\n
//
// --- Replace With RegExp ---
// MSG_TRANS(${msgid},\n\t${ret}, ${name}, ${arglist},\n\t${pack},\n\t${args},\n\t${unpack})
// 
// --- Patch Item ---
// WM_COPYDATA
// WM_COPYDATA
// WM_CTLCOLOR(\w+)
// WM_MENUSELECT
// WM_(NC)*(.)*BUTTOND(OWN|BLCLK)
// WM_SYSTEMERROR
//

#include <Windows.h>

#ifndef MSG_TRANS
#	define MSG_TRANS(msgid, \
	ret, name, argslist, \
	args, \
	send, \
	call)
#endif
#ifndef CALL
#	define CALL(name)
#endif
#ifndef SEND
#	define SEND(ret, msgid, wparam, lparam)
#endif
#ifndef ARGS
#	define ARGS(...) (__VA_ARGS__)
#endif

/*1*/ MSG_TRANS(WM_CREATE, 
	bool, Create, (LPCREATESTRUCT lpCreateStruct),
	ARGS(lpCreateStruct), 
	SEND(bool, WM_CREATE, 0L, (LPARAM)(LPCREATESTRUCT)(lpCreateStruct)), 
	((CALL(Create))((LPCREATESTRUCT)(lParam)) ? 0L : (LRESULT)-1L))
/*2*/ MSG_TRANS(WM_DESTROY, 
	void, Destroy, (),
	ARGS(), 
	SEND(void, WM_DESTROY, 0L, 0L), 
	((CALL(Destroy))(), 0L))
/*3*/ MSG_TRANS(WM_MOVE, 
	void, Move, (int x, int y),
	ARGS(x, y), 
	SEND(void, WM_MOVE, 0L, MAKELPARAM((x), (y))), 
	((CALL(Move))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*5*/ MSG_TRANS(WM_SIZE, 
	void, Size, (UINT state, int cx, int cy),
	ARGS(state, cx, cy), 
	SEND(void, WM_SIZE, (WPARAM)(UINT)(state), MAKELPARAM((cx), (cy))), 
	((CALL(Size))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*6*/ MSG_TRANS(WM_ACTIVATE, 
	void, Activate, (UINT state, HWND hwndActDeact, bool fMinimized),
	ARGS(state, hwndActDeact, fMinimized), 
	SEND(void, WM_ACTIVATE, MAKEWPARAM((state), (fMinimized)), (LPARAM)(HWND)(hwndActDeact)), 
	((CALL(Activate))((UINT)LOWORD(wParam), (HWND)(lParam), (bool)HIWORD(wParam)), 0L))
/*7*/ MSG_TRANS(WM_SETFOCUS, 
	void, SetFocus, (HWND hwndOldFocus),
	ARGS(hwndOldFocus), 
	SEND(void, WM_SETFOCUS, (WPARAM)(HWND)(hwndOldFocus), 0L), 
	((CALL(SetFocus))((HWND)(wParam)), 0L))
/*8*/ MSG_TRANS(WM_KILLFOCUS, 
	void, KillFocus, (HWND hwndNewFocus),
	ARGS(hwndNewFocus), 
	SEND(void, WM_KILLFOCUS, (WPARAM)(HWND)(hwndNewFocus), 0L), 
	((CALL(KillFocus))((HWND)(wParam)), 0L))
/*10*/ MSG_TRANS(WM_ENABLE, 
	void, Enable, (bool fEnable),
	ARGS(fEnable), 
	SEND(void, WM_ENABLE, (WPARAM)(bool)(fEnable), 0L), 
	((CALL(Enable))((bool)(wParam)), 0L))
/*11*/ MSG_TRANS(WM_SETREDRAW, 
	void, SetRedraw, (bool fRedraw),
	ARGS(fRedraw), 
	SEND(void, WM_SETREDRAW, (WPARAM)(bool)(fRedraw), 0L), 
	((CALL(SetRedraw))((bool)(wParam)), 0L))
/*12*/ MSG_TRANS(WM_SETTEXT, 
	void, SetText, (LPCTSTR lpszText),
	ARGS(lpszText), 
	SEND(void, WM_SETTEXT, 0L, (LPARAM)(LPCTSTR)(lpszText)), 
	((CALL(SetText))((LPCTSTR)(lParam)), 0L))
/*13*/ MSG_TRANS(WM_GETTEXT, 
	INT, GetText, (int cchTextMax, LPTSTR lpszText),
	ARGS(cchTextMax, lpszText), 
	SEND(int, WM_GETTEXT, (WPARAM)(int)(cchTextMax), (LPARAM)(LPTSTR)(lpszText)), 
	(LRESULT)(DWORD)(int)(CALL(GetText))((int)(wParam), (LPTSTR)(lParam)))
/*14*/ MSG_TRANS(WM_GETTEXTLENGTH, 
	INT, GetTextLength, (),
	ARGS(), 
	SEND(int, WM_GETTEXTLENGTH, 0L, 0L), 
	(LRESULT)(DWORD)(int)(CALL(GetTextLength))())
/*15*/ MSG_TRANS(WM_PAINT, 
	void, Paint, (),
	ARGS(), 
	SEND(void, WM_PAINT, 0L, 0L), 
	((CALL(Paint))(), 0L))
/*16*/ MSG_TRANS(WM_CLOSE, 
	void, Close, (),
	ARGS(), 
	SEND(void, WM_CLOSE, 0L, 0L), 
	((CALL(Close))(), 0L))
/*17*/ MSG_TRANS(WM_QUERYENDSESSION, 
	bool, QueryEndSession, (),
	ARGS(), 
	SEND(bool, WM_QUERYENDSESSION, 0L, 0L), 
	MAKELRESULT((bool)(CALL(QueryEndSession))(), 0L))
/*18*/ MSG_TRANS(WM_QUIT, 
	void, Quit, (int exitCode),
	ARGS(exitCode), 
	SEND(void, WM_QUIT, (WPARAM)(exitCode), 0L), 
	((CALL(Quit))((int)(wParam)), 0L))
/*19*/ MSG_TRANS(WM_QUERYOPEN, 
	bool, QueryOpen, (),
	ARGS(), 
	SEND(bool, WM_QUERYOPEN, 0L, 0L), 
	MAKELRESULT((bool)(CALL(QueryOpen))(), 0L))
/*20*/ MSG_TRANS(WM_ERASEBKGND, 
	bool, EraseBkgnd, (HDC hdc),
	ARGS(hdc), 
	SEND(bool, WM_ERASEBKGND, (WPARAM)(HDC)(hdc), 0L), 
	(LRESULT)(DWORD)(bool)(CALL(EraseBkgnd))((HDC)(wParam)))
/*21*/ MSG_TRANS(WM_SYSCOLORCHANGE, 
	void, SysColorChange, (),
	ARGS(), 
	SEND(void, WM_SYSCOLORCHANGE, 0L, 0L), 
	((CALL(SysColorChange))(), 0L))
/*22*/ MSG_TRANS(WM_ENDSESSION, 
	void, EndSession, (bool fEnding),
	ARGS(fEnding), 
	SEND(void, WM_ENDSESSION, (WPARAM)(bool)(fEnding), 0L), 
	((CALL(EndSession))((bool)(wParam)), 0L))
/*24*/ MSG_TRANS(WM_SHOWWINDOW, 
	void, ShowWindow, (bool fShow, UINT status),
	ARGS(fShow, status), 
	SEND(void, WM_SHOWWINDOW, (WPARAM)(bool)(fShow), (LPARAM)(UINT)(status)), 
	((CALL(ShowWindow))((bool)(wParam), (UINT)(lParam)), 0L))
/*26*/ MSG_TRANS(WM_WININICHANGE, 
	void, WinIniChange, (LPCTSTR lpszSectionName),
	ARGS(lpszSectionName), 
	SEND(void, WM_WININICHANGE, 0L, (LPARAM)(LPCTSTR)(lpszSectionName)), 
	((CALL(WinIniChange))((LPCTSTR)(lParam)), 0L))
/*27*/ MSG_TRANS(WM_DEVMODECHANGE, 
	void, DevModeChange, (LPCTSTR lpszDeviceName),
	ARGS(lpszDeviceName), 
	SEND(void, WM_DEVMODECHANGE, 0L, (LPARAM)(LPCTSTR)(lpszDeviceName)), 
	((CALL(DevModeChange))((LPCTSTR)(lParam)), 0L))
/*28*/ MSG_TRANS(WM_ACTIVATEAPP, 
	void, ActivateApp, (bool fActivate, DWORD dwThreadId),
	ARGS(fActivate, dwThreadId), 
	SEND(void, WM_ACTIVATEAPP, (WPARAM)(bool)(fActivate), (LPARAM)(dwThreadId)), 
	((CALL(ActivateApp))((bool)(wParam), (DWORD)(lParam)), 0L))
/*29*/ MSG_TRANS(WM_FONTCHANGE, 
	void, FontChange, (),
	ARGS(), 
	SEND(void, WM_FONTCHANGE, 0L, 0L), 
	((CALL(FontChange))(), 0L))
/*30*/ MSG_TRANS(WM_TIMECHANGE, 
	void, TimeChange, (),
	ARGS(), 
	SEND(void, WM_TIMECHANGE, 0L, 0L), 
	((CALL(TimeChange))(), 0L))
/*31*/ MSG_TRANS(WM_CANCELMODE, 
	void, CancelMode, (),
	ARGS(), 
	SEND(void, WM_CANCELMODE, 0L, 0L), 
	((CALL(CancelMode))(), 0L))
/*32*/ MSG_TRANS(WM_SETCURSOR, 
	bool, SetCursor, (HWND hwndCursor, UINT codeHitTest, UINT msg),
	ARGS(hwndCursor, codeHitTest, msg), 
	SEND(bool, WM_SETCURSOR, (WPARAM)(HWND)(hwndCursor), MAKELPARAM((codeHitTest), (msg))), 
	(LRESULT)(DWORD)(bool)(CALL(SetCursor))((HWND)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)))
/*33*/ MSG_TRANS(WM_MOUSEACTIVATE, 
	int, MouseActivate, (HWND hwndTopLevel, UINT codeHitTest, UINT msg),
	ARGS(hwndTopLevel, codeHitTest, msg), 
	SEND(int, WM_MOUSEACTIVATE, (WPARAM)(HWND)(hwndTopLevel), MAKELPARAM((codeHitTest), (msg))), 
	(LRESULT)(DWORD)(int)(CALL(MouseActivate))((HWND)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)))
/*34*/ MSG_TRANS(WM_CHILDACTIVATE, 
	void, ChildActivate, (),
	ARGS(), 
	SEND(void, WM_CHILDACTIVATE, 0L, 0L), 
	((CALL(ChildActivate))(), 0L))
/*35*/ MSG_TRANS(WM_QUEUESYNC, 
	void, QueueSync, (),
	ARGS(), 
	SEND(void, WM_QUEUESYNC, 0L, 0L), 
	((CALL(QueueSync))(), 0L))
/*36*/ MSG_TRANS(WM_GETMINMAXINFO, 
	void, GetMinMaxInfo, (LPMINMAXINFO lpMinMaxInfo),
	ARGS(lpMinMaxInfo), 
	SEND(void, WM_GETMINMAXINFO, 0L, (LPARAM)(LPMINMAXINFO)(lpMinMaxInfo)), 
	((CALL(GetMinMaxInfo))((LPMINMAXINFO)(lParam)), 0L))
/*39*/ MSG_TRANS(WM_ICONERASEBKGND, 
	bool, IconEraseBkgnd, (HDC hdc),
	ARGS(hdc), 
	SEND(bool, WM_ICONERASEBKGND, (WPARAM)(HDC)(hdc), 0L), 
	(LRESULT)(DWORD)(bool)(CALL(IconEraseBkgnd))((HDC)(wParam)))
/*40*/ MSG_TRANS(WM_NEXTDLGCTL, 
	HWND, NextDlgCtl, (HWND hwndSetFocus, bool fNext),
	ARGS(hwndSetFocus, fNext), 
	SEND(HWND, WM_NEXTDLGCTL, (WPARAM)(HWND)(hwndSetFocus), (LPARAM)(fNext)), 
	(LRESULT)(UINT_PTR)(HWND)(CALL(NextDlgCtl))((HWND)(wParam), (bool)(lParam)))
/*42*/ MSG_TRANS(WM_SPOOLERSTATUS, 
	void, SpoolerStatus, (UINT status, int cJobInQueue),
	ARGS(status, cJobInQueue), 
	SEND(void, WM_SPOOLERSTATUS, (WPARAM)(status), MAKELPARAM((cJobInQueue), 0)), 
	((CALL(SpoolerStatus))((UINT)(wParam), (int)(int16_t)LOWORD(lParam)), 0L))
/*43*/ MSG_TRANS(WM_DRAWITEM, 
	void, DrawItem, (const DRAWITEMSTRUCT * lpDrawItem),
	ARGS(lpDrawItem), 
	SEND(void, WM_DRAWITEM, (WPARAM)(((const DRAWITEMSTRUCT *)lpDrawItem)->CtlID), (LPARAM)(const DRAWITEMSTRUCT *)(lpDrawItem)), 
	((CALL(DrawItem))((const DRAWITEMSTRUCT *)(lParam)), 0L))
/*44*/ MSG_TRANS(WM_MEASUREITEM, 
	void, MeasureItem, (MEASUREITEMSTRUCT * lpMeasureItem),
	ARGS(lpMeasureItem), 
	SEND(void, WM_MEASUREITEM, (WPARAM)(((MEASUREITEMSTRUCT *)lpMeasureItem)->CtlID), (LPARAM)(MEASUREITEMSTRUCT *)(lpMeasureItem)), 
	((CALL(MeasureItem))((MEASUREITEMSTRUCT *)(lParam)), 0L))
/*45*/ MSG_TRANS(WM_DELETEITEM, 
	void, DeleteItem, (const DELETEITEMSTRUCT * lpDeleteItem),
	ARGS(lpDeleteItem), 
	SEND(void, WM_DELETEITEM, (WPARAM)(((const DELETEITEMSTRUCT *)(lpDeleteItem))->CtlID), (LPARAM)(const DELETEITEMSTRUCT *)(lpDeleteItem)), 
	((CALL(DeleteItem))((const DELETEITEMSTRUCT *)(lParam)), 0L))
/*46*/ MSG_TRANS(WM_VKEYTOITEM, 
	int, VkeyToItem, (UINT vk, HWND hwndListBox, int iCaret),
	ARGS(vk, hwndListBox, iCaret), 
	SEND(int, WM_VKEYTOITEM, MAKEWPARAM((vk), (iCaret)), (LPARAM)(hwndListBox)), 
	(LRESULT)(DWORD)(int)(CALL(VkeyToItem))((UINT)LOWORD(wParam), (HWND)(lParam), (int)(int16_t)HIWORD(wParam)))
/*47*/ MSG_TRANS(WM_CHARTOITEM, 
	int, CharToItem, (UINT ch, HWND hwndListBox, int iCaret),
	ARGS(ch, hwndListBox, iCaret), 
	SEND(int, WM_CHARTOITEM, MAKEWPARAM((UINT)(ch), (UINT)(iCaret)), (LPARAM)(hwndListBox)), 
	(LRESULT)(DWORD)(int)(CALL(CharToItem))((UINT)LOWORD(wParam), (HWND)(lParam), (int)(int16_t)HIWORD(wParam)))
/*48*/ MSG_TRANS(WM_SETFONT, 
	void, SetFont, (HFONT hfont, bool fRedraw),
	ARGS(hfont, fRedraw), 
	SEND(void, WM_SETFONT, (WPARAM)(HFONT)(hfont), (LPARAM)(bool)(fRedraw)), 
	((CALL(SetFont))((HFONT)(wParam), (bool)(lParam)), 0L))
/*49*/ MSG_TRANS(WM_GETFONT, 
	HFONT, GetFont, (),
	ARGS(), 
	SEND(HFONT, WM_GETFONT, 0L, 0L), 
	(LRESULT)(UINT_PTR)(HFONT)(CALL(GetFont))())
/*55*/ MSG_TRANS(WM_QUERYDRAGICON, 
	HICON, QueryDragIcon, (),
	ARGS(), 
	SEND(HICON, WM_QUERYDRAGICON, 0L, 0L), 
	(LRESULT)(DWORD)(UINT)(CALL(QueryDragIcon))())
/*57*/ MSG_TRANS(WM_COMPAREITEM, 
	int, CompareItem, (const COMPAREITEMSTRUCT * lpCompareItem),
	ARGS(lpCompareItem), 
	SEND(int, WM_COMPAREITEM, (WPARAM)(((const COMPAREITEMSTRUCT *)(lpCompareItem))->CtlID), (LPARAM)(const COMPAREITEMSTRUCT *)(lpCompareItem)), 
	(LRESULT)(DWORD)(int)(CALL(CompareItem))((const COMPAREITEMSTRUCT *)(lParam)))
/*65*/ MSG_TRANS(WM_COMPACTING, 
	void, Compacting, (UINT compactRatio),
	ARGS(compactRatio), 
	SEND(void, WM_COMPACTING, (WPARAM)(UINT)(compactRatio), 0L), 
	((CALL(Compacting))((UINT)(wParam)), 0L))
/*68*/ MSG_TRANS(WM_COMMNOTIFY, 
	void, CommNotify, (int cid, UINT flags),
	ARGS(cid, flags), 
	SEND(void, WM_COMMNOTIFY, (WPARAM)(cid), MAKELPARAM((flags), 0)), 
	((CALL(CommNotify))((int)(wParam), (UINT)LOWORD(lParam)), 0L))
/*70*/ MSG_TRANS(WM_WINDOWPOSCHANGING, 
	bool, WindowPosChanging, (LPWINDOWPOS lpwpos),
	ARGS(lpwpos), 
	SEND(bool, WM_WINDOWPOSCHANGING, 0L, (LPARAM)(LPWINDOWPOS)(lpwpos)), 
	(LRESULT)(DWORD)(bool)(CALL(WindowPosChanging))((LPWINDOWPOS)(lParam)))
/*71*/ MSG_TRANS(WM_WINDOWPOSCHANGED, 
	void, WindowPosChanged, (const WINDOWPOS *lpwpos),
	ARGS(lpwpos), 
	SEND(void, WM_WINDOWPOSCHANGED, 0L, (LPARAM)(const WINDOWPOS *)(lpwpos)), 
	((CALL(WindowPosChanged))((const WINDOWPOS *)(lParam)), 0L))
/*72*/ MSG_TRANS(WM_POWER, 
	void, Power, (int code),
	ARGS(code), 
	SEND(void, WM_POWER, (WPARAM)(int)(code), 0L), 
	((CALL(Power))((int)(wParam)), 0L))
/*74*/ MSG_TRANS(WM_COPYDATA, 
	bool, CopyData, (HWND hwndFrom, PCOPYDATASTRUCT pcds),
	ARGS(hwndFrom, pcds), 
	SEND(bool, WM_COPYDATA, (WPARAM)(hwndFrom), (LPARAM)(pcds)), 
	((CALL(CopyData))((HWND)(wParam), (PCOPYDATASTRUCT)lParam), 0L))
/*123*/ MSG_TRANS(WM_CONTEXTMENU, 
	void, ContextMenu, (HWND hwndContext, UINT xPos, UINT yPos),
	ARGS(hwndContext, xPos, yPos), 
	SEND(void, WM_CONTEXTMENU, (WPARAM)(HWND)(hwndContext), MAKELPARAM((UINT)(xPos), (UINT)(yPos))), 
	((CALL(ContextMenu))((HWND)(wParam), (int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*126*/ MSG_TRANS(WM_DISPLAYCHANGE, 
	void, DisplayChange, (UINT bitsPerPixel, UINT cxScreen, UINT cyScreen),
	ARGS(bitsPerPixel, cxScreen, cyScreen), 
	SEND(void, WM_DISPLAYCHANGE, (WPARAM)(UINT)(bitsPerPixel), (LPARAM)MAKELPARAM((UINT)(cxScreen), (UINT)(cyScreen))), 
	((CALL(DisplayChange))((UINT)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L))
/*129*/ MSG_TRANS(WM_NCCREATE, 
	bool, NCCreate, (LPCREATESTRUCT lpCreateStruct),
	ARGS(lpCreateStruct), 
	SEND(bool, WM_NCCREATE, 0L, (LPARAM)(LPCREATESTRUCT)(lpCreateStruct)), 
	(LRESULT)(DWORD)(bool)(CALL(NCCreate))((LPCREATESTRUCT)(lParam)))
/*130*/ MSG_TRANS(WM_NCDESTROY, 
	void, NCDestroy, (),
	ARGS(), 
	SEND(void, WM_NCDESTROY, 0L, 0L), 
	((CALL(NCDestroy))(), 0L))
/*131*/ MSG_TRANS(WM_NCCALCSIZE, 
	UINT, NCCalcSize, (bool fCalcValidRects, NCCALCSIZE_PARAMS * lpcsp),
	ARGS(fCalcValidRects, lpcsp), 
	SEND(UINT, WM_NCCALCSIZE, (WPARAM)(fCalcValidRects), (LPARAM)(NCCALCSIZE_PARAMS *)(lpcsp)), 
	(LRESULT)(DWORD)(UINT)(CALL(NCCalcSize))((bool)(wParam), (NCCALCSIZE_PARAMS *)(lParam)))
/*132*/ MSG_TRANS(WM_NCHITTEST, 
	UINT, NCHitTest, (int x, int y),
	ARGS(x, y), 
	SEND(UINT, WM_NCHITTEST, 0L, MAKELPARAM((x), (y))), 
	(LRESULT)(DWORD)(UINT)(CALL(NCHitTest))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)))
/*133*/ MSG_TRANS(WM_NCPAINT, 
	void, NCPaint, (HRGN hrgn),
	ARGS(hrgn), 
	SEND(void, WM_NCPAINT, (WPARAM)(HRGN)(hrgn), 0L), 
	((CALL(NCPaint))((HRGN)(wParam)), 0L))
/*134*/ MSG_TRANS(WM_NCACTIVATE, 
	bool, NCActivate, (bool fActive, HWND hwndActDeact, bool fMinimized),
	ARGS(fActive, hwndActDeact, fMinimized), 
	SEND(bool, WM_NCACTIVATE, (WPARAM)(bool)(fActive), 0L), 
	(LRESULT)(DWORD)(bool)(CALL(NCActivate))((bool)(wParam), 0L, 0L))
/*135*/ MSG_TRANS(WM_GETDLGCODE, 
	UINT, GetDlgCode, (LPMSG lpmsg),
	ARGS(lpmsg), 
	SEND(UINT, WM_GETDLGCODE, (lpmsg ? lpmsg->wParam : 0), (LPARAM)(LPMSG)(lpmsg)), 
	(LRESULT)(DWORD)(UINT)(CALL(GetDlgCode))((LPMSG)(lParam)))
/*160*/ MSG_TRANS(WM_NCMOUSEMOVE, 
	void, NCMouseMove, (int x, int y, UINT codeHitTest),
	ARGS(x, y, codeHitTest), 
	SEND(void, WM_NCMOUSEMOVE, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y))), 
	((CALL(NCMouseMove))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*161*/ MSG_TRANS(WM_NCLBUTTONDOWN, 
	void, NCLButtonDown, (int x, int y, UINT codeHitTest),
	ARGS(x, y, codeHitTest), 
	SEND(void, WM_NCLBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y))), 
	((CALL(NCLButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*162*/ MSG_TRANS(WM_NCLBUTTONUP, 
	void, NCLButtonUp, (int x, int y, UINT codeHitTest),
	ARGS(x, y, codeHitTest),
	SEND(void, WM_NCLBUTTONUP, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y))), 
	((CALL(NCLButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*163*/ MSG_TRANS(WM_NCLBUTTONDBLCLK, 
	void, NCLButtonClick, (int x, int y, UINT codeHitTest),
	ARGS(x, y, codeHitTest), 
	SEND(void, WM_NCLBUTTONDBLCLK, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y))), 
	((CALL(NCLButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*164*/ MSG_TRANS(WM_NCRBUTTONDOWN, 
	void, NCRButtonDown, (int x, int y, UINT codeHitTest),
	ARGS(x, y, codeHitTest),
	SEND(void, WM_NCRBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((CALL(NCRButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*165*/ MSG_TRANS(WM_NCRBUTTONUP, 
	void, NCRButtonUp, (int x, int y, UINT codeHitTest),
	ARGS(x, y, codeHitTest),
	SEND(void, WM_NCRBUTTONUP, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((CALL(NCRButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*166*/ MSG_TRANS(WM_NCRBUTTONDBLCLK, 
	void, NCRButtonClick, (int x, int y, UINT codeHitTest),
	ARGS(x, y, codeHitTest), 
	SEND(void, WM_NCRBUTTONDBLCLK, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((CALL(NCRButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*167*/ MSG_TRANS(WM_NCMBUTTONDOWN, 
	void, NCMButtonDown, (int x, int y, UINT codeHitTest),
	ARGS(x, y, codeHitTest),
	SEND(void, WM_NCMBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((CALL(NCMButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*168*/ MSG_TRANS(WM_NCMBUTTONUP, 
	void, NCMButtonUp, (int x, int y, UINT codeHitTest),
	ARGS(x, y, codeHitTest),
	SEND(void, WM_NCMBUTTONUP, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((CALL(NCMButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*169*/ MSG_TRANS(WM_NCMBUTTONDBLCLK, 
	void, NCMButtonClick, (int x, int y, UINT codeHitTest),
	ARGS(x, y, codeHitTest), 
	SEND(void, WM_NCMBUTTONDBLCLK, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((CALL(NCMButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*256*/ MSG_TRANS(WM_KEYDOWN, 
	void, KeyDown, (UINT vk, int16_t wRepeat, KEY_FLAGS flags),
	ARGS(vk, wRepeat, flags),
	SEND(void, WM_KEYDOWN, (WPARAM)(UINT)(vk), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))), 
	((CALL(KeyDown))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*257*/ MSG_TRANS(WM_KEYUP, 
	void, KeyUp, (UINT vk, int16_t wRepeat, KEY_FLAGS flags),
	ARGS(vk, wRepeat, flags),
	SEND(void, WM_KEYUP, (WPARAM)(UINT)(vk), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))), 
	((CALL(KeyUp))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*258*/ MSG_TRANS(WM_CHAR, 
	void, Char, (TCHAR ch, int16_t wRepeat, KEY_FLAGS flags),
	ARGS(ch, wRepeat, flags),
	SEND(void, WM_CHAR, (WPARAM)(UINT)(ch), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))),
	((CALL(Char))((TCHAR)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*259*/ MSG_TRANS(WM_DEADCHAR, 
	void, DeadChar, (TCHAR ch, int16_t wRepeat, KEY_FLAGS flags),
	ARGS(ch, wRepeat, flags),
	SEND(void, WM_DEADCHAR, (WPARAM)(UINT)(ch), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))),
	((CALL(DeadChar))((TCHAR)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*260*/ MSG_TRANS(WM_SYSKEYDOWN, 
	void, SysKeyDown, (UINT vk, int16_t wRepeat, KEY_FLAGS flags),
	ARGS(vk, wRepeat, flags),
	SEND(void, WM_SYSKEYDOWN, (WPARAM)(UINT)(vk), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))), 
	((CALL(SysKeyDown))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*261*/ MSG_TRANS(WM_SYSKEYUP, 
	void, SysKeyUp, (UINT vk, int16_t wRepeat, KEY_FLAGS flags),
	ARGS(vk, wRepeat, flags),
	SEND(void, WM_SYSKEYUP, (WPARAM)(UINT)(vk), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))), 
	((CALL(SysKeyUp))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*262*/ MSG_TRANS(WM_SYSCHAR, 
	void, SysChar, (TCHAR ch, int16_t wRepeat, KEY_FLAGS flags),
	ARGS(ch, wRepeat, flags),
	SEND(void, WM_SYSCHAR, (WPARAM)(UINT)(ch), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))),
	((CALL(SysChar))((TCHAR)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*263*/ MSG_TRANS(WM_SYSDEADCHAR, 
	void, SysDeadChar, (TCHAR ch, int16_t wRepeat, KEY_FLAGS flags),
	ARGS(ch, wRepeat, flags),
	SEND(void, WM_SYSDEADCHAR, (WPARAM)(UINT)(ch), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))),
	((CALL(SysDeadChar))((TCHAR)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*272*/ MSG_TRANS(WM_INITDIALOG, 
	bool, InitDialog, (HWND hwndFocus, LPARAM lParam),
	ARGS(hwndFocus, lParam), 
	SEND(bool, WM_INITDIALOG, (WPARAM)(HWND)(hwndFocus), (lParam)), 
	(LRESULT)(DWORD)(UINT)(bool)(CALL(InitDialog))((HWND)(wParam), lParam))
/*273*/ MSG_TRANS(WM_COMMAND, 
	int, Command, (int id, HWND hwndCtl, UINT codeNotify),
	ARGS(id, hwndCtl, codeNotify), 
	SEND(int, WM_COMMAND, MAKEWPARAM((UINT)(id), (UINT)(codeNotify)), (LPARAM)(HWND)(hwndCtl)), 
	((CALL(Command))((int)(LOWORD(wParam)), (HWND)(lParam), (UINT)HIWORD(wParam)), 0L))
/*274*/ MSG_TRANS(WM_SYSCOMMAND, 
	void, SysCommand, (UINT cmd, int x, int y),
	ARGS(cmd, x, y), 
	SEND(void, WM_SYSCOMMAND, (WPARAM)(UINT)(cmd), MAKELPARAM((x), (y))), 
	((CALL(SysCommand))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*275*/ MSG_TRANS(WM_TIMER, 
	void, Timer, (UINT id),
	ARGS(id), 
	SEND(void, WM_TIMER, (WPARAM)(UINT)(id), 0L), 
	((CALL(Timer))((UINT)(wParam)), 0L))
/*276*/ MSG_TRANS(WM_HSCROLL, 
	void, HScroll, (HWND hwndCtl, UINT code, int pos),
	ARGS(hwndCtl, code, pos), 
	SEND(void, WM_HSCROLL, MAKEWPARAM((UINT)(int)(code), (UINT)(int)(pos)), (LPARAM)(HWND)(hwndCtl)), 
	((CALL(HScroll))((HWND)(lParam), (UINT)(LOWORD(wParam)), (int)(int16_t)HIWORD(wParam)), 0L))
/*277*/ MSG_TRANS(WM_VSCROLL, 
	void, VScroll, (HWND hwndCtl, UINT code, int pos),
	ARGS(hwndCtl, code, pos), 
	SEND(void, WM_VSCROLL, MAKEWPARAM((UINT)(int)(code), (UINT)(int)(pos)), (LPARAM)(HWND)(hwndCtl)), 
	((CALL(VScroll))((HWND)(lParam), (UINT)(LOWORD(wParam)), (int)(int16_t)HIWORD(wParam)), 0L))
/*278*/ MSG_TRANS(WM_INITMENU, 
	void, InitMenu, (HMENU hMenu),
	ARGS(hMenu), 
	SEND(void, WM_INITMENU, (WPARAM)(HMENU)(hMenu), 0L), 
	((CALL(InitMenu))((HMENU)(wParam)), 0L))
/*279*/ MSG_TRANS(WM_INITMENUPOPUP, 
	void, InitMenuPopup, (HMENU hMenu, UINT item, bool fSystemMenu),
	ARGS(hMenu, item, fSystemMenu), 
	SEND(void, WM_INITMENUPOPUP, (WPARAM)(HMENU)(hMenu), MAKELPARAM((item), (fSystemMenu))), 
	((CALL(InitMenuPopup))((HMENU)(wParam), (UINT)LOWORD(lParam), (bool)HIWORD(lParam)), 0L))
/*287*/ MSG_TRANS(WM_MENUSELECT, 
	void, MenuSelect, (HMENU hmenu, int item, HMENU hmenuPopup, UINT flags),
	ARGS(hmenu, item, hmenuPopup, flags), 
	SEND(void, WM_MENUSELECT, MAKEWPARAM((item), (flags)), (LPARAM)(HMENU)((hmenu) ? (hmenu) : (hmenuPopup))), 
	((CALL(MenuSelect))((HMENU)(lParam), (HIWORD(wParam) & MF_POPUP) ? 0L : (int)(LOWORD(wParam)), (HIWORD(wParam) & MF_POPUP) ? WX::GetSubMenu((HMENU)lParam, LOWORD(wParam)) : 0L, (UINT)(((int16_t)HIWORD(wParam) == -1) ? 0xFFFFFFFF : HIWORD(wParam))), 0L))
/*288*/ MSG_TRANS(WM_MENUCHAR, 
	DWORD, MenuChar, (UINT ch, UINT flags, HMENU hmenu),
	ARGS(ch, flags, hmenu), 
	SEND(DWORD, WM_MENUCHAR, MAKEWPARAM(flags, (WORD)(ch)), (LPARAM)(HMENU)(hmenu)), 
	(LRESULT)(DWORD)(CALL(MenuChar))((UINT)(LOWORD(wParam)), (UINT)HIWORD(wParam), (HMENU)(lParam)))
/*289*/ MSG_TRANS(WM_ENTERIDLE, 
	void, EnterIdle, (UINT source, HWND hwndSource),
	ARGS(source, hwndSource), 
	SEND(void, WM_ENTERIDLE, (WPARAM)(UINT)(source), (LPARAM)(HWND)(hwndSource)), 
	((CALL(EnterIdle))((UINT)(wParam), (HWND)(lParam)), 0L))
/*294*/ MSG_TRANS(WM_MENUCOMMAND,
	void, MenuCommand, (UINT menuId, HMENU hMenu),
	ARGS(menuId, hMenu),
	SEND(void, WM_MENUCOMMAND, (WPARAM)(UINT)(menuId), (LPARAM)(HMENU)(hMenu)),
	((CALL(MenuCommand))((UINT)(wParam), (HMENU)(lParam)), 0L))
/*306*/ MSG_TRANS(WM_CTLCOLORMSGBOX, 
	HBRUSH, CtlColorMessageBox, (HDC hdc, HWND hwndChild),
	ARGS(hdc, hwndChild), 
	SEND(HBRUSH, WM_CTLCOLORMSGBOX, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(CALL(CtlColorMessageBox))((HDC)(wParam), (HWND)(lParam)))
/*307*/ MSG_TRANS(WM_CTLCOLOREDIT, 
	HBRUSH, CtlColorEdit, (HDC hdc, HWND hwndChild),
	ARGS(hdc, hwndChild), 
	SEND(HBRUSH, WM_CTLCOLOREDIT, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(CALL(CtlColorEdit))((HDC)(wParam), (HWND)(lParam)))
/*308*/ MSG_TRANS(WM_CTLCOLORLISTBOX, 
	HBRUSH, CtlColorListBox, (HDC hdc, HWND hwndChild),
	ARGS(hdc, hwndChild), 
	SEND(HBRUSH, WM_CTLCOLORLISTBOX, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(CALL(CtlColorListBox))((HDC)(wParam), (HWND)(lParam)))
/*309*/ MSG_TRANS(WM_CTLCOLORBTN, 
	HBRUSH, CtlColorButton, (HDC hdc, HWND hwndChild),
	ARGS(hdc, hwndChild), 
	SEND(HBRUSH, WM_CTLCOLORBTN, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(CALL(CtlColorButton))((HDC)(wParam), (HWND)(lParam)))
/*310*/ MSG_TRANS(WM_CTLCOLORDLG, 
	HBRUSH, CtlColorDialog, (HDC hdc, HWND hwndChild),
	ARGS(hdc, hwndChild), 
	SEND(HBRUSH, WM_CTLCOLORDLG, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(CALL(CtlColorDialog))((HDC)(wParam), (HWND)(lParam)))
/*311*/ MSG_TRANS(WM_CTLCOLORSCROLLBAR, 
	HBRUSH, CtlColorScrollBar, (HDC hdc, HWND hwndChild),
	ARGS(hdc, hwndChild), 
	SEND(HBRUSH, WM_CTLCOLORSCROLLBAR, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(CALL(CtlColorScrollBar))((HDC)(wParam), (HWND)(lParam)))
/*312*/ MSG_TRANS(WM_CTLCOLORSTATIC, 
	HBRUSH, CtlColorStatic, (HDC hdc, HWND hwndChild),
	ARGS(hdc, hwndChild), 
	SEND(HBRUSH, WM_CTLCOLORSTATIC, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(CALL(CtlColorStatic))((HDC)(wParam), (HWND)(lParam)))
/*512*/ MSG_TRANS(WM_MOUSEMOVE, 
	void, MouseMove, (int x, int y, UINT keyFlags),
	ARGS(x, y, keyFlags), 
	SEND(void, WM_MOUSEMOVE, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((CALL(MouseMove))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*513*/ MSG_TRANS(WM_LBUTTONDOWN, 
	void, LButtonDown, (int x, int y, UINT keyFlags),
	ARGS(x, y, keyFlags),
	SEND(void, WM_LBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((CALL(LButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*514*/ MSG_TRANS(WM_LBUTTONUP, 
	void, LButtonUp, (int x, int y, UINT keyFlags),
	ARGS(x, y, keyFlags),
	SEND(void, WM_LBUTTONUP, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((CALL(LButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*515*/ MSG_TRANS(WM_LBUTTONDBLCLK, 
	void, LButtonClick, (int x, int y, UINT keyFlags),
	ARGS(x, y, keyFlags), 
	SEND(void, WM_LBUTTONDBLCLK, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((CALL(LButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*516*/ MSG_TRANS(WM_RBUTTONDOWN, 
	void, RButtonDown, (int x, int y, UINT keyFlags),
	ARGS(x, y, keyFlags),
	SEND(void, WM_RBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((CALL(RButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*517*/ MSG_TRANS(WM_RBUTTONUP, 
	void, RButtonUp, (int x, int y, UINT keyFlags),
	ARGS(x, y, keyFlags),
	SEND(void, WM_RBUTTONUP, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((CALL(RButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*518*/ MSG_TRANS(WM_RBUTTONDBLCLK, 
	void, RButtonClick, (int x, int y, UINT keyFlags),
	ARGS(x, y, keyFlags), 
	SEND(void, WM_RBUTTONDBLCLK, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((CALL(RButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*519*/ MSG_TRANS(WM_MBUTTONDOWN, 
	void, MButtonDown, (int x, int y, UINT keyFlags),
	ARGS(x, y, keyFlags),
	SEND(void, WM_MBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((CALL(MButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*520*/ MSG_TRANS(WM_MBUTTONUP, 
	void, MButtonUp, (int x, int y, UINT keyFlags),
	ARGS(x, y, keyFlags),
	SEND(void, WM_MBUTTONUP, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((CALL(MButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*521*/ MSG_TRANS(WM_MBUTTONDBLCLK, 
	void, MButtonClick, (int x, int y, UINT keyFlags),
	ARGS(x, y, keyFlags), 
	SEND(void, WM_MBUTTONDBLCLK, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((CALL(MButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*522*/ MSG_TRANS(WM_MOUSEWHEEL, 
	void, MouseWheel, (int xPos, int yPos, int zDelta, UINT fwKeys),
	ARGS(xPos, yPos, zDelta, fwKeys), 
	SEND(void, WM_MOUSEWHEEL, MAKEWPARAM((fwKeys), (zDelta)), MAKELPARAM((xPos), (yPos))), 
	((CALL(MouseWheel))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (int)(int16_t)HIWORD(wParam), (UINT)(int16_t)LOWORD(wParam)), 0L))
/*528*/ MSG_TRANS(WM_PARENTNOTIFY, 
	void, ParentNotify, (UINT msg, HWND hwndChild, int idChild),
	ARGS(msg, hwndChild, idChild), 
	SEND(void, WM_PARENTNOTIFY, MAKEWPARAM(msg, idChild), (LPARAM)(hwndChild)), 
	((CALL(ParentNotify))((UINT)LOWORD(wParam), (HWND)(lParam), (UINT)HIWORD(wParam)), 0L))
/*537*/ MSG_TRANS(WM_DEVICECHANGE, 
	bool, DeviceChange, (UINT uEvent, DWORD dwEventData),
	ARGS(uEvent, dwEventData), 
	SEND(bool, WM_DEVICECHANGE, (WPARAM)(UINT)(uEvent), (LPARAM)(DWORD)(dwEventData)), 
	(LRESULT)(DWORD)(bool)(CALL(DeviceChange))((UINT)(wParam), (DWORD)(lParam)))
/*544*/ MSG_TRANS(WM_MDICREATE, 
	HWND, MDICreate, (const LPMDICREATESTRUCT lpmcs),
	ARGS(lpmcs), 
	SEND(HWND, WM_MDICREATE, 0L, (LPARAM)(LPMDICREATESTRUCT)(lpmcs)), 
	(LRESULT)(DWORD)(UINT)(CALL(MDICreate))((LPMDICREATESTRUCT)(lParam)))
/*545*/ MSG_TRANS(WM_MDIDESTROY, 
	void, MDIDestroy, (HWND hwndDestroy),
	ARGS(hwndDestroy), 
	SEND(void, WM_MDIDESTROY, (WPARAM)(hwndDestroy), 0L), 
	((CALL(MDIDestroy))((HWND)(wParam)), 0L))
/*547*/ MSG_TRANS(WM_MDIRESTORE, 
	void, MDIRestore, (HWND hwndRestore),
	ARGS(hwndRestore), 
	SEND(void, WM_MDIRESTORE, (WPARAM)(hwndRestore), 0L), 
	((CALL(MDIRestore))((HWND)(wParam)), 0L))
/*548*/ MSG_TRANS(WM_MDINEXT, 
	HWND, MDINext, (HWND hwndCur, bool fPrev),
	ARGS(hwndCur, fPrev), 
	SEND(HWND, WM_MDINEXT, (WPARAM)(hwndCur), (LPARAM)(fPrev)), 
	(LRESULT)(HWND)(CALL(MDINext))((HWND)(wParam), (bool)lParam))
/*549*/ MSG_TRANS(WM_MDIMAXIMIZE, 
	void, MDIMaximize, (HWND hwndMaximize),
	ARGS(hwndMaximize), 
	SEND(void, WM_MDIMAXIMIZE, (WPARAM)(hwndMaximize), 0L), 
	((CALL(MDIMaximize))((HWND)(wParam)), 0L))
/*550*/ MSG_TRANS(WM_MDITILE, 
	bool, MDITile, (UINT cmd),
	ARGS(cmd), 
	SEND(bool, WM_MDITILE, (WPARAM)(cmd), 0L), 
	(LRESULT)(DWORD)(CALL(MDITile))((UINT)(wParam)))
/*551*/ MSG_TRANS(WM_MDICASCADE, 
	bool, MDICascade, (UINT cmd),
	ARGS(cmd), 
	SEND(bool, WM_MDICASCADE, (WPARAM)(cmd), 0L), 
	(LRESULT)(DWORD)(CALL(MDICascade))((UINT)(wParam)))
/*552*/ MSG_TRANS(WM_MDIICONARRANGE, 
	void, MDIIconArrange, (),
	ARGS(), 
	SEND(void, WM_MDIICONARRANGE, 0L, 0L), 
	((CALL(MDIIconArrange))(), 0L))
/*553*/ MSG_TRANS(WM_MDIGETACTIVE, 
	HWND, MDIGetActive, (),
	ARGS(), 
	SEND(HWND, WM_MDIGETACTIVE, 0L, 0L), 
	(LRESULT)(UINT_PTR)(CALL(MDIGetActive))())
/*560*/ MSG_TRANS(WM_MDISETMENU, 
	HMENU, MDISetMenu, (bool fRefresh, HMENU hmenuFrame, HMENU hmenuWindow),
	ARGS(fRefresh, hmenuFrame, hmenuWindow), 
	SEND(HMENU, WM_MDISETMENU, (WPARAM)((fRefresh) ? (hmenuFrame) : 0), (LPARAM)(hmenuWindow)), 
	(LRESULT)(UINT_PTR)(CALL(MDISetMenu))((bool)(wParam), (HMENU)(wParam), (HMENU)(lParam)))
/*563*/ MSG_TRANS(WM_DROPFILES, 
	void, DropFiles, (HDROP hdrop),
	ARGS(hdrop), 
	SEND(void, WM_DROPFILES, (WPARAM)(HDROP)(hdrop), 0L), 
	((CALL(DropFiles))((HDROP)(wParam)), 0L))
/*675*/ MSG_TRANS(WM_MOUSELEAVE,
	void, MouseLeave, (),
	ARGS(), 
	SEND(void, WM_MOUSELEAVE, 0L, 0L),
	((CALL(MouseLeave))(), 0L))
/*768*/ MSG_TRANS(WM_CUT, 
	void, Cut, (),
	ARGS(), 
	SEND(void, WM_CUT, 0L, 0L), 
	((CALL(Cut))(), 0L))
/*769*/ MSG_TRANS(WM_COPY, 
	void, Copy, (),
	ARGS(), 
	SEND(void, WM_COPY, 0L, 0L), 
	((CALL(Copy))(), 0L))
/*770*/ MSG_TRANS(WM_PASTE, 
	void, Paste, (),
	ARGS(), 
	SEND(void, WM_PASTE, 0L, 0L), 
	((CALL(Paste))(), 0L))
/*771*/ MSG_TRANS(WM_CLEAR, 
	void, Clear, (),
	ARGS(), 
	SEND(void, WM_CLEAR, 0L, 0L), 
	((CALL(Clear))(), 0L))
/*772*/ MSG_TRANS(WM_UNDO, 
	void, Undo, (),
	ARGS(), 
	SEND(void, WM_UNDO, 0L, 0L), 
	((CALL(Undo))(), 0L))
/*773*/ MSG_TRANS(WM_RENDERFORMAT, 
	HANDLE, RenderFormat, (UINT fmt),
	ARGS(fmt), 
	SEND(HANDLE, WM_RENDERFORMAT, (WPARAM)(UINT)(fmt), 0L), 
	(LRESULT)(UINT_PTR)(HANDLE)(CALL(RenderFormat))((UINT)(wParam)))
/*774*/ MSG_TRANS(WM_RENDERALLFORMATS, 
	void, RenderAllFormats, (),
	ARGS(), 
	SEND(void, WM_RENDERALLFORMATS, 0L, 0L), 
	((CALL(RenderAllFormats))(), 0L))
/*775*/ MSG_TRANS(WM_DESTROYCLIPBOARD, 
	void, DestroyClipboard, (),
	ARGS(), 
	SEND(void, WM_DESTROYCLIPBOARD, 0L, 0L), 
	((CALL(DestroyClipboard))(), 0L))
/*776*/ MSG_TRANS(WM_DRAWCLIPBOARD, 
	void, DrawClipboard, (),
	ARGS(), 
	SEND(void, WM_DRAWCLIPBOARD, 0L, 0L), 
	((CALL(DrawClipboard))(), 0L))
/*777*/ MSG_TRANS(WM_PAINTCLIPBOARD, 
	void, PaintClipboard, (HWND hwndCBViewer, const LPPAINTSTRUCT lpPaintStruct),
	ARGS(hwndCBViewer, lpPaintStruct), 
	SEND(void, WM_PAINTCLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), (LPARAM)(LPPAINTSTRUCT)(lpPaintStruct)), 
	((CALL(PaintClipboard))((HWND)(wParam), (const LPPAINTSTRUCT)GlobalLock((HGLOBAL)(lParam))), GlobalUnlock((HGLOBAL)(lParam)), 0L))
/*778*/ MSG_TRANS(WM_VSCROLLCLIPBOARD, 
	void, VScrollClipboard, (HWND hwndCBViewer, UINT code, int pos),
	ARGS(hwndCBViewer, code, pos), 
	SEND(void, WM_VSCROLLCLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), MAKELPARAM((code), (pos))), 
	((CALL(VScrollClipboard))((HWND)(wParam), (UINT)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*779*/ MSG_TRANS(WM_SIZECLIPBOARD, 
	void, SizeClipboard, (HWND hwndCBViewer, const LPRECT lprc),
	ARGS(hwndCBViewer, lprc), 
	SEND(void, WM_SIZECLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), (LPARAM)(LPRECT)(lprc)), 
	((CALL(SizeClipboard))((HWND)(wParam), (const LPRECT)GlobalLock((HGLOBAL)(lParam))), GlobalUnlock((HGLOBAL)(lParam)), 0L))
/*780*/ MSG_TRANS(WM_ASKCBFORMATNAME, 
	void, AskCBFormatName, (int cchMax, LPTSTR rgchName),
	ARGS(cchMax, rgchName), 
	SEND(void, WM_ASKCBFORMATNAME, (WPARAM)(int)(cchMax), (LPARAM)(rgchName)), 
	((CALL(AskCBFormatName))((int)(wParam), (LPTSTR)(lParam)), 0L))
/*781*/ MSG_TRANS(WM_CHANGECBCHAIN, 
	void, ChangeCBChain, (HWND hwndRemove, HWND hwndNext),
	ARGS(hwndRemove, hwndNext), 
	SEND(void, WM_CHANGECBCHAIN, (WPARAM)(HWND)(hwndRemove), (LPARAM)(HWND)(hwndNext)), 
	((CALL(ChangeCBChain))((HWND)(wParam), (HWND)(lParam)), 0L))
/*782*/ MSG_TRANS(WM_HSCROLLCLIPBOARD, 
	void, HScrollClipboard, (HWND hwndCBViewer, UINT code, int pos),
	ARGS(hwndCBViewer, code, pos), 
	SEND(void, WM_HSCROLLCLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), MAKELPARAM((code), (pos))), 
	((CALL(HScrollClipboard))((HWND)(wParam), (UINT)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*783*/ MSG_TRANS(WM_QUERYNEWPALETTE, 
	bool, QueryNewPalette, (),
	ARGS(), 
	SEND(bool, WM_QUERYNEWPALETTE, 0L, 0L), 
	MAKELRESULT((bool)(CALL(QueryNewPalette))(), 0L))
/*784*/ MSG_TRANS(WM_PALETTEISCHANGING, 
	void, PaletteIsChanging, (HWND hwndPaletteChange),
	ARGS(hwndPaletteChange), 
	SEND(void, WM_PALETTEISCHANGING, (WPARAM)(HWND)(hwndPaletteChange), 0L), 
	((CALL(PaletteIsChanging))((HWND)(wParam)), 0L))
/*785*/ MSG_TRANS(WM_PALETTECHANGED, 
	void, PaletteChanged, (HWND hwndPaletteChange),
	ARGS(hwndPaletteChange), 
	SEND(void, WM_PALETTECHANGED, (WPARAM)(HWND)(hwndPaletteChange), 0L), 
	((CALL(PaletteChanged))((HWND)(wParam)), 0L))
/*786*/ MSG_TRANS(WM_HOTKEY, 
	void, HotKey, (int idHotKey, UINT fuModifiers, UINT vk),
	ARGS(idHotKey, fuModifiers, vk), 
	SEND(void, WM_HOTKEY, (WPARAM)(idHotKey), MAKELPARAM((fuModifiers), (vk))), 
	((CALL(HotKey))((int)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L))

#undef MSG_TRANS
#undef CALL
#undef SEND
