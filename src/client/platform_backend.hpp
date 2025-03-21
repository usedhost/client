#pragma once

#if defined(_WIN32) || defined(WIN32)
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

#ifdef __linux__
#include <pthread.h>
#include <dlfcn.h>
using module_handle_t = void*;
#endif

#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <memory>

enum class backend_type {
    unknown,
    Windows,
    Linux
};

struct platform_backend {
    module_handle_t handle{ nullptr };
    backend_type type{ backend_type::unknown };
    bool debug = false;

    void init(module_handle_t _handle) {
        this->handle = _handle;
#ifdef _DEBUG
        this->debug = true;
#endif

        if constexpr (std::is_same_v<module_handle_t, HMODULE>) {
            this->type = backend_type::Windows;
        }
        else {
            this->type = backend_type::Linux;
        }
    }

    void exit_thread(void* handle) {
#if defined(_WIN32) || defined(WIN32)
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)FreeLibraryAndExitThread, (LPVOID)handle, 0, nullptr);
#endif
#ifdef __linux__
        std::thread([handle]() {
            dlclose(handle);
            }).detach();
#endif
    }

	template <typename Callable>
	void run_async(Callable&& func) {
		if (this->type == backend_type::Windows) {
#if defined(_WIN32) || defined(WIN32)
            winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, std::forward<Callable>(func));
#endif
        }
		else {
			std::thread(std::forward<Callable>(func)).detach();
		}
	}

    template<typename... Args>
	void set_title(const std::string& str, Args&&... args) {
        const std::string title = fmt::vformat(str, fmt::make_format_args(args...));
        if (this->type == backend_type::Windows) {
#if defined(_WIN32) || defined(WIN32)
			winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(winrt::to_hstring(title));
#endif
        }
        else {
            
        }

    }

    void shutdown() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        exit_thread(this->handle);
    }
};