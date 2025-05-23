#pragma once

#include "wx_defs.h"

namespace WX {

#pragma region HandleBase
enum_flags(HandleAccess, DWORD,
		   Delete = DELETE,
		   ReadCtl = READ_CONTROL,
		   WriteDAC = WRITE_DAC,
		   WriteOwner = WRITE_OWNER,
		   Sync = SYNCHRONIZE,
		   GenericRead = GENERIC_READ,
		   GenericWrite = GENERIC_WRITE,
		   GenericExecute = GENERIC_EXECUTE,
		   GenericAll = GENERIC_ALL);
template<class AnyChild>
class HandleBase;
using Handle = HandleBase<void>;
template<class AnyChild>
class HandleBase : public ChainExtend<HandleBase<AnyChild>, AnyChild> {
protected:
	mutable HANDLE hObject = O;
public:
	using Child = KChain<HandleBase, AnyChild>;
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

	inline bool Close() {
		if (hObject)
			if (!CloseHandle(hObject))
				return false;
		hObject = O;
		return true;
	}

	inline bool Compare(HANDLE h) const reflect_as(CompareObjectHandles(self, h));
	//inline auto CopyTo() {
	//		DuplicateHandle(GetCurrentProcess(), self, 
	//			_In_ HANDLE hTargetProcessHandle,
	//			_Outptr_ LPHANDLE lpTargetHandle,

	//			_In_ DWORD dwDesiredAccess,
	//			_In_ BOOL bInheritHandle,
	//			_In_ DWORD dwOptions
	//		);
	//}
	inline bool WaitForSignal(DWORD dwMilliSec = INFINITE) const assertl_reflect_to(DWORD ret, (ret = WaitForSingleObject(self, dwMilliSec)) != WAIT_FAILED, ret == WAIT_OBJECT_0);
	inline bool WaitForAbandon(DWORD dwMilliSec = INFINITE) const assertl_reflect_to(DWORD ret, (ret = WaitForSingleObject(self, dwMilliSec)) != WAIT_FAILED, ret == WAIT_ABANDONED);

	class Duplication {
		using AnyAccess = typename Child::Access;
		HANDLE hSourceProcessHandle = GetCurrentProcess();
		HANDLE hSourceHandle;
		HANDLE hTargetProcessHandle;
		DWORD dwDesiredAccess;
		bool bInheritHandle = false;
		DWORD dwOptions = DUPLICATE_SAME_ACCESS;
	public:
		Duplication(HANDLE hSourceHandle, HANDLE hTargetProcessHandle) :
			hSourceHandle(hSourceHandle),
			hTargetProcessHandle(hTargetProcessHandle) {}
	public:
		inline auto &SourceProcess(HANDLE hSourceHandle) reflect_to_self(this->hSourceHandle = hSourceHandle);
		inline auto &Accesses(AnyAccess acs) reflect_to_self(this->dwDesiredAccess = acs.yield(), this->dwOptions &= ~DUPLICATE_SAME_ACCESS);
		inline auto &Inherit(bool bInheritHandle = true) reflect_to_self(this->bInheritHandle = bInheritHandle);
	public:
		inline operator Child() const assertl_reflect_to(
			HANDLE hTargetHandle = O,
			DuplicateHandle(
				hSourceProcessHandle, hSourceHandle,
				hTargetProcessHandle, &hTargetHandle,
				dwDesiredAccess, bInheritHandle,
				dwOptions), reuse_as<Child>(hTargetHandle));
	};
	inline Duplication Duplicate(HANDLE hTargetProcessHandle) reflect_as({ hObject, hTargetProcessHandle });

public: // Property - Information
	/* W */ inline auto &Information(DWORD dwMask, DWORD dwFlags) assertl_reflect_as_child(SetHandleInformation(self, dwMask, dwFlags));
	/* R */ inline DWORD Information(DWORD dwMask) const assertl_reflect_to(DWORD dwFlags = 0, GetHandleInformation(self, &dwFlags), dwFlags &dwMask);
public: // Property - Inherit
	/* W */ inline auto &Inherit(bool bInherit) reflect_to_child(Information(HANDLE_FLAG_INHERIT, bInherit ? HANDLE_FLAG_INHERIT : 0));
	/* R */ inline bool  Inherit() const reflect_as(Information(HANDLE_FLAG_INHERIT));
public: // Property - ProtectFromClose
	/* W */ inline auto &ProtectFromClose(bool bProtected) reflect_to_child(Information(HANDLE_FLAG_PROTECT_FROM_CLOSE, bProtected ? HANDLE_FLAG_PROTECT_FROM_CLOSE : 0));
	/* R */ inline bool  ProtectFromClose() const reflect_as(Information(HANDLE_FLAG_PROTECT_FROM_CLOSE));

