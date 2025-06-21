include(FetchContent)
set(CMAKE_CXX_STANDARD 23)
cmake_minimum_required(VERSION 3.15)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(Selaura)

if (WIN32)
    add_compile_definitions(SELAURA_WINDOWS)
elseif(ANDROID)
    add_compile_definitions(SELAURA_ANDROID)
elseif(UNIX)
    add_compile_definitions(SELAURA_LINUX)
endif()

set(CLIENT_VERSION "0.30")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(DEVELOPER_MODE "")
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEVELOPER_MODE " Dev")
endif()

add_compile_definitions(
        CLIENT_VERSION=\"${CLIENT_VERSION}\"
        DEVELOPER_MODE=\"${DEVELOPER_MODE}\"
)

if (MSVC)
    add_compile_options($<$<CONFIG:Release>:/Gw>)
    add_compile_options(/bigobj)
    add_compile_options(/utf-8)
    add_compile_options(/await)

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

add_library(Selaura SHARED "src/main.cpp" ${SOURCE} ${LIB})

target_include_directories(Selaura PRIVATE
    "src"
    "include"
    ${glm_SOURCE_DIR}
)

if(MSVC)
    add_compile_options(/bigobj /utf-8 /Oi /Gy /Gw /GF /fp:fast /Gd /MT /Ob2)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /DEBUG")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
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
    libhat
    GIT_REPOSITORY https://github.com/BasedInc/libhat.git
    GIT_TAG        master
)
FetchContent_Declare(
    LuaBridge
    GIT_REPOSITORY https://github.com/kunitoki/LuaBridge3.git
    GIT_TAG        master
)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG master
)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        features/shadows
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

FetchContent_MakeAvailable(fmt entt libhat LuaBridge glm spdlog)
if (MSVC)
    FetchContent_MakeAvailable(minhook)
else()
    FetchContent_MakeAvailable(dobby)
endif()

target_include_directories(Selaura PUBLIC ${cpp-i18n_SOURCE_DIR}/include)

FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_MakeAvailable(imgui)
    add_library(ImGui STATIC
        "${imgui_SOURCE_DIR}/imgui.cpp"
        "${imgui_SOURCE_DIR}/imgui_demo.cpp"
        "${imgui_SOURCE_DIR}/imgui_draw.cpp"
        "${imgui_SOURCE_DIR}/imgui_tables.cpp"
        "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
    )
    target_include_directories(ImGui PUBLIC ${imgui_SOURCE_DIR})
endif()

if(MSVC)
    target_link_libraries(Selaura PRIVATE fmt::fmt EnTT::EnTT libhat ImGui LuaBridge glm spdlog minhook)
else()
    target_link_libraries(Selaura PRIVATE fmt::fmt EnTT::EnTT libhat ImGui LuaBridge glm spdlog dobby_static)
endif()

if (ANDROID)
    target_link_libraries(Selaura PRIVATE log)
endif()