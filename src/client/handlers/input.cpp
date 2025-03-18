#include "input.hpp"

inline float ConvertDipsToPixels(float dips, float dpi) {
    static const float dipsPerInch = 96.0f;
    return floorf(dips * dpi / dipsPerInch + 0.5f);
}

namespace selaura_handlers {

    input_key keys::Escape = { "Escape", 1 };

    input_key keys::F1 = { "F1", 59 };
    input_key keys::F2 = { "F2", 60 };
    input_key keys::F3 = { "F3", 61 };
    input_key keys::F4 = { "F4", 62 };
    input_key keys::F5 = { "F5", 63 };
    input_key keys::F6 = { "F6", 64 };
    input_key keys::F7 = { "F7", 65 };
    input_key keys::F8 = { "F8", 66 };
    input_key keys::F9 = { "F9", 67 };
    input_key keys::F10 = { "F10", 68 };
    input_key keys::F11 = { "F11", 87 };
    input_key keys::F12 = { "F12", 88 };

    input_key keys::Grave = { "`", 41 };
    input_key keys::Number1 = { "1", 2 };
    input_key keys::Number2 = { "2", 3 };
    input_key keys::Number3 = { "3", 4 };
    input_key keys::Number4 = { "4", 5 };
    input_key keys::Number5 = { "5", 6 };
    input_key keys::Number6 = { "6", 7 };
    input_key keys::Number7 = { "7", 8 };
    input_key keys::Number8 = { "8", 9 };
    input_key keys::Number9 = { "9", 10 };
    input_key keys::Number0 = { "0", 11 };
    input_key keys::Minus = { "Minus", 12 };
    input_key keys::Equals = { "Equals", 13 };
    input_key keys::Backspace = { "Back", 14 };

    input_key keys::Tab = { "Tab", 15 };
    input_key keys::Q = { "Q", 16 };
    input_key keys::W = { "W", 17 };
    input_key keys::E = { "E", 18 };
    input_key keys::R = { "R", 19 };
    input_key keys::T = { "T", 20 };
    input_key keys::Y = { "Y", 21 };
    input_key keys::U = { "U", 22 };
    input_key keys::I = { "I", 23 };
    input_key keys::O = { "O", 24 };
    input_key keys::P = { "P", 25 };
    input_key keys::LeftBracket = { "LeftBracket", 26 };
    input_key keys::RightBracket = { "RightBracket", 27 };
    input_key keys::Backslash = { "", 43 };

    input_key keys::CapsLock = { "CapitalLock", 58 };
    input_key keys::A = { "A", 30 };
    input_key keys::S = { "S", 31 };
    input_key keys::D = { "D", 32 };
    input_key keys::F = { "F", 33 };
    input_key keys::G = { "G", 34 };
    input_key keys::H = { "H", 35 };
    input_key keys::J = { "J", 36 };
    input_key keys::K = { "K", 37 };
    input_key keys::L = { "L", 38 };
    input_key keys::Semicolon = { "Semicolon", 39 };
    input_key keys::Apostrophe = { "Apostrophe", 40 };
    input_key keys::Enter = { "Enter", 28 };

    input_key keys::LeftShift = { "Shift", 42 };
    input_key keys::Z = { "Z", 44 };
    input_key keys::X = { "X", 45 };
    input_key keys::C = { "C", 46 };
    input_key keys::V = { "V", 47 };
    input_key keys::B = { "B", 48 };
    input_key keys::N = { "N", 49 };
    input_key keys::M = { "M", 50 };
    input_key keys::Comma = { "", 51 };
    input_key keys::Period = { "", 52 };
    input_key keys::Slash = { "", 53 };
    input_key keys::RightShift = { "Shift", 54 };

    input_key keys::Control = { "Control", 29 };
    input_key keys::Space = { "Space", 57 };

    input_key keys::Windows = { "Windows", 91 };
    input_key keys::Menu = { "Menu", 93 };

    input_key keys::Insert = { "Insert", 210 };
    input_key keys::Delete = { "Delete", 211 };
    input_key keys::Home = { "Home", 199 };
    input_key keys::End = { "End", 207 };
    input_key keys::PageUp = { "PageUp", 201 };
    input_key keys::PageDown = { "PageDown", 209 };
    input_key keys::Up = { "Up", 200 };
    input_key keys::Down = { "Down", 208 };
    input_key keys::Left = { "Left", 203 };
    input_key keys::Right = { "Right", 205 };

	int mouse::Left = 0;
	int mouse::Right = 1;
	int mouse::Middle = 2;

    std::unordered_map<input_key, bool> input::m_keyStates;
    std::unordered_map<input_key, bool> input::m_keyPressed;
    std::unordered_map<input_key, bool> input::m_keyReleased;

