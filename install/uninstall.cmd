@echo off
pushd %~dp0
if exist install.log (
    del /q install.log
)
powershell -noprofile -executionpolicy bypass -file "install.ps1" uninstall
echo Uninstallation complete.
pause
popd