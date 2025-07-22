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
	ret, name, argslist, args, \
	send, \
	call)
#endif
#ifndef _CALL_
#	define _CALL_(name)
#endif
#ifndef _SEND_
#	define _SEND_(ret, msgid, wparam, lparam)
#endif

/*1*/ MSG_TRANS(WM_CREATE, 
	bool, Create, (LPCREATESTRUCT lpCreateStruct), (lpCreateStruct), 
	_SEND_((bool)(DWORD), WM_CREATE, 0L, (LPARAM)(LPCREATESTRUCT)(lpCreateStruct)), 
	((_CALL_(Create))((LPCREATESTRUCT)(lParam)) ? 0L : (LRESULT)-1L))
/*2*/ MSG_TRANS(WM_DESTROY, 
	void, Destroy, (), (), 
	_SEND_((void), WM_DESTROY, 0L, 0L), 
	((_CALL_(Destroy))(), 0L))
/*3*/ MSG_TRANS(WM_MOVE, 
	void, Move, (int x, int y), (x, y), 
	_SEND_((void), WM_MOVE, 0L, MAKELPARAM((x), (y))), 
	((_CALL_(Move))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*5*/ MSG_TRANS(WM_SIZE, 
	void, Size, (UINT state, int cx, int cy), (state, cx, cy), 
	_SEND_((void), WM_SIZE, (WPARAM)(UINT)(state), MAKELPARAM((cx), (cy))), 
	((_CALL_(Size))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*6*/ MSG_TRANS(WM_ACTIVATE, 
	void, Activate, (UINT state, HWND hwndActDeact, bool fMinimized), (state, hwndActDeact, fMinimized), 
	_SEND_((void), WM_ACTIVATE, MAKEWPARAM((state), (fMinimized)), (LPARAM)(HWND)(hwndActDeact)), 
	((_CALL_(Activate))((UINT)LOWORD(wParam), (HWND)(lParam), (bool)HIWORD(wParam)), 0L))
/*7*/ MSG_TRANS(WM_SETFOCUS, 
	void, SetFocus, (HWND hwndOldFocus), (hwndOldFocus), 
	_SEND_((void), WM_SETFOCUS, (WPARAM)(HWND)(hwndOldFocus), 0L), 
	((_CALL_(SetFocus))((HWND)(wParam)), 0L))
/*8*/ MSG_TRANS(WM_KILLFOCUS, 
	void, KillFocus, (HWND hwndNewFocus), (hwndNewFocus), 
	_SEND_((void), WM_KILLFOCUS, (WPARAM)(HWND)(hwndNewFocus), 0L), 
	((_CALL_(KillFocus))((HWND)(wParam)), 0L))
/*10*/ MSG_TRANS(WM_ENABLE, 
	void, Enable, (bool fEnable), (fEnable), 
	_SEND_((void), WM_ENABLE, (WPARAM)(bool)(fEnable), 0L), 
	((_CALL_(Enable))((bool)(wParam)), 0L))
/*11*/ MSG_TRANS(WM_SETREDRAW, 
	void, SetRedraw, (bool fRedraw), (fRedraw), 
	_SEND_((void), WM_SETREDRAW, (WPARAM)(bool)(fRedraw), 0L), 
	((_CALL_(SetRedraw))((bool)(wParam)), 0L))
/*12*/ MSG_TRANS(WM_SETTEXT, 
	void, SetText, (LPCTSTR lpszText), (lpszText), 
	_SEND_((void), WM_SETTEXT, 0L, (LPARAM)(LPCTSTR)(lpszText)), 
	((_CALL_(SetText))((LPCTSTR)(lParam)), 0L))
/*13*/ MSG_TRANS(WM_GETTEXT, 
	INT, GetText, (int cchTextMax, LPTSTR lpszText), (cchTextMax, lpszText), 
	_SEND_((int)(DWORD), WM_GETTEXT, (WPARAM)(int)(cchTextMax), (LPARAM)(LPTSTR)(lpszText)), 
	(LRESULT)(DWORD)(int)(_CALL_(GetText))((int)(wParam), (LPTSTR)(lParam)))
/*14*/ MSG_TRANS(WM_GETTEXTLENGTH, 
	INT, GetTextLength, (), (), 
	_SEND_((int)(DWORD), WM_GETTEXTLENGTH, 0L, 0L), 
	(LRESULT)(DWORD)(int)(_CALL_(GetTextLength))())
/*15*/ MSG_TRANS(WM_PAINT, 
	void, Paint, (), (), 
	_SEND_((void), WM_PAINT, 0L, 0L), 
	((_CALL_(Paint))(), 0L))
/*16*/ MSG_TRANS(WM_CLOSE, 
	void, Close, (), (), 
	_SEND_((void), WM_CLOSE, 0L, 0L), 
	((_CALL_(Close))(), 0L))
/*17*/ MSG_TRANS(WM_QUERYENDSESSION, 
	bool, QueryEndSession, (), (), 
	_SEND_((bool)(DWORD), WM_QUERYENDSESSION, 0L, 0L), 
	MAKELRESULT((bool)(_CALL_(QueryEndSession))(), 0L))
/*18*/ MSG_TRANS(WM_QUIT, 
	void, Quit, (int exitCode), (exitCode), 
	_SEND_((void), WM_QUIT, (WPARAM)(exitCode), 0L), 
	((_CALL_(Quit))((int)(wParam)), 0L))
/*19*/ MSG_TRANS(WM_QUERYOPEN, 
	bool, QueryOpen, (), (), 
	_SEND_((bool)(DWORD), WM_QUERYOPEN, 0L, 0L), 
	MAKELRESULT((bool)(_CALL_(QueryOpen))(), 0L))
/*20*/ MSG_TRANS(WM_ERASEBKGND, 
	bool, EraseBkgnd, (HDC hdc), (hdc), 
	_SEND_((bool)(DWORD), WM_ERASEBKGND, (WPARAM)(HDC)(hdc), 0L), 
	(LRESULT)(DWORD)(bool)(_CALL_(EraseBkgnd))((HDC)(wParam)))
/*21*/ MSG_TRANS(WM_SYSCOLORCHANGE, 
	void, SysColorChange, (), (), 
	_SEND_((void), WM_SYSCOLORCHANGE, 0L, 0L), 
	((_CALL_(SysColorChange))(), 0L))
/*22*/ MSG_TRANS(WM_ENDSESSION, 
	void, EndSession, (bool fEnding), (fEnding), 
	_SEND_((void), WM_ENDSESSION, (WPARAM)(bool)(fEnding), 0L), 
	((_CALL_(EndSession))((bool)(wParam)), 0L))
/*24*/ MSG_TRANS(WM_SHOWWINDOW, 
	void, ShowWindow, (bool fShow, UINT status), (fShow, status), 
	_SEND_((void), WM_SHOWWINDOW, (WPARAM)(bool)(fShow), (LPARAM)(UINT)(status)), 
	((_CALL_(ShowWindow))((bool)(wParam), (UINT)(lParam)), 0L))
/*26*/ MSG_TRANS(WM_WININICHANGE, 
	void, WinIniChange, (LPCTSTR lpszSectionName), (lpszSectionName), 
	_SEND_((void), WM_WININICHANGE, 0L, (LPARAM)(LPCTSTR)(lpszSectionName)), 
	((_CALL_(WinIniChange))((LPCTSTR)(lParam)), 0L))
/*27*/ MSG_TRANS(WM_DEVMODECHANGE, 
	void, DevModeChange, (LPCTSTR lpszDeviceName), (lpszDeviceName), 
	_SEND_((void), WM_DEVMODECHANGE, 0L, (LPARAM)(LPCTSTR)(lpszDeviceName)), 
	((_CALL_(DevModeChange))((LPCTSTR)(lParam)), 0L))
/*28*/ MSG_TRANS(WM_ACTIVATEAPP, 
	void, ActivateApp, (bool fActivate, DWORD dwThreadId), (fActivate, dwThreadId), 
	_SEND_((void), WM_ACTIVATEAPP, (WPARAM)(bool)(fActivate), (LPARAM)(dwThreadId)), 
	((_CALL_(ActivateApp))((bool)(wParam), (DWORD)(lParam)), 0L))
/*29*/ MSG_TRANS(WM_FONTCHANGE, 
	void, FontChange, (), (), 
	_SEND_((void), WM_FONTCHANGE, 0L, 0L), 
	((_CALL_(FontChange))(), 0L))
/*30*/ MSG_TRANS(WM_TIMECHANGE, 
	void, TimeChange, (), (), 
	_SEND_((void), WM_TIMECHANGE, 0L, 0L), 
	((_CALL_(TimeChange))(), 0L))
/*31*/ MSG_TRANS(WM_CANCELMODE, 
	void, CancelMode, (), (), 
	_SEND_((void), WM_CANCELMODE, 0L, 0L), 
	((_CALL_(CancelMode))(), 0L))
/*32*/ MSG_TRANS(WM_SETCURSOR, 
	bool, SetCursor, (HWND hwndCursor, UINT codeHitTest, UINT msg), (hwndCursor, codeHitTest, msg), 
	_SEND_((bool)(DWORD), WM_SETCURSOR, (WPARAM)(HWND)(hwndCursor), MAKELPARAM((codeHitTest), (msg))), 
	(LRESULT)(DWORD)(bool)(_CALL_(SetCursor))((HWND)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)))
/*33*/ MSG_TRANS(WM_MOUSEACTIVATE, 
	int, MouseActivate, (HWND hwndTopLevel, UINT codeHitTest, UINT msg), (hwndTopLevel, codeHitTest, msg), 
	_SEND_((int)(DWORD), WM_MOUSEACTIVATE, (WPARAM)(HWND)(hwndTopLevel), MAKELPARAM((codeHitTest), (msg))), 
	(LRESULT)(DWORD)(int)(_CALL_(MouseActivate))((HWND)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)))
/*34*/ MSG_TRANS(WM_CHILDACTIVATE, 
	void, ChildActivate, (), (), 
	_SEND_((void), WM_CHILDACTIVATE, 0L, 0L), 
	((_CALL_(ChildActivate))(), 0L))
/*35*/ MSG_TRANS(WM_QUEUESYNC, 
	void, QueueSync, (), (), 
	_SEND_((void), WM_QUEUESYNC, 0L, 0L), 
	((_CALL_(QueueSync))(), 0L))
/*36*/ MSG_TRANS(WM_GETMINMAXINFO, 
	void, GetMinMaxInfo, (LPMINMAXINFO lpMinMaxInfo), (lpMinMaxInfo), 
	_SEND_((void), WM_GETMINMAXINFO, 0L, (LPARAM)(LPMINMAXINFO)(lpMinMaxInfo)), 
	((_CALL_(GetMinMaxInfo))((LPMINMAXINFO)(lParam)), 0L))
/*39*/ MSG_TRANS(WM_ICONERASEBKGND, 
	bool, IconEraseBkgnd, (HDC hdc), (hdc), 
	_SEND_((bool)(DWORD), WM_ICONERASEBKGND, (WPARAM)(HDC)(hdc), 0L), 
	(LRESULT)(DWORD)(bool)(_CALL_(IconEraseBkgnd))((HDC)(wParam)))
/*40*/ MSG_TRANS(WM_NEXTDLGCTL, 
	HWND, NextDlgCtl, (HWND hwndSetFocus, bool fNext), (hwndSetFocus, fNext), 
	_SEND_((HWND)(UINT_PTR), WM_NEXTDLGCTL, (WPARAM)(HWND)(hwndSetFocus), (LPARAM)(fNext)), 
	(LRESULT)(UINT_PTR)(HWND)(_CALL_(NextDlgCtl))((HWND)(wParam), (bool)(lParam)))
/*42*/ MSG_TRANS(WM_SPOOLERSTATUS, 
	void, SpoolerStatus, (UINT status, int cJobInQueue), (status, cJobInQueue), 
	_SEND_((void), WM_SPOOLERSTATUS, (WPARAM)(status), MAKELPARAM((cJobInQueue), 0)), 
	((_CALL_(SpoolerStatus))((UINT)(wParam), (int)(int16_t)LOWORD(lParam)), 0L))
/*43*/ MSG_TRANS(WM_DRAWITEM, 
	void, DrawItem, (const DRAWITEMSTRUCT * lpDrawItem), (lpDrawItem), 
	_SEND_((void), WM_DRAWITEM, (WPARAM)(((const DRAWITEMSTRUCT *)lpDrawItem)->CtlID), (LPARAM)(const DRAWITEMSTRUCT *)(lpDrawItem)), 
	((_CALL_(DrawItem))((const DRAWITEMSTRUCT *)(lParam)), 0L))
/*44*/ MSG_TRANS(WM_MEASUREITEM, 
	void, MeasureItem, (MEASUREITEMSTRUCT * lpMeasureItem), (lpMeasureItem), 
	_SEND_((void), WM_MEASUREITEM, (WPARAM)(((MEASUREITEMSTRUCT *)lpMeasureItem)->CtlID), (LPARAM)(MEASUREITEMSTRUCT *)(lpMeasureItem)), 
	((_CALL_(MeasureItem))((MEASUREITEMSTRUCT *)(lParam)), 0L))
/*45*/ MSG_TRANS(WM_DELETEITEM, 
	void, DeleteItem, (const DELETEITEMSTRUCT * lpDeleteItem), (lpDeleteItem), 
	_SEND_((void), WM_DELETEITEM, (WPARAM)(((const DELETEITEMSTRUCT *)(lpDeleteItem))->CtlID), (LPARAM)(const DELETEITEMSTRUCT *)(lpDeleteItem)), 
	((_CALL_(DeleteItem))((const DELETEITEMSTRUCT *)(lParam)), 0L))
/*46*/ MSG_TRANS(WM_VKEYTOITEM, 
	int, VkeyToItem, (UINT vk, HWND hwndListBox, int iCaret), (vk, hwndListBox, iCaret), 
	_SEND_((int)(DWORD), WM_VKEYTOITEM, MAKEWPARAM((vk), (iCaret)), (LPARAM)(hwndListBox)), 
	(LRESULT)(DWORD)(int)(_CALL_(VkeyToItem))((UINT)LOWORD(wParam), (HWND)(lParam), (int)(int16_t)HIWORD(wParam)))
/*47*/ MSG_TRANS(WM_CHARTOITEM, 
	int, CharToItem, (UINT ch, HWND hwndListBox, int iCaret), (ch, hwndListBox, iCaret), 
	_SEND_((int)(DWORD), WM_CHARTOITEM, MAKEWPARAM((UINT)(ch), (UINT)(iCaret)), (LPARAM)(hwndListBox)), 
	(LRESULT)(DWORD)(int)(_CALL_(CharToItem))((UINT)LOWORD(wParam), (HWND)(lParam), (int)(int16_t)HIWORD(wParam)))
/*48*/ MSG_TRANS(WM_SETFONT, 
	void, SetFont, (HFONT hfont, bool fRedraw), (hfont, fRedraw), 
	_SEND_((void), WM_SETFONT, (WPARAM)(HFONT)(hfont), (LPARAM)(bool)(fRedraw)), 
	((_CALL_(SetFont))((HFONT)(wParam), (bool)(lParam)), 0L))
/*49*/ MSG_TRANS(WM_GETFONT, 
	HFONT, GetFont, (), (), 
	_SEND_((HFONT)(UINT_PTR), WM_GETFONT, 0L, 0L), 
	(LRESULT)(UINT_PTR)(HFONT)(_CALL_(GetFont))())
/*55*/ MSG_TRANS(WM_QUERYDRAGICON, 
	HICON, QueryDragIcon, (), (), 
	_SEND_((HICON), WM_QUERYDRAGICON, 0L, 0L), 
	(LRESULT)(DWORD)(UINT)(_CALL_(QueryDragIcon))())
/*57*/ MSG_TRANS(WM_COMPAREITEM, 
	int, CompareItem, (const COMPAREITEMSTRUCT * lpCompareItem), (lpCompareItem), 
	_SEND_((int)(DWORD), WM_COMPAREITEM, (WPARAM)(((const COMPAREITEMSTRUCT *)(lpCompareItem))->CtlID), (LPARAM)(const COMPAREITEMSTRUCT *)(lpCompareItem)), 
	(LRESULT)(DWORD)(int)(_CALL_(CompareItem))((const COMPAREITEMSTRUCT *)(lParam)))
/*65*/ MSG_TRANS(WM_COMPACTING, 
	void, Compacting, (UINT compactRatio), (compactRatio), 
	_SEND_((void), WM_COMPACTING, (WPARAM)(UINT)(compactRatio), 0L), 
	((_CALL_(Compacting))((UINT)(wParam)), 0L))
/*68*/ MSG_TRANS(WM_COMMNOTIFY, 
	void, CommNotify, (int cid, UINT flags), (cid, flags), 
	_SEND_((void), WM_COMMNOTIFY, (WPARAM)(cid), MAKELPARAM((flags), 0)), 
	((_CALL_(CommNotify))((int)(wParam), (UINT)LOWORD(lParam)), 0L))
/*70*/ MSG_TRANS(WM_WINDOWPOSCHANGING, 
	bool, WindowPosChanging, (LPWINDOWPOS lpwpos), (lpwpos), 
	_SEND_((bool)(DWORD), WM_WINDOWPOSCHANGING, 0L, (LPARAM)(LPWINDOWPOS)(lpwpos)), 
	(LRESULT)(DWORD)(bool)(_CALL_(WindowPosChanging))((LPWINDOWPOS)(lParam)))
/*71*/ MSG_TRANS(WM_WINDOWPOSCHANGED, 
	void, WindowPosChanged, (const WINDOWPOS *lpwpos), (lpwpos), 
	_SEND_((void), WM_WINDOWPOSCHANGED, 0L, (LPARAM)(const WINDOWPOS *)(lpwpos)), 
	((_CALL_(WindowPosChanged))((const WINDOWPOS *)(lParam)), 0L))
/*72*/ MSG_TRANS(WM_POWER, 
	void, Power, (int code), (code), 
	_SEND_((void), WM_POWER, (WPARAM)(int)(code), 0L), 
	((_CALL_(Power))((int)(wParam)), 0L))
/*74*/ MSG_TRANS(WM_COPYDATA, 
	bool, CopyData, (HWND hwndFrom, PCOPYDATASTRUCT pcds), (hwndFrom, pcds), 
	_SEND_((bool)(UINT)(DWORD), WM_COPYDATA, (WPARAM)(hwndFrom), (LPARAM)(pcds)), 
	((_CALL_(CopyData))((HWND)(wParam), (PCOPYDATASTRUCT)lParam), 0L))
/*123*/ MSG_TRANS(WM_CONTEXTMENU, 
	void, ContextMenu, (HWND hwndContext, UINT xPos, UINT yPos), (hwndContext, xPos, yPos), 
	_SEND_((void), WM_CONTEXTMENU, (WPARAM)(HWND)(hwndContext), MAKELPARAM((UINT)(xPos), (UINT)(yPos))), 
	((_CALL_(ContextMenu))((HWND)(wParam), (int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*126*/ MSG_TRANS(WM_DISPLAYCHANGE, 
	void, DisplayChange, (UINT bitsPerPixel, UINT cxScreen, UINT cyScreen), (bitsPerPixel, cxScreen, cyScreen), 
	_SEND_((void), WM_DISPLAYCHANGE, (WPARAM)(UINT)(bitsPerPixel), (LPARAM)MAKELPARAM((UINT)(cxScreen), (UINT)(cyScreen))), 
	((_CALL_(DisplayChange))((UINT)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L))
/*129*/ MSG_TRANS(WM_NCCREATE, 
	bool, NCCreate, (LPCREATESTRUCT lpCreateStruct), (lpCreateStruct), 
	_SEND_((bool)(DWORD), WM_NCCREATE, 0L, (LPARAM)(LPCREATESTRUCT)(lpCreateStruct)), 
	(LRESULT)(DWORD)(bool)(_CALL_(NCCreate))((LPCREATESTRUCT)(lParam)))
/*130*/ MSG_TRANS(WM_NCDESTROY, 
	void, NCDestroy, (), (), 
	_SEND_((void), WM_NCDESTROY, 0L, 0L), 
	((_CALL_(NCDestroy))(), 0L))
/*131*/ MSG_TRANS(WM_NCCALCSIZE, 
	UINT, NCCalcSize, (bool fCalcValidRects, NCCALCSIZE_PARAMS * lpcsp), (fCalcValidRects, lpcsp), 
	_SEND_((UINT)(DWORD), WM_NCCALCSIZE, (WPARAM)(fCalcValidRects), (LPARAM)(NCCALCSIZE_PARAMS *)(lpcsp)), 
	(LRESULT)(DWORD)(UINT)(_CALL_(NCCalcSize))((bool)(wParam), (NCCALCSIZE_PARAMS *)(lParam)))
/*132*/ MSG_TRANS(WM_NCHITTEST, 
	UINT, NCHitTest, (int x, int y), (x, y), 
	_SEND_((UINT)(DWORD), WM_NCHITTEST, 0L, MAKELPARAM((x), (y))), 
	(LRESULT)(DWORD)(UINT)(_CALL_(NCHitTest))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)))
/*133*/ MSG_TRANS(WM_NCPAINT, 
	void, NCPaint, (HRGN hrgn), (hrgn), 
	_SEND_((void), WM_NCPAINT, (WPARAM)(HRGN)(hrgn), 0L), 
	((_CALL_(NCPaint))((HRGN)(wParam)), 0L))
/*134*/ MSG_TRANS(WM_NCACTIVATE, 
	bool, NCActivate, (bool fActive, HWND hwndActDeact, bool fMinimized), (fActive, hwndActDeact, fMinimized), 
	_SEND_((bool)(DWORD), WM_NCACTIVATE, (WPARAM)(bool)(fActive), 0L), 
	(LRESULT)(DWORD)(bool)(_CALL_(NCActivate))((bool)(wParam), 0L, 0L))
/*135*/ MSG_TRANS(WM_GETDLGCODE, 
	UINT, GetDlgCode, (LPMSG lpmsg), (lpmsg), 
	_SEND_((UINT)(DWORD), WM_GETDLGCODE, (lpmsg ? lpmsg->wParam : 0), (LPARAM)(LPMSG)(lpmsg)), 
	(LRESULT)(DWORD)(UINT)(_CALL_(GetDlgCode))((LPMSG)(lParam)))
/*160*/ MSG_TRANS(WM_NCMOUSEMOVE, 
	void, NCMouseMove, (int x, int y, UINT codeHitTest), (x, y, codeHitTest), 
	_SEND_((void), WM_NCMOUSEMOVE, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y))), 
	((_CALL_(NCMouseMove))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*161*/ MSG_TRANS(WM_NCLBUTTONDOWN, 
	void, NCLButtonDown, (int x, int y, UINT codeHitTest), (x, y, codeHitTest), 
	_SEND_((void), WM_NCLBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y))), 
	((_CALL_(NCLButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*162*/ MSG_TRANS(WM_NCLBUTTONUP, 
	void, NCLButtonUp, (int x, int y, UINT codeHitTest), (x, y, codeHitTest),
	_SEND_((void), WM_NCLBUTTONUP, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y))), 
	((_CALL_(NCLButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*163*/ MSG_TRANS(WM_NCLBUTTONDBLCLK, 
	void, NCLButtonClick, (int x, int y, UINT codeHitTest), (x, y, codeHitTest), 
	_SEND_((void), WM_NCLBUTTONDBLCLK, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y))), 
	((_CALL_(NCLButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*164*/ MSG_TRANS(WM_NCRBUTTONDOWN, 
	void, NCRButtonDown, (int x, int y, UINT codeHitTest), (x, y, codeHitTest),
	_SEND_((void), WM_NCRBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((_CALL_(NCRButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*165*/ MSG_TRANS(WM_NCRBUTTONUP, 
	void, NCRButtonUp, (int x, int y, UINT codeHitTest), (x, y, codeHitTest),
	_SEND_((void), WM_NCRBUTTONUP, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((_CALL_(NCRButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*166*/ MSG_TRANS(WM_NCRBUTTONDBLCLK, 
	void, NCRButtonClick, (int x, int y, UINT codeHitTest), (x, y, codeHitTest), 
	_SEND_((void), WM_NCRBUTTONDBLCLK, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((_CALL_(NCRButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*167*/ MSG_TRANS(WM_NCMBUTTONDOWN, 
	void, NCMButtonDown, (int x, int y, UINT codeHitTest), (x, y, codeHitTest),
	_SEND_((void), WM_NCMBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((_CALL_(NCMButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*168*/ MSG_TRANS(WM_NCMBUTTONUP, 
	void, NCMButtonUp, (int x, int y, UINT codeHitTest), (x, y, codeHitTest),
	_SEND_((void), WM_NCMBUTTONUP, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((_CALL_(NCMButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*169*/ MSG_TRANS(WM_NCMBUTTONDBLCLK, 
	void, NCMButtonClick, (int x, int y, UINT codeHitTest), (x, y, codeHitTest), 
	_SEND_((void), WM_NCMBUTTONDBLCLK, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((_CALL_(NCMButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*256*/ MSG_TRANS(WM_KEYDOWN, 
	void, KeyDown, (UINT vk, int16_t wRepeat, KEY_FLAGS flags), (vk, wRepeat, flags),
	_SEND_((void), WM_KEYDOWN, (WPARAM)(UINT)(vk), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))), 
	((_CALL_(KeyDown))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*257*/ MSG_TRANS(WM_KEYUP, 
	void, KeyUp, (UINT vk, int16_t wRepeat, KEY_FLAGS flags), (vk, wRepeat, flags),
	_SEND_((void), WM_KEYUP, (WPARAM)(UINT)(vk), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))), 
	((_CALL_(KeyUp))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*258*/ MSG_TRANS(WM_CHAR, 
	void, Char, (TCHAR ch, int16_t wRepeat, KEY_FLAGS flags), (ch, wRepeat, flags),
	_SEND_((void), WM_CHAR, (WPARAM)(UINT)(ch), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))),
	((_CALL_(Char))((TCHAR)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*259*/ MSG_TRANS(WM_DEADCHAR, 
	void, DeadChar, (TCHAR ch, int16_t wRepeat, KEY_FLAGS flags), (ch, wRepeat, flags),
	_SEND_((void), WM_DEADCHAR, (WPARAM)(UINT)(ch), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))),
	((_CALL_(DeadChar))((TCHAR)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*260*/ MSG_TRANS(WM_SYSKEYDOWN, 
	void, SysKeyDown, (UINT vk, int16_t wRepeat, KEY_FLAGS flags), (vk, wRepeat, flags),
	_SEND_((void), WM_SYSKEYDOWN, (WPARAM)(UINT)(vk), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))), 
	((_CALL_(SysKeyDown))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*261*/ MSG_TRANS(WM_SYSKEYUP, 
	void, SysKeyUp, (UINT vk, int16_t wRepeat, KEY_FLAGS flags), (vk, wRepeat, flags),
	_SEND_((void), WM_SYSKEYUP, (WPARAM)(UINT)(vk), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))), 
	((_CALL_(SysKeyUp))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*262*/ MSG_TRANS(WM_SYSCHAR, 
	void, SysChar, (TCHAR ch, int16_t wRepeat, KEY_FLAGS flags), (ch, wRepeat, flags),
	_SEND_((void), WM_SYSCHAR, (WPARAM)(UINT)(ch), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))),
	((_CALL_(SysChar))((TCHAR)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*263*/ MSG_TRANS(WM_SYSDEADCHAR, 
	void, SysDeadChar, (TCHAR ch, int16_t wRepeat, KEY_FLAGS flags), (ch, wRepeat, flags),
	_SEND_((void), WM_SYSDEADCHAR, (WPARAM)(UINT)(ch), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))),
	((_CALL_(SysDeadChar))((TCHAR)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*272*/ MSG_TRANS(WM_INITDIALOG, 
	bool, InitDialog, (HWND hwndFocus, LPARAM lParam), (hwndFocus, lParam), 
	_SEND_((bool)(DWORD), WM_INITDIALOG, (WPARAM)(HWND)(hwndFocus), (lParam)), 
	(LRESULT)(DWORD)(UINT)(bool)(_CALL_(InitDialog))((HWND)(wParam), lParam))
/*273*/ MSG_TRANS(WM_COMMAND, 
	void, Command, (int id, HWND hwndCtl, UINT codeNotify), (id, hwndCtl, codeNotify), 
	_SEND_((void), WM_COMMAND, MAKEWPARAM((UINT)(id), (UINT)(codeNotify)), (LPARAM)(HWND)(hwndCtl)), 
	((_CALL_(Command))((int)(LOWORD(wParam)), (HWND)(lParam), (UINT)HIWORD(wParam)), 0L))
/*274*/ MSG_TRANS(WM_SYSCOMMAND, 
	void, SysCommand, (UINT cmd, int x, int y), (cmd, x, y), 
	_SEND_((void), WM_SYSCOMMAND, (WPARAM)(UINT)(cmd), MAKELPARAM((x), (y))), 
	((_CALL_(SysCommand))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*275*/ MSG_TRANS(WM_TIMER, 
	void, Timer, (UINT id), (id), 
	_SEND_((void), WM_TIMER, (WPARAM)(UINT)(id), 0L), 
	((_CALL_(Timer))((UINT)(wParam)), 0L))
/*276*/ MSG_TRANS(WM_HSCROLL, 
	void, HScroll, (HWND hwndCtl, UINT code, int pos), (hwndCtl, code, pos), 
	_SEND_((void), WM_HSCROLL, MAKEWPARAM((UINT)(int)(code), (UINT)(int)(pos)), (LPARAM)(HWND)(hwndCtl)), 
	((_CALL_(HScroll))((HWND)(lParam), (UINT)(LOWORD(wParam)), (int)(int16_t)HIWORD(wParam)), 0L))
/*277*/ MSG_TRANS(WM_VSCROLL, 
	void, VScroll, (HWND hwndCtl, UINT code, int pos), (hwndCtl, code, pos), 
	_SEND_((void), WM_VSCROLL, MAKEWPARAM((UINT)(int)(code), (UINT)(int)(pos)), (LPARAM)(HWND)(hwndCtl)), 
	((_CALL_(VScroll))((HWND)(lParam), (UINT)(LOWORD(wParam)), (int)(int16_t)HIWORD(wParam)), 0L))
/*278*/ MSG_TRANS(WM_INITMENU, 
	void, InitMenu, (HMENU hMenu), (hMenu), 
	_SEND_((void), WM_INITMENU, (WPARAM)(HMENU)(hMenu), 0L), 
	((_CALL_(InitMenu))((HMENU)(wParam)), 0L))
/*279*/ MSG_TRANS(WM_INITMENUPOPUP, 
	void, InitMenuPopup, (HMENU hMenu, UINT item, bool fSystemMenu), (hMenu, item, fSystemMenu), 
	_SEND_((void), WM_INITMENUPOPUP, (WPARAM)(HMENU)(hMenu), MAKELPARAM((item), (fSystemMenu))), 
	((_CALL_(InitMenuPopup))((HMENU)(wParam), (UINT)LOWORD(lParam), (bool)HIWORD(lParam)), 0L))
/*287*/ MSG_TRANS(WM_MENUSELECT, 
	void, MenuSelect, (HMENU hmenu, int item, HMENU hmenuPopup, UINT flags), (hmenu, item, hmenuPopup, flags), 
	_SEND_((void), WM_MENUSELECT, MAKEWPARAM((item), (flags)), (LPARAM)(HMENU)((hmenu) ? (hmenu) : (hmenuPopup))), 
	((_CALL_(MenuSelect))((HMENU)(lParam), (HIWORD(wParam) & MF_POPUP) ? 0L : (int)(LOWORD(wParam)), (HIWORD(wParam) & MF_POPUP) ? WX::GetSubMenu((HMENU)lParam, LOWORD(wParam)) : 0L, (UINT)(((int16_t)HIWORD(wParam) == -1) ? 0xFFFFFFFF : HIWORD(wParam))), 0L))
/*288*/ MSG_TRANS(WM_MENUCHAR, 
	DWORD, MenuChar, (UINT ch, UINT flags, HMENU hmenu), (ch, flags, hmenu), 
	_SEND_((DWORD), WM_MENUCHAR, MAKEWPARAM(flags, (WORD)(ch)), (LPARAM)(HMENU)(hmenu)), 
	(LRESULT)(DWORD)(_CALL_(MenuChar))((UINT)(LOWORD(wParam)), (UINT)HIWORD(wParam), (HMENU)(lParam)))
/*289*/ MSG_TRANS(WM_ENTERIDLE, 
	void, EnterIdle, (UINT source, HWND hwndSource), (source, hwndSource), 
	_SEND_((void), WM_ENTERIDLE, (WPARAM)(UINT)(source), (LPARAM)(HWND)(hwndSource)), 
	((_CALL_(EnterIdle))((UINT)(wParam), (HWND)(lParam)), 0L))
/*294*/ MSG_TRANS(WM_MENUCOMMAND,
	void, MenuCommand, (UINT menuId, HMENU hMenu), (menuId, hMenu),
	_SEND_((void), WM_MENUCOMMAND, (WPARAM)(UINT)(menuId), (LPARAM)(HMENU)(hMenu)),
	((_CALL_(MenuCommand))((UINT)(wParam), (HMENU)(lParam)), 0L))
/*306*/ MSG_TRANS(WM_CTLCOLORMSGBOX, 
	HBRUSH, CtlColorMessageBox, (HDC hdc, HWND hwndChild), (hdc, hwndChild), 
	_SEND_((HBRUSH)(UINT_PTR), WM_CTLCOLORMSGBOX, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(_CALL_(CtlColorMessageBox))((HDC)(wParam), (HWND)(lParam)))
/*307*/ MSG_TRANS(WM_CTLCOLOREDIT, 
	HBRUSH, CtlColorEdit, (HDC hdc, HWND hwndChild), (hdc, hwndChild), 
	_SEND_((HBRUSH)(UINT_PTR), WM_CTLCOLOREDIT, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(_CALL_(CtlColorEdit))((HDC)(wParam), (HWND)(lParam)))
/*308*/ MSG_TRANS(WM_CTLCOLORLISTBOX, 
	HBRUSH, CtlColorListBox, (HDC hdc, HWND hwndChild), (hdc, hwndChild), 
	_SEND_((HBRUSH)(UINT_PTR), WM_CTLCOLORLISTBOX, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(_CALL_(CtlColorListBox))((HDC)(wParam), (HWND)(lParam)))
/*309*/ MSG_TRANS(WM_CTLCOLORBTN, 
	HBRUSH, CtlColorButton, (HDC hdc, HWND hwndChild), (hdc, hwndChild), 
	_SEND_((HBRUSH)(UINT_PTR), WM_CTLCOLORBTN, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(_CALL_(CtlColorButton))((HDC)(wParam), (HWND)(lParam)))
/*310*/ MSG_TRANS(WM_CTLCOLORDLG, 
	HBRUSH, CtlColorDialog, (HDC hdc, HWND hwndChild), (hdc, hwndChild), 
	_SEND_((HBRUSH)(UINT_PTR), WM_CTLCOLORDLG, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(_CALL_(CtlColorDialog))((HDC)(wParam), (HWND)(lParam)))
/*311*/ MSG_TRANS(WM_CTLCOLORSCROLLBAR, 
	HBRUSH, CtlColorScrollBar, (HDC hdc, HWND hwndChild), (hdc, hwndChild), 
	_SEND_((HBRUSH)(UINT_PTR), WM_CTLCOLORSCROLLBAR, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(_CALL_(CtlColorScrollBar))((HDC)(wParam), (HWND)(lParam)))
/*312*/ MSG_TRANS(WM_CTLCOLORSTATIC, 
	HBRUSH, CtlColorStatic, (HDC hdc, HWND hwndChild), (hdc, hwndChild), 
	_SEND_((HBRUSH)(UINT_PTR), WM_CTLCOLORSTATIC, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(_CALL_(CtlColorStatic))((HDC)(wParam), (HWND)(lParam)))
/*512*/ MSG_TRANS(WM_MOUSEMOVE, 
	void, MouseMove, (int x, int y, UINT keyFlags), (x, y, keyFlags), 
	_SEND_((void), WM_MOUSEMOVE, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(MouseMove))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*513*/ MSG_TRANS(WM_LBUTTONDOWN, 
	void, LButtonDown, (int x, int y, UINT keyFlags), (x, y, keyFlags),
	_SEND_((void), WM_LBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(LButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*514*/ MSG_TRANS(WM_LBUTTONUP, 
	void, LButtonUp, (int x, int y, UINT keyFlags), (x, y, keyFlags),
	_SEND_((void), WM_LBUTTONUP, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(LButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*515*/ MSG_TRANS(WM_LBUTTONDBLCLK, 
	void, LButtonClick, (int x, int y, UINT keyFlags), (x, y, keyFlags), 
	_SEND_((void), WM_LBUTTONDBLCLK, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(LButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*516*/ MSG_TRANS(WM_RBUTTONDOWN, 
	void, RButtonDown, (int x, int y, UINT keyFlags), (x, y, keyFlags),
	_SEND_((void), WM_RBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(RButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*517*/ MSG_TRANS(WM_RBUTTONUP, 
	void, RButtonUp, (int x, int y, UINT keyFlags), (x, y, keyFlags),
	_SEND_((void), WM_RBUTTONUP, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(RButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*518*/ MSG_TRANS(WM_RBUTTONDBLCLK, 
	void, RButtonClick, (int x, int y, UINT keyFlags), (x, y, keyFlags), 
	_SEND_((void), WM_RBUTTONDBLCLK, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(RButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*519*/ MSG_TRANS(WM_MBUTTONDOWN, 
	void, MButtonDown, (int x, int y, UINT keyFlags), (x, y, keyFlags),
	_SEND_((void), WM_MBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(MButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*520*/ MSG_TRANS(WM_MBUTTONUP, 
	void, MButtonUp, (int x, int y, UINT keyFlags), (x, y, keyFlags),
	_SEND_((void), WM_MBUTTONUP, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(MButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*521*/ MSG_TRANS(WM_MBUTTONDBLCLK, 
	void, MButtonClick, (int x, int y, UINT keyFlags), (x, y, keyFlags), 
	_SEND_((void), WM_MBUTTONDBLCLK, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(MButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*522*/ MSG_TRANS(WM_MOUSEWHEEL, 
	void, MouseWheel, (int xPos, int yPos, int zDelta, UINT fwKeys), (xPos, yPos, zDelta, fwKeys), 
	_SEND_((void), WM_MOUSEWHEEL, MAKEWPARAM((fwKeys), (zDelta)), MAKELPARAM((xPos), (yPos))), 
	((_CALL_(MouseWheel))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (int)(int16_t)HIWORD(wParam), (UINT)(int16_t)LOWORD(wParam)), 0L))
/*528*/ MSG_TRANS(WM_PARENTNOTIFY, 
	void, ParentNotify, (UINT msg, HWND hwndChild, int idChild), (msg, hwndChild, idChild), 
	_SEND_((void), WM_PARENTNOTIFY, MAKEWPARAM(msg, idChild), (LPARAM)(hwndChild)), 
	((_CALL_(ParentNotify))((UINT)LOWORD(wParam), (HWND)(lParam), (UINT)HIWORD(wParam)), 0L))
/*537*/ MSG_TRANS(WM_DEVICECHANGE, 
	bool, DeviceChange, (UINT uEvent, DWORD dwEventData), (uEvent, dwEventData), 
	_SEND_((bool)(DWORD), WM_DEVICECHANGE, (WPARAM)(UINT)(uEvent), (LPARAM)(DWORD)(dwEventData)), 
	(LRESULT)(DWORD)(bool)(_CALL_(DeviceChange))((UINT)(wParam), (DWORD)(lParam)))
/*544*/ MSG_TRANS(WM_MDICREATE, 
	HWND, MDICreate, (const LPMDICREATESTRUCT lpmcs), (lpmcs), 
	_SEND_((HWND), WM_MDICREATE, 0L, (LPARAM)(LPMDICREATESTRUCT)(lpmcs)), 
	(LRESULT)(DWORD)(UINT)(_CALL_(MDICreate))((LPMDICREATESTRUCT)(lParam)))
/*545*/ MSG_TRANS(WM_MDIDESTROY, 
	void, MDIDestroy, (HWND hwndDestroy), (hwndDestroy), 
	_SEND_((void), WM_MDIDESTROY, (WPARAM)(hwndDestroy), 0L), 
	((_CALL_(MDIDestroy))((HWND)(wParam)), 0L))
/*547*/ MSG_TRANS(WM_MDIRESTORE, 
	void, MDIRestore, (HWND hwndRestore), (hwndRestore), 
	_SEND_((void), WM_MDIRESTORE, (WPARAM)(hwndRestore), 0L), 
	((_CALL_(MDIRestore))((HWND)(wParam)), 0L))
/*548*/ MSG_TRANS(WM_MDINEXT, 
	HWND, MDINext, (HWND hwndCur, bool fPrev), (hwndCur, fPrev), 
	_SEND_((HWND)(UINT_PTR), WM_MDINEXT, (WPARAM)(hwndCur), (LPARAM)(fPrev)), 
	(LRESULT)(HWND)(_CALL_(MDINext))((HWND)(wParam), (bool)lParam))
/*549*/ MSG_TRANS(WM_MDIMAXIMIZE, 
	void, MDIMaximize, (HWND hwndMaximize), (hwndMaximize), 
	_SEND_((void), WM_MDIMAXIMIZE, (WPARAM)(hwndMaximize), 0L), 
	((_CALL_(MDIMaximize))((HWND)(wParam)), 0L))
/*550*/ MSG_TRANS(WM_MDITILE, 
	bool, MDITile, (UINT cmd), (cmd), 
	_SEND_((bool)(DWORD), WM_MDITILE, (WPARAM)(cmd), 0L), 
	(LRESULT)(DWORD)(_CALL_(MDITile))((UINT)(wParam)))
/*551*/ MSG_TRANS(WM_MDICASCADE, 
	bool, MDICascade, (UINT cmd), (cmd), 
	_SEND_((bool)(DWORD), WM_MDICASCADE, (WPARAM)(cmd), 0L), 
	(LRESULT)(DWORD)(_CALL_(MDICascade))((UINT)(wParam)))
/*552*/ MSG_TRANS(WM_MDIICONARRANGE, 
	void, MDIIconArrange, (), (), 
	_SEND_((void), WM_MDIICONARRANGE, 0L, 0L), 
	((_CALL_(MDIIconArrange))(), 0L))
/*553*/ MSG_TRANS(WM_MDIGETACTIVE, 
	HWND, MDIGetActive, (), (), 
	_SEND_((HWND)(UINT_PTR), WM_MDIGETACTIVE, 0L, 0L), 
	(LRESULT)(UINT_PTR)(_CALL_(MDIGetActive))())
/*560*/ MSG_TRANS(WM_MDISETMENU, 
	HMENU, MDISetMenu, (bool fRefresh, HMENU hmenuFrame, HMENU hmenuWindow), (fRefresh, hmenuFrame, hmenuWindow), 
	_SEND_((HMENU)(UINT_PTR), WM_MDISETMENU, (WPARAM)((fRefresh) ? (hmenuFrame) : 0), (LPARAM)(hmenuWindow)), 
	(LRESULT)(UINT_PTR)(_CALL_(MDISetMenu))((bool)(wParam), (HMENU)(wParam), (HMENU)(lParam)))
/*563*/ MSG_TRANS(WM_DROPFILES, 
	void, DropFiles, (HDROP hdrop), (hdrop), 
	_SEND_((void), WM_DROPFILES, (WPARAM)(HDROP)(hdrop), 0L), 
	((_CALL_(DropFiles))((HDROP)(wParam)), 0L))
/*675*/ MSG_TRANS(WM_MOUSELEAVE,
	void, MouseLeave, (), (), 
	_SEND_((void), WM_MOUSELEAVE, 0L, 0L),
	((_CALL_(MouseLeave))(), 0L))
/*768*/ MSG_TRANS(WM_CUT, 
	void, Cut, (), (), 
	_SEND_((void), WM_CUT, 0L, 0L), 
	((_CALL_(Cut))(), 0L))
/*769*/ MSG_TRANS(WM_COPY, 
	void, Copy, (), (), 
	_SEND_((void), WM_COPY, 0L, 0L), 
	((_CALL_(Copy))(), 0L))
/*770*/ MSG_TRANS(WM_PASTE, 
	void, Paste, (), (), 
	_SEND_((void), WM_PASTE, 0L, 0L), 
	((_CALL_(Paste))(), 0L))
/*771*/ MSG_TRANS(WM_CLEAR, 
	void, Clear, (), (), 
	_SEND_((void), WM_CLEAR, 0L, 0L), 
	((_CALL_(Clear))(), 0L))
/*772*/ MSG_TRANS(WM_UNDO, 
	void, Undo, (), (), 
	_SEND_((void), WM_UNDO, 0L, 0L), 
	((_CALL_(Undo))(), 0L))
/*773*/ MSG_TRANS(WM_RENDERFORMAT, 
	HANDLE, RenderFormat, (UINT fmt), (fmt), 
	_SEND_((HANDLE)(UINT_PTR), WM_RENDERFORMAT, (WPARAM)(UINT)(fmt), 0L), 
	(LRESULT)(UINT_PTR)(HANDLE)(_CALL_(RenderFormat))((UINT)(wParam)))
/*774*/ MSG_TRANS(WM_RENDERALLFORMATS, 
	void, RenderAllFormats, (), (), 
	_SEND_((void), WM_RENDERALLFORMATS, 0L, 0L), 
	((_CALL_(RenderAllFormats))(), 0L))
/*775*/ MSG_TRANS(WM_DESTROYCLIPBOARD, 
	void, DestroyClipboard, (), (), 
	_SEND_((void), WM_DESTROYCLIPBOARD, 0L, 0L), 
	((_CALL_(DestroyClipboard))(), 0L))
/*776*/ MSG_TRANS(WM_DRAWCLIPBOARD, 
	void, DrawClipboard, (), (), 
	_SEND_((void), WM_DRAWCLIPBOARD, 0L, 0L), 
	((_CALL_(DrawClipboard))(), 0L))
/*777*/ MSG_TRANS(WM_PAINTCLIPBOARD, 
	void, PaintClipboard, (HWND hwndCBViewer, const LPPAINTSTRUCT lpPaintStruct), (hwndCBViewer, lpPaintStruct), 
	_SEND_((void), WM_PAINTCLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), (LPARAM)(LPPAINTSTRUCT)(lpPaintStruct)), 
	((_CALL_(PaintClipboard))((HWND)(wParam), (const LPPAINTSTRUCT)GlobalLock((HGLOBAL)(lParam))), GlobalUnlock((HGLOBAL)(lParam)), 0L))
/*778*/ MSG_TRANS(WM_VSCROLLCLIPBOARD, 
	void, VScrollClipboard, (HWND hwndCBViewer, UINT code, int pos), (hwndCBViewer, code, pos), 
	_SEND_((void), WM_VSCROLLCLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), MAKELPARAM((code), (pos))), 
	((_CALL_(VScrollClipboard))((HWND)(wParam), (UINT)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*779*/ MSG_TRANS(WM_SIZECLIPBOARD, 
	void, SizeClipboard, (HWND hwndCBViewer, const LPRECT lprc), (hwndCBViewer, lprc), 
	_SEND_((void), WM_SIZECLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), (LPARAM)(LPRECT)(lprc)), 
	((_CALL_(SizeClipboard))((HWND)(wParam), (const LPRECT)GlobalLock((HGLOBAL)(lParam))), GlobalUnlock((HGLOBAL)(lParam)), 0L))
/*780*/ MSG_TRANS(WM_ASKCBFORMATNAME, 
	void, AskCBFormatName, (int cchMax, LPTSTR rgchName), (cchMax, rgchName), 
	_SEND_((void), WM_ASKCBFORMATNAME, (WPARAM)(int)(cchMax), (LPARAM)(rgchName)), 
	((_CALL_(AskCBFormatName))((int)(wParam), (LPTSTR)(lParam)), 0L))
/*781*/ MSG_TRANS(WM_CHANGECBCHAIN, 
	void, ChangeCBChain, (HWND hwndRemove, HWND hwndNext), (hwndRemove, hwndNext), 
	_SEND_((void), WM_CHANGECBCHAIN, (WPARAM)(HWND)(hwndRemove), (LPARAM)(HWND)(hwndNext)), 
	((_CALL_(ChangeCBChain))((HWND)(wParam), (HWND)(lParam)), 0L))
/*782*/ MSG_TRANS(WM_HSCROLLCLIPBOARD, 
	void, HScrollClipboard, (HWND hwndCBViewer, UINT code, int pos), (hwndCBViewer, code, pos), 
	_SEND_((void), WM_HSCROLLCLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), MAKELPARAM((code), (pos))), 
	((_CALL_(HScrollClipboard))((HWND)(wParam), (UINT)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*783*/ MSG_TRANS(WM_QUERYNEWPALETTE, 
	bool, QueryNewPalette, (), (), 
	_SEND_((bool)(DWORD), WM_QUERYNEWPALETTE, 0L, 0L), 
	MAKELRESULT((bool)(_CALL_(QueryNewPalette))(), 0L))
/*784*/ MSG_TRANS(WM_PALETTEISCHANGING, 
	void, PaletteIsChanging, (HWND hwndPaletteChange), (hwndPaletteChange), 
	_SEND_((void), WM_PALETTEISCHANGING, (WPARAM)(HWND)(hwndPaletteChange), 0L), 
	((_CALL_(PaletteIsChanging))((HWND)(wParam)), 0L))
/*785*/ MSG_TRANS(WM_PALETTECHANGED, 
	void, PaletteChanged, (HWND hwndPaletteChange), (hwndPaletteChange), 
	_SEND_((void), WM_PALETTECHANGED, (WPARAM)(HWND)(hwndPaletteChange), 0L), 
	((_CALL_(PaletteChanged))((HWND)(wParam)), 0L))
/*786*/ MSG_TRANS(WM_HOTKEY, 
	void, HotKey, (int idHotKey, UINT fuModifiers, UINT vk), (idHotKey, fuModifiers, vk), 
	_SEND_((void), WM_HOTKEY, (WPARAM)(idHotKey), MAKELPARAM((fuModifiers), (vk))), 
	((_CALL_(HotKey))((int)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L))

#undef MSG_TRANS
#undef _CALL_
#undef _SEND_
