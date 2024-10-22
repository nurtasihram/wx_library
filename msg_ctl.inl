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
#	define _SEND_(msgid, wparam, lparam)
#endif

#if defined WX_BUTTON
#undef WX_BUTTON
/* U + 0 */ MSG_TRANS(WM_USER + BN_CLICKED,
	void, OnClicked, (), (),
	(void)_SEND_(WM_USER + BN_CLICKED, 0L, 0L),
	((_CALL_(OnClicked))(), 0L))
/* U + 1 */ MSG_TRANS(WM_USER + BN_PAINT,
	void, OnPainted, (), (),
	(void)_SEND_(WM_USER + BN_PAINT, 0L, 0L),
	((_CALL_(OnPainted))(), 0L))
/* U + 2 */ MSG_TRANS(WM_USER + BN_PUSHED,
	void, OnPushed, (), (),
	(void)_SEND_(WM_USER + BN_PUSHED, 0L, 0L),
	((_CALL_(OnPushed))(), 0L))
/* U + 3 */ MSG_TRANS(WM_USER + BN_UNPUSHED,
	void, OnUnpushed, (), (),
	(void)_SEND_(WM_USER + BN_UNPUSHED, 0L, 0L),
	((_CALL_(OnUnpushed))(), 0L))
/* U + 4 */ MSG_TRANS(WM_USER + BN_DISABLE,
	void, OnDisabled, (), (),
	(void)_SEND_(WM_USER + BN_DISABLE, 0L, 0L),
	((_CALL_(OnDisabled))(), 0L))
/* U + 5 */ MSG_TRANS(WM_USER + BN_DOUBLECLICKED,
	void, OnDoubleClicked, (), (),
	(void)_SEND_(WM_USER + BN_DOUBLECLICKED, 0L, 0L),
	((_CALL_(OnDoubleClicked))(), 0L))
/* U + 6 */ MSG_TRANS(WM_USER + BN_SETFOCUS,
	void, OnSetFocused, (), (),
	(void)_SEND_(WM_USER + BN_SETFOCUS, 0L, 0L),
	((_CALL_(OnSetFocused))(), 0L))
/* U + 7 */ MSG_TRANS(WM_USER + BN_KILLFOCUS,
	void, OnKillFocused, (), (),
	(void)_SEND_(WM_USER + BN_KILLFOCUS, 0L, 0L),
	((_CALL_(OnKillFocused))(), 0L))
#endif

#undef MSG_TRANS
#undef _CALL_
#undef _SEND_
