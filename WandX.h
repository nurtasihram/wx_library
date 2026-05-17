#pragma once

#ifndef __cplusplus
#	error This project requires C++20 compilation.
#elif __cplusplus < 202002L && defined(_MSC_VER)
#	error This project requires C++20 or later. For MSVC may need open /Zc:__cplusplus option
#elif __cplusplus < 202002L
#	error This project requires C++20 or later.
#endif

#if defined(_MSC_VER) && !defined(__clang__) && (!defined(_MSVC_TRADITIONAL) || _MSVC_TRADITIONAL)
#	error This project requires a C++20 compliant preprocessor. For MSVC may need open /Zc:preprocessor option
#endif

#pragma region Macros Self-Helpers
// macro direct operators
#define	_macro_cat_(a, b)  a ## b
#define _macro_str_(x)    #x
// macro argument counter
#define _macro_ret_13_(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, ...) _13
#define _macro_seq_12_ 12, 11, 10,  9,  8,  7,  6,  5,  4,   3,   2,   1,   0
// macro cushion
#define macro_brace0(...)   __VA_ARGS__
#define macro_brace1(...) ( __VA_ARGS__ )
#define macro_brace2(...) { __VA_ARGS__ }
#define macro_brace3(...) < __VA_ARGS__ >
#define macro_kill_brace0(arg) macro_brace0(macro_brace0 arg)
// macro invoker
#define macro_call(func, ...) macro_brace0(func(__VA_ARGS__))
#define macro_expand(...)  __VA_ARGS__
#define macro_void(...) 
// macro indirect operators
#define macro_cat(a, b)  macro_call(_macro_cat_, a, b)
#define macro_str(x)     macro_call(_macro_str_, x)
#define macro_narg(...)  macro_call(_macro_ret_13_, macro_brace0() __VA_ARGS__, _macro_seq_12_)
// macro argument counter wrappers
#define macro_nameN(name, ...) macro_cat(name, macro_narg(__VA_ARGS__))
#define macro_funcN(name, ...) macro_call(macro_nameN(name, __VA_ARGS__), __VA_ARGS__)
#pragma endregion

#pragma region Macros Of C++ Keywords Alias
// alias conditional branch
#define elif else if 
// alias return
#define ret_as(...)       {       return __VA_ARGS__; }
#define ret_to(line, ...) { line; return __VA_ARGS__; }
// alias static assert
#define misuse_assert(cond, note) { static_assert(cond , "Misused: "      note); }
#define misdef_assert(cond, note) { static_assert(cond , "Misdefined: "   note); }
#define wx_uncallable               misuse_assert(false, "Uncallable function")
#define puretype_assert(type, ref_type) static_assert(IsSameSize<type, ref_type>, "Pure type must be the same size as its reference type")
// alias type
#define alias_of_type(alias, proto_name) using alias = proto_name
#pragma endregion

#pragma region Macros Of Static Reflection
/* Macro string helpers */
#if defined(UNICODE) || defined(_UNICODE)
#	define T(str) TEXT(str)
#else
#	define T(str) TEXT(str)
#endif
/* Macro static reflection */
#define ref_member(name) \
template <class AnyClass> class member_##name##_of { \
    template<class AnyType> static auto ist(int) -> decltype(any_require<typename AnyType::name>(), std::true_type()); \
    template<class AnyType> static auto ist(...) -> std::false_type; \
    template<class AnyType> static auto adr(int) -> decltype(&AnyType::name, std::true_type()); \
    template<class AnyType> static auto adr(...) -> std::false_type; \
    template<class AnyType, class Ret, class... Args> \
    static auto cmp(Ret(*)(Args...)) -> \
        std::is_convertible<decltype(any_require<AnyType>().name(any_require<Args>()...)), Ret>; \
    template<class AnyType, class Ret, class... Args> \
    static auto cmp(Ret(AnyType::**)(Args...)) -> \
        std::is_convertible<decltype(AnyType::name(any_require<Args>()...)), Ret>; \
    template<class AnyType> \
    static auto cmp(...) -> std::false_type; \
public: \
    static constexpr bool is_type = decltype(ist<AnyClass>(0))::value; \
    static constexpr bool is_addressable = decltype(adr<AnyClass>(0))::value; \
    static constexpr bool is_existed = is_type || is_addressable; \
    template<class AnyType> \
    static constexpr bool compatible_to = \
        decltype(cmp<AnyClass>(any_require<AnyType *>()))::value; }
#pragma endregion

#pragma region Macros Of Class Member IDL
#	define  wx_class_prop_set(type, name, set) inline auto&name(type value) ret_to_self(macro_kill_brace0(set))
#	define  wx_class_prop_get(type, name, get) inline type name(          ) const { macro_kill_brace0(get); }

#	define  class_prop_getas(type, name, get) wx_class_prop_get(type, name, (return get))
#	define  class_prop_getto(type, name, get) wx_class_prop_get(type, name, (ret_to get))
#	define  class_prop_getof(type, name, get) wx_class_prop_get(type, name, (type value; macro_kill_brace0(get); return value))

#	define  class_prop_set(type, name, set) wx_class_prop_set(type, name, set)
#	define  class_prop_get(type, name, d, get) macro_call(macro_cat(class_prop_get, d), type, name, get)

