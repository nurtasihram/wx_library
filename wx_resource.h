#pragma once

#include <vector>

#include "wx_file.h"
#include "wx_gdi.h"

namespace WX {

#pragma region Icon
struct IconInfo : public RefStruct<ICONINFO> {
	using super = RefStruct<ICONINFO>;
public:
	IconInfo(bool fIcon = true) reflect_to(self->fIcon = fIcon);
	IconInfo(const ICONINFO &i) : super(i) {}
	~IconInfo() {
		if (self->hbmMask)
			Bitmap::Attach(self->hbmMask).Delete();
		if (self->hbmColor)
			Bitmap::Attach(self->hbmColor).Delete();
	}
public: // Property - Hotspot
	/* W */ inline auto &Hotspot(LPoint s) reflect_to_self(self->xHotspot = s.x, self->yHotspot = s.y);
	/* R */ inline LPoint Hotspot() const reflect_as({ (long)self->xHotspot, (long)self->yHotspot });
public: // Property - Masks
	/* W */ inline auto &Mask(HBITMAP hbmMask) reflect_to_self(self->hbmMask = hbmMask);
	/* R */ inline Bitmap &Mask() const reflect_as(Bitmap::Attach(const_cast<HBITMAP &>(self->hbmMask)));
public: // Property - Colors
	/* W */ inline auto &Colors(HBITMAP hbmColor) reflect_to_self(self->hbmColor = hbmColor);
	/* R */ inline Bitmap &Colors() const reflect_as(Bitmap::Attach(const_cast<HBITMAP &>(self->hbmColor)));
};
using CIconInfo = RefAs<IconInfo>;
class IconInfoEx : public RefStruct<ICONINFOEX> {
	using super = RefStruct<ICONINFOEX>;
public:
	IconInfoEx() reflect_to(self->cbSize = sizeof(self); self->fIcon = true);
	IconInfoEx(const ICONINFOEX &i) : super(i) {}
	~IconInfoEx() {
		if (self->hbmMask)
			Bitmap::Attach(self->hbmMask).Delete();
		if (self->hbmColor)
			Bitmap::Attach(self->hbmColor).Delete();
	}
public: // Property - Hotspot
	/* W */ inline auto &Hotspot(LSize s) reflect_to_self(self->xHotspot = s.cx, self->yHotspot = s.cy);
	/* R */ inline LSize Hotspot() const reflect_as({ (long)self->xHotspot, (long)self->yHotspot });
public: // Property - Masks
	/* W */ inline auto   &Masks(HBITMAP hbmMask) reflect_to_self(self->hbmMask = hbmMask);
	/* R */ inline Bitmap &Masks() const reflect_as(Bitmap::Attach(const_cast<HBITMAP &>(self->hbmMask)));
public: // Property - Colors
	/* W */ inline auto   &Colors(HBITMAP hbmColor) reflect_to_self(self->hbmColor = hbmColor);
	/* R */ inline Bitmap &Colors() const reflect_as(Bitmap::Attach(const_cast<HBITMAP &>(self->hbmColor)));
public: // Property - ResourceID
	/* W */ inline auto &ResourceID(WORD wResID) reflect_to_self(self->wResID = wResID);
	/* R */ inline WORD  ResourceID() const reflect_as(self->wResID);
public: // Property - ModuleName
	//	WCHAR   szModName[MAX_PATH];
	/* R */ inline const String ModuleName() const reflect_as(CString(self->szModName, std::size(self->szModName)));
public: // Property - ResourceName
	//	WCHAR   szResName[MAX_PATH];
	/* R */ inline const String ResourceName() const reflect_as(CString(self->szResName, std::size(self->szResName)));
};
class Icon {
public:
	using Info = IconInfo;
	using InfoEx = IconInfoEx;
protected:
	friend union RefAs<Icon>;
	mutable HICON hIcon = O;
	Icon(HICON h) : hIcon(h) {}
	Icon(const Icon &i) : hIcon(i.hIcon) reflect_to(i.hIcon = O);
public:
	Icon() {}
	Icon(Null) {}
	Icon(Icon &i) : hIcon(i.hIcon) reflect_to(i.hIcon = O);
	Icon(Icon &&i) : hIcon(i.hIcon) reflect_to(i.hIcon = O);
	~Icon() reflect_to(Destroy());
public:
	class CreateStruct {
		HINSTANCE hInstance = GetModuleHandle(O);
		int nWidth, nHeight;
		BYTE nPlanes = 1, nBitsPerPixel = 32;
		LPCBYTE lpANDbits = O, lpXORbits = O;
	public:
		CreateStruct(LPCBYTE lpANDbits, LPCBYTE lpXORbits) :
			lpANDbits(lpANDbits), lpXORbits(lpXORbits) {}
	public: // Property - Module
		/* W */ inline auto &Module(HINSTANCE hInstance) reflect_to_self(this->hInstance = hInstance);
//		/* R */ inline WX::Module Module() reflect_as(this->hInstance);
	public: // Property - Width
		/* W */ inline auto &Width(LONG nWidth) reflect_to_self(this->nWidth = nWidth);
		/* R */ inline LONG  Width() const reflect_as(this->nWidth);
	public: // Property - Height
		/* W */ inline auto &Height(LONG nHeight) reflect_to_self(this->nHeight = nHeight);
		/* R */ inline LONG  Height() const reflect_as(this->nHeight);
	public: // Property - Size
		/* W */ inline auto &Size(LSize sz) reflect_to_self(this->nWidth = sz.cx, this->nHeight = sz.cy);
		/* R */ inline LSize Size() const reflect_as({ this->nWidth, this->nHeight });
	public: // Property - Planes
		/* W */ inline auto &Planes(UINT nPlanes) reflect_to_self(this->nPlanes = nPlanes);
		/* R */ inline UINT  Planes() const reflect_as(this->nPlanes);
	public: // Property - BitsPerPixel
		/* W */ inline auto &BitsPerPixel(UINT nBitsPerPixel) reflect_to_self(this->nBitsPerPixel = nBitsPerPixel);
		/* R */ inline UINT  BitsPerPixel() const reflect_as(this->nBitsPerPixel);
	public: // Property - Masks
		/* W */ inline auto   &Mask(LPCVOID lpBits) reflect_to_self(this->lpANDbits = (LPCBYTE)lpBits);
		/* R */ inline LPCBYTE Mask() const reflect_as(this->lpANDbits);
	public: // Property - Colors
		/* W */ inline auto   &Colors(LPCVOID lpBits) reflect_to_self(this->lpXORbits = (LPCBYTE)lpBits);
		/* R */ inline LPCBYTE Colors() const reflect_as(this->lpXORbits);
	public:
		inline Icon Create() const assertl_reflect_as(auto h = CreateIcon(hInstance, nWidth, nHeight, nPlanes, nBitsPerPixel, lpANDbits, lpXORbits), h);
	};
	static inline CreateStruct Create(LPCBYTE lpANDbits, LPCBYTE lpXORbits = O) reflect_as({ lpANDbits, lpXORbits });
	static inline Icon Create(HBITMAP hbmColor, HBITMAP hbmMask = O) assertl_reflect_as(auto h = CreateIconIndirect(&CIconInfo(IconInfo())->Colors(hbmColor).Mask(hbmMask)), h);
	inline void Destroy() {
		if (self)
			assertl(DestroyIcon(hIcon));
		hIcon = O;
	}
#pragma region Properties
public: // Property - Info
	/* R */ inline Info Informations() const assertl_reflect_to(ICONINFO i, GetIconInfo(hIcon, &i), i);
public: // Property - InfoEx
	/* R */ inline InfoEx InformationsEx() const assertl_reflect_to(ICONINFOEX i, GetIconInfoEx(hIcon, &i), i);
public: // Property - Masks
	/* R */ inline Bitmap Mask() const reflect_as(Informations().Mask());
public: // Property - Colors
	/* R */ inline Bitmap Colors() const reflect_as(Informations().Colors());
#pragma endregion
public:
	inline operator HICON() const reflect_as(hIcon);
	inline Icon operator+() const assertl_reflect_as(auto h = CopyIcon(hIcon), h);
	inline auto &operator=(Icon &i) reflect_to_self(std::swap(hIcon, i.hIcon));
	inline auto &operator=(Icon &&i) reflect_to_self(std::swap(hIcon, i.hIcon));
	inline auto &operator=(const Icon &i) const reflect_to_self(std::swap(hIcon, i.hIcon));
public:
	static inline Icon &Attach(HICON &hIcon) reflect_as(ref_as<Icon>(hIcon));
	static inline const Icon &Attach(const HICON &hIcon) reflect_as(ref_as<const Icon>(hIcon));
};
using CIcon = RefAs<Icon>;
#pragma endregion

#pragma region Cursor
class Cursor : public Icon {
public:
	using super = Icon;
protected:
	friend union RefAs<Cursor>;
	Cursor(HCURSOR h) : super((HICON)h) {}
	Cursor(const Cursor &c) : Icon(c) {}
public:
	Cursor() {}
	Cursor(Null) {}
	Cursor(Cursor &i) : super(i) {}
	Cursor(Cursor &&i) : super(i) {}
	~Cursor() reflect_to(Destroy());
public:
	class CreateStruct {
		HINSTANCE hInstance = GetModuleHandle(O);
		int nWidth = 0, nHeight = 0, xHotspot = 0, yHotspot = 0;
		LPCBYTE lpANDbits, lpXORbits;
	public:
		CreateStruct(LPCBYTE lpANDbits, LPCBYTE lpXORbits, LPoint Hotspot) :
			xHotspot(Hotspot.x), yHotspot(Hotspot.y), lpANDbits(lpANDbits), lpXORbits(lpXORbits) {}
	public:
		inline auto &Module(HINSTANCE hInstance) reflect_to_self(this->hInstance = hInstance);
		inline auto &Hotspot(LSize s) reflect_to_self(this->xHotspot = s.cx, this->yHotspot = s.cy);
		inline auto &Width(LONG nWidth) reflect_to_self(this->nWidth = nWidth);
		inline auto &Height(LONG nHeight) reflect_to_self(this->nHeight = nHeight);
		inline auto &Size(LSize sz) reflect_to_self(this->nWidth = sz.cx, this->nHeight = sz.cy);
	public:
		inline Cursor Create() const assertl_reflect_as(auto h = CreateCursor(hInstance, xHotspot, yHotspot, nWidth, nHeight, lpANDbits, lpXORbits), h);
		inline operator Cursor() const reflect_as(Create());
	};
	static inline CreateStruct Create(LPCBYTE lpANDbits, LPCBYTE lpXORbits = O, LPoint Hotspot = 0) reflect_as({ lpANDbits, lpXORbits, Hotspot });
	static inline Cursor Create(HBITMAP hbmColor, HBITMAP hbmMask = O, LPoint Hotspot = 0) assertl_reflect_as(auto h = CreateIconIndirect(&CIconInfo(IconInfo())->Colors(hbmColor).Mask(hbmMask)), h);
	inline void Destroy() {
		if (self) {
			assertl(DestroyCursor(super::hIcon));
			super::hIcon = O;
		}
	}
#pragma region Properties
public: // Property - Hotspot
	/* R */ inline LPoint Hotspot() const reflect_as(Informations().Hotspot());
#pragma endregion
	inline operator HCURSOR() const reflect_as((HCURSOR)super::hIcon);
	inline Cursor operator+() const assertl_reflect_as(auto h = CopyCursor(super::hIcon), h);
	inline auto &operator=(Cursor &i) reflect_to_self(std::swap(hIcon, i.hIcon));
	inline auto &operator=(Cursor &&i) reflect_to_self(std::swap(hIcon, i.hIcon));
	inline auto &operator=(const Cursor &i) const reflect_to_self(std::swap(hIcon, i.hIcon));
public:
	static inline Cursor &Attach(HCURSOR &hCursor) reflect_as(ref_as<Cursor>(hCursor));
	static inline const Cursor &Attach(const HCURSOR &hCursor) reflect_as(ref_as<const Cursor>(hCursor));
};
using CCursor = RefAs<Cursor>;
#pragma endregion

#pragma region Menu
class Menu;
using CMenu = RefAs<Menu>;
//enum_class(MenuBmp, HBITMAP,
//	Callback      = HBMMENU_CALLBACK,
//	System        = HBMMENU_SYSTEM,
//	BarRestore    = HBMMENU_MBAR_RESTORE,
//	BarMinimize   = HBMMENU_MBAR_MINIMIZE,
//	BarClose      = HBMMENU_MBAR_CLOSE,
//	BarCloseD     = HBMMENU_MBAR_CLOSE_D,
//	BarMinimizeD  = HBMMENU_MBAR_MINIMIZE_D,
//	PopupClose    = HBMMENU_POPUP_CLOSE,
//	PopupRestore  = HBMMENU_POPUP_RESTORE,
//	PopupMaximize = HBMMENU_POPUP_MAXIMIZE,
//	PopupMinimize = HBMMENU_POPUP_MINIMIZE);
enum_flags(MenuItemType, UINT,
	String        = MFT_STRING,
	Bitmap        = MFT_BITMAP,
	BarBreak      = MFT_MENUBARBREAK,
	Break         = MFT_MENUBREAK,
	OwnerDraw     = MFT_OWNERDRAW,
	RadioCheck    = MFT_RADIOCHECK,
	Separator     = MFT_SEPARATOR,
	RightOrder    = MFT_RIGHTORDER,
	RightJustify  = MFT_RIGHTJUSTIFY);
enum_flags(MenuItemState, UINT,
	Default       = MFS_DEFAULT,
	Grayed        = MFS_GRAYED,
	Enabled       = MFS_ENABLED,
	Disabled      = MFS_DISABLED,
	Checked       = MFS_CHECKED,
	Unchecked     = MFS_UNCHECKED,
	Hilite        = MFS_HILITE,
	Unhilite      = MFS_UNHILITE);
enum_flags(MenuStyle, DWORD,
	NoCheck       = MNS_NOCHECK,
	Modeless      = MNS_MODELESS,
	DragDrop      = MNS_DRAGDROP,
	AutoDismiss   = MNS_AUTODISMISS,
	NotifyByPos   = MNS_NOTIFYBYPOS,
	CheckOrBmp    = MNS_CHECKORBMP);
class MenuItem {
	friend class Menu;
	HMENU hMenu;
	UINT uID, flags;
	MenuItem(HMENU hMenu, UINT uID, UINT flags) :
		hMenu(hMenu), uID(uID), flags(flags) {}
	using Type = MenuItemType;
	using State = MenuItemState;
public:
	inline void Delete(UINT uID) assertl(DeleteMenu(hMenu, uID, flags) || (flags = 0));
	inline void Remove(UINT uID) assertl(RemoveMenu(hMenu, uID, flags) || (flags = 0));
	inline auto&Hilite(HWND hWnd, bool bHilite = true) assertl_reflect_as_self(HiliteMenuItem(hWnd, hMenu, uID, flags | (bHilite ? MF_HILITE : MF_UNHILITE)));
	CMenu Sub(int nPos);
public: // Property - Enable
	/* W */ inline auto &Enable(bool bEnable) assertl_reflect_as_self(EnableMenuItem(hMenu, uID, flags | (bEnable ? MF_ENABLED : (MF_DISABLED | MF_GRAYED))) >= 0);
public: // Property - Check
	/* W */ inline auto &Check(bool bChecked) assertl_reflect_as_self(CheckMenuItem(hMenu, uID, flags | (bChecked ? MF_CHECKED : MF_UNCHECKED)) >= 0);
};
class Menu {
public:
	using Item = MenuItem;
	using Style = MenuStyle;
protected:
	friend union RefAs<Menu>;
	mutable HMENU hMenu = O;
	Menu(HMENU h) : hMenu(h) {}
	Menu(const Menu &m) : hMenu(m.hMenu) reflect_to(m.hMenu = O);
public:
	Menu() : Menu(Create()) {}
	Menu(Null) {}
	Menu(Menu &m) : hMenu(m) reflect_to(m.hMenu = O);
	Menu(Menu &&m) : hMenu(m) reflect_to(m.hMenu = O);
	~Menu() reflect_to(Destroy());
public:
	static inline Menu Create()      assertl_reflect_as(auto h = CreateMenu(), h);
	static inline Menu CreatePopup() assertl_reflect_as(auto h = CreatePopupMenu(), h);
	inline void Destroy() {
		if (self)
			assertl(DestroyMenu(hMenu));
		hMenu = O;
	}
public:
	inline auto&String(LPCSTR lpString, UINT_PTR uID = 0, bool bEnable = true) assertl_reflect_as_self(AppendMenuA(hMenu, MF_STRING | (bEnable ? MF_ENABLED : (MF_DISABLED | MF_GRAYED)), uID, lpString));
	inline auto&String(LPCWSTR lpString, UINT_PTR uID = 0, bool bEnable = true) assertl_reflect_as_self(AppendMenuW(hMenu, MF_STRING | (bEnable ? MF_ENABLED : (MF_DISABLED | MF_GRAYED)), uID, lpString));
	inline auto&Popup(LPCSTR lpString, HMENU hPopup, bool bEnable = true) assertl_reflect_as_self(AppendMenuA(hMenu, MF_POPUP | (bEnable ? MF_ENABLED : (MF_DISABLED | MF_GRAYED)), (UINT_PTR)hPopup, lpString));
	inline auto&Popup(LPCWSTR lpString, HMENU hPopup, bool bEnable = true) assertl_reflect_as_self(AppendMenuW(hMenu, MF_POPUP | (bEnable ? MF_ENABLED : (MF_DISABLED | MF_GRAYED)), (UINT_PTR)hPopup, lpString));
	inline auto&Check(LPCSTR lpString, UINT_PTR uID = 0, bool bChecked = false, bool bEnable = true) assertl_reflect_as_self(AppendMenuA(hMenu, (bChecked ? MF_CHECKED : MF_UNCHECKED) | (bEnable ? MF_ENABLED : (MF_DISABLED | MF_GRAYED)), uID, lpString));
	inline auto&Check(LPCWSTR lpString, UINT_PTR uID = 0, bool bChecked = false, bool bEnable = true) assertl_reflect_as_self(AppendMenuW(hMenu, (bChecked ? MF_CHECKED : MF_UNCHECKED) | (bEnable ? MF_ENABLED : (MF_DISABLED | MF_GRAYED)), uID, lpString));
	inline auto&Separator() assertl_reflect_as_self(AppendMenu(hMenu, MF_SEPARATOR, 0, O));

