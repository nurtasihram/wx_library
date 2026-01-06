module;

#define WX_CPPM_CORE
#include "wx"

export module wx;

subtype_branch(ProtoEnum);

export namespace WX {

constexpr bool IsUnicode =
#if defined(UNICODE)
	UNICODE;
#elif defined(_UNICODE)
	_UNICODE;
#else
	false;
#endif
 
template<class AnyType>
concept IntagerType = // std::is_same_v<int8_t, AnyType> ||		// may duplicated with char
					// std::is_same_v<int16_t, AnyType> ||		// may duplicated with wchar_t
					std::is_same_v<int32_t, AnyType> ||
					std::is_same_v<int64_t, AnyType> ||
					std::is_same_v<uint8_t, AnyType> ||
					std::is_same_v<uint16_t, AnyType> ||
					std::is_same_v<uint32_t, AnyType> ||
					std::is_same_v<uint64_t, AnyType>;
template<class AnyType>
concept FloatType = std::is_same_v<float, AnyType> ||
				    std::is_same_v<double, AnyType>;
				  // || std::is_same_v<long double, AnyType>	// Unsupport by some compilers
template<class AnyType>
concept NumberType = IntagerType<AnyType> || FloatType<AnyType>;

template<class Type1, class Type2>
constexpr bool IsEqualType = false;
template<class AnyType>
constexpr bool IsEqualType<AnyType, AnyType> = true;
template<class Type1, class Type2>
constexpr bool IsNotEqualType = !IsEqualType<Type1, Type2>;
template<class Type1, class Type2>
concept EqualType = IsEqualType<Type1, Type2>;
template<class Type, class Type2>
concept NotEqualType = IsNotEqualType<Type, Type2>;

template<class Type1, class Type2>
constexpr bool IsSameType(Type1, Type2) reflect_as(IsEqualType<Type1, Type2>);

template<class Type1, class Type2>
concept IsSameSizeType = sizeof(Type1) == sizeof(Type2);

template<class AnyType>
struct SizeOf_t { static constexpr size_t val = sizeof(AnyType); };
template<>
struct SizeOf_t<void> { static constexpr size_t val = 0; };
template<class AnyType>
constexpr size_t SizeOf = SizeOf_t<AnyType>::val;

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
	requires(std::is_same_v<typename Hand<AnyStrict>::base, AnyType>)
inline auto clap_hand(AnyType &a) -> Hand<AnyStrict>::clap reflect_as(static_cast<typename Hand<AnyStrict>::clap>(a));

#pragma endregion

#pragma region Prototypes Type Traits & Helpers System
template<class AnyType>
struct TypeNode // endnode
{ using proto = AnyType; };
template<class LastType, class ThisType = LastType>
	requires(IsNotEqualType<LastType, ThisType>)
struct TypeChain : TypeNode<LastType> {
	using type = LastType;
	using remove = ThisType;
};

/* --- Pointer --- */
template<class AnyType>
struct TypeNode<AnyType *> : TypeChain<AnyType, AnyType *> {};
template<class AnyType> constexpr bool IsPointerType = false;
template<class AnyType> constexpr bool IsPointerType<AnyType *> = true;
template<class AnyType> concept PointerType = IsPointerType<AnyType>;
template<class AnyType> concept NotPointerType = !IsPointerType<AnyType>;
template<class AnyType> using AlwaysPointer = std::conditional_t
	<IsPointerType<AnyType>, AnyType, typename TypeNode<AnyType *>::type>;
template<class AnyType> using NotPointer = std::conditional_t
	<!IsPointerType<AnyType>, AnyType, typename TypeNode<AnyType>::remove>;
template<class AnyType> using PointerWith = typename TypeNode<AnyType *>::type;
inline constexpr bool IsPointer(auto *) reflect_as(true);
inline constexpr bool IsPointer(auto) reflect_as(false);
/* --- Left Value Reference --- */
template<class AnyType>
struct TypeNode<AnyType &> : TypeChain<AnyType, AnyType &> {};
template<class AnyType> constexpr bool IsLeftType = false;
template<class AnyType> constexpr bool IsLeftType<AnyType &> = true;
template<class AnyType> concept LeftType = IsLeftType<AnyType>;
template<class AnyType> concept NotLeftType = !IsLeftType<AnyType>; 
template<class AnyType> using AlwaysLeft = std::conditional_t
	<IsLeftType<AnyType>, AnyType, typename TypeNode<AnyType>::type &>;
template<class AnyType> using NotLeft = std::conditional_t
	<!IsLeftType<AnyType>, AnyType, typename TypeNode<AnyType>::remove>;
template<class AnyType> using LeftWith = typename TypeNode<AnyType &>::type;
inline constexpr bool IsLeft(auto &) reflect_as(true);
inline constexpr bool IsLeft(auto) reflect_as(false);
/* --- Right Value Reference --- */
template<class AnyType>
struct TypeNode<AnyType &&> : TypeChain<AnyType, AnyType &&> {};
template<class AnyType> constexpr bool IsRightType = false;
template<class AnyType>	constexpr bool IsRightType<AnyType &&> = true;
template<class AnyType>	concept RightType = IsRightType<AnyType>;
template<class AnyType>	concept NotRightType = !IsRightType<AnyType>;
template<class AnyType> using AlwaysRight = std::conditional_t
	<IsRightType<AnyType>, AnyType, typename TypeNode<AnyType>::type &&>;
template<class AnyType> using NotRight = std::conditional_t
	<!IsRightType<AnyType>, AnyType, typename TypeNode<AnyType>::remove>;
template<class AnyType> using RightWith = typename TypeNode<AnyType &&>::type;
inline constexpr bool IsRight(auto &&) reflect_as(true);
inline constexpr bool IsRight(auto) reflect_as(false);
/* --- Const --- */
template<class AnyType>
struct TypeNode<const AnyType> : TypeChain<AnyType, AnyType const> {};
template<class AnyType>	constexpr bool IsConstType = false;
template<class AnyType>	constexpr bool IsConstType<const AnyType> = true;
template<class AnyType>	concept ConstType = IsConstType<AnyType>;
template<class AnyType> concept NotConstType = !IsConstType<AnyType>;
template<class AnyType> using AlwaysConst = std::conditional_t
	<IsConstType<AnyType>, AnyType, const typename TypeNode<AnyType>::type>;
template<class AnyType> using NotConst = std::conditional_t
	<!IsConstType<AnyType>, AnyType, typename TypeNode<AnyType>::remove>;
template<class AnyType> using ConstWith = typename TypeNode<const AnyType>::type;
inline constexpr bool IsConst(const auto &) reflect_as(true);
inline constexpr bool IsConst(auto) reflect_as(false);
/* --- Volatile --- */
template<class AnyType>
struct TypeNode<volatile AnyType> : TypeChain<AnyType, AnyType volatile> {};
template<class AnyType>	constexpr bool IsVolatileType = false;
template<class AnyType>	constexpr bool IsVolatileType<volatile AnyType> = true;
template<class AnyType>	concept VolatileType = IsVolatileType<AnyType>;
template<class AnyType> concept NotVolatileType = !IsVolatileType<AnyType>;
template<class AnyType> using AlwaysVolatile = std::conditional_t
	<IsVolatileType<AnyType>, AnyType, volatile typename TypeNode<AnyType>::type>;
template<class AnyType> using NotVolatile = std::conditional_t
	<!IsVolatileType<AnyType>, AnyType, typename TypeNode<AnyType>::remove>;
template<class AnyType> using VolatileWith = typename TypeNode<volatile AnyType>::type;
inline constexpr bool IsVolatile(volatile auto &) reflect_as(true);
inline constexpr bool IsVolatile(auto) reflect_as(false);

/* --- Array --- */
template<class AnyType>
struct TypeNode<AnyType []> : TypeChain<AnyType, AnyType []>
{ static constexpr auto is_c_variadic = true; };
template<class AnyType, size_t Len>
struct TypeNode<AnyType[Len]> : TypeChain<AnyType, AnyType[Len]> {
	static constexpr auto is_c_variadic = false;
	static constexpr auto arr_len = Len;
};
// type_with
template<class AnyType>
using ArrayVariadicWith = AnyType[];
template<class AnyType, size_t Len>
using ArrayWith = AnyType[Len];
// variadic
template<class AnyType> constexpr bool IsArrayVariadicType = false;
template<class AnyType>	constexpr bool IsArrayVariadicType<AnyType []> = true;
template<class AnyType> concept ArrayVariadicType = IsArrayVariadicType<AnyType>;
template<class AnyType> concept NotArrayVariadicType = !IsArrayVariadicType<AnyType>;
template<class AnyType> using NotArrayVariadic = std::conditional_t
	<!IsArrayVariadicType<AnyType>, AnyType, typename TypeNode<AnyType>::remove>;
inline constexpr bool IsArrayVariadic(auto []) reflect_as(true);
inline constexpr bool IsArrayVariadic(auto) reflect_as(false);
// fixed-length
template<class AnyType> constexpr bool IsArrayType = false;
template<class AnyType, size_t Len> constexpr bool IsArrayType<AnyType[Len]> = true;
template<class AnyType> concept ArrayType = IsArrayType<AnyType>;
template<class AnyType> concept NotArrayType = !IsArrayType<AnyType>;
template<class AnyType> using NotArray = std::conditional_t
	<!IsArrayType<AnyType>, AnyType, typename TypeNode<AnyType>::remove>;
inline constexpr bool IsArray(ArrayType auto) reflect_as(true);
inline constexpr bool IsArray(auto) reflect_as(false);
// all
template<class AnyType> constexpr bool IsArrayAllType = IsArrayType<AnyType> || IsArrayVariadicType<AnyType>;
template<class AnyType> concept ArrayAllType = IsArrayAllType<AnyType>;
template<class AnyType> concept NotArrayAllType = !IsArrayAllType<AnyType>;
inline constexpr bool IsArrayAll(ArrayAllType auto) reflect_as(true);
inline constexpr bool IsArrayAll(auto) reflect_as(false);
// checks
template<class AnyType, size_t Len>
constexpr size_t ArrCountOf(const ArrayWith<AnyType, Len> &) reflect_as(Len);

/* --- Final Remove --- */
template<class AnyType>
using ProtoOf = typename TypeNode<AnyType>::proto;
template<class AnyType>
using RemoveStorage = typename TypeNode<AnyType>::remove;

/* --- Complex Prototypes --- */

/* --- Function --- */
template<class RetType, class...Args>
struct TypeNode<RetType(Args...)> { // endnode
	using proto = RetType(Args...);
	using variadic = RetType(Args..., ...);
	using return_type = RetType;
	template<template<class...> class ArgsList>
	using arg_list = ArgsList<Args...>;
	static constexpr bool is_c_variadic = false;
	static constexpr auto arg_num = sizeof...(Args);
};
template<class RetType, class...Args>
struct TypeNode<RetType(*)(Args...)> : TypeChain<RetType(Args...), RetType(*)(Args...)> {};
template<class RetType, class...Args>
struct TypeNode<RetType(&)(Args...)> : TypeChain<RetType(Args...), RetType(&)(Args...)> {};
template<class RetType, class...Args>
struct TypeNode<RetType(Args..., ...)> : TypeChain<RetType(Args...), RetType(Args..., ...)>
{ static constexpr bool is_c_variadic = true; };
template<class RetType, class...Args>
struct TypeNode<RetType(*)(Args..., ...)> : TypeChain<RetType(Args...), RetType(*)(Args..., ...)>
{ static constexpr bool is_c_variadic = true; };
template<class RetType, class...Args>
struct TypeNode<RetType(&)(Args..., ...)> : TypeChain<RetType(Args...), RetType(&)(Args..., ...)>
{ static constexpr bool is_c_variadic = true; };
// type_with
template<class RetType, class...Args>
using FunctionWith = RetType(Args...);
template<class RetType, class...Args>
using FunctionVariadicWith = RetType(Args..., ...);
template<class RetType, class ArgsList>
struct FunctionWithHelper;
template<class RetType, template<class...> class ArgsList, class...Args>
struct FunctionWithHelper<RetType, ArgsList<Args...>> {
	using type = RetType(Args...);
	using variadic_type = RetType(Args..., ...);
};
template<class RetType, class ArgsList>
using FunctionWithList = typename FunctionWithHelper<RetType, ArgsList>::type;
template<class RetType, class ArgsList>
using FunctionVariadicWithList = typename FunctionWithHelper<RetType, ArgsList>::variadic_type;
// proto-typical
template<class AnyType> constexpr bool IsFunctionProtoType = false;
template<class RetType, class...Args> constexpr bool IsFunctionProtoType<RetType(Args...)> = true;
template<class AnyType> concept FunctionProtoType = IsFunctionProtoType<AnyType>;
template<class AnyType> concept NotFunctionProto = !IsFunctionProtoType<AnyType>;
// proto-variadic
template<class AnyType> constexpr bool IsFunctionVariadicProtoType = false;
template<class RetType, class...Args> constexpr bool IsFunctionVariadicProtoType<RetType(Args..., ...)> = true;
template<class AnyType> concept FunctionVariadicProto = IsFunctionVariadicProtoType<AnyType>;
template<class AnyType> concept NotFunctionVariadicProto = !IsFunctionVariadicProtoType<AnyType>;
// typical
template<class AnyType> constexpr bool IsFunctionType = IsFunctionProtoType<ProtoOf<AnyType>>;
template<class AnyType> concept FunctionType = IsFunctionType<AnyType>;
template<class AnyType> concept NotFunctionType = !IsFunctionType<AnyType>;
inline constexpr bool IsFunction(FunctionType auto) reflect_as(true);
inline constexpr bool IsFunction(auto) reflect_as(false);
// variadic
template<class AnyType> constexpr bool IsFunctionVariadicType = IsFunctionVariadicProtoType<ProtoOf<AnyType>>;
template<class AnyType> concept FunctionVariadicType = IsFunctionVariadicType<AnyType>;
template<class AnyType> concept NotFunctionVariadicType = !IsFunctionVariadicType<AnyType>;
inline constexpr bool IsFunctionVariadic(FunctionVariadicType auto) reflect_as(true);
inline constexpr bool IsFunctionVariadic(auto) reflect_as(false);
// all
template<class AnyType> constexpr bool IsFunctionAllType = IsFunctionType<AnyType> || IsFunctionVariadicType<AnyType>;
template<class AnyType> concept FunctionAllType = IsFunctionAllType<AnyType>;
template<class AnyType> concept NotFunctionAllType = !IsFunctionAllType<AnyType>;
template<FunctionAllType AnyFunc> using AlwaysFunctionVariadic = std::conditional_t
	<IsFunctionVariadicType<AnyFunc>, AnyFunc, typename TypeNode<AnyFunc>::variadic>;
template<FunctionAllType AnyFunc> using NotFunctionVariadic = std::conditional_t
	<!IsFunctionVariadicType<AnyFunc>, AnyFunc, typename TypeNode<AnyFunc>::proto>;
inline constexpr bool IsFunctionAll(FunctionAllType auto) reflect_as(true);
inline constexpr bool IsFunctionAll(auto) reflect_as(false);
// checks
inline constexpr auto ArgCountOf(FunctionAllType auto fn) reflect_as(TypeNode<decltype(fn)>::arg_num);
template<class...> class ArgsList;
template<FunctionAllType AnyFunc, template<class...> class ArgsList = WX::ArgsList>
using FunctionArgsListOf = typename TypeNode<AnyFunc>::template arg_list<ArgsList>;
template<FunctionAllType AnyFunc>
using FunctionReturnTypeOf = typename TypeNode<AnyFunc>::return_type;

/* --- Member Pointer --- */
template<class AnyClass, class AnyType>
struct TypeNode<AnyType AnyClass:: *> : TypeChain<AnyType, AnyType AnyClass:: *> 
{ using owner = AnyClass; };
// type_with
template<class AnyClass, class AnyType>
using MemberPointerWith = AnyType AnyClass:: *;
// type
template<class AnyType> constexpr bool IsMemberPointerType = false;
template<class AnyClass, class AnyType> constexpr bool IsMemberPointerType<AnyType AnyClass:: *> = true;
template<class AnyType> concept MemberPointerType = IsMemberPointerType<AnyType>;
template<class AnyType> concept NotMemberPointerType = !IsMemberPointerType<AnyType>;
inline constexpr bool IsMemberPointer(MemberPointerType auto) reflect_as(true);
inline constexpr bool IsMemberPointer(auto) reflect_as(false);
// type_of
template<class AnyType, class AnyClass> constexpr bool IsMemberPointerTypeOf = false;
template<class AnyType, class AnyClass>	constexpr bool IsMemberPointerTypeOf<AnyType AnyClass:: *, AnyClass> = true;
template<class AnyType, class AnyClass> concept MemberPointerOf = IsMemberPointerTypeOf<AnyType, AnyClass>;
template<class AnyClass> inline constexpr bool IsMemberPointerOf(MemberPointerOf<AnyClass> auto) reflect_as(true);
template<class AnyClass> inline constexpr bool IsMemberPointerOf(auto) reflect_as(false);
/* --- Member Function Pointer (Method) --- */
template<class AnyClass, class RetType, class...Args>
struct TypeNode<RetType(AnyClass:: *)(Args...)> : TypeChain<RetType(Args...), RetType(AnyClass:: *)(Args...)> { using owner = AnyClass; };
template<class AnyClass, class RetType, class...Args>
struct TypeNode<RetType(AnyClass:: *)(Args..., ...)> : TypeChain<RetType(Args..., ...), RetType(AnyClass:: *)(Args..., ...)>
{ using owner = AnyClass; };
// type_with
template<class AnyClass, class RetType, class...Args>
using MethodWith = RetType(AnyClass:: *)(Args...);
template<class AnyClass, class RetType, class...Args>
using MethodVariadicWith = RetType(AnyClass:: *)(Args..., ...);
template<class AnyClass, class RetType, class ArgsList>
struct MethodWithHelper;
template<class AnyClass, class RetType, template<class...> class ArgsList, class...Args>
struct MethodWithHelper<AnyClass, RetType, ArgsList<Args...>> {
	using type = RetType(AnyClass:: *)(Args...);
	using variadic_type = RetType(AnyClass:: *)(Args..., ...);
};
template<class AnyClass, class RetType, class ArgsList>
using MethodWithList = typename MethodWithHelper<AnyClass, RetType, ArgsList>::type;
template<class AnyClass, class RetType, class ArgsList>
using MethodVariadicWithList = typename MethodWithHelper<AnyClass, RetType, ArgsList>::variadic_type;
// typical
template<class AnyType> constexpr bool IsMethodType = false;
template<class AnyClass, class RetType, class...Args> constexpr bool IsMethodType<RetType(AnyClass:: *)(Args...)> = true;
template<class AnyType> concept MethodType = IsMethodType<AnyType>;
template<class AnyType> concept NotMethodType = !IsMethodType<AnyType>;
inline constexpr bool IsMethod(MethodType auto) reflect_as(true);
inline constexpr bool IsMethod(auto) reflect_as(false);
// variadic
template<class AnyType> constexpr bool IsMethodVariadicType = false;
template<class AnyClass, class RetType, class...Args> constexpr bool IsMethodVariadicType<RetType(AnyClass:: *)(Args..., ...)> = true;
template<class AnyType> concept MethodVariadicType = IsMethodVariadicType<AnyType>;
inline constexpr bool IsMethodVariadic(MethodVariadicType auto) reflect_as(true);
inline constexpr bool IsMethodVariadic(auto) reflect_as(false);
// all
template<class AnyType> constexpr bool IsMethodAllType = IsMethodType<AnyType> || IsMethodVariadicType<AnyType>;
template<class AnyType> concept MethodAllType = IsMethodAllType<AnyType>;
template<class AnyType> concept NotMethodAllType = !IsMethodAllType<AnyType>;
inline constexpr bool IsMethodAll(MethodAllType auto) reflect_as(true);
inline constexpr bool IsMethodAll(auto) reflect_as(false);
// (alias)
template<class AnyType> constexpr bool IsMemberFunctionType = IsMethodType<AnyType>;
template<class AnyType> constexpr bool IsMemberFunctionVariadicType = IsMethodVariadicType<AnyType>;
template<class AnyType> constexpr bool IsMemberFunctionAllType = IsMethodAllType<AnyType>;
template<class AnyType> concept MemberFunctionType = IsMethodType<AnyType>;
template<class AnyType> concept MemberFunctionVariadicType = IsMethodVariadicType<AnyType>;
template<class AnyType> concept MemberFunctionAllType = IsMethodAllType<AnyType>;
inline constexpr bool IsMemberFunction(MemberFunctionType auto) reflect_as(true);
inline constexpr bool IsMemberFunction(auto) reflect_as(false);
inline constexpr bool IsMemberFunctionVariadic(MemberFunctionVariadicType auto) reflect_as(true);
inline constexpr bool IsMemberFunctionVariadic(auto) reflect_as(false);
inline constexpr bool IsMemberFunctionAll(MemberFunctionAllType auto) reflect_as(true);
inline constexpr bool IsMemberFunctionAll(auto) reflect_as(false);
// type_of
template<class AnyType, class AnyClass> constexpr bool IsMethodTypeOf  = false;
template<MethodType AnyMethod, class AnyClass> constexpr bool IsMethodTypeOf<AnyMethod, AnyClass> = EqualType<AnyClass, typename TypeNode<AnyMethod>::owner>;
template<class AnyType, class AnyClass> constexpr bool IsMethodVariadicTypeOf = false;
template<MethodVariadicType AnyMethod, class AnyClass> constexpr bool IsMethodVariadicTypeOf<AnyMethod, AnyClass> = EqualType<AnyClass, typename TypeNode<AnyMethod>::owner>;
template<class AnyType, class AnyClass> constexpr bool IsMethodAllTypeOf = false;
template<MethodAllType AnyMethod, class AnyClass> constexpr bool IsMethodAllTypeOf<AnyMethod, AnyClass> = EqualType<AnyClass, typename TypeNode<AnyMethod>::owner>;
template<class AnyType, class AnyClass> concept MethodTypeOf = IsMethodTypeOf<AnyType, AnyClass>;
template<class AnyType, class AnyClass> concept MethodVariadicTypeOf = IsMethodVariadicTypeOf<AnyType, AnyClass>;
template<class AnyType, class AnyClass> concept MethodAllTypeOf = IsMethodAllTypeOf<AnyType, AnyClass>;
template<class AnyClass> inline constexpr bool IsMethodOf(MethodTypeOf<AnyClass> auto) reflect_as(true);
template<class AnyClass> inline constexpr bool IsMethodOf(auto) reflect_as(false);
template<class AnyClass> inline constexpr bool IsMethodVariadicOf(MethodVariadicTypeOf<AnyClass> auto) reflect_as(true);
template<class AnyClass> inline constexpr bool IsMethodVariadicOf(auto) reflect_as(false);
template<class AnyClass> inline constexpr bool IsMethodAllOf(MethodAllTypeOf<AnyClass> auto) reflect_as(true);
template<class AnyClass> inline constexpr bool IsMethodAllOf(auto) reflect_as(false);
// (alias)
template<class AnyType, class AnyClass> constexpr bool IsMemberFunctionTypeOf = IsMethodTypeOf<AnyType, AnyClass>;
template<class AnyType, class AnyClass> constexpr bool IsMemberFunctionVariadicTypeOf = IsMethodVariadicTypeOf<AnyType, AnyClass>;
template<class AnyType, class AnyClass> constexpr bool IsMemberFunctionAllTypeOf = IsMethodAllTypeOf<AnyType, AnyClass>;
template<class AnyType, class AnyClass> concept MemberFunctionTypeOf = MethodTypeOf<AnyType, AnyClass>;
template<class AnyType, class AnyClass> concept MemberFunctionVariadicTypeOf = MethodVariadicTypeOf<AnyType, AnyClass>;
template<class AnyType, class AnyClass> concept MemberFunctionAllTypeOf = MethodAllTypeOf<AnyType, AnyClass>;
template<class AnyClass> inline constexpr bool IsMemberFunctionOf(MemberFunctionTypeOf<AnyClass> auto) reflect_as(true);
template<class AnyClass> inline constexpr bool IsMemberFunctionOf(auto) reflect_as(false);
template<class AnyClass> inline constexpr bool IsMemberFunctionVariadicOf(MemberFunctionVariadicTypeOf<AnyClass> auto) reflect_as(true);
template<class AnyClass> inline constexpr bool IsMemberFunctionVariadicOf(auto) reflect_as(false);
template<class AnyClass> inline constexpr bool IsMemberFunctionAllOf(MemberFunctionAllTypeOf<AnyClass> auto) reflect_as(true);
template<class AnyClass> inline constexpr bool IsMemberFunctionAllOf(auto) reflect_as(false);
#pragma endregion

#pragma region Any Functional Compatible test
template<class AnyCallable, class Ret, class... Args>
concept StaticCompatible =
	requires(AnyCallable f, Args... args) {
		{ f(args...) } -> std::convertible_to<Ret>;
	};
template<class AnyCallable, class FuncType>
constexpr bool static_compatible = false;
template<class AnyCallable, class Ret, class... Args>
constexpr bool static_compatible<AnyCallable, Ret(Args...)> = StaticCompatible<AnyCallable, Ret, Args...>;
#pragma endregion

#pragma region (De/C)onstructor Compatible test
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
template<class AnyClass>
concept DestructorEffectless =
	std::is_pointer_v<AnyClass> ||
	std::is_reference_v<AnyClass> ||
	std::is_trivially_destructible_v<AnyClass>;
template<class AnyClass>
concept DestructorEffective = !DestructorEffectless<AnyClass>;
#pragma endregion

eunm class TypeModifiers : uint8_t {
	None = 0x00,
	Pointer = 0x01,
	Left = 0x02,
	Right = 0x03,
	Const = 0x04,
	Volatile = 0x08,
};
enum class TypePrototypes : uint8_t {
	None = 0x00,
	ArrayVariadic = 0x01,
	ArrayFixed = 0x02,
	Function = 0x03,
	FunctionVariadic = 0x04,
	Member = 0x10,
};

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
#pragma endregion

#pragma region Chain Extender 
template<class ParentClass, class ChildClass>
using Chain = std::conditional_t<std::is_void_v<ChildClass>, ParentClass, ChildClass>;
template<class ParentClass, class ChildClass>
concept IsChainExtended =
	(!std::is_void_v<ChildClass> && std::is_base_of_v<ParentClass, ChildClass>) ||
	  std::is_void_v<ChildClass>;
template<class ParentClass, class ChildClass>
struct ChainExtender {
	using Child = Chain<ParentClass, ChildClass>;
	using Self = ParentClass;
	ChainExtender() requires(IsChainExtended<ParentClass, ChildClass>) = default;
	Child &__child__() reflect_as(*static_cast<Child *>(this));
	const Child &__child__() const reflect_as(*static_cast<const Child *>(this));
};
#define static
subtype_branch(super);
#undef static
template<class Class1, class Class2>
constexpr bool is_chain_extended_on =
std::is_void_v<Class1> || std::is_void_v<Class2> ? false :
	std::is_same_v<Class1, Class2> ? true :
	is_chain_extended_on<subtype_branchof_super<Class1, void>, Class2>;
#pragma endregion

#pragma region Class Reference
template<class AnyRef>
union RefAs {
private:
	AnyRef t;
public:
	RefAs(auto &arg) : t(arg) {}
	RefAs(const auto &arg) : t(arg) {}
	RefAs(AnyRef &&arg) : t(to_right_hand(arg)) {}
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
	RefStruct() : AnyStruct({ 0 }) {}
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
			CopyMemory(pBuffer, lpString, size * sizeof(AnyChar));
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
template<class AnyType>
concept IsEnum = requires { typename AnyType::EnumType; };
template<class Class1, class Class2>
constexpr bool is_chain_enum_on =
std::is_void_v<Class1> || std::is_void_v<Class2> ? false :
	std::is_same_v<Class1, Class2> ? true :
	is_chain_enum_on<subtype_branchof_ProtoEnum<Class1, void>, Class2>;
template<IsEnum Enum1, IsEnum Enum2, class EnumType>
inline auto __makeResult(EnumType val) {
	constexpr auto left = is_chain_enum_on<Enum1, Enum2>;
	constexpr auto right = is_chain_enum_on<Enum2, Enum1>;
	static_assert(left || right, "Convertless");
	if_c (left)
		return reuse_as<Enum1>((typename Enum1::ProtoType)val);
	else
		return reuse_as<Enum2>((typename Enum2::ProtoType)val);
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
#pragma endregion

}
