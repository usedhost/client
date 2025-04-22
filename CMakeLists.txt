include(FetchContent)
set(CMAKE_CXX_STANDARD 23)
cmake_minimum_required(VERSION 3.5.0)
cmake_policy(SET CMP0169 OLD)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(Selaura)

if (MSVC)
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
else()
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_definitions(BUILD_TYPE_RELEASE)
        add_compile_options(-O3)
    elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_definitions(BUILD_TYPE_DEBUG)
        add_compile_options(-O0 -g)
    endif()
endif() 
 
file(GLOB_RECURSE SOURCE "src/*.cpp" "src/*.hpp")
file(GLOB_RECURSE LIB "include/*.cpp" "include/*.h")

add_library(Selaura SHARED "src/load/main.cpp" ${SOURCE} ${LIB})

target_include_directories(Selaura PRIVATE
    "src"
    "include"
)

if(MSVC)
    add_compile_options(/bigobj /utf-8 /O2 /Oi /Gy /Gw /GF /fp:fast /Gd /MT /Ob2)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
else()
    add_compile_options(-fvisibility=hidden -fPIC -fno-stack-check)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -O3")
endif()

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        master
)
FetchContent_Declare(
    entt
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG        d4014c74dc3793aba95ae354d6e23a026c2796db
)
FetchContent_Declare(
    typesafe
    GIT_REPOSITORY https://github.com/foonathan/type_safe.git
    GIT_TAG        cdf334cd8e5fcb5e21ab470decdfcbd190ef7347
)
FetchContent_Declare(
    libhat
    GIT_REPOSITORY https://github.com/BasedInc/libhat.git
    GIT_TAG        master
)
FetchContent_Declare(
    magic_enum
    GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
    GIT_TAG        master
)

if (MSVC)
    FetchContent_Declare(
        safetyhook
        GIT_REPOSITORY https://github.com/cursey/safetyhook.git
        GIT_TAG main
    )
else()
    FetchContent_Declare(
        Dobby
        GIT_REPOSITORY https://github.com/selauraclient/Dobby.git
        GIT_TAG master
    )
endif()

if (MSVC)
    FetchContent_MakeAvailable(fmt entt typesafe libhat magic_enum safetyhook)
else()
    FetchContent_MakeAvailable(fmt entt typesafe libhat magic_enum Dobby)
endif()

target_link_libraries(Selaura PRIVATE fmt::fmt EnTT::EnTT type_safe libhat magic_enum)

if (MSVC)
    target_link_libraries(Selaura PRIVATE safetyhook)
else()
    target_link_libraries(Selaura PRIVATE Dobby)
endif()

if (!MSVC)
    find_library(log-lib log) 
    target_link_libraries(Selaura PRIVATE ${log-lib})
endif()
