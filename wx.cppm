module;

#define WX_CPPM_TYPE
#include "wx_type"

export module wx;

namespace WX {

export
constexpr bool IsUnicode =
#if defined(UNICODE) || defined(_UNICODE)
	true;
#else
	false;
#endif

#pragma region String References
export {
template<class TCHAR>
class StringBase;
using String = StringBase<TCHAR>;
using StringA = StringBase<CHAR>;
using StringW = StringBase<WCHAR>;
template<bool IsUnicode>
using StringX = switch_structx(String);

template<bool IsUnicode>
using XCHAR = std::conditional_t<IsUnicode, WCHAR, CHAR>;
template<bool IsUnicode>
using LPXSTR = std::conditional_t<IsUnicode, LPWSTR, LPSTR>;
template<bool IsUnicode>
using LPCXSTR = std::conditional_t<IsUnicode, LPCWSTR, LPCSTR>;
template<class TCHAR>
constexpr bool IsCharA = std::is_same_v<TCHAR, CHAR> || std::is_same_v<TCHAR, LPSTR> || std::is_same_v<TCHAR, LPCSTR>;
template<class TCHAR>
constexpr bool IsCharW = std::is_same_v<TCHAR, WCHAR> || std::is_same_v<TCHAR, LPWSTR> || std::is_same_v<TCHAR, LPCWSTR>;
template<bool IsUnicode, class AnyTypeW, class AnyTypeA>
constexpr auto AnyX(AnyTypeW *w, AnyTypeA *a) {
	if constexpr (IsUnicode)
		 return w;
	else return a;
}
template<bool IsUnicode, class AnyTypeW, class AnyTypeA>
constexpr auto &AnyX(AnyTypeW &w, AnyTypeA &a) {
	if constexpr (IsUnicode)
		 return w;
	else return a;
}
template<bool IsUnicode, class AnyTypeW, class AnyTypeA>
constexpr auto AnyX(AnyTypeW &&w, AnyTypeA &&a) {
	if constexpr (IsUnicode)
		 return w;
	else return a;
}
}
#pragma endregion

#pragma region WX Inside 

#pragma region Static Compatible
template <class AnyCallable, class Ret, class... Args>
auto __static_compatible(...) -> std::false_type;
template <class AnyCallable, class Ret, class... Args>
auto __static_compatible(int) -> std::is_convertible<
	decltype(std::declval<AnyCallable>()(std::declval<Args>()...)), Ret>;
export {
	template<class AnyCallable, class FuncType>
	constexpr bool static_compatible = false;
	template<class AnyCallable, class Ret, class... Args>
	constexpr bool static_compatible<AnyCallable, Ret(Args...)> = decltype(__static_compatible<AnyCallable, Ret, Args...>(0))::value;
}
#pragma endregion

#pragma region Chain Extender 
export template<class ParentClass, class ChildClass>
using Chain = std::conditional_t<std::is_void_v<ChildClass>, ParentClass, ChildClass>;
export template<class ParentClass, class ChildClass>
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
#define static // In G++ maybe fail on static in template
subtype_branch(super);
#undef static
export template<class Class1, class Class2>
constexpr bool is_chain_extended_on =
std::is_void_v<Class1> || std::is_void_v<Class2> ? false :
	std::is_same_v<Class1, Class2> ? true :
	is_chain_extended_on<subtype_branchof_super<Class1, void>, Class2>;
#pragma endregion

#pragma region Reuse 77 Casts
export {
template<class OutType, class InType>
inline OutType reuse_as(InType in) {
	misuse_assert(sizeof(OutType) == sizeof(InType), "Must fit same size");
	return *(OutType *)&in;
}
template<class OutType, class InType>
inline OutType small_cast(InType in) {
	misuse_assert(sizeof(OutType) >= sizeof(InType), "sizeof in-type must small or equal to out-type");
	return *(OutType *)&in;
}
template<class OutType, class InType>
inline OutType big_cast(InType in) {
	misuse_assert(sizeof(OutType) <= sizeof(InType), "sizeof in-type must big or equal to out-type");
	return *(OutType *)&in;
}
template<class OutType, class InType>
inline OutType &ref_as(InType &in) {
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
constexpr bool IsRef = false;
template<class RefType>
constexpr bool IsRef<RefAs<RefType>> = true;
}
#pragma endregion

#pragma region Array & Counter 
export {
template<class AnyType, size_t Len>
using arrayof = AnyType[Len];
template<class...Args>
constexpr size_t ArgsCount(Args...) reflect_as(sizeof...(Args));
template<class AnyType>
constexpr size_t lengthof = 0;
template<class AnyType, size_t Len>
constexpr size_t lengthof<const arrayof<AnyType, Len> &> = Len;
template<class AnyType, size_t Len>
constexpr auto &_CountOf(const arrayof<AnyType, Len> &a) reflect_as(a);
template<class AnyType>
struct SizeOf_t { static constexpr size_t val = sizeof(AnyType); };
template<>
struct SizeOf_t<void> { static constexpr size_t val = 0; };
template<class AnyType>
constexpr size_t SizeOf = SizeOf_t<AnyType>::val;
}
#pragma endregion

#pragma region Enum
def_memberof(HasProtoEnum);
export template<class AnyType>
constexpr bool IsEnum = member_HasProtoEnum_of<AnyType>::callable;
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
		if constexpr (IsEnum<AnyEnum>) {
			if constexpr (IsCharW<TCHAR>)
				reflect_as(GetMaps<AnyEnum::Count>(AnyEnum::__EntriesW))
			else reflect_as(GetMaps<AnyEnum::Count>(AnyEnum::__EntriesA))
		}
	}
};
#pragma region EnumSupports
export {
/* EnumTableX */
template<class AnyEnum, class TCHAR = ::TCHAR>
constexpr auto EnumTable = Rx<TCHAR>::template Table<AnyEnum>();
template<class AnyEnum>
constexpr auto EnumTableA = EnumTable<AnyEnum, CHAR>;
template<class AnyEnum>
constexpr auto EnumTableW = EnumTable<AnyEnum, WCHAR>;
/* (misc) */
template<class Enum1, class Enum2, class EnumType>
inline auto __makeResult(EnumType val) {
	constexpr auto left = is_chain_extended_on<Enum1, Enum2>;
	constexpr auto right = is_chain_extended_on<Enum2, Enum1>;
	static_assert(left || right, "Convertless");
	if constexpr (left)
		return (Enum1)val;
	elif constexpr (right)
		return (Enum1)val;
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
}
#pragma endregion
#pragma endregion

#pragma region ToProto
export {
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
}
#pragma endregion

#pragma region TypeList 
export {
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
}
#pragma endregion

#pragma region FunctionOf
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
export
template<class OtherType>
using functionof = __functionof<to_proto<OtherType>>;
#pragma endregion

#pragma endregion

#pragma region Compilation Informations
export {
/* _CPLUSPLUS_STANDARD */
#define _CPLUSPLUS_STANDARDA _MACRO_CALL(STROFA, __cplusplus)
#define _CPLUSPLUS_STANDARDW _MACRO_CALL(STROFW, __cplusplus)
#define _CPLUSPLUS_STANDARD T(_CPLUSPLUS_STANDARDA)
inline  CHAR CPLUSPLUS_STANDARDA[]{ _CPLUSPLUS_STANDARDA };
inline WCHAR CPLUSPLUS_STANDARDW[]{ _CPLUSPLUS_STANDARDW };
inline TCHAR CPLUSPLUS_STANDARD []{ _CPLUSPLUS_STANDARD  };
/* _CHAR_MODE */
#ifdef UNICODE
#	define _CHAR_MODEA "Unicode"
#else
#	define _CHAR_MODEA "Multibyte"
#endif
#define _CHAR_MODEW LSTR(_CHAR_MODEA)
#define _CHAR_MODE  TEXT(_CHAR_MODEA)
inline  CHAR CHAR_MODEA[]{ _CHAR_MODEA };
inline WCHAR CHAR_MODEW[]{ _CHAR_MODEW };
inline TCHAR CHAR_MODE []{ _CHAR_MODE  };
/* _BUILD_DATE */
#define _BUILD_DATEA __DATE__ " " __TIME__
#define _BUILD_DATEW LSTR(_BUILD_DATEA)
#define _BUILD_DATE  TEXT(_BUILD_DATEA)
inline  CHAR BUILD_DATEA[]{ _BUILD_DATEA };
inline WCHAR BUILD_DATEW[]{ _BUILD_DATEW };
inline TCHAR BUILD_DATE []{ _BUILD_DATE  };
/* _COMPILATION_MODE */
#ifdef _DEBUG
#	define _COMPILATION_MODEA  "Debug"
#else
#	define _COMPILATION_MODEA  "Release"
#endif
#	define _COMPILATION_MODEW LSTR(_COMPILATION_MODEA)
#	define _COMPILATION_MODE  TEXT(_COMPILATION_MODEA)
inline  CHAR COMPILATION_MODEA[]{ _COMPILATION_MODEA };
inline WCHAR COMPILATION_MODEW[]{ _COMPILATION_MODEW };
inline TCHAR COMPILATION_MODE []{ _COMPILATION_MODE  };
/* _COMPILATION_PLATFORM */
#ifdef _WIN64
#	define _COMPILATION_PLATFORMA  "64-bits"
#elif defined(_WIN32)
#	define _COMPILATION_PLATFORMA "32-bits"
#else
#	define _COMPILATION_PLATFORMA "Unknown"
#endif
#define _COMPILATION_PLATFORMW LSTR(_COMPILATION_PLATFORMA)
#define _COMPILATION_PLATFORM  TEXT(_COMPILATION_PLATFORMA)
inline  CHAR COMPILATION_PLATFORMA[]{ _COMPILATION_PLATFORMA };
inline WCHAR COMPILATION_PLATFORMW[]{ _COMPILATION_PLATFORMW };
inline TCHAR COMPILATION_PLATFORM []{ _COMPILATION_PLATFORM  };
/* _COMPILATION_ARCHITECTURE */
#ifdef _M_X64
#	define _COMPILATION_ARCHITECTUREA "x64"
#elif defined(_M_IX86)
#	define _COMPILATION_ARCHITECTUREA "x86"
#elif defined(_M_AMD64)
#	define _COMPILATION_ARCHITECTUREA "AMD64"
#elif defined(_M_ARM64)
#	define _COMPILATION_ARCHITECTUREA "ARM64"
#elif defined(_M_ARM)
#	define _COMPILATION_ARCHITECTUREA "ARM"
#elif defined(_M_ARM64EC)
#	define _COMPILATION_ARCHITECTUREA "ARM64EC"
#else
#	define _COMPILATION_ARCHITECTUREA "Unknown"
#endif
#define _COMPILATION_ARCHITECTUREW LSTR(_COMPILATION_ARCHITECTUREA)
#define _COMPILATION_ARCHITECTURE  TEXT(_COMPILATION_ARCHITECTUREA)
inline  CHAR COMPILATION_ARCHITECTUREA[]{ _COMPILATION_ARCHITECTUREA };
inline WCHAR COMPILATION_ARCHITECTUREW[]{ _COMPILATION_ARCHITECTUREW };
inline TCHAR COMPILATION_ARCHITECTURE []{ _COMPILATION_ARCHITECTURE  };
/* _COMPILATION_COMPILER */
#if defined(__clang__)
#	define _COMPILATION_COMPILERA \
	"Clang " _MACRO_CALL(STROFA, __clang_version__)
#elif defined(__GNUC__)
#	define _COMPILATION_COMPILERA \
	"GCC " _MACRO_CALL(STROFA, __VERSION__)
#elif _MSC_VER
#	define _COMPILATION_COMPILERA \
	"Microsoft C++ (_MSC_FULL_VER=" _MACRO_CALL(STROFA, _MSC_FULL_VER) ")"
#else
#	define _COMPILATION_COMPILERA \
	"Unknown"
#endif
#define _COMPILATION_COMPILERW LSTR(_COMPILATION_COMPILERA)
#define _COMPILATION_COMPILER  TEXT(_COMPILATION_COMPILERA)
inline  CHAR COMPILATION_COMPILERA[]{ _COMPILATION_COMPILERA };
inline WCHAR COMPILATION_COMPILERW[]{ _COMPILATION_COMPILERW };
inline TCHAR COMPILATION_COMPILER []{ _COMPILATION_COMPILER  };
/* _NTDDI_ */
#if NTDDI_VERSION >= NTDDI_WIN11_GE
#	define _NTDDI_NAMEA "Windows 11 'Germanium'"
#elif NTDDI_VERSION >= NTDDI_WIN11_GA
#	define _NTDDI_NAMEA "Windows 11 'Gallium'"
#elif NTDDI_VERSION >= NTDDI_WIN11_ZN
#	define _NTDDI_NAMEA "Windows 11 'Zinc'"
#elif NTDDI_VERSION >= NTDDI_WIN10_CU
#	define _NTDDI_NAMEA "Windows 10 'Copper'"
#elif NTDDI_VERSION >= NTDDI_WIN10_NI
#	define _NTDDI_NAMEA "Windows 10 'Nickel'"
#elif NTDDI_VERSION >= NTDDI_WIN10_CO
#	define _NTDDI_NAMEA "Windows 10 'Cobalt'"
#elif NTDDI_VERSION >= NTDDI_WIN10_FE
#	define _NTDDI_NAMEA "Windows 10 'Iron'"
#elif NTDDI_VERSION >= NTDDI_WIN10_MN
#	define _NTDDI_NAMEA "Windows 10 'Manganese'"
#elif NTDDI_VERSION >= NTDDI_WIN10_VB
#	define _NTDDI_NAMEA "Windows 10 'Vibranium'"
#elif NTDDI_VERSION >= NTDDI_WIN10_19H1
#	define _NTDDI_NAMEA "Windows 10 1903 '19H1''"
#elif NTDDI_VERSION >= NTDDI_WIN10_RS5
#	define _NTDDI_NAMEA "Windows 10 1809 'Redstone 5'"
#elif NTDDI_VERSION >= NTDDI_WIN10_RS4
#	define _NTDDI_NAMEA "Windows 10 1803 'Redstone 4'"
#elif NTDDI_VERSION >= NTDDI_WIN10_RS3
#	define _NTDDI_NAMEA "Windows 10 1709 'Redstone 3'"
#elif NTDDI_VERSION >= NTDDI_WIN10_RS2
#	define _NTDDI_NAMEA "Windows 10 1703 'Redstone 2'"
#elif NTDDI_VERSION >= NTDDI_WIN10_RS1
#	define _NTDDI_NAMEA "Windows 10 1607 'Redstone 1'"
#elif NTDDI_VERSION >= NTDDI_WIN10_TH2
#	define _NTDDI_NAMEA "Windows 10 1511 'Threshold 2'"
#elif NTDDI_VERSION >= NTDDI_WIN10
#	define _NTDDI_NAMEA "Windows 10 1507 'Threshold'"
#elif NTDDI_VERSION >= NTDDI_WINBLUE
#	define _NTDDI_NAMEA "Windows 8.1"
#elif NTDDI_VERSION >= NTDDI_WIN8
#	define _NTDDI_NAMEA "Windows 8"
#elif NTDDI_VERSION >= NTDDI_WIN7
#	define _NTDDI_NAMEA "Windows 7"
#elif NTDDI_VERSION >= NTDDI_WIN6SP4
#	define _NTDDI_NAMEA "Windows Vista SP4"
#elif NTDDI_VERSION >= NTDDI_WIN6SP3
#	define _NTDDI_NAMEA "Windows Vista SP3"
#elif NTDDI_VERSION >= NTDDI_WIN6SP2
#	define _NTDDI_NAMEA "Windows Vista SP2"
#elif NTDDI_VERSION >= NTDDI_WIN6SP1
#	define _NTDDI_NAMEA "Windows Vista SP1"
#elif NTDDI_VERSION >= NTDDI_WIN6
#	define _NTDDI_NAMEA "Windows Vista"
#elif NTDDI_VERSION >= NTDDI_WS03SP4
#	define _NTDDI_NAMEA "Windows Server 2003 SP4"
#elif NTDDI_VERSION >= NTDDI_WS03SP3
#	define _NTDDI_NAMEA "Windows Server 2003 SP3"
#elif NTDDI_VERSION >= NTDDI_WS03SP2
#	define _NTDDI_NAMEA "Windows Server 2003 SP2"
#elif NTDDI_VERSION >= NTDDI_WS03SP1
#	define _NTDDI_NAMEA "Windows Server 2003 SP1"
#elif NTDDI_VERSION >= NTDDI_WS03
#	define _NTDDI_NAMEA "Windows Server 2003"
#elif NTDDI_VERSION >= NTDDI_WINXPSP4
#	define _NTDDI_NAMEA "Windows XP SP4"
#elif NTDDI_VERSION >= NTDDI_WINXPSP3
#	define _NTDDI_NAMEA "Windows XP SP3"
#elif NTDDI_VERSION >= NTDDI_WINXPSP2
#	define _NTDDI_NAMEA "Windows XP SP2"
#elif NTDDI_VERSION >= NTDDI_WINXPSP1
#	define _NTDDI_NAMEA "Windows XP SP1"
#elif NTDDI_VERSION >= NTDDI_WINXP
#	define _NTDDI_NAMEA "Windows XP"
#else
#	define _NTDDI_NAMEA "Older Windows Version"
#endif
#define _NTDDI_NAMEW LSTR(_NTDDI_NAMEA)
#define _NTDDI_NAME  TEXT(_NTDDI_NAMEA)
#define _NTDDI_VERA _MACRO_CALL(STROFA, NTDDI_VERSION)
#define _NTDDI_VERW _MACRO_CALL(STROFW, NTDDI_VERSION)
#define _NTDDI_VER  _MACRO_CALL(STROF , NTDDI_VERSION)
#define _NTDDIA _NTDDI_NAMEA  " (NTDDI_VERSION="  _NTDDI_VERA  ")"
#define _NTDDIW _NTDDI_NAMEW L" (NTDDI_VERSION="  _NTDDI_VERW L")"
#define _NTDDI  _NTDDI_NAME T(" (NTDDI_VERSION=") _NTDDI_VER T(")")
inline  CHAR TARGET_NTDDI_NAMEA[]{ _NTDDI_NAMEA };
inline WCHAR TARGET_NTDDI_NAMEW[]{ _NTDDI_NAMEW };
inline TCHAR TARGET_NTDDI_NAME[]{ _NTDDI_NAME };
inline  CHAR TARGET_NTDDI_VERA[]{ _NTDDI_VERA };
inline WCHAR TARGET_NTDDI_VERW[]{ _NTDDI_VERW };
inline TCHAR TARGET_NTDDI_VER []{ _NTDDI_VER  };
inline  CHAR TARGET_NTDDIA[]{ _NTDDIA };
inline WCHAR TARGET_NTDDIW[]{ _NTDDIW };
inline TCHAR TARGET_NTDDI []{ _NTDDI  };
/* _COMPILATION_INFO */
#define _COMPILATION_INFOA \
	"C++ Standard:     " _CPLUSPLUS_STANDARDA "\n" \
	"Compilation Mode: " _COMPILATION_MODEA "\n" \
	"Char Mode:        " _CHAR_MODEA "\n" \
	"Build Date:       " _BUILD_DATEA "\n" \
	"Platform Bits:    " _COMPILATION_PLATFORMA "\n" \
	"Architecture:     " _COMPILATION_ARCHITECTUREA "\n" \
	"Compiler:         " _COMPILATION_COMPILERA "\n" \
	"NTDDI Version:    " _NTDDIA "\n"
#define _COMPILATION_INFOW LSTR(_COMPILATION_INFOA)
#define _COMPILATION_INFO  TEXT(_COMPILATION_INFOA)
inline  CHAR COMPILATION_INFOA[]{ _COMPILATION_INFOA };
inline WCHAR COMPILATION_INFOW[]{ _COMPILATION_INFOW };
inline TCHAR COMPILATION_INFO []{ _COMPILATION_INFO  };
}
#pragma endregion

#pragma region Exception
export
class Exception {
	LPCSTR lpFile = O;
	LPCSTR lpFunc = O;
	LPCSTR lpSent = O;
	UINT uLine = 0;
	DWORD dwErrCode = 0;
public:
	Exception() {}
	inline Exception(LPCSTR lpszFile, LPCSTR lpszFunc, LPCSTR lpszSent,
			  UINT nLine) :
		lpFile(lpszFile), lpFunc(lpszFunc), lpSent(lpszSent),
		uLine(nLine), dwErrCode(GetLastError())
	{ SetLastError(0); }
	inline Exception(LPCSTR lpszFile, LPCSTR lpszFunc, LPCSTR lpszSent,
			  UINT nLine, DWORD dwErrCode) :
		lpFile(lpszFile), lpFunc(lpszFunc), lpSent(lpszSent),
		uLine(nLine), dwErrCode(GetLastError()) {}
public: // Property - File
	template<bool IsUnicode = WX::IsUnicode>
	StringX<IsUnicode> File() const;
	const StringA FileA() const;
	StringW FileW() const;
public: // Property - Function
	template<bool IsUnicode = WX::IsUnicode>
	StringX<IsUnicode> Function() const;
	const StringA FunctionA() const;
	StringW FunctionW() const;
public: // Property - Sentence
	template<bool IsUnicode = WX::IsUnicode>
	StringX<IsUnicode> Sentence() const;
	const StringA SentenceA() const;
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
	inline operator bool() const reflect_as(lpSent);
	operator StringA() const;
	operator StringW() const;
};
#pragma endregion

#pragma region FunctionBase
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
#pragma region Function
export {
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
}
#pragma endregion
#pragma endregion

#pragma region StrSafe.h
#undef StringCchCopy
// StringCchCopy
inline void StringCchCopy(LPSTR pszDest, size_t cchDest, LPCSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyA(pszDest, cchDest, pszSrc)));
inline void StringCchCopy(LPWSTR pszDest, size_t cchDest, LPCWSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyW(pszDest, cchDest, pszSrc)));
#undef StringCbCopy
// StringCbCopy
inline void StringCbCopy(LPSTR pszDest, size_t cbDest, LPCSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyA(pszDest, cbDest, pszSrc)));
inline void StringCbCopy(LPWSTR pszDest, size_t cbDest, LPCWSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyW(pszDest, cbDest, pszSrc)));
#undef StringCchCopyEx
// StringCchCopyEx
inline void StringCchCopy(LPSTR pszDest, size_t cchDest, LPCSTR pszSrc,
						  LPSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyExA(pszDest, cchDest, pszSrc, ppszDestEnd, pcchRemaining, dwFlags)));
