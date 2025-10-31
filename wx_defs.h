﻿#pragma once

#ifndef __cplusplus
#	error This project requires C++20 compilation.
#elif __cplusplus < 202002L
#	error This project requires C++20 or later. For MSVC may need open /Zc:__cplusplus option
#endif

#include <cstdint>
#include <functional>

#include "wx__rm.inl"

#define _M_(...) __VA_ARGS__ 
#define _B_(...) { __VA_ARGS__ }
#define _MACRO_CALL(func, ...) func(__VA_ARGS__)

#define STROF(note) T(#note)
#define STROFA(note) #note
#define STROFW(note) L ## #note
#define _LSTR(str) L##str
#define LSTR(str) _MACRO_CALL(_LSTR, str)
#define S(str) T(str##_S)
#define T TEXT

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

#define using_structx(name) using name = std::conditional_t<IsUnicode, name##W, name##A>
#define locale_charmode(unicode) static constexpr bool IsUnicode = unicode

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
static auto __subtype_branchof_##name(int) -> typename AnyType::name; \
template<class AnyType, class OtherType> \
static auto __subtype_branchof_##name(...) -> OtherType; \
template<class AnyType, class OtherType> \
using subtype_branchof_##name = \
	decltype(__subtype_branchof_##name<AnyType, OtherType>(0))
#pragma endregion

using Null = decltype(nullptr);
constexpr inline Null O = nullptr;
