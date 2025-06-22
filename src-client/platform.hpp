#pragma once

#include <string>
#include <fmt/format.h>
#include <span>
#include <memory>
#include <filesystem>
#include "plugins/plugin_api.hpp"

#ifdef SELAURA_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Psapi.h>

#include <winrt/base.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>

#include <MinHook.h>
#else
#include <dlfcn.h>
#include <link.h>
#include <dobby.h>
#endif

namespace selaura::platform {
    inline std::span<std::byte> mc_bytes;

    void set_title(const std::string& title);

    template <typename... Args>
    void set_title(fmt::format_string<Args...> fmt_str, Args&&... args) {
        set_title(fmt::format(fmt_str, std::forward<Args>(args)...));
    }

    void create_instance(void* mc_handle);

    std::filesystem::path get_data_folder();

    using mod_info_t = selaura_mod_info(*)(std::shared_ptr<selaura_runtime>);
    mod_info_t load_mod_info(std::filesystem::path path);

    using mod_entry_t = void(*)(std::shared_ptr<selaura_runtime>);
    mod_entry_t load_mod(std::filesystem::path path);

    void hook_init();
    void hook(void* target, void* detour, void** original);
};