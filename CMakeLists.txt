cmake_minimum_required(VERSION 3.16)


project(EvilPikmin LANGUAGES CXX)



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(EvilPikmin
    src/main.cpp 
    "src/entities/Guy.hpp"  
    "src/entities/Entity.hpp"
    "include/Animation.h"
    "src/CollisionGrid.hpp"
    "src/tools/Mallet.hpp"
    "src/Gamestate.hpp"
    "src/entities/decorations/Bloodstain.hpp"
    "include/Helper.h"
    "src/entities/Bomb.hpp"
    "src/tools/Tool.hpp"
    "src/tools/Bombs.hpp" 
)


option(USE_INSTALL_RESOURCE_PATH "Set resource path to install location" OFF)
 
if(NOT USE_INSTALL_RESOURCE_PATH)
    #set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/resources/")
    target_compile_definitions(EvilPikmin PUBLIC RESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
else()
    target_compile_definitions(EvilPikmin PUBLIC RESOURCE_PATH="${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/resources/")
    #set(RESOURCE_PATH "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/resources/")
endif()


# 

target_include_directories(EvilPikmin PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(EvilPikmin PRIVATE sfml-graphics)
target_link_libraries(EvilPikmin PRIVATE sfml-audio)
target_compile_features(EvilPikmin PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET EvilPikmin
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:EvilPikmin>
        VERBATIM)
endif()

install(TARGETS EvilPikmin)

