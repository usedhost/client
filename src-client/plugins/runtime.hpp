#pragma once
#include <spdlog/spdlog.h>
#include "plugin_api.hpp"

namespace selaura {
    inline void runtime_init(const std::shared_ptr<selaura_runtime> &runtime) {
        auto r = runtime;
        runtime->info = [r](const char* msg) {
            spdlog::info("[Plugin Info] [{}] {}", r->name, msg);
        };

        runtime->debug = [r](const char* msg) {
            spdlog::info("[Plugin Debug] [{}] {}", r->name, msg);
        };

        runtime->warn = [r](const char* msg) {
            spdlog::info("[Plugin Warn] [{}] {}", r->name, msg);
        };

        runtime->error = [r](const char* msg) {
            spdlog::info("[Plugin Error] [{}] {}", r->name, msg);
        };
    }
};