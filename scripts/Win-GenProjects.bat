@echo off
pushd ..\
call vendor\bin\premake\windows\premake5.exe vs2019
popd
PAUSE