inline void StringCchCopy(LPWSTR pszDest, size_t cchDest, LPCWSTR pszSrc,
						  LPWSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyExW(pszDest, cchDest, pszSrc, ppszDestEnd, pcchRemaining, dwFlags)));
#undef StringCbCopyEx
// StringCbCopyEx
inline void StringCbCopy(LPSTR pszDest, size_t cbDest, LPCSTR pszSrc,
						 LPSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyExA(pszDest, cbDest, pszSrc, ppszDestEnd, pcbRemaining, dwFlags)));
inline void StringCbCopy(LPWSTR pszDest, size_t cbDest, LPCWSTR pszSrc,
						 LPWSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyExW(pszDest, cbDest, pszSrc, ppszDestEnd, pcbRemaining, dwFlags)));
#undef StringCchCopyN
// StringCchCopyN
inline void StringCchCopyN(LPSTR pszDest, size_t cchDest, LPCSTR pszSrc, size_t cchToCopy)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyNA(pszDest, cchDest, pszSrc, cchToCopy)));
inline void StringCchCopyN(LPWSTR pszDest, size_t cchDest, LPCWSTR pszSrc, size_t cchToCopy)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyNW(pszDest, cchDest, pszSrc, cchToCopy)));
#undef StringCbCopyN
// StringCbCopyN
inline void StringCbCopyN(LPSTR pszDest, size_t cbDest, LPCSTR pszSrc, size_t cbToCopy)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyNA(pszDest, cbDest, pszSrc, cbToCopy)));
inline void StringCbCopyN(LPWSTR pszDest, size_t cbDest, LPCWSTR pszSrc, size_t cbToCopy)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyNW(pszDest, cbDest, pszSrc, cbToCopy)));
#undef StringCchCopyNEx
// StringCchCopyNEx
inline void StringCchCopyN(LPSTR pszDest, size_t cchDest,
						   LPCSTR pszSrc, size_t cchToCopy,
						   LPSTR *ppszDestEnd, size_t *pcchRemaining,
						   DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyNExA(pszDest, cchDest, pszSrc, cchToCopy, ppszDestEnd, pcchRemaining, dwFlags)));
