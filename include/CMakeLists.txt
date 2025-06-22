cmake_minimum_required(VERSION 3.15)
project(selaura LANGUAGES CXX)

include(FetchContent)

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
    libhat
    GIT_REPOSITORY https://github.com/BasedInc/libhat.git
    GIT_TAG        master
)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.x
)

if (MSVC)
    FetchContent_Declare(
        minhook
        GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
        GIT_TAG        master
    )
else()
    FetchContent_Declare(
        dobby
        GIT_REPOSITORY https://github.com/selauraclient/Dobby
        GIT_TAG        master
    )
endif()

set(DOBBY_DEBUG OFF)
set(DOBBY_GENERATE_SHARED OFF)

if (MSVC)
    FetchContent_MakeAvailable(minhook)
else()
    FetchContent_MakeAvailable(dobby)
endif()

FetchContent_MakeAvailable(fmt entt libhat spdlog)

add_library(selaura INTERFACE)
add_library(selaura::selaura ALIAS selaura)
target_include_directories(selaura INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_directories(selaura INTERFACE fmt::fmt EnTT::EnTT libhat spdlog)