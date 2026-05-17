module;

#include <cstdint>
#include <typeinfo>
#include <type_traits>
#include <functional>

#define WANDX_CPPM_EXPORT_NATIVE
#include "WandX.h"

export module WandX;

export namespace WandX {

#pragma region Prototypes AnyFrom Standard Library

// real-type extension checkers

template<class AnyClass, class AnyBase>
constexpr bool IsExtendedOf = std::is_base_of_v<AnyBase, AnyClass>;
template<class AnyType>
concept Extendable = std::is_class_v<AnyType> && !std::is_final_v<AnyType>;

// real address retrievers

constexpr auto *address_cast(auto &obj) noexcept ret_as(std::addressof(obj));

// type name retrievers

template<class AnyType>
constexpr auto TypeNameOf() ret_as(typeid(AnyType).name());
constexpr auto TypeNameOf(auto type) ret_as(typeid(decltype(type)).name());

// intagers 

using Int8   = std:: int8_t;
using Int16  = std:: int16_t;
using Int32  = std:: int32_t;
using Int64  = std:: int64_t;

using Int8U  = std::uint8_t;
using Int16U = std::uint16_t;
using Int32U = std::uint32_t;
using Int64U = std::uint64_t;

using IntP   = std:: intptr_t;
using IntPU  = std::uintptr_t;

using SizeT  = std::size_t;

#pragma endregion

}

