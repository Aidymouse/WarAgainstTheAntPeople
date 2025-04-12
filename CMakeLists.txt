cmake_minimum_required(VERSION 3.28)

project(EvilPikmin LANGUAGES CXX VERSION 0.0.1)
#set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)


set(GRAPHICS_PATH "\"../resources/graphics/\"")
if(ABSOLUTE_GRAPHICS)
    set(GRAPHICS_PATH "\"resources/graphics/\"")
endif()

add_executable(EvilPikmin src/main.cpp)

target_include_directories(EvilPikmin PUBLIC
    include
    # "${PROJECT_BINARY_DIR}"
)

configure_file(include/ProjectConfig.h.in ProjectConfig.h)

add_subdirectory(src)

# SDL3
# set(SDL_X11 OFF)
# set(SDL_X11_SHARED OFF)
# set(SDL_X11_XCURSOR OFF)
# set(SDL_X11_XDBE OFF)
# set(SDL_X11_XFIXES OFF)
# set(SDL_X11_XINPUT OFF)
# set(SDL_X11_XRANDR OFF)
# set(SDL_X11_XSCRNSAVER OFF)
# set(SDL_X11_XSHAPE OFF)
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
target_link_libraries(EvilPikmin PRIVATE SDL3::SDL3)

