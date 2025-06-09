#pragma once

#ifdef SELAURA_WINDOWS
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Input.h>
#include <winrt/windows.graphics.display.h>
#include <Windows.h>
#endif

namespace selaura {
    struct input_manager {

        void init();

#ifdef SELAURA_WINDOWS
        void init_winrt_hooks();
        void key_down_hk(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::KeyEventArgs const& args);
#endif

        // jni hooks

    };
};