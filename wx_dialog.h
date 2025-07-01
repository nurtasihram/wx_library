#pragma once

#include <string>
#include <vector>

#include "wx_window.h"

namespace WX {

enum_flags(ChooserColorStyle, DWORD,
	InitRGB              = CC_RGBINIT,
	FullOpen             = CC_FULLOPEN,
	PreventFullOpen      = CC_PREVENTFULLOPEN,
	ShowHelp             = CC_SHOWHELP,
	EnableHook           = CC_ENABLEHOOK,
	EnableTemplate       = CC_ENABLETEMPLATE,
	EnableTemplateHandle = CC_ENABLETEMPLATEHANDLE,
	SolidColor           = CC_SOLIDCOLOR,
	AnyColor             = CC_ANYCOLOR);
template<bool IsUnicode>
class ChooserColorT : public RefStruct<std::conditional_t<IsUnicode, CHOOSECOLORW, CHOOSECOLORA>> {
	using LPCTSTR = LPCXSTR<IsUnicode>;
public:
	using Style = ChooserColorStyle;
	using ColorSet = arrayof<RGBColor, 16>;
	using CColorSet = const arrayof<RGBColor, 16>;
public:
	ChooserColorT() reflect_to(self->lStructSize = sizeof(CHOOSECOLOR));
public: // Properties
	/* W */ inline auto &Parent(HWND hWnd) reflect_to_self(self->hwndOwner = hWnd);
	/* W */ inline auto &Module(HINSTANCE hMod) reflect_to_self(self->hInstance = (HWND &)hMod);
	/* W */ inline auto &Styles(Style style) reflect_to_self(self->Flags = style.yield());
	/* W */ inline auto &TemplateName(LPCTSTR lpTemplateName) reflect_to_self(self->lpTemplateName = lpTemplateName);
	/* W */ inline auto &CustColors(ColorSet *lpCustColors) reflect_to_self(self->lpCustColors = (COLORREF *)lpCustColors);
	/* R */ inline CColorSet *CustColors() const reflect_as((CColorSet *)self->lpCustColors);
	/* W */ inline auto &Result(COLORREF rgb) reflect_to_self(self->rgbResult = rgb);
	/* R */ inline RGBColor Result() const reflect_as(self->rgbResult);
//	LPARAM       lCustData;
//	LPCCHOOKPROC lpfnHook;
//	LPEDITMENU   lpEditInfo;
public:
	inline bool Choose() {
		if constexpr (IsUnicode)
			reflect_as(ChooseColorW(self))
		else
			reflect_as(ChooseColorA(self))
	}
};
using ChooserColor = ChooserColorT<IsUnicode>;
using ChooserColorA = ChooserColorT<false>;
using ChooserColorW = ChooserColorT<true>;

enum_flags(ChooserFontStyle, DWORD,
	ScreenFonts          = CF_SCREENFONTS,
	PrinterFonts         = CF_PRINTERFONTS,
	ShowHelp             = CF_SHOWHELP,
	EnableHook           = CF_ENABLEHOOK,
	EnableTemplate       = CF_ENABLETEMPLATE,
	EnableTemplateHandle = CF_ENABLETEMPLATEHANDLE,
	InitTologFontStruct  = CF_INITTOLOGFONTSTRUCT,
	UseStyle             = CF_USESTYLE,
	Effects              = CF_EFFECTS,
	Apply                = CF_APPLY,
	Ansionly             = CF_ANSIONLY,
	NoVectorFonts        = CF_NOVECTORFONTS,
	NoSimulations        = CF_NOSIMULATIONS,
	LimitSize            = CF_LIMITSIZE,
	FixedPitchOnly       = CF_FIXEDPITCHONLY,
	WYSIWYG              = CF_WYSIWYG,
	ForceFontExist       = CF_FORCEFONTEXIST,
	ScalableOnly         = CF_SCALABLEONLY,
	TTOnly               = CF_TTONLY,
	NoFaceSel            = CF_NOFACESEL,
	NoStyleSel           = CF_NOSTYLESEL,
	NoSizeSel            = CF_NOSIZESEL,
	SelectScript         = CF_SELECTSCRIPT,
	NoScriptSel          = CF_NOSCRIPTSEL,
	NoVertFonts          = CF_NOVERTFONTS,
	InActiveFonts        = CF_INACTIVEFONTS);
template<bool IsUnicode>
class ChooserFontT : public RefStruct<std::conditional_t<IsUnicode, CHOOSEFONTW, CHOOSEFONTA>> {
	using LPCTSTR = LPCXSTR<IsUnicode>;
protected:
	FontLogicT<IsUnicode> crLogFont;
public:
	using Style = ChooserFontStyle;
public:
	ChooserFontT() reflect_to(self->lStructSize = sizeof(CHOOSEFONT));
public: // Properties
	/* W */ inline auto &Parent(HWND hWnd) reflect_to_self(self->hwndOwner = hWnd);
	/* W */ inline auto &Module(HINSTANCE hMod) reflect_to_self(self->hInstance = hMod);
	/* W */ inline auto &Styles(Style style) reflect_to_self(self->Flags = style.yield());
	/* W */ inline auto &TemplateName(LPCTSTR lpTemplateName) reflect_to_self(self->lpTemplateName = lpTemplateName);
	/* W */ inline auto    &FontTypes(FontType ft) reflect_to_self(self->nFontType = ft.yield());
	/* R */ inline FontType FontTypes() const reflect_as(reuse_as<FontType>(self->nFontType));
	/* W */ inline auto &SizeMin(INT nSizeMin) reflect_to_self(self->nSizeMin = nSizeMin);
	/* R */ inline INT   SizeMin() const reflect_as(self->nSizeMin);
	/* W */ inline auto &SizeMax(INT nSizeMax) reflect_to_self(self->nSizeMax = nSizeMax);
	/* R */ inline INT   SizeMax() const reflect_as(self->nSizeMax);
	/* W */ inline auto &PointSize(INT iPointSize) reflect_to_self(self->iPointSize = iPointSize);
	/* R */ inline INT   PointSize() const reflect_as(self->iPointSize);
	/* W */ inline auto    &Color(COLORREF rgbColors) reflect_to_self(self->rgbColors = rgbColors);
	/* R */ inline RGBColor Color() const reflect_as(self->rgbColors);
	// LPCFHOOKPROC    lpfnHook;
	// LPARAM          lCustData;
	// HDC             hDC;
	// LPWSTR          lpszStyle;
	/* R */ inline auto &LogFont() reflect_as(crLogFont);
	/* R */ inline auto &LogFont() const reflect_as(crLogFont);
public:
	inline bool Choose() {
		if constexpr (IsUnicode)
			reflect_as(ChooseFontW(self))
		else
			reflect_as(ChooseFontA(self))
	}
};
using ChooserFont = ChooserFontT<IsUnicode>;
using ChooserFontA = ChooserFontT<false>;
using ChooserFontW = ChooserFontT<true>;

enum_flags(ChooserFileStyle, DWORD,
	ReadOnly             = OFN_READONLY,
	OverwritePrompt      = OFN_OVERWRITEPROMPT,
	HideReadOnly         = OFN_HIDEREADONLY,
	NoChangeDir          = OFN_NOCHANGEDIR,
	ShowHelp             = OFN_SHOWHELP,
	EnableHook           = OFN_ENABLEHOOK,
	EnableTemplate       = OFN_ENABLETEMPLATE,
	EnableTemplateHandle = OFN_ENABLETEMPLATEHANDLE,
	NoValidate           = OFN_NOVALIDATE,
	AllowMultiSelect     = OFN_ALLOWMULTISELECT,
	ExtensionDifferent   = OFN_EXTENSIONDIFFERENT,
	PathMustExist        = OFN_PATHMUSTEXIST,
	FileMustExist        = OFN_FILEMUSTEXIST,
	CreatePrompt         = OFN_CREATEPROMPT,
	ShareAware           = OFN_SHAREAWARE,
	NoReadOnlyReturn     = OFN_NOREADONLYRETURN,
	NoTestFileCreate     = OFN_NOTESTFILECREATE,
	NoNetworkButton      = OFN_NONETWORKBUTTON,
	NoLongNames          = OFN_NOLONGNAMES,
	Explorer             = OFN_EXPLORER,
	NodeReferenceLinks   = OFN_NODEREFERENCELINKS,
	LongNames            = OFN_LONGNAMES,
	EnableIncludeNotify  = OFN_ENABLEINCLUDENOTIFY,
	EnableSizing         = OFN_ENABLESIZING,
	DontAddToRecent      = OFN_DONTADDTORECENT,
	ForcesHowHidden      = OFN_FORCESHOWHIDDEN);
template<bool IsUnicode>
class ChooserFileT : public RefStruct<std::conditional_t<IsUnicode, OPENFILENAMEW, OPENFILENAMEA>> {
	using LPTSTR = LPXSTR<IsUnicode>;
	using LPCTSTR = LPCXSTR<IsUnicode>;
	using TCHAR = XCHAR<IsUnicode>;
	using String = StringBase<TCHAR>;
public:
	using Style = ChooserFileStyle;
	using String = StringBase<TCHAR>;
public:
	ChooserFileT() reflect_to(self->lStructSize = sizeof(OPENFILENAME));
public: // Property - Parent
	/* W */ inline auto &Parent(HWND hWnd) reflect_to_self(self->hwndOwner = hWnd);
public: // Property - Module
	/* W */ inline auto &Module(HINSTANCE hMod) reflect_to_self(self->hInstance = hMod);
public: // Property - Styles
	/* W */ inline auto &Styles(Style Flags) reflect_to_self(self->Flags = Flags.yield());
public: // Property - TemplateName
	/* W */ inline auto &TemplateName(LPCTSTR lpTemplateName) reflect_to_self(self->lpTemplateName = lpTemplateName);
public: // Property - FileOffset
	/* R */ inline WORD FileOffset() const reflect_as(self->nFileOffset);
public: // Property - FileExtension
	/* R */ inline WORD FileExtension() const reflect_as(self->nFileExtension);
public: // Property - File
	/* W */ inline auto &File(LPTSTR lpstrFile) reflect_to_self(self->lpstrFile = lpstrFile);
	/* R */ inline const String File() const reflect_as(CString(self->lpstrFile, self->nMaxFile));
public: // Property - FileMaxLen
	/* W */ inline auto &FileMaxLen(DWORD nMaxFile) reflect_to_self(self->nMaxFile = nMaxFile);
	/* R */ inline auto  FileMaxLen() const reflect_as(self->nMaxFile);
public: // Property - FileTitle
	/* W */ inline auto &FileTitle(LPTSTR lpstrFileTitle) reflect_as(self->lpstrFileTitle);
	/* R */ inline const String FileTitle() const reflect_as(CString(self->lpstrFileTitle, self->nMaxFileTitle));
public: // Property - FileTitleMaxLen
	/* W */ inline auto &FileTitleMaxLen(DWORD nMaxFileTitle) reflect_to_self(self->nMaxFileTitle = nMaxFileTitle);
	/* W */ inline auto  FileTitleMaxLen() const reflect_as(self->nMaxFileTitle = nMaxFileTitle);
public: // Property - CustomFilter
	/* W */ inline auto &CustomFilter(LPTSTR lpstrCustomFilter) reflect_to_self(self->lpstrCustomFilter);
	/* R */ inline const String CustomFilter() const reflect_as(CString(self->lpstrCustomFilter, self->nMaxCustomFilter));
public: // Property - CustomFilterMaxLen
	/* W */ inline auto &CustomFilterMaxLen(DWORD nMaxCustomFilter) reflect_to_self(self->nMaxCustomFilter = nMaxCustomFilter);
	/* R */ inline auto  CustomFilterMaxLen() const reflect_as(self->nMaxCustomFilter);
public: // Property - Filter
	/* W */ inline auto &Filter(LPCTSTR lpstrFilter) reflect_to_self(self->lpstrFilter = lpstrFilter);
public: // Property - FilterIndex
	/* R */ inline DWORD FilterIndex() const reflect_as(self->nFilterIndex);
public: // Property - InitialDir
	/* W */ inline auto &InitialDir(LPCTSTR lpstrInitialDir) reflect_to_self(self->lpstrInitialDir = lpstrInitialDir);
public: // Property - Title
	/* W */ inline auto &Title(LPCTSTR lpstrTitle) reflect_to_self(self->lpstrTitle = lpstrTitle);
public: // Property - DefExt
	/* W */ inline auto &DefExt(LPCTSTR lpstrDefExt) reflect_to_self(self->lpstrDefExt = lpstrDefExt);
public:
	inline bool OpenFile() {
		if constexpr (IsUnicode)
			reflect_as(GetOpenFileNameW(self))
		else
			reflect_as(GetOpenFileNameA(self))
	}
	inline bool SaveFile() {
		if constexpr (IsUnicode)
			reflect_as(GetSaveFileNameW(self))
		else
			reflect_as(GetSaveFileNameA(self))
	}
};
using ChooserFile = ChooserFileT<IsUnicode>;
using ChooserFileA = ChooserFileT<false>;
using ChooserFileW = ChooserFileT<true>;

enum_flags(FindReplaceStyle, DWORD,
	Down                 = FR_DOWN,
	WholeWord            = FR_WHOLEWORD,
	MatchCase            = FR_MATCHCASE,
	FindNext             = FR_FINDNEXT,
	Replace              = FR_REPLACE,
	ReplaceAll           = FR_REPLACEALL,
	DialogTerm           = FR_DIALOGTERM,
	ShowHelp             = FR_SHOWHELP,
	EnableHook           = FR_ENABLEHOOK,
	EnableTemplate       = FR_ENABLETEMPLATE,
	NoUpDown             = FR_NOUPDOWN,
	NoMatchCase          = FR_NOMATCHCASE,
	NoWholeWord          = FR_NOWHOLEWORD,
	EnableTemplateHandle = FR_ENABLETEMPLATEHANDLE,
	HideUpDown           = FR_HIDEUPDOWN,
	HideMatchCase        = FR_HIDEMATCHCASE,
	HideWholeWord        = FR_HIDEWHOLEWORD,
	Raw                  = FR_RAW,
	ShowWrapAround       = FR_SHOWWRAPAROUND,
	NoWrapAround         = FR_NOWRAPAROUND,
	WrapAround           = FR_WRAPAROUND,
	MatchDiac            = FR_MATCHDIAC,
	MatchKashida         = FR_MATCHKASHIDA,
	MatchAlefHamza       = FR_MATCHALEFHAMZA);
class FindReplace : public RefStruct<FINDREPLACE> {
public:
	using Style = FindReplaceStyle;
public:
	FindReplace() {
		self->lStructSize = sizeof(FINDREPLACE);
	}
public: // Properties
	/* W */ inline auto &Parent(HWND hWnd) reflect_to_self(self->hwndOwner = hWnd);
	/* W */ inline auto &Module(HINSTANCE hMod) reflect_to_self(self->hInstance = hMod);
	/* W */ inline auto &Styles(Style Flags) reflect_to_self(self->Flags = Flags.yield());
	/* W */ inline auto &TemplateName(const TCHAR *lpTemplateName) reflect_to_self(self->lpTemplateName = lpTemplateName);
	/* R */ inline const String FindWhat() reflect_as(CString(self->lpstrFindWhat, self->wFindWhatLen));
	/* R */ inline const String ReplaceWith() reflect_as(CString(self->lpstrReplaceWith, self->wReplaceWithLen));
	//LPARAM       lCustData;          // data passed to hook fn.
	//LPFRHOOKPROC lpfnHook;           // ptr. to hook fn. or NULL
public:
	inline HWND Find() {
		reflect_as(FindText(self));
	}
};

//class ConfigComm : public RefStruct<COMMCONFIG> {
//	HWND hwndOwner = O;
//public:
//	ConfigComm() {
//		self->dwSize = sizeof(COMMCONFIG);
//		//self->wVersion = COMMCONFIG_VERSION;
//	}
//public: // Properties
//	/* W */ inline auto &Parent(HWND hWnd) reflect_to_self(this->hwndOwner = hWnd);
//public:
//	inline bool Config() reflect_as(CommConfigDialog(L"", hwndOwner, self))
//};

#pragma region Dialog Template

inline void PushHeap(void *&pHeap, size_t &maxSize, const void *pData, size_t dataSize) {
	assertl(dataSize <= maxSize);
	CopyMemory(pHeap, pData, dataSize);
	maxSize -= dataSize;
	(uint8_t *&)pHeap += dataSize;
}
template<class AnyType>
inline void PushHeap(void *&pHeap, size_t &maxSize, const AnyType &type)
{ PushHeap(pHeap, maxSize, &type, sizeof(AnyType)); }
template<>
inline void PushHeap<std::wstring>(void *&pHeap, size_t &maxSize, const std::wstring &str)
{ PushHeap(pHeap, maxSize, str.c_str(), str.size() * 2 + 2); }

class DialogControl {
	DLGITEMTEMPLATE dit = { 0 };
	std::wstring className;
	std::wstring caption;
	WORD sizeParam = 0;
public:
	enum_class(Classes, WORD,
		Button    = 0x0080, // See Microsoft Learn
		Edit      = 0x0081,
		Static    = 0x0082,
		ListBox   = 0x0083,
		Scrollbar = 0x0084,
		ComboBox  = 0x0085);

