module;

#define WX_CPPM_TYPE
#include "wx_type"

export module wx.type;

import wx;
import wx.proto;

#pragma region Win32 Prototype Includes
namespace WX {

#pragma region datetimeapi.h
#undef GetDateFormat
// GetDateFormat
inline int GetDateFormat(LCID Locale, DWORD dwFlags, const SYSTEMTIME *lpDate, LPCSTR lpFormat, LPSTR lpDateStr, int cchDate)
	assertl_reflect_as(auto res = ::GetDateFormatA(Locale, dwFlags, lpDate, lpFormat, lpDateStr, cchDate); res > 0, res);
inline int GetDateFormat(LCID Locale, DWORD dwFlags, const SYSTEMTIME *lpDate, LPCWSTR lpFormat, LPWSTR lpDateStr, int cchDate)
	assertl_reflect_as(auto res = ::GetDateFormatW(Locale, dwFlags, lpDate, lpFormat, lpDateStr, cchDate); res > 0, res);
#undef GetTimeFormat
// GetTimeFormat
inline int GetTimeFormat(LCID Locale, DWORD dwFlags, const SYSTEMTIME *lpTime, LPCSTR lpFormat, LPSTR lpTimeStr, int cchTime)
	assertl_reflect_as(auto res = ::GetTimeFormatA(Locale, dwFlags, lpTime, lpFormat, lpTimeStr, cchTime); res > 0, res);
inline int GetTimeFormat(LCID Locale, DWORD dwFlags, const SYSTEMTIME *lpTime, LPCWSTR lpFormat, LPWSTR lpTimeStr, int cchTime)
	assertl_reflect_as(auto res = ::GetTimeFormatW(Locale, dwFlags, lpTime, lpFormat, lpTimeStr, cchTime); res > 0, res);
#undef GetTimeFormatEx
// GetTimeFormatEx
inline int GetTimeFormat(LPCWSTR lpLocaleName, DWORD dwFlags, const SYSTEMTIME *lpTime, LPCWSTR lpFormat, LPWSTR lpTimeStr, int cchTime)
	assertl_reflect_as(auto res = ::GetTimeFormatEx(lpLocaleName, dwFlags, lpTime, lpFormat, lpTimeStr, cchTime); res > 0, res);
#undef GetDateFormatEx
// GetDateFormatEx
inline int GetDateFormat(LPCWSTR lpLocaleName, DWORD dwFlags, const SYSTEMTIME *lpDate, LPCWSTR lpFormat, LPWSTR lpDateStr, int cchDate, LPCWSTR lpCalendar)
	assertl_reflect_as(auto res = ::GetDateFormatEx(lpLocaleName, dwFlags, lpDate, lpFormat, lpDateStr, cchDate, lpCalendar); res > 0, res);
// GetDurationFormatEx - Deprecated
#pragma endregion

#pragma region handleapi.h
// CloseHandle
inline void CloseHandle(HANDLE hObject)
	assertl_reflect_as(::CloseHandle(hObject));
// DuplicateHandle
inline void DuplicateHandle(HANDLE hSourceProcessHandle, HANDLE hSourceHandle,
							HANDLE hTargetProcessHandle, LPHANDLE lpTargetHandle,
							DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwOptions)
	assertl_reflect_as(::DuplicateHandle(hSourceProcessHandle, hSourceHandle,
										 hTargetProcessHandle, lpTargetHandle,
										 dwDesiredAccess, bInheritHandle, dwOptions));
// CompareObjectHandles
inline bool CompareObjectHandles(HANDLE hObject1, HANDLE hObject2)
	reflect_as(::CompareObjectHandles(hObject1, hObject2));
// GetHandleInformation
inline void GetHandleInformation(HANDLE hObject, LPDWORD lpdwFlags)
	assertl_reflect_as(::GetHandleInformation(hObject, lpdwFlags));
// SetHandleInformation
inline void SetHandleInformation(HANDLE hObject, DWORD dwMask, DWORD dwFlags)
	assertl_reflect_as(::SetHandleInformation(hObject, dwMask, dwFlags));
#pragma endregion

}
#pragma endregion

export namespace WX {

#pragma region HandleBase
enum_flags(HandleAccess, DWORD,
	Delete         = DELETE,
	ReadCtl        = READ_CONTROL,
	WriteDAC       = WRITE_DAC,
	WriteOwner     = WRITE_OWNER,
	Sync           = SYNCHRONIZE,
	GenericRead    = GENERIC_READ,
	GenericWrite   = GENERIC_WRITE,
	GenericExecute = GENERIC_EXECUTE,
	GenericAll     = GENERIC_ALL);
template<class AnyChild>
class HandleBase;
using Handle = HandleBase<void>;
template<class AnyChild>
class HandleBase : public ChainExtender<HandleBase<AnyChild>, AnyChild> {
protected:
	mutable HANDLE hObject = O;
public:
	using Child = Chain<HandleBase, AnyChild>;
	using Access = HandleAccess;
protected:
	HandleBase(HANDLE h) : hObject(h) {}
	HandleBase(const HandleBase &h) : hObject(h.hObject) reflect_to(h.hObject = O);
public:
	HandleBase() {}
	HandleBase(Null) {}
	HandleBase(HandleBase &obj) : hObject(obj.hObject) reflect_to(obj.hObject = O);
	HandleBase(HandleBase &&obj) : hObject(obj.hObject) reflect_to(obj.hObject = O);
	~HandleBase() reflect_to(Close());
public:
	inline void Close() reflect_to(if (hObject) (WX::CloseHandle(hObject), hObject = O));
public:
	inline bool Compare(HANDLE h) const reflect_as(WX::CompareObjectHandles(self, h));
	//inline auto CopyTo() {
	//		DuplicateHandle(GetCurrentProcess(), self, 
	//			_In_ HANDLE hTargetProcessHandle,
	//			_Outptr_ LPHANDLE lpTargetHandle,
	//			_In_ DWORD dwDesiredAccess,
	//			_In_ BOOL bInheritHandle,
	//			_In_ DWORD dwOptions
	//		);
	//}

