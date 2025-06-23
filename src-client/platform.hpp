#pragma once

#include <string>
#include <fmt/format.h>
#include <libhat/scanner.hpp>
#include <span>
#include <spdlog/spdlog.h>
#include <memory>
#include <filesystem>
#include "plugins/plugin.hpp"
#include "plugins/runtime.hpp"

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

    using plugin_entry_t = selaura::plugin*(*)();
    selaura::plugin* load_plugin(std::filesystem::path path);

    void hook_init();
    void hook(void* target, void* detour, void** original);

    template <hat::fixed_string T>
    std::optional<uintptr_t> find_pattern() {
        constexpr hat::fixed_signature parsed = hat::compile_signature<T>();
        if (!parsed.has_value()) {
            spdlog::error("Invalid signature! {:s}", T);
            return std::nullopt;
        }

        const auto result = hat::find_pattern(mc_bytes, parsed.value());

        if (!result.has_result()) {
            return std::nullopt;
        }
        return reinterpret_cast<uintptr_t>(result.get());
    }

    template <typename>
    static constexpr bool always_false = false;

    template <typename fn_t>
    void* resolve_func_ptr(fn_t fn) {
        if constexpr (std::is_pointer_v<fn_t>) {
            return reinterpret_cast<void*>(fn);
        }
        else if constexpr (std::is_member_function_pointer_v<fn_t>) {
#if defined(_MSC_VER)
            return *reinterpret_cast<void**>(&fn);
#elif defined(__clang__)
            union {
                fn_t mfp;
                struct {
                    void* addr;
                    ptrdiff_t adj;
                } s;
            } caster{ .mfp = fn };
            return caster.s.addr;
#endif
        }
        else {
            static_assert(always_false<fn_t>, "unsupported function type for hook resolution");
        }
        return nullptr;
    }
};