	DialogControl(Classes classId) : className({ (wchar_t)classId.yield() }) {}
	DialogControl(LPCWSTR pCaption, Classes classId = Classes::Static) :
		className({ (wchar_t)classId.yield() }), caption(pCaption) {}
	DialogControl(LPCWSTR pCaption, WORD id) : 
		className({ (wchar_t)id }), caption(pCaption) { dit.id = id; }

#pragma region Properties
public: // Property - Style
	template<class AnyStyle>
	/* W */ inline auto &Style(AnyStyle style) reflect_to_self(dit.style = style.yield());
public: // Property - StyleEx
	template<class AnyStyle>
	/* W */ inline auto &StyleEx(AnyStyle exStyle) reflect_to_self(dit.dwExtendedStyle = exStyle.yield());
public: // Property - Position
	/* W */ inline auto &Position(LPoint p) reflect_to_self(dit.x = (SHORT)p.x, dit.y = (SHORT)p.y);
public: // Property - Size
	/* W */ inline auto &Size(LSize sz) reflect_to_self(dit.cx = (SHORT)sz.cx, dit.cy = (SHORT)sz.cy);
public: // Property - ID
	/* W */ inline auto &ID(WORD id) reflect_to_self(dit.id = id);
public: // Property - Class
	/* W */ inline auto &Class(std::wstring className) reflect_to_self(this->className = className);
	/* W */ inline auto &Class(WORD classId) reflect_to_self(this->className = { (wchar_t)classId });
public: // Property - Caption
	/* W */ inline auto &Caption(LPCWSTR lpszCaption) reflect_to_self(this->caption = lpszCaption);
#pragma endregion

private:
	friend class DialogFactory;
	inline size_t HeapSize() {
		return
			sizeof(DLGITEMTEMPLATE) +
			(className.size() + caption.size()) * 2 + 2 +
			sizeof(sizeParam) + sizeParam;
	}
	inline void PushToHeap(void *&pHeap, size_t &maxSize) {
		PushHeap(pHeap, maxSize, dit);
		if (className.size() <= 1) {
			WORD aClassId[2] = { 0xFFFF, className[0] };
			PushHeap(pHeap, maxSize, aClassId);
		}
		else PushHeap(pHeap, maxSize, className);
		PushHeap(pHeap, maxSize, caption);
		PushHeap(pHeap, maxSize, sizeParam);
	}
};
using DCtl = DialogControl;
using DClass = DialogControl::Classes;
class DialogFactory {
	DLGTEMPLATE dt = { 0 };
	std::wstring menuName;
	std::wstring className;
	std::wstring caption;
	std::vector<DialogControl> dits;
public:
	DialogFactory() {}
	DialogFactory(LPCWSTR pCaption) : caption(pCaption) {}
	
