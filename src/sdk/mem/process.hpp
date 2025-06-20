#pragma once

#include <string_view>
#include <optional>
#include <cstddef>
#include <cstdint>
#include <span>
#include <stdexcept>
#include <utility>
#include <type_traits>

#include <libhat/scanner.hpp>

#ifdef SELAURA_WINDOWS
#include <Windows.h>
#include <Psapi.h>
#else
#include <dlfcn.h>
#include <link.h>
#endif

namespace selaura {
    struct process {
        std::byte* base;
        std::size_t size;

        void* native;
    };

    selaura::process get_handle();
};