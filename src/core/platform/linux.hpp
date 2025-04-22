#pragma once
#if defined(__unix__) || defined(__APPLE__)

#include <link.h>
#include <dlfcn.h>

#include <span>
#include <byte>
#include <string>
#include <stdexcept>


namespace selaura::detail {
    using game_memory = std::span<std::byte>;

    void* get_module_handle(std::string_view name);
    void* get_module_handle();
    void get_module_info(std::byte*& base, std::size_t& size);
    std::byte* get_module_base();
    std::size_t get_module_size();
    std::span<std::byte> get_game_memory();

    template <typename T, typename = std::enable_if_t<std::is_pointer_v<T>>>
    inline constexpr void safe_release(T& ptr);

}

#endif