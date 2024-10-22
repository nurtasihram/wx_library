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
#define __braceO (
#define Obrace__ )
#define _B_(...) { __VA_ARGS__ }

#define elif else if
#define fn(...) [&](__VA_ARGS__)

#define ___inline_class___ __inline_cls_
#define extends(...) : __VA_ARGS__
#define inline_constructor(...) ___inline_class___(__VA_ARGS__)
#define inline_destructor() ~___inline_class___()
#define inline_newex(ext, argslist, ...) \
	([&] { \
		struct ___inline_class___ ext __VA_ARGS__; \
		return new ___inline_class___ argslist; \
	})()
#define inline_new(ext, argslist, ...) inline_newex(extends(ext), argslist, __VA_ARGS__)
#define inline_classex(ext, argslist, ...) \
	([&] { \
		struct ___inline_class___ ext __VA_ARGS__; \
		return ___inline_class___ argslist; \
	})()
#define inline_class(argslist, ...) inline_classex(_M_(), argslist, __VA_ARGS__)

#define msvc_property(...) __declspec(property(__VA_ARGS__))

#define misuse_assert(cond, note) static_assert(cond, "Misused: " note)
#define misdef_assert(cond, note) static_assert(cond, "Misdefined: " note)
#define child_assert(base, sub) \
	misuse_assert((std::is_base_of_v<base, sub>), #sub " must base on " #base)

#define reflect_as(...) { return __VA_ARGS__; }
#define reflect_to(line, ...) { line; return __VA_ARGS__; }

#define reflect_to_self(...)  { __VA_ARGS__; retself; }
#define reflect_to_child(...) { __VA_ARGS__; retchild; }

#define _if(...) __VA_ARGS__ ? 
#define _else :
#define _elif(...) : __VA_ARGS__ ?
#define _return

namespace WX {

template<class CharType>
class StringBase;
using String = StringBase<TCHAR>;
using StringA = StringBase<CHAR>;
using StringW = StringBase<WCHAR>;

const StringA operator ""_A(LPCSTR lpString, size_t uLen);
const StringW operator ""_W(LPCWSTR lpString, size_t uLen);
const String operator ""_S(LPCTSTR lpString, size_t uLen);

#define S(str) _T(str##_S)

#ifdef UNICODE
constexpr bool IsUnicode = true;
#else
constexpr bool IsUnicode = false;
#endif

template<class OutType, class InType>
static inline OutType force_cast(InType in) reflect_as(*(OutType *)&in);

template<class OutType, class InType>
static inline OutType &reuse_as(InType &in) {
	misuse_assert(sizeof(OutType) == sizeof(InType), "Must fit same size");
	return *(OutType *)(&in);
}

using Null = decltype(nullptr);
constexpr Null O = nullptr;

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

template<class AnyClass>
union RefAs {
private:
	AnyClass t;
public:
	template<class...AnyType>
	RefAs(AnyType &...arg) : t(arg...) {}
	template<class...AnyType>
	RefAs(AnyType &&...arg) : t(arg...) {}
	template<class...AnyType>
	RefAs(const AnyType &...arg) : t(arg...) {}
	~RefAs() {}
	inline AnyClass &operator*() reflect_as(t);
	inline const AnyClass &operator*() const reflect_as(t);
	inline AnyClass *operator&() reflect_as(std::addressof(t));
	inline const AnyClass *operator&() const reflect_as(std::addressof(t));
	inline AnyClass *operator->() reflect_as(std::addressof(t));
	inline const AnyClass *operator->() const reflect_as(std::addressof(t));
	inline operator AnyClass &() reflect_as(t);
	inline operator const AnyClass &() const reflect_as(t);
	template<class AnyType>
	inline operator AnyType() reflect_as(t);
	template<class AnyType>
	inline operator AnyType() const reflect_as(t);
};

template<class AnyStruct>
struct RefStruct : private AnyStruct {
	RefStruct() : AnyStruct{ 0 } {}
	RefStruct(const AnyStruct &s) : AnyStruct(s) {}
	RefStruct(const AnyStruct &&s) : AnyStruct(s) {}
	inline operator AnyStruct *() reflect_as(this);
	inline operator const AnyStruct *() const reflect_as(this);
	inline AnyStruct &operator*() reflect_as(*this);
	inline const AnyStruct &operator*() const reflect_as(*this);
	inline AnyStruct *operator&() reflect_as(this);
	inline const AnyStruct *operator&() const reflect_as(this);
	inline AnyStruct *operator->() reflect_as(this);
	inline const AnyStruct *operator->() const reflect_as(this);
};

template<class AnyType>
union RefAs<AnyType *> {
private:
	AnyType *ptr;
public:
	template<class OtherType>
	RefAs(OtherType *ptr) : ptr((AnyType *)ptr) { static_assert(std::is_convertible_v<OtherType, AnyType>); }
	inline auto&operator*() reflect_as(*ptr);
	inline auto&operator*() const reflect_as(*ptr);
	inline auto operator->() reflect_as(ptr);
	inline auto operator->() const reflect_as(ptr);
	inline operator bool() const reflect_as(ptr);
};

#pragma region Type Traits

#pragma region KChain

template<class ParentClass, class ChildClass>
using KChain = std::conditional_t<std::is_void_v<ChildClass>, ParentClass, ChildClass>;

template<class ParentClass, class ChildClass>
struct ChainExtend {
	using Child = KChain<ParentClass, ChildClass>;
	using Self = ParentClass;
	constexpr ChainExtend() {
		if constexpr (!std::is_void_v<ChildClass>)
			child_assert(ParentClass, ChildClass);
	}
	Child &child_() reflect_as(*static_cast<Child *>(this));
	const Child &child_() const reflect_as(*static_cast<const Child *>(this));
	Self &self_() reflect_as(*static_cast<Self *>(this));
	const Self &self_() const reflect_as(*static_cast<const Self *>(this));
};

#define child    (this->child_())
#define self     (*this)
#define retself  return self
#define retchild return child

#pragma endregion

#pragma region Compatible
template <class AnyType, class Ret, class... Args>
static auto _static_compatible(...) -> std::false_type;
template <class AnyType, class Ret, class... Args>
static auto _static_compatible(int) -> std::is_convertible<
	decltype(std::declval<AnyType>()(std::declval<Args>()...)), Ret>;
template<class AnyType, class FuncType>
static constexpr bool static_compatible = false;
template<class AnyType, class Ret, class... Args>
static constexpr bool static_compatible<AnyType, Ret(Args...)> =
decltype(_static_compatible<AnyType, Ret, Args...>(0))::value;
#pragma endregion

#pragma region SFINAE Type Helper
#define def_memberof(name) \
template <class AnyClass> class member_##name##_of { \
	template<class _AnyClass> \
	static auto _retof_##name(int) -> decltype(&_AnyClass::name); \
	template<class _AnyClass> \
	static auto _retof_##name(...) -> void; \
	template<class _AnyClass, class Ret, class... Args> \
	static auto _compatible(Ret(*)(Args...)) -> std::is_convertible< \
		decltype(std::declval<_AnyClass>().name(std::declval<Args>()...)), Ret>; \
	template<class _AnyClass> \
	static auto _compatible(...) -> std::false_type; \
public: \
	using type = decltype(_retof_##name<AnyClass>(0)); \
	static constexpr bool existed = !std::is_void_v<type>; \
	template<class AnyType> \
	static constexpr bool compatible_to = \
		decltype(_compatible<AnyClass>(std::declval<AnyType *>()))::value; }
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

template<class Class1, class Class2>
struct chain_is_ext_of_t {
	subtype_branch(super);
	static constexpr bool value() {
		if constexpr (std::is_same_v<Class1, Class2>)
			return true;
		else if constexpr (std::is_void_v<subtype_branchof_super<Class1, void>>)
			return false;
		else if constexpr (std::is_same_v<typename Class1::super, Class2>)
			return true;
		else
			return chain_is_ext_of_t<typename Class1::super, Class2>::value();
	}
};

#pragma region Enumerate
template<class Enum1, class Enum2, class EnumType>
inline auto __makeResult(EnumType val) {
	constexpr auto left = chain_is_ext_of_t<Enum1, Enum2>::value();
	constexpr auto right = chain_is_ext_of_t<Enum2, Enum1>::value();
	static_assert(left || right, "Convertless");
	if constexpr (left)
		return force_cast<Enum1>(val);
	else if constexpr (right)
		return force_cast<Enum2>(val);
}
#define enum_default
#define enum_alias
#define enum_complex
enum class EnumModifies : CHAR {
	no = 0,
	defualt = 'd',
	alias = 'a',
	complex = 'c'
};
template<class ProtoType>
struct EnumToken {
	const String *pszEnumName;
	const ProtoType *val;
	LPCTSTR lpLeft = O, lpRight = O;
	USHORT lnLeft = 0, lnRight = 0;
	EnumModifies mod = EnumModifies::no;
	EnumToken() {}
	EnumToken(const String &szEnumName, const ProtoType *val) :
		pszEnumName(std::addressof(szEnumName)), val(val) {}
	inline const String Left() const;
	inline const String Right() const;
	inline const ProtoType &Value() const reflect_as(*val);
	inline const String &EnumName() const reflect_as(*pszEnumName);
};
template<class AnyType>
struct EnumUnitBase {
	using ProtoType = AnyType;
	using ProtoUnit = EnumUnitBase;
	ProtoType val;
	constexpr EnumUnitBase(ProtoType val) : val(val) {}
};
def_memberof(EnumName);
template<class AnyType>
static constexpr bool IsEnumBased = member_EnumName_of<AnyType>::existed;
template<class AnyType>
using EnumUnit = std::conditional_t<
	IsEnumBased<AnyType>, AnyType,
	EnumUnitBase<AnyType>>;
template<class SubClass, class BaseType>
struct EnumBase {
	static constexpr bool IsProtoEnum = !IsEnumBased<BaseType>;
	static const String &&EnumName;
	using ProtoEnum = std::conditional_t<IsProtoEnum, SubClass, BaseType>;
	using ProtoUnit = typename EnumUnit<BaseType>::ProtoUnit;
	using ProtoType = typename ProtoUnit::ProtoType;
	using Token = EnumToken<ProtoType>;
	static constexpr size_t CountAll() reflect_as(IsProtoEnum ? SubClass::Count : SubClass::Count + ProtoEnum::CountAll());
};
#define __enum_ex(name, base, oprt, estr, ...) \
class name : public EnumBase<name, base> { \
public: \
	using EnumType = name; \
	using super = base; \
	using ProtoType = typename EnumBase<name, base>::ProtoType; \
	using ProtoUnit = typename EnumBase<name, base>::ProtoUnit; \
public: \
	friend struct EnumBase<name, base>; \
	static constexpr TCHAR __Name[] = _T(#name); \
	static constexpr TCHAR __Entries[] = _T(estr); \
	static inline const ProtoType *__Index(size_t ind) { \
		static const ProtoType *const values[] = { __VA_ARGS__ }; \
		return values[ind]; \
	} \
	class Unit : protected ProtoUnit { \
	protected: friend class name; \
		Unit(const ProtoUnit &val) : ProtoUnit(val.val) {} \
		constexpr Unit(const ProtoType &val) : ProtoUnit(val) { static_assert(sizeof(val) == sizeof(self), "alignment error"); } \
		const ProtoType *operator=(const ProtoType &) const reflect_as(std::addressof(val)); \
	public: using EnumType = name; \
		oprt(Unit); \
		inline ProtoType yield() const reflect_as(val); \
	} val; \
public: \
	static inline const Unit __VA_ARGS__; \
	oprt(Unit); \
	template<class AnyType> \
	constexpr name(AnyType val) : val(reuse_as<Unit>(val)) \
	{ static_assert(chain_is_ext_of_t<name, typename AnyType::EnumType>::value(), "enumerate error"); } \
	constexpr name(Unit val) : val(val.val) {} \
	static constexpr size_t Count = CountOf({ __VA_ARGS__ }); \
	inline ProtoType yield() const reflect_as(val.yield()); \
	inline operator Unit() const reflect_as(val); }
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


#pragma region MessageBox
enum_flags(MB, int,
	Ok                   =  MB_OK,
	OkCancel             =  MB_OKCANCEL,
	AbortRetryIgnore     =  MB_ABORTRETRYIGNORE,
	YesNoCancel          =  MB_YESNOCANCEL,
	YesNo                =  MB_YESNO,
	RetryCancel          =  MB_RETRYCANCEL,
	CancelTryContinue    =  MB_CANCELTRYCONTINUE,
	IconHand             =  MB_ICONHAND,
	IconQuestion         =  MB_ICONQUESTION,
	IconExclamation      =  MB_ICONEXCLAMATION,
	IconAsterisk         =  MB_ICONASTERISK,
	UserIcon             =  MB_USERICON,
	IconWarning          =  MB_ICONWARNING,
	IconError            =  MB_ICONERROR,
	IconInformation      =  MB_ICONINFORMATION,
	IconStop             =  MB_ICONSTOP,
	DefButton1           =  MB_DEFBUTTON1,
	DefButton2           =  MB_DEFBUTTON2,
	DefButton3           =  MB_DEFBUTTON3,
	DefButton4           =  MB_DEFBUTTON4,
	ApplModal            =  MB_APPLMODAL,
	SystemModal          =  MB_SYSTEMMODAL,
	TaskModal            =  MB_TASKMODAL,
	Help                 =  MB_HELP,
	NoFocus              =  MB_NOFOCUS,
	SetForeground        =  MB_SETFOREGROUND,
	DefaultDesktopOnly   =  MB_DEFAULT_DESKTOP_ONLY,
	Topmost              =  MB_TOPMOST,
	Right                =  MB_RIGHT,
	RtlReading           =  MB_RTLREADING,
	ServiceNotification  =  MB_SERVICE_NOTIFICATION);
inline auto MsgBox(LPCTSTR lpCaption = O, LPCTSTR lpText = O, MB type = MB::Ok, HWND hParent = O) reflect_as(MessageBox(hParent, lpText, lpCaption, type.yield()));
#pragma endregion

#pragma region Exception

class Exception {
	LPCTSTR lpszFile = O, lpszFunc = O, lpszSent = O;
	size_t szFile = 0, szFunc = 0, szSent = 0;
	UINT uLine = 0;
	DWORD dwErrCode = 0;
public:
	Exception() {}
	template<size_t szFile, size_t szFunc, size_t szSent>
	Exception(const TCHAR(&strFile)[szFile],
			  const TCHAR(&strFunc)[szFunc],
			  const TCHAR(&strSent)[szSent],
			  UINT uLine,
			  DWORD dwErrCode = GetLastError()) :
		lpszFile(strFile), lpszFunc(strFunc), lpszSent(strSent),
		szFile(szFile - 1), szFunc(szFunc - 1), szSent(szSent - 1),
		uLine(uLine), dwErrCode(dwErrCode) {}
public:
	const String File() const;
	const String Function() const;
	const String Sentence() const;
	inline UINT Line() const reflect_as(uLine);
	inline DWORD LastError() const reflect_as(dwErrCode);
	String toString() const;
	operator String() const;
	inline operator bool() const reflect_as(lpszSent);
};
int MsgBox(LPCTSTR lpCaption, const Exception &err, HWND hParent = O);
class OnError {
	static std::function<bool(const Exception &)> invoker;
	bool bIgnore = false;
public:
	template<class AnyFunc>
	OnError(const AnyFunc &af) reflect_to(invoker = af);
	OnError(const Exception &err) : bIgnore(invoker(err)) {}
	inline operator bool() const reflect_as(bIgnore);
};
static std::function<bool(const Exception &err)> OnError = [](const Exception &err) {
	switch (MsgBox(_T("Error"), err)) {
		case IDABORT:
			throw err;
		case IDIGNORE:
			return false;
		case IDRETRY:
			break;
	}
	return true;
};
#define wx_exception(line, ...) Exception(_T(__FILE__), _T(__FUNCTION__), _T(#line), __LINE__)
#define assert(line) { using namespace WX; while (!(line)) if (OnError(wx_exception(line))) break; }

#define assert_reflect_as(line, ...) \
{ if (line) return __VA_ARGS__; throw wx_exception(line); }
#define assert_reflect_as_self(line)  assert_reflect_as(line, self)
#define assert_reflect_as_child(line) assert_reflect_as(line, child)

#define assert_reflect_to(defs, line, ...) \
{ defs; if (line) return __VA_ARGS__; throw wx_exception(line); }
#define assert_reflect_to_self(defs, line)  assert_reflect_to(defs, line, self)
#define assert_reflect_to_child(defs, line) assert_reflect_to(defs, line, child)

#define check_reflect_to(line, ...) \
{ SetLastError(0); line; if (auto _err = GetLastError()) throw wx_exception(line, _err); return __VA_ARGS__; }
#define check_reflect_to_self(line)  check_reflect_to(line, self)
#define check_reflect_to_child(line) check_reflect_to(line, child)

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
		if constexpr (std::is_pointer_v<PackType>) reflect_to(assert(func), func(args...))
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
	inline Ret operator()(Args...args) const reflect_to(assert(func), (*func)(args...));
	inline auto &operator=(const Function &f) const noexcept reflect_to_self(func = f.func, bAllocated = false);
	inline auto &operator=(const Function &f) noexcept reflect_to_self(func = f.func, bAllocated = false);
	inline auto &operator=(Function &&f) noexcept reflect_to_self(func = f.func, f.func = O, bAllocated = true);
};
template<class...FuncTypes>
using fn = Function<FuncTypes...>;
#pragma endregion

#pragma endregion

#pragma region Basic Types
struct LSize;
struct LPoint : public POINT {
	LPoint() : POINT{ 0 } {}
	LPoint(const POINT &p) : POINT(p) {}
	LPoint(const LPoint &p) : POINT(p) {}
	LPoint(LONG a) : POINT{ a, a } {}
	LPoint(LONG x, LONG y) : POINT{ x, y } {}
	inline LPoint  operator+ ()                const reflect_to_self();
	inline LPoint  operator~ ()                const reflect_as({ y,  x });
	inline LPoint  operator* (double l)        const reflect_as({ LONG((double)x * l), LONG((double)y * l) });
	inline LPoint  operator/ (double l)        const reflect_as({ LONG((double)x / l), LONG((double)y / l) });
	inline LPoint  operator* (int l)           const reflect_as({ x * l, y * l });
	inline LPoint  operator/ (int l)           const reflect_as({ x / l, y / l });
	inline LPoint  operator- ()                const reflect_as({ -x, -y });
	inline LPoint  operator+ (const LPoint &s) const reflect_as({ x + s.x, y + s.y });
	inline LPoint  operator- (const LPoint &s) const reflect_as({ x - s.x, y - s.y });
	inline LPoint &operator*=(double p)              reflect_to_self(x = LONG((double)x * p), y = LONG((double)y * p));
	inline LPoint &operator/=(double p)              reflect_to_self(x = LONG((double)x / p), y = LONG((double)y / p));
	inline LPoint &operator+=(const LPoint &p)       reflect_to_self(x += p.x, y += p.y);
	inline LPoint &operator-=(const LPoint &p)       reflect_to_self(x -= p.x, y -= p.y);
	inline LPoint &operator =(const LPoint &p)       reflect_to_self(x = p.x, y = p.y);
	inline bool    operator==(LPoint pt)       const reflect_as(pt.x == x && pt.y == y);
	inline bool    operator!=(LPoint pt)       const reflect_as(pt.x != x || pt.y != y);
	inline operator LPARAM() const reflect_as((LPARAM)this);
	operator LSize() const;
};
struct LSize : public SIZE {
	LSize() : SIZE{ 0 } {}
	LSize(const SIZE &s) : SIZE(s) {}
	LSize(const LSize &s) : SIZE(s) {}
	LSize(LONG c) : SIZE{ c, c } {}
	LSize(LONG cx, LONG cy) : SIZE{ cx, cy } {}
	inline LSize  operator+ ()               const reflect_to_self();
	inline LSize  operator- ()               const reflect_as({ -cx, -cy });
	inline LSize  operator~ ()               const reflect_as({  cy,  cx });
	inline LSize  operator* (double l)       const reflect_as({ LONG((double)cx * l), LONG((double)cy * l) });
	inline LSize  operator/ (double l)       const reflect_as({ LONG((double)cx / l), LONG((double)cy / l) });
	inline LSize  operator* (int l)          const reflect_as({ cx * l, cy * l });
	inline LSize  operator/ (int l)          const reflect_as({ cx / l, cy / l });
	inline LSize  operator+ (const LSize &s) const reflect_as({ cx + s.cx, cy + s.cy });
	inline LSize  operator- (const LSize &s) const reflect_as({ cx - s.cx, cy - s.cy });
	inline LSize &operator*=(double p)             reflect_to_self(cx = LONG((double)cx * p), cy = LONG((double)cy * p));
	inline LSize &operator/=(double p)             reflect_to_self(cx = LONG((double)cx / p), cy = LONG((double)cy / p));
	inline LSize &operator+=(const LSize &p)       reflect_to_self(cx += p.cx, cy += p.cy);
	inline LSize &operator-=(const LSize &p)       reflect_to_self(cx -= p.cx, cy -= p.cy);
	inline LSize &operator =(const LSize &p)       reflect_to_self(cx = p.cx, cy = p.cy);
	inline bool   operator==(LSize sz)       const reflect_as(sz.cx == cx && sz.cy == cy);
	inline bool   operator!=(LSize sz)       const reflect_as(sz.cx != cx || sz.cy != cy);
	inline operator LPARAM() const reflect_as((LPARAM)this);
	inline operator LPoint() const reflect_as({ cx, cy });
};
inline LPoint::operator LSize() const reflect_as({ x, y });
struct LRect : public RECT {
	LRect() : RECT{ 0 } {}
	LRect(const MARGINS &m) : RECT({ m.cxLeftWidth, m.cyTopHeight, m.cxRightWidth, m.cyBottomHeight }) {}
	LRect(const RECT &rc) : RECT(rc) {}
	LRect(const LRect &r) : RECT(r) {}
	LRect(const LPoint &p0, const LPoint &p1) : RECT{ p0.x, p0.y, p1.x, p1.y } {}
	LRect(const LPoint &pt, const LSize &sz = 0) : RECT{ pt.x, pt.y, pt.x + sz.cx - 1, pt.y + sz.cy - 1 } {}
	LRect(const LSize &sz, const LPoint &pt = 0) : RECT{ pt.x, pt.y, pt.x + sz.cx - 1, pt.y + sz.cy - 1 } {}
	LRect(LONG a) : RECT{ a, a, a, a } {}
	LRect(LONG left, LONG top, LONG right, LONG bottom) : RECT{ left, top, right, bottom } {}
	inline LSize  size()         const reflect_as({ right - left + 1, bottom - top + 1});
	inline LPoint top_left()     const reflect_as({ left,    top });
	inline LPoint bottom_left()  const reflect_as({ left, bottom });
	inline LPoint top_right()    const reflect_as({ right,    top });
	inline LPoint bottom_right() const reflect_as({ right, bottom });
	inline auto   width()        const reflect_as(right - left);
	inline auto   height()       const reflect_as(bottom - top);
	inline LRect  operator+ ()                const reflect_to_self();
	inline LRect  operator- ()                const reflect_as({ -left,   -top, -right, -bottom });
	inline LRect  operator~ ()                const reflect_as({ right, bottom,   left,     top });
	inline LRect  operator+ (const LRect &r)  const reflect_as({ left + r.left, top + r.top, right + r.right, bottom + r.bottom });
	inline LRect  operator- (const LRect &r)  const reflect_as({ left - r.left, top - r.top, right - r.right, bottom - r.bottom });
	inline LRect  operator+ (const LPoint &p) const reflect_as({ left + p.x, top + p.y, right + p.x, bottom + p.y });
	inline LRect  operator- (const LPoint &p) const reflect_as({ left - p.x, top - p.y, right - p.x, bottom - p.y });
	inline LRect  operator+ (const LSize &p)  const reflect_as({ left, top, right + p.cx, bottom + p.cy });
	inline LRect  operator- (const LSize &p)  const reflect_as({ left, top, right - p.cx, bottom - p.cy });
	inline LRect  operator* (double l)        const reflect_as({ LONG((double)left * l), LONG((double)top * l), LONG((double)right * l), LONG((double)bottom * l) });
	inline LRect  operator/ (double l)        const reflect_as({ LONG((double)left / l), LONG((double)top / l), LONG((double)right / l), LONG((double)bottom / l) });
	inline LRect  operator* (int l)           const reflect_as({ left * l, top * l, right * l, bottom * l });
	inline LRect  operator/ (int l)           const reflect_as({ left / l, top / l, right / l, bottom / l });
	inline LRect &operator*=(double l)              reflect_to_self(left = LONG((double)left * l), top = LONG((double)top * l), right = LONG((double)right * l), bottom = LONG((double)bottom * l));
	inline LRect &operator/=(double l)              reflect_to_self(left = LONG((double)left / l), top = LONG((double)top / l), right = LONG((double)right / l), bottom = LONG((double)bottom / l));
	inline LRect &operator/=(int l)                 reflect_to_self(left /= l, top /= l, right /= l, bottom /= l);
	inline LRect &operator*=(int l)                 reflect_to_self(left *= l; top *= l, right *= l, bottom *= l);
	inline LRect &operator+=(const LRect &r)        reflect_to_self(left += r.left, top += r.top, right += r.right, bottom += r.bottom);
	inline LRect &operator-=(const LRect &r)        reflect_to_self(left -= r.left, top -= r.top, right -= r.right, bottom -= r.bottom);
	inline LRect &operator+=(const LPoint &p)       reflect_to_self(left += p.x, top += p.y, right += p.x, bottom += p.y);
	inline LRect &operator-=(const LPoint &p)       reflect_to_self(left -= p.x, top -= p.y, right -= p.x, bottom -= p.y);
	inline operator MARGINS() const reflect_as({ left, right, top, bottom });
	inline operator LSize()   const reflect_as({ right - left + 1, bottom - top + 1 });
	inline operator LPoint()  const reflect_as({ left, top });
	inline operator LPRECT()        reflect_as(this);
	inline operator LPCRECT() const reflect_as(this);
	inline operator LPARAM()  const reflect_as((LPARAM)this);
	static inline LRect &Attach(RECT &rc) reflect_as(reuse_as<LRect>(rc));
};
inline LRect operator+(const LPoint &p, const LRect &r) reflect_as(r + p);
inline LRect operator-(const LPoint &p, const LRect &r) reflect_as(-(r - p));
inline LRect operator&(const LPoint &p, const LSize &s) reflect_as({ p, s });
inline LRect operator&(const LSize &s, const LPoint &p) reflect_as({ p, s });

class RGBColor {
protected:
	COLORREF cr;
public:
	RGBColor(COLORREF color) : cr(color) {}
	RGBColor(BYTE red, BYTE green, BYTE blue) :
		cr(RGB(red, green, blue)) {}

	inline BYTE Red()   const reflect_as(GetRValue(self));
	inline BYTE Green() const reflect_as(GetGValue(self));
	inline BYTE Blue()  const reflect_as(GetBValue(self));

	template<size_t len>
	static inline arrayof<RGBColor, len> &Attach(arrayof<COLORREF, len> &ary) reflect_as(reuse_as<arrayof<RGBColor, len>>(ary));
	inline operator COLORREF() const { return cr; }
	static inline RGBColor &Attach(COLORREF &clr) reflect_as(*(RGBColor *)&clr);
};

enum_class(Locales, LCID,
	enum_default Default = LOCALE_CUSTOM_DEFAULT,
	Unspecified = LOCALE_CUSTOM_UNSPECIFIED,
	UIDefault   = LOCALE_CUSTOM_UI_DEFAULT,
	Neutral     = LOCALE_NEUTRAL,
	Invariant   = LOCALE_INVARIANT);
enum_flags(TimeFormat, DWORD,
	enum_default Default = 0,
	NoMinutesOrSeconds = TIME_NOMINUTESORSECONDS,
	NoSecond           = TIME_NOSECONDS,
	NoTimeMarker       = TIME_NOTIMEMARKER,
	Force24H           = TIME_FORCE24HOURFORMAT);
enum_flags(DateFormat, DWORD,
	enum_default Default = 0,
	ShortDate    = DATE_SHORTDATE,
	LongDate     = DATE_LONGDATE,
	CalendarAlt  = DATE_USE_ALT_CALENDAR);
struct SysTime : public SYSTEMTIME {
	SysTime(Null) : SYSTEMTIME{ 0 } {}
	SysTime() reflect_to(GetSystemTime(this));
	SysTime(const FILETIME &ft) assert(FileTimeToSystemTime(&ft, this));
	static inline SysTime Local() reflect_to(SysTime st; GetLocalTime(&st), st);
	String FormatTime(TimeFormat = TimeFormat::Default, Locales = Locales::Default) const;
	String FormatDate(DateFormat = DateFormat::Default, Locales = Locales::Default) const;
	operator String() const;
};
#pragma endregion

}