export namespace WandX {

#pragma region Basic Type Traits & Helpers System

/* Nullptr Type & Value */

using Nu = decltype(nullptr);
constexpr Nu O = nullptr;

template<class AnyType> constexpr bool IsNu     = false;
template<             > constexpr bool IsNu<Nu> = true;
template<class AnyType> concept NotNu = !IsNu<AnyType>;

/* Void Type Helpers */

template<class AnyType> constexpr bool IsVoid        = false;
template<             > constexpr bool IsVoid<void>  = true;
template<class AnyType> concept       NotVoid        = !IsVoid<AnyType>;

/* Type Size Helpers */

template<class Type1, class Type2> constexpr bool IsSameSize     = sizeof(Type1) == sizeof(Type2);
template<class Type1, class Type2> concept          SameSizeType = IsSameSize<Type1, Type2>;

template<class AnyType> constexpr SizeT SizeOf        = sizeof(AnyType);
template<             > constexpr SizeT SizeOf<void>  = 0;

/* Same / Equal Helpers */

// Values Equalities

template<auto val1, auto val2> constexpr bool IsEqualValue = val1 == val2;
template<auto val1, auto val2> constexpr bool UnequalValue = val1 != val2;

template<auto val0, auto...valN> constexpr bool AllEqualValue = (IsEqualValue<val0, valN> && ...);
template<auto val0, auto...valN> constexpr bool  IsEqualityIn = (IsEqualValue<val0, valN> || ...);
template<auto val0, auto...valN> constexpr bool  UnequalityIn = (UnequalValue<val0, valN> && ...);

template<auto val1, auto val2> concept  EqualToValue = IsEqualValue<val1, val2>;
template<auto val1, auto val2> concept NequalToValue = UnequalValue<val1, val2>;

template<auto val0, auto...valN> concept  EqualityIn = IsEqualityIn<val0, valN...>;
template<auto val0, auto...valN> concept NequalityIn = UnequalityIn<val0, valN...>;

// Values Same

template<auto val1, auto val2> constexpr bool IsSameValue             = false;
template<auto val0>            constexpr bool IsSameValue<val0, val0> = true;
template<auto val1, auto val2> constexpr bool NoSameValue             = IsSameValue<val1, val2>;

template<auto val0, auto...valN> constexpr bool  AllSameValue = (IsSameValue<val0, valN> && ...);
template<auto val0, auto...valN> constexpr bool  IsOneOfValue = (IsSameValue<val0, valN> || ...);
template<auto val0, auto...valN> constexpr bool IsNoneOfValue = (NoSameValue<val0, valN> && ...);

template<auto val1, auto val2> concept   SameAsValue = IsSameValue<val1, val2>;
template<auto val1, auto val2> concept NoSameAsValue = NoSameValue<val1, val2>;

template<auto val0, auto...valN> concept  OneOfValue =  IsOneOfValue<val0, valN...>;
template<auto val0, auto...valN> concept NoneOfValue = IsNoneOfValue<val0, valN...>;

// Types

template<class Type1, class Type2> constexpr bool IsSame               = false;
template<class Type0>              constexpr bool IsSame<Type0, Type0> = true;
template<class Type1, class Type2> constexpr bool NoSame               = !IsSame<Type1, Type2>;

template<class Type0, class...TypeN> constexpr bool  AllSame = (IsSame<Type0, TypeN> && ...);
template<class Type0, class...TypeN> constexpr bool  IsOneOf = (IsSame<Type0, TypeN> || ...);
template<class Type0, class...TypeN> constexpr bool IsNoneOf = (NoSame<Type0, TypeN> && ...);

template<class Type1, class Type2> concept   SameAs = IsSame<Type1, Type2>;
template<class Type1, class Type2> concept NoSameAs = NoSame<Type1, Type2>;

template<class Type0, class...TypeN> concept  OneOf =  IsOneOf<Type0, TypeN...>;
template<class Type0, class...TypeN> concept NoneOf = IsNoneOf<Type0, TypeN...>;

/* Wrap Of Type & Value */

template<auto           val> struct         OfValue { static constexpr auto value = val; };
template<class      AnyType> concept        OfValuable = requires{ AnyType::value; };
template<OfValuable AnyType> constexpr auto ValueOf    =           AnyType::value;

template<class     AnyType> struct  OfType              { using   type = AnyType; };
template<class     AnyType> concept OfTypical = requires{ typename AnyType::type; };
template<OfTypical AnyType> using   TypeOf    =           typename AnyType::type;

// Ifs

template<bool b, auto true_val, auto false_val> constexpr auto ValueIf                            = false_val;
template<        auto true_val, auto false_val> constexpr auto ValueIf<true, true_val, false_val> =  true_val;

template<bool,   class TrueType, class FalseType> struct TypeIfProto                             : OfType<FalseType> {};
template<        class TrueType, class FalseType> struct TypeIfProto<true,  TrueType, FalseType> : OfType< TrueType> {};
template<bool b, class TrueType, class FalseType> using  TypeIf = TypeOf<TypeIfProto<b, TrueType, FalseType>>;

template<class AnyType, class AnyDefault> using VoidChain = TypeIf<IsVoid<AnyType>, AnyDefault, AnyType>;

// ValueMap

template<auto...caseN>                                            struct ValueMapProto;
template<auto key_val>                                            struct ValueMapProto<key_val>                              : OfValue<key_val>                 {};
template<auto key_val, auto default_val>                          struct ValueMapProto<key_val, default_val>                 : OfValue<default_val>             {};
template<auto key_val, auto case_val, auto ret_val, auto...caseN> struct ValueMapProto<key_val, case_val, ret_val, caseN...> {
	template<class = void, bool = IsEqualValue<key_val, case_val>>
	struct Selector : ValueMapProto<key_val, caseN...> {};
	template<class _>
	struct Selector<_, true> : OfValue<ret_val> {};
	static constexpr auto value = ValueOf<Selector<>>;
	 
};
template<auto key_val, auto case_val, auto ret_val>               struct ValueMapProto<key_val, case_val, ret_val>           : OfValue<ret_val>
{ static_assert(IsSameValue<key_val, case_val>, "ValueMapProto Error: No matching value found."); };
template<auto...caseN> constexpr auto ValueMap = ValueOf<ValueMapProto<caseN...>>;

// ValueSwitch

template<auto...caseN>            struct ValueSwitchProto;
template<auto default_val>        struct ValueSwitchProto<default_val>           : OfValue<default_val>       {};
template<auto val1, auto...caseN> struct ValueSwitchProto< true, val1, caseN...> : OfValue<val1>              {};
template<auto val1, auto...caseN> struct ValueSwitchProto<false, val1, caseN...> : ValueSwitchProto<caseN...> {};
template<bool case0, auto val1>   struct ValueSwitchProto<case0, val1>           : OfValue<val1>
{ static_assert(case0, "ValueSwitchProto Error: No matching case found."); };
template<auto...caseN> constexpr auto ValueSwitch = ValueOf<ValueSwitchProto<caseN...>>;

// TypeMap

template<class...CaseN>                                               struct TypeMapProto;
template<class KeyType>                                               struct TypeMapProto<KeyType>                              : OfType<KeyType>                 {};
template<class KeyType, class DefaultType>                            struct TypeMapProto<KeyType, DefaultType>                 : OfType<DefaultType>             {};
template<class KeyType, class  RetType               , class...CaseN> struct TypeMapProto<KeyType,  KeyType, RetType, CaseN...> : OfType<RetType>                 {};
template<class KeyType, class CaseType, class TypeRet, class...CaseN> struct TypeMapProto<KeyType, CaseType, TypeRet, CaseN...> : TypeMapProto<KeyType, CaseN...> {};
template<class KeyType, class CaseType, class TypeRet>                struct TypeMapProto<KeyType, CaseType, TypeRet>           : OfType<TypeRet>
{ static_assert(IsSame<KeyType, CaseType>, "TypeMapProto Error: No matching type found."); };
template<class...CaseN> using TypeMap = TypeOf<TypeMapProto<CaseN...>>;

// TypeSwitch

template<bool, class> struct TypeCase;
template<class AnyType>           constexpr bool IsTypeCase = false;
template<bool caseN, class TypeN> constexpr bool IsTypeCase<TypeCase<caseN, TypeN>> = true;
template<class AnyType>           concept TypeCaseType = IsTypeCase<AnyType>;

template<class...CaseN>              struct TypeSwitchProto;
template<class DefaultType>          struct TypeSwitchProto<DefaultType>                      : OfType<DefaultType>       {};
template<class Type1, class...CaseN> struct TypeSwitchProto<TypeCase<true , Type1>, CaseN...> : OfType<Type1>             {};
template<class Type1, class...CaseN> struct TypeSwitchProto<TypeCase<false, Type1>, CaseN...> : TypeSwitchProto<CaseN...> {};
template<class TypeX, class...CaseN> struct TypeSwitchProto<TypeX, CaseN...> 
{ static_assert(TypeCaseType<TypeX>, "TypeSwitchProto Error: Invalid TypeCase provided."); };
template<bool case0, class Type0>    struct TypeSwitchProto<TypeCase<case0, Type0>>           : OfType<Type0>
{ static_assert(case0, "TypeSwitchProto Error: No matching case found."); };
template<class...CaseN> using TypeSwitch = TypeOf<TypeSwitchProto<CaseN...>>;

/* Numeric Types */

// Int8 and Int16 may duplicated with char or wchar_t, so they are excluded in Numeral
template<class AnyType> concept Numeral             = OneOf<AnyType, Int8U, Int16U, Int32U, Int64U, Int32, Int64>;
template<class AnyType> concept PositiveNumeral     = OneOf<AnyType, Int8U, Int16U, Int32U, Int64U>;
template<class AnyType> concept SignedIntagerType   = OneOf<AnyType, Int8 , Int16,  Int32,  Int64 >;
template<class AnyType> concept UnsignedIntagerType = PositiveNumeral<AnyType>;
template<class AnyType> concept IntagerType         = SignedIntagerType<AnyType> || UnsignedIntagerType<AnyType>;

template<class AnyType> concept FloatType = OneOf<AnyType, float, double/*, long double*/>;

template<class AnyType> concept SignedAllType = FloatType<AnyType> || SignedIntagerType<AnyType>;
template<class AnyType> concept NumberType    = FloatType<AnyType> || Numeral<AnyType>;

template<Int8U bits>
using IntXU = TypeSwitch<
	TypeCase<bits <=  8,  Int8U>,
	TypeCase<bits <= 16, Int16U>,
	TypeCase<bits <= 32, Int32U>,
	TypeCase<bits <= 64, Int64U>
>;

template<Int8U bits>
using IntX = TypeSwitch<
	TypeCase<bits <=  8,  Int8>,
	TypeCase<bits <= 16, Int16>,
	TypeCase<bits <= 32, Int32>,
	TypeCase<bits <= 64, Int64>
>;

#pragma endregion

#pragma region Type Modifiers & Filters

/* Type filters */

template<class AnyType> constexpr bool IsLeft                 = false;
template<class AnyType> constexpr bool IsRight                = false;
template<class AnyType> constexpr bool IsPointer              = false;
template<class AnyType> constexpr bool IsConst                = false;
template<class AnyType> constexpr bool IsVolatile             = false;
template<class AnyType> constexpr bool IsArrayVariadic        = false;
template<class AnyType> constexpr bool IsArrayInLength        = false;
template<class AnyType> constexpr bool IsMemberPointer        = false;
template<class AnyType> constexpr bool IsFuntionProto         = false;
template<class AnyType> constexpr bool IsFuntionVariadicProto = false;

template<class AnyType>                 constexpr bool IsLeft                         <AnyType &>             = true;
template<class AnyType>                 constexpr bool IsRight                        <AnyType &&>            = true;
template<class AnyType>                 constexpr bool IsPointer                      <AnyType *>             = true;
template<class AnyType>                 constexpr bool IsConst                        <AnyType const>         = true;
template<class AnyType>                 constexpr bool IsVolatile                     <AnyType volatile>      = true;
template<class AnyType>                 constexpr bool IsArrayVariadic                <AnyType     [   ]>     = true;
template<class AnyType, SizeT Len>      constexpr bool IsArrayInLength                <AnyType     [Len]>     = true;
template<class AnyType, SizeT Len>      constexpr bool IsArrayInLength                <AnyType (& )[Len]>     = true;
template<class AnyType, SizeT Len>      constexpr bool IsArrayInLength                <AnyType (&&)[Len]>     = true;
template<class AnyType, class AnyOnwer> constexpr bool IsMemberPointer                <AnyType AnyOnwer:: *>    = true;
template<class AnyType, class...ParaN>  constexpr bool IsFuntionProto                 <AnyType (ParaN...)>      = true;
template<class AnyType, class...ParaN>  constexpr bool IsFuntionVariadicProto         <AnyType (ParaN..., ...)> = true;

template<class AnyType> concept LeftType                    = IsLeft                  <AnyType>;
template<class AnyType> concept RightType                   = IsRight                 <AnyType>;
template<class AnyType> concept PointerType                 = IsPointer               <AnyType>;
template<class AnyType> concept ConstType                   = IsConst                 <AnyType>;
template<class AnyType> concept VolatileType                = IsVolatile              <AnyType>;
template<class AnyType> concept ArrayVariadicType           = IsArrayVariadic         <AnyType>;
template<class AnyType> concept ArrayInLengthType           = IsArrayInLength         <AnyType>;
template<class AnyType> concept MemberPointerType           = IsMemberPointer         <AnyType>;
template<class AnyType> concept FuntionProtoType            = IsFuntionProto          <AnyType>;
template<class AnyType> concept FuntionVariadicProtoType    = IsFuntionVariadicProto  <AnyType>;

template<class AnyType> concept NotLeftType                 = !IsLeft                 <AnyType>;
template<class AnyType> concept NotRightType                = !IsRight                <AnyType>;
template<class AnyType> concept NotPointerType              = !IsPointer              <AnyType>;
template<class AnyType> concept NotConstType                = !IsConst                <AnyType>;
template<class AnyType> concept NotVolatileType             = !IsVolatile             <AnyType>;
template<class AnyType> concept NotArrayVariadicType        = !IsArrayVariadic        <AnyType>;
template<class AnyType> concept NotArrayInLengthType        = !IsArrayInLength        <AnyType>;
template<class AnyType> concept NotMemberPointerType        = !IsMemberPointer        <AnyType>;
template<class AnyType> concept NotFuntionProtoType         = !IsFuntionProto         <AnyType>;
template<class AnyType> concept NotFuntionVariadicProtoType = !IsFuntionVariadicProto <AnyType>;

constexpr bool IsVolatileType            (                         auto) ret_as(false);
constexpr bool IsPointerType             (                         auto) ret_as(false);
constexpr bool IsMemberPointerType       (                         auto) ret_as(false);
constexpr bool IsVolatileType            (            VolatileType auto) ret_as(true);
constexpr bool IsPointerType             (             PointerType auto) ret_as(true);
constexpr bool IsMemberPointerType       (       MemberPointerType auto) ret_as(true);

template<class AnyType> constexpr bool IsHand              = IsLeft          <AnyType> || IsRight                <AnyType>;
template<class AnyType> constexpr bool IsArray             = IsArrayVariadic <AnyType> || IsArrayInLength        <AnyType>;
template<class AnyType> constexpr bool IsFunctionAllProto  = IsFuntionProto  <AnyType> || IsFuntionVariadicProto <AnyType>;

template<class AnyType> concept HandType             = IsHand             <AnyType>;
template<class AnyType> concept ArrayType            = IsArray            <AnyType>;
template<class AnyType> concept FunctionAllProtoType = IsFunctionAllProto <AnyType>;

constexpr bool IsFunctionAllProtoType(                     auto) ret_as(false);
constexpr bool IsFunctionAllProtoType(FunctionAllProtoType auto) ret_as(true);

enum class Modifications {
	No                    = 0 << 0,
	Left                  = 1 << 0,
	Right                 = 1 << 1,
	Const                 = 1 << 2,
	Volatile              = 1 << 3,
	Pointer               = 1 << 4,
	ArrayVariadic         = 1 << 5,
	ArrayInLength         = 1 << 6,
	MemberPointer         = 1 << 7,
	FuntionProto          = 1 << 8,
	FuntionVariadicProto  = 1 << 9
};
using TypeNodes = Modifications;

template<class AnyType>
struct ProtoNodeOf {
	using proto = AnyType;
	using remove = AnyType;
	static constexpr Modifications modification = Modifications::No;
};
template<class AnyType> using     ProtoOf = typename ProtoNodeOf<AnyType>::proto;
template<class AnyType> using RemoveModOf = typename ProtoNodeOf<AnyType>::remove;

template<class AnyType> constexpr bool IsProto = IsSame<AnyType, ProtoOf<AnyType>>;
template<class AnyType> constexpr auto ModOf = ProtoNodeOf<AnyType>::modification;

template<class AnyType, Modifications mod> constexpr bool HasMod = 
	ProtoNodeOf<AnyType>::modification == mod ? true :
	IsProto<AnyType> ? false :
	HasMod<RemoveModOf<AnyType>, mod>;
template<class AnyType, Modifications mod> concept ModOn = HasMod<AnyType, mod>;

template<Modifications mod, ModOn<mod> AnyType> constexpr auto IndexProtoNodeValue = [](){
	using node = ProtoNodeOf<AnyType>;
	if constexpr (node::modification == mod)
		 return node{};
	else return IndexProtoNodeValue<mod, RemoveModOf<AnyType>>;
}();
template<Modifications mod, class AnyType> using IndexProtoNode = decltype(IndexProtoNodeValue<mod, AnyType>);

template<class AnyType> concept ModOnRight                = ModOn<AnyType, Modifications::Right                >;
template<class AnyType> concept ModOnConst                = ModOn<AnyType, Modifications::Const                >;
template<class AnyType> concept ModOnVolatile             = ModOn<AnyType, Modifications::Volatile             >;
template<class AnyType> concept ModOnPointer              = ModOn<AnyType, Modifications::Pointer              >;
template<class AnyType> concept ModOnArrayVariadic        = ModOn<AnyType, Modifications::ArrayVariadic        >;
template<class AnyType> concept ModOnArrayInLength        = ModOn<AnyType, Modifications::ArrayInLength        >;
template<class AnyType> concept ModOnMemberPointer        = ModOn<AnyType, Modifications::MemberPointer        >;
template<class AnyType> concept ModOnFuntionProto         = ModOn<AnyType, Modifications::FuntionProto         >;
template<class AnyType> concept ModOnFuntionVariadicProto = ModOn<AnyType, Modifications::FuntionVariadicProto >;

template<class AnyType> concept ModOnArray            = ModOnArrayVariadic<AnyType> || ModOnArrayInLength       <AnyType>;
template<class AnyType> concept ModOnFunctionAllProto = ModOnFuntionProto <AnyType> || ModOnFuntionVariadicProto<AnyType>;

/* functionals */

template<class...>
class ParaList;

template<class AnyRet, class...ParaN>
struct ProtoNodeOf<AnyRet(ParaN...)> {
	using proto       = AnyRet(ParaN...);
	using remove      = proto;
	using return_type = AnyRet;
	template<template<class...> class AnyList = ParaList>
	using para_list = AnyList<ParaN...>;
	static constexpr auto countof_para = sizeof...(ParaN);
	static constexpr Modifications modification = Modifications::FuntionProto;
};
template<class AnyRet, class...ParaN>
struct ProtoNodeOf<AnyRet(ParaN..., ...)>  {
	using proto       = AnyRet(ParaN..., ...);
	using remove      = proto;
	using return_type = AnyRet;
	template<template<class...> class AnyList = ParaList>
	using listof_para = AnyList<ParaN...>;
	static constexpr SizeT countof_para = sizeof...(ParaN);
	static constexpr Modifications modification = Modifications::FuntionVariadicProto;
};

/** Prototype Shims **/

template<class LastType, class NextType, Modifications mod>
	requires(NoSame<LastType, NextType>)
struct TypeShim : ProtoNodeOf<LastType> {
	using remove = LastType;
	using type   = NextType;
	static constexpr Modifications modification = mod;
};

template<class AnyType>                struct LeftShim              : TypeShim<AnyType, AnyType &        , Modifications::Left         > {};
template<class AnyType>                struct RightShim             : TypeShim<AnyType, AnyType &&       , Modifications::Right        > {};
template<class AnyType>                struct PointerShim           : TypeShim<AnyType, AnyType *        , Modifications::Pointer      > {};
template<class AnyType>                struct ConstShim             : TypeShim<AnyType, AnyType const    , Modifications::Const        > {};
template<class AnyType>                struct VolatileShim          : TypeShim<AnyType, AnyType volatile , Modifications::Volatile     > {};
template<class AnyType, SizeT Len = 0> struct ArrayShim             : TypeShim<AnyType, AnyType [Len]    , Modifications::ArrayInLength> {};
template<class AnyType>                struct ArrayShim<AnyType, 0> : TypeShim<AnyType, AnyType [   ]    , Modifications::ArrayVariadic> {};
template<class AnyType, class Onwer>   struct MemberPointerShim     : TypeShim<AnyType, AnyType Onwer:: *, Modifications::MemberPointer> {}; ///////

/* Prototype Nodes */

template<class AnyType>              struct ProtoNodeOf<AnyType &              > : LeftShim          <AnyType>         {};
template<class AnyType>              struct ProtoNodeOf<AnyType &&             > : RightShim         <AnyType>         {};
template<class AnyType>              struct ProtoNodeOf<AnyType *              > : PointerShim       <AnyType>         {};
template<class AnyType>              struct ProtoNodeOf<AnyType const          > : ConstShim         <AnyType>         {};
template<class AnyType>              struct ProtoNodeOf<AnyType volatile       > : VolatileShim      <AnyType>         {};
template<class AnyType, class Owner> struct ProtoNodeOf<AnyType Owner:: *      > : MemberPointerShim <AnyType, Owner>  { using owner = Owner; };
template<class AnyType>              struct ProtoNodeOf<AnyType           [   ]> : ArrayShim         <AnyType>         { static constexpr auto length = 0; };
template<class AnyType, SizeT Len>   struct ProtoNodeOf<AnyType           [Len]> : ArrayShim         <AnyType, Len>    { static constexpr auto length = Len; };
template<class AnyType, SizeT Len>   struct ProtoNodeOf<AnyType (&)       [Len]> : LeftShim          <AnyType [Len]>   {};
template<class AnyType, SizeT Len>   struct ProtoNodeOf<AnyType (&&)      [Len]> : RightShim         <AnyType [Len]>   {};
template<class AnyType, SizeT Len>   struct ProtoNodeOf<AnyType (*)       [Len]> : PointerShim       <AnyType [Len]>   {};
template<class AnyType, SizeT Len>   struct ProtoNodeOf<AnyType  const    [Len]> : ConstShim         <AnyType [Len]>   {};
template<class AnyType, SizeT Len>   struct ProtoNodeOf<AnyType  volatile [Len]> : VolatileShim      <AnyType [Len]>   {};

/* add modifications */

template<class AnyType>                using LeftOf           = TypeOf<LeftShim          <AnyType>       >;
template<class AnyType>                using RightOf          = TypeOf<RightShim         <AnyType>       >;
template<class AnyType>                using ConstOf          = TypeOf<ConstShim         <AnyType>       >;
template<class AnyType>                using VolatileOf       = TypeOf<VolatileShim      <AnyType>       >;
template<class AnyType>                using PointerOf        = TypeOf<PointerShim       <AnyType>       >;
template<class AnyType>                using ArrayVariadicOf  = TypeOf<ArrayShim         <AnyType>       >;
template<class AnyType, class Onwer>   using MemberPointerOf  = TypeOf<MemberPointerShim <AnyType, Onwer>>;
template<class AnyType, SizeT Len = 0> using ArrayOf          = TypeOf<ArrayShim         <AnyType, Len>  >;

/* remove modifications */

template<LeftType          AnyLeft>          using RemoveLeftOf     = RemoveModOf<AnyLeft>;
template<RightType         AnyRight>         using RemoveRightOf    = RemoveModOf<AnyRight>;
template<ConstType         AnyConst>         using RemoveConstOf    = RemoveModOf<AnyConst>;
template<VolatileType      AnyVolatile>      using RemoveVolatileOf = RemoveModOf<AnyVolatile>;
template<PointerType       AnyPointer>       using RemovePointerOf  = RemoveModOf<AnyPointer>;
template<ArrayType         AnyArray>         using RemoveArrayOf    = RemoveModOf<AnyArray>;
template<MemberPointerType AnyMemberPointer> using MemberTypeOf     = RemoveModOf<AnyMemberPointer>;
template<MemberPointerType AnyMemberPointer> using OwnerTypeOf      = typename ProtoNodeOf<AnyMemberPointer>::owner;

/* conditional modifications */

template<bool UseShim, template<class> class ShimType, class AnyType> struct CondShim;
template<              template<class> class ShimType, class AnyType> struct CondShim<true , ShimType, AnyType> : OfType<ShimType<AnyType>> {};
template<              template<class> class ShimType, class AnyType> struct CondShim<false, ShimType, AnyType> : OfType<AnyType> {};
template<bool UseShim, template<class> class ShimType, class AnyType> using  CondShimFor = TypeOf<CondShim<UseShim, ShimType, AnyType>>;

template<class AnyType> using LeftFor      = CondShimFor<!IsLeft    <AnyType>, LeftShim    , AnyType>;
template<class AnyType> using RightFor     = CondShimFor<!IsRight   <AnyType>, RightShim   , AnyType>;
template<class AnyType> using PointerFor   = CondShimFor<!IsPointer <AnyType>, PointerShim , AnyType>;
template<class AnyType> using ConstFor     = CondShimFor<!IsConst   <AnyType>, ConstShim   , AnyType>;
template<class AnyType> using VolatileFor  = CondShimFor<!IsVolatile<AnyType>, VolatileShim, AnyType>;

// array

template<bool UseShim, class AnyType, SizeT Len> struct CondArrayShim;
template<              class AnyType, SizeT Len> struct CondArrayShim<false, AnyType, Len> : OfType<AnyType> {};
template<              class AnyType, SizeT Len> struct CondArrayShim<true , AnyType, Len> : ArrayShim<AnyType, Len> {};
template<bool UseShim, class AnyType, SizeT Len>  using CondArrayShimFor = TypeOf<CondArrayShim<UseShim, AnyType, Len>>;

template<ArrayType AnyArray>                using ArrayForVariadic  = ArrayOf<RemoveModOf<AnyArray>>;
template<ArrayType AnyArray, SizeT Len>     using LengthForArray    = ArrayOf<RemoveModOf<AnyArray>, Len>;
template<class     AnyType , SizeT Len = 0> using ArrayFor          = CondArrayShimFor<!IsArray<AnyType>, AnyType, Len>;

/* functional */

template<class AnyType> constexpr bool IsFunction                   = IsFuntionProto         <ProtoOf<AnyType>>;
template<class AnyType> constexpr bool IsFunctionVariadic           = IsFuntionVariadicProto <ProtoOf<AnyType>>;
template<class AnyType> constexpr bool IsFunctionAll                = IsFunctionAllProto     <ProtoOf<AnyType>>;
template<class AnyType> constexpr bool IsMethod                     = IsMemberPointer        <AnyType> &&  IsFunction         <AnyType>;
template<class AnyType> constexpr bool IsMethodVariadic             = IsMemberPointer        <AnyType> &&  IsFunctionVariadic <AnyType>;
template<class AnyType> constexpr bool IsMethodAll                  = IsMemberPointer        <AnyType> &&  IsFunctionAll      <AnyType>;
template<class AnyType> constexpr bool IsStaticFunction             = IsFunction             <AnyType> && !IsMemberPointer    <AnyType>;
template<class AnyType> constexpr bool IsStaticFunctionVariadic     = IsFunctionVariadic     <AnyType> && !IsMemberPointer    <AnyType>;
template<class AnyType> constexpr bool IsStaticFunctionAll          = IsFunctionAll          <AnyType> && !IsMemberPointer    <AnyType>;

template<class AnyType> concept FunctionType                = IsFunction               <AnyType>;
template<class AnyType> concept FunctionVariadicType        = IsFunctionVariadic       <AnyType>;
template<class AnyType> concept FunctionAllType             = IsFunctionAll            <AnyType>;
template<class AnyType> concept MethodType                  = IsMethod                 <AnyType>;
template<class AnyType> concept MethodVariadicType          = IsMethodVariadic         <AnyType>;
template<class AnyType> concept MethodAllType               = IsMethodAll              <AnyType>;
template<class AnyType> concept StaticFunctionType          = IsStaticFunction         <AnyType>;
template<class AnyType> concept StaticFunctionVariadicType  = IsStaticFunctionVariadic <AnyType>;
template<class AnyType> concept StaticFunctionAllType       = IsStaticFunctionAll      <AnyType>;

constexpr bool IsFunctionType               (                            auto) ret_as(false);
constexpr bool IsFunctionVariadicType       (                            auto) ret_as(false);
constexpr bool IsFunctionAllType            (                            auto) ret_as(false);
constexpr bool IsMethodType                 (                            auto) ret_as(false);
constexpr bool IsMethodVariadicType         (                            auto) ret_as(false);
constexpr bool IsMethodAllType              (                            auto) ret_as(false);
constexpr bool IsStaticFunctionType         (                            auto) ret_as(false);
constexpr bool IsStaticFunctionVariadicType (                            auto) ret_as(false);
constexpr bool IsStaticFunctionAllType      (                            auto) ret_as(false);
constexpr bool IsFunctionType               (               FunctionType auto) ret_as(true);
constexpr bool IsFunctionVariadicType       (       FunctionVariadicType auto) ret_as(true);
constexpr bool IsFunctionAllType            (            FunctionAllType auto) ret_as(true);
constexpr bool IsMethodType                 (                 MethodType auto) ret_as(true);
constexpr bool IsMethodVariadicType         (         MethodVariadicType auto) ret_as(true);
constexpr bool IsMethodAllType              (              MethodAllType auto) ret_as(true);
constexpr bool IsStaticFunctionType         (         StaticFunctionType auto) ret_as(true);
constexpr bool IsStaticFunctionVariadicType ( StaticFunctionVariadicType auto) ret_as(true);
constexpr bool IsStaticFunctionAllType      (      StaticFunctionAllType auto) ret_as(true);

template<class AnyRet, class...ParaN> using StaticFunctionProtoOf           = AnyRet   (ParaN...);
template<class AnyRet, class...ParaN> using StaticFunctionVariadicProtoOf   = AnyRet   (ParaN..., ...);
template<class AnyRet, class...ParaN> using StaticFunctionOf                = AnyRet(&)(ParaN...);
template<class AnyRet, class...ParaN> using StaticFunctionPtrOf             = AnyRet(*)(ParaN...);
template<class AnyRet, class...ParaN> using StaticFunctionPointerOf         = AnyRet(*)(ParaN...);
template<class AnyRet, class...ParaN> using StaticFunctionVariadicOf        = AnyRet(&)(ParaN..., ...);
template<class AnyRet, class...ParaN> using StaticFunctionVariadicPtrOf     = AnyRet(*)(ParaN..., ...);
template<class AnyRet, class...ParaN> using StaticFunctionVariadicPointerOf = AnyRet(*)(ParaN..., ...);

/* Others */

template<ArrayType      AnyArray> constexpr SizeT CountOfArray = ProtoNodeOf<AnyArray>::length;
template<FunctionAllType AnyFunc> constexpr SizeT CountOfPara  = ProtoNodeOf<AnyFunc>::countof_para;

template<ModOnArray AnyArray>
constexpr SizeT ArrayCountOf(AnyArray) ret_as(IndexProtoNode<Modifications::ArrayInLength, AnyArray>::length);
template<ModOnFunctionAllProto AnyFunc>
constexpr SizeT ParaCountOf(AnyFunc) ret_as(IndexProtoNode<Modifications::FuntionProto, AnyFunc>::countof_para);

template<FunctionAllType AnyFunc> using ReturnOfType = typename ProtoNodeOf<AnyFunc>::return_type;
template<FunctionAllType auto fn> using ReturnTypeOf = typename ProtoNodeOf<decltype(fn)>::return_type;
template<FunctionAllType AnyFunc, template<class...> class AnyList = ParaList>
using ParaListOfType = typename ProtoNodeOf<AnyFunc>::template listof_para<AnyList>;
template<FunctionAllType auto fn, template<class...> class AnyList = ParaList>
using ParaListTypeOf = typename ProtoNodeOf<decltype(fn)>::template listof_para<AnyList>;

template<template<class, class...> class AnyFuncOf, class AnyRet, class AnyListOfPara>
struct ListMake_expend {};
template<template<class, class...> class AnyFuncOf, class AnyRet, template<class...> class ParaList, class...ParaN>
struct ListMake_expend<AnyFuncOf, AnyRet, ParaList<ParaN...>> { using type = AnyFuncOf<AnyRet, ParaN...>; };
template<template<class, class...> class AnyFuncOf, class AnyRet, class AnyListOfPara>
using ListMake = TypeOf<ListMake_expend<AnyFuncOf, AnyRet, AnyListOfPara>>;

/* Bound return type */

template<FunctionType               AnyFunc, class AnyRet> constexpr bool IsFunctionRetOf               = IsSame<AnyRet, typename ProtoNodeOf<AnyFunc>::return_type>; 
template<FunctionVariadicType       AnyFunc, class AnyRet> constexpr bool IsFunctionVariadicRetOf       = IsSame<AnyRet, typename ProtoNodeOf<AnyFunc>::return_type>; 
template<FunctionAllType            AnyFunc, class AnyRet> constexpr bool IsFunctionAllRetOf            = IsSame<AnyRet, typename ProtoNodeOf<AnyFunc>::return_type>; 
template<MethodType                 AnyFunc, class AnyRet> constexpr bool IsMethodRetOf                 = IsSame<AnyRet, typename ProtoNodeOf<AnyFunc>::return_type>; 
template<MethodVariadicType         AnyFunc, class AnyRet> constexpr bool IsMethodVariadicRetOf         = IsSame<AnyRet, typename ProtoNodeOf<AnyFunc>::return_type>; 
template<MethodAllType              AnyFunc, class AnyRet> constexpr bool IsMethodAllRetOf              = IsSame<AnyRet, typename ProtoNodeOf<AnyFunc>::return_type>; 
template<StaticFunctionType         AnyFunc, class AnyRet> constexpr bool IsStaticFunctionRetOf         = IsSame<AnyRet, typename ProtoNodeOf<AnyFunc>::return_type>; 
template<StaticFunctionVariadicType AnyFunc, class AnyRet> constexpr bool IsStaticFunctionVariadicRetOf = IsSame<AnyRet, typename ProtoNodeOf<AnyFunc>::return_type>; 
template<StaticFunctionAllType      AnyFunc, class AnyRet> constexpr bool IsStaticFunctionAllRetOf      = IsSame<AnyRet, typename ProtoNodeOf<AnyFunc>::return_type>; 

template<class AnyType, class AnyRet> concept FunctionRetOf               = IsFunctionRetOf               <AnyType, AnyRet>;
template<class AnyType, class AnyRet> concept FunctionVariadicRetOf       = IsFunctionVariadicRetOf       <AnyType, AnyRet>;
template<class AnyType, class AnyRet> concept FunctionAllRetOf            = IsFunctionAllRetOf            <AnyType, AnyRet>;
template<class AnyType, class AnyRet> concept MethodRetOf                 = IsMethodRetOf                 <AnyType, AnyRet>;
template<class AnyType, class AnyRet> concept MethodVariadicRetOf         = IsMethodVariadicRetOf         <AnyType, AnyRet>;
template<class AnyType, class AnyRet> concept MethodAllRetOf              = IsMethodAllRetOf              <AnyType, AnyRet>;
template<class AnyType, class AnyRet> concept StaticFunctionRetOf         = IsStaticFunctionRetOf         <AnyType, AnyRet>;
template<class AnyType, class AnyRet> concept StaticFunctionVariadicRetOf = IsStaticFunctionVariadicRetOf <AnyType, AnyRet>;
template<class AnyType, class AnyRet> concept StaticFunctionAllRetOf      = IsStaticFunctionAllRetOf      <AnyType, AnyRet>;

/* Require */

template<class AnyRet, class...ParaN> AnyRet any_require(ParaN...) noexcept wx_uncallable;

/* Member Pointable test */

template<MemberPointerType AnyMemberPtr, class AnyType> constexpr bool IsMemberPointableOf = requires(AnyMemberPtr ptr) { (any_require<AnyType>().*ptr); };
template<class             AnyMemberPtr, class AnyType> concept          MemberPointableOf = IsMemberPointableOf<AnyMemberPtr, AnyType>;
template<class AnyType> constexpr bool IsMemberPointableOfType(auto) ret_as(false);
template<class AnyType> constexpr bool IsMemberPointableOfType(MemberPointableOf<AnyType> auto) ret_as(true);

#pragma endregion

#pragma region Invokable Cube Helpers

template<auto  fn     , auto ...arg  > concept InvokableFrom = requires()                        { fn(arg...); }; // implicit
template<class AnyType, class...ParaN> concept InvokableTo   = requires(AnyType fn, ParaN...arg) { fn(arg...); }; // implicit

template<auto fn, class...ParaN> concept InvokableFromLeft        = requires(ParaN...arg) { fn(arg                  ...); }; // implicit arg
template<auto fn, class...ParaN> concept InvokableFromLeftToRight = requires(           ) { fn(any_require<ParaN>() ...); }; // explicit arg
template<auto fn, class...ParaN> concept InvokableFromLeftToHand  = InvokableFromLeft<fn, ParaN...> && InvokableFromLeftToRight<fn, ParaN...>;	// 

template<class AnyType, auto...arg> concept InvokableFromRight       = requires(AnyType fn) {                     fn(arg ...); }; // implicit functor
template<class AnyType, auto...arg> concept InvokableFromRightToLeft = requires(          ) { any_require<AnyType>()(arg ...); }; // explicit functor
template<class AnyType, auto...arg> concept InvokableFromRightToHand = InvokableFromRight<AnyType, arg...> && InvokableFromRight<AnyType, arg...>; // 

template<class AnyType, class...ParaN> concept InvokableToRight = requires(ParaN...arg) { any_require<AnyType>()(arg                  ...); }; // explicit functor implicit arg
template<class AnyType, class...ParaN> concept InvokableToLeft  = requires(AnyType  fn) { fn                    (any_require<ParaN>() ...); }; // implicit functor explicit arg	  
template<class AnyType, class...ParaN> concept InvokableToHand  = requires(           ) { any_require<AnyType>()(any_require<ParaN>() ...); }; // explicit functor explicit arg

template<auto fn_up, auto fn_down> constexpr bool InvokableDownTo      = false;
template<auto fn_up, auto fn_down> constexpr bool InvokableDownToRight = false;
template<auto fn_up, auto fn_down> constexpr bool InvokableDownToHand  = false;

template<auto fn_up, class Ret, class...ParaN, Ret(*fn_down)(ParaN...)> constexpr bool InvokableDownTo     <fn_up, fn_down> = InvokableFromLeft       <fn_up, ParaN...>;
template<auto fn_up, class Ret, class...ParaN, Ret(*fn_down)(ParaN...)>	constexpr bool InvokableDownToRight<fn_up, fn_down> = InvokableFromLeftToRight<fn_up, ParaN...>;
template<auto fn_up, class Ret, class...ParaN, Ret(*fn_down)(ParaN...)>	constexpr bool InvokableDownToHand <fn_up, fn_down> = InvokableFromLeftToHand <fn_up, ParaN...>;

template<auto fn1, auto fn2> constexpr bool InvokableAmbiguous = InvokableDownTo<fn1, fn2> || InvokableDownTo<fn2, fn1>;

#pragma endregion

#pragma region Type Reference Helpers

template<class OutType> constexpr       OutType &  ref_cast(      SameSizeType<OutType> auto & in) noexcept ret_as(*(      OutType *)&in);
template<class OutType> constexpr const OutType &  ref_cast(const SameSizeType<OutType> auto & in) noexcept ret_as(*(const OutType *)&in);
template<class OutType> constexpr       OutType  reuse_cast(      SameSizeType<OutType> auto   in) noexcept ret_as(*(      OutType *)&in);
template<class OutType, class InType> requires(sizeof(OutType) <= sizeof(InType)) constexpr OutType   big_cast(InType in) noexcept ret_as(*(OutType *)&in);
template<class OutType, class InType> requires(sizeof(OutType) >= sizeof(InType)) constexpr OutType small_cast(InType in) noexcept ret_as(*(OutType *)&in);

/* --- Hand --- */

template<class AnyType>
struct Hand {
	using base  = AnyType;
	using left  = AnyType  &;
	using right = AnyType &&;
	using clap  = AnyType &&;
	static constexpr bool is_left = false;
	static constexpr bool is_right = false;
};

// Left Hand

template<class AnyType>
struct Hand<AnyType &> {
	using base  = AnyType;
	using left  = AnyType  &;
	using right = AnyType &&;
	using clap  = AnyType  &;
	static constexpr bool is_left = true;
	static constexpr bool is_right = false;
};
template<class AnyType>	constexpr AnyType && right_cast(AnyType &a) noexcept ret_as(static_cast<AnyType &&>(a));
template<class AnyType>	constexpr AnyType &   left_cast(AnyType &a) noexcept ret_as(a);

// Right Hand

template<class AnyType>
struct Hand<AnyType &&> {
	using base  = AnyType;
	using left  = AnyType  &;
	using right = AnyType &&;
	using clap  = AnyType &&;
	static constexpr bool is_left = false;
	static constexpr bool is_right = true;
};
template<class AnyType>	constexpr AnyType && right_cast(AnyType &&a) noexcept ret_as(static_cast<AnyType &&>(a));
template<class AnyType>	constexpr AnyType &   left_cast(AnyType &&a) noexcept ret_as(a);

// Clap Hand

template<class AnyStrict, class AnyType> requires(IsSame<typename Hand<AnyStrict>::base, AnyType>)
constexpr auto hand_cast(AnyType &a) noexcept -> Hand<AnyStrict>::clap ret_as(static_cast<typename Hand<AnyStrict>::clap>(a));

#pragma endregion

#pragma region Any Functional Compatible test  ////////////////////////////////////
template<class AnyCallable, class Ret, class... ParaN>
concept StaticCompatible = requires(AnyCallable f, ParaN... args) { { f(args...) } -> std::convertible_to<Ret>; };
template<class AnyCallable, class FuncType>
constexpr bool static_compatible = false;
template<class AnyCallable, class Ret, class... ParaN>
constexpr bool static_compatible<AnyCallable, Ret(ParaN...)> = StaticCompatible<AnyCallable, Ret, ParaN...>;
#pragma endregion

#pragma region DConstructor Compatible test

/* --- Single Constructor --- */

template<class AnyType, class... ParaN>
struct ConstructorOf {
	static constexpr bool as_new        = requires(ParaN... args) { new AnyType(args...); };
	static constexpr bool as_placement  = requires(ParaN... args) { new(any_require<void *>()) AnyType(args...); };
	static constexpr bool as_static     = requires(ParaN... args) { AnyType(args...); };
	static constexpr bool any_ways      = as_new || as_placement || as_static;
};
template<class AnyType>
struct ConstructorOf<AnyType, void> : ConstructorOf<AnyType> {};

/* --- Multi-Constructors --- */

template<class AnyType, class... ParaLists>
struct ConstructorsOf;
template<class AnyType>
struct ConstructorsOf<AnyType> : ConstructorOf<AnyType> {};
template<class AnyType, class OtherType>
struct ConstructorsOf<AnyType, OtherType> : ConstructorOf<AnyType, OtherType> {};
template<class AnyType, template<class...> class AnyList, class... ParaN>
struct ConstructorsOf<AnyType, AnyList<ParaN...>> {};
template<class AnyType, class OtherType, class... Others>
struct ConstructorsOf<AnyType, OtherType, Others...> : ConstructorsOf<AnyType, ConstructorsOf<OtherType>, Others...> {};
template<class AnyType, template<class...> class AnyList, class... ParaN, class... Others>
struct ConstructorsOf<AnyType, AnyList<ParaN...>, Others...> {
	static constexpr bool as_new       = ConstructorOf<AnyType, ParaN...>::as_new       && ConstructorsOf<AnyType, Others...>::as_new;
	static constexpr bool as_placement = ConstructorOf<AnyType, ParaN...>::as_placement && ConstructorsOf<AnyType, Others...>::as_placement;
	static constexpr bool as_static    = ConstructorOf<AnyType, ParaN...>::as_static    && ConstructorsOf<AnyType, Others...>::as_static;
	static constexpr bool any_ways     = ConstructorOf<AnyType, ParaN...>::any_ways     && ConstructorsOf<AnyType, Others...>::any_ways;
};

/* --- Single Constructor Assertions --- */

template<class AnyType, class... ParaN> concept ConstructorNewAssert        = ConstructorOf<AnyType, ParaN...>::as_new;
template<class AnyType, class... ParaN> concept ConstructorPlacementAssert  = ConstructorOf<AnyType, ParaN...>::as_placement;
template<class AnyType, class... ParaN> concept ConstructorStaticAssert     = ConstructorOf<AnyType, ParaN...>::as_static;
template<class AnyType, class... ParaN> concept ConstructorAssert           = ConstructorOf<AnyType, ParaN...>::any_ways;

/* --- Multi Constructors - Assertions --- */

template<class AnyType, class... ParaNList> concept ConstructorsNewAssert        = ConstructorsOf<AnyType, ParaNList...>::as_new;
template<class AnyType, class... ParaNList> concept ConstructorsPlacementAssert  = ConstructorsOf<AnyType, ParaNList...>::as_placement;
template<class AnyType, class... ParaNList> concept ConstructorsStaticAssert     = ConstructorsOf<AnyType, ParaNList...>::as_static;
template<class AnyType, class... ParaNList> concept ConstructorsAssert           = ConstructorsOf<AnyType, ParaNList...>::any_ways;

/* --- Destructor --- */

template<class AnyType>
concept DestructorEffectless =
	std::is_pointer_v<AnyType> ||
	std::is_reference_v<AnyType> ||
	std::is_trivially_destructible_v<AnyType>;
template<class AnyType>
concept DestructorEffective = !DestructorEffectless<AnyType>;

#pragma endregion

#pragma region Array
template<class AnyType, SizeT Len>
struct Array {
	AnyType data[Len]{ 0 };
public:
	using CharType = AnyType;
public:
	constexpr Array() {}
	constexpr Array(Nu) {}
	template<class...Para>
	constexpr Array(Para...s) requires((sizeof...(Para)) == Len) : data{ s... } {}
	constexpr Array(const AnyType(&s)[Len]) { for (SizeT i = 0; i < Len; ++i) data[i] = s[i]; }
	constexpr Array(const Array &s) { for (SizeT i = 0; i < Len; ++i) data[i] = s.data[i]; }
public:
	constexpr SizeT Length() const ret_as(Len);
	constexpr auto begin() ret_as(data);
	constexpr auto begin() const ret_as(data);
	constexpr auto end() ret_as(data + Len);
	constexpr auto end() const ret_as(data + Len);
	template<class NewType>
	constexpr Array<NewType, Len> &cast() ret_as(ref_cast<Array<NewType, Len>>(self));
	template<class NewType>
	constexpr const Array<NewType, Len> &cast() const ret_as(ref_cast<const Array<NewType, Len>>(self));
public:
	constexpr operator const AnyType *() const ret_as(data);
	constexpr auto &operator*() ret_as(data[0]);
	constexpr auto &operator*() const ret_as(data[0]);
	constexpr auto &operator[](SizeT index) ret_as(data[index]);
	constexpr auto &operator[](SizeT index) const ret_as(data[index]);
	template<SizeT Len1> constexpr auto operator+(const AnyType(&s)[Len1]) const {
		AnyType result[Len + Len1]{};
		for (SizeT i = 0; i < Len; ++i) result[i] = data[i];
		for (SizeT j = 0; j < Len1; ++j) result[Len + j] = s[j];
		return Array<AnyType, Len + Len1>(result);
	}
	template<SizeT Len1> constexpr auto operator+(const Array<AnyType, Len1> &s) const ret_as(operator+(s.data));
	constexpr bool operator==(const AnyType(&s)[Len]) const {
		for (SizeT i = 0; i < Len; ++i)
			if (data[i] != s[i])
				return false;
		return true;
	}
	constexpr bool operator!=(const AnyType(&s)[Len]) const ret_as(!operator==(s));
	constexpr bool operator==(const Array<AnyType, Len> &s) const ret_as(operator==(s.data));
	constexpr bool operator!=(const Array<AnyType, Len> &s) const ret_as(operator!=(s.data));
};
template<class AnyType, SizeT Len>
constexpr auto &ArrayProxy(AnyType(&s)[Len]) ret_as(ref_cast<Array<AnyType, Len>>(s));
template<class AnyChar, SizeT Len> using LiString = Array<AnyChar, Len>;
template<SizeT Len> using LiStringA = LiString< char  , Len>;
template<SizeT Len> using LiStringW = LiString<wchar_t, Len>;
constexpr auto LiStringO = LiString("");
#pragma endregion

#pragma region Arguments List
template<class...>
class ParaList;
// No Argument
template<>
class ParaList<void> {
public:
	static constexpr SizeT Count = 0;
public:
	template<class AnyCallable>
	inline auto invoke(AnyCallable f) ret_as(f());
	template<class AnyClass, class AnyMethod>
	inline auto invoke(AnyClass &cls, AnyMethod method) ret_as((cls.*method)());
public:
	template<class AnyClass>
	inline auto constructor() ret_as(AnyClass());
	template<class AnyClass>
	inline auto new_constructor() ret_as(new AnyClass());
};
template<>
class ParaList<> : ParaList<void> {}; // Must have this alias specialization for some C/C++ exchange support
// Single Argument
template<class Type0>
class ParaList<Type0> {
	using Hand0 = Hand<Type0>;
	using Left0 = typename Hand0::left;
	using Right0 = typename Hand0::right;
	using Clap0 = typename Hand0::clap;
	Clap0 arg0;
public:
	ParaList(Type0 arg0) : arg0(hand_cast<Type0>(arg0)) {}
public:
	static constexpr SizeT Count = 1;
public:
	template<SizeT ind> requires(ind == 0)
	using type = Type0;     
public:
	template<SizeT ind> requires(ind == 0)
	inline Left0 value_left() ret_as(arg0);
	template<SizeT ind> requires(ind == 0)
	inline const Left0 value_left() const ret_as(arg0);
	template<SizeT ind> requires(ind == 0)
	inline Right0 value_right() ret_as(static_cast<Right0>(arg0));
	template<SizeT ind> requires(ind == 0)
	inline const Right0 value_right() const ret_as(static_cast<const Right0>(arg0));
	template<SizeT ind> requires(ind == 0)
	inline Clap0 value() ret_as(static_cast<Clap0>(arg0));
	template<SizeT ind> requires(ind == 0)
	inline const Clap0 value() const ret_as(static_cast<const Clap0>(arg0));
public:
	template<class AnyCallable>
	inline auto invoke(AnyCallable f) ret_as(f(value()));
	template<class AnyClass, class AnyMethod>
	inline auto invoke(AnyClass &cls, AnyMethod method) ret_as((cls.*method)(value()));
public:
	template<class AnyClass>
	inline auto constructor() ret_as(AnyClass(value()));
	template<class AnyClass>
	inline auto new_constructor() ret_as(new AnyClass(value()));
};
// Multiple Arguments
template<NotVoid Type0, NotVoid...Types>
class ParaList<Type0, Types...> {
	using Hand0 = Hand<Type0>;
	using Left0 = typename Hand0::left;
	using Right0 = typename Hand0::right;
	using Clap0 = typename Hand0::clap;
	using TypeN = ParaList<Types...>;
	using ind_seq = std::index_sequence_for<Type0, Types...>;
private:
	Clap0 arg0;
	TypeN args;
public:
	ParaList(Type0 arg0, Types... args) :
		arg0(hand_cast<Type0>(arg0)),
		args(hand_cast<Types>(args)...) {}
public:
	static constexpr SizeT Count = 1 + sizeof...(Types);
private:
	template<SizeT ind, class = void>
	struct index : TypeN::template index<ind - 1> {};
	template<class ___>
	struct index<0, ___> { using type = Type0; };
public:
	template<SizeT ind> requires(ind < Count)
	using type = typename index<ind>::type;
public:
	template<SizeT ind> requires(ind < Count)
	inline auto &value_left() {
		if constexpr (ind)
			 ret_as(args.template value_left<ind - 1>())
		else ret_as(arg0)
	}            
	template<SizeT ind> requires(ind < Count)
	inline auto &value_left() const {
		if constexpr (ind)
			 ret_as(args.template value_left<ind - 1>())
		else ret_as(arg0)
	}
	template<SizeT ind> requires(ind < Count)
	inline auto value_right() {
		if constexpr (ind)
			 ret_as(args.template value_right<ind - 1>())
		else ret_as(static_cast<Right0>(arg0))
	}
	template<SizeT ind> requires(ind < Count)
	inline auto value_right() const {
		if constexpr (ind)
			 ret_as(args.template value_right<ind - 1>())
		else ret_as(static_cast<const Right0>(arg0))
	}
	template<SizeT ind> requires(ind < Count)
	inline auto value() {
		if constexpr (ind)
			 ret_as(args.template value<ind - 1>())
		else ret_as(static_cast<Clap0>(arg0))
	}
	template<SizeT ind> requires(ind < Count)
	inline auto value() const {
		if constexpr (ind)
			 ret_as(args.template value<ind - 1>())
		else ret_as(static_cast<const Clap0>(arg0))
	}
private:
	template<class AnyCallable, SizeT... ind>
	inline auto invoke(AnyCallable f, std::index_sequence<ind...>) ret_as(f(value<ind>()...));
	template<class AnyClass, class AnyMethod, SizeT... ind>
	inline auto invoke(AnyClass &cls, AnyMethod method, std::index_sequence<ind...>) ret_as((cls.*method)(value<ind>()...));
private:
	template<class AnyClass, SizeT... ind>
	inline auto &&construct(std::index_sequence<ind...>) ret_as(AnyClass(value<ind>()...));
	template<class AnyClass, SizeT... ind>
	inline auto *new_construct(std::index_sequence<ind...>) ret_as(new AnyClass(value<ind>()...));
public:
	template<class AnyCallable>
	inline auto invoke(AnyCallable f) ret_as(invoke(f, ind_seq{}));
	template<class AnyClass, class AnyMethod>
	inline auto invoke(AnyClass &cls, AnyMethod method) ret_as(invoke(cls, method, ind_seq{}));
public:
	template<class AnyClass>
	inline auto &&construct() ret_as(construct<AnyClass>(ind_seq{}));
	template<class AnyClass>
	inline auto *new_construct() ret_as(new_construct<AnyClass>(ind_seq{}));
};
#pragma endregion

#pragma region Chain Extended Helper

template<class AnyChild, template<class = void> class AnyBase>
struct ChainBegin {
	using Parent = AnyBase<AnyChild>;
	using Child = VoidChain<AnyChild, Parent>;
	ChainBegin() = default;
	constexpr auto &__child__() requires(IsExtendedOf<Child, Parent>) ret_as(static_cast<Child &>(self));
	constexpr auto &__child__() const requires(IsExtendedOf<Child, Parent>) ret_as(static_cast<const Child &>(self));
};
template<template<class = void> class AnyBase, class AnyChild>
struct ChainNext : public AnyBase<AnyChild> {
	using Super = AnyBase<AnyChild>;
	using Shim = ChainNext<AnyBase, AnyChild>;
	using Super::Super;
	constexpr auto & __super__() requires(IsExtendedOf<Shim, Super>) ret_as(static_cast<Super &>(self));
	constexpr auto & __super__() const requires(IsExtendedOf<Shim, Super>) ret_as(static_cast<const Super &>(self));
};

template<class           AnyType> constexpr bool HasSuper     = requires { typename AnyType::Super; };
template<class           AnyType> concept        HasSuperType = HasSuper<AnyType>;
template<HasSuperType AnyChained> using              SuperOf  = typename AnyChained::Super;

template<class           AnyType> constexpr bool HasChild     = requires { typename AnyType::Child; };
template<class           AnyType> concept        HasChildType = HasChild<AnyType>;
template<HasChildType AnyChained> using              ChildOf  = typename AnyChained::Child;

template<class AnyClass, class AnyBase>
constexpr bool IsChainExtendedOf = [] {
	if  constexpr  (IsSame<AnyClass, AnyBase>) return true;
	elif constexpr (!HasSuper<AnyClass>)       return false;
	else return IsChainExtendedOf<SuperOf<AnyClass>, AnyBase>;
}();

template<class AnyFrom, class AnyTo> concept          UpChainOf = IsChainExtendedOf<AnyFrom, AnyTo>;
template<class AnyFrom, class AnyTo> concept        DownChainOf = IsChainExtendedOf<AnyTo, AnyFrom>;
template<class Type1  , class Type2> concept        SameChainOf = UpChainOf<Type1, Type2>   ||   DownChainOf<Type1, Type2>;
template<class Type1  , class Type2> constexpr int OrderChainOf = UpChainOf<Type1, Type2> ? +1 : DownChainOf<Type1, Type2> ? -1 : 0;

template<HasSuperType AnyChained> constexpr bool  IsRealChained = IsExtendedOf<AnyChained, typename AnyChained::Super>;
template<class           AnyType> concept           RealChained = IsRealChained<AnyType>;

template<class AnyFrom, class AnyTo> concept           UpCastOf = IsExtendedOf<AnyFrom, AnyTo>;
template<class AnyFrom, class AnyTo> concept         DownCastOf = IsExtendedOf<AnyTo, AnyFrom>;
template<class Type1  , class Type2> concept         SameCastOf = UpCastOf<Type1, Type2>   ||   DownCastOf<Type1, Type2>;
template<class Type1  , class Type2> constexpr int  OrderCastOf = UpCastOf<Type1, Type2> ? +1 : DownCastOf<Type1, Type2> ? -1 : 0;

template<class AnyClass>
constexpr auto further_chain(AnyClass *pThis) {
	if constexpr (HasChild<AnyClass>) {
		using Child = ChildOf<AnyClass>;
		constexpr bool has_child_ref = requires(AnyClass c) { c.__child__(); };
		misuse_assert(has_child_ref, "ChainBegin is required for further chaining");
		return &pThis->__child__();
	}
	else return pThis;
}

#pragma endregion

template<Extendable...ExtensionN>
struct MultiBaseOf : ExtensionN... {};

template<Extendable...ExtensionN>
struct OverrideFunctor;
template<Extendable Extension0>
struct OverrideFunctor<Extension0> : public Extension0 {
	using Extension0::operator();
};
template<Extendable Extension0, Extendable...ExtensionN>
struct OverrideFunctor<Extension0, ExtensionN...> : public Extension0, public OverrideFunctor<ExtensionN...> {
	using Extension0::operator();
	using OverrideFunctor<ExtensionN...>::operator();
};

#pragma region Proxy Shims

template<class AnyRef>
union ProxyView final {
private:
	AnyRef t;
public:
	ProxyView(auto &arg) : t(arg) {}
	ProxyView(const auto &arg) : t(arg) {}
	ProxyView(AnyRef &&arg) : t(right_cast(arg)) {}
	~ProxyView() {}
public:
	template<class AnyType>
	constexpr operator AnyType() ret_as((AnyType)t);
	template<class AnyType>
	constexpr operator AnyType() const ret_as((AnyType)t);
public:
	constexpr operator AnyRef &() ret_as(t);
	constexpr operator AnyRef *() ret_as(address_cast(t));
	constexpr operator const AnyRef &() const ret_as(t);
	constexpr operator const AnyRef *() const ret_as(address_cast(t));
public:
	constexpr auto &operator*() ret_as(t);
	constexpr auto *operator&() ret_as(address_cast(t));
	constexpr auto *operator->() ret_as(address_cast(t));
	constexpr auto &operator*() const ret_as(t);
	constexpr auto *operator&() const ret_as(address_cast(t));
	constexpr auto *operator->() const ret_as(address_cast(t));
};
template<class AnyType>
union ProxyView<AnyType *> final {
private:
	AnyType *ptr;
public:
	template<class OtherType>
	ProxyView(OtherType *ptr) : ptr((AnyType *)ptr) {}
public:
	constexpr operator AnyType *() ret_as(ptr);
	constexpr operator const AnyType *() const ret_as(ptr);
public:
	constexpr auto &operator *()       ret_as(*ptr);
	constexpr auto &operator *() const ret_as(*ptr);
	constexpr auto *operator &()       ret_as(&ptr);
	constexpr auto *operator &() const ret_as(&ptr);
	constexpr auto *operator->()       ret_as( ptr);
	constexpr auto *operator->() const ret_as( ptr);
};
template<class OtherType> constexpr bool IsProxyViewOf = false;
template<class RefType>   constexpr bool IsProxyViewOf<ProxyView<RefType>> = true;

template<class AnyType> concept HasBaseType = requires { typename AnyType::BaseType; };
template<HasBaseType AnyEnum> using BaseTypeOf = typename AnyEnum::BaseType;

template<class OutType, class InType>
constexpr auto safe_c_cast(const InType &c_value) {
	if constexpr (HasBaseType<OutType>) {
		 misuse_assert(IsSameSize<macro_brace0(BaseTypeOf<OutType>, InType)>, "Unsafe enum cast detected");
		 return reuse_cast<OutType>(c_value);
	}
	else return (OutType)c_value;
}
template<class SetType, class GetType>
constexpr SetType &safe_setval(SetType &set, GetType &&get) noexcept ret_as((set = (SetType)get));

template<class AnyTypePureC>
struct ProxyType {
	template<class AnyChild>
	struct CValue {
		using Super = CValue;
		using BaseType = AnyTypePureC;
		friend AnyChild;
	protected:
		mutable BaseType proxy_obj;
	public:
		CValue(const BaseType &s) noexcept : proxy_obj(s) {}
	public:
		static constexpr       AnyChild &view_cast(      BaseType &s) noexcept requires(IsExtendedOf<AnyChild, Super>) ret_as(reuse_cast<      AnyChild &>(s));
		static constexpr const AnyChild &view_cast(const BaseType &s) noexcept requires(IsExtendedOf<AnyChild, Super>) ret_as(reuse_cast<const AnyChild &>(s));
	public:
		constexpr operator         BaseType &()       noexcept ret_as(proxy_obj);
		constexpr operator   const BaseType &() const noexcept ret_as(proxy_obj);
		constexpr       BaseType & operator *()       noexcept ret_as(proxy_obj);
		constexpr const BaseType & operator *() const noexcept ret_as(proxy_obj);
		constexpr       BaseType * operator->()       noexcept ret_as(address_cast(proxy_obj));
		constexpr const BaseType * operator->() const noexcept ret_as(address_cast(proxy_obj));
	public:
		inline auto operator=(const BaseType &s) noexcept
			requires(ConstructorStaticAssert<AnyChild, BaseType>) {
			AnyChild last{ (const BaseType &)proxy_obj };
			proxy_obj = s;
			return right_cast(last);
		}
	};
	template<class AnyChild>
	struct CStruct : protected AnyTypePureC {
		using Super = CStruct;
		using BaseType = AnyTypePureC;
		friend AnyChild;
	private:
		static constexpr bool has_self_size() noexcept ret_as(requires(AnyChild c) { c.SelfSize; });
	public:
		constexpr CStruct(const BaseType &s) noexcept : BaseType(s) {}
		constexpr CStruct(Nu) noexcept : BaseType({ 0 }) {}
		constexpr CStruct() : BaseType({ 0 }) {
			if constexpr (has_self_size())
				 static_cast<AnyChild *>(this)->SelfSize(sizeof(AnyChild));
		}
	public:
		static constexpr       AnyChild &view_cast(      BaseType &s) noexcept requires(IsExtendedOf<AnyChild, Super>) ret_as(reuse_cast<      AnyChild &>(s));
		static constexpr const AnyChild &view_cast(const BaseType &s) noexcept requires(IsExtendedOf<AnyChild, Super>) ret_as(reuse_cast<const AnyChild &>(s));
	public:
		constexpr operator         BaseType &()       noexcept ret_as(self);
		constexpr operator   const BaseType &() const noexcept ret_as(self);
		constexpr       BaseType & operator *()       noexcept ret_as(self);
		constexpr const BaseType & operator *() const noexcept ret_as(self);
		constexpr       BaseType * operator->()       noexcept ret_as(this);
		constexpr const BaseType * operator->() const noexcept ret_as(this);
		constexpr       BaseType * operator &()       noexcept ret_as(this);
		constexpr const BaseType * operator &() const noexcept ret_as(this);
	public:
		inline auto operator=(const BaseType &s) noexcept
			requires(ConstructorStaticAssert<AnyChild, BaseType>) {
			AnyChild last{ (const BaseType &)self };
			(BaseType &)self = s;
			return right_cast(last);
		}
	};
};

template<class AnyChild, class AnyStruct>
using ProxyCStruct = typename ProxyType<AnyStruct>::template CStruct<AnyChild>;

#pragma endregion

#pragma region Exception
class Exception {
	const char
		*lpFile = O,
		*lpFunc = O,
		*lpSent = O;
	Int32U
		uLine = 0,
		uErrCode = 0;
public:
	Exception() {}
	Exception(const char *lpszFile, const char *lpszFunc, const char *lpszSent,
			  Int32U nLine, Int32U uErrCode = 0) :
		lpFile(lpszFile), lpFunc(lpszFunc), lpSent(lpszSent),
		uLine(nLine), uErrCode(uErrCode) {}
public:
	inline auto File()      const ret_as(lpFile);
	inline auto Function()  const ret_as(lpFunc);
	inline auto Sentence()  const ret_as(lpSent);
	inline auto Line()      const ret_as(uLine);
	inline auto ErrorCode() const ret_as(uErrCode);
public:
	inline operator bool() const ret_as(lpSent);
};
#pragma endregion

#pragma region Lambda ////////////////////////////////////
/* --- LambdaBase --- */
template<class RetType, class... ParaN>
struct LambdaBase {
	virtual ~LambdaBase() = default;
	virtual RetType operator()(ParaN ...) = 0;
};
template<class PackType, class RetType, class... ParaN>
class FunctionPackage : public LambdaBase<RetType, ParaN...> {
	mutable PackType func;
public:
	FunctionPackage(PackType &f) : func(f) {}
	RetType operator()(ParaN ...args) override {
		static_assert(static_compatible<PackType, RetType(ParaN...)>, "Argument list uncompatible");
		// if constexpr (IsPointer<PackType>)
		return func(args...);
	}
};
/* --- Lambda --- */
template<class...>
class Lambda;
template<class RetType, class... ParaN>
class Lambda<RetType(ParaN...)> final {
private:
	mutable LambdaBase<RetType, ParaN...> *func = O;
	mutable bool bAllocated = false;
public:
	Lambda() {}
	Lambda(Nu) {}
	Lambda(const Lambda &f) : func(f.func) {}
public:
	template<class Type>
	Lambda(Type &f) : func(new FunctionPackage<Type, RetType, ParaN...>(f)), bAllocated(true) {}
	template<class Type>
	Lambda(Type f) : func(new FunctionPackage<Type, RetType, ParaN...>(f)), bAllocated(true) {}
	~Lambda() { if (func && bAllocated) delete func, func = O; }
public:
	inline operator bool() const ret_as(!func);
	inline bool operator!=(Nu) const ret_as(func);
	inline bool operator==(Nu) const ret_as(!func);
	inline Lambda operator&() retself;
	inline const Lambda operator&() const retself;
	inline RetType operator()(ParaN...args) const ret_as(func(args...));
	inline auto &operator=(const Lambda &f) const noexcept ret_to_self(func = f.func, bAllocated = false);
	inline auto &operator=(const Lambda &f) noexcept ret_to_self(func = f.func, bAllocated = false);
	inline auto &operator=(Lambda &&f) noexcept ret_to_self(func = f.func, f.func = O, bAllocated = true);
};
template<class...FuncTypes>
using fn = Lambda<FuncTypes...>;
#pragma endregion

#pragma region Enum

template<class       AnyType> concept HasEnumType = requires { typename AnyType::EnumType; };
template<HasEnumType AnyEnum> using    EnumTypeOf = typename AnyEnum::EnumType;

template<class AnyType>
struct EnumBase;

template<class AnyType> constexpr bool IsEnumBased = IsExtendedOf<AnyType, EnumBase<AnyType>>;
template<class AnyType> concept          EnumBased = IsEnumBased<AnyType>;

template<class AnyChild, class AnyBase, bool = IsEnumBased<AnyBase>>
struct EnumClassShim;

template<class AnyType>
constexpr bool IsEnumAtom = []() {
	if constexpr (HasSuperType<AnyType> && HasEnumType<AnyType>)
		 return IsExtendedOf<AnyType, EnumClassShim<EnumTypeOf<AnyType>, SuperOf<AnyType>>>;
	else return false;
}();
template<class AnyType>
concept EnumAtomType = IsEnumAtom<AnyType>;

template<class AnyType> constexpr bool IsEnum = IsEnumBased<AnyType> || IsEnumAtom<AnyType>;
template<class AnyType> concept EnumType = IsEnum<AnyType>;

template<EnumType AnyEnum>
using SuperOfEnum = SuperOf<EnumTypeOf<AnyEnum>>;

template<EnumType AnyEnum>
constexpr bool HasSuperEnum = ([]() {
	if constexpr (HasSuperType<AnyEnum>)
		return IsEnumBased<SuperOfEnum<AnyEnum>>;
	return false;
})();

template<class AnyEnum , class AnyBase > concept          UpCastOfEnum =    UpChainOf<EnumTypeOf<AnyEnum >, EnumTypeOf<AnyBase >>;
template<class AnyEnum , class AnyBase > concept        DownCastOfEnum =  DownChainOf<EnumTypeOf<AnyEnum >, EnumTypeOf<AnyBase >>;
template<class AnyEnum , class AnyBase > constexpr int OrderCastOfEnum = OrderChainOf<EnumTypeOf<AnyEnum >, EnumTypeOf<AnyBase >>;
template<class AnyEnum1, class AnyEnum2> concept       SameChainOfEnum =  SameChainOf<EnumTypeOf<AnyEnum1>, EnumTypeOf<AnyEnum2>>;

template<EnumType AnyEnum> constexpr bool IsPureEnum = IsSameSize<AnyEnum, BaseTypeOf<AnyEnum>>;
template<class AnyType> concept PureEnumType = IsPureEnum<AnyType>;

template<EnumType AnyEnum, bool = HasSuperEnum<AnyEnum>>
struct HasDefaultEnumProto;
template<EnumType AnyEnum>
struct HasDefaultEnumProto<AnyEnum, true> : OfValue<true> {};
template<EnumType AnyEnum>
struct HasDefaultEnumProto<AnyEnum, false> : OfValue<requires { AnyEnum::Default; }> {};
template<EnumType AnyEnum>
constexpr bool HasDefaultEnum = ValueOf<HasDefaultEnumProto<AnyEnum>>;

template<EnumType AnyEnum, bool = HasSuperEnum<AnyEnum>>
struct DefaultEnumValueProto;
template<EnumType AnyEnum>
struct DefaultEnumValueProto<AnyEnum, true> : OfValue<ValueOf<DefaultEnumValueProto<SuperOfEnum<AnyEnum>>>> {};
template<EnumType AnyEnum>
struct DefaultEnumValueProto<AnyEnum, false> : OfValue<AnyEnum::Default.yield()> {};

template<EnumType AnyEnum>
	requires(HasDefaultEnum<AnyEnum>)
constexpr auto DefaultEnumAtom = AnyEnum::value_cast(ValueOf<DefaultEnumValueProto<AnyEnum>>);

template<EnumType AnyEnum>
	requires(HasDefaultEnum<AnyEnum>)
constexpr auto DefaultEnumValue = ValueOf<DefaultEnumValueProto<AnyEnum>>;

template<EnumType AnyEnum1, EnumType AnyEnum2>
constexpr auto enum_result_cast(BaseTypeOf<AnyEnum1> v) {
	constexpr int order = OrderCastOfEnum<AnyEnum1, AnyEnum2>;
	static_assert(order != 0, "Different branches of enums cannot summon safe result");
	if constexpr (order > 0)
		 return AnyEnum1::value_cast(v);
	else return AnyEnum2::value_cast(v);
}

template<class AnyChild, class AnyBase>
struct EnumClassShim<AnyChild, AnyBase, false> : EnumBase<AnyChild> {
	using EnumType = AnyChild;
	using BaseType = AnyBase;
	using ShimType = EnumClassShim;
	using Super    = AnyBase;
protected:
	BaseType value;
	friend AnyChild;
	constexpr EnumClassShim(BaseType v) : value(v) {}
	/* DUMMY, only for macro */ constexpr BaseType operator=(BaseType a) const ret_as(a);
public:
	constexpr EnumClassShim() : value(DefaultEnumValue<AnyChild>) {}
public:
	constexpr BaseType yield() const noexcept ret_as(value);
	static constexpr AnyChild value_cast(BaseType v) ret_as(v);
public:
	inline auto *operator&() ret_as(&value);
	/* adjust atom into set */ constexpr operator AnyChild() const ret_as(value);
	constexpr explicit operator BaseType() const noexcept ret_as(value);
	constexpr bool operator==(SameChainOfEnum<AnyChild> auto e) const ret_as(this->yield() == e.yield());
	constexpr bool operator!=(SameChainOfEnum<AnyChild> auto e) const ret_as(this->yield() != e.yield());
	inline AnyChild operator=(DownCastOfEnum<AnyChild> auto v) ret_as(this->value = v.yield());
};
template<class AnyChild, class AnyBase>
struct EnumClassShim<AnyChild, AnyBase, true> : EnumClassShim<AnyChild, BaseTypeOf<AnyBase>> {
	using EnumType = AnyChild;
	using BaseType = BaseTypeOf<AnyBase>;
	using ShimType = EnumClassShim<AnyChild, BaseType>;
	using Super = AnyBase;
protected:
	friend AnyChild;
	constexpr EnumClassShim(BaseType v) : ShimType(v) {}
	/* DUMMY, only for macro */ using ShimType::operator=;
public:
	constexpr EnumClassShim(AnyBase v) : ShimType(v.yield()) {}
	constexpr EnumClassShim(DownCastOfEnum<AnyChild> auto v) : ShimType(v.yield()) {}
	constexpr EnumClassShim() : ShimType(DefaultEnumValue<AnyChild>) {}
public:
	static constexpr AnyChild value_cast(BaseType v) ret_as(v);
	template<class AnyEnum> requires DownCastOfEnum<AnyEnum, AnyChild>
	constexpr AnyEnum down_cast() const ret_as(AnyEnum::value_cast(this->yield()));
public:
	using ShimType::operator&;
	/* adjust atom into set */ constexpr operator AnyChild() const ret_as(this->yield());
};

template<class AnyChild, class AnyBase>
struct EnumFlagsShim : EnumClassShim<AnyChild, AnyBase> {
	using ShimType = EnumClassShim<AnyChild, AnyBase>;
	using BaseType = typename ShimType::BaseType;
protected:
	friend AnyChild;
	using ShimType::ShimType;
	using ShimType::operator=;
public: // Flags operators
	using ShimType::operator&;