#	define  class_prop_map(type, name, d, get, set) \
			class_prop_get(type, name, d, get); \
			class_prop_set(type, name, set)

#	define  class_method(name, ret, arg, body) inline ret name arg ret_##body
#pragma endregion

#pragma region Macros Of Proxy Shim
// proxy struct
#define proxy_struct(name, struct_name) \
    struct name final : WandX::ProxyCStruct<name, struct_name>
// proxy self-size
#define proxy_prop_size(proto_name, type) \
    public:    proxy_prop_get(SelfSize, proto_name, type); \
    protected: proxy_prop_set(SelfSize, proto_name, size_t); friend struct CStruct
// proxy property
#define proxy_prop_set(name, proto_name, type) \
    inline auto&name(type value) ret_to_self(safe_setval(CStruct::proto_name, value))
#define proxy_prop_get(name, proto_name, type) \
    inline auto name(          ) const ret_as(WandX::safe_c_cast<type>(CStruct::proto_name))
#define proxy_prop(name, proto_name, type_in, type_out) \
    proxy_prop_set(name, proto_name, type_in ); \
    proxy_prop_get(name, proto_name, type_out)
#define proxy_prop_sync(name, proto_name, type)\
    proxy_prop    (name, proto_name, type, type)
// proxy array property
#define proxy_prop_set_arr(name, proto_name, type) \
    inline auto &name(const Array<type, ArrayCountOf(&CStruct::proto_name)> &arr)  ret_to_self(ArrayProxy(CStruct::proto_name).cast<type>() = arr);
#define proxy_prop_get_arr(name, proto_name, type) \
    inline auto &name(                                                        ) const ret_as(ArrayProxy(CStruct::proto_name).cast<type>());
#define proxy_prop_arrc(name, proto_name, type) \
    proxy_prop_set_arr(name, proto_name, type); \
    proxy_prop_get_arr(name, proto_name, type)
// proxy string fixed property
#define proxy_prop_set_sfx(name, proto_name) \
    inline auto&name(const String &str) ret_to_self(WandX::Copy(CStruct::proto_name, str))
#define proxy_prop_get_sfx(name, proto_name) \
    inline auto name() const ret_as(CString(CStruct::proto_name, ArrayCountOf(CStruct::proto_name)))
// proxy view
#define proxy_basetype(name, base, ...) \
    protected: mutable base proxy_obj{ __VA_ARGS__ }; \
    public: name() {} name(base obj) : proxy_obj(obj) {} \
    inline       name yield(base obj)       ret_to(name last = proxy_obj; proxy_obj = obj, right_cast(last)); \
    inline const name yield(base obj) const ret_to(name last = proxy_obj; proxy_obj = obj, right_cast(last)); \
    inline Nu operator=(Nu) ret_to(proxy_obj = O, O); \
    inline operator base() const ret_as(proxy_obj); \
    friend union WandX::ProxyView<name>
// 
//#define use_public_super() public: using Super = 
#define class_extended(name, parent)       class name : public parent
#define class_super_constructor()          using Super::Super
#define class_chain_begin(name)            template<class AnyChild> class name : public ChainBegin<AnyChild, name>
#define class_chain_node(name, parent)     template<class AnyChild> class name : public ChainBegin<AnyChild, name>, public parent<name>
#define class_chain_end(name, parent)      class name : public parent<name>
#pragma endregion

#pragma region Macros Of Enum 
#define enum_shim(type, name, base) WandX::Enum##type##Shim<name, base>
#define enum_base(type, name, base, ...)                              \
struct name : public enum_shim(type, name, base) {                    \
    using ShimType = enum_shim(type, name, base)                 ;    \
    using ShimType::ShimType                                     ;    \
    using typename ShimType::Super                               ;    \
    using typename ShimType::BaseType                            ;    \
    static constexpr ShimType                      __VA_ARGS__   ;    \
    static constexpr BaseType EnumEntries     []{  __VA_ARGS__ } ;    \
    static constexpr char     EnumProtoString []{ #__VA_ARGS__ } ;    \
    static constexpr char     EnumName        []{  #name       } ; }; \
    puretype_assert(name, base)
#define enum_class(name, base, ...) enum_base(Class, name, base, __VA_ARGS__)
#define enum_flags(name, base, ...) enum_base(Flags, name, base, __VA_ARGS__)
#pragma endregion

#pragma region Macros Of Chain Extended Helper
// alias key-word
#define self     macro_brace1(*this)
#define pself    macro_brace1( this)
#define child    macro_brace1( this->__child__())
#define super    macro_brace1( this->__super__())
#define pchild   macro_brace1(&this->__child__())
#define psuper   macro_brace1(&this->__super__())
// alias return
#define retself           {              return self ; }
#define retchild          {              return child; }
#define retsuper          {              return super; }
#define ret_to_self(...)  { __VA_ARGS__; return self ; }
#define ret_to_child(...) { __VA_ARGS__; return child; }
#pragma endregion

#pragma region Macros Of Exception System throw
/* exception answer */
#define wx_answer           int
#define wx_answer_ignore    0
#define wx_answer_retry     1
#define wx_answer_abort     throw
#pragma endregion

#ifndef WANDX_CPPM_EXPORT_NATIVE
import WandX;
using namespace WandX;
#else
#	undef WANDX_CPPM_EXPORT_NATIVE
#endif