inline void StringCchCopyN(LPWSTR pszDest, size_t cchDest,
						   LPCWSTR pszSrc, size_t cchToCopy,
						   LPWSTR *ppszDestEnd, size_t *pcchRemaining,
						   DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCopyNExW(pszDest, cchDest, pszSrc, cchToCopy, ppszDestEnd, pcchRemaining, dwFlags)));
#undef StringCbCopyNEx
// StringCbCopyNEx
inline void StringCbCopyN(LPSTR pszDest, size_t cbDest,
						  LPCSTR pszSrc, size_t cbToCopy,
						  LPSTR *ppszDestEnd, size_t *pcbRemaining,
						  DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyNExA(pszDest, cbDest, pszSrc, cbToCopy, ppszDestEnd, pcbRemaining, dwFlags)));
inline void StringCbCopyN(LPWSTR pszDest, size_t cbDest,
						  LPCWSTR pszSrc, size_t cbToCopy,
						  LPWSTR *ppszDestEnd, size_t *pcbRemaining,
						  DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCopyNExW(pszDest, cbDest, pszSrc, cbToCopy, ppszDestEnd, pcbRemaining, dwFlags)));
#undef StringCchCat
// StringCchCat
inline void StringCchCat(LPSTR pszDest, size_t cchDest, LPCSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCchCatA(pszDest, cchDest, pszSrc)));
inline void StringCchCat(LPWSTR pszDest, size_t cchDest, LPCWSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCchCatW(pszDest, cchDest, pszSrc)));
#undef StringCbCat
// StringCbCat
inline void StringCbCat(LPSTR pszDest, size_t cbDest, LPCSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCbCatA(pszDest, cbDest, pszSrc)));
inline void StringCbCat(LPWSTR pszDest, size_t cbDest, LPCWSTR pszSrc)
	assertl_reflect_as(SUCCEEDED(::StringCbCatW(pszDest, cbDest, pszSrc)));