    float input::m_x = 0.0f;
    float input::m_y = 0.0f;
    std::unordered_map<int, bool> input::m_buttonStates;
    std::unordered_map<int, bool> input::m_buttonPressed;
    std::unordered_map<int, bool> input::m_buttonReleased;
    float input::m_wheelDelta = 0.0f;

	float input::dpi = 96;

    winrt::event_token input::m_keyDownToken;
    winrt::event_token input::m_keyUpToken;
    winrt::event_token input::m_charRecievedToken;

    winrt::event_token input::m_pointerMovedToken;
    winrt::event_token input::m_pointerExitedToken;
    winrt::event_token input::m_pointerPressedToken;
    winrt::event_token input::m_pointerReleasedToken;
    winrt::event_token input::m_pointerWheelChangedToken;

    winrt::event_token input::m_dpiChangedToken;

    winrt::Windows::UI::Core::CoreWindow input::m_window = nullptr;

    void input::initialize(winrt::Windows::UI::Core::CoreWindow const& window) {
        m_window = window;
        m_keyDownToken = m_window.KeyDown({ &input::OnKeyDown });
        m_keyUpToken = m_window.KeyUp({ &input::OnKeyUp });
        m_charRecievedToken = m_window.CharacterReceived({ &input::OnCharReceived });
        m_pointerMovedToken = m_window.PointerMoved({ &input::OnPointerMoved });
        m_pointerExitedToken = m_window.PointerExited({ &input::OnPointerExited });
        m_pointerPressedToken = m_window.PointerPressed({ &input::OnPointerPressed });
        m_pointerReleasedToken = m_window.PointerReleased({ &input::OnPointerReleased });
        m_pointerWheelChangedToken = m_window.PointerWheelChanged({ &input::OnPointerWheelChanged });

        dpi = 96;
        auto displayInformation = winrt::Windows::Graphics::Display::DisplayInformation::GetForCurrentView();
		dpi = displayInformation.LogicalDpi();
		m_dpiChangedToken = displayInformation.DpiChanged({ &input::OnDpiChanged });
    }

    void input::shutdown() {
        m_window.KeyDown(m_keyDownToken);
        m_window.KeyUp(m_keyUpToken);
        m_window.CharacterReceived(m_charRecievedToken);
        m_window.PointerMoved(m_pointerMovedToken);
        m_window.PointerExited(m_pointerExitedToken);
        m_window.PointerPressed(m_pointerPressedToken);
        m_window.PointerReleased(m_pointerReleasedToken);
        m_window.PointerWheelChanged(m_pointerWheelChangedToken);

        m_keyStates.clear();
        m_keyPressed.clear();
        m_keyReleased.clear();
        m_buttonStates.clear();
        m_buttonPressed.clear();
        m_buttonReleased.clear();
        m_wheelDelta = 0.0f;
    }

    bool input::is_key_down(input_key key) {
        return m_keyStates[key];
    }

    bool input::is_key_pressed(input_key key) {
        bool pressed = m_keyPressed[key];
        m_keyPressed[key] = false;
        return pressed;
    }

    bool input::is_key_released(input_key key) {
        bool released = m_keyReleased[key];
        m_keyReleased[key] = false;
        return released;
    }

    float input::get_mouse_x() noexcept {
        return m_x;
    }

    float input::get_mouse_y() noexcept {
        return m_y;
    }

    bool input::is_button_down(int button) {
        return m_buttonStates[button];
    }

    bool input::is_button_pressed(int button) {
        bool pressed = m_buttonPressed[button];
        m_buttonPressed[button] = false;
        return pressed;
    }

    bool input::is_button_released(int button) {
        bool released = m_buttonReleased[button];
        m_buttonReleased[button] = false;
        return released;
    }

    float input::get_wheel_delta() {
        float delta = m_wheelDelta;
        m_wheelDelta = 0.0f;
        return delta;
    }

    void input::OnKeyDown(winrt::Windows::UI::Core::CoreWindow const& sender,
        winrt::Windows::UI::Core::KeyEventArgs const& args) {

        auto key = args.VirtualKey();
        auto translated_key = input_key{ std::string{ magic_enum::enum_name(key) }, args.KeyStatus().ScanCode };
        if (!m_keyStates[translated_key]) {
            m_keyPressed[translated_key] = true;
        }
        m_keyStates[translated_key] = true;

		auto event = selaura_event_types::KeyDown{ &translated_key };
		selaura_handlers::event::dispatch<selaura_event_types::KeyDown>(event);

		logger::debug("Key Down: {}, {}", translated_key.name, translated_key.scancode);
    }

    void input::OnKeyUp(winrt::Windows::UI::Core::CoreWindow const& sender,
        winrt::Windows::UI::Core::KeyEventArgs const& args) {

        auto key = args.VirtualKey();
        auto translated_key = input_key{ std::string{ magic_enum::enum_name(key) }, args.KeyStatus().ScanCode };
        m_keyStates[translated_key] = false;
        m_keyReleased[translated_key] = true;

		auto event = selaura_event_types::KeyUp{ &translated_key };
		selaura_handlers::event::dispatch<selaura_event_types::KeyUp>(event);
    }

