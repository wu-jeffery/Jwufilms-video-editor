@echo off

:: Set up the Visual Studio environment
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

cd C:\developer\repos\video_editing_software\app\build

rmdir /S /Q CMakeFiles

cd ..

rmdir /S /Q build 
mkdir build 
cd build

cmake -G "Visual Studio 17 2022" -A x64 ..

cmake --build . --config Debug

"C:\Qt\6.7.2\msvc2019_64\bin\windeployqt.exe" "C:\developer\repos\video_editing_software\app\build\Debug\app.exe"

cd C:\developer\repos\video_editing_software\app\build\Debug

app.exe

pause