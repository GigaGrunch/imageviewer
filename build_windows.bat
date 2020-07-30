@echo off

set current_dir=%cd%
cd %~dp0

set script_dir=%cd%
set build_dir=%script_dir%\build
set code_dir=%script_dir%\code
set sdl_dir=%script_dir%\..\SDL

if exist %build_dir%\ (
	rmdir /q /s %build_dir% || goto :error
)

mkdir %build_dir% || goto :error

copy %sdl_dir%\lib\SDL2.dll %build_dir% || goto :error

cd %build_dir%
cl /nologo /Wall /Fe"imageviewer.exe" %code_dir%\windows_imageviewer.c /link %sdl_dir%\lib\SDL2.lib || goto :error

if "%1" == "run" (
	imageviewer.exe
)

cd %current_dir%
exit /b

:error
cd %current_dir%
exit /b %errorlevel%