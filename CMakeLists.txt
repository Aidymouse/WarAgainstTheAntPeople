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

configure_file(include/ProjectConfig.h.in ../include/ProjectConfig.h)

add_subdirectory(src)

#SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

target_link_libraries(EvilPikmin PRIVATE SFML::Graphics)

# Boost
# set(BOOST_INCLUDE_LIBRARIES unordered )
# set(BOOST_ENABLE_CMAKE ON)
# # set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
# # set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
# include(FetchContent)
# FetchContent_Declare(Boost
#     URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
#     USES_TERMINAL_DOWNLOAD TRUE
#     DOWNLOAD_NO_EXTRACT FALSE
#     EXCLUDE_FROM_ALL
#     SYSTEM
# )
# FetchContent_MakeAvailable(Boost)
#
# target_link_libraries(EvilPikmin PUBLIC
#     Boost::unordered
# )
