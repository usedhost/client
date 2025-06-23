#pragma once
#include <format>
#include <functional>
#include <optional>

namespace selaura {
    struct runtime {
        std::function<void()> terminate;
        std::function<void(void* target, void* detour, void** original)> hook_raw;
        std::function<std::optional<uintptr_t>(const std::string_view pattern)> sig;
        std::function<void(const std::string&)> info_fn;
        std::function<void(const std::string&)> warn_fn;
        std::function<void(const std::string&)> error_fn;
        std::function<void(const std::string&)> debug_fn;

        template<typename... Args>
        void info(std::format_string<Args...> fmt, Args&&... args) {
            if (info_fn) info_fn(std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        void warn(std::format_string<Args...> fmt, Args&&... args) {
            if (warn_fn) warn_fn(std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        void error(std::format_string<Args...> fmt, Args&&... args) {
            if (error_fn) error_fn(std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        void debug(std::format_string<Args...> fmt, Args&&... args) {
            if (debug_fn) debug_fn(std::format(fmt, std::forward<Args>(args)...));
        }

    };
};