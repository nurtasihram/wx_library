﻿#pragma once

#include <tchar.h>

#include <windows.h>
#include <strsafe.h>
#include <uxtheme.h>

#include <cstdint>
#include <functional>
#include <type_traits>
#include <utility>

#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"OneCore.lib")
#pragma comment(linker, "\"" \
	"/manifestdependency:" \
	" type='win32'" \
	" name='Microsoft.Windows.Common-Controls'" \
	" version='6.0.0.0'" \
	" processorArchitecture='*'" \
	" publicKeyToken='6595b64144ccf1df'" \
	" language='*'" \
"\"")

#ifdef min
#	undef min
#endif
#ifdef max
#	undef max
#endif

#define _M_(...) __VA_ARGS__ 
#define _B_(...) { __VA_ARGS__ }

#define _MACRO_CALL(func, ...) func(__VA_ARGS__)
#define STROF(note) _T(#note)

#define elif else if
#define _if(...) __VA_ARGS__ ? 
#define _else :
#define _elif(...) : __VA_ARGS__ ?
#define _return

#define self (*this)
#define retself return self
#define reflect_as(...) { return __VA_ARGS__; }
#define reflect_to(line, ...) { line; return __VA_ARGS__; }
#define reflect_to_self(...)  { __VA_ARGS__; retself; }

