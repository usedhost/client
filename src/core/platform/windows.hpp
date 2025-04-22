#ifdef _WIN32
#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <span>
#include <string>
#include <stdexcept>
#include <type_traits>

#include <d3d11.h>
#include <d3dcompiler.h>

namespace selaura::detail {

    HMODULE get_module_handle(std::wstring_view name);
    HMODULE get_module_handle();
    const MODULEINFO& get_module_info();
    std::byte* get_module_base();
    std::size_t get_module_size();
    std::span<std::byte> get_game_memory();

    template <typename T, typename = std::enable_if_t<std::is_pointer_v<T>>>
    inline constexpr void safe_release(T& ptr);

}
#endif