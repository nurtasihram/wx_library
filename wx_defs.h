#pragma once

#ifndef __cplusplus
#	error This project requires C++20 compilation.
#elif __cplusplus < 202002L && defined(_MSC_VER)
#	error This project requires C++20 or later. For MSVC may need open /Zc:__cplusplus option
#elif __cplusplus < 202002L
#	error This project requires C++20 or later.
#endif

#include <cstdint>
#include <functional>

/* Macro helpers */
#define _M_(...) __VA_ARGS__ 
#define _B_(...) { __VA_ARGS__ }
#define _MACRO_CALL(func, ...) func(__VA_ARGS__)

/* Macro string helpers */
#define STROFA(note) #note
#define STROFW(note) L ## #note
#define _LSTR(str) L##str
#define LSTR(str) _MACRO_CALL(_LSTR, str)
#if defined(UNICODE) || defined(_UNICODE)
#	define T(str) LSTR(str)
#else
#	define T(str) str
#endif
#define STROF(note) T(#note)

/* Macro conditional branch */
#define if_c if constexpr
#define elif_c elif constexpr
#define elif else if 
#define _if(...) __VA_ARGS__ ? 
#define _else :
#define _elif(...) : __VA_ARGS__ ?
#define _return

/* Macro reflector */
#define self (*this)
#define retself return self
#define reflect_as(...) { return __VA_ARGS__; }
#define reflect_to(line, ...) { line; return __VA_ARGS__; }
#define reflect_to_self(...)  { __VA_ARGS__; retself; }

/* Macro static assert */
#define misuse_assert(cond, note) static_assert(cond, "Misused: " note)
#define misdef_assert(cond, note) static_assert(cond, "Misdefined: " note)

/* Macro static reflection */
#pragma region SFINAE Type Helper
#define use_member(name) \
template <class AnyClass> class member_##name##_of { \
	template<class AnyType> static auto ist(int) -> decltype(std::declval<typename AnyType::name>(), std::true_type()); \
	template<class AnyType> static auto ist(...) -> std::false_type; \
	template<class AnyType> static auto adr(int) -> decltype(&AnyType::name, std::true_type()); \
	template<class AnyType> static auto adr(...) -> std::false_type; \
	template<class AnyType, class Ret, class... Args> \
	static auto cmp(Ret(*)(Args...)) -> \
		std::is_convertible<decltype(std::declval<AnyType>().name(std::declval<Args>()...)), Ret>; \
	template<class AnyType, class Ret, class... Args> \
	static auto cmp(Ret(AnyType::**)(Args...)) -> \
		std::is_convertible<decltype(AnyType::name(std::declval<Args>()...)), Ret>; \
	template<class AnyType> \
	static auto cmp(...) -> std::false_type; \
public: \
	static constexpr bool is_type = decltype(ist<AnyClass>(0))::value; \
	static constexpr bool is_addressable = decltype(adr<AnyClass>(0))::value; \
	static constexpr bool is_existed = is_type || is_addressable; \
	template<class AnyType> \
	static constexpr bool compatible_to = \
		decltype(cmp<AnyClass>(std::declval<AnyType *>()))::value; }
#define subtype_branch(name) \
template<class AnyType, class OtherType> \
static auto __subtype_branchof_##name(int) -> typename AnyType::name; \
template<class AnyType, class OtherType> \
static auto __subtype_branchof_##name(...) -> OtherType; \
template<class AnyType, class OtherType> \
using subtype_branchof_##name = \
	decltype(__subtype_branchof_##name<AnyType, OtherType>(0))
#pragma endregion

using Null = decltype(nullptr);
constexpr inline Null O = nullptr;