#undef StringCchCatEx
// StringCchCatEx
inline void StringCchCat(LPSTR pszDest, size_t cchDest, LPCSTR pszSrc,
						 LPSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCatExA(pszDest, cchDest, pszSrc, ppszDestEnd, pcchRemaining, dwFlags)));
inline void StringCchCat(LPWSTR pszDest, size_t cchDest, LPCWSTR pszSrc,
						 LPWSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCatExW(pszDest, cchDest, pszSrc, ppszDestEnd, pcchRemaining, dwFlags)));
#undef StringCbCatEx
// StringCbCatEx
inline void StringCbCat(LPSTR pszDest, size_t cbDest, LPCSTR pszSrc,
						LPSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCatExA(pszDest, cbDest, pszSrc, ppszDestEnd, pcbRemaining, dwFlags)));
inline void StringCbCat(LPWSTR pszDest, size_t cbDest, LPCWSTR pszSrc,
						LPWSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCatExW(pszDest, cbDest, pszSrc, ppszDestEnd, pcbRemaining, dwFlags)));
#undef StringCchCatN
// StringCchCatN
inline void StringCchCatN(LPSTR pszDest, size_t cchDest, LPCSTR pszSrc, size_t cchToAppend)
	assertl_reflect_as(SUCCEEDED(::StringCchCatNA(pszDest, cchDest, pszSrc, cchToAppend)));
inline void StringCchCatN(LPWSTR pszDest, size_t cchDest, LPCWSTR pszSrc, size_t cchToAppend)
	assertl_reflect_as(SUCCEEDED(::StringCchCatNW(pszDest, cchDest, pszSrc, cchToAppend)));
#undef StringCbCatN
// StringCbCatN
inline void StringCbCatN(LPSTR pszDest, size_t cbDest, LPCSTR pszSrc, size_t cbToAppend)
	assertl_reflect_as(SUCCEEDED(::StringCbCatNA(pszDest, cbDest, pszSrc, cbToAppend)));
inline void StringCbCatN(LPWSTR pszDest, size_t cbDest, LPCWSTR pszSrc, size_t cbToAppend)
	assertl_reflect_as(SUCCEEDED(::StringCbCatNW(pszDest, cbDest, pszSrc, cbToAppend)));
#undef StringCchCatNEx
// StringCchCatNEx
inline void StringCchCatN(LPSTR pszDest, size_t cchDest,
						  LPCSTR pszSrc, size_t cchToAppend,
						  LPSTR *ppszDestEnd, size_t *pcchRemaining,
						  DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCatNExA(pszDest, cchDest, pszSrc, cchToAppend, ppszDestEnd, pcchRemaining, dwFlags)));
inline void StringCchCatN(LPWSTR pszDest, size_t cchDest,
						  LPCWSTR pszSrc, size_t cchToAppend,
						  LPWSTR *ppszDestEnd, size_t *pcchRemaining,
						  DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchCatNExW(pszDest, cchDest, pszSrc, cchToAppend, ppszDestEnd, pcchRemaining, dwFlags)));
#undef StringCbCatNEx
// StringCbCatNEx
inline void StringCbCatN(LPSTR pszDest, size_t cbDest,
						 LPCSTR pszSrc, size_t cbToAppend,
						 LPSTR *ppszDestEnd, size_t *pcbRemaining,
						 DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCatNExA(pszDest, cbDest, pszSrc, cbToAppend, ppszDestEnd, pcbRemaining, dwFlags)));
inline void StringCbCatN(LPWSTR pszDest, size_t cbDest,
						 LPCWSTR pszSrc, size_t cbToAppend,
						 LPWSTR *ppszDestEnd, size_t *pcbRemaining,
						 DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbCatNExW(pszDest, cbDest, pszSrc, cbToAppend, ppszDestEnd, pcbRemaining, dwFlags)));
#undef StringCchVPrintf
// StringCchVPrintf
inline void StringCchVPrintf(LPSTR pszDest, size_t cchDest, LPCSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCchVPrintfA(pszDest, cchDest, pszFormat, argList)));
inline void StringCchVPrintf(LPWSTR pszDest, size_t cchDest, LPCWSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCchVPrintfW(pszDest, cchDest, pszFormat, argList)));
#undef StringCbVPrintf
// StringCbVPrintf
inline void StringCbVPrintf(LPSTR pszDest, size_t cbDest, LPCSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCbVPrintfA(pszDest, cbDest, pszFormat, argList)));
inline void StringCbVPrintf(LPWSTR pszDest, size_t cbDest, LPCWSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCbVPrintfW(pszDest, cbDest, pszFormat, argList)));
#undef StringCchPrintf
// StringCchPrintf
inline void StringCchPrintf(LPSTR pszDest, size_t cchDest, LPCSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCchPrintfA(pszDest, cchDest, pszFormat)));
inline void StringCchPrintf(LPWSTR pszDest, size_t cchDest, LPCWSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCchPrintfW(pszDest, cchDest, pszFormat)));
#undef StringCbPrintf
// StringCbPrintf
inline void StringCbPrintf(LPSTR pszDest, size_t cbDest, LPCSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCbPrintfA(pszDest, cbDest, pszFormat)));
inline void StringCbPrintf(LPWSTR pszDest, size_t cbDest, LPCWSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCbPrintfW(pszDest, cbDest, pszFormat)));
#undef StringCchPrintfEx
// StringCchPrintfEx
inline void StringCchPrintf(LPSTR pszDest, size_t cchDest, LPSTR *ppszDestEnd,
							size_t *pcchRemaining, DWORD dwFlags, LPCSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCchPrintfExA(pszDest, cchDest, ppszDestEnd, pcchRemaining, dwFlags, pszFormat)));
inline void StringCchPrintf(LPWSTR pszDest, size_t cchDest, LPWSTR *ppszDestEnd,
							size_t *pcchRemaining, DWORD dwFlags, LPCWSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCchPrintfExW(pszDest, cchDest, ppszDestEnd, pcchRemaining, dwFlags, pszFormat)));
#undef StringCbPrintfEx
// StringCbPrintfEx
inline void StringCbPrintf(LPSTR pszDest, size_t cbDest, LPSTR *ppszDestEnd,
						   size_t *pcbRemaining, DWORD dwFlags, LPCSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCbPrintfExA(pszDest, cbDest, ppszDestEnd, pcbRemaining, dwFlags, pszFormat)));
inline void StringCbPrintf(LPWSTR pszDest, size_t cbDest, LPWSTR *ppszDestEnd,
						   size_t *pcbRemaining, DWORD dwFlags, LPCWSTR pszFormat, ...)
	assertl_reflect_as(SUCCEEDED(::StringCbPrintfExW(pszDest, cbDest, ppszDestEnd, pcbRemaining, dwFlags, pszFormat)));
#undef StringCchVPrintfEx
// StringCchVPrintfEx
inline void StringCchVPrintf(LPSTR pszDest, size_t cchDest, LPSTR *ppszDestEnd,
							 size_t *pcchRemaining, DWORD dwFlags, LPCSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCchVPrintfExA(pszDest, cchDest, ppszDestEnd, pcchRemaining, dwFlags, pszFormat, argList)));
inline void StringCchVPrintf(LPWSTR pszDest, size_t cchDest, LPWSTR *ppszDestEnd,
							 size_t *pcchRemaining, DWORD dwFlags, LPCWSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCchVPrintfExW(pszDest, cchDest, ppszDestEnd, pcchRemaining, dwFlags, pszFormat, argList)));
#undef StringCbVPrintfEx
// StringCbVPrintfEx
inline void StringCbVPrintf(LPSTR pszDest, size_t cbDest, LPSTR *ppszDestEnd,
							size_t *pcbRemaining, DWORD dwFlags, LPCSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCbVPrintfExA(pszDest, cbDest, ppszDestEnd, pcbRemaining, dwFlags, pszFormat, argList)));
inline void StringCbVPrintf(LPWSTR pszDest, size_t cbDest, LPWSTR *ppszDestEnd,
							size_t *pcbRemaining, DWORD dwFlags, LPCWSTR pszFormat, va_list argList)
	assertl_reflect_as(SUCCEEDED(::StringCbVPrintfExW(pszDest, cbDest, ppszDestEnd, pcbRemaining, dwFlags, pszFormat, argList)));
#undef StringCchGets
// StringCchGets
inline void StringCchGets(LPSTR pszDest, size_t cchDest)
	assertl_reflect_as(SUCCEEDED(::StringCchGetsA(pszDest, cchDest)));
