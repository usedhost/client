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


    selaura::key input_manager::translate_key(winrt::Windows::System::VirtualKey vkey) {
        uint32_t key = static_cast<uint32_t>(vkey);

        switch (key) {
            case 0x09: return selaura::key::Tab;
            case 0x25: return selaura::key::LeftArrow;
            case 0x27: return selaura::key::RightArrow;
            case 0x26: return selaura::key::UpArrow;
            case 0x28: return selaura::key::DownArrow;
            case 0x21: return selaura::key::PageUp;
            case 0x22: return selaura::key::PageDown;
            case 0x24: return selaura::key::Home;
            case 0x23: return selaura::key::End;
            case 0x2D: return selaura::key::Insert;
            case 0x2E: return selaura::key::Delete;
            case 0x08: return selaura::key::Backspace;
            case 0x20: return selaura::key::Space;
            case 0x0D: return selaura::key::Enter;
            case 0x1B: return selaura::key::Escape;

            case 0xA2: return selaura::key::LeftCtrl;
            case 0xA0: return selaura::key::LeftShift;
            case 0xA4: return selaura::key::LeftAlt;
            case 0x5B: return selaura::key::LeftSuper;

            case 0xA3: return selaura::key::RightCtrl;
            case 0xA1: return selaura::key::RightShift;
            case 0xA5: return selaura::key::RightAlt;
            case 0x5C: return selaura::key::RightSuper;

            case 0x5D: return selaura::key::Menu;

            case 0x30: return selaura::key::NUM_0;
            case 0x31: return selaura::key::NUM_1;
            case 0x32: return selaura::key::NUM_2;
            case 0x33: return selaura::key::NUM_3;
            case 0x34: return selaura::key::NUM_4;
            case 0x35: return selaura::key::NUM_5;
            case 0x36: return selaura::key::NUM_6;
            case 0x37: return selaura::key::NUM7;
            case 0x38: return selaura::key::NUM_8;
            case 0x39: return selaura::key::NUM_9;

            case 0x41: return selaura::key::A;
            case 0x42: return selaura::key::B;
            case 0x43: return selaura::key::C;
            case 0x44: return selaura::key::D;
            case 0x45: return selaura::key::E;
            case 0x46: return selaura::key::F;
            case 0x47: return selaura::key::G;
            case 0x48: return selaura::key::H;
            case 0x49: return selaura::key::I;
            case 0x4A: return selaura::key::J;
            case 0x4B: return selaura::key::K;
            case 0x4C: return selaura::key::L;
            case 0x4D: return selaura::key::M;
            case 0x4E: return selaura::key::N;
            case 0x4F: return selaura::key::O;
            case 0x50: return selaura::key::P;
            case 0x51: return selaura::key::Q;
            case 0x52: return selaura::key::R;
            case 0x53: return selaura::key::S;
            case 0x54: return selaura::key::T;
            case 0x55: return selaura::key::U;
            case 0x56: return selaura::key::V;
            case 0x57: return selaura::key::W;
            case 0x58: return selaura::key::X;
            case 0x59: return selaura::key::Y;
            case 0x5A: return selaura::key::Z;

            case 0x70: return selaura::key::F1;
            case 0x71: return selaura::key::F2;
            case 0x72: return selaura::key::F3;
            case 0x73: return selaura::key::F4;
            case 0x74: return selaura::key::F5;
            case 0x75: return selaura::key::F6;
            case 0x76: return selaura::key::F7;
            case 0x77: return selaura::key::F8;
            case 0x78: return selaura::key::F9;
            case 0x79: return selaura::key::F10;
            case 0x7A: return selaura::key::F11;
            case 0x7B: return selaura::key::F12;

            case 0x14: return selaura::key::CapsLock;
            case 0x91: return selaura::key::ScrollLock;
            case 0x90: return selaura::key::NumLock;
            case 0x2C: return selaura::key::PrintScreen;
            case 0x13: return selaura::key::Pause;

            case 0x6E: return selaura::key::KeypadDecimal;
            case 0x6F: return selaura::key::KeypadDivide;
            case 0x6A: return selaura::key::KeypadMultiply;
            case 0x6D: return selaura::key::KeypadSubtract;
            case 0x6B: return selaura::key::KeypadAdd;
            case 0xBB: return selaura::key::Equal;
            case 0xBA: return selaura::key::Semicolon;
            case 0xBD: return selaura::key::Minus;
            case 0xBC: return selaura::key::Comma;
            case 0xBE: return selaura::key::Period;
            case 0xBF: return selaura::key::Slash;
            case 0xC0: return selaura::key::GraveAccent;
            case 0xDB: return selaura::key::LeftBracket;
            case 0xDC: return selaura::key::Backslash;
            case 0xDD: return selaura::key::RightBracket;
            case 0xDE: return selaura::key::Apostrophe;
            case 0xE2: return selaura::key::Oem102;

            default: return selaura::key::None;
        }
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

        selaura::key_event ev{&cancelled, translate_key(args.VirtualKey()), action};
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