	constexpr bool operator<=(DownCastOfEnum<AnyChild> auto e) const ret_as(BaseType(this->yield() & e.yield()) == this->yield());
	constexpr bool operator>=(DownCastOfEnum<AnyChild> auto e) const ret_as(BaseType(this->yield() & e.yield()) == e.yield());
	constexpr auto operator~() const -> AnyChild ret_as(BaseType(~this->yield()));

	constexpr auto operator|(EnumType auto e) const ret_as(enum_result_cast<AnyChild, decltype(e)>(BaseType(this->yield() | e.yield())));
	constexpr auto operator&(EnumType auto e) const ret_as(enum_result_cast<AnyChild, decltype(e)>(BaseType(this->yield() & e.yield())));
	constexpr auto operator^(EnumType auto e) const ret_as(enum_result_cast<AnyChild, decltype(e)>(BaseType(this->yield() ^ e.yield())));
	constexpr auto operator-(EnumType auto e) const ret_as(enum_result_cast<AnyChild, decltype(e)>(BaseType(this->yield() & ~e.yield())));

	inline AnyChild operator|=(DownCastOfEnum<AnyChild> auto e) ret_as(this->value |= e.yield());
	inline AnyChild operator&=(DownCastOfEnum<AnyChild> auto e) ret_as(this->value &= e.yield());
	inline AnyChild operator^=(DownCastOfEnum<AnyChild> auto e) ret_as(this->value ^= e.yield());
	inline AnyChild operator-=(DownCastOfEnum<AnyChild> auto e) ret_as(this->value &= ~e.yield());
};

template<class AnyChild>
struct EnumBase {
	/** Add public features here **/
	/*** Enumerated item parser ***/
	/*** reflect to string ***/
	/*** flags analyser ***/
};

#pragma endregion

#pragma region AssertOperators
enum class AssertOps {
	Default     , // arg => false  ( convert to bool )
	Bigger      , // arg >  val
	BigEqual    , // arg >= val
	Smaller     , // arg <  val
	SmallEqual  , // arg <= val
	Equal       , // arg == val
	Nequal      , // arg != val
	ByErrorCode , // arg <=> val  ( val(   ) != 0    )
	CustomTest    // arg  => val  ( val(arg) == true )
};

template<AssertOps ops>
constexpr auto AssertFaultMap = ValueMap<ops,
	AssertOps::   Bigger  , LiString(" <= "),
	AssertOps::   BigEqual, LiString(" < " ),
	AssertOps:: Smaller   , LiString(" >= "),
	AssertOps:: SmallEqual, LiString(" > " ),
	AssertOps::      Equal, LiString(" != "),
	AssertOps::     Nequal, LiString(" == "),
	AssertOps::ByErrorCode, LiString(" <=> "),
	AssertOps::CustomTest , LiString(""),
	AssertOps::Default    , LiString(" => false ")
>;

template<AssertOps ops, auto val>
constexpr bool assert_oeperator(auto arg) {
	     if constexpr   (ops == AssertOps::   Bigger  )  return val <  arg;
	else if constexpr   (ops == AssertOps::   BigEqual)  return val <= arg;
	else if constexpr   (ops == AssertOps:: Smaller   )  return val >  arg;
	else if constexpr   (ops == AssertOps:: SmallEqual)  return val >= arg;
	else if constexpr   (ops == AssertOps::      Equal)  return val == arg;
	else if constexpr   (ops == AssertOps::     Nequal)  return val != arg;
	else if constexpr   (ops == AssertOps::ByErrorCode)  return val() != 0;
	else if constexpr   (ops == AssertOps::CustomTest )  return val( arg );
	else { static_assert(ops == AssertOps::Default    ); return (bool)arg; }
}

template<AssertOps ops, auto val = true, auto val_str = LiStringO>
struct AssertOperator {
	constexpr bool operator()(auto arg) const ret_as(assert_oeperator<ops, val>(arg));
	static constexpr auto FaultString = AssertFaultMap<ops> + val_str;
};
template<class AnyType> constexpr bool IsAssertOperatorType = false;
template<AssertOps ops, auto val, auto val_str>
constexpr bool IsAssertOperatorType<AssertOperator<ops, val, val_str>> = true;
template<class AnyType> concept AssertOperatorType = IsAssertOperatorType<AnyType>;
template<auto assert> constexpr bool IsAssertOperator = IsAssertOperatorType<decltype(assert)>;

constexpr auto AssertTrue     = AssertOperator<AssertOps::Default                      >();
constexpr auto AssertPositive = AssertOperator<AssertOps::Bigger  , 0, LiString("0")   >();
constexpr auto AssertNotZero  = AssertOperator<AssertOps::Nequal  , 0, LiString("0")   >();
constexpr auto AssertNatural  = AssertOperator<AssertOps::BigEqual, 0, LiString("0")   >();
constexpr auto AssertNotNull  = AssertOperator<AssertOps::Nequal  , O, LiString("null")>();
template<auto fault_val, auto fault_str>
constexpr auto AssertFaultValue = AssertOperator<AssertOps::Nequal, fault_val, fault_str>();
#pragma endregion

template<auto file, auto name, class AnyType>
class BridgeAPI;
template<auto file, auto name, class AnyRet, class...ParaN>
class BridgeAPI<name, file, AnyRet(*)(ParaN...)> {
	using API_Type = AnyRet(*)(ParaN...);
public:
	template<API_Type fn> requires(fn != O)
		class Ref {
		public: // API prototype infomations proxy
			template<class NewAPI>
			struct PointerProxy {
				static constexpr auto  Name    = name;
				static constexpr IntPU Address = (IntPU)(void *)fn;
				constexpr API_Type operator*() const ret_as(fn);
				constexpr NewAPI   operator&() const ret_as(NewAPI::Reflective);
			};
		public: // reflectors
			template<AssertOperatorType auto assert, auto GetLastError = O, class NewRet = AnyRet>
				requires(NotVoid<AnyRet>)
			struct AssertReturn {
				static constexpr NewRet Reflective(ParaN...args) {
					if (auto ret = fn(right_cast(args)...); assert(ret))
						return (NewRet)ret; /* can be void */
					throw Exception(file, name, name + assert.FaultString, __LINE__,GetLastError ? (Int32)GetLastError() : 0);
				}
				constexpr auto operator()(ParaN...args) const ret_as(Reflective(right_cast(args)...));
			};
			struct Passby { constexpr AnyRet operator()(ParaN...args) const { return fn(args...); } };
			struct NoReturn { [[noreturn]] constexpr void operator()(ParaN...args) const { fn(args...); } };
	};
};

}