inline void StringCchGets(LPWSTR pszDest, size_t cchDest)
	assertl_reflect_as(SUCCEEDED(::StringCchGetsW(pszDest, cchDest)));
#undef StringCbGets
// StringCbGets
inline void StringCbGets(LPSTR pszDest, size_t cbDest)
	assertl_reflect_as(SUCCEEDED(::StringCbGetsA(pszDest, cbDest)));
inline void StringCbGets(LPWSTR pszDest, size_t cbDest)
	assertl_reflect_as(SUCCEEDED(::StringCbGetsW(pszDest, cbDest)));
#undef StringCchGetsEx
// StringCchGetsEx
inline void StringCchGets(LPSTR pszDest, size_t cchDest,
						  LPSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchGetsExA(pszDest, cchDest, ppszDestEnd, pcchRemaining, dwFlags)));
inline void StringCchGets(LPWSTR pszDest, size_t cchDest,
						  LPWSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCchGetsExW(pszDest, cchDest, ppszDestEnd, pcchRemaining, dwFlags)));
#undef StringCbGetsEx
// StringCbGetsEx
inline void StringCbGets(LPSTR pszDest, size_t cbDest,
						 LPSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbGetsExA(pszDest, cbDest, ppszDestEnd, pcbRemaining, dwFlags)));
inline void StringCbGets(LPWSTR pszDest, size_t cbDest,
						 LPWSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags)
	assertl_reflect_as(SUCCEEDED(::StringCbGetsExW(pszDest, cbDest, ppszDestEnd, pcbRemaining, dwFlags)));
#undef StringCchLength
// StringCchLength
inline void StringCchLength(LPCSTR psz, size_t cchMax, size_t *pcchLength)
	assertl_reflect_as(SUCCEEDED(::StringCchLengthA(psz, cchMax, pcchLength)));
inline void StringCchLength(LPCWSTR psz, size_t cchMax, size_t *pcchLength)
	assertl_reflect_as(SUCCEEDED(::StringCchLengthW(psz, cchMax, pcchLength)));
#undef StringCbLength
// StringCbLength
inline void StringCbLength(LPCSTR psz, size_t cbMax, size_t *pcbLength)
	assertl_reflect_as(SUCCEEDED(::StringCbLengthA(psz, cbMax, pcbLength)));
inline void StringCbLength(LPCWSTR psz, size_t cbMax, size_t *pcbLength)
	assertl_reflect_as(SUCCEEDED(::StringCbLengthW(psz, cbMax, pcbLength)));
#pragma endregion

#pragma region MaxLens 
export {
constexpr UINT MaxLenPath = MAX_PATH;
constexpr UINT MaxLenTitle = MaxLenPath * 3;
constexpr UINT MaxLenClass = 256;
constexpr UINT MaxLenNotice = 32767;
}
#pragma endregion

