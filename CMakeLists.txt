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

    "include/state/AudioManager.hpp" "src/state/AudioManager.cpp"
    "include/state/CollisionGrid.hpp" "src/state/CollisionGrid.cpp"
    "include/state/CollisionManager.hpp" "src/state/CollisionManager.cpp"
    "include/state/Gamestate.hpp" "src/state/Gamestate.cpp"
    "include/state/GraphicsManager.hpp" "src/state/GraphicsManager.cpp"

    "include/helper/AnimationGenerator.hpp"
    "include/helper/Debug.hpp" 

    "include/entities/Entity.hpp" "src/entities/Entity.cpp"
    "include/entities/TestEntity.hpp" "src/entities/TestEntity.cpp"

    "include/entities/creatures/Guy.hpp" "src/entities/creatures/Guy.cpp"

    "include/entities/decorations/Bloodstain.hpp" "src/entities/decorations/Bloodstain.cpp"

    "include/entities/objects/Bomb.hpp" "src/entities/objects/Bomb.cpp"
    "include/entities/objects/FloorPanel.hpp" "src/entities/objects/FloorPanel.cpp"

    "include/entities/tools/ToolHolder.hpp" "src/entities/tools/ToolHolder.cpp"
    "include/entities/tools/Bombs.hpp" "src/entities/tools/Bombs.cpp"
    "include/entities/tools/Fire.hpp" "src/entities/tools/Fire.cpp"
    "include/entities/tools/Mallet.hpp" "src/entities/tools/Mallet.cpp"
    "include/entities/tools/Tool.hpp"

)


option(USE_INSTALL_RESOURCE_PATH "Set resource path to install location" OFF)
 
if(NOT USE_INSTALL_RESOURCE_PATH)
    #set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/resources/")
    target_compile_definitions(EvilPikmin PUBLIC RESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
else()
    target_compile_definitions(EvilPikmin PUBLIC RESOURCE_PATH="${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/resources/")
    #set(RESOURCE_PATH "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/resources/")
endif()

target_include_directories(EvilPikmin PRIVATE "include")

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

