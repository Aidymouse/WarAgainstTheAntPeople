@echo off
cmake -G Ninja -S . -B ninja_out -DCMAKE_CXX_COMPILER="C:\Program Files\LLVM\bin\clang++.exe"
mv ninja_out/compile_commands.json src/compile_commands.json
cmake -G "Visual Studio 17 2022" -S . -B out
cmake --build out
C:\Users\aidan\Desktop\Programming\cpp\EvilPikmin\out\bin\Debug\EvilPikmin.exe
