cmake_minimum_required(VERSION 3.24)

project(filemgr)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    raygui
    GIT_REPOSITORY https://github.com/raysan5/raygui.git
    GIT_TAG master
)
FetchContent_GetProperties(raygui)

if(NOT raygui_POPULATED)
    FetchContent_MakeAvailable(raygui)
    add_library(raygui INTERFACE)
    target_include_directories(raygui INTERFACE ${raygui_SOURCE_DIR}/src)
    target_link_libraries(raygui INTERFACE raylib)
    #target_compile_definitions(raygui INTERFACE RAYGUI_IMPLEMENTATION)
endif()

set(RAYLIB_VERBOSE OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(src)