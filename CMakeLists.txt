cmake_minimum_required(VERSION 3.28)

project(EvilPikmin LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_executable(EvilPikmin src/main.cpp)

include_directories(include)
add_subdirectory(src)

#SFML
set(SFML_USE_DRM false) # Disables need for X11
#set(EGL_CONTEXT_CLIENT_VERSION 2)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

target_link_libraries(EvilPikmin PRIVATE SFML::Graphics)
