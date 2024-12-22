cmake_minimum_required(VERSION 3.16)

project(EvilPikmin LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

include_directories(include)

add_subdirectory(src)
#add_subdirectory(src/engine)