	inline auto&String(UINT uPosition, LPCTSTR lpString, UINT_PTR uID = 0, bool bEnable = true) assertl_reflect_as_self(InsertMenu(hMenu, uPosition, MF_STRING | (bEnable ? MF_ENABLED : MF_DISABLED), uID, lpString));
	inline auto&Popup(UINT uPosition, LPCTSTR lpString, HMENU hPopup) assertl_reflect_as_self(InsertMenu(hMenu, uPosition, MF_POPUP, (UINT_PTR)hPopup, lpString));
	inline auto&Check(UINT uPosition, LPCTSTR lpString, UINT_PTR uID = 0, bool bChecked = false) assertl_reflect_as_self(InsertMenu(hMenu, uPosition, (bChecked ? MF_CHECKED : MF_UNCHECKED), uID, lpString));
	inline auto&Separator(UINT uPosition) assertl_reflect_as_self(InsertMenu(hMenu, uPosition, MF_SEPARATOR, 0, O));

	inline auto&Radio(UINT idFirst, UINT idLast, UINT idCheck) assertl_reflect_as_self(CheckMenuRadioItem(hMenu, idFirst, idLast, idCheck, MF_BYCOMMAND));
	inline auto&RadioIndex(UINT indFirst, UINT indLast, UINT indCheck) assertl_reflect_as_self(CheckMenuRadioItem(hMenu, indFirst, indLast, indCheck, MF_BYPOSITION));
public:	
	enum_flags(Tracks, UINT,
		LeftButton          = TPM_LEFTBUTTON,
		RightButton         = TPM_RIGHTBUTTON,
		LeftAlign           = TPM_LEFTALIGN,
		CenterAlign         = TPM_CENTERALIGN,
		RightAlign          = TPM_RIGHTALIGN,
		TopAlign            = TPM_TOPALIGN,
		VCenterAlign        = TPM_VCENTERALIGN,
		BottomAlign         = TPM_BOTTOMALIGN,
		Horizontal          = TPM_HORIZONTAL,
		Vertical            = TPM_VERTICAL,
		NoNotify            = TPM_NONOTIFY,
		ReturnCmd           = TPM_RETURNCMD,
		Recurse             = TPM_RECURSE,
		HorPosAnimation     = TPM_HORPOSANIMATION,
		HorNegAnimation     = TPM_HORNEGANIMATION,
		VerPosAnimation     = TPM_VERPOSANIMATION,
		VerNegAnimation     = TPM_VERNEGANIMATION,
		NoAnimation         = TPM_NOANIMATION,
		LayoutRtl           = TPM_LAYOUTRTL,
		WorkArea            = TPM_WORKAREA);
	inline bool Track(Tracks tt, POINT pt, HWND hParent) const reflect_as(TrackPopupMenu(hMenu, tt.yield(), pt.x, pt.y, 0, hParent, O));