	inline auto &Add(const DialogControl &dc) reflect_to_self(dits.push_back(dc));

#pragma region Properties
public: // Property - Style
	template<class AnyStyle>
	/* W */ inline auto &Style(AnyStyle style) reflect_to_self(dt.style = style.yield());
public: // Property - StyleEx
	template<class AnyStyle>
	/* W */ inline auto &StyleEx(AnyStyle exStyle) reflect_to_self(dt.dwExtendedStyle = exStyle.yield());
public: // Property - Position
	/* W */ inline auto &Position(LPoint p) reflect_to_self(dt.x = (SHORT)p.x, dt.y = (SHORT)p.y);
public: // Property - Size
	/* W */ inline auto &Size(LSize sz) reflect_to_self(dt.cx = (SHORT)sz.cx, dt.cy = (SHORT)sz.cy);
public: // Property - Menu
	/* W */ inline auto &Menu(std::wstring menuName) reflect_to_self(this->menuName = menuName);
	/* W */ inline auto &Menu(WORD menuId) reflect_to_self(this->menuName = { (wchar_t)menuId });
public: // Property - Class
	/* W */ inline auto &Class(std::wstring className) reflect_to_self(this->className = className);
	/* W */ inline auto &Class(WORD classId) reflect_to_self(this->className = { (wchar_t)classId });
public: // Property - Caption
	/* W */ inline auto &Caption(std::wstring caption) reflect_to_self(this->caption = caption);
#pragma endregion

private:
	inline size_t HeapSize() {
		auto size = sizeof(DLGTEMPLATE) + (menuName.size() + className.size() + caption.size()) * 2 + 6;
		// size += 0; //************* style & DS_SETFONT ************/
		for (auto &dit : dits)
			size += (dit.HeapSize() + 3) & ~3; // Align to DWORD // See Microsoft Learn for more
		return size;
	}
	inline void PushToHeap(void *&pHeap, size_t &maxSize) {
		if (menuName.size() == 1) {
			WORD aMenuId[2] = { 0xFFFF, menuName[0] };
			PushHeap(pHeap, maxSize, aMenuId);
		}
		else PushHeap(pHeap, maxSize, menuName);
		if (className.size() == 1) {
			WORD aClassId[2] = { 0xFFFF, className[0] };
			PushHeap(pHeap, maxSize, aClassId);
		}
		else PushHeap(pHeap, maxSize, className);
		PushHeap(pHeap, maxSize, caption);
		for (auto &dit : dits) {
			dit.PushToHeap(pHeap, maxSize);
			// Align to DWORD // See Microsoft Learn for more
			maxSize += 3;
			maxSize &= ~3;
			(LONG_PTR &)pHeap += 3;
			(LONG_PTR &)pHeap &= ~3;
		}
	}
public:
	inline AutoPointer<Heap, DLGTEMPLATE> Make() {
		auto maxSize = HeapSize();
		AutoPointer<Heap, DLGTEMPLATE> hDlg = { HAF::ZeroInit, maxSize };
		auto lpDlg = hDlg.Alloc(maxSize);
		PushHeap((void *&)lpDlg, maxSize, dt);
		PushToHeap((void *&)lpDlg, maxSize);
		hDlg->cdit = (WORD)dits.size();
		return hDlg;
	}
};
using DFact = DialogFactory;

class DialogItem {
	template<class AnyChild>
	friend class DialogBase;
	HWND hDlg = O;
	int nIDDlgItem = 0;
protected:
	DialogItem(HWND hDlg, int nIDDlgItem) :
		hDlg(hDlg), nIDDlgItem(nIDDlgItem) {}
public: // Property - String
	/* W */ inline auto &Text(LPTSTR lpText) assertl_reflect_as_self(SetDlgItemText(hDlg, nIDDlgItem, lpText));
	/* R */ inline String Text() const {
		auto len = GetDlgItemText(hDlg, nIDDlgItem, O, 0);
		if (len <= 0) return O;
		String text((size_t)len);
		assertl(GetDlgItemText(hDlg, nIDDlgItem, text, len));
		return text;
	}
public: // Property - Int
	/* W */ inline auto &Int(int val) {
		bool bSigned = val < 0;
		if (bSigned) val = -val;
		assertl(SetDlgItemInt(hDlg, nIDDlgItem, val, bSigned));
		retself;
	}
	/* R */ inline int Int(bool bSigned = true) const {
		BOOL lpTranslated = false;
		auto val = GetDlgItemInt(hDlg, nIDDlgItem, &lpTranslated, bSigned);
		assertl(lpTranslated);
		return val;
	}
public: // Property - CheckButton
	/* W */ inline auto &CheckButton(bool bCheck) assertl_reflect_as_self(CheckDlgButton(hDlg, nIDDlgItem, bCheck ? BST_CHECKED : BST_UNCHECKED));
	/* R */ inline bool CheckButton() const reflect_as(IsDlgButtonChecked(hDlg, nIDDlgItem) == BST_CHECKED);
public:
	template<class AnyWindow>
	inline operator AnyWindow() reflect_as(reuse_as<AnyWindow>(GetDlgItem(hDlg, nIDDlgItem)));
};
template<class AnyChild>
class DialogBase : public WindowBase<AnyChild> {
private:
	def_memberof(Forming);
	def_memberof(InitDialog);

public:
	using super = WindowBase<AnyChild>;
	using Child = AnyChild;
public:
	DialogBase() {}
public:
	inline INT_PTR Box(HWND hParent = NULL, HINSTANCE hInst = GetModuleHandle(O)) {
		if constexpr (member_Forming_of<Child>::template compatible_to<LPDLGTEMPLATE()>)
			return DialogBoxIndirectParam(hInst, child.Forming(), hParent, DlgProc, (LPARAM)this);
		else if constexpr (member_Forming_of<Child>::template compatible_to<LPCTSTR()>)
			return DialogBoxParam(hInst, child.Forming(), hParent, DlgProc, (LPARAM)this);
		else {
			static_assert(member_Forming_of<Child>::template compatible_to<UINT()>, "requires a valid template");
			return DialogBoxParam(hInst, MAKEINTRESOURCE(child.Forming()), hParent, DlgProc, (LPARAM)this);
		}
	}
	inline auto&Create(HWND hParent = NULL, HINSTANCE hInst = GetModuleHandle(O)) {
		if constexpr (member_Forming_of<Child>::template compatible_to<LPDLGTEMPLATE()>)
			assertl(CreateDialogIndirectParam(hInst, child.Forming(), hParent, DlgProc, (LPARAM)this))
		else if constexpr (member_Forming_of<Child>::template compatible_to<LPCTSTR()>)
			assertl(CreateDialogParam(hInst, child.Forming(), hParent, DlgProc, (LPARAM)this))
		else {
			static_assert(member_Forming_of<Child>::template compatible_to<UINT()>, "requires a valid template");
			assertl(CreateDialogParam(hInst, MAKEINTRESOURCE(child.Forming()), hParent, DlgProc, (LPARAM)this));
		}
		retchild;
	}

