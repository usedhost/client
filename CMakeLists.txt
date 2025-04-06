set(CMAKE_CXX_STANDARD 23)
cmake_minimum_required(VERSION 3.24.0)

project(Selaura)

add_compile_options($<$<CONFIG:Release>:/Gw>)

add_compile_options(/bigobj)
add_compile_options(/utf-8)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(BUILD_TYPE_RELEASE)
    add_compile_options(/O2 /Oi /Gy /Gw /GF /fp:fast /Gd /MT /Ob2)
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(BUILD_TYPE_DEBUG)
    add_compile_options(/Od /Zi /MT)
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.hpp")
file(GLOB_RECURSE LIB_FILES "include/*.cpp" "include/*.h")

add_library(Selaura SHARED "src/load/main.cpp" ${SOURCE_FILES} ${LIB_FILES})

target_include_directories(Selaura PRIVATE
    "src"
    "include"
)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        master
)
FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG        f931687ff04d435871ac9664bb299f71f2a8fafc
)

FetchContent_MakeAvailable(fmt entt)

add_library(MinHook SHARED IMPORTED GLOBAL)
set_target_properties(MinHook PROPERTIES IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/include/minhook/minhook.lib")

target_link_libraries(Selaura PRIVATE fmt::fmt EnTT::EnTT)
target_link_libraries(Selaura PUBLIC MinHook)