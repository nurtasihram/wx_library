#pragma once

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

namespace WX {

using Null = decltype(nullptr);
constexpr Null O = nullptr;

#pragma region String Reference
#ifdef UNICODE
constexpr bool IsUnicode = true;
#else
constexpr bool IsUnicode = false;
#endif
template<class CharType>
class StringBase;
using String = StringBase<TCHAR>;
using StringA = StringBase<CHAR>;
using StringW = StringBase<WCHAR>;
const StringA operator ""_A(LPCSTR lpString, size_t uLen);
const StringW operator ""_W(LPCWSTR lpString, size_t uLen);
const String operator ""_S(LPCTSTR lpString, size_t uLen);
#define S(str) _T(str##_S)
template<bool IsUnicode>
using XCHAR = std::conditional_t<IsUnicode, WCHAR, CHAR>;
template<bool IsUnicode>
using LPXSTR = std::conditional_t<IsUnicode, LPWSTR, LPSTR>;
template<bool IsUnicode>
using LPCXSTR = std::conditional_t<IsUnicode, LPCWSTR, LPCSTR>;
template<bool IsUnicode>
using StringX = std::conditional_t<IsUnicode, StringW, StringA>;
template<bool IsUnicode, class AnyTypeA, class AnyTypeW>
static constexpr auto AnyX(AnyTypeA *a, AnyTypeW *w) {
	if constexpr (IsUnicode)
		return w;
	else
		return a;
}
template<bool IsUnicode, class AnyTypeA, class AnyTypeW>
static constexpr auto &AnyX(AnyTypeA &a, AnyTypeW &w) {
	if constexpr (IsUnicode)
		return w;
	else
		return a;
}
template<bool IsUnicode, class AnyTypeA, class AnyTypeW>
static constexpr auto AnyX(AnyTypeA &&a, AnyTypeW &&w) {
	if constexpr (IsUnicode)
		return w;
	else
		return a;
}
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
class RefAs {
	union Ref {
		AnyRef t;
		Ref() {}
		Ref(Null) {}
		~Ref() {}
	} t;
public:
	RefAs() : t(O) reflect_to(ZeroMemory(std::addressof(t.t), sizeof(t)));
	template<class AnyType>
	RefAs(AnyType &arg) reflect_to(new(&self) AnyRef(arg));
	template<class AnyType>
	RefAs(AnyType &&arg) reflect_to(new(&self) AnyRef(arg));
	template<class AnyType>
	RefAs(const AnyType &arg) reflect_to(new(&self) AnyRef(arg));
public:
	template<class AnyType>
	inline operator AnyType() reflect_as((AnyType)t.t);
	template<class AnyType>
	inline operator AnyType() const reflect_as((AnyType)t.t);
	inline operator AnyRef &() reflect_as(t.t);
	inline operator const AnyRef &() const reflect_as(t.t);
	inline operator AnyRef *() reflect_as(std::addressof(t.t));
	inline operator const AnyRef *() const reflect_as(std::addressof(t.t));
	inline auto &operator*() reflect_as(t.t);
	inline auto &operator*() const reflect_as(t.t);
	inline auto operator&() reflect_as(std::addressof(t.t));
	inline auto operator&() const reflect_as(std::addressof(t.t));
	inline auto operator->() reflect_as(std::addressof(t.t));
	inline auto operator->() const reflect_as(std::addressof(t.t));
};
template<class AnyType>
struct RefAs<AnyType *> {
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
template<class OtherType>
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
public:
	String File() const;
	StringA FileA() const;
	StringW FileW() const;
public:
	String Function() const;
	StringA FunctionA() const;
	StringW FunctionW() const;
public:
	String Sentence() const;
	StringA SentenceA() const;
	StringW SentenceW() const;
public:
	inline UINT Line() const reflect_as(uLine);
	inline DWORD LastError() const reflect_as(dwErrCode);
public:
	auto toString() const;
	StringA toStringA() const;
	StringW toStringW() const;
public:
	auto Message() const;
	StringA MessageA() const;
	StringW MessageW() const;
public:
	auto Format() const;
	StringA FormatA() const;
	StringW FormatW() const;
public:
	operator StringA() const;
	operator StringW() const;
	inline operator bool() const reflect_as(lpszSent);
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

#pragma region Enumerate
template<class AnyType>
constexpr AnyType ConstIndexOf(size_t ind, AnyType t0) {
	return t0;
}
template<class AnyType, class...AnyTypes>
constexpr AnyType ConstIndexOf(size_t ind, AnyType t0, AnyTypes...tN) {
	if (ind == 0)
		return t0;
	else
		return ConstIndexOf(ind - 1, tN...);
}
template<class Enum1, class Enum2, class EnumType>
inline auto __makeResult(EnumType val) {
	constexpr auto left = is_chain_extended_on<Enum1, Enum2>;
	constexpr auto right = is_chain_extended_on<Enum2, Enum1>;
	static_assert(left || right, "Convertless");
	if constexpr (left)
		return reuse_as<Enum1>(val);
	elif  constexpr (right)
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
def_memberof(IsProtoEnum);
template<class AnyType>
static constexpr bool IsEnumBased = member_IsProtoEnum_of<AnyType>::callable;
template<class AnyType>
using EnumUnit = std::conditional_t<IsEnumBased<AnyType>, AnyType, EnumUnitBase<AnyType>>;
template<class SubClass, class BaseType>
struct EnumBase {
	static constexpr bool IsProtoEnum = !IsEnumBased<BaseType>;
	using ProtoEnum = std::conditional_t<IsProtoEnum, SubClass, BaseType>;
	using ProtoUnit = typename EnumUnit<BaseType>::ProtoUnit;
	using ProtoType = typename ProtoUnit::ProtoType;
	static constexpr size_t CountAll() reflect_as(IsProtoEnum ? SubClass::Count : SubClass::Count + ProtoEnum::CountAll()); \
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
	static constexpr size_t Count = CountOf({ __VA_ARGS__ }); \
	static constexpr TCHAR __Name[] = _T(#name); \
	static constexpr TCHAR __Entries[] = _T(estr); \
	static constexpr ProtoType __Vals(size_t ind) reflect_as(ConstIndexOf(ind, __VA_ARGS__)); \
public: \
	inline ProtoType yield() const reflect_as(val.yield()); \
	inline operator Unit() const reflect_as(val); \
	oprt(Unit); }
#define enum_flags_opr(name) \
	inline name operator~ (      ) const reflect_as(~val); \
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
		if constexpr (ind == 0) return type;
		else return TypeList<Types...>::template indexof<ind - 1>();
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
		if constexpr (std::is_pointer_v<PackType>) reflect_to(assertl(func), func(args...))
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

#pragma endregion

#pragma region Point Size Rect
struct LSize;
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
	inline operator LPARAM() const reflect_as((LPARAM)this);
	inline operator COORD() const reflect_as({ (SHORT)x, (SHORT)y });
	inline LPoint  operator+ () const reflect_to_self();
	inline LPoint  operator~ () const reflect_as({ y,  x });
	inline LPoint  operator* (double l) const reflect_as({ LONG((double)x * l), LONG((double)y * l) });
	inline LPoint  operator/ (double l) const reflect_as({ LONG((double)x / l), LONG((double)y / l) });
	inline LPoint  operator* (int l) const reflect_as({ x * l, y * l });
	inline LPoint  operator/ (int l) const reflect_as({ x / l, y / l });
	inline LPoint  operator- () const reflect_as({ -x, -y });
	inline LPoint  operator+ (const LPoint &s) const reflect_as({ x + s.x, y + s.y });
	inline LPoint  operator- (const LPoint &s) const reflect_as({ x - s.x, y - s.y });
	inline LPoint &operator*=(double p) reflect_to_self(x = LONG((double)x * p), y = LONG((double)y * p));
	inline LPoint &operator/=(double p) reflect_to_self(x = LONG((double)x / p), y = LONG((double)y / p));
	inline LPoint &operator+=(const LPoint &p) reflect_to_self(x += p.x, y += p.y);
	inline LPoint &operator-=(const LPoint &p) reflect_to_self(x -= p.x, y -= p.y);
	inline LPoint &operator =(const LPoint &p) reflect_to_self(x = p.x, y = p.y);
	inline bool    operator==(LPoint pt) const reflect_as(pt.x == x && pt.y == y);
	inline bool    operator!=(LPoint pt) const reflect_as(pt.x != x || pt.y != y);
};
struct LSize : public SIZE {
public:
	LSize() : SIZE{ 0 } {}
	LSize(const SIZE &s) : SIZE(s) {}
	LSize(const LSize &s) : SIZE(s) {}
	LSize(LONG c) : SIZE{ c, c } {}
	LSize(LONG cx, LONG cy) : SIZE{ cx, cy } {}
	LSize(const LPoint &p) : SIZE{ p.x, p.y } {}
	LSize(COORD c) : SIZE{ c.X, c.Y } {}
public:
	inline auto Square() const reflect_as(cx * cy);
public:
	inline operator LPARAM() const reflect_as((LPARAM)this);
	inline operator LPoint() const reflect_as({ cx, cy });
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
	LRect(const MARGINS &m) : RECT({ m.cxLeftWidth, m.cyTopHeight, m.cxRightWidth, m.cyBottomHeight }) {}
	LRect(const RECT &rc) : RECT(rc) {}
	LRect(const LRect &r) : RECT(r) {}
	LRect(const LSize &sz) : RECT{ 0, 0, sz.cx - 1, sz.cy - 1 } {}
	LRect(const LPoint &p0, const LPoint &p1) : RECT{ p0.x, p0.y, p1.x, p1.y } {}
	LRect(LONG a) : RECT{ a, a, a, a } {}
	LRect(LONG left, LONG top, LONG right, LONG bottom) : RECT{ left, top, right, bottom } {}
	LRect(SMALL_RECT sr) : RECT{ sr.Left, sr.Top, sr.Right, sr.Bottom } {}
public:
	inline auto xsize()        const reflect_as(right - left + 1);
	inline auto ysize()        const reflect_as(bottom - top + 1);
	inline LSize size()        const reflect_as({ xsize(), ysize() });
	inline auto  dx()           const reflect_as(right - left);
	inline auto  dy()           const reflect_as(bottom - top);
	inline LSize d()            const reflect_as({ dx(), dy() });
	inline auto &xmove(LONG dx) reflect_to_self(right += dx, left += dx);
	inline auto &ymove(LONG dy) reflect_to_self(bottom += dy, top += dy);
	LRect &align(LAlign a, const LRect &r2);
public:
	inline auto x0() const reflect_as(left);
	inline auto y0() const reflect_as(top);
	inline auto x1() const reflect_as(right);
	inline auto y1() const reflect_as(bottom);
public:
	inline LPoint left_top()     const reflect_as({ left,  top });
	inline auto   &left_top(LPoint lt) reflect_to_self(left = lt.x, top = lt.y);
	static inline LRect left_top(LPoint lt, LSize sz) reflect_as({ lt.x, lt.y, lt.x + sz.cx - 1, lt.y + sz.cy - 1 });
public:
	inline LPoint left_bottom()    const reflect_as({ left,  bottom });
	inline auto  &left_bottom(LPoint lt) reflect_to_self(left = lt.x, bottom = lt.y);
public:
	inline LPoint right_top()    const reflect_as({ right, top });
	inline auto  &right_top(LPoint rt) reflect_to_self(right = rt.x, top = rt.y);
public:
	inline LPoint right_bottom() const reflect_as({ right, bottom });
	inline auto  &right_bottom(LPoint rb) reflect_to_self(right = rb.x, bottom = rb.y);
public:
	inline operator LSize()   const reflect_as({ right - left + 1, bottom - top + 1 });
	inline operator LPRECT()        reflect_as(this);
	inline operator LPCRECT() const reflect_as(this);
	inline operator LPARAM()  const reflect_as((LPARAM)this);
	inline operator MARGINS() const reflect_as({ left, right, top, bottom });
	inline operator SMALL_RECT() const reflect_as({ (SHORT)left, (SHORT)top, (SHORT)right, (SHORT)bottom });
	inline LRect  operator+ () const reflect_to_self();
	inline LRect  operator- () const reflect_as({ -left,   -top, -right, -bottom });
	inline LRect  operator~ () const reflect_as({ right, bottom,   left,     top });
	inline LRect  operator+ (const LRect &r) const reflect_as({ left + r.left, top + r.top, right + r.right, bottom + r.bottom });
	inline LRect  operator- (const LRect &r) const reflect_as({ left - r.left, top - r.top, right - r.right, bottom - r.bottom });
	inline LRect  operator+ (const LPoint &p) const reflect_as({ left + p.x, top + p.y, right + p.x, bottom + p.y });
	inline LRect  operator- (const LPoint &p) const reflect_as({ left - p.x, top - p.y, right - p.x, bottom - p.y });
	inline LRect  operator* (double l) const reflect_as({ LONG((double)left * l), LONG((double)top * l), LONG((double)right * l), LONG((double)bottom * l) });
	inline LRect  operator/ (double l) const reflect_as({ LONG((double)left / l), LONG((double)top / l), LONG((double)right / l), LONG((double)bottom / l) });
	inline LRect  operator* (int l ) const reflect_as({ left * l, top * l, right * l, bottom * l });
	inline LRect  operator/ (int l) const reflect_as({ left / l, top / l, right / l, bottom / l });
	inline LRect &operator*=(double l) reflect_to_self(left = LONG((double)left * l), top = LONG((double)top * l), right = LONG((double)right * l), bottom = LONG((double)bottom * l));
	inline LRect &operator/=(double l) reflect_to_self(left = LONG((double)left / l), top = LONG((double)top / l), right = LONG((double)right / l), bottom = LONG((double)bottom / l));
	inline LRect &operator/=(int l) reflect_to_self(left /= l, top /= l, right /= l, bottom /= l);
	inline LRect &operator*=(int l) reflect_to_self(left *= l; top *= l, right *= l, bottom *= l);
	inline LRect &operator+=(const LRect &r) reflect_to_self(left += r.left, top += r.top, right += r.right, bottom += r.bottom);
	inline LRect &operator-=(const LRect &r) reflect_to_self(left -= r.left, top -= r.top, right -= r.right, bottom -= r.bottom);
	inline LRect &operator+=(const LPoint &p) reflect_to_self(left += p.x, top += p.y, right += p.x, bottom += p.y);
	inline LRect &operator-=(const LPoint &p) reflect_to_self(left -= p.x, top -= p.y, right -= p.x, bottom -= p.y);
	static inline LRect &Attach(RECT &rc) reflect_as(ref_as<LRect>(rc));
};
inline LRect operator+(const LPoint &p, const LRect &r) reflect_as(r + p);
inline LRect operator-(const LPoint &p, const LRect &r) reflect_as(-(r - p));
inline LRect operator&(const LPoint &p, const LSize &s) reflect_as({ p, s });
inline LRect operator&(const LSize &s, const LPoint &p) reflect_as({ p, s });
inline LRect &WX::LRect::align(LAlign a, const LRect &r2) {
	if (a == LAlign::HCenter)
		xmove((r2.left + r2.right - left - right) / 2);
	elif  (a <= LAlign::Right) {
		left += r2.right - right;
		right = r2.right;
	}
	else /* if (a <= LAlign::Left) */ {
		right += r2.left - left;
		left = r2.left;
	}
	if (a == LAlign::VCenter)
		ymove((r2.top + r2.bottom - top - bottom) / 2);
	elif  (a <= LAlign::Bottom) {
		top += r2.bottom - bottom;
		bottom = r2.bottom;
	}
	else /* if (a & LAlign::Top) */ {
		bottom += r2.top - top;
		top = r2.top;
	}
	return*this;
}
#pragma endregion

#pragma region Times
enum_class(Locales, LCID,
	Default = LOCALE_CUSTOM_DEFAULT,
	Unspecified = LOCALE_CUSTOM_UNSPECIFIED,
	UIDefault   = LOCALE_CUSTOM_UI_DEFAULT,
	Neutral     = LOCALE_NEUTRAL,
	Invariant   = LOCALE_INVARIANT);
enum_flags(TimeFormat, DWORD,
	Default            = 0,
	NoMinutesOrSeconds = TIME_NOMINUTESORSECONDS,
	NoSecond           = TIME_NOSECONDS,
	NoTimeMarker       = TIME_NOTIMEMARKER,
	Force24H           = TIME_FORCE24HOURFORMAT);
enum_flags(DateFormat, DWORD,
	Default      = 0,
	ShortDate    = DATE_SHORTDATE,
	LongDate     = DATE_LONGDATE,
	CalendarAlt  = DATE_USE_ALT_CALENDAR);
struct SystemTime : public SYSTEMTIME {
public:
	SystemTime(Null) : SYSTEMTIME{ 0 } {}
	SystemTime() reflect_to(GetSystemTime(this));
	SystemTime(const FILETIME &ft) assertl(FileTimeToSystemTime(&ft, this));
public:
	static inline SystemTime Local() reflect_to(SystemTime st; GetLocalTime(&st), st);
public:
	String FormatTime(TimeFormat = TimeFormat::Default, Locales = Locales::Default) const;
	StringA FormatTimeA(TimeFormat = TimeFormat::Default, Locales = Locales::Default) const;
	StringW FormatTimeW(TimeFormat = TimeFormat::Default, Locales = Locales::Default) const;
	String FormatDate(DateFormat = DateFormat::Default, Locales = Locales::Default) const;
	StringA FormatDateA(DateFormat = DateFormat::Default, Locales = Locales::Default) const;
	StringW FormatDateW(DateFormat = DateFormat::Default, Locales = Locales::Default) const;
public:
	operator StringA() const;
	operator StringW() const;
};
using SysTime = SystemTime;
struct FileTime : protected FILETIME {
public:
	FileTime() : FILETIME{ 0 } {}
	FileTime(const FILETIME &ft) : FILETIME(ft) {}
	FileTime(LARGE_INTEGER li) { ref_as<LARGE_INTEGER>(self) = li; }
	FileTime(const SYSTEMTIME &st) assertl(SystemTimeToFileTime(&st, this));
public:
	inline FileTime LocalTime() assertl_reflect_to(FILETIME ft, FileTimeToLocalFileTime(this, &ft), ft);
public:
	inline operator StringA() const;
	inline operator StringW() const;
	inline operator SystemTime() const assertl_reflect_to(SystemTime st, FileTimeToSystemTime(this, &st), st);
	inline operator SYSTEMTIME() const assertl_reflect_to(SystemTime st, FileTimeToSystemTime(this, &st), st);
	inline operator LARGE_INTEGER() const reflect_as(reuse_as<LARGE_INTEGER>(*this));
	inline LPFILETIME operator &() reflect_as(this);
	inline const FILETIME *operator &() const reflect_as(this);
};
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
