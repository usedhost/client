#pragma once
#include "runtime.hpp"
#include "../platform.hpp"
#include <spdlog/spdlog.h>

namespace selaura {
    inline void runtime_link(std::shared_ptr<selaura::runtime> runtime) {
        runtime->terminate = []() {
            spdlog::warn("Plugin terminated the game.");
            std::terminate();
        };
        runtime->hook_raw = [](void* target, void* detour, void** original) {
            selaura::platform::hook(target, detour, original);
        };
        runtime->sig = [](const std::string_view pattern) -> std::optional<uintptr_t> {
            const auto parsed = hat::parse_signature(pattern);
            if (!parsed.has_value()) {
                spdlog::error("Invalid signature! {:s}", pattern);
                return std::nullopt;
            }

            const auto result = hat::find_pattern(platform::mc_bytes, parsed.value());

            if (!result.has_result()) {
                return std::nullopt;
            }
            return reinterpret_cast<uintptr_t>(result.get());
        };
        runtime->info_fn = [](const std::string& msg) {
            spdlog::info(msg);
        };
        runtime->warn_fn = [](const std::string& msg) {
            spdlog::warn(msg);
        };
        runtime->error_fn = [](const std::string& msg) {
            spdlog::error(msg);
        };
        runtime->debug_fn = [](const std::string& msg) {
            spdlog::debug(msg);
        };
    }
};