#pragma region Strings
export {
enum_class(CodePages, UINT,
	Active       = CP_ACP,
	OEM          = CP_OEMCP,
	Macintosh    = CP_MACCP,
	ThreadActive = CP_THREAD_ACP,
	Symbol       = CP_SYMBOL,
	UTF7         = CP_UTF7,
	UTF8         = CP_UTF8);
template<class CharType = TCHAR> const StringBase<CharType> CString(size_t uLen, const CharType *lpString);
template<class CharType = TCHAR> const StringBase<CharType> CString(const CharType *lpString, size_t maxLen);
template<class CharType>
inline size_t Length(const CharType *lpString, size_t MaxLen) {
	WX::StringCchLength(lpString, MaxLen, &MaxLen);
	return MaxLen;
}
template<class TCHAR>
class StringBase {
	locale_charmode(IsCharW<TCHAR>);
	using LPTSTR = TCHAR *;
	using LPCTSTR = const TCHAR *;
	enum StrFlags : size_t {
		STR_DEF = 0,
		STR_READONLY = 1,
		STR_MOVABLE = 2,
		STR_RELEASE = 4
	};
	mutable LPTSTR lpsz = O;
	mutable size_t Len : sizeof(void *) * 8 - 3;
	mutable size_t Flags : 3;
private:
	template<class _TCHAR> friend const StringBase<_TCHAR> CString(size_t uLen, const _TCHAR *lpString);
	template<class _TCHAR> friend const StringBase<_TCHAR> CString(const _TCHAR *lpString, size_t maxLen);
	StringBase(size_t len, UINT flags, LPTSTR lpBuffer) :
		lpsz(lpBuffer), Len((UINT)len), Flags(flags) {
		if (len <= 0 || !lpBuffer) {
			Len = 0;
			lpsz = O;
		}
	}
	StringBase(size_t len, LPCTSTR lpString) : StringBase(len, STR_READONLY, const_cast<LPTSTR>(lpString)) {}
public:
	StringBase() : Len(0), Flags(0) {}
	StringBase(Null) : Len(0), Flags(0) {}
	StringBase(const StringBase &) = delete;
	StringBase(StringBase &str) : StringBase(str.Len, str.Flags, str.lpsz) { str.Len = 0, str.Flags = STR_DEF, str.lpsz = 0; }
	StringBase(StringBase &&str) : StringBase(str.Len, str.Flags, str.lpsz) { str.Len = 0, str.Flags = STR_DEF, str.lpsz = 0; }
	explicit StringBase(size_t Len) : lpsz(Alloc(Len)), Len(Len), Flags(STR_MOVABLE | STR_RELEASE) {}
	StringBase(size_t Len, LPTSTR lpBuffer) : StringBase(Len, STR_MOVABLE | STR_RELEASE, lpBuffer) {}
	StringBase(TCHAR ch) : lpsz(Alloc(1)), Len(1), Flags(STR_MOVABLE | STR_RELEASE) reflect_to(lpsz[0] = ch);
	template<size_t len> StringBase(TCHAR(&str)[len]) : StringBase(len - 1, STR_DEF, str) {}
	template<size_t len> StringBase(const TCHAR(&str)[len]) : lpsz(const_cast<LPTSTR>(str)), Len(len - 1), Flags(STR_READONLY) {}
	~StringBase() { operator~(); }
public: // Memories Management
	static inline LPTSTR Realloc(size_t len, LPTSTR lpsz) {
		if (!lpsz && len <= 0) return O;
		if (len <= 0) {
			Free(lpsz);
			return O;
		}
		return (LPTSTR)realloc(lpsz, (len + 1) * sizeof(TCHAR));
	}
	static inline LPTSTR Alloc(size_t len) {
		if (len == 0) return O;
		auto nlen = (len + 1) * sizeof(TCHAR);
		auto lpsz = (LPTSTR)malloc(nlen);
		ZeroMemory(lpsz, nlen);
		return lpsz;
	}
	static inline void Free(void *lpsz) reflect_to(free(lpsz));
	static inline LPTSTR Resize(LPTSTR &lpsz, size_t len) reflect_as(lpsz = Realloc(len, lpsz));
public:
	inline void Trunc() {
		if (!(Flags & STR_MOVABLE))
			self = +self;
		Len = (UINT)WX::Length(lpsz, Len + 1);
		lpsz = Realloc(Len, lpsz);
	}
	inline void Resize(size_t NewLen) {
		if (!(Flags & STR_MOVABLE))
			self = +self;
		if (NewLen <= 0) return;
		auto OldLen = WX::Length(lpsz, Len + 1);
		Len = (UINT)NewLen;
		lpsz = Realloc(NewLen, lpsz);
		if (NewLen < OldLen)
			lpsz[OldLen] = 0;
	}
	inline void Copy(LPCTSTR lpSrc)
		reflect_as(WX::StringCchCopy(lpsz, Length(), lpSrc));
	inline void CopyTo(LPTSTR lpDst, size_t lenDst) const {
		if (!lpDst && lenDst) return;
		if (auto len = Length())
			WX::StringCchCopy(lpDst, lenDst, lpsz);
		else
			lpDst[0] = '\0';
	}
public:
	inline LPCTSTR c_str() const reflect_as(lpsz && Len ? lpsz : O);
	inline LPCTSTR c_str_safe() const {
		if (!Len || !lpsz) {
			if constexpr (IsUnicode)
				return L"";
			else
				return "";
		}
		return lpsz;
	}
public:
	inline size_t Length() const reflect_as(lpsz ? Len : 0);
	inline size_t Size() const reflect_as(lpsz ? (Len + 1) * sizeof(TCHAR) : 0);
public:
	inline operator bool() const reflect_as(lpsz &&Len);
	inline operator LPCTSTR () const reflect_as(Len ? lpsz : O);
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
		auto lpsz = StringBase::Alloc(Len);
		CopyMemory(lpsz, this->lpsz, (Len + 1) * sizeof(TCHAR));
		lpsz[Len] = '\0';
		return lpsz;
	}
	inline StringBase operator+() const {
		if (!lpsz || !Len) return O;
		auto lpsz = StringBase::Alloc(Len);
		CopyMemory(lpsz, this->lpsz, (Len + 1) * sizeof(TCHAR));
		lpsz[Len] = '\0';
		return { Len, lpsz };
	}
	inline StringBase operator-() const {
		size_t nLen = WX::Length(lpsz, Len + 1);
		if (nLen <= 0) return O;
		auto lpsz = StringBase::Alloc(nLen);
		CopyMemory(lpsz, this->lpsz, (nLen + 1) * sizeof(TCHAR));
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
	inline auto &operator+=(const StringBase &str) {
		if (!str.lpsz || !str.Len) retself;
		if (!lpsz || !Len) return self = +str;
		auto nLen = Len + str.Len;
		if (!(Flags & STR_MOVABLE) || (Flags & STR_READONLY)) {
			auto lpsz = StringBase::Alloc(Len);
			CopyMemory(lpsz, this->lpsz, (Len + 1) * sizeof(TCHAR));
			if (!(Flags & STR_RELEASE))
				Free(this->lpsz);
			this->lpsz = lpsz;
		}
		else lpsz = Realloc(nLen, lpsz);
		CopyMemory(lpsz + Len, str.lpsz, (str.Len + 1) * sizeof(TCHAR));
		Len = nLen;
		retself;
	}
	//inline StringBase operator+(const StringBase &str) && reflect_as(self += str);
	//inline StringBase operator+(const StringBase &str) & reflect_as(self + str);
	//inline StringBase operator+(const StringBase &str) const & {
	//	if (!str.lpsz || !str.Len) return *this;
	//	if (!lpsz || Len) return +str;
	//	auto nLen = Len + str.Len;
	//	auto lpsz = StringBase::Alloc(nLen);
	//	CopyMemory(lpsz, this->lpsz, Len * sizeof(TCHAR));
	//	CopyMemory(lpsz + Len, str.lpsz, (str.Len + 1) * sizeof(TCHAR));
	//	return{ nLen, lpsz };
	//}
public:
	inline LPTSTR begin() reflect_as(Len ? lpsz : O);
	inline LPTSTR end() reflect_as(Len &&lpsz ? lpsz + Len : O);
	inline LPCTSTR begin() const reflect_as(Len ? lpsz : O);
	inline LPCTSTR end() const reflect_as(Len &&lpsz ? lpsz + Len : O);
};
/* Literal operator of String  */
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
/* CString */
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
/* Fits */
inline StringA FitsA(const StringW &str, CodePages cp = CodePages::Active) {
	int tLen, uLen = (int)str.Length();
	LPCWSTR lpString = str;
	assertl((tLen = WideCharToMultiByte(cp.yield(), 0, lpString, (int)uLen, O, 0, O, O)) > 0);
	// if (tLen != uLen) warnning glyphs missing 
	auto lpsz = StringA::Alloc(tLen);
	assertl(tLen == WideCharToMultiByte(cp.yield(), 0, lpString, (int)uLen, lpsz, tLen, O, O));
	lpsz[tLen] = 0;
	return{ (size_t)tLen, lpsz };
}
inline StringW FitsW(const StringA &str, CodePages cp = CodePages::Active) {
	int tLen, uLen = (int)str.Length();
	LPCSTR lpString = str;
	assertl((tLen = MultiByteToWideChar(cp.yield(), 0, lpString, (int)uLen, O, 0)) > 0);
	// if (tLen != uLen) warnning glyphs missing 
	auto lpsz = StringW::Alloc(tLen);
	assertl(tLen == MultiByteToWideChar(cp.yield(), 0, lpString, (int)uLen, lpsz, tLen));
	lpsz[tLen] = 0;
	return{ (size_t)tLen, lpsz };
}
template<bool IsUnicode = WX::IsUnicode, class TCHAR = ::TCHAR>
inline auto Fits(StringBase<TCHAR> str) {
	if constexpr (std::is_same_v<XCHAR<IsUnicode>, TCHAR>)
		return str;
	elif constexpr (IsUnicode)
		return FitsW(str);
	else return FitsA(str);
}
template<class CharType>
inline String Fits(const CharType *lpString, size_t MaxLen, CodePages cp = CodePages::Active) {
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
		if constexpr (IsUnicode)
			assertl((tLen = MultiByteToWideChar(cp.yield(), 0, lpString, (int)uLen, O, 0)) > 0)
		else assertl((tLen = WideCharToMultiByte(cp.yield(), 0, lpString, (int)uLen, O, 0, O, O)) > 0)
			// if (tLen != uLen) warnning glyphs missing 
			auto lpsz = String::Alloc(tLen);
		if constexpr (IsUnicode)
			assertl(tLen == MultiByteToWideChar(cp.yield(), 0, lpString, (int)uLen, lpsz, tLen))
		else assertl(tLen == WideCharToMultiByte(cp.yield(), 0, lpString, (int)uLen, lpsz, tLen, O, O))
			lpsz[tLen] = 0;
		return{ (size_t)tLen, lpsz };
	}
}
/* Misc */
template<class TCHAR>
inline size_t CountAll(const StringBase<TCHAR> &src, const StringBase<TCHAR> &strTarget) {
	using LPCTSTR = const TCHAR *;
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
template<class TCHAR>
inline StringBase<TCHAR> ReplaceAll(const StringBase<TCHAR> &src,
									const StringBase<TCHAR> &strTarget,
									const StringBase<TCHAR> &strWith = O) {
	using LPCTSTR = const TCHAR *;
	auto count = CountAll(src, strTarget);
	if (count <= 0) return O;
	auto tLen = strTarget.Length();
	auto nLen = src.Length() + count * (strWith.Length() - strTarget.Length());
	auto lpDst = StringBase<TCHAR>::Alloc(nLen);
	for (LPCTSTR li = src, hi = src.end(); li < hi; ) {
		LPCTSTR lj = strTarget, hj = strTarget.end();
		for (; lj < hj; ++lj)
			if ((*lpDst++ = *li++) != *lj)
				break;
		if (lj < hj) continue;
		lpDst -= tLen;
		for (LPCTSTR lpwStr = strWith, lpwEnd = strWith.end(); lpwStr < lpwEnd; ++lpwStr)
			*lpDst++ = *lpwStr;
	}
	return{ nLen, lpDst };
}
template<class TCHAR>
inline size_t LengthOf(const StringBase<TCHAR> &str) reflect_as(str.Length());
template<class TCHAR, class... Args>
inline size_t LengthOf(const StringBase<TCHAR> &str, const Args&... args) reflect_as(str.Length() + (LengthOf((const StringBase<TCHAR> &)args) + ...));
template<class TCHAR>
inline TCHAR *Copies(TCHAR *lpBuffer) reflect_as(lpBuffer);
template<class TCHAR, class... Args>
inline TCHAR *Copies(TCHAR *lpBuffer, const StringBase<TCHAR> &str, const Args &... args) {
	auto uLen = str.Length();
	if (uLen > 0) CopyMemory(lpBuffer, str, uLen * sizeof(TCHAR));
	return Copies(lpBuffer + uLen, args...);
}
template<class TCHAR>
inline void Copy(StringBase<TCHAR> &str, const TCHAR *lpSrc)
	reflect_to(StringCchCopy(str, str.Length(), lpSrc));
template<class AnyType>
inline void Fill(AnyType *lpArray, const AnyType &Sample, size_t Len) {
	while (Len--)
		CopyMemory(lpArray++, &Sample, sizeof(AnyType));
}
/* format */
constexpr size_t Len_sprintf_buff = 1024;
template<class TCHAR = ::TCHAR>
inline StringBase<TCHAR> format(const TCHAR *lpFormat, va_list argList) {
	TCHAR buff[Len_sprintf_buff];
	size_t remain = 0;
	StringCchVPrintf(buff, Len_sprintf_buff, O, &remain, STRSAFE_NULL_ON_FAILURE, lpFormat, argList);
	return +CString(buff, Len_sprintf_buff - remain + 1);
}
template<class TCHAR = ::TCHAR>
inline StringBase<TCHAR> format(const TCHAR *lpFormat, ...) {
	va_list argList;
	va_start(argList, lpFormat);
	auto &&str = format(lpFormat, argList);
	va_end(argList);
	return str;
}
}
#pragma endregion

