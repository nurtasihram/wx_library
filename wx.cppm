module;

#define WX_CPPM_CORE
#include "wx"

export module wx;

export namespace WX {

constexpr bool IsUnicode =
#if defined(UNICODE)
	UNICODE;
#elif defined(_UNICODE)
	_UNICODE;
#else
	false;
#endif

template<class Type1, class Type2> constexpr bool IsSame = false;
template<class AnyType>	constexpr bool IsSame<AnyType, AnyType> = true;
template<class Type1, class Type2> constexpr bool IsNotSame = !IsSame<Type1, Type2>;
template<class Type1, class Type2> concept SameAs = IsSame<Type1, Type2>;
template<class Type1, class Type2> concept NotSameType = IsNotSame<Type1, Type2>;

template<bool Condition, class TrueType, class FalseType> struct ConditionType;
template<class TrueType, class FalseType> struct ConditionType<true, TrueType, FalseType> { using type = TrueType; };
template<class TrueType, class FalseType> struct ConditionType<false, TrueType, FalseType> { using type = FalseType; };
template<bool Condition, class TrueType, class FalseType> using ConditionOf = typename ConditionType<Condition, TrueType, FalseType>::type;

template<class Type1, class Type2>
constexpr bool IsSameType(Type1, Type2) reflect_as(IsSame<Type1, Type2>);

template<class AnyType>
concept IntagerType = // IsSame<int8_t, AnyType> ||		// may duplicated with char
					  // IsSame<int16_t, AnyType> ||	// may duplicated with wchar_t
					IsSame<int32_t, AnyType> ||
					IsSame<int64_t, AnyType> ||
					IsSame<uint8_t, AnyType> ||
					IsSame<uint16_t, AnyType> ||
					IsSame<uint32_t, AnyType> ||
					IsSame<uint64_t, AnyType>;
template<class AnyType>
concept FloatType = // IsSame<long double, AnyType> ||	// Unsupport by some compilers
					IsSame<float, AnyType> ||
				    IsSame<double, AnyType>;
template<class AnyType>
concept NumberType = IntagerType<AnyType> || FloatType<AnyType>;

template<class Type1, class Type2>
concept IsSameSizeType = sizeof(Type1) == sizeof(Type2);

template<class AnyType> constexpr size_t SizeOf = sizeof(AnyType);
template<> constexpr size_t SizeOf<void> = 0;

template<class AnyType> constexpr bool IsVoid = false
template<> constexpr bool IsVoid<void> = true;
template<class AnyType> constexpr bool NotVoid = !IsVoid<AnyType>;
template<class AnyType> concept VoidType = IsVoid<AnyType>;
template<class AnyType> concept NotVoidType = NotVoid<AnyType>;

#pragma region Type Reference Helpers

template<class OutType>
inline OutType &ref_as(IsSameSizeType<OutType> auto &in) reflect_as(*(OutType *)&in);
template<class OutType>
inline OutType reuse_as(IsSameSizeType<OutType> auto in) reflect_as(*(OutType *)&in);
template<class OutType, class InType>
	requires(sizeof(OutType) >= sizeof(InType))
inline OutType small_cast(InType in) reflect_as(*(OutType *)&in);
template<class OutType, class InType>
	requires(sizeof(OutType) <= sizeof(InType))
inline OutType big_cast(InType in) reflect_as(*(OutType *)&in);

/* --- Hand --- */
template<class AnyType>
struct Hand {
	using left = AnyType &;
	using right = AnyType &&;
	using base = AnyType;
	using clap = AnyType &&;
	static constexpr bool is_left = false;
	static constexpr bool is_right = false;
};
// Left Hand
template<class AnyType>
struct Hand<AnyType &> {
	using left = AnyType &;
	using right = AnyType &&;
	using base = AnyType;
	using clap = AnyType &;
	static constexpr bool is_left = true;
	static constexpr bool is_right = false;
};
template<class AnyType>
inline AnyType &&to_right_hand(AnyType &a) reflect_as(static_cast<AnyType &&>(a));
template<class AnyType>
inline AnyType &to_left_hand(AnyType &a) reflect_as(a);
// Right Hand
template<class AnyType>
struct Hand<AnyType &&> {
	using left = AnyType &;
	using right = AnyType &&;
	using base = AnyType;
	using clap = AnyType &&;
	static constexpr bool is_left = false;
	static constexpr bool is_right = true;
};
template<class AnyType>
inline AnyType &&to_right_hand(AnyType &&a) reflect_as(static_cast<AnyType &&>(a));
template<class AnyType>
inline AnyType &to_left_hand(AnyType &&a) reflect_as(a);
// Clap Hand
template<class AnyStrict, class AnyType>
	requires(IsSame<typename Hand<AnyStrict>::base, AnyType>)
inline auto clap_hand(AnyType &a) -> Hand<AnyStrict>::clap reflect_as(static_cast<typename Hand<AnyStrict>::clap>(a));

#pragma endregion

#pragma region Prototypes Type Traits & Helpers System
enum class TypeMod {
	None = 0,
	Left = 1 << 0,
	Right = 1 << 1,
	Const = 1 << 2,
	Volatile = 1 << 3,
	Pointer = 1 << 4,
	ArrayVariadic = 1 << 5,
	ArrayFixed = 1 << 6,
	MemberPointer = 1 << 7,
	FuntionProto = 1 << 8,
	FuntionVariadicProto = 1 << 9,
};

/* Type filters */
template<class AnyType>	constexpr bool IsLeft = false;
template<class AnyType>	constexpr bool IsRight = false;
template<class AnyType>	constexpr bool IsConst = false;
template<class AnyType>	constexpr bool IsVolatile = false;
template<class AnyType>	constexpr bool IsPointer = false;
template<class AnyType>	constexpr bool IsArrayVariadic = false;
template<class AnyType> constexpr bool IsArrayFixed = false;
template<class AnyType> constexpr bool IsMemberPointer = false;
template<class AnyType> constexpr bool IsFuntionProto = false;
template<class AnyType> constexpr bool IsFuntionVariadicProto = false;
template<class AnyType>	constexpr bool IsLeft<AnyType &> = true;
template<class AnyType>	constexpr bool IsRight<AnyType &&> = true;
template<class AnyType>	constexpr bool IsConst<const AnyType> = true;
template<class AnyType>	constexpr bool IsVolatile<volatile AnyType> = true;
template<class AnyType>	constexpr bool IsPointer<AnyType *> = true;
template<class AnyType>	constexpr bool IsArrayVariadic<AnyType []> = true;
template<class AnyType, size_t Len> constexpr bool IsArrayFixed<AnyType [Len]> = true;
template<class AnyType, size_t Len> constexpr bool IsArrayFixed<AnyType (&)[Len]> = true;
template<class AnyType, size_t Len> constexpr bool IsArrayFixed<AnyType (&&)[Len]> = true;
template<class AnyType, class Onwer> constexpr bool IsMemberPointer<AnyType Onwer:: *> = true;
template<class AnyRet, class...Args> constexpr bool IsFuntionProto<AnyRet(Args...)> = true;
template<class AnyRet, class...Args> constexpr bool IsFuntionVariadicProto<AnyRet(Args..., ...)> = true;
/** concepts **/
template<class AnyType>	concept LeftType = IsLeft<AnyType>;
template<class AnyType>	concept RightType = IsRight<AnyType>;
template<class AnyType>	concept ConstType = IsConst<AnyType>;
template<class AnyType>	concept VolatileType = IsVolatile<AnyType>;
template<class AnyType>	concept PointerType = IsPointer<AnyType>;
template<class AnyType>	concept ArrayVariadicType = IsArrayVariadic<AnyType>;
template<class AnyType> concept ArrayFixedType = IsArrayFixed<AnyType>;
template<class AnyType> concept MemberPointerType = IsMemberPointer<AnyType>;
template<class AnyType> concept FuntionProtoType = IsFuntionProto<AnyType>;
template<class AnyType> concept FuntionVariadicProtoType = IsFuntionVariadicProto<AnyType>;
// Negative concepts
template<class AnyType>	concept NotLeftType = !IsLeft<AnyType>;
template<class AnyType>	concept NotRightType = !IsRight<AnyType>;
template<class AnyType>	concept NotConstType = !IsConst<AnyType>;
template<class AnyType>	concept NotVolatileType = !IsVolatile<AnyType>;
template<class AnyType>	concept NotPointerType = !IsPointer<AnyType>;
template<class AnyType>	concept NotArrayVariadicType = !IsArrayVariadic<AnyType>;
template<class AnyType> concept NotArrayFixedType = !IsArrayFixed<AnyType>;
template<class AnyType> concept NotMemberPointerType = !IsMemberPointer<AnyType>;
template<class AnyType> concept NotFuntionProtoType = !IsFuntionProto<AnyType>;
template<class AnyType> concept NotFuntionVariadicProtoType = !IsFuntionVariadicProto<AnyType>;
/** functions **/
constexpr bool IsVolatileType(auto) reflect_as(false);
constexpr bool IsPointerType(auto) reflect_as(false);
constexpr bool IsMemberPointerType(auto) reflect_as(false);
constexpr bool IsFuntionProtoType(auto) reflect_as(false);
constexpr bool IsFuntionVariadicProtoType(auto) reflect_as(false);
constexpr bool IsVolatileType(VolatileType auto) reflect_as(true);
constexpr bool IsPointerType(PointerType auto) reflect_as(true);
constexpr bool IsMemberPointerType(MemberPointerType auto) reflect_as(true);
constexpr bool IsFuntionProtoType(FuntionProtoType auto) reflect_as(true);
constexpr bool IsFuntionVariadicProtoType(FuntionVariadicProtoType auto) reflect_as(true);
/*** typical mixed type checks ***/
template<class AnyType> constexpr bool IsHand = IsLeft<AnyType> || IsRight<AnyType>;
template<class AnyType>	constexpr bool IsArray = IsArrayVariadic<AnyType> || IsArrayFixed<AnyType>;
template<class AnyType>	constexpr bool IsFunctionAllProto = IsFuntionProto<AnyType> || IsFuntionVariadicProto<AnyType>;
/**** concepts ****/
template<class AnyType> concept HandType = IsHand<AnyType>;
template<class AnyType> concept ArrayType = IsArray<AnyType>;
template<class AnyType> concept FunctionAllProtoType = IsFunctionAllProto<AnyType>;
/**** constexpr funcs ****/
constexpr bool IsFunctionAllProtoType(auto) reflect_as(false);
constexpr bool IsFunctionAllProtoType(FunctionAllProtoType auto) reflect_as(true);
/* Prototype Traits */
template<class AnyType> struct ProtoNodeOf { using proto = AnyType; };
template<class LastType, class NextType, TypeMod mod> requires(IsNotSame<LastType, NextType>)
struct TypeShim : ProtoNodeOf<LastType> {
	using remove = LastType;
	using type = NextType;
	static constexpr TypeMod modification = mod;
};
template<class AnyRet, class...Args> struct ProtoNodeOf<AnyRet(Args...)> {
	using proto = AnyRet(Args...);
	using return_type = AnyRet;
	template<template<class...> class AnyList>
	using listof_args = AnyList<Args...>;
	static constexpr auto countof_args = sizeof...(Args);
	static constexpr TypeMod modification = TypeMod::FuntionProto;
};
template<class AnyRet, class...Args> struct ProtoNodeOf<AnyRet(Args..., ...)>  {
	using proto = AnyRet(Args..., ...);
	using return_type = AnyRet;
	template<template<class...> class AnyList>
	using listof_args = AnyList<Args...>;
	static constexpr bool countof_args = sizeof...(Args);
	static constexpr TypeMod modification = TypeMod::FuntionVariadicProto;
};
template<class AnyType> using ProtoOf = typename ProtoNodeOf<AnyType>::proto;
template<class AnyType>	using RemoveModOf = typename ProtoNodeOf<AnyType>::remove;
template<class AnyType> constexpr bool IsProto = IsSame<AnyType, ProtoOf<AnyType>>;
template<class AnyType> constexpr auto ModOf = ProtoNodeOf<AnyType>::modification;
/** Prototype Shims **/
template<class AnyType>	struct LeftShim : TypeShim<AnyType, AnyType &, TypeMod::Left> {};
template<class AnyType>	struct RightShim : TypeShim<AnyType, AnyType &&, TypeMod::Right> {};
template<class AnyType>	struct ConstShim : TypeShim<AnyType, const AnyType, TypeMod::Const> {};
template<class AnyType>	struct VolatileShim : TypeShim<AnyType, volatile AnyType, TypeMod::Volatile> {};
template<class AnyType>	struct PointerShim : TypeShim<AnyType, AnyType *, TypeMod::Pointer> {};
template<class AnyType, size_t Len = 0> struct ArrayShim : TypeShim<AnyType, AnyType [Len], TypeMod::ArrayFixed> {};
template<class AnyType> struct ArrayShim<AnyType, 0> : TypeShim<AnyType, AnyType [], TypeMod::ArrayVariadic> {};
template<class AnyType, class Onwer> struct MemberPointerShim : TypeShim<AnyType, AnyType Onwer:: *, TypeMod::MemberPointer> {}; ///////
/** Prototype Nodes **/
template<class AnyType>	struct ProtoNodeOf<AnyType &> : LeftShim<AnyType> {};
template<class AnyType>	struct ProtoNodeOf<AnyType &&> : RightShim<AnyType> {};
template<class AnyType>	struct ProtoNodeOf<const AnyType> : ConstShim<AnyType> {};
template<class AnyType>	struct ProtoNodeOf<volatile AnyType> : VolatileShim<AnyType> {};
template<class AnyType>	struct ProtoNodeOf<AnyType *> : PointerShim<AnyType> {};
template<class AnyType, class Owner> struct ProtoNodeOf<AnyType Owner:: *> : MemberPointerShim<AnyType, Owner> { using owner = Owner; };
template<class AnyType>	struct ProtoNodeOf<AnyType []> : ArrayShim<AnyType> { static constexpr auto length = 0; };
template<class AnyType, size_t Len> struct ProtoNodeOf<AnyType [Len]> : ArrayShim<AnyType, Len> { static constexpr auto length = Len; };
template<class AnyType, size_t Len> struct ProtoNodeOf<AnyType (&)[Len]> : LeftShim<AnyType [Len]> {};
template<class AnyType, size_t Len> struct ProtoNodeOf<AnyType (&&)[Len]> : RightShim<AnyType [Len]> {};
template<class AnyType, size_t Len> struct ProtoNodeOf<const AnyType [Len]> : ConstShim<AnyType [Len]> {};
template<class AnyType, size_t Len> struct ProtoNodeOf<volatile AnyType [Len]> : VolatileShim<AnyType [Len]> {};
/** add modifications **/
template<class AnyType> using LeftOf = typename LeftShim<AnyType>::type;
template<class AnyType> using RightOf = typename RightShim<AnyType>::type;
template<class AnyType> using ConstOf = typename ConstShim<AnyType>::type;
template<class AnyType> using VolatileOf = typename VolatileShim<AnyType>::type;
template<class AnyType> using PointerOf = typename PointerShim<AnyType>::type;
template<class AnyType> using ArrayVariadicOf = typename ArrayShim<AnyType>::type;
template<class AnyType, size_t Len = 0> using ArrayOf = typename ArrayShim<AnyType, Len>::type;
template<class AnyType, class Onwer> using MemberPointerOf = typename MemberPointerShim<AnyType, Onwer>::type;
/** remove modifications **/
template<LeftType AnyLeft> using RemoveLeftOf = RemoveModOf<AnyLeft>;
template<RightType AnyRight> using RemoveRightOf = RemoveModOf<AnyRight>;
template<ConstType AnyConst> using RemoveConstOf = RemoveModOf<AnyConst>;
template<VolatileType AnyVolatile> using RemoveVolatileOf = RemoveModOf<AnyVolatile>;
template<PointerType AnyPointer> using RemovePointerOf = RemoveModOf<AnyPointer>;
template<ArrayType AnyArray> using RemoveArrayOf = RemoveModOf<AnyArray>;
template<MemberPointerType AnyMemberPointer> using MemberTypeOf = RemoveModOf<AnyMemberPointer>;
template<MemberPointerType AnyMemberPointer> using OwnerTypeOf = typename ProtoNodeOf<AnyMemberPointer>::owner;
/** conditional modifications **/
template<bool UseShim, template<class> class ShimType, class AnyType> struct CondShim;
template<template<class> class ShimType, class AnyType> struct CondShim<true, ShimType, AnyType> { using type = typename ShimType<AnyType>::type; };
template<template<class> class ShimType, class AnyType> struct CondShim<false, ShimType, AnyType> { using type = AnyType; };
template<bool UseShim, template<class> class ShimType, class AnyType> using CondShimFor = typename CondShim<UseShim, ShimType, AnyType>::type;
template<class AnyType> using LeftFor = CondShimFor<!IsLeft<AnyType>, LeftShim, AnyType>;
template<class AnyType> using RightFor = CondShimFor<!IsRight<AnyType>, RightShim, AnyType>;
template<class AnyType> using ConstFor = CondShimFor<!IsConst<AnyType>, ConstShim, AnyType>;
template<class AnyType> using VolatileFor = CondShimFor<!IsVolatile<AnyType>, VolatileShim, AnyType>;
template<class AnyType> using PointerFor = CondShimFor<!IsPointer<AnyType>, PointerShim, AnyType>;
// array
template<bool UseShim, class AnyType, size_t Len> struct CondArrayShim;
template<class AnyType, size_t Len> struct CondArrayShim<true, AnyType, Len> { using type = typename ArrayShim<AnyType, Len>::type; };
template<class AnyType, size_t Len> struct CondArrayShim<false, AnyType, Len> { using type = AnyType; };
template<bool UseShim, class AnyType, size_t Len> using CondArrayShimFor = typename CondArrayShim<UseShim, AnyType, Len>::type;
template<ArrayType AnyArray, size_t Len> using LengthForArray = ArrayOf<RemoveModOf<AnyArray>, Len>;
template<ArrayType AnyArray> using ArrayForVariadic = ArrayOf<RemoveModOf<AnyArray>>;
template<class AnyType, size_t Len = 0> using ArrayFor = CondArrayShimFor<!IsArray<AnyType>, AnyType, Len>;
/* functional */
template<class AnyType> constexpr bool IsFunction = IsFuntionProto<ProtoOf<AnyType>>;
template<class AnyType> constexpr bool IsFunctionVariadic = IsFuntionVariadicProto<ProtoOf<AnyType>>;
template<class AnyType> constexpr bool IsFunctionAll = IsFunctionAllProto<ProtoOf<AnyType>>;
template<class AnyType> constexpr bool IsMethod = IsMemberPointer<AnyType> && IsFunction<AnyType>;
template<class AnyType> constexpr bool IsMethodVariadic = IsMemberPointer<AnyType> && IsFunctionVariadic<AnyType>;
template<class AnyType> constexpr bool IsMethodAll = IsMemberPointer<AnyType> && IsFunctionAll<AnyType>;
template<class AnyType> constexpr bool IsStaticFunction = IsFunction<AnyType> && !IsMemberPointer<AnyType>;
template<class AnyType> constexpr bool IsStaticFunctionVariadic = IsFunctionVariadic<AnyType> && !IsMemberPointer<AnyType>;
template<class AnyType> constexpr bool IsStaticFunctionAll = IsFunctionAll<AnyType> && !IsMemberPointer<AnyType>;
/** concepts **/
template<class AnyType> concept FunctionType = IsFunction<AnyType>;
template<class AnyType> concept FunctionVariadicType = IsFunctionVariadic<AnyType>;
template<class AnyType> concept FunctionAllType = IsFunctionAll<AnyType>;
template<class AnyType> concept MethodType = IsMethod<AnyType>;
template<class AnyType> concept MethodVariadicType = IsMethodVariadic<AnyType>;
template<class AnyType> concept MethodAllType = IsMethodAll<AnyType>;
template<class AnyType> concept StaticFunctionType = IsStaticFunction<AnyType>;
template<class AnyType> concept StaticFunctionVariadicType = IsStaticFunctionVariadic<AnyType>;
template<class AnyType> concept StaticFunctionAllType = IsStaticFunctionAll<AnyType>;
/** constexpr funcs **/
constexpr bool IsFunctionType(auto) reflect_as(false);
constexpr bool IsFunctionVariadicType(auto) reflect_as(false);
constexpr bool IsFunctionAllType(auto) reflect_as(false);
constexpr bool IsMethodType(auto) reflect_as(false);
constexpr bool IsMethodVariadicType(auto) reflect_as(false);
constexpr bool IsMethodAllType(auto) reflect_as(false);
constexpr bool IsStaticFunctionType(auto) reflect_as(false);
constexpr bool IsStaticFunctionVariadicType(auto) reflect_as(false);
constexpr bool IsStaticFunctionAllType(auto) reflect_as(false);
constexpr bool IsFunctionType(FunctionType auto) reflect_as(true);
constexpr bool IsFunctionVariadicType(FunctionVariadicType auto) reflect_as(true);
constexpr bool IsFunctionAllType(FunctionAllType auto) reflect_as(true);
constexpr bool IsMethodType(MethodType auto) reflect_as(true);
constexpr bool IsMethodVariadicType(MethodVariadicType auto) reflect_as(true);
constexpr bool IsMethodAllType(MethodAllType auto) reflect_as(true);
constexpr bool IsStaticFunctionType(StaticFunctionType auto) reflect_as(true);
constexpr bool IsStaticFunctionVariadicType(StaticFunctionVariadicType auto) reflect_as(true);
constexpr bool IsStaticFunctionAllType(StaticFunctionAllType auto) reflect_as(true);
/* others */
template<ArrayType AnyArray> constexpr size_t CountOfArray = ProtoNodeOf<AnyArray>::length;
template<FunctionAllType AnyFunc> constexpr size_t CountOfArgs = ProtoNodeOf<AnyFunc>::countof_args;

constexpr size_t ArrayCountOf(ArrayType auto &a) reflect_as(CountOfArray<decltype(a)>);
constexpr size_t ArgsCountOf(FunctionAllType auto f) reflect_as(CountOfArgs<decltype(f)>);

template<FunctionAllType AnyFunc>
using ReturnTypeOf = typename ProtoNodeOf<AnyFunc>::return_type;
template<FunctionAllType AnyFunc, template<class...> class AnyList>
using ListArgsOf = typename ProtoNodeOf<AnyFunc>::template listof_args<AnyList>;
#pragma endregion

#pragma region Any Functional Compatible test
template<class AnyCallable, class Ret, class... Args>
concept StaticCompatible = requires(AnyCallable f, Args... args) { { f(args...) } -> std::convertible_to<Ret>; };
template<class AnyCallable, class FuncType>
constexpr bool static_compatible = false;
template<class AnyCallable, class Ret, class... Args>
constexpr bool static_compatible<AnyCallable, Ret(Args...)> = StaticCompatible<AnyCallable, Ret, Args...>;
#pragma endregion

#pragma region DConstructor Compatible test
/* --- Single Constructor --- */
template<class AnyType, class... Args>
struct ConstructorOf {
	static constexpr bool as_new = requires(Args... args) { new AnyType(args...); };
	static constexpr bool as_placement = requires(Args... args) { new(std::declval<void *>()) AnyType(args...); };
	static constexpr bool as_static = requires(Args... args) { AnyType(args...); };
	static constexpr bool any_ways = as_new || as_placement || as_static;
};
template<class AnyType>
struct ConstructorOf<AnyType, void> : ConstructorOf<AnyType> {};
/* --- Multi-Constructors --- */
template<class AnyType, class... ArgsLists>
struct ConstructorsOf;
template<class AnyType>
struct ConstructorsOf<AnyType> : ConstructorOf<AnyType> {};
template<class AnyType, class OtherType>
struct ConstructorsOf<AnyType, OtherType> : ConstructorOf<AnyType, OtherType> {};
template<class AnyType, template<class...> class AnyList, class... Args>
struct ConstructorsOf<AnyType, AnyList<Args...>> {};
template<class AnyType, class OtherType, class... Others>
struct ConstructorsOf<AnyType, OtherType, Others...> : ConstructorsOf<AnyType, ConstructorsOf<OtherType>, Others...> {};
template<class AnyType, template<class...> class AnyList, class... Args, class... Others>
struct ConstructorsOf<AnyType, AnyList<Args...>, Others...> {
	static constexpr bool as_new = ConstructorOf<AnyType, Args...>::as_new && ConstructorsOf<AnyType, Others...>::as_new;
	static constexpr bool as_placement = ConstructorOf<AnyType, Args...>::as_placement && ConstructorsOf<AnyType, Others...>::as_placement;
	static constexpr bool as_static = ConstructorOf<AnyType, Args...>::as_static && ConstructorsOf<AnyType, Others...>::as_static;
	static constexpr bool any_ways = ConstructorOf<AnyType, Args...>::any_ways && ConstructorsOf<AnyType, Others...>::any_ways;
};
/* --- Single Constructor Assertions --- */
template<class AnyType, class... Args>
concept ConstructorNewAssert = ConstructorOf<AnyType, Args...>::as_new;
template<class AnyType, class... Args>
concept ConstructorPlacementAssert = ConstructorOf<AnyType, Args...>::as_placement;
template<class AnyType, class... Args>
concept ConstructorStaticAssert = ConstructorOf<AnyType, Args...>::as_static;
template<class AnyType, class... Args>
concept ConstructorAssert = ConstructorOf<AnyType, Args...>::any_ways;
/* --- Multi Constructors - Assertions --- */
template<class AnyType, class... Args>
concept ConstructorsNewAssert = ConstructorsOf<AnyType, Args...>::as_new;
template<class AnyType, class... Args>
concept ConstructorsPlacementAssert = ConstructorsOf<AnyType, Args...>::as_placement;
template<class AnyType, class... Args>
concept ConstructorsStaticAssert = ConstructorsOf<AnyType, Args...>::as_static;
template<class AnyType, class... Args>
concept ConstructorsAssert = ConstructorsOf<AnyType, Args...>::any_ways;
/* --- Destructor --- */
template<class AnyType>
concept DestructorEffectless =
	std::is_pointer_v<AnyType> ||
	std::is_reference_v<AnyType> ||
	std::is_trivially_destructible_v<AnyType>;
template<class AnyType>
concept DestructorEffective = !DestructorEffectless<AnyType>;
#pragma endregion

#pragma region Arguments List
template<class...>
class ArgsList;
// No Argument
template<>
class ArgsList<void> {
public:
	static constexpr size_t Count = 0;
public:
	template<class AnyCallable>
	inline auto invoke(AnyCallable f) reflect_as(f());
	template<class AnyClass, class AnyMethod>
	inline auto invoke(AnyClass &cls, AnyMethod method) reflect_as((cls.*method)());
public:
	template<class AnyClass>
	inline auto constructor() reflect_as(AnyClass());
	template<class AnyClass>
	inline auto new_constructor() reflect_as(new AnyClass());
};
template<>
class ArgsList<> : ArgsList<void> {}; // Must have this alias specialization for some C/C++ exchange support
// Single Argument
template<class Type0>
class ArgsList<Type0> {
	using Hand0 = Hand<Type0>;
	using Left0 = typename Hand0::left;
	using Right0 = typename Hand0::right;
	using Clap0 = typename Hand0::clap;
	Clap0 arg0;
public:
	ArgsList(Type0 arg0) : arg0(clap_hand<Type0>(arg0)) {}
public:
	static constexpr size_t Count = 1;
public:
	template<size_t ind> requires(ind == 0)
	using type = Type0;	 
public:
	template<size_t ind> requires(ind == 0)
	inline Left0 value_left() reflect_as(arg0);
	template<size_t ind> requires(ind == 0)
	inline const Left0 value_left() const reflect_as(arg0);
	template<size_t ind> requires(ind == 0)
	inline Right0 value_right() reflect_as(static_cast<Right0>(arg0));
	template<size_t ind> requires(ind == 0)
	inline const Right0 value_right() const reflect_as(static_cast<const Right0>(arg0));
	template<size_t ind> requires(ind == 0)
	inline Clap0 value() reflect_as(static_cast<Clap0>(arg0));
	template<size_t ind> requires(ind == 0)
	inline const Clap0 value() const reflect_as(static_cast<const Clap0>(arg0));
public:
	template<class AnyCallable>
	inline auto invoke(AnyCallable f) reflect_as(f(value()));
	template<class AnyClass, class AnyMethod>
	inline auto invoke(AnyClass &cls, AnyMethod method) reflect_as((cls.*method)(value()));
public:
	template<class AnyClass>
	inline auto constructor() reflect_as(AnyClass(value()));
	template<class AnyClass>
	inline auto new_constructor() reflect_as(new AnyClass(value()));
};
// Multiple Arguments
template<class Type0, class...Types>
	requires(!std::is_void_v<Type0> && ... && !std::is_void_v<Types>)
class ArgsList<Type0, Types...> {
	using Hand0 = Hand<Type0>;
	using Left0 = typename Hand0::left;
	using Right0 = typename Hand0::right;
	using Clap0 = typename Hand0::clap;
	using TypeN = ArgsList<Types...>;
	using ind_seq = std::index_sequence_for<Type0, Types...>;
private:
	Clap0 arg0;
	TypeN args;
public:
	ArgsList(Type0 arg0, Types... args) :
		arg0(clap_hand<Type0>(arg0)),
		args(clap_hand<Types>(args)...) {}
public:
	static constexpr size_t Count = 1 + sizeof...(Types);
private:
	template<size_t ind, class = void>
	struct index : TypeN::template index<ind - 1> {};
	template<class ___>
	struct index<0, ___> { using type = Type0; };
public:
	template<size_t ind> requires(ind < Count)
	using type = typename index<ind>::type;
public:
	template<size_t ind> requires(ind < Count)
	inline auto &value_left() {
		if_c (ind)
			 reflect_as(args.template value_left<ind - 1>())
		else reflect_as(arg0)
	}			
	template<size_t ind> requires(ind < Count)
	inline auto &value_left() const {
		if_c (ind)
			 reflect_as(args.template value_left<ind - 1>())
		else reflect_as(arg0)
	}
	template<size_t ind> requires(ind < Count)
	inline auto value_right() {
		if_c (ind)
			 reflect_as(args.template value_right<ind - 1>())
		else reflect_as(static_cast<Right0>(arg0))
	}
	template<size_t ind> requires(ind < Count)
	inline auto value_right() const {
		if_c (ind)
			 reflect_as(args.template value_right<ind - 1>())
		else reflect_as(static_cast<const Right0>(arg0))
	}
	template<size_t ind> requires(ind < Count)
	inline auto value() {
		if_c (ind)
			 reflect_as(args.template value<ind - 1>())
		else reflect_as(static_cast<Clap0>(arg0))
	}
	template<size_t ind> requires(ind < Count)
	inline auto value() const {
		if_c (ind)
			 reflect_as(args.template value<ind - 1>())
		else reflect_as(static_cast<const Clap0>(arg0))
	}
private:
	template<class AnyCallable, size_t... ind>
	inline auto invoke(AnyCallable f, std::index_sequence<ind...>) reflect_as(f(value<ind>()...));
	template<class AnyClass, class AnyMethod, size_t... ind>
	inline auto invoke(AnyClass &cls, AnyMethod method, std::index_sequence<ind...>) reflect_as((cls.*method)(value<ind>()...));
private:
	template<class AnyClass, size_t... ind>
	inline auto &&construct(std::index_sequence<ind...>) reflect_as(AnyClass(value<ind>()...));
	template<class AnyClass, size_t... ind>
	inline auto *new_construct(std::index_sequence<ind...>) reflect_as(new AnyClass(value<ind>()...));
public:
	template<class AnyCallable>
	inline auto invoke(AnyCallable f) reflect_as(invoke(f, ind_seq{}));
	template<class AnyClass, class AnyMethod>
	inline auto invoke(AnyClass &cls, AnyMethod method) reflect_as(invoke(cls, method, ind_seq{}));
public:
	template<class AnyClass>
	inline auto &&construct() reflect_as(construct<AnyClass>(ind_seq{}));
	template<class AnyClass>
	inline auto *new_construct() reflect_as(new_construct<AnyClass>(ind_seq{}));
};
template<FunctionAllType AnyFunc>
using ArgsListOf = ListArgsOf<AnyFunc, ArgsList>;
#pragma endregion

#pragma region Chain Extended Helper 
template<class ParentClass, class ChildClass>
using Chain = std::conditional_t<std::is_void_v<ChildClass>, ParentClass, ChildClass>;
template<class ParentClass, class ChildClass>
concept IsChainExtended =
	(!std::is_void_v<ChildClass> && std::is_base_of_v<ParentClass, ChildClass>) ||
	  std::is_void_v<ChildClass>;
template<class ParentClass, class ChildClass>
struct ExtendShim {
	using Child = Chain<ParentClass, ChildClass>;
	using Self = ParentClass;
	ExtendShim() requires(IsChainExtended<ParentClass, ChildClass>) = default;
	Child &__child__() reflect_as(*static_cast<Child *>(this));
	const Child &__child__() const reflect_as(*static_cast<const Child *>(this));
};
#define static
subtype_branch(super);
#undef static
template<class Class1, class Class2>
constexpr bool is_chain_extended_on =
std::is_void_v<Class1> || std::is_void_v<Class2> ? false :
	IsSame<Class1, Class2> ? true :
	is_chain_extended_on<subtype_branchof_super<Class1, void>, Class2>;
#pragma endregion

#pragma region Class Reference
template<class AnyRef>
union ProxyShim final {
private:
	AnyRef t;
public:
	ProxyShim(auto &arg) : t(arg) {}
	ProxyShim(const auto &arg) : t(arg) {}
	ProxyShim(AnyRef &&arg) : t(to_right_hand(arg)) {}
	~ProxyShim() {}
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
union ProxyShim<AnyType *> final {
private:
	AnyType *ptr;
public:
	template<class OtherType>
	ProxyShim(OtherType *ptr) : ptr((AnyType *)ptr) {}
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
class StructShim : protected AnyStruct {
public:
	StructShim() : AnyStruct({ 0 }) {}
	StructShim(const AnyStruct &s) : AnyStruct(s) {}
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
constexpr bool IsProxyOf = false;
template<class RefType>
constexpr bool IsProxyOf<ProxyShim<RefType>> = true;
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