	inline operator bool() const reflect_as(hObject &&hObject != INVALID_HANDLE_VALUE);
	inline operator HANDLE() const reflect_as(hObject);
	inline operator const Handle() const reflect_as(ref_as<Handle>(self));

	inline Child &operator=(Child &obj) reflect_to_child(std::swap(obj.hObject, hObject));
	inline Child &operator=(Child &&obj) reflect_to_child(std::swap(obj.hObject, hObject));
	inline const Child &operator=(const Child &obj) const reflect_to_child(std::swap(obj.hObject, hObject));

	static inline auto &Attach(HANDLE &hObj) reflect_as(ref_as<Child>(hObj));
	static inline auto &Attach(const HANDLE &hObj) reflect_as(ref_as<const Child>(hObj));
};
#define BaseOf_Handle(name) name : public WX::HandleBase<name>
#pragma endregion

#pragma region Memory

#pragma region Local
enum_flags(LocalAllocFlags, UINT,
		   enum_default Fixed = LMEM_FIXED,
		   Modify = LMEM_MODIFY,
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
} inline LocalHeap;
#pragma endregion

#pragma region Heap
class HeapSummary : protected HEAP_SUMMARY {
public:
	HeapSummary() : HEAP_SUMMARY{ 0 } reflect_to(this->cb = sizeof(*this));
	HeapSummary(Null) : HeapSummary() {}
	HeapSummary(const HEAP_SUMMARY &hs) : HEAP_SUMMARY(hs) {}
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
public:
	inline LPHEAP_SUMMARY operator&() reflect_as(this);
};
enum_flags(HeapAllocFlag, UINT,
		   enum_default Fixed = 0,
		   GenerateExceptions = HEAP_GENERATE_EXCEPTIONS,
		   NoSerialize = HEAP_NO_SERIALIZE,
		   ZeroInit = HEAP_ZERO_MEMORY);
using HAF = HeapAllocFlag;
class Heap;
using CHeap = RefAs<Heap>;
class BaseOf_Handle(Heap) {
protected:
	using super = HandleBase<Heap>;
	Heap(HANDLE hHeap) : super(hHeap) {}
public:
	using Summary = HeapSummary;
	using AllocFlags = HeapAllocFlag;

	Heap() : super(GetProcessHeap()) {}
	Heap(Null) {}
	Heap(Heap & h) : super(h) {}
	Heap(Heap && h) : super(h) {}
	Heap(const Heap &) = delete;
	~Heap() reflect_to(Destroy());

	using super::operator=;

	static inline Heap Create(DWORD flOptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize) reflect_as(HeapCreate(flOptions, dwInitialSize, dwMaximumSize));

	static Heap This;

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

	inline size_t Sizeof(const void *ptr, DWORD flags) const assertl_reflect_as(auto size = HeapSize(self, flags, ptr), size);
	inline bool IsValid(const void *ptr, DWORD flags) const reflect_as(HeapValidate(self, flags, ptr));

	inline auto &Lock() assertl_reflect_as_self(HeapLock(self));
	inline auto &Unlock() assertl_reflect_as_self(HeapUnlock(self));

	//	HeapWalk();
	//	SIZE_T HeapCompact(HANDLE hHeap, DWORD dwFlags);

public: // Property - Summaries
	inline Summary Summaries(DWORD dwFlags = 0) const assertl_reflect_to(Summary s, ::HeapSummary(self, dwFlags, &s), s);

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
};
inline Heap Heap::This = GetProcessHeap();
#pragma endregion

template<class HeapType, class AnyType = void>
class AutoPointer {
	HeapType &heap;
	mutable AnyType *p = O;
public:
	using AllocFlags = typename HeapType::AllocFlags;
	AutoPointer() : heap(Heap::This) {}
	explicit AutoPointer(size_t size) : heap(Heap::This), p(heap.Alloc(size)) {}
	AutoPointer(AllocFlags flags, size_t size = SizeOf<AnyType>) : heap(Heap::This), p((AnyType *)heap.Alloc(size, flags)) {}
	explicit AutoPointer(HeapType &heap) : heap(heap) {}
	~AutoPointer() reflect_to(Free());

	inline AnyType *Alloc(size_t size = SizeOf<AnyType>) {
		if (size <= 0)
			Free();
		if (p)
			p = (AnyType *)heap.Realloc(p, size);
		else
			p = (AnyType *)heap.Alloc(size);
		return p;
	}
	template<class AnyFlags>
	inline AnyType *Alloc(size_t size, AnyFlags flags) {
		if (p)
			p = (AnyType *)heap.Realloc(p, size, flags);
		else
			p = (AnyType *)heap.Alloc(size, flags);
		return p;
	}

