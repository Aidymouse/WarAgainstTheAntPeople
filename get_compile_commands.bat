@echo off
cmake -G Ninja -S . -B ninja_out -DCMAKE_CXX_COMPILER="C:\Program Files\LLVM\bin\clang++.exe"
mv ninja_out/compile_commands.json src/compile_commands.json
