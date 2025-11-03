@echo off
setlocal enabledelayedexpansion
set workspace=%cd%
cd %cd%\..\
set global_dir=%cd%
cd !workspace!
if /i "%1" == "clean" (
    echo -- Clean started
    set clear_path="gcm.cache" "workspace\x64" "workspace\Debug" "workspace\Release" "workspace\wx_test"
    for %%p in (!clear_path!) do (
        rmdir %%p /s /q && echo clean and remove folder %%p
    )
    set clear_filter=*.o *.obj *.pcm *.exe *.manifest *.aps
    for %%p in (!clear_filter!) do (
        del %%p /q && echo remove file %%p
    )
    echo -- Clean finished
) else if /i "%1" == "build" (
    set module_files="!global_dir!\wx.cppm" "!global_dir!\wx.proto.cppm" "!global_dir!\wx.type.cppm" "!global_dir!\wx.realtime.cppm" "!global_dir!\wx.console.cppm" "!global_dir!\wx.gdi.cppm" "!global_dir!\wx.resource.cppm" "!global_dir!\wx.window.cppm"
    set source_files="!workspace!\wx_test.cpp"
    set include_paths="!global_dir!"
    if /i "%2" == "clang" (
        set compiler=clang++
        set compile_mod=-std=c++2a -fmodules -fprebuilt-module-path="./" --precompile
        set compile_src=-std=c++2a -fmodules -fprebuilt-module-path="./" -c -I!include_paths! -Wunused-command-line-argument
        set link_args=
    ) else if /i "%2" == "mingw" (
        set compiler=g++
        set compile_mod=-c -std=c++20 -fmodules
        set compile_src=-c -std=c++20 -fmodules -I!include_paths!
        set link_args=-lgdi32 -lcomdlg32
    ) else (
        echo Unknown compiler %2
        goto help
    )
    echo ----- Compilation test ----- 
    !compiler! --version || echo Compiler command "!compiler!" is invalid && goto end
    echo ----------------------------
    echo -- Use compiler %2
    echo  -- Compile modules
    for %%p in (!module_files!) do (
        echo  - module %%p
        echo !compiler! %%p !compile_mod!
        !compiler! %%p !compile_mod! || echo Module %%p compile failed && goto end
    )
    echo  -- Compile source files
    for %%p in (!source_files!) do (
        echo  - source %%p
        echo !compiler! %%p !compile_src!
        !compiler! %%p !compile_src! || echo Source %%p compile failed && goto end
    )
	if /i "%2" == "clang" (
		echo  -- Compile PCM files
		for %%p in (*.pcm) do (
			echo  - PCM %%p
			echo !compiler! %%p !compile_src!
			!compiler! %%p !compile_src! || echo PCM %%p compile failed && goto end
		)
	)
    echo  -- Link object files
    set object_files=
    for %%i in (*.o) do (
        set object_files=!object_files! %%i
    )
    echo !compiler! !object_files! -o wx_test.exe !link_args!
    !compiler! !object_files! -o wx_test.exe !link_args! || echo Link failed && goto end
    echo -- Compilation built
) else (
    if not "%1" == "" (
        if /i not "%1" == "help" (
            echo Unknown commands %*
        )
    )
:help
    echo    clean           - prebuild files like *.o *.obj *.pcm gcm.cache *.pdb *.idb
    echo    build clang     - build test target with clang++
    echo    build mingw     - build test target with MinGW
    echo    help            - show this list
)
:end