#pragma region FormatNumeral
export {
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
const CharType *fmt_push(fmt_word &fmt, const CharType *format) {
	auto ch = *format;
	if (ch == ' ') {
		fmt.right_dir = true;
		fmt.symbol = Symbol::Space;
		ch = *++format;
	}
	elif(ch == '*') {
		fmt.symbol = Symbol::Space;
		ch = *++format;
	}
	switch (ch) {
		case '+':
			fmt.symbol = Symbol::Pos;
			ch = *++format;
			break;
	}
	switch (ch) {
		case '0':
			fmt.int_blank = Align::Zero;
			fmt.int_align = true;
			ch = *++format;
			break;
		case ' ':
			fmt.int_blank = Align::Space;
			fmt.int_align = true;
			ch = *++format;
			break;
	}
	if (ch == '~') {
		fmt.int_trunc = true;
		ch = *++format;
	}
	auto align = 0;
	while ('0' <= ch && ch <= '9') {
		align *= 10;
		align += ch - '0';
		if (align > 32)
			return nullptr; // overflow
		ch = *++format;
	}
	fmt.int_calign = align;
	if (ch == '.') {
		fmt.float_force = true;
		ch = *++format;
	}
	elif(ch == '0') {
		fmt.float_blank = Align::Zero;
		fmt.float_align = true;
		ch = *++format;
	}
	align = 0;
	while ('0' <= ch && ch <= '9') {
		align *= 10;
		align += ch - '0';
		if (align > 32)
			return nullptr; // overflow
		ch = *++format;
	}
	fmt.float_calign = align;
	if (ch == ' ') {
		fmt.float_blank = Align::Space;
		fmt.float_align = true;
		ch = *++format;
	}
	switch (ch) {
		case 'q':
			fmt.radix_type = Rad::Qua;
			ch = *++format;
			break;
		case 'o':
			fmt.radix_type = Rad::Oct;
			ch = *++format;
			break;
		case 'd':
			fmt.radix_type = Rad::Dec;
			ch = *++format;
			break;
		case 'X':
			fmt.alfa_type = Cap::Big;
			[[fallthrough]];
		case 'x':
			fmt.radix_type = Rad::Hex;
			ch = *++format;
			break;
		default:
			return nullptr;
	}
	return format;
}
template<class CharType>
inline bool fmt_single(fmt_word &fmt, const CharType *format) {
	if (!format) return false;
	if (auto hpformat = fmt_push(fmt, format))
		return hpformat[0] == '\0';
	return true;
}
class format_numeral : public fmt_word {
public:
	format_numeral() : fmt_word{ 0 } {}
	format_numeral(fmt_word fmt) : fmt_word(fmt) {}
	format_numeral(const char *lpFormat) : fmt_word{ 0 } assertl(fmt_single(self, lpFormat));
	format_numeral(const wchar_t *lpFormat) : fmt_word{ 0 } assertl(fmt_single(self, lpFormat));
private:
	template<class TCHAR>
	static inline auto __push(uintptr_t ui, TCHAR *hpString, TCHAR alfa, uint8_t radix, uint8_t int_trunc) {
		uint8_t len = 0;
		do {
			auto d_sm = ui / radix;
			auto rbit = (TCHAR)(ui - d_sm * radix);
			ui = d_sm;
			*--hpString = rbit + (rbit < 10 ? '0' : alfa);
		} while (ui && ++len < int_trunc);
		return hpString;
	}
	template<class TCHAR>
	static inline auto __push(double pure_float, TCHAR *lpString, TCHAR alfa, uint8_t radix, uint8_t float_trunc) {
		uint8_t len = 0;
		while (pure_float > 0.f && len++ < float_trunc) {
			pure_float *= radix;
			auto rbit = (TCHAR)pure_float;
			pure_float -= rbit;
			*lpString++ = rbit + (rbit < 10 ? '0' : alfa);
		}
		return lpString;
	}
	template<class TCHAR>
	static inline auto __moveH2L(TCHAR *lpString, TCHAR *hpString, int uLength) {
		while (uLength--)
			*lpString++ = *hpString++;
		return lpString;
	}
private:
	inline uint8_t _radix() const reflect_as((uint8_t)radix_type == (uint8_t)Rad::Dec ? 10 : (2 << (uint8_t)radix_type));
	template<class TCHAR>
	inline TCHAR _alfa_char() const reflect_as(((uint8_t)alfa_type == (uint8_t)Cap::Big ? 'A' : 'a') - 10);
	template<class TCHAR>
	inline TCHAR _fill_int_char() const reflect_as((uint8_t)int_blank == (uint8_t)Align::Space ? ' ' : '0');
	template<class TCHAR>
	inline TCHAR _fill_float_char() const reflect_as((uint8_t)float_blank == (uint8_t)Align::Space ? ' ' : '0');
	template<class TCHAR>
	inline auto _push(uintptr_t uint_part, TCHAR *hpBuffer, uint8_t radix, TCHAR alfa, bool neg) const {
		auto lpBuffer = __push(uint_part, hpBuffer, alfa, radix, int_trunc ? int_calign : 32);
		auto int_len = hpBuffer - lpBuffer;
		if (int_len < int_calign && int_align) {
			auto fill = _fill_int_char<TCHAR>();
			while (int_len++ < int_calign)
				*--lpBuffer = fill;
		}
		if (neg)
			*--lpBuffer = '-';
		elif((uint8_t)symbol == (uint8_t)Symbol::Pos)
			*--lpBuffer = '+';
		elif((uint8_t)symbol == (uint8_t)Symbol::Space)
			*--lpBuffer = ' ';
		if (right_dir)
			while (int_len++ < int_calign)
				*--lpBuffer = ' ';
		return lpBuffer;
	}
	template<class TCHAR>
	inline auto _push(double float_part, TCHAR *lpBuffer, uint8_t radix, TCHAR alfa) const {
		auto hpBuffer = __push(
			float_part, lpBuffer + 1,
			alfa, radix, float_calign);
		auto float_len = hpBuffer - lpBuffer - 1;
		if (float_align) {
			auto fill = _fill_float_char<TCHAR>();
			while (float_len++ < int_calign)
				*hpBuffer++ = fill;
		}
		if (float_len > 0)
			*lpBuffer = '.';
		elif(float_force)
			*lpBuffer = '.';
		elif(float_align)
			*lpBuffer = ' ';
		else --hpBuffer;
		return hpBuffer;
	}
public:
	template<class TCHAR>
	inline auto push(uintptr_t uint_part, TCHAR *lpBuffer, TCHAR *&hpBuffer, size_t maxLength) const {
		hpBuffer = lpBuffer + maxLength - 2;
		lpBuffer = _push(uint_part, hpBuffer, _radix(), _alfa_char<TCHAR>(), false);
		return lpBuffer;
	}
	template<class TCHAR>
	inline auto push(intptr_t int_part, TCHAR *lpBuffer, TCHAR *&hpBuffer, size_t maxLength) const {
		bool neg = int_part < 0;
		if (neg) int_part = -int_part;
		hpBuffer = lpBuffer + maxLength - 2;
		lpBuffer = _push((uintptr_t)int_part, hpBuffer, _radix(), _alfa_char<TCHAR>(), neg);
		return lpBuffer;
	}
	template<class TCHAR>
	inline auto push(double float_part, TCHAR *lpBuffer, TCHAR *&hpBuffer, size_t maxLength) const {
		auto rad = _radix();
		auto alfa = _alfa_char<TCHAR>();
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
	template<class AnyType>
	inline String operator()(AnyType i) reflect_as(toString(i));
	static constexpr size_t maxLength = 64;
	template<class TCHAR = ::TCHAR, class AnyType>
	inline StringBase<TCHAR> toString(AnyType i) const {
		TCHAR lpBuffer[maxLength] = { 0 }, *hpString, *lpString;
		if constexpr (std::is_unsigned_v<AnyType>)
			lpString = push((uintptr_t)i, lpBuffer, hpString, maxLength);
		elif constexpr (std::is_integral_v<AnyType>)
			lpString = push((intptr_t)i, lpBuffer, hpString, maxLength);
		elif constexpr (std::is_floating_point_v<AnyType>)
			lpString = push(i, lpBuffer, hpString, maxLength);
		return +CString(hpString - lpString, lpString);
	}
	template<class AnyType>
	inline StringA toStringA(AnyType i) const reflect_as(toString<CHAR>(i));
	template<class AnyType>
	inline StringW toStringW(AnyType i) const reflect_as(toString<WCHAR>(i));
};
inline format_numeral operator ""_nx(const char *format, size_t n) reflect_as(format);
inline format_numeral operator ""_nx(const wchar_t *format, size_t n) reflect_as(format);
}
#pragma endregion

/* Rx::Token */
template<class TCHAR>
inline Rx<TCHAR>::Token::operator const StringBase<TCHAR>() const reflect_as(CString(len, lpsz));

#pragma region EnumParses
export {
template<class TCHAR, class AnyEnum>
StringBase<TCHAR> EnumClassParseX(AnyEnum e) {
	using EnumType = typename AnyEnum::EnumType;
	misuse_assert(IsEnum<EnumType>, "template type must be based on EnumBase");
	constexpr auto table = EnumTable<EnumType, TCHAR>;
	auto val = e.yield();
	for (auto i = 0; i < EnumType::Count; ++i)
		if (val == EnumType::__Vals[i])
			return table[i].key;
	if constexpr (EnumType::HasProtoEnum)
		return EnumClassParseX<TCHAR>(reuse_as<typename EnumType::ProtoEnum>(e));
	else return format_numeral("d").toString<TCHAR>(val);
}
template<class AnyEnum>
inline auto EnumClassParse(AnyEnum e) reflect_as(EnumClassParseX<TCHAR>(e));
template<class AnyEnum>
inline auto EnumClassParseA(AnyEnum e) reflect_as(EnumClassParseX<CHAR>(e));
template<class AnyEnum>
inline auto EnumClassParseW(AnyEnum e) reflect_as(EnumClassParseX<WCHAR>(e));
}
#pragma endregion

#pragma region Exception::
template<bool IsUnicode>
inline StringX<IsUnicode> Exception::File() const reflect_as(Fits(FileA()));
inline const StringA Exception::FileA() const reflect_as(CString(lpFile, 1024));
inline StringW Exception::FileW() const reflect_as(FitsW(FileA()));

template<bool IsUnicode>
inline StringX<IsUnicode> Exception::Function() const reflect_as(Fits(FunctionA()));
inline const StringA Exception::FunctionA() const reflect_as(CString(lpFunc, 1024));
inline StringW Exception::FunctionW() const reflect_as(FitsW(FunctionA()));

template<bool IsUnicode>
inline StringX<IsUnicode> Exception::Sentence() const reflect_as(Fits(SentenceA()));
inline const StringA Exception::SentenceA() const reflect_as(CString(lpSent, 1024));
inline StringW Exception::SentenceW() const reflect_as(FitsW(SentenceA()));

template<bool IsUnicode>
inline StringX<IsUnicode> Exception::ErrorMessage() const {
	if constexpr (IsUnicode)
		 reflect_as(ErrorMessageW())
	else reflect_as(ErrorMessageA());
}
inline StringA Exception::ErrorMessageA() const {
	if (!ErrorCode()) return O;
	LPSTR lpsz;
	auto len = ::FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		O, ErrorCode(), 0, (LPSTR)&lpsz, 0, O);
	auto &&msg = CString(lpsz, len);
	LocalFree(lpsz);
	return +msg;
}
inline StringW Exception::ErrorMessageW() const {
	if (!ErrorCode()) return O;
	LPWSTR lpsz;
	auto len = ::FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		O, ErrorCode(), 0, (LPWSTR)&lpsz, 0, O);
	auto &&msg = CString(lpsz, len);
	LocalFree(lpsz);
	return +msg;
}

