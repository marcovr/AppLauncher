@echo off
if "%WindowsSdkDir%"=="" (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
)

msbuild src/applauncher.vcxproj /property:Configuration=Release