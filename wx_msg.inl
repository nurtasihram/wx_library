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
	bool, OnCreate, (LPCREATESTRUCT lpCreateStruct), (lpCreateStruct), 
	_SEND_((bool)(DWORD), WM_CREATE, 0L, (LPARAM)(LPCREATESTRUCT)(lpCreateStruct)), 
	((_CALL_(OnCreate))((LPCREATESTRUCT)(lParam)) ? 0L : (LRESULT)-1L))
/*2*/ MSG_TRANS(WM_DESTROY, 
	void, OnDestroy, (), (), 
	_SEND_((void), WM_DESTROY, 0L, 0L), 
	((_CALL_(OnDestroy))(), 0L))
/*3*/ MSG_TRANS(WM_MOVE, 
	void, OnMove, (int x, int y), (x, y), 
	_SEND_((void), WM_MOVE, 0L, MAKELPARAM((x), (y))), 
	((_CALL_(OnMove))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*5*/ MSG_TRANS(WM_SIZE, 
	void, OnSize, (UINT state, int cx, int cy), (state, cx, cy), 
	_SEND_((void), WM_SIZE, (WPARAM)(UINT)(state), MAKELPARAM((cx), (cy))), 
	((_CALL_(OnSize))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*6*/ MSG_TRANS(WM_ACTIVATE, 
	void, OnActivate, (UINT state, HWND hwndActDeact, bool fMinimized), (state, hwndActDeact, fMinimized), 
	_SEND_((void), WM_ACTIVATE, MAKEWPARAM((state), (fMinimized)), (LPARAM)(HWND)(hwndActDeact)), 
	((_CALL_(OnActivate))((UINT)LOWORD(wParam), (HWND)(lParam), (bool)HIWORD(wParam)), 0L))
/*7*/ MSG_TRANS(WM_SETFOCUS, 
	void, OnSetFocus, (HWND hwndOldFocus), (hwndOldFocus), 
	_SEND_((void), WM_SETFOCUS, (WPARAM)(HWND)(hwndOldFocus), 0L), 
	((_CALL_(OnSetFocus))((HWND)(wParam)), 0L))
/*8*/ MSG_TRANS(WM_KILLFOCUS, 
	void, OnKillFocus, (HWND hwndNewFocus), (hwndNewFocus), 
	_SEND_((void), WM_KILLFOCUS, (WPARAM)(HWND)(hwndNewFocus), 0L), 
	((_CALL_(OnKillFocus))((HWND)(wParam)), 0L))
/*10*/ MSG_TRANS(WM_ENABLE, 
	void, OnEnable, (bool fEnable), (fEnable), 
	_SEND_((void), WM_ENABLE, (WPARAM)(bool)(fEnable), 0L), 
	((_CALL_(OnEnable))((bool)(wParam)), 0L))
/*11*/ MSG_TRANS(WM_SETREDRAW, 
	void, OnSetRedraw, (bool fRedraw), (fRedraw), 
	_SEND_((void), WM_SETREDRAW, (WPARAM)(bool)(fRedraw), 0L), 
	((_CALL_(OnSetRedraw))((bool)(wParam)), 0L))
/*12*/ MSG_TRANS(WM_SETTEXT, 
	void, OnSetText, (LPCTSTR lpszText), (lpszText), 
	_SEND_((void), WM_SETTEXT, 0L, (LPARAM)(LPCTSTR)(lpszText)), 
	((_CALL_(OnSetText))((LPCTSTR)(lParam)), 0L))
/*13*/ MSG_TRANS(WM_GETTEXT, 
	INT, OnGetText, (int cchTextMax, LPTSTR lpszText), (cchTextMax, lpszText), 
	_SEND_((int)(DWORD), WM_GETTEXT, (WPARAM)(int)(cchTextMax), (LPARAM)(LPTSTR)(lpszText)), 
	(LRESULT)(DWORD)(int)(_CALL_(OnGetText))((int)(wParam), (LPTSTR)(lParam)))
/*14*/ MSG_TRANS(WM_GETTEXTLENGTH, 
	INT, OnGetTextLength, (), (), 
	_SEND_((int)(DWORD), WM_GETTEXTLENGTH, 0L, 0L), 
	(LRESULT)(DWORD)(int)(_CALL_(OnGetTextLength))())
/*15*/ MSG_TRANS(WM_PAINT, 
	void, OnPaint, (), (), 
	_SEND_((void), WM_PAINT, 0L, 0L), 
	((_CALL_(OnPaint))(), 0L))
/*16*/ MSG_TRANS(WM_CLOSE, 
	void, OnClose, (), (), 
	_SEND_((void), WM_CLOSE, 0L, 0L), 
	((_CALL_(OnClose))(), 0L))
/*17*/ MSG_TRANS(WM_QUERYENDSESSION, 
	bool, OnQueryEndSession, (), (), 
	_SEND_((bool)(DWORD), WM_QUERYENDSESSION, 0L, 0L), 
	MAKELRESULT((bool)(_CALL_(OnQueryEndSession))(), 0L))
/*18*/ MSG_TRANS(WM_QUIT, 
	void, OnQuit, (int exitCode), (exitCode), 
	_SEND_((void), WM_QUIT, (WPARAM)(exitCode), 0L), 
	((_CALL_(OnQuit))((int)(wParam)), 0L))
/*19*/ MSG_TRANS(WM_QUERYOPEN, 
	bool, OnQueryOpen, (), (), 
	_SEND_((bool)(DWORD), WM_QUERYOPEN, 0L, 0L), 
	MAKELRESULT((bool)(_CALL_(OnQueryOpen))(), 0L))
/*20*/ MSG_TRANS(WM_ERASEBKGND, 
	bool, OnEraseBkgnd, (HDC hdc), (hdc), 
	_SEND_((bool)(DWORD), WM_ERASEBKGND, (WPARAM)(HDC)(hdc), 0L), 
	(LRESULT)(DWORD)(bool)(_CALL_(OnEraseBkgnd))((HDC)(wParam)))
/*21*/ MSG_TRANS(WM_SYSCOLORCHANGE, 
	void, OnSysColorChange, (), (), 
	_SEND_((void), WM_SYSCOLORCHANGE, 0L, 0L), 
	((_CALL_(OnSysColorChange))(), 0L))
/*22*/ MSG_TRANS(WM_ENDSESSION, 
	void, OnEndSession, (bool fEnding), (fEnding), 
	_SEND_((void), WM_ENDSESSION, (WPARAM)(bool)(fEnding), 0L), 
	((_CALL_(OnEndSession))((bool)(wParam)), 0L))
/*24*/ MSG_TRANS(WM_SHOWWINDOW, 
	void, OnShowWindow, (bool fShow, UINT status), (fShow, status), 
	_SEND_((void), WM_SHOWWINDOW, (WPARAM)(bool)(fShow), (LPARAM)(UINT)(status)), 
	((_CALL_(OnShowWindow))((bool)(wParam), (UINT)(lParam)), 0L))
/*26*/ MSG_TRANS(WM_WININICHANGE, 
	void, OnWinIniChange, (LPCTSTR lpszSectionName), (lpszSectionName), 
	_SEND_((void), WM_WININICHANGE, 0L, (LPARAM)(LPCTSTR)(lpszSectionName)), 
	((_CALL_(OnWinIniChange))((LPCTSTR)(lParam)), 0L))
/*27*/ MSG_TRANS(WM_DEVMODECHANGE, 
	void, OnDevModeChange, (LPCTSTR lpszDeviceName), (lpszDeviceName), 
	_SEND_((void), WM_DEVMODECHANGE, 0L, (LPARAM)(LPCTSTR)(lpszDeviceName)), 
	((_CALL_(OnDevModeChange))((LPCTSTR)(lParam)), 0L))
/*28*/ MSG_TRANS(WM_ACTIVATEAPP, 
	void, OnActivateApp, (bool fActivate, DWORD dwThreadId), (fActivate, dwThreadId), 
	_SEND_((void), WM_ACTIVATEAPP, (WPARAM)(bool)(fActivate), (LPARAM)(dwThreadId)), 
	((_CALL_(OnActivateApp))((bool)(wParam), (DWORD)(lParam)), 0L))
/*29*/ MSG_TRANS(WM_FONTCHANGE, 
	void, OnFontChange, (), (), 
	_SEND_((void), WM_FONTCHANGE, 0L, 0L), 
	((_CALL_(OnFontChange))(), 0L))
/*30*/ MSG_TRANS(WM_TIMECHANGE, 
	void, OnTimeChange, (), (), 
	_SEND_((void), WM_TIMECHANGE, 0L, 0L), 
	((_CALL_(OnTimeChange))(), 0L))
/*31*/ MSG_TRANS(WM_CANCELMODE, 
	void, OnCancelMode, (), (), 
	_SEND_((void), WM_CANCELMODE, 0L, 0L), 
	((_CALL_(OnCancelMode))(), 0L))
/*32*/ MSG_TRANS(WM_SETCURSOR, 
	bool, OnSetCursor, (HWND hwndCursor, UINT codeHitTest, UINT msg), (hwndCursor, codeHitTest, msg), 
	_SEND_((bool)(DWORD), WM_SETCURSOR, (WPARAM)(HWND)(hwndCursor), MAKELPARAM((codeHitTest), (msg))), 
	(LRESULT)(DWORD)(bool)(_CALL_(OnSetCursor))((HWND)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)))
/*33*/ MSG_TRANS(WM_MOUSEACTIVATE, 
	int, OnMouseActivate, (HWND hwndTopLevel, UINT codeHitTest, UINT msg), (hwndTopLevel, codeHitTest, msg), 
	_SEND_((int)(DWORD), WM_MOUSEACTIVATE, (WPARAM)(HWND)(hwndTopLevel), MAKELPARAM((codeHitTest), (msg))), 
	(LRESULT)(DWORD)(int)(_CALL_(OnMouseActivate))((HWND)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)))
/*34*/ MSG_TRANS(WM_CHILDACTIVATE, 
	void, OnChildActivate, (), (), 
	_SEND_((void), WM_CHILDACTIVATE, 0L, 0L), 
	((_CALL_(OnChildActivate))(), 0L))
/*35*/ MSG_TRANS(WM_QUEUESYNC, 
	void, OnQueueSync, (), (), 
	_SEND_((void), WM_QUEUESYNC, 0L, 0L), 
	((_CALL_(OnQueueSync))(), 0L))
/*36*/ MSG_TRANS(WM_GETMINMAXINFO, 
	void, OnGetMinMaxInfo, (LPMINMAXINFO lpMinMaxInfo), (lpMinMaxInfo), 
	_SEND_((void), WM_GETMINMAXINFO, 0L, (LPARAM)(LPMINMAXINFO)(lpMinMaxInfo)), 
	((_CALL_(OnGetMinMaxInfo))((LPMINMAXINFO)(lParam)), 0L))
/*39*/ MSG_TRANS(WM_ICONERASEBKGND, 
	bool, OnIconEraseBkgnd, (HDC hdc), (hdc), 
	_SEND_((bool)(DWORD), WM_ICONERASEBKGND, (WPARAM)(HDC)(hdc), 0L), 
	(LRESULT)(DWORD)(bool)(_CALL_(OnIconEraseBkgnd))((HDC)(wParam)))
/*40*/ MSG_TRANS(WM_NEXTDLGCTL, 
	HWND, OnNextDlgCtl, (HWND hwndSetFocus, bool fNext), (hwndSetFocus, fNext), 
	_SEND_((HWND)(UINT_PTR), WM_NEXTDLGCTL, (WPARAM)(HWND)(hwndSetFocus), (LPARAM)(fNext)), 
	(LRESULT)(UINT_PTR)(HWND)(_CALL_(OnNextDlgCtl))((HWND)(wParam), (bool)(lParam)))
/*42*/ MSG_TRANS(WM_SPOOLERSTATUS, 
	void, OnSpoolerStatus, (UINT status, int cJobInQueue), (status, cJobInQueue), 
	_SEND_((void), WM_SPOOLERSTATUS, (WPARAM)(status), MAKELPARAM((cJobInQueue), 0)), 
	((_CALL_(OnSpoolerStatus))((UINT)(wParam), (int)(int16_t)LOWORD(lParam)), 0L))
/*43*/ MSG_TRANS(WM_DRAWITEM, 
	void, OnDrawItem, (const DRAWITEMSTRUCT * lpDrawItem), (lpDrawItem), 
	_SEND_((void), WM_DRAWITEM, (WPARAM)(((const DRAWITEMSTRUCT *)lpDrawItem)->CtlID), (LPARAM)(const DRAWITEMSTRUCT *)(lpDrawItem)), 
	((_CALL_(OnDrawItem))((const DRAWITEMSTRUCT *)(lParam)), 0L))
/*44*/ MSG_TRANS(WM_MEASUREITEM, 
	void, OnMeasureItem, (MEASUREITEMSTRUCT * lpMeasureItem), (lpMeasureItem), 
	_SEND_((void), WM_MEASUREITEM, (WPARAM)(((MEASUREITEMSTRUCT *)lpMeasureItem)->CtlID), (LPARAM)(MEASUREITEMSTRUCT *)(lpMeasureItem)), 
	((_CALL_(OnMeasureItem))((MEASUREITEMSTRUCT *)(lParam)), 0L))
/*45*/ MSG_TRANS(WM_DELETEITEM, 
	void, OnDeleteItem, (const DELETEITEMSTRUCT * lpDeleteItem), (lpDeleteItem), 
	_SEND_((void), WM_DELETEITEM, (WPARAM)(((const DELETEITEMSTRUCT *)(lpDeleteItem))->CtlID), (LPARAM)(const DELETEITEMSTRUCT *)(lpDeleteItem)), 
	((_CALL_(OnDeleteItem))((const DELETEITEMSTRUCT *)(lParam)), 0L))
/*46*/ MSG_TRANS(WM_VKEYTOITEM, 
	int, OnVkeyToItem, (UINT vk, HWND hwndListBox, int iCaret), (vk, hwndListBox, iCaret), 
	_SEND_((int)(DWORD), WM_VKEYTOITEM, MAKEWPARAM((vk), (iCaret)), (LPARAM)(hwndListBox)), 
	(LRESULT)(DWORD)(int)(_CALL_(OnVkeyToItem))((UINT)LOWORD(wParam), (HWND)(lParam), (int)(int16_t)HIWORD(wParam)))
/*47*/ MSG_TRANS(WM_CHARTOITEM, 
	int, OnCharToItem, (UINT ch, HWND hwndListBox, int iCaret), (ch, hwndListBox, iCaret), 
	_SEND_((int)(DWORD), WM_CHARTOITEM, MAKEWPARAM((UINT)(ch), (UINT)(iCaret)), (LPARAM)(hwndListBox)), 
	(LRESULT)(DWORD)(int)(_CALL_(OnCharToItem))((UINT)LOWORD(wParam), (HWND)(lParam), (int)(int16_t)HIWORD(wParam)))
/*48*/ MSG_TRANS(WM_SETFONT, 
	void, OnSetFont, (HFONT hfont, bool fRedraw), (hfont, fRedraw), 
	_SEND_((void), WM_SETFONT, (WPARAM)(HFONT)(hfont), (LPARAM)(bool)(fRedraw)), 
	((_CALL_(OnSetFont))((HFONT)(wParam), (bool)(lParam)), 0L))
/*49*/ MSG_TRANS(WM_GETFONT, 
	HFONT, OnGetFont, (), (), 
	_SEND_((HFONT)(UINT_PTR), WM_GETFONT, 0L, 0L), 
	(LRESULT)(UINT_PTR)(HFONT)(_CALL_(OnGetFont))())
/*55*/ MSG_TRANS(WM_QUERYDRAGICON, 
	HICON, OnQueryDragIcon, (), (), 
	_SEND_((HICON), WM_QUERYDRAGICON, 0L, 0L), 
	(LRESULT)(DWORD)(UINT)(_CALL_(OnQueryDragIcon))())
/*57*/ MSG_TRANS(WM_COMPAREITEM, 
	int, OnCompareItem, (const COMPAREITEMSTRUCT * lpCompareItem), (lpCompareItem), 
	_SEND_((int)(DWORD), WM_COMPAREITEM, (WPARAM)(((const COMPAREITEMSTRUCT *)(lpCompareItem))->CtlID), (LPARAM)(const COMPAREITEMSTRUCT *)(lpCompareItem)), 
	(LRESULT)(DWORD)(int)(_CALL_(OnCompareItem))((const COMPAREITEMSTRUCT *)(lParam)))
/*65*/ MSG_TRANS(WM_COMPACTING, 
	void, OnCompacting, (UINT compactRatio), (compactRatio), 
	_SEND_((void), WM_COMPACTING, (WPARAM)(UINT)(compactRatio), 0L), 
	((_CALL_(OnCompacting))((UINT)(wParam)), 0L))
/*68*/ MSG_TRANS(WM_COMMNOTIFY, 
	void, OnCommNotify, (int cid, UINT flags), (cid, flags), 
	_SEND_((void), WM_COMMNOTIFY, (WPARAM)(cid), MAKELPARAM((flags), 0)), 
	((_CALL_(OnCommNotify))((int)(wParam), (UINT)LOWORD(lParam)), 0L))
/*70*/ MSG_TRANS(WM_WINDOWPOSCHANGING, 
	bool, OnWindowPosChanging, (LPWINDOWPOS lpwpos), (lpwpos), 
	_SEND_((bool)(DWORD), WM_WINDOWPOSCHANGING, 0L, (LPARAM)(LPWINDOWPOS)(lpwpos)), 
	(LRESULT)(DWORD)(bool)(_CALL_(OnWindowPosChanging))((LPWINDOWPOS)(lParam)))
/*71*/ MSG_TRANS(WM_WINDOWPOSCHANGED, 
	void, OnWindowPosChanged, (const WINDOWPOS *lpwpos), (lpwpos), 
	_SEND_((void), WM_WINDOWPOSCHANGED, 0L, (LPARAM)(const WINDOWPOS *)(lpwpos)), 
	((_CALL_(OnWindowPosChanged))((const WINDOWPOS *)(lParam)), 0L))
/*72*/ MSG_TRANS(WM_POWER, 
	void, OnPower, (int code), (code), 
	_SEND_((void), WM_POWER, (WPARAM)(int)(code), 0L), 
	((_CALL_(OnPower))((int)(wParam)), 0L))
/*74*/ MSG_TRANS(WM_COPYDATA, 
	bool, OnCopyData, (HWND hwndFrom, PCOPYDATASTRUCT pcds), (hwndFrom, pcds), 
	_SEND_((bool)(UINT)(DWORD), WM_COPYDATA, (WPARAM)(hwndFrom), (LPARAM)(pcds)), 
	((_CALL_(OnCopyData))((HWND)(wParam), (PCOPYDATASTRUCT)lParam), 0L))
/*123*/ MSG_TRANS(WM_CONTEXTMENU, 
	void, OnContextMenu, (HWND hwndContext, UINT xPos, UINT yPos), (hwndContext, xPos, yPos), 
	_SEND_((void), WM_CONTEXTMENU, (WPARAM)(HWND)(hwndContext), MAKELPARAM((UINT)(xPos), (UINT)(yPos))), 
	((_CALL_(OnContextMenu))((HWND)(wParam), (int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*126*/ MSG_TRANS(WM_DISPLAYCHANGE, 
	void, OnDisplayChange, (UINT bitsPerPixel, UINT cxScreen, UINT cyScreen), (bitsPerPixel, cxScreen, cyScreen), 
	_SEND_((void), WM_DISPLAYCHANGE, (WPARAM)(UINT)(bitsPerPixel), (LPARAM)MAKELPARAM((UINT)(cxScreen), (UINT)(cyScreen))), 
	((_CALL_(OnDisplayChange))((UINT)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L))
/*129*/ MSG_TRANS(WM_NCCREATE, 
	bool, OnNCCreate, (LPCREATESTRUCT lpCreateStruct), (lpCreateStruct), 
	_SEND_((bool)(DWORD), WM_NCCREATE, 0L, (LPARAM)(LPCREATESTRUCT)(lpCreateStruct)), 
	(LRESULT)(DWORD)(bool)(_CALL_(OnNCCreate))((LPCREATESTRUCT)(lParam)))
/*130*/ MSG_TRANS(WM_NCDESTROY, 
	void, OnNCDestroy, (), (), 
	_SEND_((void), WM_NCDESTROY, 0L, 0L), 
	((_CALL_(OnNCDestroy))(), 0L))
/*131*/ MSG_TRANS(WM_NCCALCSIZE, 
	UINT, OnNCCalcSize, (bool fCalcValidRects, NCCALCSIZE_PARAMS * lpcsp), (fCalcValidRects, lpcsp), 
	_SEND_((UINT)(DWORD), WM_NCCALCSIZE, (WPARAM)(fCalcValidRects), (LPARAM)(NCCALCSIZE_PARAMS *)(lpcsp)), 
	(LRESULT)(DWORD)(UINT)(_CALL_(OnNCCalcSize))((bool)(wParam), (NCCALCSIZE_PARAMS *)(lParam)))
/*132*/ MSG_TRANS(WM_NCHITTEST, 
	UINT, OnNCHitTest, (int x, int y), (x, y), 
	_SEND_((UINT)(DWORD), WM_NCHITTEST, 0L, MAKELPARAM((x), (y))), 
	(LRESULT)(DWORD)(UINT)(_CALL_(OnNCHitTest))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)))
/*133*/ MSG_TRANS(WM_NCPAINT, 
	void, OnNCPaint, (HRGN hrgn), (hrgn), 
	_SEND_((void), WM_NCPAINT, (WPARAM)(HRGN)(hrgn), 0L), 
	((_CALL_(OnNCPaint))((HRGN)(wParam)), 0L))
/*134*/ MSG_TRANS(WM_NCACTIVATE, 
	bool, OnNCActivate, (bool fActive, HWND hwndActDeact, bool fMinimized), (fActive, hwndActDeact, fMinimized), 
	_SEND_((bool)(DWORD), WM_NCACTIVATE, (WPARAM)(bool)(fActive), 0L), 
	(LRESULT)(DWORD)(bool)(_CALL_(OnNCActivate))((bool)(wParam), 0L, 0L))
/*135*/ MSG_TRANS(WM_GETDLGCODE, 
	UINT, OnGetDlgCode, (LPMSG lpmsg), (lpmsg), 
	_SEND_((UINT)(DWORD), WM_GETDLGCODE, (lpmsg ? lpmsg->wParam : 0), (LPARAM)(LPMSG)(lpmsg)), 
	(LRESULT)(DWORD)(UINT)(_CALL_(OnGetDlgCode))((LPMSG)(lParam)))
/*160*/ MSG_TRANS(WM_NCMOUSEMOVE, 
	void, OnNCMouseMove, (int x, int y, UINT codeHitTest), (x, y, codeHitTest), 
	_SEND_((void), WM_NCMOUSEMOVE, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y))), 
	((_CALL_(OnNCMouseMove))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*161*/ MSG_TRANS(WM_NCLBUTTONDOWN, 
	void, OnNCLButtonDown, (int x, int y, UINT codeHitTest), (x, y, codeHitTest), 
	_SEND_((void), WM_NCLBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y))), 
	((_CALL_(OnNCLButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*162*/ MSG_TRANS(WM_NCLBUTTONUP, 
	void, OnNCLButtonUp, (int x, int y, UINT codeHitTest), (x, y, codeHitTest),
	_SEND_((void), WM_NCLBUTTONUP, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y))), 
	((_CALL_(OnNCLButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*163*/ MSG_TRANS(WM_NCLBUTTONDBLCLK, 
	void, OnNCLButtonClick, (int x, int y, UINT codeHitTest), (x, y, codeHitTest), 
	_SEND_((void), WM_NCLBUTTONDBLCLK, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y))), 
	((_CALL_(OnNCLButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*164*/ MSG_TRANS(WM_NCRBUTTONDOWN, 
	void, OnNCRButtonDown, (int x, int y, UINT codeHitTest), (x, y, codeHitTest),
	_SEND_((void), WM_NCRBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((_CALL_(OnNCRButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*165*/ MSG_TRANS(WM_NCRBUTTONUP, 
	void, OnNCRButtonUp, (int x, int y, UINT codeHitTest), (x, y, codeHitTest),
	_SEND_((void), WM_NCRBUTTONUP, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((_CALL_(OnNCRButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*166*/ MSG_TRANS(WM_NCRBUTTONDBLCLK, 
	void, OnNCRButtonClick, (int x, int y, UINT codeHitTest), (x, y, codeHitTest), 
	_SEND_((void), WM_NCRBUTTONDBLCLK, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((_CALL_(OnNCRButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*167*/ MSG_TRANS(WM_NCMBUTTONDOWN, 
	void, OnNCMButtonDown, (int x, int y, UINT codeHitTest), (x, y, codeHitTest),
	_SEND_((void), WM_NCMBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((_CALL_(OnNCMButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*168*/ MSG_TRANS(WM_NCMBUTTONUP, 
	void, OnNCMButtonUp, (int x, int y, UINT codeHitTest), (x, y, codeHitTest),
	_SEND_((void), WM_NCMBUTTONUP, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((_CALL_(OnNCMButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*169*/ MSG_TRANS(WM_NCMBUTTONDBLCLK, 
	void, OnNCMButtonClick, (int x, int y, UINT codeHitTest), (x, y, codeHitTest), 
	_SEND_((void), WM_NCMBUTTONDBLCLK, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) ), 
	((_CALL_(OnNCMButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*256*/ MSG_TRANS(WM_KEYDOWN, 
	void, OnKeyDown, (UINT vk, int16_t wRepeat, KEY_FLAGS flags), (vk, wRepeat, flags),
	_SEND_((void), WM_KEYDOWN, (WPARAM)(UINT)(vk), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))), 
	((_CALL_(OnKeyDown))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*257*/ MSG_TRANS(WM_KEYUP, 
	void, OnKeyUp, (UINT vk, int16_t wRepeat, KEY_FLAGS flags), (vk, wRepeat, flags),
	_SEND_((void), WM_KEYUP, (WPARAM)(UINT)(vk), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))), 
	((_CALL_(OnKeyUp))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*258*/ MSG_TRANS(WM_CHAR, 
	void, OnChar, (TCHAR ch, int16_t wRepeat, KEY_FLAGS flags), (ch, wRepeat, flags),
	_SEND_((void), WM_CHAR, (WPARAM)(UINT)(ch), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))),
	((_CALL_(OnChar))((TCHAR)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*259*/ MSG_TRANS(WM_DEADCHAR, 
	void, OnDeadChar, (TCHAR ch, int16_t wRepeat, KEY_FLAGS flags), (ch, wRepeat, flags),
	_SEND_((void), WM_DEADCHAR, (WPARAM)(UINT)(ch), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))),
	((_CALL_(OnDeadChar))((TCHAR)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*260*/ MSG_TRANS(WM_SYSKEYDOWN, 
	void, OnSysKeyDown, (UINT vk, int16_t wRepeat, KEY_FLAGS flags), (vk, wRepeat, flags),
	_SEND_((void), WM_SYSKEYDOWN, (WPARAM)(UINT)(vk), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))), 
	((_CALL_(OnSysKeyDown))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*261*/ MSG_TRANS(WM_SYSKEYUP, 
	void, OnSysKeyUp, (UINT vk, int16_t wRepeat, KEY_FLAGS flags), (vk, wRepeat, flags),
	_SEND_((void), WM_SYSKEYUP, (WPARAM)(UINT)(vk), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))), 
	((_CALL_(OnSysKeyUp))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*262*/ MSG_TRANS(WM_SYSCHAR, 
	void, OnSysChar, (TCHAR ch, int16_t wRepeat, KEY_FLAGS flags), (ch, wRepeat, flags),
	_SEND_((void), WM_SYSCHAR, (WPARAM)(UINT)(ch), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))),
	((_CALL_(OnSysChar))((TCHAR)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*263*/ MSG_TRANS(WM_SYSDEADCHAR, 
	void, OnSysDeadChar, (TCHAR ch, int16_t wRepeat, KEY_FLAGS flags), (ch, wRepeat, flags),
	_SEND_((void), WM_SYSDEADCHAR, (WPARAM)(UINT)(ch), MAKELPARAM((wRepeat), reuse_as<WORD>(flags))),
	((_CALL_(OnSysDeadChar))((TCHAR)(wParam), (int)(int16_t)LOWORD(lParam), reuse_as<KEY_FLAGS>(HIWORD(lParam))), 0L))
/*272*/ MSG_TRANS(WM_INITDIALOG, 
	bool, OnInitDialog, (HWND hwndFocus, LPARAM lParam), (hwndFocus, lParam), 
	_SEND_((bool)(DWORD), WM_INITDIALOG, (WPARAM)(HWND)(hwndFocus), (lParam)), 
	(LRESULT)(DWORD)(UINT)(bool)(_CALL_(OnInitDialog))((HWND)(wParam), lParam))
/*273*/ MSG_TRANS(WM_COMMAND, 
	void, OnCommand, (int id, HWND hwndCtl, UINT codeNotify), (id, hwndCtl, codeNotify), 
	_SEND_((void), WM_COMMAND, MAKEWPARAM((UINT)(id), (UINT)(codeNotify)), (LPARAM)(HWND)(hwndCtl)), 
	((_CALL_(OnCommand))((int)(LOWORD(wParam)), (HWND)(lParam), (UINT)HIWORD(wParam)), 0L))
/*274*/ MSG_TRANS(WM_SYSCOMMAND, 
	void, OnSysCommand, (UINT cmd, int x, int y), (cmd, x, y), 
	_SEND_((void), WM_SYSCOMMAND, (WPARAM)(UINT)(cmd), MAKELPARAM((x), (y))), 
	((_CALL_(OnSysCommand))((UINT)(wParam), (int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*275*/ MSG_TRANS(WM_TIMER, 
	void, OnTimer, (UINT id), (id), 
	_SEND_((void), WM_TIMER, (WPARAM)(UINT)(id), 0L), 
	((_CALL_(OnTimer))((UINT)(wParam)), 0L))
/*276*/ MSG_TRANS(WM_HSCROLL, 
	void, OnHScroll, (HWND hwndCtl, UINT code, int pos), (hwndCtl, code, pos), 
	_SEND_((void), WM_HSCROLL, MAKEWPARAM((UINT)(int)(code), (UINT)(int)(pos)), (LPARAM)(HWND)(hwndCtl)), 
	((_CALL_(OnHScroll))((HWND)(lParam), (UINT)(LOWORD(wParam)), (int)(int16_t)HIWORD(wParam)), 0L))
/*277*/ MSG_TRANS(WM_VSCROLL, 
	void, OnVScroll, (HWND hwndCtl, UINT code, int pos), (hwndCtl, code, pos), 
	_SEND_((void), WM_VSCROLL, MAKEWPARAM((UINT)(int)(code), (UINT)(int)(pos)), (LPARAM)(HWND)(hwndCtl)), 
	((_CALL_(OnVScroll))((HWND)(lParam), (UINT)(LOWORD(wParam)), (int)(int16_t)HIWORD(wParam)), 0L))
/*278*/ MSG_TRANS(WM_INITMENU, 
	void, OnInitMenu, (HMENU hMenu), (hMenu), 
	_SEND_((void), WM_INITMENU, (WPARAM)(HMENU)(hMenu), 0L), 
	((_CALL_(OnInitMenu))((HMENU)(wParam)), 0L))
/*279*/ MSG_TRANS(WM_INITMENUPOPUP, 
	void, OnInitMenuPopup, (HMENU hMenu, UINT item, bool fSystemMenu), (hMenu, item, fSystemMenu), 
	_SEND_((void), WM_INITMENUPOPUP, (WPARAM)(HMENU)(hMenu), MAKELPARAM((item), (fSystemMenu))), 
	((_CALL_(OnInitMenuPopup))((HMENU)(wParam), (UINT)LOWORD(lParam), (bool)HIWORD(lParam)), 0L))
/*287*/ MSG_TRANS(WM_MENUSELECT, 
	void, OnMenuSelect, (HMENU hmenu, int item, HMENU hmenuPopup, UINT flags), (hmenu, item, hmenuPopup, flags), 
	_SEND_((void), WM_MENUSELECT, MAKEWPARAM((item), (flags)), (LPARAM)(HMENU)((hmenu) ? (hmenu) : (hmenuPopup))), 
	((_CALL_(OnMenuSelect))((HMENU)(lParam), (HIWORD(wParam) & MF_POPUP) ? 0L : (int)(LOWORD(wParam)), (HIWORD(wParam) & MF_POPUP) ? GetSubMenu((HMENU)lParam, LOWORD(wParam)) : 0L, (UINT)(((int16_t)HIWORD(wParam) == -1) ? 0xFFFFFFFF : HIWORD(wParam))), 0L))
/*288*/ MSG_TRANS(WM_MENUCHAR, 
	DWORD, OnMenuChar, (UINT ch, UINT flags, HMENU hmenu), (ch, flags, hmenu), 
	_SEND_((DWORD), WM_MENUCHAR, MAKEWPARAM(flags, (WORD)(ch)), (LPARAM)(HMENU)(hmenu)), 
	(LRESULT)(DWORD)(_CALL_(OnMenuChar))((UINT)(LOWORD(wParam)), (UINT)HIWORD(wParam), (HMENU)(lParam)))
/*289*/ MSG_TRANS(WM_ENTERIDLE, 
	void, OnEnterIdle, (UINT source, HWND hwndSource), (source, hwndSource), 
	_SEND_((void), WM_ENTERIDLE, (WPARAM)(UINT)(source), (LPARAM)(HWND)(hwndSource)), 
	((_CALL_(OnEnterIdle))((UINT)(wParam), (HWND)(lParam)), 0L))
/*294*/ MSG_TRANS(WM_MENUCOMMAND,
	void, OnMenuCommand, (UINT menuId, HMENU hMenu), (menuId, hMenu),
	_SEND_((void), WM_MENUCOMMAND, (WPARAM)(UINT)(menuId), (LPARAM)(HMENU)(hMenu)),
	((_CALL_(OnMenuCommand))((UINT)(wParam), (HMENU)(lParam)), 0L))
/*306*/ MSG_TRANS(WM_CTLCOLORMSGBOX, 
	HBRUSH, OnCtlColorMessageBox, (HDC hdc, HWND hwndChild), (hdc, hwndChild), 
	_SEND_((HBRUSH)(UINT_PTR), WM_CTLCOLORMSGBOX, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(_CALL_(OnCtlColorMessageBox))((HDC)(wParam), (HWND)(lParam)))
/*307*/ MSG_TRANS(WM_CTLCOLOREDIT, 
	HBRUSH, OnCtlColorEdit, (HDC hdc, HWND hwndChild), (hdc, hwndChild), 
	_SEND_((HBRUSH)(UINT_PTR), WM_CTLCOLOREDIT, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(_CALL_(OnCtlColorEdit))((HDC)(wParam), (HWND)(lParam)))
/*308*/ MSG_TRANS(WM_CTLCOLORLISTBOX, 
	HBRUSH, OnCtlColorListBox, (HDC hdc, HWND hwndChild), (hdc, hwndChild), 
	_SEND_((HBRUSH)(UINT_PTR), WM_CTLCOLORLISTBOX, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(_CALL_(OnCtlColorListBox))((HDC)(wParam), (HWND)(lParam)))
/*309*/ MSG_TRANS(WM_CTLCOLORBTN, 
	HBRUSH, OnCtlColorButton, (HDC hdc, HWND hwndChild), (hdc, hwndChild), 
	_SEND_((HBRUSH)(UINT_PTR), WM_CTLCOLORBTN, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(_CALL_(OnCtlColorButton))((HDC)(wParam), (HWND)(lParam)))
/*310*/ MSG_TRANS(WM_CTLCOLORDLG, 
	HBRUSH, OnCtlColorDialog, (HDC hdc, HWND hwndChild), (hdc, hwndChild), 
	_SEND_((HBRUSH)(UINT_PTR), WM_CTLCOLORDLG, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(_CALL_(OnCtlColorDialog))((HDC)(wParam), (HWND)(lParam)))
/*311*/ MSG_TRANS(WM_CTLCOLORSCROLLBAR, 
	HBRUSH, OnCtlColorScrollBar, (HDC hdc, HWND hwndChild), (hdc, hwndChild), 
	_SEND_((HBRUSH)(UINT_PTR), WM_CTLCOLORSCROLLBAR, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(_CALL_(OnCtlColorScrollBar))((HDC)(wParam), (HWND)(lParam)))
/*312*/ MSG_TRANS(WM_CTLCOLORSTATIC, 
	HBRUSH, OnCtlColorStatic, (HDC hdc, HWND hwndChild), (hdc, hwndChild), 
	_SEND_((HBRUSH)(UINT_PTR), WM_CTLCOLORSTATIC, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild)), 
	(LRESULT)(UINT_PTR)(HBRUSH)(_CALL_(OnCtlColorStatic))((HDC)(wParam), (HWND)(lParam)))
/*512*/ MSG_TRANS(WM_MOUSEMOVE, 
	void, OnMouseMove, (int x, int y, UINT keyFlags), (x, y, keyFlags), 
	_SEND_((void), WM_MOUSEMOVE, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(OnMouseMove))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*513*/ MSG_TRANS(WM_LBUTTONDOWN, 
	void, OnLButtonDown, (int x, int y, UINT keyFlags), (x, y, keyFlags),
	_SEND_((void), WM_LBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(OnLButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*514*/ MSG_TRANS(WM_LBUTTONUP, 
	void, OnLButtonUp, (int x, int y, UINT keyFlags), (x, y, keyFlags),
	_SEND_((void), WM_LBUTTONUP, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(OnLButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*515*/ MSG_TRANS(WM_LBUTTONDBLCLK, 
	void, OnLButtonClick, (int x, int y, UINT keyFlags), (x, y, keyFlags), 
	_SEND_((void), WM_LBUTTONDBLCLK, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(OnLButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*516*/ MSG_TRANS(WM_RBUTTONDOWN, 
	void, OnRButtonDown, (int x, int y, UINT keyFlags), (x, y, keyFlags),
	_SEND_((void), WM_RBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(OnRButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*517*/ MSG_TRANS(WM_RBUTTONUP, 
	void, OnRButtonUp, (int x, int y, UINT keyFlags), (x, y, keyFlags),
	_SEND_((void), WM_RBUTTONUP, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(OnRButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*518*/ MSG_TRANS(WM_RBUTTONDBLCLK, 
	void, OnRButtonClick, (int x, int y, UINT keyFlags), (x, y, keyFlags), 
	_SEND_((void), WM_RBUTTONDBLCLK, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(OnRButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*519*/ MSG_TRANS(WM_MBUTTONDOWN, 
	void, OnMButtonDown, (int x, int y, UINT keyFlags), (x, y, keyFlags),
	_SEND_((void), WM_MBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(OnMButtonDown))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*520*/ MSG_TRANS(WM_MBUTTONUP, 
	void, OnMButtonUp, (int x, int y, UINT keyFlags), (x, y, keyFlags),
	_SEND_((void), WM_MBUTTONUP, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(OnMButtonUp))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*521*/ MSG_TRANS(WM_MBUTTONDBLCLK, 
	void, OnMButtonClick, (int x, int y, UINT keyFlags), (x, y, keyFlags), 
	_SEND_((void), WM_MBUTTONDBLCLK, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y))), 
	((_CALL_(OnMButtonClick))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (UINT)(wParam)), 0L))
/*522*/ MSG_TRANS(WM_MOUSEWHEEL, 
	void, OnMouseWheel, (int xPos, int yPos, int zDelta, UINT fwKeys), (xPos, yPos, zDelta, fwKeys), 
	_SEND_((void), WM_MOUSEWHEEL, MAKEWPARAM((fwKeys), (zDelta)), MAKELPARAM((xPos), (yPos))), 
	((_CALL_(OnMouseWheel))((int)(int16_t)LOWORD(lParam), (int)(int16_t)HIWORD(lParam), (int)(int16_t)HIWORD(wParam), (UINT)(int16_t)LOWORD(wParam)), 0L))
/*528*/ MSG_TRANS(WM_PARENTNOTIFY, 
	void, OnParentNotify, (UINT msg, HWND hwndChild, int idChild), (msg, hwndChild, idChild), 
	_SEND_((void), WM_PARENTNOTIFY, MAKEWPARAM(msg, idChild), (LPARAM)(hwndChild)), 
	((_CALL_(OnParentNotify))((UINT)LOWORD(wParam), (HWND)(lParam), (UINT)HIWORD(wParam)), 0L))
/*537*/ MSG_TRANS(WM_DEVICECHANGE, 
	bool, OnDeviceChange, (UINT uEvent, DWORD dwEventData), (uEvent, dwEventData), 
	_SEND_((bool)(DWORD), WM_DEVICECHANGE, (WPARAM)(UINT)(uEvent), (LPARAM)(DWORD)(dwEventData)), 
	(LRESULT)(DWORD)(bool)(_CALL_(OnDeviceChange))((UINT)(wParam), (DWORD)(lParam)))
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
	void, OnDropFiles, (HDROP hdrop), (hdrop), 
	_SEND_((void), WM_DROPFILES, (WPARAM)(HDROP)(hdrop), 0L), 
	((_CALL_(OnDropFiles))((HDROP)(wParam)), 0L))
/*675*/ MSG_TRANS(WM_MOUSELEAVE,
	void, OnMouseLeave, (), (), 
	_SEND_((void), WM_MOUSELEAVE, 0L, 0L),
	((_CALL_(OnMouseLeave))(), 0L))
/*768*/ MSG_TRANS(WM_CUT, 
	void, OnCut, (), (), 
	_SEND_((void), WM_CUT, 0L, 0L), 
	((_CALL_(OnCut))(), 0L))
/*769*/ MSG_TRANS(WM_COPY, 
	void, OnCopy, (), (), 
	_SEND_((void), WM_COPY, 0L, 0L), 
	((_CALL_(OnCopy))(), 0L))
/*770*/ MSG_TRANS(WM_PASTE, 
	void, OnPaste, (), (), 
	_SEND_((void), WM_PASTE, 0L, 0L), 
	((_CALL_(OnPaste))(), 0L))
/*771*/ MSG_TRANS(WM_CLEAR, 
	void, OnClear, (), (), 
	_SEND_((void), WM_CLEAR, 0L, 0L), 
	((_CALL_(OnClear))(), 0L))
/*772*/ MSG_TRANS(WM_UNDO, 
	void, OnUndo, (), (), 
	_SEND_((void), WM_UNDO, 0L, 0L), 
	((_CALL_(OnUndo))(), 0L))
/*773*/ MSG_TRANS(WM_RENDERFORMAT, 
	HANDLE, OnRenderFormat, (UINT fmt), (fmt), 
	_SEND_((HANDLE)(UINT_PTR), WM_RENDERFORMAT, (WPARAM)(UINT)(fmt), 0L), 
	(LRESULT)(UINT_PTR)(HANDLE)(_CALL_(OnRenderFormat))((UINT)(wParam)))
/*774*/ MSG_TRANS(WM_RENDERALLFORMATS, 
	void, OnRenderAllFormats, (), (), 
	_SEND_((void), WM_RENDERALLFORMATS, 0L, 0L), 
	((_CALL_(OnRenderAllFormats))(), 0L))
/*775*/ MSG_TRANS(WM_DESTROYCLIPBOARD, 
	void, OnDestroyClipboard, (), (), 
	_SEND_((void), WM_DESTROYCLIPBOARD, 0L, 0L), 
	((_CALL_(OnDestroyClipboard))(), 0L))
/*776*/ MSG_TRANS(WM_DRAWCLIPBOARD, 
	void, OnDrawClipboard, (), (), 
	_SEND_((void), WM_DRAWCLIPBOARD, 0L, 0L), 
	((_CALL_(OnDrawClipboard))(), 0L))
/*777*/ MSG_TRANS(WM_PAINTCLIPBOARD, 
	void, OnPaintClipboard, (HWND hwndCBViewer, const LPPAINTSTRUCT lpPaintStruct), (hwndCBViewer, lpPaintStruct), 
	_SEND_((void), WM_PAINTCLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), (LPARAM)(LPPAINTSTRUCT)(lpPaintStruct)), 
	((_CALL_(OnPaintClipboard))((HWND)(wParam), (const LPPAINTSTRUCT)GlobalLock((HGLOBAL)(lParam))), GlobalUnlock((HGLOBAL)(lParam)), 0L))
/*778*/ MSG_TRANS(WM_VSCROLLCLIPBOARD, 
	void, OnVScrollClipboard, (HWND hwndCBViewer, UINT code, int pos), (hwndCBViewer, code, pos), 
	_SEND_((void), WM_VSCROLLCLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), MAKELPARAM((code), (pos))), 
	((_CALL_(OnVScrollClipboard))((HWND)(wParam), (UINT)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*779*/ MSG_TRANS(WM_SIZECLIPBOARD, 
	void, OnSizeClipboard, (HWND hwndCBViewer, const LPRECT lprc), (hwndCBViewer, lprc), 
	_SEND_((void), WM_SIZECLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), (LPARAM)(LPRECT)(lprc)), 
	((_CALL_(OnSizeClipboard))((HWND)(wParam), (const LPRECT)GlobalLock((HGLOBAL)(lParam))), GlobalUnlock((HGLOBAL)(lParam)), 0L))
/*780*/ MSG_TRANS(WM_ASKCBFORMATNAME, 
	void, OnAskCBFormatName, (int cchMax, LPTSTR rgchName), (cchMax, rgchName), 
	_SEND_((void), WM_ASKCBFORMATNAME, (WPARAM)(int)(cchMax), (LPARAM)(rgchName)), 
	((_CALL_(OnAskCBFormatName))((int)(wParam), (LPTSTR)(lParam)), 0L))
/*781*/ MSG_TRANS(WM_CHANGECBCHAIN, 
	void, OnChangeCBChain, (HWND hwndRemove, HWND hwndNext), (hwndRemove, hwndNext), 
	_SEND_((void), WM_CHANGECBCHAIN, (WPARAM)(HWND)(hwndRemove), (LPARAM)(HWND)(hwndNext)), 
	((_CALL_(OnChangeCBChain))((HWND)(wParam), (HWND)(lParam)), 0L))
/*782*/ MSG_TRANS(WM_HSCROLLCLIPBOARD, 
	void, OnHScrollClipboard, (HWND hwndCBViewer, UINT code, int pos), (hwndCBViewer, code, pos), 
	_SEND_((void), WM_HSCROLLCLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), MAKELPARAM((code), (pos))), 
	((_CALL_(OnHScrollClipboard))((HWND)(wParam), (UINT)LOWORD(lParam), (int)(int16_t)HIWORD(lParam)), 0L))
/*783*/ MSG_TRANS(WM_QUERYNEWPALETTE, 
	bool, OnQueryNewPalette, (), (), 
	_SEND_((bool)(DWORD), WM_QUERYNEWPALETTE, 0L, 0L), 
	MAKELRESULT((bool)(_CALL_(OnQueryNewPalette))(), 0L))
/*784*/ MSG_TRANS(WM_PALETTEISCHANGING, 
	void, OnPaletteIsChanging, (HWND hwndPaletteChange), (hwndPaletteChange), 
	_SEND_((void), WM_PALETTEISCHANGING, (WPARAM)(HWND)(hwndPaletteChange), 0L), 
	((_CALL_(OnPaletteIsChanging))((HWND)(wParam)), 0L))
/*785*/ MSG_TRANS(WM_PALETTECHANGED, 
	void, OnPaletteChanged, (HWND hwndPaletteChange), (hwndPaletteChange), 
	_SEND_((void), WM_PALETTECHANGED, (WPARAM)(HWND)(hwndPaletteChange), 0L), 
	((_CALL_(OnPaletteChanged))((HWND)(wParam)), 0L))
/*786*/ MSG_TRANS(WM_HOTKEY, 
	void, OnHotKey, (int idHotKey, UINT fuModifiers, UINT vk), (idHotKey, fuModifiers, vk), 
	_SEND_((void), WM_HOTKEY, (WPARAM)(idHotKey), MAKELPARAM((fuModifiers), (vk))), 
	((_CALL_(OnHotKey))((int)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L))

#undef MSG_TRANS
#undef _CALL_
#undef _SEND_
