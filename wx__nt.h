#pragma once

#include "wx__rm.inl"

/* WinNT assert & reflector */
#define wx_throw_line_nt(sent) throw WX::Exception(__FILE__, __FUNCTION__, #sent, __LINE__, GetLastError())
#define assertl(sent) { using namespace WX; if (!(sent)) wx_throw_line_nt(sent); }

#define assertl_reflect_as(sent, ...) { if (sent) return __VA_ARGS__; wx_throw_line_nt(sent); }
#define assertl_reflect_as_self(sent)  assertl_reflect_as(sent, self)
#define assertl_reflect_as_child(sent) assertl_reflect_as(sent, child)

#define assertl_reflect_to(defs, sent, ...) { defs; if (sent) return __VA_ARGS__; wx_throw_line_nt(sent); }
#define assertl_reflect_to_self(defs, sent)  assertl_reflect_to(defs, sent, self)
#define assertl_reflect_to_child(defs, sent) assertl_reflect_to(defs, sent, child)

#define nt_assertl_reflect_to(sent, ...) { SetLastError(ERROR_SUCCESS); sent; if (GetLastError()) wx_throw_line_nt(sent); return __VA_ARGS__; }
#define nt_assertl_reflect_to_self(sent)  nt_assertl_reflect_to(sent, self)
#define nt_assertl_reflect_to_child(sent) nt_assertl_reflect_to(sent, child)
