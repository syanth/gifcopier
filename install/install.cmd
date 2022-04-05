@echo off
pushd %~dp0
if exist install.log (
    del /q install.log
)
powershell -noprofile -executionpolicy bypass -file "install.ps1" > install.log
if %errorlevel% equ -1 goto fail
if %errorlevel% equ 1 goto cancel
if %errorlevel% equ 0 goto success

:cancel
echo Installation cancelled. Run as administrator if you want to install GIFCopier.
goto end

:fail
echo Installation failed. Check install.log for details.
goto end

:success
echo Successfully installed.
goto end

:end
pause
popd