	//inline auto Modify(UINT uID) reflect_as(ModifyMenu(hMenu, uID, MF_BYCOMMAND, ));

#pragma region Properties
public: // Property - ItemCount
	inline auto ItemCount() const reflect_as(GetMenuItemCount(hMenu));
#pragma endregion
public:
	inline operator bool() const reflect_as(IsMenu(hMenu));
	inline operator HMENU() const reflect_as(hMenu);
	inline operator LPARAM() const reflect_as((LPARAM)hMenu);
	inline Item operator[](UINT ind) reflect_as({ hMenu, ind, MF_BYPOSITION });
	inline const Item operator[](UINT ind) const reflect_as({ hMenu, ind, MF_BYPOSITION });
	inline Item operator()(UINT ind) reflect_as({ hMenu, ind, MF_BYCOMMAND });
	inline const Item operator()(UINT ind) const reflect_as({ hMenu, ind, MF_BYCOMMAND });
	inline auto &operator=(Menu &m) reflect_to_self(std::swap(hMenu, m.hMenu));
	inline auto &operator=(const Menu &m) const reflect_to_self(std::swap(hMenu, m.hMenu));
public:
	static inline Menu &Attach(HMENU &hMenu) reflect_as(ref_as<Menu>(hMenu));
	static inline const Menu &Attach(const HMENU &hMenu) reflect_as(ref_as<const Menu>(hMenu));
};
inline CMenu MenuItem::Sub(int nPos) reflect_as({ GetSubMenu(hMenu, nPos) });
static inline Menu MenuPopup() reflect_as(Menu::CreatePopup());
#undef MENUITEM_PROPERTY
#pragma endregion

#pragma region Module
class Module {
protected:
	friend union RefAs<Module>;
	mutable HINSTANCE hInst = O;
	Module(HINSTANCE h) : hInst(h) {}
	Module(const Module &m) : hInst(m.hInst) reflect_to(m.hInst = O);
public:
	Module() : hInst(GetModuleHandle(O)) {}
	Module(Null) {}
	Module(Module &m) : hInst(m) reflect_to(m.hInst = O);
	Module(Module &&m) : hInst(m) reflect_to(m.hInst = O);
	Module(LPCSTR lpModuleName) : hInst(Handle(lpModuleName)) {}
	Module(LPCWSTR lpModuleName) : hInst(Handle(lpModuleName)) {}
	~Module() reflect_to(Free());
public:
	template<class TCHAR>
	static inline Module Handle(const TCHAR *lpModuleName) {
		constexpr bool IsUnicode = IsCharW<TCHAR>;
		global_symbolx(GetModuleHandle);
		assertl_reflect_as(auto h = GetModuleHandle(lpModuleName), h);
	}
	template<class TCHAR>
	static inline Module Library(const TCHAR *lpLibFileName) {
		constexpr bool IsUnicode = IsCharW<TCHAR>;
		global_symbolx(LoadLibrary);
		assertl_reflect_as(auto h = LoadLibrary(lpLibFileName), h);
	}
//	static inline Module Load(LPCSTR lpModuleName, LPVOID lpParameterBlock = O) reflect_as(LoadModule(lpModuleName, lpParameterBlock));
public:
	inline void Free() {
		if (self)
			assertl(::FreeLibrary(hInst));
		hInst = O;
	}
public: // Property - Menu
	template<class TCHAR>
	/* R */ inline CMenu Menu(const TCHAR *lpszName) const {
		constexpr bool IsUnicode = IsCharW<TCHAR>;
		global_symbolx(LoadMenu);
		assertl_reflect_as(auto h = LoadMenu(self, lpszName), h);
	}
	/* R */ inline CMenu Menu(WORD wID) const reflect_as(LoadMenu(self, MAKEINTRESOURCE(wID)));
public: // Property - Bitmap
	template<class TCHAR>
	/* R */ inline CBitmap Bitmap(const TCHAR *lpszName) const {
		constexpr bool IsUnicode = IsCharW<TCHAR>;
		global_symbolx(LoadBitmap);
		assertl_reflect_as(auto h = LoadBitmap(self, lpszName), h);
	}
	inline CBitmap Bitmap(WORD wID) const reflect_as(LoadBitmap(self, MAKEINTRESOURCE(wID)));
public: // Property - Icon
	template<class TCHAR>
	/* R */ inline CIcon Icon(const TCHAR *lpszName) const {
		constexpr bool IsUnicode = IsCharW<TCHAR>;
		global_symbolx(LoadIcon);
		assertl_reflect_as(auto h = LoadIcon(self, lpszName), h);
	}
	inline CIcon Icon(WORD wID) const reflect_as(LoadIcon(self, MAKEINTRESOURCE(wID)));
public: // Property - Cursor
	template<class TCHAR>
	/* R */ inline CCursor Cursor(const TCHAR *lpszName) const {
		constexpr bool IsUnicode = IsCharW<TCHAR>;
		global_symbolx(LoadCursor);
		assertl_reflect_as(auto h = LoadCursor(self, lpszName), h);
	}
	inline CCursor Cursor(WORD wID) const reflect_as(LoadCursor(self, MAKEINTRESOURCE(wID)));
public: // Property - String
	template<bool IsUnicode = WX::IsUnicode>
	inline StringX<IsUnicode> String(WORD wID) const {
		if constexpr (IsUnicode)
			 return StringW(wID);
		else return StringA(wID);
	}
	inline WX::StringA StringA(WORD wID) const {
		auto len = (int)StringW(wID).Length();
		auto lpsz = StringA::Alloc(len);
		assertl((len = LoadStringA(self, wID, lpsz, len)) > 0);
		return{ (size_t)len, lpsz };
	}
	inline const WX::StringW StringW(WORD wID) const {
		LPCWSTR lpString = O;
		int len;
		assertl((len = LoadStringW(self, wID, (LPWSTR)&lpString, 0)) > 0);
		return CString(len, lpString);
	}
public: // Property - Procedure
	template<class AnyFunc>
	inline AnyFunc *Procedure(LPCSTR lpName) reflect_as((AnyFunc  *)::GetProcAddress(self, lpName));
public: // Property - FileName
	template<bool IsUnicode = WX::IsUnicode>
	/* R */ inline StringX<IsUnicode> FileName() const {
		global_symbolx(GetModuleFileName);
		auto lpsz = StringX<IsUnicode>::Alloc(MaxLenPath);
		int len;
		assertl((len = GetModuleFileName(self, lpsz, MaxLenPath)) > 0);
		StringX<IsUnicode>::Resize(lpsz, len);
		return { (size_t)len, lpsz };
	}
	/* R */ inline WX::StringA FileNameA() const reflect_as(FileName<false>());
	/* R */ inline WX::StringW FileNameW() const reflect_as(FileName<true>());
public:
	inline operator bool() const reflect_as(hInst);
	inline operator HINSTANCE() const reflect_as(hInst);
	inline operator LPARAM() const reflect_as((LPARAM)hInst);
	inline auto &operator=(Module &m) reflect_to_self(std::swap(hInst, m.hInst));
	inline auto &operator=(Module &&m) reflect_to_self(std::swap(hInst, m.hInst));
	inline auto &operator=(const Module &m) const reflect_to_self(std::swap(hInst, m.hInst));
public:
	static inline Module &Attach(HINSTANCE &hInst) reflect_as(ref_as<Module>(hInst));
	static inline const Module &Attach(const HINSTANCE &hInst) reflect_as(ref_as<const Module>(hInst));
};
using CModule = RefAs<Module>;
#pragma endregion

inline Bitmap ClipBitmap(const Bitmap &bmp, LRect rc) {
	auto &&size = rc.size();
	Bitmap nBmp = Bitmap::Create(size).BitsPerPixel(bmp.Log().BitsPerPixel());
	DC srcDC = DC::CreateCompatible(), dstDC = DC::CreateCompatible();
	srcDC.Select(nBmp);
	dstDC.Select(bmp);
	srcDC.BltBit(0, size, dstDC);
	return nBmp;
}

inline void SaveToFile(DC &dc, const Palette &pal, const Bitmap &bmp, File &file) {
	auto &&log = bmp.Log();
	bool usePal = log.BitsPerPixel() < 24 && pal;
	auto usage = usePal ? DIB_PAL_COLORS : DIB_RGB_COLORS;
	auto palSize = usePal ? (DWORD)std::min(pal.Size(), (size_t)4 << log.BitsPerPixel()) : 0;
	BitmapHeader header;
	header.Size(log.Size());
	header.Planes(log.Planes());
	header.BitsPerPixel(log.BitsPerPixel());
	assertl(GetDIBits(dc, bmp, 0, log.Height(), O, header, usage));
	header.PaletteSize(palSize);
	header.ColorsSize(header.SizeImage());
	assertl(file.Write(&header, sizeof(header) - 4) == sizeof(header) - 4);
	assertl(file.Write(pal.Entries().data(), palSize) == palSize);
	AutoPointer<Heap> hBits(header.SizeImage());
	assertl(GetDIBits(dc, bmp, 0, log.Height(), &hBits, header, usage));
	assertl(file.Write(&hBits, header.SizeImage()) == header.SizeImage());
}

inline void SaveToFile(DC &dc, const Palette &pal, const Bitmap &bmp, File &&file) reflect_to(SaveToFile(dc, pal, bmp, file));

}