#define misuse_assert(cond, note) static_assert(cond, "Misused: " note)
#define misdef_assert(cond, note) static_assert(cond, "Misdefined: " note)
#define child_assert(base, sub) \
		misuse_assert((std::is_base_of_v<base, sub>), #sub " must base on " #base)

#pragma region Compilation Informations
#ifndef __cplusplus
#	error This header file requires C++ compilation.
#elif __cplusplus < 201703L
#	error This header file requires C++17 or later. For MSVC may need open /Zc:__cplusplus option
#endif
/* CPLUSPLUS_STANDARD */
#define CPLUSPLUS_STANDARDA _MACRO_CALL(STROF, __cplusplus)
#define CPLUSPLUS_STANDARDW L##CPLUSPLUS_STANDARDA
#define CPLUSPLUS_STANDARD _T(CPLUSPLUS_STANDARDA)
/* CHAR_MODE */
#ifdef UNICODE
#	define CHAR_MODEA "Unicode"
#else
#	define CHAR_MODEA "ANSI"
#endif
#define CHAR_MODEW L##CHAR_MODEA
#define CHAR_MODE _T(CHAR_MODEA)
/* COMPILATION_MODE */
#ifdef _DEBUG
#	define COMPILATION_MODEA "Debug"
#else
#	define COMPILATION_MODEA "Release"
#endif
#define COMPILATION_MODEW L##COMPILATION_MODEA
#define COMPILATION_MODE _T(COMPILATION_MODEA)
/* BUILD_DATE */
#define BUILD_DATEA __DATE__ " " __TIME__
#define BUILD_DATEW L##BUILD_DATEA
#define BUILD_DATE _T(BUILD_DATEA)
/* COMPILATION_PLATFORM */
#ifdef _WIN64
#	define COMPILATION_PLATFORMA "Windows 64-bit"
#elif defined(_WIN32)
#	define COMPILATION_PLATFORMA "Windows 32-bit"
#else
#	define COMPILATION_PLATFORMA "Unknown"
#endif
#define COMPILATION_PLATFORMW L##COMPILATION_PLATFORMA
#define COMPILATION_PLATFORM _T(COMPILATION_PLATFORMA)
/* COMPILATION_ARCHITECTURE */
#ifdef _M_X64
#	define COMPILATION_ARCHITECTUREA "x64"
#elif defined(_M_IX86)
#	define COMPILATION_ARCHITECTUREA "x86"
#elif defined(_M_AMD64)
#	define COMPILATION_ARCHITECTUREA "AMD64"
#elif defined(_M_ARM64)
#	define COMPILATION_ARCHITECTUREA "ARM64"
#elif defined(_M_ARM)
#	define COMPILATION_ARCHITECTUREA "ARM"
#elif defined(_M_ARM64EC)
#	define COMPILATION_ARCHITECTUREA "ARM64EC"
#else
#	define COMPILATION_ARCHITECTUREA "Unknown"
#endif
#define COMPILATION_ARCHITECTUREW L##COMPILATION_ARCHITECTUREA
#define COMPILATION_ARCHITECTURE _T(COMPILATION_ARCHITECTUREA)
/* COMPILATION_COMPILER */
#ifdef _MSC_VER
#	define COMPILATION_COMPILERA \
	"Microsoft C++ " _MACRO_CALL(STROF, _MSC_FULL_VER)
#elif defined(__GNUC__)
#	define COMPILATION_COMPILERA \
	"GCC " _MACRO_CALL(STROF, __VERSION__)
#elif defined(__clang__)
#	define COMPILATION_COMPILERA \
	"Clang " _MACRO_CALL(STROF, __clang_version__)
#else
#	define COMPILATION_COMPILERA \
	"Unknown"
#endif
#define COMPILATION_COMPILERW L##COMPILATION_COMPILERA
#define COMPILATION_COMPILER _T(COMPILATION_COMPILERA)
/* COMPILATION_INFO */
#define COMPILATION_INFOA \
	"C++ Standard:     " CPLUSPLUS_STANDARDA "\n" \
	"Compilation Mode: " COMPILATION_MODEA "\n" \
	"Char Mode:        " CHAR_MODEA "\n" \
	"Build Date:       " BUILD_DATEA "\n" \
	"Platform:         " COMPILATION_PLATFORMA "\n" \
	"Architecture:     " COMPILATION_ARCHITECTUREA "\n" \
	"Compiler:         " COMPILATION_COMPILERA "\n"
#define COMPILATION_INFOW L##COMPILATION_INFOA
#define COMPILATION_INFO _T(COMPILATION_INFOA)
#pragma endregion

namespace WX {

using Null = decltype(nullptr);
constexpr Null O = nullptr;

#pragma region String Reference
template<bool IsUnicode>
using XCHAR = std::conditional_t<IsUnicode, WCHAR, CHAR>;
template<bool IsUnicode>
using LPXSTR = std::conditional_t<IsUnicode, LPWSTR, LPSTR>;
template<bool IsUnicode>
using LPCXSTR = std::conditional_t<IsUnicode, LPCWSTR, LPCSTR>;
#ifdef UNICODE
constexpr bool IsUnicode = true;
#else
constexpr bool IsUnicode = false;
#endif
template<bool IsUnicode, class AnyTypeW, class AnyTypeA>
static constexpr auto AnyX(AnyTypeW *w, AnyTypeA *a) {
	if constexpr (IsUnicode)
		 return w;
	else return a;
}
template<bool IsUnicode, class AnyTypeW, class AnyTypeA>
static constexpr auto &AnyX(AnyTypeW &w, AnyTypeA &a) {
	if constexpr (IsUnicode)
		 return w;
	else return a;
}
template<bool IsUnicode, class AnyTypeW, class AnyTypeA>
static constexpr auto AnyX(AnyTypeW &&w, AnyTypeA &&a) {
	if constexpr (IsUnicode)
		 return w;
	else return a;
}
template<class TCHAR>
static constexpr bool IsCharA = std::is_same_v<TCHAR, CHAR>; 
template<class TCHAR>
static constexpr bool IsCharW = std::is_same_v<TCHAR, WCHAR>; 
#ifndef __clang__
#	define locale_symbolx(name) static constexpr auto name = AnyX<IsUnicode>(name##W, name##A)
#	define global_symbolx(name) static constexpr auto name = AnyX<IsUnicode>(::name##W, ::name##A)
#else
#	define locale_symbolx(name) static auto name = AnyX<IsUnicode>(name##W, name##A)
#	define global_symbolx(name) static auto name = AnyX<IsUnicode>(::name##W, ::name##A)
#endif
#define const_stringx(name, str) static constexpr auto name##A = str; static constexpr auto name##W = L##str
#define auto_stringx(name, str) const_stringx(name, str); locale_symbolx(name)
#define switch_structx(name) std::conditional_t<IsUnicode, name##W, name##A>
#define using_structx(name) using name = std::conditional_t<IsUnicode, name##W, name##A>
template<class CharType>
class StringBase;
using String = StringBase<TCHAR>;
using StringA = StringBase<CHAR>;
using StringW = StringBase<WCHAR>;
const StringA operator""_A(LPCSTR lpString, size_t uLen);
const StringW operator""_W(LPCWSTR lpString, size_t uLen);
const String operator""_S(LPCTSTR lpString, size_t uLen);
#define S(str) _T(str##_S)
template<bool IsUnicode>
using StringX = switch_structx(String);
#pragma endregion

#pragma region Reuse & Cast
template<class OutType, class InType>
static inline OutType reuse_as(InType in) {
	misuse_assert(sizeof(OutType) == sizeof(InType), "Must fit same size");
	return *(OutType *)&in;
}
template<class OutType, class InType>
static inline OutType small_cast(InType in) {
	misuse_assert(sizeof(OutType) >= sizeof(InType), "sizeof in-type must small or equal to out-type");
	return *(OutType *)&in;
}
template<class OutType, class InType>
static inline OutType big_cast(InType in) {
	misuse_assert(sizeof(OutType) <= sizeof(InType), "sizeof in-type must big or equal to out-type");
	return *(OutType *)&in;
}
template<class OutType, class InType>
static inline OutType &ref_as(InType &in) {
	misuse_assert(sizeof(OutType) == sizeof(InType), "Must fit same size");
	return *(OutType *)(&in);
}
template<class AnyRef>
union RefAs {
private:
	AnyRef t;
public:
	template<class AnyType>
	RefAs(AnyType &arg) : t(arg) {}
	template<class AnyType>
	RefAs(AnyType &&arg) : t(std::forward<AnyType>(arg)) {}
	template<class AnyType>
	RefAs(const AnyType &arg) : t(arg) {}
	~RefAs() {}
public:
	template<class AnyType>
	inline operator AnyType() reflect_as((AnyType)t);
	template<class AnyType>
	inline operator AnyType() const reflect_as((AnyType)t);
	inline operator AnyRef &() reflect_as(t);
	inline operator const AnyRef &() const reflect_as(t);
	inline operator AnyRef *() reflect_as(std::addressof(t));
	inline operator const AnyRef *() const reflect_as(std::addressof(t));
	inline auto &operator*() reflect_as(t);
	inline auto &operator*() const reflect_as(t);
	inline auto operator&() reflect_as(std::addressof(t));
	inline auto operator&() const reflect_as(std::addressof(t));
	inline auto operator->() reflect_as(std::addressof(t));
	inline auto operator->() const reflect_as(std::addressof(t));
};
template<class AnyType>
union RefAs<AnyType *> {
private:
	AnyType *ptr;
public:
	template<class OtherType>
	RefAs(OtherType *ptr) : ptr((AnyType *)ptr) {}
public:
	inline operator AnyType *() reflect_as(ptr);
	inline operator const AnyType *() const reflect_as(ptr);
	inline auto &operator*() reflect_as(*ptr);
	inline auto &operator*() const reflect_as(*ptr);
	inline auto *operator&() reflect_as(&ptr);
	inline auto *operator&() const reflect_as(&ptr);
	inline auto *operator->() reflect_as(ptr);
	inline auto *operator->() const reflect_as(ptr);
};
template <class AnyStruct>
class RefStruct : protected AnyStruct {
public:
	RefStruct() reflect_to(ZeroMemory(this, sizeof(AnyStruct)));
	RefStruct(const AnyStruct &s) : AnyStruct(s) {}
public:
	inline operator AnyStruct &() reflect_to_self();
	inline operator const AnyStruct &() const reflect_to_self();
	inline AnyStruct &operator*() reflect_to_self();
	inline const AnyStruct &operator *() const reflect_to_self();
	inline AnyStruct *operator&() reflect_as(this);
	inline const AnyStruct *operator&() const reflect_as(this);
	inline AnyStruct *operator->() reflect_as(this);
	inline const AnyStruct *operator->() const reflect_as(this);
};
template <class OtherType>
static constexpr bool IsRef = false;
template<class RefType>
static constexpr bool IsRef<RefAs<RefType>> = true;
#pragma endregion

#pragma region Exception
class Exception {
	LPCSTR lpszFile = O, lpszFunc = O, lpszSent = O;
	size_t szFile = 0, szFunc = 0, szSent = 0;
	UINT uLine = 0;
	DWORD dwErrCode = 0;
public:
	Exception() {}
	template<size_t szFile, size_t szFunc, size_t szSent>
	Exception(const char(&strFile)[szFile],
			  const char(&strFunc)[szFunc],
			  const char(&strSent)[szSent],
			  UINT uLine,
			  DWORD dwErrCode = GetLastError()) :
		lpszFile(strFile), lpszFunc(strFunc), lpszSent(strSent),
		szFile(szFile - 1), szFunc(szFunc - 1), szSent(szSent - 1),
		uLine(uLine), dwErrCode(dwErrCode) {}
public: // Property - File
	template<bool IsUnicode = WX::IsUnicode>
	StringX<IsUnicode> File() const;
	StringA FileA() const;
	StringW FileW() const;
public: // Property - Function
	template<bool IsUnicode = WX::IsUnicode>
	StringX<IsUnicode> Function() const;
	StringA FunctionA() const;
	StringW FunctionW() const;
public: // Property - Sentence
	template<bool IsUnicode = WX::IsUnicode>
	StringX<IsUnicode> Sentence() const;
	StringA SentenceA() const;
	StringW SentenceW() const;
public: // Property - Line
	inline UINT Line() const reflect_as(uLine);
public: // Property - ErrorCode
	inline DWORD ErrorCode() const reflect_as(dwErrCode);
public: // Property - ErrorMessage
	template<bool IsUnicode = WX::IsUnicode>
	StringX<IsUnicode> ErrorMessage() const;
	StringA ErrorMessageA() const;
	StringW ErrorMessageW() const;
public:
	template<bool IsUnicode = WX::IsUnicode>
	StringX<IsUnicode> toString() const;
	StringA toStringA() const;
	StringW toStringW() const;
public:
	inline operator bool() const reflect_as(lpszSent);
	operator StringA() const;
	operator StringW() const;
};
int MsgBox(LPCSTR lpCaption, const Exception &err, HWND hParent = O);
int MsgBox(LPCWSTR lpCaption, const Exception &err, HWND hParent = O);
#define wx_answer_retry return false
#define wx_answer_ignore return true
#define wx_answer_abort(err) throw(err)
using wx_answer = bool;

class Catch {
	static std::function<bool(const Exception &)> invoker;
	wx_answer bAnswer = false;
public:
	template<class AnyFunc>
	Catch(const AnyFunc &af) reflect_to(invoker = af);
	Catch(const Exception &err) : bAnswer(invoker(err)) {}
	inline operator wx_answer() const reflect_as(bAnswer);
};
static std::function<wx_answer(const Exception &)> Catch = [](const Exception &err) {
	switch (MsgBox(_T("Global error"), err)) {
		case IDIGNORE:
			wx_answer_ignore;
		case IDRETRY:
			wx_answer_retry;
		case IDABORT:
			break;
	}
	wx_answer_abort(err);
};

#define wx_throw_line(sent) throw Exception(__FILE__, __FUNCTION__, sent, __LINE__)
#define assertl(sent) { using namespace WX; if (!(sent)) wx_throw_line(#sent); }

#define assertl_reflect_as(sent, ...) \
{ if (sent) return __VA_ARGS__; wx_throw_line(#sent); }
#define assertl_reflect_as_self(sent)  assertl_reflect_as(sent, self)
#define assertl_reflect_as_child(sent) assertl_reflect_as(sent, child)

#define assertl_reflect_to(defs, sent, ...) \
{ defs; if (sent) return __VA_ARGS__; wx_throw_line(#sent); }
#define assertl_reflect_to_self(defs, sent)  assertl_reflect_to(defs, sent, self)
#define assertl_reflect_to_child(defs, sent) assertl_reflect_to(defs, sent, child)

#define nt_assertl_reflect_to(sent, ...) \
{ SetLastError(0); sent; if (GetLastError()) wx_throw_line(#sent); return __VA_ARGS__; }
#define nt_assertl_reflect_to_self(sent)  nt_assertl_reflect_to(sent, self)
#define nt_assertl_reflect_to_child(sent) nt_assertl_reflect_to(sent, child)
#pragma endregion

#pragma region Type Traits

#pragma region SFINAE Type Helper
#define def_memberof(name) \
template <class AnyClass> class member_##name##_of { \
	template<class _AnyClass> \
	static auto __refof_##name(int) -> decltype(&_AnyClass::name); \
	template<class _AnyClass> \
	static auto __refof_##name(...) -> void; \
	template<class _AnyClass, class Ret, class... Args> \
	static auto __compatible(Ret(*)(Args...)) -> std::is_convertible< \
		decltype(std::declval<_AnyClass>().name(std::declval<Args>()...)), Ret>; \
	template<class _AnyClass> \
	static auto __compatible(...) -> std::false_type; \
public: \
	using type = decltype(__refof_##name<AnyClass>(0)); \
	static constexpr bool callable = !std::is_void_v<type>; \
	template<class AnyType> \
	static constexpr bool compatible_to = \
		decltype(__compatible<AnyClass>(std::declval<AnyType *>()))::value; }
#define subtype_branch(name) \
template<class AnyType, class OtherType> \
static inline auto __subtype_branchof_##name(int) -> \
	typename AnyType::name; \
template<class AnyType, class OtherType> \
static inline auto __subtype_branchof_##name(...) -> \
	OtherType; \
template<class AnyType, class OtherType> \
using subtype_branchof_##name = \
	decltype(__subtype_branchof_##name<AnyType, OtherType>(0))
#pragma endregion

#pragma region Chain Extender
template<class ParentClass, class ChildClass>
using Chain = std::conditional_t<std::is_void_v<ChildClass>, ParentClass, ChildClass>;
template<class ParentClass, class ChildClass>
struct ChainExtender {
	using Child = Chain<ParentClass, ChildClass>;
	using Self = ParentClass;
	constexpr ChainExtender() {
		if constexpr (!std::is_void_v<ChildClass>)
			child_assert(ParentClass, ChildClass);
	}
	Child &child_() reflect_as(*static_cast<Child *>(this));
	const Child &child_() const reflect_as(*static_cast<const Child *>(this));
	Self &self_() reflect_as(*static_cast<Self *>(this));
	const Self &self_() const reflect_as(*static_cast<const Self *>(this));
};
#define child (this->child_())
#define retchild return child
#define reflect_to_child(...) { __VA_ARGS__; retchild; }
subtype_branch(super);
template<class Class1, class Class2>
constexpr bool is_chain_extended_on =
	std::is_void_v<Class1> || std::is_void_v<Class2> ? false :
	std::is_same_v<Class1, Class2> ?  true :
	is_chain_extended_on<subtype_branchof_super<Class1, void>, Class2>;
#pragma endregion

#pragma region Static Compatible
template <class AnyCallable, class Ret, class... Args>
static auto __static_compatible(...) -> std::false_type;
template <class AnyCallable, class Ret, class... Args>
static auto __static_compatible(int) -> std::is_convertible<
	decltype(std::declval<AnyCallable>()(std::declval<Args>()...)), Ret>;
template<class AnyCallable, class FuncType>
static constexpr bool static_compatible = false;
template<class AnyCallable, class Ret, class... Args>
static constexpr bool static_compatible<AnyCallable, Ret(Args...)> =
decltype(__static_compatible<AnyCallable, Ret, Args...>(0))::value;
#pragma endregion

#pragma region Type List
template<class...>
struct TypeList;
template<>
struct TypeList<> {
	static constexpr size_t Length() reflect_as(0);
	template<class AnyType>
	inline auto invoke(AnyType &f) reflect_as(f());
};
template<>
struct TypeList<void> {
	template<int ind>
	struct index;
	template<size_t ind>
	inline void indexof() { misuse_assert(ind >= 0, "index overflowed"); }
	template<class AnyType>
	inline auto invoke(AnyType &f) reflect_as(f());
};
template<class Type0>
struct TypeList<Type0> {
	Type0 type;
	template<class AnyType>
	TypeList(AnyType &type) : type(type) {}
	template<class AnyType>
	TypeList(AnyType &&type) : type(type) {}
	template<int ind, class = void>
	struct index { misuse_assert(ind >= 0, "Index overflowed"); };
	template<class ___>
	struct index<0, ___> { using type = Type0; };
	template<size_t ind>
	using IndexOf = typename index<ind>::type;
	template<size_t ind>
	inline auto &indexof() reflect_to(misuse_assert(ind >= 0, "index overflowed"), type);
public:
	template<class ClassType, class MethodType>
	inline auto invoke(ClassType &cls, MethodType method) reflect_as((cls.*method)(std::forward<Type0>(type)));
	template<class AnyType>
	inline auto invoke(AnyType &f) reflect_as(f(std::forward<Type0>(type)));
};
template<class Type0, class...Types>
struct TypeList<Type0, Types...> : TypeList<Types...> {
	Type0 type;
	template<class AnyType, class...Args>
	TypeList(AnyType &type, Args...args) : TypeList<Types...>(args...), type(type) {}
	template<class AnyType, class...Args>
	TypeList(AnyType &&type, Args...args) : TypeList<Types...>(args...), type(type) {}
	static constexpr size_t Length() reflect_as(1 + sizeof...(Types));
	template<size_t ind, class = void>
	struct index : TypeList<Types...>::template index<ind - 1> {};
	template<class ___>
	struct index<0, ___> { using type = Type0; };
	template<size_t ind>
	using IndexOf = typename index<ind>::type;
	template<size_t ind>
	inline auto &indexof() {
		if constexpr (ind == 0)
			 return TypeList<Types...>::template indexof<ind - 1>();
		else return type;
	}
	using ind_seq = std::index_sequence_for<Type0, Types...>;
private:
	template<class ClassType, class MethodType, size_t... ind>
	inline auto invoke(ClassType &cls, MethodType method, std::index_sequence<ind...>) reflect_as((cls.*method)(indexof<ind>()...));
	template<class AnyType, size_t... ind>
	inline auto invoke(AnyType &f, std::index_sequence<ind...>) reflect_as(f(indexof<ind>()...));
public:
	template<class ClassType, class MethodType>
	inline auto invoke(ClassType &cls, MethodType method) reflect_as(call(cls, method, ind_seq{}));
	template<class AnyType>
	inline auto invoke(AnyType &f) reflect_as(call(f, ind_seq{}));
};
#pragma endregion

#pragma region Array Counter
template<class AnyType, size_t Len>
using arrayof = AnyType[Len];
template<class...Args>
constexpr size_t ArgsCount(Args...) reflect_as(sizeof...(Args));
template<class AnyType>
static constexpr size_t lengthof = 0;
template<class AnyType, size_t Len>
static constexpr size_t lengthof<const arrayof<AnyType, Len> &> = Len;
template<class AnyType, size_t Len>
constexpr auto &_CountOf(const arrayof<AnyType, Len> &a) reflect_as(a);
#define CountOf(...) lengthof<decltype(_CountOf(__VA_ARGS__))>
template<class AnyType>
struct SizeOf_t { static constexpr size_t val = sizeof(AnyType); };
template<>
struct SizeOf_t<void> { static constexpr size_t val = 0; };
template<class AnyType>
constexpr size_t SizeOf = SizeOf_t<AnyType>::val;
#pragma endregion

#pragma region Const ConstArray
template<class AnyType, size_t Len>
struct ConstArray {
	AnyType array[Len];
	template<class OtherType, size_t xLen, size_t... ind>
	constexpr ConstArray(const OtherType(&arr)[xLen], std::index_sequence<ind...>, size_t Off = 0) : array{ arr[ind + Off]... } {}
	template<class OtherType, size_t xLen>
	constexpr ConstArray(const OtherType(&arr)[xLen], size_t Off = 0) : ConstArray(arr, std::make_index_sequence<Len>{}, Off) {}
	static constexpr size_t Length = Len;
	constexpr operator const arrayof<AnyType, Len>&() const reflect_as(array);
	template<class OtherType>
	constexpr operator ConstArray<OtherType, Len>() const reflect_as(array);
};
template<class AnyType>
struct ConstArray<AnyType, 0>
{ static constexpr size_t Length = 0; };
template<class AnyType, size_t Len>
constexpr ConstArray<AnyType, Len> ArrayOf(const AnyType(&arr)[Len], size_t Off = 0) reflect_as({ arr, Off });
#pragma endregion

#pragma region Proto
template<class AnyType>
struct to_proto_t {
	using type = AnyType;
};
template<class AnyType>
struct to_proto_t<AnyType *> : to_proto_t<AnyType> {};
template<class AnyType>
struct to_proto_t<AnyType &> : to_proto_t<AnyType> {};
template<class AnyType>
struct to_proto_t<AnyType &&> : to_proto_t<AnyType> {};
template<class AnyType>
struct to_proto_t<const AnyType> : to_proto_t<AnyType> {};
template<class AnyType>
struct to_proto_t<volatile AnyType> : to_proto_t<AnyType> {};
template<class AnyType>
using to_proto = typename to_proto_t<AnyType>::type;
#pragma endregion

#pragma region Function Of
template<class OtherType>
struct __functionof {
	static constexpr bool is_static = false;
	static constexpr bool is_method = false;
};
template<class Ret, class AnyClass, class...Args>
struct __functionof<Ret(AnyClass:: *)(Args...)> {
	using Belong = AnyClass;
	using Return = Ret;
	using ArgsList = TypeList<Args...>;
	using Pointer = Ret(AnyClass:: *)(Args...);
	static constexpr bool is_method = true;
	static constexpr bool is_static = false;
	static constexpr bool is_ellipsis = false;
};
template<class Ret, class AnyClass, class...Args>
struct __functionof<Ret(AnyClass:: *)(Args..., ...)> {
	using Belong = AnyClass;
	using Return = Ret;
	using ArgsList = TypeList<Args...>;
	using Pointer = Ret(AnyClass:: *)(Args...);
	static constexpr bool is_method = true;
	static constexpr bool is_static = false;
	static constexpr bool is_ellipsis = true;
};
template<class Ret, class... Args>
struct __functionof<Ret(Args...)> {
	using Return = Ret;
	using ArgsList = TypeList<Args...>;
	using Pointer = Ret(*)(Args...);
	static constexpr bool is_method = false;
	static constexpr bool is_static = true;
	static constexpr bool is_ellipsis = false;
};
template<class Ret, class... Args>
struct __functionof<Ret(Args..., ...)> {
	using Return = Ret;
	using ArgsList = TypeList<Args...>;
	using Pointer = Ret(*)(Args...);
	static constexpr bool is_method = false;
	static constexpr bool is_static = true;
	static constexpr bool is_ellipsis = true;
};
template<class OtherType>
using functionof = __functionof<to_proto<OtherType>>;
#pragma endregion

#pragma region Function
template<class RetType, class ArgsList>
struct FunctionBase {};
template<class RetType, class... Args>
struct FunctionBase<RetType, TypeList<Args...>> {
	virtual ~FunctionBase() = default;
	virtual RetType operator()(Args ...) = 0;
};
template<class PackType, class RetType, class ArgsList>
class FunctionPackage {};
template<class PackType, class RetType, class... Args>
class FunctionPackage<PackType, RetType, TypeList<Args...>> :
	public FunctionBase<RetType, TypeList<Args...>> {
	mutable PackType func;
public:
	FunctionPackage(PackType &f) : func(f) {}
	RetType operator()(Args ...args) override {
		static_assert(static_compatible<PackType, RetType(Args...)>, "Argument list uncompatible");
		if constexpr (std::is_pointer_v<PackType>)
			 reflect_to(assertl(func), func(args...))
		else reflect_as(func(args...));
	}
};
template<class...>
class Function;
template<class Ret, class... Args>
class Function<Ret(Args...)> {
public:
	using RetType = Ret;
	using ArgsList = TypeList<Args...>;
private:
	mutable FunctionBase<Ret, ArgsList> *func = O;
	mutable bool bAllocated = false;
public:
	Function() {}
	Function(Null) {}
	Function(const Function &f) : func(f.func) {}
public:
	template<class Type>
	Function(Type &f) : func(new FunctionPackage<Type, Ret, ArgsList>(f)), bAllocated(true) {}
	template<class Type>
	Function(Type f) : func(new FunctionPackage<Type, Ret, ArgsList>(f)), bAllocated(true) {}
	~Function() { if (func && bAllocated) delete func, func = O; }
public:
	inline operator bool() const reflect_as(!func);
	inline bool operator!=(Null) const reflect_as(func);
	inline bool operator==(Null) const reflect_as(!func);
	inline Function operator&() reflect_to_self();
	inline const Function operator&() const reflect_to_self();
	inline Ret operator()(Args...args) const reflect_to(assertl(func), (*func)(args...));
	inline auto &operator=(const Function &f) const noexcept reflect_to_self(func = f.func, bAllocated = false);
	inline auto &operator=(const Function &f) noexcept reflect_to_self(func = f.func, bAllocated = false);
	inline auto &operator=(Function &&f) noexcept reflect_to_self(func = f.func, f.func = O, bAllocated = true);
};
template<class...FuncTypes>
using fn = Function<FuncTypes...>;
#pragma endregion

#pragma region Enumerate
def_memberof(HasProtoEnum);
template<class AnyType>
static constexpr bool IsEnum = member_HasProtoEnum_of<AnyType>::callable;
template<class TCHAR>
class Rx {
	using LPCTSTR = const TCHAR *;
	using String = StringBase<TCHAR>;
	static constexpr bool __a_z(TCHAR w) reflect_as('a' <= w && w <= 'z');
	static constexpr bool __A_Z(TCHAR w) reflect_as('A' <= w && w <= 'Z');
	static constexpr bool __0_9(TCHAR w) reflect_as('0' <= w && w <= '9');
	static constexpr bool __A_z(TCHAR w) reflect_as(__a_z(w) || __A_Z(w));
	static constexpr bool _word(TCHAR w) reflect_as(__A_z(w) || __0_9(w));
	static constexpr bool _Word(TCHAR w) reflect_as(_word(w) || w == '_');
	static constexpr bool __s(TCHAR w) reflect_as(w == '\n' || w == '\r' || w == '\t' || w == ' ');
	struct Token {
		friend class Rx;
		LPCTSTR lpsz;
		size_t len;
	public:
		constexpr Token() : lpsz(O), len(0) {}
		constexpr Token(LPCTSTR lpsz, LPCTSTR hpsz) : lpsz(lpsz), len(hpsz - lpsz) {}
		constexpr operator LPCTSTR() const reflect_as(lpsz);
		operator const String() const;
	};
	struct Map { Token key, val; };
	template<size_t len>
	class Maps {
		friend class Rx;
		Map map[len];
	public:
		static constexpr size_t Length = len;
		constexpr Map operator[](size_t ind) const { return map[ind]; }
	};
	struct MapN { Map map; LPCTSTR hpsz; };
	static constexpr MapN _GetMap(LPCTSTR lpsz) {
		LPCTSTR hpsz = lpsz;
		// skip blank
		while (auto ch = hpsz[0])
			if (__s(hpsz[0]))
				++hpsz;
			else
				break;
		// get key
		lpsz = hpsz;
		while (auto ch = hpsz[0])
			if (_Word(hpsz[0]))
				++hpsz;
			else
				break;
		Token key{ lpsz, hpsz };
		// skip blank
		while (auto ch = hpsz[0])
			if (__s(hpsz[0]))
				++hpsz;
			else
				break;
		// get equal
		if (hpsz[0] != '=')
			return{ {}, {} };
		++hpsz;
		// skip blank
		while (auto ch = hpsz[0])
			if (__s(hpsz[0]))
				++hpsz;
			else
				break;
		// get val
		lpsz = hpsz;
		while (auto ch = hpsz[0])
			if (hpsz[0] != ',')
				++hpsz;
			else
				break;
		Token val{ lpsz, hpsz };
		if (hpsz[0] == ',')
			++hpsz;
		return{ { key, val }, hpsz };
	}
	template<size_t count>
	static constexpr Maps<count> GetMaps(LPCTSTR lpsz) {
		Maps<count> maps;
		for (size_t i = 0; i < count; ++i) {
			auto map = _GetMap(lpsz);
			lpsz = map.hpsz;
			maps.map[i] = map.map;
		}
		return maps;
	}
public:
	template<class AnyEnum>
	static constexpr auto Table() {
		misuse_assert(IsEnum<AnyEnum>, "template type must be based on EnumBase");
		if constexpr (IsCharW<TCHAR>)
			 return GetMaps<AnyEnum::Count>(AnyEnum::__EntriesW);
		else return GetMaps<AnyEnum::Count>(AnyEnum::__EntriesA);
	}
};
/* EnumTableX */
template<class AnyEnum, class TCHAR = ::TCHAR>
static constexpr auto EnumTable = Rx<TCHAR>::template Table<AnyEnum>();
template<class AnyEnum>
static constexpr auto EnumTableA = EnumTable<AnyEnum, CHAR>;
template<class AnyEnum>
static constexpr auto EnumTableW = EnumTable<AnyEnum, WCHAR>;
/* (misc) */
template<class Enum1, class Enum2, class EnumType>
inline auto __makeResult(EnumType val) {
	constexpr auto left = is_chain_extended_on<Enum1, Enum2>;
	constexpr auto right = is_chain_extended_on<Enum2, Enum1>;
	static_assert(left || right, "Convertless");
	if constexpr (left)
		return reuse_as<Enum1>(val);
	elif constexpr (right)
		return reuse_as<Enum2>(val);
}
template<class AnyType>
struct EnumUnitBase {
	using ProtoType = AnyType;
	using ProtoUnit = EnumUnitBase;
	ProtoType val;
	constexpr EnumUnitBase(ProtoType val) : val(val) {}
	static constexpr size_t CountAll = 0;
};
template<class AnyType>
using EnumUnit = std::conditional_t<IsEnum<AnyType>, AnyType, EnumUnitBase<AnyType>>;
template<class SubClass, class BaseType>
struct EnumBase {
	static constexpr bool HasProtoEnum = IsEnum<BaseType>;
	using ProtoEnum = std::conditional_t<HasProtoEnum, BaseType, void>;
	using ProtoUnit = typename EnumUnit<BaseType>::ProtoUnit;
	using ProtoType = typename ProtoUnit::ProtoType;
	static constexpr size_t CountAll() reflect_as(HasProtoEnum ? SubClass::Count + ProtoEnum::CountAll() : SubClass::Count); \
};
#define __enum_ex(name, base, oprt, estr, ...) \
class name : public EnumBase<name, base> { \
public: \
	using super = EnumBase<name, base>; \
	using EnumType = name; \
	using ProtoEnum = typename super::ProtoEnum; \
	using ProtoUnit = typename super::ProtoUnit; \
	using ProtoType = typename super::ProtoType; \
protected: \
	friend struct EnumBase<name, base>; \
	class Unit : protected ProtoUnit { \
	protected: friend class name; \
		Unit(const ProtoUnit &val) : ProtoUnit(val.val) {} \
		constexpr Unit(const ProtoType &val) : ProtoUnit(val) { static_assert(sizeof(val) == sizeof(self), "alignment error"); } \
		constexpr ProtoType operator=(const ProtoType &v) const reflect_as(v); \
	public: using EnumType = name; \
		oprt(Unit); \
		inline ProtoType yield() const reflect_as(val); \
	} val; \
public: \
	template<class AnyType> \
	constexpr name(AnyType val) : val(ref_as<Unit>(val)) \
	{ static_assert(is_chain_extended_on<name, typename AnyType::EnumType>, "enumerate error"); } \
	constexpr name(Unit val) : val(val.val) { static_assert(sizeof(val) == sizeof(self), "alignment error"); } \
public: \
	static inline const Unit __VA_ARGS__; \
	static constexpr size_t Count = CountOf({ __VA_ARGS__ }); 	static constexpr CHAR __NameA[]{ #name }; \
	static constexpr WCHAR __NameW[]{ L ## #name }; \
	static constexpr CHAR __EntriesA[]{ estr }; \
	static constexpr WCHAR __EntriesW[]{ L ## estr }; \
	static inline ProtoType __Vals[]{ __VA_ARGS__ }; \
public: \
	inline ProtoType yield() const reflect_as(val.yield()); \
	inline operator Unit() const reflect_as(val); \
	oprt(Unit); }
#define enum_flags_opr(name) \
	inline name operator~ () const reflect_as(~val); \
	template<class AnyType> inline auto operator^(AnyType v) const reflect_as(__makeResult<EnumType, typename AnyType::EnumType>(yield() ^  v.yield())); \
	template<class AnyType> inline auto operator|(AnyType v) const reflect_as(__makeResult<EnumType, typename AnyType::EnumType>(yield() |  v.yield())); \
	template<class AnyType> inline auto operator&(AnyType v) const reflect_as(__makeResult<EnumType, typename AnyType::EnumType>(yield() &  v.yield())); \
	template<class AnyType> inline auto operator+(AnyType v) const reflect_as(__makeResult<EnumType, typename AnyType::EnumType>(yield() |  v.yield())); \
	template<class AnyType> inline auto operator-(AnyType v) const reflect_as(__makeResult<EnumType, typename AnyType::EnumType>(yield() & ~v.yield())); \
	inline name operator^=(name v) reflect_to_self( val ^=  v.val); \
	inline name operator|=(name v) reflect_to_self( val |=  v.val); \
	inline name operator&=(name v) reflect_to_self( val &=  v.val); \
	inline bool operator==(name v) const reflect_as( yield() == v.yield()); \
	inline bool operator!=(name v) const reflect_as( yield() != v.yield()); \
	inline bool operator<=(name v) const reflect_as((yield() &  v.yield()) ==   yield()); \
	inline bool operator>=(name v) const reflect_as((yield() &  v.yield()) == v.yield())
#define enum_class_opr(name) \
	inline bool operator==(name v) const reflect_as(val == v.val); \
	inline bool operator!=(name v) const reflect_as(val != v.val)
#define enum_explicit inline operator const ProtoType &() const reflect_as(val)
#define enum_ex(name, base, oprt, ...) __enum_ex(name, base, oprt, #__VA_ARGS__, __VA_ARGS__)
#define enum_flags(name, base, ...) __enum_ex(name, base, enum_flags_opr, #__VA_ARGS__, __VA_ARGS__)
#define enum_class(name, base, ...) __enum_ex(name, base, enum_class_opr, #__VA_ARGS__, __VA_ARGS__)
#define enum_flags_explicit(name, base, ...) __enum_ex(name, base, enum_explicit enum_flags_opr, #__VA_ARGS__, __VA_ARGS__)
#define enum_class_explicit(name, base, ...) __enum_ex(name, base, enum_explicit enum_class_opr, #__VA_ARGS__, __VA_ARGS__)
#pragma endregion

#pragma endregion

class RGBColor {
protected:
	COLORREF cr;
public:
	RGBColor(COLORREF color) : cr(color) {}
	RGBColor(BYTE red, BYTE green, BYTE blue) :
		cr(RGB(red, green, blue)) {}
public:
	inline BYTE Red()   const reflect_as(GetRValue(self));
	inline BYTE Green() const reflect_as(GetGValue(self));
	inline BYTE Blue()  const reflect_as(GetBValue(self));
public:
	template<size_t len>
	static inline arrayof<RGBColor, len> &Attach(arrayof<COLORREF, len> &ary) reflect_as(ref_as<arrayof<RGBColor, len>>(ary));
	inline operator COLORREF() const { return cr; }
	static inline RGBColor &Attach(COLORREF &clr) reflect_as(*(RGBColor *)&clr);
};

#pragma region MessageBox
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
inline auto MsgBox(LPCSTR lpCaption, LPCSTR lpText = O, MB type = MB::Ok, HWND hParent = O) reflect_as(MessageBoxA(hParent, lpText, lpCaption, type.yield()));
inline auto MsgBox(LPCWSTR lpCaption = O, LPCWSTR lpText = O, MB type = MB::Ok, HWND hParent = O) reflect_as(MessageBoxW(hParent, lpText, lpCaption, type.yield()));
#pragma endregion

}
