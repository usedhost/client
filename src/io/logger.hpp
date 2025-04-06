#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

#ifdef _WIN32
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.Storage.h>
#include <Windows.h>

namespace console {
    extern HWND window;
    extern FILE* f;
    extern RECT rect;

    void open();
    void scrollToTop();
    void resize();
}
#endif

namespace logger {
    extern std::ofstream logs;
    extern std::filesystem::path path;

    void clear();
    void init();
    void info(const std::string& string);
    void error(const std::string& string);
}