	inline void Free() {
		if (p) heap.Free(p);
		p = O;
	}

	inline AnyType *&operator*() reflect_as(p);
	inline const AnyType *&operator*() const reflect_as(p);
	inline AnyType *operator&() reflect_as(p);
	inline const AnyType *operator&() const reflect_as(p);
	inline AnyType *operator->() reflect_as(p);
	inline const AnyType *operator->() const reflect_as(p);
};
#pragma endregion

// constexpr UINT MaxLenDefault = 512;
constexpr UINT MaxLenPath = MAX_PATH;
constexpr UINT MaxLenTitle = MaxLenPath * 3;
constexpr UINT MaxLenClass = MaxLenTitle * 2;
constexpr UINT MaxLenNotice = 32767;

#pragma region String

enum_class(CodePages, UINT,
		   Active = CP_ACP,
		   OEM = CP_OEMCP,
		   Macintosh = CP_MACCP,
		   ThreadActive = CP_THREAD_ACP,
		   Symbol = CP_SYMBOL,
		   UTF7 = CP_UTF7,
		   UTF8 = CP_UTF8);
enum StrFlags : size_t {
	STR_DEF = 0,
	STR_READONLY = 1,
	STR_MOVABLE = 2,
	STR_RELEASE = 4
};

template<class CharType> String Fits(const CharType *lpString, size_t MaxLen, CodePages cp = CodePages::Active);
template<class CharType = TCHAR> const StringBase<CharType> CString(size_t uLen, const CharType *lpString);
template<class CharType = TCHAR> const StringBase<CharType> CString(const CharType *lpString, size_t maxLen);
template<class CharType>
inline size_t Length(const CharType *lpString, size_t MaxLen) {
	if constexpr (std::is_same_v<CharType, CHAR>)
		assertl(SUCCEEDED(StringCchLengthA(lpString, MaxLen, &MaxLen)))
	else if constexpr (std::is_same_v<CharType, WCHAR>)
		assertl(SUCCEEDED(StringCchLengthW(lpString, MaxLen, &MaxLen)));
	return MaxLen;
}

template<class CharType>
class StringBase {
	mutable CharType *lpsz = O;
	mutable size_t Len : sizeof(void *) * 8 - 3;
	mutable size_t Flags : 3;
private:
	template<class _CharType>
	friend String Fits(const _CharType *lpString, size_t MaxLen, CodePages cp);
	template<class _CharType> friend const StringBase<_CharType> CString(size_t uLen, const _CharType *lpString);
	template<class _CharType> friend const StringBase<_CharType> CString(const _CharType *lpString, size_t maxLen);

	StringBase(size_t len, UINT flags, CharType *lpBuffer) :
		lpsz(lpBuffer), Len((UINT)len), Flags(flags) {
		if (len <= 0 || !lpBuffer) {
			Len = 0;
			lpsz = O;
		}
	}
	StringBase(size_t len, const CharType *lpString) : StringBase(len, STR_READONLY, const_cast<CharType *>(lpString)) {}
public:
	StringBase() : Len(0), Flags(0) {}
	StringBase(Null) : Len(0), Flags(0) {}
	StringBase(const StringBase &) = delete;
	StringBase(StringBase &str) : StringBase(str.Len, str.Flags, str.lpsz) { str.Len = 0, str.Flags = STR_DEF, str.lpsz = 0; }
	StringBase(StringBase &&str) : StringBase(str.Len, str.Flags, str.lpsz) { str.Len = 0, str.Flags = STR_DEF, str.lpsz = 0; }

	explicit StringBase(size_t Len) : lpsz(Alloc(Len)), Len(Len), Flags(STR_MOVABLE | STR_RELEASE) {}
	StringBase(size_t Len, CharType *lpBuffer) : StringBase(Len, STR_MOVABLE | STR_RELEASE, lpBuffer) {}

	StringBase(CharType ch) : lpsz(Alloc(1)), Len(1), Flags(STR_MOVABLE | STR_RELEASE) reflect_to(lpsz[0] = ch);

	template<size_t len> StringBase(arrayof<CharType, len> &str) : StringBase(len - 1, STR_DEF, str) {}
	template<size_t len> StringBase(const arrayof<CharType, len> &str) : lpsz(const_cast<CharType *>(str)), Len(len - 1), Flags(STR_READONLY) {}
	template<size_t len> StringBase(const ConstArray<CharType, len> &str) : StringBase(str.array) {}