	//class Duplication {
	//	using AnyAccess = typename Child::Access;
	//	HANDLE hSourceProcessHandle = GetCurrentProcess();
	//	HANDLE hSourceHandle;
	//	HANDLE hTargetProcessHandle;
	//	DWORD dwDesiredAccess;
	//	bool bInheritHandle = false;
	//	DWORD dwOptions = DUPLICATE_SAME_ACCESS;
	//public:
	//	Duplication(HANDLE hSourceHandle, HANDLE hTargetProcessHandle) :
	//		hSourceHandle(hSourceHandle),
	//		hTargetProcessHandle(hTargetProcessHandle) {}
	//public:
	//	inline auto &SourceProcess(HANDLE hSourceHandle) reflect_to_self(this->hSourceHandle = hSourceHandle);
	//	inline auto &Accesses(AnyAccess acs) reflect_to_self(this->dwDesiredAccess = acs.yield(), this->dwOptions &= ~DUPLICATE_SAME_ACCESS);
	//	inline auto &Inherit(bool bInheritHandle = true) reflect_to_self(this->bInheritHandle = bInheritHandle);
	//public:
	//	inline operator Child() const assertl_reflect_to(
	//		HANDLE hTargetHandle = O,
	//		DuplicateHandle(
	//			hSourceProcessHandle, hSourceHandle,
	//			hTargetProcessHandle, &hTargetHandle,
	//			dwDesiredAccess, bInheritHandle,
	//			dwOptions), reuse_as<Child>(hTargetHandle));
	//};
	//inline Duplication Duplicate(HANDLE hTargetProcessHandle) reflect_as({ hObject, hTargetProcessHandle });

