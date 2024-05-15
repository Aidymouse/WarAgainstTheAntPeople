cmake_minimum_required(VERSION 3.16)

project(EvilPikmin LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

message("${CMAKE_CXX_COMPILER_ID}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(EvilPikmin
    "src/main.cpp"
    "src/CollisionGrid.cpp"
    "src/Gamestate.cpp"

    "src/include/Lib/Gamestate.h" 
    "src/include/Types/Animation.h"
    "src/include/Types/Collisions.h"
    "src/include/Types/CollisionShapes.h"

    "src/include/Lib/AnimationGenerator.h"
    "src/include/Lib/GraphicsManager.h" "src/lib/GraphicsManager.cpp"
    "src/include/Lib/CollisionManager.h" "src/lib/CollisionManager.cpp"

    "src/lib/AnimationGenerator.cpp"
    "src/include/Lib/AudioManager.h" "src/lib/AudioManager.cpp" 

    "src/include/Lib/Helper.hpp"

    "src/tools/Tool.cpp"
    "src/include/Tools/Mallet.h" "src/tools/Mallet.cpp"
    "src/include/Tools/Bombs.h" "src/tools/Bombs.cpp" 
    "src/include/Tools/Fire.h" "src/tools/Fire.cpp"

    "src/include/Entities/Entity.h" "src/entities/Entity.cpp"
    "src/include/Entities/Guy.h" "src/entities/Guy.cpp"  
    "src/include/Entities/Bomb.h"  "src/entities/Bomb.cpp"
    "src/include/Entities/FloorPanel.h" "src/entities/FloorPanel.cpp"
    "src/include/Entities/TestEntity.h" "src/entities/TestEntity.cpp"

    "src/entities/decorations/Bloodstain.cpp"
)


option(USE_INSTALL_RESOURCE_PATH "Set resource path to install location" OFF)
 
if(NOT USE_INSTALL_RESOURCE_PATH)
    #set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/resources/")
    target_compile_definitions(EvilPikmin PUBLIC RESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
else()
    target_compile_definitions(EvilPikmin PUBLIC RESOURCE_PATH="${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/resources/")
    #set(RESOURCE_PATH "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/resources/")
endif()

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

