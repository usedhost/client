set(CMAKE_CXX_STANDARD 23)

project(Selaura)

add_compile_options($<$<CONFIG:Release>:/Gw>)

add_compile_options(/bigobj)
add_compile_options(/utf-8)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(/O2 /Oi /Gy /Gw /GF /fp:fast /Gd /MT /Ob2)
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(/Od /Zi /MT)
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.hpp")
file(GLOB_RECURSE LIB_FILES "include/*.cpp" "include/*.h")

add_library(Selaura SHARED src/load/dllmain.cpp ${SOURCE_FILES} ${LIB_FILES})

target_include_directories(Selaura PRIVATE
        "src"
        "src/client"
        "include"
)

add_library(MinHook SHARED IMPORTED GLOBAL)
set_target_properties(MinHook PROPERTIES IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/include/minhook/minhook.lib")

target_precompile_headers(Selaura PRIVATE "src/pch.hpp")

target_link_libraries(Selaura PUBLIC MinHook)