	inline auto Wait(DWORD dwMillisecond = INFINITE) reflect_as(::WaitForSingleObject)

public: // Property - Information
	/* W */ inline auto &Information(DWORD dwMask, DWORD dwFlags) reflect_to_child(WX::SetHandleInformation(self, dwMask, dwFlags));
	/* R */ inline DWORD Information(DWORD dwMask) const reflect_to(DWORD dwFlags = 0, WX::GetHandleInformation(self, &dwFlags), dwFlags &dwMask);
public: // Property - Inherit
	/* W */ inline auto &Inherit(bool bInherit) reflect_to_child(Information(HANDLE_FLAG_INHERIT, bInherit ? HANDLE_FLAG_INHERIT : 0));
	/* R */ inline bool Inherit() const reflect_as(Information(HANDLE_FLAG_INHERIT));
public: // Property - ProtectFromClose
	/* W */ inline auto &ProtectFromClose(bool bProtected) reflect_to_child(Information(HANDLE_FLAG_PROTECT_FROM_CLOSE, bProtected ? HANDLE_FLAG_PROTECT_FROM_CLOSE : 0));
	/* R */ inline bool ProtectFromClose() const reflect_as(Information(HANDLE_FLAG_PROTECT_FROM_CLOSE));
public:
	inline operator bool() const reflect_as(hObject && hObject != INVALID_HANDLE_VALUE);
	inline operator HANDLE() const reflect_as(hObject);
	inline operator const Handle() const reflect_as(ref_as<Handle>(self));
	inline void operator=(Child &obj) reflect_to(std::swap(obj.hObject, hObject));
	inline void operator=(Child &&obj) reflect_to(std::swap(obj.hObject, hObject));
	inline void operator=(const Child &obj) const reflect_to(std::swap(obj.hObject, hObject));
public:
	static inline auto &Attach(HANDLE &hObj) reflect_as(ref_as<Child>(hObj));
	static inline auto &Attach(const HANDLE &hObj) reflect_as(ref_as<const Child>(hObj));
};
#pragma endregion

#pragma region Heaps
#pragma region Local
enum_flags(LocalAllocFlags, UINT,
	Fixed    = LMEM_FIXED,
	Modify   = LMEM_MODIFY,
	Moveable = LMEM_MOVEABLE,
	ZeroInit = LMEM_ZEROINIT);
using LAF = LocalAllocFlags;
class Local {
public:
	using AllocFlags = LAF;
	static inline void *Alloc(size_t size, LAF flags = LAF::Fixed) reflect_to(auto ptr = LocalAlloc(flags.yield(), size), ptr);
	template<class AnyType>
	static inline AnyType *Alloc(LAF flags = LAF::Fixed) reflect_to(auto ptr = (AnyType *)LocalAlloc(flags.yield(), sizeof(AnyType)), ptr);
	static inline void *Realloc(void *ptr, size_t size, LAF flags = LAF::Fixed) reflect_as(LocalReAlloc(ptr, size, flags.yield()));
	static inline void  Free(void *ptr) {
		if (ptr)
			assertl(!LocalFree(ptr));
	}
	static inline void *Lock(void *ptr) reflect_as(LocalLock(ptr));
	static inline void Unlock(void *ptr) assertl_reflect_as(LocalUnlock(ptr));
	static inline void AutoFree(void *&ptr) reflect_to(if (ptr) (Free(ptr), ptr = O));
} inline LocalHeap;
#pragma endregion

#pragma region Heap
class HeapSummary : public RefStruct<HEAP_SUMMARY> {
public:
	using super = RefStruct<HEAP_SUMMARY>;
public:
	HeapSummary() reflect_to(this->cb = sizeof(HEAP_SUMMARY));
	HeapSummary(const HEAP_SUMMARY &hs) : super(hs) {}
public: // Property - Allocated
	/* W */ inline auto &Allocated(size_t cbAllocated) reflect_to_self(this->cbAllocated = cbAllocated);
	/* R */ inline size_t Allocated() const reflect_as(this->cbAllocated);
public: // Property - Committed
	/* W */ inline auto &Committed(size_t cbCommitted) reflect_to_self(this->cbCommitted = cbCommitted);
	/* R */ inline size_t Committed() const reflect_as(this->cbCommitted);
public: // Property - Reserved
	/* W */ inline auto &Reserved(size_t cbReserved) reflect_to_self(this->cbReserved = cbReserved);
	/* R */ inline size_t Reserved() const reflect_as(this->cbReserved);
public: // Property - MaxReserve
	/* W */ inline auto &MaxReserve(size_t cbMaxReserve) reflect_to_self(this->cbMaxReserve = cbMaxReserve);
	/* R */ inline size_t MaxReserve() const reflect_as(this->cbMaxReserve);
};
enum_flags(HeapAllocFlag, UINT,
	Fixed              = 0,
	GenerateExceptions = HEAP_GENERATE_EXCEPTIONS,
	NoSerialize        = HEAP_NO_SERIALIZE,
	ZeroInit           = HEAP_ZERO_MEMORY);
using HAF = HeapAllocFlag;
class BaseOf_Handle(Heap) {
public:
	using super = HandleBase<Heap>;
	using AllocFlags = HeapAllocFlag;
protected:
	INNER_USE(Heap);
	Heap(HANDLE hHeap) : super(hHeap) {}
public:
	Heap() : super(GetProcessHeap()) {}
	Heap(Null) {}
	Heap(Heap & h) : super(h) {}
	Heap(Heap && h) : super(h) {}
	Heap(const Heap &) = delete;
	~Heap() reflect_to(Destroy());
public:
	class CreateStruct {
		DWORD flOptions = 0;
		SIZE_T dwInitialSize = 0;
		SIZE_T dwMaximumSize = 0;
	public:
		CreateStruct() {}
	public:
		inline auto &MaximumSize(SIZE_T dwMaximumSize) reflect_to_self(this->dwMaximumSize = dwMaximumSize);
		inline auto &InitialSize(SIZE_T dwInitialSize) reflect_to_self(this->dwInitialSize = dwInitialSize);
		inline auto &Excutable() reflect_to_self(this->flOptions |= HEAP_CREATE_ENABLE_EXECUTE);
		inline auto &GenerateException() reflect_to_self(this->flOptions |= HEAP_GENERATE_EXCEPTIONS);
		inline auto &NoSerialize() reflect_to_self(this->flOptions |= HEAP_NO_SERIALIZE);
	public:
		inline operator Heap() reflect_as(HeapCreate(flOptions, dwInitialSize, dwMaximumSize));
	};
	static inline CreateStruct Create() reflect_as({});
public:
	//	DWORD GetProcessHeaps(_In_ DWORD NumberOfHeaps, _Out_writes_to_(NumberOfHeaps, return) PHANDLE ProcessHeaps);
	inline bool Destroy() {
		if (super::hObject && super::hObject != GetProcessHeap())
			if (!HeapDestroy(super::hObject))
				return false;
		super::hObject = O;
		return true;
	}
	inline void *Alloc(size_t size, AllocFlags flags = AllocFlags::Fixed) assertl_reflect_as(auto h = HeapAlloc(self, flags.yield(), size), h);
	inline void *Realloc(void *ptr, size_t nSize, DWORD flags = 0) assertl_reflect_as((ptr = HeapReAlloc(self, flags, ptr, nSize)), ptr);
	inline bool Free(void *ptr, DWORD flags = 0) reflect_as(HeapFree(self, flags, ptr));
	inline size_t Size(const void *ptr, DWORD flags) const assertl_reflect_as(auto size = HeapSize(self, flags, ptr), size);
	inline bool IsValid(const void *ptr, DWORD flags) const reflect_as(HeapValidate(self, flags, ptr));
	inline auto &Lock() assertl_reflect_as_self(HeapLock(self));
	inline auto &Unlock() assertl_reflect_as_self(HeapUnlock(self));
	//	HeapWalk();
	//	SIZE_T HeapCompact(HANDLE hHeap, DWORD dwFlags);
public: // Property - Summaries
	inline HeapSummary Summaries(DWORD dwFlags = 0) const assertl_reflect_to(HeapSummary s, ::HeapSummary(self, dwFlags, &s), s);
	//BOOL HeapSetInformation(
	//	_In_opt_ HANDLE HeapHandle,
	//	_In_ HEAP_INFORMATION_CLASS HeapInformationClass,
	//	_In_reads_bytes_opt_(HeapInformationLength) PVOID HeapInformation,
	//	_In_ SIZE_T HeapInformationLength);
	//BOOL HeapQueryInformation(
	//	_In_opt_ HANDLE HeapHandle,
	//	_In_ HEAP_INFORMATION_CLASS HeapInformationClass,
	//	_Out_writes_bytes_to_opt_(HeapInformationLength, *ReturnLength) PVOID HeapInformation,
	//	_In_ SIZE_T HeapInformationLength,
	//	_Out_opt_ PSIZE_T ReturnLength);
	using super::operator=;
};
using CHeap = RefAs<Heap>;
CHeap ThisHeap = Heap{};
#pragma endregion

template<class HeapType, class AnyType = void>
class HeapPointer {
	HeapType &heap;
	mutable AnyType *p = O;
public:
	using AllocFlags = typename HeapType::AllocFlags;
	HeapPointer() : heap(ThisHeap) {}
	explicit HeapPointer(size_t size) : heap(ThisHeap), p(heap.Alloc(size)) {}
	HeapPointer(AllocFlags flags, size_t size = SizeOf<AnyType>) : heap(ThisHeap), p((AnyType *)heap.Alloc(size, flags)) {}
	explicit HeapPointer(HeapType &heap) : heap(heap) {}
	~HeapPointer() reflect_to(Free());
public:
	inline AnyType *Alloc(size_t size = SizeOf<AnyType>) {
		if (size <= 0)
			Free();
		return (AnyType *)(p ? heap.Realloc(p, size) : heap.Alloc(size));
	}
	template<class AnyFlags>
	inline AnyType *Alloc(size_t size, AnyFlags flags) {
		return (AnyType *)(p ? heap.Realloc(p, size, flags) : heap.Alloc(size, flags));
	}
	inline void Free() {
		if (p)
			heap.Free(p);
		p = O;
	}
public:
	inline AnyType *&operator*() reflect_as(p);
	inline const AnyType *&operator*() const reflect_as(p);
	inline AnyType *operator&() reflect_as(p);
	inline const AnyType *operator&() const reflect_as(p);
	inline AnyType *operator->() reflect_as(p);
	inline const AnyType *operator->() const reflect_as(p);
};
#pragma endregion

#pragma region Times
enum_class(Locales, LCID,
	Default                = LOCALE_CUSTOM_DEFAULT,
	Unspecified            = LOCALE_CUSTOM_UNSPECIFIED,
	UIDefault              = LOCALE_CUSTOM_UI_DEFAULT,
	Neutral                = LOCALE_NEUTRAL,
	Invariant              = LOCALE_INVARIANT);
enum_flags(TimeFormat, DWORD,
	Default                = 0,
	NoMinutesOrSeconds     = TIME_NOMINUTESORSECONDS,
	NoSecond               = TIME_NOSECONDS,
	NoTimeMarker           = TIME_NOTIMEMARKER,
	Force24H               = TIME_FORCE24HOURFORMAT);
enum_flags(DateFormat, DWORD,
	Default                = 0,
	ShortDate              = DATE_SHORTDATE,
	LongDate               = DATE_LONGDATE,
	UseAltCalendar         = DATE_USE_ALT_CALENDAR,
	YearMonth              = DATE_YEARMONTH,
	LTRReading             = DATE_LTRREADING,
	RTLReading             = DATE_RTLREADING,
	AutoLayout             = DATE_AUTOLAYOUT,
	MonthDay               = DATE_MONTHDAY);
class SystemTime : public RefStruct<SYSTEMTIME> {
public:
	using super = RefStruct<SYSTEMTIME>;
public:
	SystemTime(Null) {}
	SystemTime() reflect_to(GetSystemTime(this));
	SystemTime(const SYSTEMTIME &st) : super(st) {}
	SystemTime(const FILETIME &ft) assertl(FileTimeToSystemTime(&ft, this));
public:
	static inline SystemTime LocalTime() reflect_to(SystemTime st; GetLocalTime(&st), st);
public: // Property - Year
	/* W */ inline auto &Year(WORD wYear) reflect_to_self(self->wYear = wYear);
	/* R */ inline WORD Year() const reflect_as(self->wYear);
public: // Property - Month
	/* W */ inline auto &Month(WORD wMonth) reflect_to_self(self->wMonth = wMonth);
	/* R */ inline WORD Month() const reflect_as(self->wMonth);
public: // Property - Day
	/* W */ inline auto &Day(WORD wDay) reflect_to_self(self->wDay = wDay);
	/* R */ inline WORD Day() const reflect_as(self->wDay);
public: // Property - Hour
	/* W */ inline auto &Hour(WORD wHour) reflect_to_self(self->wHour = wHour);
	/* R */ inline WORD Hour() const reflect_as(self->wHour);
public: // Property - Minute
	/* W */ inline auto &Minute(WORD wMinute) reflect_to_self(self->wMinute = wMinute);
	/* R */ inline WORD Minute() const reflect_as(self->wMinute);
public: // Property - Second
	/* W */ inline auto &Second(WORD wSecond) reflect_to_self(self->wSecond = wSecond);
	/* R */ inline WORD Second() const reflect_as(self->wSecond);
public: // Property - MilliSeconds
	/* W */ inline auto &MilliSeconds(WORD wMilliseconds) reflect_to_self(self->wMilliseconds = wMilliseconds);
	/* R */ inline WORD MilliSeconds() const reflect_as(self->wMilliseconds);
public: // FormatDate
	template<bool IsUnicode = WX::IsUnicode>
	inline StringX<IsUnicode> FormatDate(Locales locale = Locales::Default, DateFormat df = DateFormat::Default, LPCXSTR<IsUnicode> lpFormat = O) const {
		int len = WX::GetDateFormat(locale.yield(), df.yield(), this, lpFormat, O, 0);
		auto lpsz = StringX<IsUnicode>::Alloc(len - 1);
		WX::GetDateFormat(locale.yield(), df.yield(), this, lpFormat, lpsz, len);
		return{ (size_t)len, lpsz };
	}
	inline StringA FormatDate(Locales locale, DateFormat df, LPCSTR lpFormat) const reflect_as(FormatDate<false>(locale, df, lpFormat));
	inline StringW FormatDate(Locales locale, DateFormat df, LPCWSTR lpFormat) const reflect_as(FormatDate<true>(locale, df, lpFormat));
	inline StringA FormatDateA(Locales locale = Locales::Default, DateFormat df = DateFormat::Default, LPCSTR lpFormat = O) const reflect_as(FormatDate<false>(locale, df, lpFormat));
	inline StringW FormatDateW(Locales locale = Locales::Default, DateFormat df = DateFormat::Default, LPCWSTR lpFormat = O) const reflect_as(FormatDate<true>(locale, df, lpFormat));
	inline StringW FormatDate(LPCWSTR lpLocaleName, DateFormat df = DateFormat::Default, LPCWSTR lpFormat = O) const {
		int len = WX::GetDateFormat(lpLocaleName, df.yield(), this, lpFormat, O, 0, O);
		auto lpsz = StringW::Alloc(len - 1);
		WX::GetDateFormat(lpLocaleName, df.yield(), this, lpFormat, lpsz, len, O);
		return{ (size_t)len, lpsz };
	}
public: // FormatTime
	template<bool IsUnicode = WX::IsUnicode>
	inline StringX<IsUnicode> FormatTime(Locales locale = Locales::Default, TimeFormat tf = TimeFormat::Default, LPCXSTR<IsUnicode> lpFormat = O) const {
		int len = WX::GetTimeFormat(locale.yield(), tf.yield(), this, lpFormat, O, 0);
		auto lpsz = StringX<IsUnicode>::Alloc(len - 1);
		GetTimeFormat(locale.yield(), tf.yield(), this, lpFormat, lpsz, len);
		return{ (size_t)len, lpsz };
	}
	inline StringA FormatTime(Locales locale, TimeFormat tf, LPCSTR lpFormat) const reflect_as(FormatTime<false>(locale, tf, lpFormat));
	inline StringW FormatTime(Locales locale, TimeFormat tf, LPCWSTR lpFormat) const reflect_as(FormatTime<true>(locale, tf, lpFormat));
	inline StringA FormatTimeA(Locales locale = Locales::Default, TimeFormat tf = TimeFormat::Default, LPCSTR lpFormat = O) const reflect_as(FormatTime<false>(locale, tf, lpFormat));
	inline StringW FormatTimeW(Locales locale = Locales::Default, TimeFormat tf = TimeFormat::Default, LPCWSTR lpFormat = O) const reflect_as(FormatTime<true>(locale, tf, lpFormat));
	inline StringW FormatTime(LPCWSTR lpLocaleName, TimeFormat tf = TimeFormat::Default, LPCWSTR lpFormat = O) const {
		int len = WX::GetTimeFormat(lpLocaleName, tf.yield(), this, lpFormat, O, 0);
		auto lpsz = StringW::Alloc(len - 1);
		WX::GetTimeFormat(lpLocaleName, tf.yield(), this, lpFormat, lpsz, len);
		return{ (size_t)len, lpsz };
	}
public:
	template<bool IsUnicode = WX::IsUnicode>
	inline StringX<IsUnicode> toString() const {
		int lenDate = WX::GetDateFormat(LOCALE_CUSTOM_DEFAULT, 0, this, (LPCXSTR<IsUnicode>)O, O, 0);
		int lenTime = WX::GetTimeFormat(LOCALE_CUSTOM_DEFAULT, 0, this, (LPCXSTR<IsUnicode>)O, O, 0);
		auto lpsz = StringX<IsUnicode>::Alloc(lenDate + lenTime - 1);
		WX::GetDateFormat(LOCALE_CUSTOM_DEFAULT, 0, this, O, lpsz, lenDate);
		WX::GetTimeFormat(LOCALE_CUSTOM_DEFAULT, 0, this, O, lpsz + lenDate, lenTime);
		lpsz[lenDate - 1] = ' ';
		return{ (size_t)(lenDate + lenTime - 1), lpsz };
	}
	inline StringA toStringA() const reflect_as(toString<false>());
	inline StringW toStringW() const reflect_as(toString<true>());

public:
	inline operator StringA() const reflect_as(toStringA());
	inline operator StringW() const reflect_as(toStringW());
	inline operator FILETIME() const assertl_reflect_to(FILETIME ft, SystemTimeToFileTime(this, &ft), ft);
};
using SysTime = SystemTime;
class FileTime : public RefStruct<FILETIME> {
public:
	using super = RefStruct<FILETIME>;
public:
	FileTime() {}
	FileTime(const FILETIME &ft) : super(ft) {}
	FileTime(LARGE_INTEGER li) { ref_as<LARGE_INTEGER>(self) = li; }
	FileTime(const SYSTEMTIME &st) assertl(SystemTimeToFileTime(&st, this));
public:
	static inline FileTime SystemTime() reflect_to(FileTime ft; GetSystemTimeAsFileTime(&ft), ft);
public:
	inline FileTime ToLocal() assertl_reflect_to(FILETIME ft, FileTimeToLocalFileTime(this, &ft), ft);
	inline FileTime ToUniversal() assertl_reflect_to(FILETIME ft, LocalFileTimeToFileTime(this, &ft), ft);
public:
	template<bool IsUnicode = WX::IsUnicode>
	inline StringX<IsUnicode> toString() const reflect_as(SysTime(self).toString<IsUnicode>());
	inline StringA toStringA() const reflect_as(toString<false>());
	inline StringW toStringW() const reflect_as(toString<true>());

public:
	inline operator StringA() const reflect_as(toStringA());
	inline operator StringW() const reflect_as(toStringW());
	inline operator SYSTEMTIME() const assertl_reflect_to(SYSTEMTIME st, FileTimeToSystemTime(this, &st), st);
	inline operator LARGE_INTEGER() const reflect_as(reuse_as<LARGE_INTEGER>(*this));
};
#pragma endregion

#pragma region Point Size Rect
struct LPoint : public POINT {
public:
	LPoint() : POINT{ 0 } {}
	LPoint(const POINT &p) : POINT(p) {}
	LPoint(const LPoint &p) : POINT(p) {}
	LPoint(LONG a) : POINT{ a, a } {}
	LPoint(LONG x, LONG y) : POINT{ x, y } {}
	LPoint(const SIZE &s) : POINT{ s.cx, s.cy } {}
	LPoint(COORD c) : POINT{ c.X, c.Y } {}
public:
	template<bool IsUnicode>
	inline StringX<IsUnicode> toString() const {
		auto_stringx(fmt, "{ x: %d, y: %d }");
		return format(fmt, x, y);
	}
	inline StringA toStringA() const reflect_as(toString<false>());
	inline StringW toStringW() const reflect_as(toString<true>());
public:
	inline operator LPARAM() const reflect_as((LPARAM)this);
	inline operator COORD() const reflect_as({ (SHORT)x, (SHORT)y });
	inline operator SIZE() const reflect_as({ x, y });
	inline LPoint  operator+ () const reflect_to_self();
	inline LPoint  operator~ () const reflect_as({ y,  x });
	inline LPoint  operator* (double l) const reflect_as({ LONG((double)x * l), LONG((double)y * l) });
	inline LPoint  operator/ (double l) const reflect_as({ LONG((double)x / l), LONG((double)y / l) });
	inline LPoint  operator* (int l) const reflect_as({ x * l, y * l });
	inline LPoint  operator/ (int l) const reflect_as({ x / l, y / l });
	inline LPoint  operator- () const reflect_as({ -x, -y });
	inline LPoint  operator+ (POINT s) const reflect_as({ x + s.x, y + s.y });
	inline LPoint  operator- (POINT s) const reflect_as({ x - s.x, y - s.y });
	inline LPoint &operator*=(double p) reflect_to_self(x = LONG((double)x * p), y = LONG((double)y * p));
	inline LPoint &operator/=(double p) reflect_to_self(x = LONG((double)x / p), y = LONG((double)y / p));
	inline LPoint &operator+=(POINT p) reflect_to_self(x += p.x, y += p.y);
	inline LPoint &operator-=(POINT p) reflect_to_self(x -= p.x, y -= p.y);
	inline LPoint &operator =(POINT p) reflect_to_self(x = p.x, y = p.y);
	inline bool    operator==(POINT pt) const reflect_as(pt.x == x && pt.y == y);
	inline bool    operator!=(POINT pt) const reflect_as(pt.x != x || pt.y != y);
};
struct LSize : public SIZE {
public:
	LSize() : SIZE{ 0 } {}
	LSize(const SIZE &s) : SIZE(s) {}
	LSize(const LSize &s) : SIZE(s) {}
	LSize(LONG c) : SIZE{ c, c } {}
	LSize(LONG cx, LONG cy) : SIZE{ cx, cy } {}
	LSize(COORD c) : SIZE{ c.X, c.Y } {}
	LSize(POINT p) : SIZE{ p.x, p.y } {}
public:
	inline auto Square() const reflect_as(cx * cy);
public:
	template<bool IsUnicode>
	inline StringX<IsUnicode> toString() const {
		auto_stringx(fmt, "{ cx: %d, cy: %d }");
		return format(fmt, cx, cy);
	}
	inline StringA toStringA() const reflect_as(toString<false>());
	inline StringW toStringW() const reflect_as(toString<true>());
public:
	inline operator LPARAM() const reflect_as((LPARAM)this);
	inline operator COORD() const reflect_as({ (SHORT)cx, (SHORT)cy });
	inline LSize  operator+ () const reflect_to_self();
	inline LSize  operator- () const reflect_as({ -cx, -cy });
	inline LSize  operator~ () const reflect_as({ cy,  cx });
	inline LSize  operator* (double l) const reflect_as({ LONG((double)cx * l), LONG((double)cy * l) });
	inline LSize  operator/ (double l) const reflect_as({ LONG((double)cx / l), LONG((double)cy / l) });
	inline LSize  operator* (int l) const reflect_as({ cx * l, cy * l });
	inline LSize  operator/ (int l) const reflect_as({ cx / l, cy / l });
	inline LSize  operator+ (const LSize &s) const reflect_as({ cx + s.cx, cy + s.cy });
	inline LSize  operator- (const LSize &s) const reflect_as({ cx - s.cx, cy - s.cy });
	inline LSize &operator*=(double p) reflect_to_self(cx = LONG((double)cx * p), cy = LONG((double)cy * p));
	inline LSize &operator/=(double p) reflect_to_self(cx = LONG((double)cx / p), cy = LONG((double)cy / p));
	inline LSize &operator+=(const LSize &p) reflect_to_self(cx += p.cx, cy += p.cy);
	inline LSize &operator-=(const LSize &p) reflect_to_self(cx -= p.cx, cy -= p.cy);
	inline LSize &operator =(const LSize &p) reflect_to_self(cx = p.cx, cy = p.cy);
	inline bool   operator==(LSize sz) const reflect_as(sz.cx == cx && sz.cy == cy);
	inline bool   operator!=(LSize sz) const reflect_as(sz.cx != cx || sz.cy != cy);
};
enum_flags(LAlign, BYTE,
	Left	= 1 << 0,
	Right	= 2 << 0,
	HCenter = 3 << 0,
	Top		= 1 << 2,
	Bottom  = 2 << 2,
	VCenter = 3 << 2);
struct LRect : public RECT {
public:
	LRect() : RECT{ 0 } {}
	LRect(const RECT &rc) : RECT(rc) {}
	LRect(const LRect &rc) : RECT(rc) {}
	LRect(LONG a) : RECT{ a, a, a, a } {}
	LRect(LONG left, LONG top, LONG right, LONG bottom) : RECT{ left, top, right, bottom } {}
//	LRect(const MARGINS &m) : RECT({ m.cxLeftWidth, m.cyTopHeight, m.cxRightWidth, m.cyBottomHeight }) {}
	LRect(SMALL_RECT s) : RECT{ s.Left, s.Top, s.Right, s.Bottom } {}
	LRect(SIZE sz) : RECT{ 0, 0, sz.cx - 1, sz.cy - 1 } {}
	LRect(POINT p0,  POINT p1) : RECT{ p0.x, p0.y, p1.x, p1.y } {}
public:
	static inline LRect left_top(LPoint lt, LSize sz) reflect_as({ lt.x, lt.y, lt.x + sz.cx - 1, lt.y + sz.cy - 1 });
public:
	inline auto xsize() const reflect_as(right - left + 1);
	inline auto ysize() const reflect_as(bottom - top + 1);
	inline LSize size() const reflect_as({ xsize(), ysize() });
	inline auto  dx()           const reflect_as(right - left);
	inline auto  dy()           const reflect_as(bottom - top);
	inline LSize d()            const reflect_as({ dx(), dy() });
	inline auto &xmove(LONG dx) reflect_to_self(right += dx, left += dx);
	inline auto &ymove(LONG dy) reflect_to_self(bottom += dy, top += dy);
	LRect &align(LAlign a, const LRect &r2) {
		if (a == LAlign::HCenter)
			xmove((r2.left + r2.right - left - right) / 2);
		elif(a <= LAlign::Right) {
			left += r2.right - right;
			right = r2.right;
		}
		else /* if (a <= LAlign::Left) */ {
			right += r2.left - left;
			left = r2.left;
		}
		if (a == LAlign::VCenter)
			ymove((r2.top + r2.bottom - top - bottom) / 2);
		elif(a <= LAlign::Bottom) {
			top += r2.bottom - bottom;
			bottom = r2.bottom;
		}
		else /* if (a & LAlign::Top) */ {
			bottom += r2.top - top;
			top = r2.top;
		}
		retself;
	}
public:
	inline auto x0() const reflect_as(left);
	inline auto y0() const reflect_as(top);
	inline auto x1() const reflect_as(right);
	inline auto y1() const reflect_as(bottom);
public:
	template<bool IsUnicode>
	inline StringX<IsUnicode> toString() const {
		auto_stringx(fmt, "{ left: %d, top: %d, right: %d, bottom: %d }");
		return format(fmt, left, top, right, bottom);
	}
	inline StringA toStringA() const reflect_as(toString<false>());
	inline StringW toStringW() const reflect_as(toString<true>());
public: // Property - left_top
	inline LPoint left_top()     const reflect_as({ left,  top });
	inline auto   &left_top(LPoint lt) reflect_to_self(left = lt.x, top = lt.y);
public: // Property - left_bottom
	inline LPoint left_bottom()    const reflect_as({ left,  bottom });
	inline auto  &left_bottom(LPoint lt) reflect_to_self(left = lt.x, bottom = lt.y);
public: // Property - right_top
	inline LPoint right_top()    const reflect_as({ right, top });
	inline auto  &right_top(LPoint rt) reflect_to_self(right = rt.x, top = rt.y);
public: // Property - right_bottom
	inline LPoint right_bottom() const reflect_as({ right, bottom });
	inline auto  &right_bottom(LPoint rb) reflect_to_self(right = rb.x, bottom = rb.y);
public:
	inline operator StringA() const reflect_as(toStringA());
	inline operator StringW() const reflect_as(toStringW());
	inline operator SIZE()   const reflect_as({ right - left + 1, bottom - top + 1 });
	inline operator LSize()   const reflect_as({ right - left + 1, bottom - top + 1 });
	inline operator LPRECT()        reflect_as(this);
	inline operator LPCRECT() const reflect_as(this);
	inline operator LPARAM()  const reflect_as((LPARAM)this);
//	inline operator MARGINS() const reflect_as({ left, right, top, bottom });
	inline operator SMALL_RECT() const reflect_as({ (SHORT)left, (SHORT)top, (SHORT)right, (SHORT)bottom });
	inline LRect  operator+ () const reflect_to_self();
	inline LRect  operator- () const reflect_as({ -left,   -top, -right, -bottom });
	inline LRect  operator~ () const reflect_as({ right, bottom,   left,     top });
	inline LRect  operator+ (const RECT &r) const reflect_as({ left + r.left, top + r.top, right + r.right, bottom + r.bottom });
	inline LRect  operator- (const RECT &r) const reflect_as({ left - r.left, top - r.top, right - r.right, bottom - r.bottom });
	inline LRect  operator+ (POINT p) const reflect_as({ left + p.x, top + p.y, right + p.x, bottom + p.y });
	inline LRect  operator- (POINT p) const reflect_as({ left - p.x, top - p.y, right - p.x, bottom - p.y });
	inline LRect  operator* (double l) const reflect_as({ LONG((double)left * l), LONG((double)top * l), LONG((double)right * l), LONG((double)bottom * l) });
	inline LRect  operator/ (double l) const reflect_as({ LONG((double)left / l), LONG((double)top / l), LONG((double)right / l), LONG((double)bottom / l) });
	inline LRect  operator* (int l ) const reflect_as({ left * l, top * l, right * l, bottom * l });
	inline LRect  operator/ (int l) const reflect_as({ left / l, top / l, right / l, bottom / l });
	inline LRect &operator*=(double l) reflect_to_self(left = LONG((double)left * l), top = LONG((double)top * l), right = LONG((double)right * l), bottom = LONG((double)bottom * l));
	inline LRect &operator/=(double l) reflect_to_self(left = LONG((double)left / l), top = LONG((double)top / l), right = LONG((double)right / l), bottom = LONG((double)bottom / l));
	inline LRect &operator/=(int l) reflect_to_self(left /= l, top /= l, right /= l, bottom /= l);
	inline LRect &operator*=(int l) reflect_to_self(left *= l; top *= l, right *= l, bottom *= l);
	inline LRect &operator+=(const RECT &r) reflect_to_self(left += r.left, top += r.top, right += r.right, bottom += r.bottom);
	inline LRect &operator-=(const RECT &r) reflect_to_self(left -= r.left, top -= r.top, right -= r.right, bottom -= r.bottom);
	inline LRect &operator+=(POINT p) reflect_to_self(left += p.x, top += p.y, right += p.x, bottom += p.y);
	inline LRect &operator-=(POINT p) reflect_to_self(left -= p.x, top -= p.y, right -= p.x, bottom -= p.y);
};
inline LRect operator+(LPoint p, const LRect &r) reflect_as(r + p);
inline LRect operator-(LPoint p, const LRect &r) reflect_as(-(r - p));
#pragma endregion

#pragma region Message Wrapper
class Message : public RefStruct<MSG> {
public:
	using super = RefStruct<MSG>;
public:
	Message() {}
	Message(const MSG &msg) : super(msg) {}
	Message(HWND hwnd, UINT  message, WPARAM wParam, LPARAM lParam) : super(MSG{ hwnd, message, wParam, lParam }) {}
public: // Property - Window
	/* W */ inline auto&Window(HWND hwnd) reflect_as(self->hwnd);
	/* R */ inline auto Window() const reflect_as(self->hwnd);
public: // Property - ID
	/* W */ inline auto&ID(UINT msgid) reflect_to_self(self->message = msgid);
	template<class AnyEnum = UINT>
	/* R */ inline AnyEnum ID() const reflect_as(reuse_as<AnyEnum>(self->message));
public: // Property - ParamW
	template<class AnyType = WPARAM>
	/* W */ inline auto&ParamW(AnyType wParam) reflect_to_self(self->wParam = small_cast<WPARAM>(wParam));
	template<class AnyType = WPARAM>
	/* R */ inline AnyType ParamW() const reflect_as(big_cast<AnyType>(self->wParam));
public: // Property - ParamL
	template<class AnyType = WPARAM>
	/* W */ inline auto&ParamL(AnyType lParam) reflect_to_self(self->lParam = small_cast<LPARAM>(lParam));
	template<class AnyType = WPARAM>
	/* R */ inline AnyType ParamL() const reflect_as(big_cast<AnyType>(self->lParam));
public: // Property - Param
	template<class WParam = WPARAM, class LParam = LPARAM>
	/* W */ inline auto&Param(WParam wParam, LParam lParam) reflect_to_self(self->wParam = small_cast<WPARAM>(wParam), self->lParam = small_cast<LPARAM>(lParam));
public: // Property - Time
	/* W */ inline auto &Time(DWORD time) reflect_to_self(self->time = time);
	/* R */ inline DWORD Time() const reflect_as(self->time);
public: // Property - Point
	/* W */ inline auto  &Point(POINT pt) reflect_to_self(self->pt = pt);
	/* R */ inline LPoint Point() const reflect_as(self->pt);
public:
	inline bool Translate() const reflect_as(WX::TranslateMessage(this));
public:
	template<class RetType = LRESULT, bool IsUnicode = WX::IsUnicode>
	inline RetType Dispatch() const reflect_as((RetType)DispatchMessage<IsUnicode>(this));
public:
	template<class RetType = LRESULT, bool IsUnicode = WX::IsUnicode>
	inline RetType Send() const reflect_as((RetType)SendMessage<IsUnicode>(self->hwnd, self->message, self->wParam, self->lParam));
public:
	template<bool IsUnicode = WX::IsUnicode>
	inline void Post() reflect_to(WX::PostMessage<IsUnicode>(self->hwnd, self->message, self->wParam, self->lParam));
public:
	template<bool IsUnicode = WX::IsUnicode>
	inline bool Get(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_as(WX::GetMessage<IsUnicode>(this, O, wMsgFilterMin, wMsgFilterMax));
	template<bool IsUnicode = WX::IsUnicode>
	inline bool Get(HWND hwnd, UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_as(WX::GetMessage<IsUnicode>(this, hwnd, wMsgFilterMin, wMsgFilterMax));
	template<bool IsUnicode = WX::IsUnicode>
	inline bool GetThread(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_as(WX::GetMessage<IsUnicode>(this, (HWND)-1, wMsgFilterMin, wMsgFilterMax));
public:
	template<bool IsUnicode = WX::IsUnicode>
	inline bool GetSafe(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_as(WX::GetMessage<IsUnicode>(this, O, wMsgFilterMin, wMsgFilterMax));
	template<bool IsUnicode = WX::IsUnicode>
	inline bool GetSafe(HWND hwnd, UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_as(WX::GetMessage<IsUnicode>(this, hwnd, wMsgFilterMin, wMsgFilterMax));
	template<bool IsUnicode = WX::IsUnicode>
	inline bool GetThreadSafe(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_as(WX::GetMessage<IsUnicode>(this, (HWND)-1, wMsgFilterMin, wMsgFilterMax));
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
		inline auto&Remove() reflect_to_self(this->wRemoveMsg |= PM_REMOVE);
		inline auto&NoYield() reflect_to_self(this->wRemoveMsg |= PM_NOYIELD);
		inline auto&Input() reflect_to_self(this->wRemoveMsg |= PM_QS_INPUT);
		inline auto&Paint() reflect_to_self(this->wRemoveMsg |= PM_QS_PAINT);
		inline auto&MessagePost() reflect_to_self(this->wRemoveMsg |= PM_QS_POSTMESSAGE);
		inline auto&MessageSend() reflect_to_self(this->wRemoveMsg |= PM_QS_SENDMESSAGE);
	public:
		inline operator bool() reflect_as(WX::PeekMessage<IsUnicode>(lpMsg, hwnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg));
	};
	inline Peeks Peek(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_as({ this, O, wMsgFilterMin, wMsgFilterMax });
	inline Peeks Peek(HWND hwnd, UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_as({ this, hwnd, wMsgFilterMin, wMsgFilterMax });
	inline Peeks PeekThread(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0) reflect_as({ this, (HWND)-1, wMsgFilterMin, wMsgFilterMax });
};
using Msg = Message;
class MessageException : public Exception {
	Message msg;
public:
	using super = Exception;
public:
	MessageException(const Exception &err, const Message &msg) : 
		super(err), msg(msg) {}
public:
	inline const WX::Msg &Msg() const reflect_as(msg);
	inline const WX::Msg &Message() const reflect_as(msg);
public:
	inline operator const WX::Msg &() const reflect_as(msg);
};
using MsgException = MessageException;
#pragma endregion

#pragma region MsgBox
enum_flags(MB, int,
	Ok                  = MB_OK,
	OkCancel            = MB_OKCANCEL,
	AbortRetryIgnore    = MB_ABORTRETRYIGNORE,
	YesNoCancel         = MB_YESNOCANCEL,
	YesNo               = MB_YESNO,
	RetryCancel         = MB_RETRYCANCEL,
	CancelTryContinue   = MB_CANCELTRYCONTINUE,
	IconHand            = MB_ICONHAND,
	IconQuestion        = MB_ICONQUESTION,
	IconExclamation     = MB_ICONEXCLAMATION,
	IconAsterisk        = MB_ICONASTERISK,
	UserIcon            = MB_USERICON,
	IconWarning         = MB_ICONWARNING,
	IconError           = MB_ICONERROR,
	IconInformation     = MB_ICONINFORMATION,
	IconStop            = MB_ICONSTOP,
	DefButton1          = MB_DEFBUTTON1,
	DefButton2          = MB_DEFBUTTON2,
	DefButton3          = MB_DEFBUTTON3,
	DefButton4          = MB_DEFBUTTON4,
	ApplModal           = MB_APPLMODAL,
	SystemModal         = MB_SYSTEMMODAL,
	TaskModal           = MB_TASKMODAL,
	Help                = MB_HELP,
	NoFocus             = MB_NOFOCUS,
	SetForeground       = MB_SETFOREGROUND,
	DefaultDesktopOnly  = MB_DEFAULT_DESKTOP_ONLY,
	TopMost             = MB_TOPMOST,
	Right               = MB_RIGHT,
	RtlReading          = MB_RTLREADING,
	ServiceNotification = MB_SERVICE_NOTIFICATION);
inline auto MsgBox(LPCSTR lpCaption, LPCSTR lpText = O, MB type = MB::Ok, HWND hParent = O)
	reflect_as(WX::MessageBox(hParent, lpText, lpCaption, type.yield()));
inline auto MsgBox(LPCWSTR lpCaption = O, LPCWSTR lpText = O, MB type = MB::Ok, HWND hParent = O)
	reflect_as(WX::MessageBox(hParent, lpText, lpCaption, type.yield()));
inline int MsgBox(LPCSTR lpCaption, const Exception &err, HWND hParent = O)
	reflect_as(MsgBox(lpCaption, err.toStringA(), MB::IconError | MB::AbortRetryIgnore, hParent));
inline int MsgBox(LPCWSTR lpCaption, const Exception &err, HWND hParent = O)
	reflect_as(MsgBox(lpCaption, err.toStringW(), MB::IconError | MB::AbortRetryIgnore, hParent));
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

class RGBColor {
protected:
	COLORREF cr;
public:
	RGBColor(COLORREF color) : cr(color) {}
	RGBColor(BYTE red, BYTE green, BYTE blue) :
		cr(RGB(red, green, blue)) {}
public:
	inline BYTE Red() const reflect_as(GetRValue(self));
	inline BYTE Green() const reflect_as(GetGValue(self));
	inline BYTE Blue() const reflect_as(GetBValue(self));
public:
	template<size_t len>
	static inline arrayof<RGBColor, len> &Attach(arrayof<COLORREF, len> &ary) reflect_as(ref_as<arrayof<RGBColor, len>>(ary));
	inline operator COLORREF() const { return cr; }
	static inline RGBColor &Attach(COLORREF &clr) reflect_as(*(RGBColor *)&clr);
};

}
