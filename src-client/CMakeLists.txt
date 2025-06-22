cmake_minimum_required(VERSION 3.15)
project(selaura_client LANGUAGES CXX)

add_library(selaura_client SHARED
    ${SELAURA_BEDROCK_SOURCES}
    main.cpp
    instance.cpp
    platform.cpp
)
add_library(selaura::client ALIAS selaura_client)


target_include_directories(selaura_client PRIVATE
    ${SELAURA_BEDROCK_INCLUDE_DIR}
)

target_link_libraries(selaura_client PRIVATE
    fmt::fmt
    EnTT::EnTT
    spdlog
    libhat
)

if (MSVC)
    target_link_libraries(selaura_client PRIVATE
        minhook
    )
else()
    target_link_libraries(selaura_client PRIVATE
        dobby_static
    )
endif()
