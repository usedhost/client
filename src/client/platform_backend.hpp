#pragma once

// Define platform macros
#if defined(_WIN32) || defined(WIN32)
#define SELAURA_WIN32 1
#else
#define SELAURA_WIN32 0
#endif

#ifdef __linux__
#define SELAURA_LINUX 1
#else
#define SELAURA_LINUX 0
#endif

#if SELAURA_WIN32
#include <Windows.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/base.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <CoreWindow.h>
using module_handle_t = HMODULE;
#endif

#if SELAURA_LINUX
#include <pthread.h>
#include <dlfcn.h>
using module_handle_t = void*;
#endif

#define FMT_HEADER_ONLY
#include "../../include/fmt/format.h"
#include <memory>
#include <thread>
#include <chrono>

struct platform_backend {
    module_handle_t handle{ nullptr };
    bool debug = false;

    void init(module_handle_t _handle) {
        this->handle = _handle;
#ifdef _DEBUG
        this->debug = true;
#endif
    }

    void exit_thread(void* handle) {
#if SELAURA_WIN32
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)FreeLibraryAndExitThread, (LPVOID)handle, 0, nullptr);
#elif SELAURA_LINUX
        std::thread([handle]() {
            dlclose(handle);
            }).detach();
#endif
    }

    template <typename Callable>
    void run_async(Callable&& func) {
#if SELAURA_WIN32
        winrt::Windows::ApplicationModel::Core::CoreApplication::MainView()
            .CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, std::forward<Callable>(func));
#elif SELAURA_LINUX
        std::thread(std::forward<Callable>(func)).detach();
#endif
    }

    template<typename... Args>
    void set_title(const std::string& str, Args&&... args) {
        const std::string title = fmt::vformat(str, fmt::make_format_args(args...));
#if SELAURA_WIN32
        winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(winrt::to_hstring(title));
#elif SELAURA_LINUX

#endif
    }

    void shutdown() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        exit_thread(this->handle);
    }
};
