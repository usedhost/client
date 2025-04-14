#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <fmt/base.h>
#include <fmt/color.h>
#include <fmt/format.h>

#ifdef _WIN32
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.Storage.h>
#include <Windows.h>

namespace console {
    extern HANDLE handle;
    extern HWND window;
    extern RECT rect;

    void open();
    void scrollToTop();
    void resize();
    void updateDimensions(std::string string);
}
#else
#include <android/log.h>
#endif

namespace logger {
    extern std::ofstream logs;
    extern std::filesystem::path path;

    void clear();
    void init();

    template <typename... T>
    void out(const fmt::text_style color, const std::string& prefix, const std::string& fmt, T&&... args) {
        auto msg = fmt::format(fmt::runtime(fmt), std::forward<T>(args)...);
        logs.open(path, std::ios::app);
        logs << "[" << prefix << "] " << msg << std::endl;
        logs.close();
#ifdef _WIN32
        fmt::print("{}{}{} {}\n",
            fmt::format(fmt::fg(fmt::color::gray), "["),
            fmt::format(color, fmt::runtime(prefix)),
            fmt::format(fmt::fg(fmt::color::gray), "]"),
            fmt::format(color, fmt::runtime(msg))
        );

        console::updateDimensions(msg);
        console::resize();
#else
        __android_log_print(ANDROID_LOG_INFO, "SELAURA", "[%s] %s", prefix, msg);
#endif
    }

    void info(const std::string& fmt, auto&&... args) {
        out(fmt::fg(fmt::color::forest_green), "INFO", fmt, (args)...);
    }
    void error(const std::string& fmt, auto&&... args) {
        out(fmt::fg(fmt::color::red), "ERROR", fmt, (args)...);
    }
}