	~StringBase() { operator~(); }
public:
	static inline CharType *Realloc(size_t len, CharType *lpsz) {
		if (!lpsz && len <= 0) return O;
		if (len <= 0) {
			Free(lpsz);
			return O;
		}
		return (CharType *)HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, lpsz, (len + 1) * sizeof(TCHAR));
	}
	static inline CharType *Alloc(size_t len) {
		if (len == 0) return O;
		return (CharType *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (len + 1) * sizeof(TCHAR));
	}
	static inline void Free(void *lpsz) reflect_to(HeapFree(GetProcessHeap(), 0, lpsz));
public:
	inline auto &Trunc() {
		if (!(Flags & STR_MOVABLE))
			self = +self;
		Len = (UINT)WX::Length(lpsz, Len);
		lpsz = Realloc(Len, lpsz);
		retself;
	}
	inline auto &Resize(size_t NewLen) {
		if (!(Flags & STR_MOVABLE))
			self = +self;
		if (NewLen <= 0) retself;
		auto OldLen = WX::Length(lpsz, Len);
		Len = (UINT)NewLen;
		lpsz = Realloc(NewLen, lpsz);
		if (NewLen < OldLen)
			lpsz[OldLen] = 0;
		retself;
	}

	inline const StringBase str_safe() const { ///////////////////
		//		if (!Len || !lpsz) return _T("");
		if (!lpsz[Len]) return &*this;
		return +*this;
	}
	inline size_t Length() const reflect_as(lpsz ? Len : 0);
	inline size_t Size() const reflect_as(lpsz ? (Len + 1) * sizeof(TCHAR) : 0);

	inline CharType *begin() reflect_as(Len ? lpsz : O);
	inline CharType *end() reflect_as(Len &&lpsz ? lpsz + Len : O);
	inline const CharType *begin() const reflect_as(Len ? lpsz : O);
	inline const CharType *end() const reflect_as(Len &&lpsz ? lpsz + Len : O);
public:
	inline operator bool() const reflect_as(lpsz &&Len);
	inline operator CharType *() {
		if (!(Flags & STR_MOVABLE))
			self = +self;
		return Len ? lpsz : O;
	}
	inline operator LPCTSTR() const reflect_as(Len ? lpsz : O);
	inline StringBase operator&() reflect_as({ Len, 0, lpsz });
	inline const StringBase operator&() const reflect_as({ Len, lpsz });
	inline void operator~() const {
		if (lpsz && (Flags & STR_RELEASE))
			Free(lpsz);
		lpsz = O;
		Len = 0;
	}
	inline LPTSTR operator*() const {
		if (!lpsz || !Len) return O;
		LPTSTR lpsz = StringBase::Alloc(Len);
		CopyMemory(lpsz, this->lpsz, (Len + 1) * sizeof(CharType));
		lpsz[Len] = '\0';
		return lpsz;
	}
	inline StringBase operator+() const {
		if (!lpsz || !Len) return O;
		LPTSTR lpsz = StringBase::Alloc(Len);
		CopyMemory(lpsz, this->lpsz, (Len + 1) * sizeof(CharType));
		lpsz[Len] = '\0';
		return { Len, lpsz };
	}
	inline StringBase operator-() const {
		size_t nLen = WX::Length(lpsz, Len);
		if (nLen <= 0) return O;
		LPTSTR lpsz = StringBase::Alloc(nLen);
		CopyMemory(lpsz, this->lpsz, (nLen + 1) * sizeof(CharType));
		lpsz[nLen] = '\0';
		return{ nLen, lpsz };
	}

	auto operator=(StringBase &) const = delete;
	auto operator=(const StringBase &str) = delete;
	inline auto &operator=(StringBase &&str) noexcept {
		uintptr_t c;
		c = Len, Len = str.Len, str.Len = c;
		c = Flags, Flags = str.Flags, str.Flags = Flags;
		std::swap(lpsz, str.lpsz);
		retself;
	}
	inline auto &operator=(StringBase &str) noexcept {
		uintptr_t c;
		c = Len, Len = str.Len, str.Len = c;
		c = Flags, Flags = str.Flags, str.Flags = Flags;
		std::swap(lpsz, str.lpsz);
		retself;
	}
	inline auto &operator=(const StringBase &str) const noexcept {
		uintptr_t c;
		c = Len, Len = str.Len, str.Len = c;
		c = Flags, Flags = str.Flags, str.Flags = Flags;
		std::swap(lpsz, str.lpsz);
		retself;
	}
};

