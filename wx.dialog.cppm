module;

#define WX_CPPM_DIALOG
#include "wx_dialog"

export module wx.dialog;

import wx.proto;
import wx.gdi;

#pragma region Win32 Prototype Includes
namespace WX {

//////////// ! -- TODO: Add exception system with CommDlgExtendedError -- !  ////////////

#pragma region CommDlg.h
#undef GetOpenFileName
inline bool GetOpenFileName(LPOPENFILENAMEA lpofn)
	reflect_as(::GetOpenFileNameA(lpofn));
inline bool GetOpenFileName(LPOPENFILENAMEW lpofn)
	reflect_as(::GetOpenFileNameW(lpofn));
#undef GetSaveFileName
inline bool GetSaveFileName(LPOPENFILENAMEA lpofn)
	reflect_as(::GetSaveFileNameA(lpofn));
inline bool GetSaveFileName(LPOPENFILENAMEW lpofn)
	reflect_as(::GetSaveFileNameW(lpofn));
#undef GetFileTitle
inline short GetFileTitle(LPCSTR lpFileName, LPSTR lpBuffer, WORD cchSize)
	assertl_reflect_as(auto res = ::GetFileTitleA(lpFileName, lpBuffer, cchSize); res >= 0, res);
inline short GetFileTitle(LPCWSTR lpFileName, LPWSTR lpBuffer, WORD cchSize)
	assertl_reflect_as(auto res = ::GetFileTitleW(lpFileName, lpBuffer, cchSize); res >= 0, res);
#undef ChooseColor
inline bool ChooseColor(LPCHOOSECOLORA lpcc)
	reflect_as(::ChooseColorA(lpcc));
inline bool ChooseColor(LPCHOOSECOLORW lpcc)
	reflect_as(::ChooseColorW(lpcc));
#undef FindText
inline HWND FindText(LPFINDREPLACEA lpfr)
	reflect_as(::FindTextA(lpfr));
inline HWND FindText(LPFINDREPLACEW lpfr)
	reflect_as(::FindTextW(lpfr));
#undef ReplaceText
inline HWND ReplaceText(LPFINDREPLACEA lpfr)
	reflect_as(::ReplaceTextA(lpfr));
inline HWND ReplaceText(LPFINDREPLACEW lpfr)
	reflect_as(::ReplaceTextW(lpfr));
#undef ChooseFont
inline bool ChooseFont(LPCHOOSEFONTA lpcf)
	reflect_as(::ChooseFontA(lpcf));
inline bool ChooseFont(LPCHOOSEFONTW lpcf)
	reflect_as(::ChooseFontW(lpcf));
inline bool PrintDlg(LPPRINTDLGA lppd)
	reflect_as(::PrintDlgA(lppd));
inline bool PrintDlg(LPPRINTDLGW lppd)
	reflect_as(::PrintDlgW(lppd));
#undef PrintDlgEx
inline bool PrintDlg(LPPRINTDLGEXA lppd)
	reflect_as(::PrintDlgExA(lppd));
inline bool PrintDlg(LPPRINTDLGEXW lppd)
	reflect_as(::PrintDlgExW(lppd));
#undef PageSetupDlg
inline bool PageSetupDlg(LPPAGESETUPDLGA lppsd)
	reflect_as(::PageSetupDlgA(lppsd));
inline bool PageSetupDlg(LPPAGESETUPDLGW lppsd)
	reflect_as(::PageSetupDlgW(lppsd));
#pragma endregion

}
#pragma endregion

