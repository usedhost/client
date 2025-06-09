#include "input_manager.hpp"

#include "../instance.hpp"
#include "magic_vtable.hpp"

namespace selaura {

    void input_manager::init() {
#ifdef SELAURA_WINDOWS
        winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [&]() {
            init_winrt_hooks();
        });
#endif
    }

#ifdef SELAURA_WINDOWS
    void input_manager::init_winrt_hooks() {
        auto coreWindow = winrt::Windows::UI::Core::CoreWindow::GetForCurrentThread();

    }

    void input_manager::key_down_hk(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::KeyEventArgs const& args) {
        spdlog::info("key scan code {}", args.KeyStatus().ScanCode);
    }
#endif
};