	fmt_word() = default;
	fmt_word(const fmt_word &) = default;
	template<class CharType>
	fmt_word(const CharType *format) {
		auto ch = *format;
		if (ch == ' ') {
			right_dir = true;
			symbol = Symbol::Space;
			ch = *++format;
		}
		elif (ch == '*') {
			symbol = Symbol::Space;
			ch = *++format;
		}
		switch (ch) {
			case '+':
				symbol = Symbol::Pos;
				ch = *++format;
				break;
		}
		switch (ch) {
			case '0':
				int_blank = Align::Zero;
				int_align = true;
				ch = *++format;
				break;
			case ' ':
				int_blank = Align::Space;
				int_align = true;
				ch = *++format;
				break;
		}
		if (ch == '~') {
			int_trunc = true;
			ch = *++format;
		}
		auto align = 0;
		while ('0' <= ch && ch <= '9') {
			align *= 10;
			align += ch - '0';
			if (align > 32)
				return; // overflow
			ch = *++format;
		}
		int_calign = align;
		if (ch == '.') {
			float_force = true;
			ch = *++format;
		}
		elif (ch == '0') {
			float_blank = Align::Zero;
			float_align = true;
			ch = *++format;
		}
		align = 0;
		while ('0' <= ch && ch <= '9') {
			align *= 10;
			align += ch - '0';
			if (align > 32)
				return; // overflow
			ch = *++format;
		}
		float_calign = align;
		if (ch == ' ') {
			float_blank = Align::Space;
			float_align = true;
			ch = *++format;
		}
		switch (ch) {
			case 'q':
				radix_type = Rad::Qua;
				ch = *++format;
				break;
			case 'o':
				radix_type = Rad::Oct;
				ch = *++format;
				break;
			case 'd':
				radix_type = Rad::Dec;
				ch = *++format;
				break;
			case 'X':
				alfa_type = Cap::Big;
				[[fallthrough]];
			case 'x':
				radix_type = Rad::Hex;
				ch = *++format;
				break;
			default:
				return; // Unknown
		}
		return;
	}
};
class format_numeral : public fmt_word {
public:
	format_numeral() {}
	format_numeral(fmt_word fmt) : fmt_word(fmt) {}
	format_numeral(const char *lpFormat) : fmt_word(lpFormat) {}
	format_numeral(const wchar_t *lpFormat) : fmt_word(lpFormat) {}
private:
	template<class AnyChar>
	static inline auto __push(uintptr_t ui, AnyChar *hpString, AnyChar alfa, uint8_t radix, uint8_t int_trunc) {
		uint8_t len = 0;
		do {
			auto d_sm = ui / radix;
			auto rbit = (AnyChar)(ui - d_sm * radix);
			ui = d_sm;
			*--hpString = rbit + (rbit < 10 ? '0' : alfa);
		} while (ui && ++len < int_trunc);
		return hpString;
	}
	template<class AnyChar>
	static inline auto __push(double pure_float, AnyChar *lpString, AnyChar alfa, uint8_t radix, uint8_t float_trunc) {
		uint8_t len = 0;
		while (pure_float > 0.f && len++ < float_trunc) {
			pure_float *= radix;
			auto rbit = (AnyChar)pure_float;
			pure_float -= rbit;
			*lpString++ = rbit + (rbit < 10 ? '0' : alfa);
		}
		return lpString;
	}
	template<class AnyChar>
	static inline auto __moveH2L(AnyChar *lpString, AnyChar *hpString, int uLength) {
		while (uLength--)
			*lpString++ = *hpString++;
		return lpString;
	}
private:
	inline uint8_t _radix() const reflect_as((uint8_t)radix_type == (uint8_t)Rad::Dec ? 10 : (2 << (uint8_t)radix_type));
	template<class AnyChar>
	inline AnyChar _alfa_char() const reflect_as(((uint8_t)alfa_type == (uint8_t)Cap::Big ? 'A' : 'a') - 10);
	template<class AnyChar>
	inline AnyChar _fill_int_char() const reflect_as((uint8_t)int_blank == (uint8_t)Align::Space ? ' ' : '0');
	template<class AnyChar>
	inline AnyChar _fill_float_char() const reflect_as((uint8_t)float_blank == (uint8_t)Align::Space ? ' ' : '0');
	template<class AnyChar>
	inline auto _push(uintptr_t uint_part, AnyChar *hpBuffer, uint8_t radix, AnyChar alfa, bool neg) const {
		auto lpBuffer = __push(uint_part, hpBuffer, alfa, radix, int_trunc ? int_calign : 32);
		auto int_len = hpBuffer - lpBuffer;
		if (int_len < int_calign && int_align) {
			auto fill = _fill_int_char<AnyChar>();
			while (int_len++ < int_calign)
				*--lpBuffer = fill;
		}
		if (neg)
			*--lpBuffer = '-';
		elif ((uint8_t)symbol == (uint8_t)Symbol::Pos)
			*--lpBuffer = '+';
		elif ((uint8_t)symbol == (uint8_t)Symbol::Space)
			*--lpBuffer = ' ';
		if (right_dir)
			while (int_len++ < int_calign)
				*--lpBuffer = ' ';
		return lpBuffer;
	}
	template<class AnyChar>
	inline auto _push(double float_part, AnyChar *lpBuffer, uint8_t radix, AnyChar alfa) const {
		auto hpBuffer = __push(
			float_part, lpBuffer + 1,
			alfa, radix, float_calign);
		auto float_len = hpBuffer - lpBuffer - 1;
		if (float_align) {
			auto fill = _fill_float_char<AnyChar>();
			while (float_len++ < int_calign)
				*hpBuffer++ = fill;
		}
		if (float_len > 0)
			*lpBuffer = '.';
		elif (float_force)
			*lpBuffer = '.';
		elif (float_align)
			*lpBuffer = ' ';
		else --hpBuffer;
		return hpBuffer;
	}
public:
	template<class AnyChar>
	inline auto push(uintptr_t uint_part, AnyChar *lpBuffer, AnyChar *&hpBuffer, size_t maxLength) const {
		hpBuffer = lpBuffer + maxLength - 2;
		lpBuffer = _push(uint_part, hpBuffer, _radix(), _alfa_char<AnyChar>(), false);
		return lpBuffer;
	}
	template<class AnyChar>
	inline auto push(intptr_t int_part, AnyChar *lpBuffer, AnyChar *&hpBuffer, size_t maxLength) const {
		bool neg = int_part < 0;
		if (neg) int_part = -int_part;
		hpBuffer = lpBuffer + maxLength - 2;
		lpBuffer = _push((uintptr_t)int_part, hpBuffer, _radix(), _alfa_char<AnyChar>(), neg);
		return lpBuffer;
	}
	template<class AnyChar>
	inline auto push(double float_part, AnyChar *lpBuffer, AnyChar *&hpBuffer, size_t maxLength) const {
		auto rad = _radix();
		auto alfa = _alfa_char<AnyChar>();
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
	static constexpr size_t MaxLen = 64;
	template<class AnyChar, class AnyType>
	inline size_t push(AnyType i, AnyChar *pBuffer) const {
		AnyChar lpBuffer[MaxLen] = { 0 }, *hpString, *lpString;
		if_c (std::is_unsigned_v<AnyType>)
			lpString = push((uintptr_t)i, lpBuffer, hpString, MaxLen);
		elif_c (std::is_integral_v<AnyType>)
			lpString = push((intptr_t)i, lpBuffer, hpString, MaxLen);
		elif_c (std::is_floating_point_v<AnyType>)
			lpString = push(i, lpBuffer, hpString, MaxLen);
		auto size = (size_t)(hpString - lpString);
		if (pBuffer)
			for (size_t i = 0; i < size; i++)
				pBuffer[i] = lpString[i];
		return size;
	}
};
const auto DEC = format_numeral("d");
const auto FPT = format_numeral(".5d");
inline format_numeral operator ""_nx(const char *format, size_t n) reflect_as(format);
inline format_numeral operator ""_nx(const wchar_t *format, size_t n) reflect_as(format);
#pragma endregion

#pragma region Exception
class Exception {
	const char
		*lpFile = O,
		*lpFunc = O,
		*lpSent = O;
	uint32_t
		uLine = 0,
		uErrCode = 0;
public:
	Exception() {}
	Exception(const char *lpszFile, const char *lpszFunc, const char *lpszSent,
			  uint32_t nLine, uint32_t uErrCode = 0) :
		lpFile(lpszFile), lpFunc(lpszFunc), lpSent(lpszSent),
		uLine(nLine), uErrCode(uErrCode) {}
public:
	inline auto File() const reflect_as(lpFile);
	inline auto Function() const reflect_as(lpFunc);
	inline auto Sentence() const reflect_as(lpSent);
	inline auto Line() const reflect_as(uLine);
	inline auto ErrorCode() const reflect_as(uErrCode);
public:
	inline operator bool() const reflect_as(lpSent);
};
#pragma endregion

#pragma region Lambda
/* --- LambdaBase --- */
template<class RetType, class... Args>
struct LambdaBase {
	virtual ~LambdaBase() = default;
	virtual RetType operator()(Args ...) = 0;
};
template<class PackType, class RetType, class... Args>
class FunctionPackage : public LambdaBase<RetType, Args...> {
	mutable PackType func;
public:
	FunctionPackage(PackType &f) : func(f) {}
	RetType operator()(Args ...args) override {
		static_assert(static_compatible<PackType, RetType(Args...)>, "Argument list uncompatible");
		if_c (std::is_pointer_v<PackType>)
			 return func(args...);
		else return func(args...);
	}
};
/* --- Lambda --- */
template<class...>
class Lambda;
template<class RetType, class... Args>
class Lambda<RetType(Args...)> final {
private:
	mutable LambdaBase<RetType, Args...> *func = O;
	mutable bool bAllocated = false;
public:
	Lambda() {}
	Lambda(Null) {}
	Lambda(const Lambda &f) : func(f.func) {}
public:
	template<class Type>
	Lambda(Type &f) : func(new FunctionPackage<Type, RetType, Args...>(f)), bAllocated(true) {}
	template<class Type>
	Lambda(Type f) : func(new FunctionPackage<Type, RetType, Args...>(f)), bAllocated(true) {}
	~Lambda() { if (func && bAllocated) delete func, func = O; }
public:
	inline operator bool() const reflect_as(!func);
	inline bool operator!=(Null) const reflect_as(func);
	inline bool operator==(Null) const reflect_as(!func);
	inline Lambda operator&() reflect_to_self();
	inline const Lambda operator&() const reflect_to_self();
	inline RetType operator()(Args...args) const reflect_as(func(args...));
	inline auto &operator=(const Lambda &f) const noexcept reflect_to_self(func = f.func, bAllocated = false);
	inline auto &operator=(const Lambda &f) noexcept reflect_to_self(func = f.func, bAllocated = false);
	inline auto &operator=(Lambda &&f) noexcept reflect_to_self(func = f.func, f.func = O, bAllocated = true);
};
template<class...FuncTypes>
using fn = Lambda<FuncTypes...>;
#pragma endregion

#pragma region Enum
/* (misc) */
template<class AnyType> constexpr bool IsEnum = requires { typename AnyType::EnumType; };
template<class AnyType>	concept EnumType = IsEnum<AnyType>;

template<class AnyType>
struct EnumUnitBase {
	using ProtoType = AnyType;
	using ProtoUnit = EnumUnitBase;
	ProtoType val;
	constexpr EnumUnitBase(ProtoType val) : val(val) {}
	static constexpr size_t CountAll = 0;
};
template<class AnyType>
using EnumUnit = ConditionOf<IsEnum<AnyType>, AnyType, EnumUnitBase<AnyType>>;

template<class SubClass, class BaseType>
struct EnumBase {
	static constexpr bool HasProtoEnum = IsEnum<BaseType>;
	using ProtoEnum = ConditionOf<HasProtoEnum, BaseType, void>;
	using ProtoUnit = typename EnumUnit<BaseType>::ProtoUnit;
	using ProtoType = typename ProtoUnit::ProtoType;
	static constexpr size_t CountAll() reflect_as(HasProtoEnum ? SubClass::Count + ProtoEnum::CountAll() : SubClass::Count); \
};
template<EnumType AnyEnum> using EnumProtoTypeOf = typename EnumUnit<AnyEnum>::ProtoType;
template<EnumType AnyEnum> constexpr bool IsEnumProto = IsEnum<typename AnyEnum::ProtoEnum>;
template<class AnyType> concept NotProtoEnum = !IsEnumProto<AnyType>;
template<NotProtoEnum AnyEnum> using ProtoEnumOf = typename EnumUnit<AnyEnum>::ProtoEnum;

template<EnumType Type1, EnumType Type2>
constexpr bool IsExtendedOf() {
	if constexpr (IsSame<Type1, Type2>)
		 return true;
	elif constexpr (IsEnumProto<Type1>)
		 return false;
	else return IsExtendedOf<ProtoEnumOf<Type1>, Type2>();
}

template<EnumType Enum1, EnumType Enum2, class AnyEnum>
	requires(IsExtendedOf<Enum1, Enum2>() || IsExtendedOf<Enum2, Enum1>())
inline auto __makeResult(AnyEnum val) {
	if_c (IsExtendedOf<Enum1, Enum2>())
		 return reuse_as<Enum1>((typename Enum1::ProtoType)val);
	else return reuse_as<Enum2>((typename Enum2::ProtoType)val);
}

template<class AnyType, class AnyEnum>
concept EnumCastable =
	IsEnum<AnyEnum> &&
	std::is_convertible_v<AnyType, EnumProtoTypeOf<AnyEnum>>;
template<class AnyEnum, class AnyType>
	requires(IsEnum<AnyEnum> && std::is_convertible_v<AnyType, EnumProtoTypeOf<AnyEnum>>)
inline AnyEnum enum_cast(AnyType val) reflect_as(reuse_as<AnyEnum>(val));

#pragma endregion

}
