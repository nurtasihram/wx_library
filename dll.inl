#pragma once

#ifdef DLL_EXPORTS

#	define DLL_EXPORT extern "C" __declspec(dllexport)
#	define REG_FUNC(ret, name, ...) DLL_EXPORT ret name(__VA_ARGS__);
#	include DLL_EXPORTS
#	undef REG_FUNC
#	define REG_FUNC(ret, name, ...) DLL_EXPORT ret name(__VA_ARGS__)

#elif defined DLL_IMPORTS

#	ifndef MOD_NAME
#		error Please define MOD_NAME as namespace of module before include this file
#	endif

namespace MOD_NAME {

using namespace WX;

extern WX::Module Module;

#	define REG_FUNC(ret, name, ...) extern ret(*name)(__VA_ARGS__);
#	include DLL_IMPORTS
#	undef REG_FUNC

size_t LoadDll(LPCTSTR lpFilenameDLL);
void CloseDll();

#	ifdef DLL_IMPORTS_DEF
WX::Module Module = O;
#		define REG_FUNC(ret, name, ...) ret(*name)(__VA_ARGS__) = O;
#		include DLL_IMPORTS
#		undef REG_FUNC
size_t LoadDll(LPCTSTR lpFilenameDLL) {
	Module = WX::Module::Library(lpFilenameDLL);
	size_t CountFn = 0;
#		define REG_FUNC(ret, name, ...) \
	if ((name = Module.Proc<ret(__VA_ARGS__)>(#name))) ++CountFn;
#		include DLL_IMPORTS
#		undef REG_FUNC
	return CountFn;
}
void CloseDll() {
	Module.Free();
}
#		undef DLL_IMPORTS_DEF
#	endif

}

#	undef DLL_IMPORTS
#	undef MOD_NAME

#endif

#undef LIST_FILE
