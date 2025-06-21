#pragma once
#include <spdlog/spdlog.h>
#include "plugin_api.hpp"

namespace selaura {
    inline void runtime_init(const std::shared_ptr<selaura_runtime> &runtime) {
        runtime->info = [](const char* msg) {
            spdlog::info("[Mod Info] {}", msg);
        };

        runtime->debug = [](const char* msg) {
            spdlog::info("[Mod Debug] {}", msg);
        };

        runtime->warn = [](const char* msg) {
            spdlog::info("[Mod Warn] {}", msg);
        };

        runtime->error = [](const char* msg) {
            spdlog::info("[Mod Error] {}", msg);
        };
    }
};