inline const StringA operator ""_A(LPCSTR lpString, size_t uLen) {
	if (uLen == 0 || !*lpString) return O;
	return CString(uLen, lpString);
}
inline const StringW operator ""_W(LPCWSTR lpString, size_t uLen) {
	if (uLen == 0 || !*lpString) return O;
	return CString(uLen, lpString);
}
inline const String operator ""_S(LPCTSTR lpString, size_t uLen) {
	if (uLen == 0 || !*lpString) return O;
	return CString(uLen, lpString);
}

template<class CharType>
inline const StringBase<CharType> CString(size_t Len, const CharType *lpString) {
	if (Len == 0 || !*lpString) return O;
	return { Len, lpString };
}
template<class CharType>
inline const StringBase<CharType> CString(const CharType *lpString, size_t MaxLen) {
	if (!lpString) return O;
	return { WX::Length(lpString, MaxLen), lpString };
}

template<class CharType>
inline String Fits(const CharType *lpString, size_t MaxLen, CodePages cp) {
	if (!lpString || !MaxLen) return O;
	auto uLen = WX::Length(lpString, MaxLen);
	if (!uLen) return O;
	if constexpr (std::is_same_v<CharType, TCHAR>) {
		auto lpsz = String::Alloc(uLen);
		CopyMemory(lpsz, lpString, (uLen + 1) * sizeof(TCHAR));
		return{ uLen, lpsz };
	}
	else {
		int tLen;
#ifdef UNICODE
		assertl((tLen = MultiByteToWideChar(cp.yield(), 0, lpString, (int)uLen, O, 0)) > 0);
#else
		assertl((tLen = WideCharToMultiByte(cp.yield(), 0, lpString, (int)uLen, O, 0, O, O)) > 0);
#endif
		// if (tLen != uLen) warnning glyphs missing 
		auto lpsz = String::Alloc(tLen);
#ifdef UNICODE
		assertl(tLen == MultiByteToWideChar(cp.yield(), 0, lpString, (int)uLen, lpsz, tLen));
#else
		assertl(tLen == WideCharToMultiByte(cp.yield(), 0, lpString, (int)uLen, lpsz, tLen, O, O));
#endif
		lpsz[tLen] = 0;
		return{ (size_t)tLen, lpsz };
	}
}

inline size_t CountAll(const String &src, const String &strTarget) {
	if (!src || !strTarget) return 0;
	if (src.Length() < strTarget.Length()) return 0;
	size_t count = 0;
	for (LPCTSTR li = src, hi = src.end(); li < hi; ) {
		LPCTSTR lj = strTarget, hj = strTarget.end();
		for (; lj < hj; ++lj)
			if (*li++ != *lj)
				break;
		if (lj < hj)
			++count;
	}
	return count;
}
inline String ReplaceAll(const String &src, const String &strTarget, const String &strWith = O) {
	auto count = CountAll(src, strTarget);
	if (count <= 0) return O;
	auto tLen = strTarget.Length();
	auto nLen = count * (strWith.Length() - strTarget.Length());
	String str(src.Length() + nLen);
	LPTSTR lpDst = str;
	for (LPCTSTR li = src, hi = src.end(); li < hi; ) {
		LPCTSTR lj = strTarget, hj = strTarget.end();
		for (; lj < hj; ++lj)
			if ((*lpDst++ = *li++) != *lj)
				break;
		if (lj < hj)
			continue;
		lpDst -= tLen;
		for (LPCTSTR lpwStr = strWith, lpwEnd = strWith.end(); lpwStr < lpwEnd; ++lpwStr)
			*lpDst++ = *lpwStr;
	}
	return str;
}

inline size_t LengthOf(const String &str) reflect_as(str.Length());
template<class... Args>
inline size_t LengthOf(const Args&... args) reflect_as((LengthOf((const String &)args) + ...));

inline LPTSTR Copies(LPTSTR lpBuffer) reflect_as((LPTSTR)lpBuffer);
template<class... Args>
inline LPTSTR Copies(LPTSTR lpBuffer, const String &str, const Args &... args) {
	auto uLen = str.Length();
	if (uLen > 0) assertl(StringCchCopy(lpBuffer, uLen + 1, str) == 0);
	return Copies(lpBuffer + uLen, args...);
}

inline String _Cats() reflect_as(O);
template<class... Args>
inline String _Cats(const String &str, const Args &... args) {
	if (auto uLength = LengthOf<const String &, const Args &...>(str, args...)) {
		String buff(uLength);
		*Copies(buff, str, args...) = 0;
		return buff;
	}
	return O;
}

inline void *Copy(void *lpDst) reflect_as(lpDst);
template<class... Args>
inline void *Copy(void *lpDst, const void *lpSrc, size_t uSize, Args... args) {
	if (!uSize) return Copy(lpDst, args...);
	CopyMemory(lpDst, lpSrc, uSize);
	return Copy(((uint8_t *)lpDst) + uSize, args...);
}