    void input::OnCharReceived(winrt::Windows::UI::Core::CoreWindow const& sender,
        winrt::Windows::UI::Core::CharacterReceivedEventArgs const& args) {

		auto character = args.KeyCode();
		auto event = selaura_event_types::CharReceived{ character };
		selaura_handlers::event::dispatch<selaura_event_types::CharReceived>(event);
    }

    void input::OnPointerMoved(winrt::Windows::UI::Core::CoreWindow const& sender,
        winrt::Windows::UI::Core::PointerEventArgs const& args) {
        auto point = args.CurrentPoint();
        auto pos = point.Position();
        m_x = ConvertDipsToPixels(pos.X, dpi);
        m_y = ConvertDipsToPixels(pos.Y, dpi);

		auto event = selaura_event_types::PointerMoved{ m_x, m_y };

		selaura_handlers::event::dispatch<selaura_event_types::PointerMoved>(event);
    }

    void input::OnPointerExited(winrt::Windows::UI::Core::CoreWindow const& sender,
        winrt::Windows::UI::Core::PointerEventArgs const& args) {
        m_x = -1.0f;
        m_y = -1.0f;

		auto event = selaura_event_types::PointerExited{};
		selaura_handlers::event::dispatch<selaura_event_types::PointerExited>(event);
    }

    void input::OnPointerPressed(winrt::Windows::UI::Core::CoreWindow const& sender,
        winrt::Windows::UI::Core::PointerEventArgs const& args) {
        auto point = args.CurrentPoint();
        auto pos = point.Position();
        m_x = ConvertDipsToPixels(pos.X, dpi);
        m_y = ConvertDipsToPixels(pos.Y, dpi);

        int state = -1;
        auto updateKind = point.Properties().PointerUpdateKind();

        switch (updateKind) {
        case winrt::Windows::UI::Input::PointerUpdateKind::LeftButtonPressed:
            m_buttonStates[0] = true;
            m_buttonPressed[0] = true;
            state = 0;
            break;
        case winrt::Windows::UI::Input::PointerUpdateKind::RightButtonPressed:
            m_buttonStates[1] = true;
            m_buttonPressed[1] = true;
            state = 1;
            break;
        case winrt::Windows::UI::Input::PointerUpdateKind::MiddleButtonPressed:
            m_buttonStates[2] = true;
            m_buttonPressed[2] = true;
            state = 2;
            break;
        default:
            break;
        }

        if (state != -1) {
            auto event = selaura_event_types::PointerPressed{ m_x, m_y, state };
            selaura_handlers::event::dispatch<selaura_event_types::PointerPressed>(event);
        }

        args.Handled(true);
    }


    void input::OnPointerReleased(winrt::Windows::UI::Core::CoreWindow const& sender,
        winrt::Windows::UI::Core::PointerEventArgs const& args) {
        auto point = args.CurrentPoint();
        auto pos = point.Position();
        m_x = ConvertDipsToPixels(pos.X, dpi);
        m_y = ConvertDipsToPixels(pos.Y, dpi);

        int state = -1;
        auto updateKind = point.Properties().PointerUpdateKind();

        switch (updateKind) {
        case winrt::Windows::UI::Input::PointerUpdateKind::LeftButtonReleased:
            m_buttonStates[0] = false;
            m_buttonReleased[0] = true;
            state = 0;
            break;
        case winrt::Windows::UI::Input::PointerUpdateKind::RightButtonReleased:
            m_buttonStates[1] = false;
            m_buttonReleased[1] = true;
            state = 1;
            break;
        case winrt::Windows::UI::Input::PointerUpdateKind::MiddleButtonReleased:
            m_buttonStates[2] = false;
            m_buttonReleased[2] = true;
            state = 2;
            break;
        default:
            break;
        }

        if (state != -1) {
            logger::debug("release {}", state);
            auto event = selaura_event_types::PointerReleased{ m_x, m_y, state };
            selaura_handlers::event::dispatch<selaura_event_types::PointerReleased>(event);
        }

        args.Handled(true);
    }


    void input::OnPointerWheelChanged(winrt::Windows::UI::Core::CoreWindow const& sender,
        winrt::Windows::UI::Core::PointerEventArgs const& args) {
        auto point = args.CurrentPoint();
        m_wheelDelta += point.Properties().MouseWheelDelta();

		auto event = selaura_event_types::PointerWheelChanged{ m_wheelDelta };
		selaura_handlers::event::dispatch<selaura_event_types::PointerWheelChanged>(event);
    }

	void input::OnDpiChanged(winrt::Windows::Graphics::Display::DisplayInformation const& sender,
		winrt::Windows::Foundation::IInspectable const& args) {
        
        float dpi = sender.LogicalDpi();
	}
}
