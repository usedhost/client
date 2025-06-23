#pragma once

#include <cstddef>
#include <span>
#include <memory>
#include <stdexcept>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#ifdef SELAURA_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Psapi.h>
#endif

#include "platform.hpp"
#include "plugins/runtime_linkage.hpp"

namespace selaura {
    struct instance : std::enable_shared_from_this<instance> {
        bool start();
        void init();
    private:
        std::shared_ptr<selaura::runtime> runtime;
    };

    std::shared_ptr<selaura::instance> get();
};