template<class AnyType>
inline void Fill(AnyType *lpArray, const AnyType &Sample, size_t Len) {
	while (Len--)
		CopyMemory(lpArray++, &Sample, sizeof(AnyType));
}

#pragma endregion

#pragma region Numeral Format 
enum class Symbol : uint8_t { Def = 0, Neg, Pos, Space };
enum class Cap : uint8_t { Small = 0, Big };
enum class Align : uint8_t { Space = 0, Zero };
enum class Rad : uint8_t { Dec = 0, Qua, Oct, Hex };
struct fmt_word {
	bool int_align : 1;
	Align int_blank : 1;
	bool int_trunc : 1;
	uint8_t int_calign : 5;

	bool float_align : 1;
	Align float_blank : 1;
	bool float_force : 1;
	uint8_t float_calign : 5;

	Symbol symbol : 2;
	Cap alfa_type : 1;
	bool right_dir : 1;
	Rad radix_type : 2;
};
template<class CharType>
static const CharType *fmt_push(fmt_word &fmt, const CharType *format) {
	auto ch = *format;
	if (ch == CharType(' ')) {
		fmt.right_dir = true;
		fmt.symbol = Symbol::Space;
		ch = *++format;
	}
	elif(ch == CharType('*')) {
		fmt.symbol = Symbol::Space;
		ch = *++format;
	}
	switch (ch) {
		case CharType('+'):
			fmt.symbol = Symbol::Pos;
			ch = *++format;
			break;
	}
	switch (ch) {
		case CharType('0'):
			fmt.int_blank = Align::Zero;
			fmt.int_align = true;
			ch = *++format;
			break;
		case CharType(' '):
			fmt.int_blank = Align::Space;
			fmt.int_align = true;
			ch = *++format;
			break;
	}
	if (ch == CharType('~')) {
		fmt.int_trunc = true;
		ch = *++format;
	}
	auto align = 0;
	while (CharType('0') <= ch && ch <= CharType('9')) {
		align *= 10;
		align += ch - CharType('0');
		if (align > 32)
			return nullptr; // overflow
		ch = *++format;
	}
	fmt.int_calign = align;
	if (ch == CharType('.')) {
		fmt.float_force = true;
		ch = *++format;
	}
	elif(ch == CharType('0')) {
		fmt.float_blank = Align::Zero;
		fmt.float_align = true;
		ch = *++format;
	}
	align = 0;
	while (CharType('0') <= ch && ch <= CharType('9')) {
		align *= 10;
		align += ch - CharType('0');
		if (align > 32)
			return nullptr; // overflow
		ch = *++format;
	}
	fmt.float_calign = align;
	if (ch == CharType(' ')) {
		fmt.float_blank = Align::Space;
		fmt.float_align = true;
		ch = *++format;
	}
	switch (ch) {
		case CharType('q'):
			fmt.radix_type = Rad::Qua;
			ch = *++format;
			break;
		case CharType('o'):
			fmt.radix_type = Rad::Oct;
			ch = *++format;
			break;
		case CharType('d'):
			fmt.radix_type = Rad::Dec;
			ch = *++format;
			break;
		case CharType('X'):
			fmt.alfa_type = Cap::Big;
			[[fallthrough]];
		case CharType('x'):
			fmt.radix_type = Rad::Hex;
			ch = *++format;
			break;
		default:
			return nullptr;
	}
	return format;
}
template<class CharType>
static inline bool fmt_single(fmt_word &fmt, const CharType *format) {
	if (!format) return false;
	if (auto hpformat = fmt_push(fmt, format))
		return hpformat[0] == _T('\0');
	return true;
}
struct format_numeral : public fmt_word {
public:
	format_numeral() : fmt_word{ 0 } {}
	format_numeral(fmt_word fmt) : fmt_word(fmt) {}
	format_numeral(const char *lpFormat) : fmt_word{ 0 } assertl(fmt_single(self, lpFormat));
	format_numeral(const wchar_t *lpFormat) : fmt_word{ 0 } assertl(fmt_single(self, lpFormat));
private:
	static inline auto __push(
		uintptr_t ui, LPTSTR hpString,
		TCHAR alfa, uint8_t radix,
		uint8_t int_trunc) {
		uint8_t len = 0;
		do {
			auto d_sm = ui / radix;
			auto rbit = (TCHAR)(ui - d_sm * radix);
			ui = d_sm;
			*--hpString = rbit + (rbit < 10 ? _T('0') : alfa);
		} while (ui && ++len < int_trunc);
		return hpString;
	}
	static inline auto __push(
		double pure_float, LPTSTR lpString,
		TCHAR alfa, uint8_t radix,
		uint8_t float_trunc) {
		uint8_t len = 0;
		while (pure_float > 0.f && len++ < float_trunc) {
			pure_float *= radix;
			auto rbit = (TCHAR)pure_float;
			pure_float -= rbit;
			*lpString++ = rbit + (rbit < 10 ? _T('0') : alfa);
		}
		return lpString;
	}
	static inline auto __moveH2L(LPTSTR lpString, LPTSTR hpString,
								 int uLength) {
		while (uLength--) *lpString++ = *hpString++;
		return lpString;
	}
private:
	inline uint8_t _radix() const reflect_as(radix_type == Rad::Dec ? 10 : (2 << (uint8_t)radix_type));
	inline TCHAR _alfa_char() const reflect_as((alfa_type == Cap::Big ? _T('A') : _T('a')) - 10);
	inline auto _push(uintptr_t uint_part, LPTSTR hpBuffer,
					  uint8_t radix, TCHAR alfa,
					  bool neg) const {
		auto lpBuffer = __push(uint_part, hpBuffer, alfa, radix, int_trunc ? int_calign : 32);
		auto int_len = hpBuffer - lpBuffer;
		if (int_len < int_calign && int_align) {
			auto fill = int_blank == Align::Space ?
				_T(' ') : _T('0');
			while (int_len++ < int_calign)
				*--lpBuffer = fill;
		}
		if (neg)
			*--lpBuffer = _T('-');
		elif(symbol == Symbol::Pos)
			*--lpBuffer = _T('+');
		elif(symbol == Symbol::Space)
			*--lpBuffer = _T(' ');
		if (right_dir)
			while (int_len++ < int_calign)
				*--lpBuffer = _T(' ');
		return lpBuffer;
	}
	inline auto _push(double float_part, LPTSTR lpBuffer,
					  uint8_t radix, TCHAR alfa) const {
		auto hpBuffer = __push(
			float_part, lpBuffer + 1,
			alfa, radix, float_calign);
		auto float_len = hpBuffer - lpBuffer - 1;
		if (float_align) {
			auto fill = float_blank == Align::Space ?
				_T(' ') : _T('0');
			while (float_len++ < int_calign)
				*hpBuffer++ = fill;
		}
		if (float_len > 0)
			*lpBuffer = _T('.');
		elif(float_force)
			*lpBuffer = _T('.');
		elif(float_align)
			*lpBuffer = _T(' ');
		else --hpBuffer;
		return hpBuffer;
	}
public:
	inline auto push(uintptr_t uint_part, LPTSTR lpBuffer, LPTSTR &hpBuffer, size_t maxLength) const {
		hpBuffer = lpBuffer + maxLength - 2;
		lpBuffer = _push(uint_part, hpBuffer, _radix(), _alfa_char(), false);
		return lpBuffer;
	}
	inline auto push(intptr_t int_part, LPTSTR lpBuffer, LPTSTR &hpBuffer, size_t maxLength) const {
		bool neg = int_part < 0;
		if (neg) int_part = -int_part;
		hpBuffer = lpBuffer + maxLength - 2;
		lpBuffer = _push((uintptr_t)int_part, hpBuffer, _radix(), _alfa_char(), neg);
		return lpBuffer;
	}
	inline auto push(double float_part, LPTSTR lpBuffer, LPTSTR &hpBuffer, size_t maxLength) const {
		auto rad = _radix();
		auto alfa = _alfa_char();
		bool neg = float_part < 0.;
		if (neg) float_part = -float_part;
		auto uint_part = (uintptr_t)float_part;
		hpBuffer = lpBuffer + maxLength - 2;
		lpBuffer = _push(uint_part, hpBuffer, rad, alfa, neg);
		auto lpBufferNew = lpBuffer - float_calign;
		hpBuffer = __moveH2L(lpBufferNew, lpBuffer, (int)(hpBuffer - lpBuffer));
		lpBuffer = lpBufferNew;
		hpBuffer = _push(float_part - uint_part, hpBuffer, rad, alfa);
		return lpBuffer;
	}
public:
	static constexpr size_t maxLength = 64;
	template<class AnyType>
	inline String operator()(AnyType i) const {
		TCHAR lpBuffer[maxLength] = { 0 }, *hpString, *lpString;
		if constexpr (std::is_unsigned_v<AnyType>)
			lpString = push((uintptr_t)i, lpBuffer, hpString, maxLength);
		elif constexpr (std::is_integral_v<AnyType>)
			lpString = push((intptr_t)i, lpBuffer, hpString, maxLength);
		elif constexpr (std::is_floating_point_v<AnyType>)
			lpString = push(i, lpBuffer, hpString, maxLength);
		return +CString(hpString - lpString, lpString);
	}
};
static inline format_numeral operator ""_nx(const char *format, size_t n) reflect_as(format);
static inline format_numeral operator ""_nx(const wchar_t *format, size_t n) reflect_as(format);

