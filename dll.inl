#include "./wx/resource.h"

#ifndef DLL_INL_LIST
#	error Please define DLL_INL_LIST as list registered functions / variables
#endif

#ifdef DLL_EXPORTS
#	undef DLL_EXPORTS
#	define DLL_EXPORT extern "C" __declspec(dllexport)
#	define REG_FUNC(ret, name, ...) DLL_EXPORT ret name(__VA_ARGS__);
#	include DLL_INL_LIST
#	undef REG_FUNC
#	define REG_FUNC(ret, name, ...) DLL_EXPORT ret name(__VA_ARGS__)
#else
#	ifndef MOD_NAME
#		error Please define MOD_NAME as namespace of module before include this file
#	endif
namespace MOD_NAME {
#	undef MOD_NAME
using namespace WX;
extern WX::Module Module;
#	define REG_FUNC(ret, name, ...) extern ret(*name)(__VA_ARGS__);
#	include DLL_INL_LIST
#	undef REG_FUNC
size_t LoadDll(LPCTSTR lpFilenameDLL);
void CloseDll();
#	ifdef DLL_IMPORTS
#	undef DLL_IMPORTS
WX::Module Module = O;
#	define REG_FUNC(ret, name, ...) ret(*name)(__VA_ARGS__) = O;
#	include DLL_INL_LIST
#	undef REG_FUNC
size_t LoadDll(LPCTSTR lpFilenameDLL) {
	Module = WX::Module::Library(lpFilenameDLL);
	size_t CountFn = 0;
#	define REG_FUNC(ret, name, ...) \
	if ((name = Module.Proc<ret(__VA_ARGS__)>(#name))) ++CountFn;
#	include DLL_INL_LIST
#	undef REG_FUNC
	return CountFn;
}
void CloseDll() {
	Module.Free();
}
#	endif
}
#endif

#undef DLL_INL_LIST