export namespace WX {

class DialogIItem {
	template<class>
	friend class DialogBase;
	mutable HWND hDlg;
	mutable int nIDDlgItem;
private:
	DialogIItem(HWND hDlg, int nIDDlgItem) : hDlg(hDlg), nIDDlgItem(nIDDlgItem) {}
	DialogIItem(const DialogIItem &) = delete;
public:
	DialogIItem(DialogIItem &dii) : hDlg(dii.hDlg), nIDDlgItem(dii.nIDDlgItem) {}
public:
	template<class RetType = LRESULT, class MsgType = UINT, class WParam = WPARAM, class LParam = LPARAM>
	inline RetType Send(MsgType msgid, WParam wParam = 0, LParam lParam = 0) const
		reflect_as(big_cast<RetType>(WX::SendDlgItemMessage(hDlg, nIDDlgItem, (UINT)(msgid), small_cast<WPARAM>(wParam), small_cast<LPARAM>(lParam))));
#pragma region Properties
public: // Property - Int
	/* W */ inline auto &Int(INT value) reflect_to_self(WX::SetDlgItemInt(hDlg, nIDDlgItem, value, true));
	/* W */ inline auto &Int(UINT value) reflect_to_self(WX::SetDlgItemInt(hDlg, nIDDlgItem, value, false));
	/* R */ inline INT   Int() const reflect_as(WX::GetDlgItemInt(hDlg, nIDDlgItem, O, true));
public: // Property - UInt
	/* R */ inline UINT  UInt() const reflect_as(WX::GetDlgItemInt(hDlg, nIDDlgItem, O, false));
public: // Property - ButtonCheck
	/* W */ inline auto &CheckButton(bool bCheck) reflect_to_self(WX::CheckDlgButton(hDlg, nIDDlgItem, bCheck ? BST_CHECKED : BST_UNCHECKED));
	/* R */ inline bool CheckButton() const reflect_as(WX::IsDlgButtonChecked(hDlg, nIDDlgItem) == BST_CHECKED);
public: // Property - Text
	template<class TCHAR>
	/* W */ inline auto &Text(const TCHAR *lpText) reflect_to_self(WX::SetDlgItemText(hDlg, nIDDlgItem, lpText));
	template<size_t MaxLen = MaxLenNotice, bool IsUnicode = WX::IsUnicode>
	/* R */ inline StringX<IsUnicode> Text() const {
		StringX<IsUnicode> str(MaxLen);
		auto len = WX::GetDlgItemText(hDlg, nIDDlgItem, str, (int)MaxLen);
		return inject(str.Resize(len));
	}
	template<size_t MaxLen = MaxLenNotice>
	/* R */ inline StringA TextA() const reflect_as(Text<MaxLen, false>());
	template<size_t MaxLen = MaxLenNotice>
	/* R */ inline StringW TextW() const reflect_as(Text<MaxLen, true>());
public: // Property - Window
	template<class AnyChild = void>
	/* R */ inline WindowShim<AnyChild> Window() reflect_as(WX::GetDlgItem(hDlg, nIDDlgItem));
	template<class AnyChild = void>
	/* R */ inline CWindowShim<AnyChild> Window() const reflect_as(WX::GetDlgItem(hDlg, nIDDlgItem));
#pragma endregion
public:
	inline operator HWND() const reflect_as(WX::GetDlgItem(hDlg, nIDDlgItem));
	template<class AnyChild>
	inline operator WindowShim<AnyChild>() reflect_as(WX::GetDlgItem(hDlg, nIDDlgItem));
	template<class AnyChild>
	inline operator CWindowShim<AnyChild>() const reflect_as(WX::GetDlgItem(hDlg, nIDDlgItem));
};
template<class AnyChild>
class DialogBase : public WindowBase<AnyChild> {
public:
public:
	template<class IsUnicode>
	class CreateStructX {

	};
	// inline auto Create()
	// inline auto Box()
	template<class AnyType = INT_PTR>
	inline void End(AnyType nResult) reflect_to(WX::EndDialog(self, small_cast<INT_PTR>(nResult)));
#pragma region Properties
public: //
#pragma endregion
};

//////////// ! -- TODO: Add exception system with CommDlgExtendedError -- !  ////////////

template<class DIALOGSTRUCT, class AnyChild>
class DialogCommon :
	public RefStruct<DIALOGSTRUCT>,
	public ChainExtender<DialogCommon<DIALOGSTRUCT, AnyChild>, AnyChild> {
	using LPCTSTR = decltype(DIALOGSTRUCT::lpTemplateName);
	using String = StringX<std::is_same_v<LPCTSTR, LPCWSTR>>;
public:
	using super = RefStruct<DIALOGSTRUCT>;
	using Child = AnyChild;
public:
	DialogCommon() reflect_to(this->lStructSize = sizeof(DIALOGSTRUCT));
public: // Properties
	/* W */ inline auto &Owner(HWND hwndOwner) reflect_to_child(self->hwndOwner = hwndOwner);
	/* W */ inline auto &Module(HINSTANCE hInstance) reflect_to_child(self->hInstance = (decltype(self->hInstance))hInstance);
	/* W */ inline auto &Template(LPCTSTR lpTemplateName) reflect_to_child(self->lpTemplateName = lpTemplateName);
	template<class AnyType>
	/* W */ inline auto &CustData(AnyType dat) reflect_to_child(self->lCustData = small_cast<LPARAM>(dat));
public:
	//	LPOFNHOOKPROC lpfnHook;
};

#pragma region DialogColor
enum_flags(DialogColorStyle, DWORD,
	InitRGB              = CC_RGBINIT,
	FullOpen             = CC_FULLOPEN,
	PreventFullOpen      = CC_PREVENTFULLOPEN,
	ShowHelp             = CC_SHOWHELP,
	EnableHook           = CC_ENABLEHOOK,
	EnableTemplate       = CC_ENABLETEMPLATE,
	EnableTemplateHandle = CC_ENABLETEMPLATEHANDLE,
	SolidColor           = CC_SOLIDCOLOR,
	AnyColor             = CC_ANYCOLOR);
using DlgColorStyle = DialogColorStyle;
template<bool IsUnicode, class AnyChild = void>
class DialogColorX : public DialogCommon<
	switch_structx(CHOOSECOLOR),
	Chain<DialogColorX<IsUnicode, AnyChild>, AnyChild>> {
	using_structx(CHOOSECOLOR);
public:
	using super = DialogCommon<CHOOSECOLOR, DialogColorX>;
public:
	using Style = DialogColorStyle;
	using ColorSet = arrayof<RGBColor, 16>;
	using CColorSet = const arrayof<RGBColor, 16>;
public:
	DialogColorX() reflect_to(self->lStructSize = sizeof(CHOOSECOLOR));
public: // Property - Styles
	/* W */ inline auto &Styles(Style style) reflect_to_child(self->Flags = style.yield());
public: // Property - CustColors
	/* W */ inline auto &CustColors(ColorSet *lpCustColors) reflect_to_child(self->lpCustColors = (COLORREF *)lpCustColors);
	/* R */ inline CColorSet *CustColors() const reflect_as((CColorSet *)self->lpCustColors);
public: // Property - Result
	/* W */ inline auto &Result(COLORREF rgb) reflect_to_child(self->rgbResult = rgb);
	/* R */ inline RGBColor Result() const reflect_as(self->rgbResult);
public:
	inline bool Choose() reflect_as(WX::ChooseColor(this));
};
template<class AnyChild = void>
using DialogColor  = DialogColorX<IsUnicode, AnyChild>;
template<class AnyChild = void>
using DialogColorA = DialogColorX<false, AnyChild>;
template<class AnyChild = void>
using DialogColorW = DialogColorX<true, AnyChild>;
template<class AnyChild = void>
using DlgColor = DialogColor<AnyChild>;
template<class AnyChild = void>
using DlgColorA = DialogColorA<AnyChild>;
template<class AnyChild = void>
using DlgColorW = DialogColorW<AnyChild>;
#pragma endregion

#pragma region DialogFont
enum_flags(DialogFontStyle, DWORD,
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
using DlgFontStyle = DialogFontStyle;
template<bool IsUnicode, class AnyChild = void>
class DialogFontX : public DialogCommon<
	switch_structx(CHOOSEFONT),
	Chain<DialogFontX<IsUnicode, AnyChild>, AnyChild>> {
	using_structx(CHOOSEFONT);
	using_structx(FontLogic);
	using_structx(LOGFONT);
	using_structx(String);
	using LPCTSTR = LPCXSTR<IsUnicode>;
public:
	using super = RefStruct<CHOOSEFONT>;
	using Style = DialogFontStyle;
public:
	DialogFontX() reflect_to(self->lStructSize = sizeof(CHOOSEFONT));
	~DialogFontX() reflect_to(String::AutoFree(self->lpszStyle));
public: // Property - Styles
	/* W */ inline auto &Styles(Style style) reflect_to_self(self->Flags = style.yield());
public: // Property - FontTypes
	/* W */ inline auto    &FontTypes(FontType ft) reflect_to_self(self->nFontType = ft.yield());
	/* R */ inline FontType FontTypes() const reflect_as(reuse_as<FontType>(self->nFontType));
public: // Property - SizeMin
	/* W */ inline auto&SizeMin(INT nSizeMin) reflect_to_self(self->nSizeMin = nSizeMin);
	/* R */ inline INT   SizeMin() const reflect_as(self->nSizeMin);
public: // Property - SizeMax
	/* W */ inline auto&SizeMax(INT nSizeMax) reflect_to_self(self->nSizeMax = nSizeMax);
	/* R */ inline INT  SizeMax() const reflect_as(self->nSizeMax);
public: // Property - PointSize
	/* W */ inline auto&PointSize(INT iPointSize) reflect_to_self(self->iPointSize = iPointSize);
	/* R */ inline INT  PointSize() const reflect_as(self->iPointSize);
public: // Property - Color
	/* W */ inline auto    &Color(COLORREF rgbColors) reflect_to_self(self->rgbColors = rgbColors);
	/* R */ inline RGBColor Color() const reflect_as(self->rgbColors);
public: // Property - DC
	/* W */ inline auto&DC(HDC hDC) reflect_to_self(self->hDC = hDC);
	/* R */ inline CDC  DC() const reflect_as(self->hDC);
public: // Property - FontStyle
	/* W */ inline auto &FontStyle(const String &style) reflect_to_self(String::AutoCopy(self->lpszStyle, style));
	template<size_t MaxLen = MaxLenNotice>
	/* R */ inline const String FontStyle() const reflect_as(CString(self->lpszStyle, MaxLen));
public: // Property - LogFont
	/* W */ inline auto &LogFont(LOGFONT *lpLogFont) reflect_to_self(self->lpLogFont = lpLogFont);
	/* W */ inline auto &LogFont(FontLogic *lpLogFont) reflect_to_self(self->lpLogFont = (LOGFONT *)lpLogFont);
	/* R */ inline auto LogFont() const reflect_as(self->lpLogFont);
public:
	inline bool Choose() reflect_as(WX::ChooseFont(this));
};
template<class AnyChild = void>
using DialogFont = DialogFontX<IsUnicode, AnyChild>;
template<class AnyChild = void>
using DialogFontA = DialogFontX<false, AnyChild>;
template<class AnyChild = void>
using DialogFontW = DialogFontX<true, AnyChild>;
template<class AnyChild = void>
using DlgFont = DialogFont<AnyChild>;
template<class AnyChild = void>
using DlgFontA = DialogFontA<AnyChild>;
template<class AnyChild = void>
using DlgFontW = DialogFontW<AnyChild>;
#pragma endregion

#pragma region DialogFile
enum_flags(DialogFileStyle, DWORD,
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
using DlgFileStyle = DialogFileStyle;
template<bool IsUnicode, class AnyChild = void>
class DialogFileX : public DialogCommon<
	switch_structx(OPENFILENAME),
	Chain<DialogFileX<IsUnicode, AnyChild>, AnyChild>> {
	using_structx(OPENFILENAME);
	using LPTSTR = LPXSTR<IsUnicode>;
	using LPCTSTR = LPCXSTR<IsUnicode>;
	using String = StringX<IsUnicode>;
public:
	using super = RefStruct<OPENFILENAME>;
	using Style = DialogFileStyle;
public:
	DialogFileX() reflect_to(self->lStructSize = sizeof(OPENFILENAME));
public: // Property - Styles
	/* W */ inline auto &Styles(Style Flags) reflect_to_self(self->Flags = Flags.yield());
public: // Property - FileOffset
	/* R */ inline WORD FileOffset() const reflect_as(self->nFileOffset);
public: // Property - FileExtension
	/* R */ inline WORD FileExtension() const reflect_as(self->nFileExtension);
public: // Property - File
//	/* W */ inline auto &File(const String &strFile) reflect_to_self(self->lpstrFile = lpstrFile);
	/* W */ inline auto &File(String &strFile) reflect_to_self(self->lpstrFile = strFile, self->nMaxFile = (DWORD)strFile.Length());
	/* R */ inline const String File() const reflect_as(CString(self->lpstrFile, self->nMaxFile));
public: // Property - FileMaxLen
	/* W */ inline auto &FileMaxLen(DWORD nMaxFile) reflect_to_self(self->nMaxFile = nMaxFile);
	/* R */ inline auto  FileMaxLen() const reflect_as(self->nMaxFile);
public: // Property - FileTitle
	/* W */ inline auto &FileTitle(LPTSTR lpstrFileTitle) reflect_as(self->lpstrFileTitle = lpstrFileTitle);
	/* W */ inline auto &FileTitle(String &strFileTitle) reflect_to_self(self->lpstrFileTitle = strFileTitle, self->nMaxFileTitle = (DWORD)strFileTitle.Length());
	/* R */ inline const String FileTitle() const reflect_as(CString(self->lpstrFileTitle, self->nMaxFileTitle));
public: // Property - FileTitleMaxLen
	/* W */ inline auto &FileTitleMaxLen(DWORD nMaxFileTitle) reflect_to_self(self->nMaxFileTitle = nMaxFileTitle);
	/* W */ inline auto  FileTitleMaxLen() const reflect_as(self->nMaxFileTitle);
public: // Property - CustomFilter
	/* W */ inline auto &CustomFilter(LPTSTR lpstrCustomFilter) reflect_to_self(self->lpstrCustomFilter = lpstrCustomFilter);
	/* W */ inline auto &CustomFilter(String &strCustFilter) reflect_to_self(self->lpstrCustomFilter = strCustFilter, self->nMaxCustFilter = (DWORD)strCustFilter.Length());
	/* R */ inline const String CustomFilter() const reflect_as(CString(self->lpstrCustomFilter, self->nMaxCustFilter));
public: // Property - CustomFilterMaxLen
	/* W */ inline auto &CustomFilterMaxLen(DWORD nMaxCustFilter) reflect_to_self(self->nMaxCustFilter = nMaxCustFilter);
	/* R */ inline auto  CustomFilterMaxLen() const reflect_as(self->nMaxCustFilter);
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
	inline bool OpenFile() reflect_as(WX::GetOpenFileName(this));
	inline bool SaveFile() reflect_as(WX::GetSaveFileName(this));
};
template<class AnyChild = void>
using DialogFile = DialogFileX<IsUnicode, AnyChild>;
template<class AnyChild = void>
using DialogFileA = DialogFileX<false, AnyChild>;
template<class AnyChild = void>
using DialogFileW = DialogFileX<true, AnyChild>;
template<class AnyChild = void>
using DlgFile = DialogFile<AnyChild>;
template<class AnyChild = void>
using DlgFileA = DialogFileA<AnyChild>;
template<class AnyChild = void>
using DlgFileW = DialogFileW<AnyChild>;
#pragma endregion

#pragma region FindReplace
enum_flags(DialogTextStyle, DWORD,
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
using DlgTextStyle = DialogTextStyle;
template<bool IsUnicode, class AnyChild = void>
class DialogTextX : public DialogCommon<
	switch_structx(FINDREPLACE),
	Chain<DialogTextX<IsUnicode, AnyChild>, AnyChild>> {
	using_structx(FINDREPLACE);
	using String = StringX<IsUnicode>;
public:
	using super = RefStruct<FINDREPLACE>;
	using Style = DialogTextStyle;
public:
	DialogTextX() reflect_to(self->lStructSize = sizeof(FINDREPLACE));
public: // Properties
	/* W */ inline auto &Styles(Style Flags) reflect_to_self(self->Flags = Flags.yield());
	/* R */ inline const String FindWhat() reflect_as(CString(self->lpstrFindWhat, self->wFindWhatLen));
	/* R */ inline const String ReplaceWith() reflect_as(CString(self->lpstrReplaceWith, self->wReplaceWithLen));
public:
	inline HWND Find() reflect_as(WX::FindText(this));
	inline HWND Replace() reflect_as(WX::ReplaceText(this));
};
template<class AnyChild = void>
using DialogText = DialogTextX<IsUnicode, AnyChild>;
template<class AnyChild = void>
using DialogTextA = DialogTextX<false, AnyChild>;
template<class AnyChild = void>
using DialogTextW = DialogTextX<true, AnyChild>;
template<class AnyChild = void>
using DlgText = DialogText<AnyChild>;
template<class AnyChild = void>
using DlgTextA = DialogTextA<AnyChild>;
template<class AnyChild = void>
using DlgTextW = DialogTextW<AnyChild>;
#pragma endregion

#pragma region DialogPrint
#pragma endregion

#pragma region DialogPageSetup
#pragma endregion

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

#if 0
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
inline void PushHeap<StringW>(void *&pHeap, size_t &maxSize, const StringW &str)
{ PushHeap(pHeap, maxSize, str, str.Size()); }

class DialogControl {
	DLGITEMTEMPLATE dit = { 0 };
	StringW className;
	StringW caption;
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
	DialogControl(const StringW &caption, Classes classId = Classes::Static) :
		className({ (wchar_t)classId.yield() }), caption(+caption) {}
	DialogControl(const StringW &caption, WORD id) :
		className({ (wchar_t)id }), caption(+caption) { dit.id = id; }

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
public: // Property - WindowClass
	/* W */ inline auto &WindowClass(const StringW &className) reflect_to_self(this->className = +className);
	/* W */ inline auto &WindowClass(WORD classId) reflect_to_self(this->className = { (wchar_t)classId });
public: // Property - Caption
	/* W */ inline auto &Caption(const StringW &lpszCaption) reflect_to_self(this->caption = +lpszCaption);
#pragma endregion

private:
	friend class DialogFactory;
	inline size_t HeapSize() {
		return
			sizeof(DLGITEMTEMPLATE) +
			className.Size() + caption.Size() + 2 +
			sizeof(sizeParam) + sizeParam;
	}
	inline void PushToHeap(void *&pHeap, size_t &maxSize) {
		PushHeap(pHeap, maxSize, dit);
		if (className.Length() <= 1) {
			WORD aClassId[2] = { 0xFFFF, className[0] };
			PushHeap(pHeap, maxSize, aClassId);
		} else PushHeap(pHeap, maxSize, className);
		PushHeap(pHeap, maxSize, caption);
		PushHeap(pHeap, maxSize, sizeParam);
	}
};
using DCtl = DialogControl;
using DClass = DialogControl::Classes;
class DialogFactory {
	DLGTEMPLATE dt = { 0 };
	StringW menuName;
	StringW className;
	StringW caption;
	std::vector<DialogControl> dits;
public:
	DialogFactory() {}
	DialogFactory(const StringW &caption) : caption(+caption) {}
public:
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
	/* W */ inline auto &Menu(const StringW &menuName) reflect_to_self(this->menuName = +menuName);
	/* W */ inline auto &Menu(WORD menuId) reflect_to_self(this->menuName = { (wchar_t)menuId });
public: // Property - WindowClass
	/* W */ inline auto &WindowClass(const StringW &className) reflect_to_self(this->className = +className);
	/* W */ inline auto &WindowClass(WORD classId) reflect_to_self(this->className = { (wchar_t)classId });
public: // Property - Caption
	/* W */ inline auto &Caption(const StringW &caption) reflect_to_self(this->caption = +caption);
#pragma endregion

private:
	inline size_t HeapSize() {
		auto size =
			sizeof(DLGTEMPLATE) +
			menuName.Size() + className.Size() + caption.Size();
		// size += 0; //************* style & DS_SETFONT ************/
		for (auto &dit : dits)
			size += (dit.HeapSize() + 3) & ~3; // Align to DWORD // See Microsoft Learn for more
		return size;
	}
	inline void PushToHeap(void *&pHeap, size_t &maxSize) {
		if (menuName.Length() == 1) {
			WORD aMenuId[2] = { 0xFFFF, menuName[0] };
			PushHeap(pHeap, maxSize, aMenuId);
		} else PushHeap(pHeap, maxSize, menuName);
		if (className.Length() == 1) {
			WORD aClassId[2] = { 0xFFFF, className[0] };
			PushHeap(pHeap, maxSize, aClassId);
		} else PushHeap(pHeap, maxSize, className);
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
	inline HeapPointer<DLGTEMPLATE> Make() {
		auto maxSize = HeapSize();
		HeapPointer<DLGTEMPLATE> hDlg = { HAF::ZeroInit, maxSize };
		auto lpDlg = hDlg.Alloc(maxSize);
		PushHeap((void *&)lpDlg, maxSize, dt);
		PushToHeap((void *&)lpDlg, maxSize);
		hDlg->cdit = (WORD)dits.size();
		return hDlg;
	}
};
using DFact = DialogFactory;

class DialogItem {
	template<class>
	friend class DialogBase;
	HWND hDlg = O;
	int nIDDlgItem = 0;
protected:
	DialogItem(HWND hDlg, int nIDDlgItem) :
		hDlg(hDlg), nIDDlgItem(nIDDlgItem) {}
public: // Property - String
	/* W */ inline auto &Text(LPSTR lpText) reflect_to_self(WX::SetDlgItemText(hDlg, nIDDlgItem, lpText));
	/* W */ inline auto &Text(LPWSTR lpText) reflect_to_self(WX::SetDlgItemText(hDlg, nIDDlgItem, lpText));
	template<bool IsUnicode = WX::IsUnicode>
	/* R */ inline StringX<IsUnicode> Text() const {
		auto len = WX::GetDlgItemText(hDlg, nIDDlgItem, (LPXSTR<IsUnicode>)O, 0);
		StringX<IsUnicode> str((size_t)len);
		WX::GetDlgItemText(hDlg, nIDDlgItem, str, len);
		return inject(str);
	}
	/* R */ inline StringA TextA() const reflect_as(Text<false>());
	/* R */ inline StringW TextW() const reflect_as(Text<true>());
public: // Property - Int
	/* W */ inline auto &Int(INT val) reflect_to_self(WX::SetDlgItemInt(hDlg, nIDDlgItem, std::abs(val), val < 0));
//	/* R */ inline int Int(bool bSigned = true) const nt_assertl_reflect_to_self(auto val = GetDlgItemInt(hDlg, nIDDlgItem, O, false), val);
public: // Property - UInt
	/* W */ inline auto &UInt(UINT val) reflect_to_self(WX::SetDlgItemInt(hDlg, nIDDlgItem, val, false));
//	/* R */ inline UINT  UInt() const nt_assertl_reflect_to_self(auto val = GetDlgItemInt(hDlg, nIDDlgItem, O, false), val);
public: // Property - CheckButton
	/* W */ inline auto &CheckButton(bool bCheck) reflect_to_self(WX::CheckDlgButton(hDlg, nIDDlgItem, bCheck ? BST_CHECKED : BST_UNCHECKED));
	/* R */ inline bool CheckButton() const reflect_as(WX::IsDlgButtonChecked(hDlg, nIDDlgItem) == BST_CHECKED);
public:
	template<class AnyWindow>
	inline operator AnyWindow() reflect_as(reuse_as<AnyWindow>(GetDlgItem(hDlg, nIDDlgItem)));
};

//template<class AnyChild>
//class DialogBase : public WindowBase<AnyChild> {
//private:
//	use_member(Forming);
//	use_member(InitDialog);
//public:
//	using super = WindowBase<AnyChild>;
//	using Child = AnyChild;
//public:
//	DialogBase() {}
//public:
//	inline INT_PTR Box(HWND hParent = NULL, HINSTANCE hInst = GetModuleHandle((LPCTSTR)O)) {
//		if_c (member_Forming_of<Child>::template compatible_to<LPDLGTEMPLATE()>)
//			return DialogBoxIndirectParam(hInst, child.Forming(), hParent, DlgProc, (LPARAM)this);
//		elif_c (member_Forming_of<Child>::template compatible_to<LPCTSTR()>)
//			return DialogBoxParam(hInst, child.Forming(), hParent, DlgProc, (LPARAM)this);
//		else {
//			static_assert(member_Forming_of<Child>::template compatible_to<UINT()>, "requires a valid template");
//			return DialogBoxParam(hInst, MAKEINTRESOURCE(child.Forming()), hParent, DlgProc, (LPARAM)this);
//		}
//	}
//	inline auto&Create(HWND hParent = NULL, HINSTANCE hInst = GetModuleHandle((LPCTSTR)O)) {
//		if_c (member_Forming_of<Child>::template compatible_to<LPDLGTEMPLATE()>)
//			assertl(CreateDialogIndirectParam(hInst, child.Forming(), hParent, DlgProc, (LPARAM)this))
//		elif_c (member_Forming_of<Child>::template compatible_to<LPCTSTR()>)
//			assertl(CreateDialogParam(hInst, child.Forming(), hParent, DlgProc, (LPARAM)this))
//		else {
//			static_assert(member_Forming_of<Child>::template compatible_to<UINT()>, "requires a valid template");
//			assertl(CreateDialogParam(hInst, MAKEINTRESOURCE(child.Forming()), hParent, DlgProc, (LPARAM)this));
//		}
//		retchild;
//	}
//
//	inline auto&End(INT_PTR nResult) assertl_reflect_as_child(::EndDialog(self, nResult));
//
//	inline DialogItem Item(int nIDDlgItem) reflect_as({ self, nIDDlgItem });
//
//	template<class AnyWindow>
//	inline AnyWindow Item(int nIDDlgItem) reflect_as(reuse_as<AnyWindow>(GetDlgItem(self, nIDDlgItem)));
//
//protected:
//	static INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msgid, WPARAM wParam, LPARAM lParam) {
//		auto &Wnd = super::Attach(hDlg);
//		auto pThis = (Child *)Wnd.UserData();
//		switch (msgid) {
//			case WM_INITDIALOG: {
//				pThis = (Child *)lParam;
//				if (!Wnd.UserData(pThis))
//					return (INT_PTR)false;
//				(HWND &)*reuse_as<Window *>(pThis) = hDlg;
//				if_c (member_InitDialog_of<Child>::is_addressable) {
//					using fn_type = bool();
//					misdef_assert((member_InitDialog_of<Child>::template compatible_to<fn_type>),
//								  "Member InitDialog must be a method compatible to bool()");
//					return (INT_PTR)pThis->InitDialog();
//				}
//				return (INT_PTR)true;
//			}
//		}
//		if (pThis)
//			try {
//			switch (msgid) {
//				case WM_NULL:
//					break;
//#define _CALL_(name) pThis->name
//#define MSG_TRANS(msgid, ret, name, argslist, args, send, call) \
//					case msgid: \
//						if_c (super::template member_##name##_of<Child>::is_addressable) { \
//							using fn_type = ret argslist; \
//							misdef_assert((super::template member_##name##_of<Child>::template compatible_to<fn_type>), \
//										  "Member " #name " must be a method compatible to " #ret #argslist); \
//							call; \
//							return (INT_PTR)true; \
//						} break;
//#include "wx__msg.inl"
//			}
//			if_c (super::template member_Callback_of<Child>::is_addressable)
//				return ((Child *)pThis)->Callback(msgid, wParam, lParam);
//		} catch (MSG) {}
//		return (INT_PTR)false;
//	}
//};

#pragma endregion
#endif

}