#define nX(form, ...) (format_numeral(form)(__VA_ARGS__))

#ifdef _WIN64
#	define oPTR oH016
#else
#	define oPTR oH08
#endif

#pragma endregion

#pragma region Stringifications
inline const String &Cats(bool b) {
	static auto &&t = S("true");
	static auto &&f = S("false");
	return b ? t : f;
}
inline String Cats(double f) reflect_as(nX(".5d", f));
inline String Cats(LONG i) reflect_as(nX("d", i));
inline String Cats(int32_t i) reflect_as(nX("d", i));
inline String Cats(int64_t i) reflect_as(nX("d", i));
inline String Cats(uint8_t i) reflect_as(nX("d", i));
inline String Cats(uint16_t i) reflect_as(nX("d", i));
inline String Cats(uint32_t i) reflect_as(nX("d", i));
inline String Cats(uint64_t i) reflect_as(nX("d", i));
inline String Cats(DWORD i) reflect_as(nX("d", i));
inline String Cats(WCHAR chs) reflect_as((TCHAR)chs);
inline String Cats(CHAR chs) reflect_as((TCHAR)chs);
inline String Cats(const Exception &err) reflect_as(err);
inline const String &Cats(const String &str) reflect_as(str);
template<class AnyType>
inline String Cats(const AnyType &tt) reflect_as((String)tt);
template<size_t len>
inline String Cats(const TCHAR(&Chars)[len]) reflect_as(Chars);
template<class... Args>
inline String Cats(const Args& ...args) reflect_as(_Cats(Cats(args)...));