template<bool IsUnicode>
inline StringX<IsUnicode> Exception::toString() const reflect_as(Fits(toStringA()));
inline StringA Exception::toStringA() const {
	auto &&str = format(
		"File:          %s\n"
		"Function:      %s\n"
		"Sentence:      %s\n"
		"Line:          %d\n",
		lpFile,
		lpFunc,
		lpSent,
		Line());
	if (!ErrorCode()) return str;
	str += format(
		"Error Code:    %d\n"
		"Error Message: %s\n",
		ErrorCode(),
		(LPCSTR)ErrorMessageA());
	return str;
}
inline StringW Exception::toStringW() const reflect_as(FitsW(StringA()));
inline Exception::operator StringA() const reflect_as(toStringA());
inline Exception::operator StringW() const reflect_as(toStringW());
#pragma endregion

#pragma region Cats
export {
template<class TCHAR>
inline StringBase<TCHAR> Concat() reflect_as(O);
template<class TCHAR, class... Args>
inline StringBase<TCHAR> Concat(const StringBase<TCHAR> &str, const Args &... args) {
	if (auto len = LengthOf(str, args...)) {
		auto lpsz = StringBase<TCHAR>::Alloc(len);
		*Copies(lpsz, str, args...) = 0;
		return{ len, lpsz };
	}
	return O;
}
template<class TCHAR, class AnyNumberal>
inline StringBase<TCHAR> X(const TCHAR *form, AnyNumberal i) {
	if constexpr (IsCharW<TCHAR>)
		 reflect_as(format_numeral(form).toStringW(i))
	else reflect_as(format_numeral(form).toStringA(i))
}
#pragma region CatsA
StringA StrTrueA = "true";
StringA StrFalseA = "false";
inline const StringA &CatsA(bool b) reflect_as(b ? StrTrueA : StrFalseA);
inline StringA CatsA(double f) reflect_as(X(".5d", f));
inline StringA CatsA(LONG i) reflect_as(X("d", i));
inline StringA CatsA(int32_t i) reflect_as(X("d", i));
inline StringA CatsA(int64_t i) reflect_as(X("d", i));
inline StringA CatsA(uint8_t i) reflect_as(X("d", i));
inline StringA CatsA(uint16_t i) reflect_as(X("d", i));
inline StringA CatsA(uint32_t i) reflect_as(X("d", i));
inline StringA CatsA(uint64_t i) reflect_as(X("d", i));
inline StringA CatsA(DWORD i) reflect_as(X("d", i));
inline StringA CatsA(CHAR chs) reflect_as((CHAR)chs);
inline StringA CatsA(WCHAR chs) reflect_as((CHAR)chs);
inline StringA CatsA(LPCSTR lpsz) reflect_as(+CString(lpsz, 0x1FF));
inline StringA CatsA(const Exception &err) reflect_as(err);
inline const StringA &CatsA(const StringA &str) reflect_as(str);
template<class AnyType>
inline StringA CatsA(const AnyType &tt) reflect_as((StringA)tt);
template<size_t len>
inline StringA CatsA(const CHAR(&Chars)[len]) reflect_as(Chars);
template<class... Args>
inline StringA CatsA(const Args& ...args) reflect_as(Concat(CatsA(args)...));
#pragma endregion
#pragma region CatsW
StringW StrTrueW = L"true";
StringW StrFalseW = L"false";
inline const StringW &CatsW(bool b) reflect_as(b ? StrTrueW : StrFalseW);
inline StringW CatsW(double f) reflect_as(X(L".5d", f));
inline StringW CatsW(LONG i) reflect_as(X(L"d", i));
inline StringW CatsW(int32_t i) reflect_as(X(L"d", i));
inline StringW CatsW(int64_t i) reflect_as(X(L"d", i));
inline StringW CatsW(uint8_t i) reflect_as(X(L"d", i));
inline StringW CatsW(uint16_t i) reflect_as(X(L"d", i));
inline StringW CatsW(uint32_t i) reflect_as(X(L"d", i));
inline StringW CatsW(uint64_t i) reflect_as(X(L"d", i));
inline StringW CatsW(DWORD i) reflect_as(X(L"d", i));
inline StringW CatsW(CHAR chs) reflect_as((WCHAR)chs);
inline StringW CatsW(WCHAR chs) reflect_as((WCHAR)chs);
inline StringW CatsW(LPCWSTR lpsz) reflect_as(+CString(lpsz, 1024));
inline StringW CatsW(const Exception &err) reflect_as(err);
inline const StringW &CatsW(const StringW &str) reflect_as(str);
template<class AnyType>
inline StringW CatsW(const AnyType &tt) reflect_as((StringW)tt);
template<size_t len>
inline StringW CatsW(const WCHAR(&Chars)[len]) reflect_as(Chars);
template<class... Args>
inline StringW CatsW(const Args& ...args) reflect_as(Concat(CatsW(args)...));
#pragma endregion
#pragma region Cats
inline auto &Cats(bool b) reflect_as(AnyX<IsUnicode>(CatsA(b), CatsW(b)));
inline String Cats(double f) reflect_as(X(T(".5d"), f));
inline String Cats(LONG i) reflect_as(X(T("d"), i));
inline String Cats(int32_t i) reflect_as(X(T("d"), i));
inline String Cats(int64_t i) reflect_as(X(T("d"), i));
inline String Cats(uint8_t i) reflect_as(X(T("d"), i));
inline String Cats(uint16_t i) reflect_as(X(T("d"), i));
inline String Cats(uint32_t i) reflect_as(X(T("d"), i));
inline String Cats(uint64_t i) reflect_as(X(T("d"), i));
inline String Cats(DWORD i) reflect_as(X(T("d"), i));
inline String Cats(CHAR chs) reflect_as((TCHAR)chs);
inline String Cats(WCHAR chs) reflect_as((TCHAR)chs);
inline String Cats(LPCTSTR lpsz) reflect_as(+CString(lpsz, 1024));
inline String Cats(const Exception &err) reflect_as(err);
inline const String &Cats(const String &str) reflect_as(str);
template<class AnyType>
inline String Cats(const AnyType &tt) reflect_as((String)tt);
template<size_t len>
inline String Cats(const TCHAR(&Chars)[len]) reflect_as(Chars);
template<class... Args>
inline String Cats(const Args& ...args) reflect_as(Concat(Cats(args)...));
#pragma endregion
}
#pragma endregion

}
