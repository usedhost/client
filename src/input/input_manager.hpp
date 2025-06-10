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
        static void key_hk(winrt::Windows::UI::Core::CoreDispatcher const& sender, winrt::Windows::UI::Core::AcceleratorKeyEventArgs const& args);
        static void pointer_moved_hk(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::PointerEventArgs const& args);
#endif

        // jni hooks

    };
};