static constexpr size_t Len_sprintf_buff = 1024;
inline String sprintf(LPCTSTR lpszFormat, ...) {
	va_list argList;
	va_start(argList, lpszFormat);
	TCHAR buff[Len_sprintf_buff];
	size_t remain = 0;
	assertl(SUCCEEDED(StringCchVPrintfEx(buff, Len_sprintf_buff, O, &remain, STRSAFE_NULL_ON_FAILURE, lpszFormat, argList)));
	va_end(argList);
	return +CString(buff, Len_sprintf_buff - remain + 1);
}

inline const String Exception::File() const reflect_as(CString(szFile, lpszFile));
inline const String Exception::Function() const reflect_as(CString(szFunc, lpszFunc));;
inline const String Exception::Sentence() const reflect_as(CString(szSent, lpszSent));

inline Exception::operator String() const reflect_as(Cats(
	_T("\nFile:      "), File(),
	_T("\nFunction:  "), Function(),
	_T("\nSentence:  "), Sentence(),
	_T("\nLine:      "), Line(),
	_T("\nLastError: "), LastError()));
inline String Exception::toString() const reflect_to_self();

inline int MsgBox(LPCTSTR lpCaption, const Exception &err, HWND hParent) reflect_as(MsgBox(lpCaption, err.toString(), MB::IconError | MB::AbortRetryIgnore, hParent));

inline String SysTime::FormatTime(TimeFormat tf, Locales locale) const {
	auto len = ::GetTimeFormat(locale.yield(), tf.yield(), this, O, O, 0);
	if (len <= 0) return O;
	String str((size_t)len - 1);
	::GetTimeFormat(locale.yield(), tf.yield(), this, O, str, len);
	return str;
}
inline String SysTime::FormatDate(DateFormat df, Locales locale) const {
	auto len = ::GetDateFormat(locale.yield(), df.yield(), this, O, O, 0);
	if (len <= 0) return O;
	String str((size_t)len - 1);
	::GetDateFormat(locale.yield(), df.yield(), this, O, str, len);
	return str;
}

inline SysTime::operator String() const {
	auto lenDate = ::GetDateFormat(0, 0, this, O, O, 0);
	auto lenTime = ::GetTimeFormat(0, 0, this, O, O, 0);
	if (lenDate <= 0 && lenTime <= 0) return O;
	String str((size_t)lenDate + lenTime - 1);
	::GetDateFormat(0, 0, this, O, str, lenDate);
	str[lenDate - 1] = _T(' ');
	::GetTimeFormat(0, 0, this, O, (LPTSTR)str + lenDate, lenTime);
	return str;
}
#pragma endregion

}
