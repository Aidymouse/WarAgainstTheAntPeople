cmake_minimum_required(VERSION 3.28)

project(EvilPikmin LANGUAGES CXX VERSION 0.0.1)
#set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Something to do with sdl ?
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(GRAPHICS_PATH "\"../resources/graphics/\"")
if(WINDOWS)
	message("Windows")
	set(GRAPHICS_PATH "\"../../resources/graphics/\"")
endif()

if(ABSOLUTE_GRAPHICS)
	set(GRAPHICS_PATH "\"resources/graphics/\"")
endif()

add_executable(EvilPikmin src/main.cpp)

target_include_directories(EvilPikmin PUBLIC
    include
    # "${PROJECT_BINARY_DIR}"
)

configure_file(include/ProjectConfig.h.in ../include/ProjectConfig.h)

add_subdirectory(src)
#add_subdirectory(lib)


### SDL3

# Linux
# find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

# Window
add_subdirectory(lib/SDL EXCLUDE_FROM_ALL)
# add_subdirectory(lib/SDL_Image EXCLUDE_FROM_ALL)
target_link_libraries(EvilPikmin PRIVATE SDL3::SDL3)