	inline auto&End(INT_PTR nResult) assertl_reflect_as_child(::EndDialog(self, nResult));

	inline DialogItem Item(int nIDDlgItem) reflect_as({ self, nIDDlgItem });

	template<class AnyWindow>
	inline AnyWindow Item(int nIDDlgItem) reflect_as(reuse_as<AnyWindow>(GetDlgItem(self, nIDDlgItem)));

protected:
	static INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msgid, WPARAM wParam, LPARAM lParam) {
		auto &Wnd = super::Attach(hDlg);
		auto pThis = (Child *)Wnd.UserData();
		switch (msgid) {
			case WM_INITDIALOG: {
				pThis = (Child *)lParam;
				if (!Wnd.UserData(pThis))
					return (INT_PTR)false;
				(HWND &)*reuse_as<Window *>(pThis) = hDlg;
				if constexpr (member_InitDialog_of<Child>::callable) {
					using fn_type = bool();
					misdef_assert((member_InitDialog_of<Child>::template compatible_to<fn_type>),
								  "Member InitDialog must be a method compatible to bool()");
					return (INT_PTR)pThis->InitDialog();
				}
				return (INT_PTR)true;
			}
		}
		if (pThis)
			try {
			switch (msgid) {
				case WM_NULL:
					break;
#define _CALL_(name) pThis->name
#define MSG_TRANS(msgid, ret, name, argslist, args, send, call) \
					case msgid: \
						if constexpr (super::template member_##name##_of<Child>::callable) { \
							using fn_type = ret argslist; \
							misdef_assert((super::template member_##name##_of<Child>::template compatible_to<fn_type>), \
										  "Member " #name " must be a method compatible to " #ret #argslist); \
							call; \
							return (INT_PTR)true; \
						} break;
#include "wx_msg.inl"
			}
			if constexpr (super::template member_Callback_of<Child>::callable)
				return ((Child *)pThis)->Callback(msgid, wParam, lParam);
		} catch (MSG) {}
		return (INT_PTR)false;
	}
};
#define SFINAE_Dialog(name) friend class WX::DialogBase<name>; friend class WX::WindowBase<name>
#define BaseOf_Dialog(name) name : public WX::DialogBase<name>

#pragma endregion

}
