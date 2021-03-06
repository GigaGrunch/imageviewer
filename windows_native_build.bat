@echo off

where /q cl || (
	echo 'cl' not in PATH, executing 'vcvarsall x64'

	where /q vcvarsall || (
		echo 'vcvarsall' not in PATH, exiting
		goto :error
	)

	vcvarsall x64

	echo .
	echo for some reason, the script terminates after running 'vcvarsall', just try to compile again
)

set current_dir=%cd%
cd %~dp0

set script_dir=%cd%
set build_dir=%script_dir%\build
set code_dir=%script_dir%\code

if exist %build_dir%\ (
	rmdir /q /s %build_dir% || goto :error
)

mkdir %build_dir% || goto :error

cd %build_dir%
cl /nologo /Wall /Fe"imageviewer.exe" %code_dir%\windows_native_imageviewer.c || goto :error

if "%1" == "run" (
	imageviewer.exe || goto :error
)

cd %current_dir%
exit /b

:error
cd %current_dir%
exit /b %errorlevel%