#include "input_manager.hpp"

#include "../instance.hpp"

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

        auto token = coreWindow.Dispatcher().AcceleratorKeyActivated({&input_manager::key_hk});
        auto mouse_token = coreWindow.PointerMoved({ &input_manager::pointer_moved_hk });
    }

    void input_manager::key_hk(winrt::Windows::UI::Core::CoreDispatcher const& sender, winrt::Windows::UI::Core::AcceleratorKeyEventArgs const& args) {
        auto inst = selaura::instance::get();
        auto evm = inst->get<selaura::event_manager>();

        bool cancelled = false;

        selaura::key_action action = selaura::key_action::unknown;
        using Type = winrt::Windows::UI::Core::CoreAcceleratorKeyEventType;

        switch (args.EventType()) {
            case Type::KeyDown:         action = selaura::key_action::key_down; break;
            case Type::KeyUp:           action = selaura::key_action::key_up; break;
            case Type::SystemKeyDown:   action = selaura::key_action::system_key_down; break;
            case Type::SystemKeyUp:     action = selaura::key_action::system_key_up; break;
            default: break;
        }

        selaura::key_event ev{&cancelled, static_cast<uint32_t>(args.VirtualKey()), action};
        evm.dispatch<selaura::key_event>(ev);

        if (cancelled) {
            args.Handled(true);
        }
    }

    void input_manager::pointer_moved_hk(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::PointerEventArgs const& args) {
        //spdlog::info("mouse pos x: {}, y: {}", args.CurrentPoint().Position().X, args.CurrentPoint().Position().Y);
        //args.Handled(true);
    }
#endif
};