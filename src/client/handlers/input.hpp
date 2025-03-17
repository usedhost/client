#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Input.h>
#include <winrt/windows.graphics.display.h>
#include <Windows.h>

#include <magic_enum/magic_enum.hpp>
#include <functional>
#include <string>
#include <unordered_map>
#include <imgui/imgui.h>

#include "../io/logger.hpp"
#include "event.hpp"

namespace selaura_handlers {
    struct input_key {
        std::string name;
        uint32_t scancode;

        bool operator==(const input_key& other) const noexcept {
            return name == other.name && scancode == other.scancode;
        }
    };

    namespace keys {
        extern input_key Escape;
        extern input_key F1;
        extern input_key F2;
        extern input_key F3;
        extern input_key F4;
        extern input_key F5;
        extern input_key F6;
        extern input_key F7;
        extern input_key F8;
        extern input_key F9;
        extern input_key F10;
        extern input_key F11;
        extern input_key F12;

        extern input_key Grave;
        extern input_key Number1;
        extern input_key Number2;
        extern input_key Number3; 
        extern input_key Number4;
        extern input_key Number5; 
        extern input_key Number6;
        extern input_key Number7;
        extern input_key Number8;
        extern input_key Number9;
        extern input_key Number0;
        extern input_key Minus; 
        extern input_key Equals;
        extern input_key Backspace;

        extern input_key Tab;
        extern input_key Q;
        extern input_key W;
        extern input_key E;
        extern input_key R;
        extern input_key T;
        extern input_key Y;
        extern input_key U;
        extern input_key I;
        extern input_key O;
        extern input_key P;
        extern input_key LeftBracket;
        extern input_key RightBracket;
        extern input_key Backslash;

        extern input_key CapsLock;
        extern input_key A;
        extern input_key S;
        extern input_key D;
        extern input_key F;
        extern input_key G;
        extern input_key H;
        extern input_key J;
        extern input_key K;
        extern input_key L;
        extern input_key Semicolon;
        extern input_key Apostrophe;
        extern input_key Enter;

        extern input_key LeftShift;
        extern input_key Z;
        extern input_key X;
        extern input_key C;
        extern input_key V;
        extern input_key B;
        extern input_key N;
        extern input_key M;
        extern input_key Comma;
        extern input_key Period;
        extern input_key Slash;
        extern input_key RightShift;

        extern input_key Space;
        extern input_key Control;

        extern input_key Windows;
        extern input_key Menu;

        extern input_key Insert;
        extern input_key Delete;
        extern input_key Home;
        extern input_key End;
        extern input_key PageUp;
        extern input_key PageDown;
        extern input_key Up;
        extern input_key Down;
        extern input_key Left;
        extern input_key Right;
    };

    namespace mouse {
        extern int Left;
		extern int Right;
		extern int Middle;
    };

    class input {
    public:
        static void initialize(winrt::Windows::UI::Core::CoreWindow const& window);
        static void shutdown();

        static bool is_key_down(input_key key);
        static bool is_key_pressed(input_key key);
        static bool is_key_released(input_key key);

        static float get_mouse_x() noexcept;
        static float get_mouse_y() noexcept;
        static bool is_button_down(int button);
        static bool is_button_pressed(int button);
        static bool is_button_released(int button);
        static float get_wheel_delta();

    private:
        static std::unordered_map<input_key, bool> m_keyStates;
        static std::unordered_map<input_key, bool> m_keyPressed;
        static std::unordered_map<input_key, bool> m_keyReleased;

        static float m_x;
        static float m_y;
        static std::unordered_map<int, bool> m_buttonStates;
        static std::unordered_map<int, bool> m_buttonPressed;
        static std::unordered_map<int, bool> m_buttonReleased;
        static float m_wheelDelta;

        static float dpi;

        static winrt::event_token m_keyDownToken;
        static winrt::event_token m_keyUpToken;
        static winrt::event_token m_charRecievedToken;

        static winrt::event_token m_pointerMovedToken;
        static winrt::event_token m_pointerExitedToken;
        static winrt::event_token m_pointerPressedToken;
        static winrt::event_token m_pointerReleasedToken;
        static winrt::event_token m_pointerWheelChangedToken;

        static winrt::event_token m_dpiChangedToken;

        static void OnKeyDown(winrt::Windows::UI::Core::CoreWindow const& sender,
            winrt::Windows::UI::Core::KeyEventArgs const& args);
        static void OnKeyUp(winrt::Windows::UI::Core::CoreWindow const& sender,
            winrt::Windows::UI::Core::KeyEventArgs const& args);
        static void OnCharReceived(winrt::Windows::UI::Core::CoreWindow const& sender,
            winrt::Windows::UI::Core::CharacterReceivedEventArgs const& args);
        static void OnPointerMoved(winrt::Windows::UI::Core::CoreWindow const& sender,
            winrt::Windows::UI::Core::PointerEventArgs const& args);
        static void OnPointerExited(winrt::Windows::UI::Core::CoreWindow const& sender,
            winrt::Windows::UI::Core::PointerEventArgs const& args);
        static void OnPointerPressed(winrt::Windows::UI::Core::CoreWindow const& sender,
            winrt::Windows::UI::Core::PointerEventArgs const& args);
        static void OnPointerReleased(winrt::Windows::UI::Core::CoreWindow const& sender,
            winrt::Windows::UI::Core::PointerEventArgs const& args);
        static void OnPointerWheelChanged(winrt::Windows::UI::Core::CoreWindow const& sender,
            winrt::Windows::UI::Core::PointerEventArgs const& args);
		static void OnDpiChanged(winrt::Windows::Graphics::Display::DisplayInformation const& sender,
			winrt::Windows::Foundation::IInspectable const& args);

        static winrt::Windows::UI::Core::CoreWindow m_window;
    };

}

namespace std {
    template <>
    struct hash<selaura_handlers::input_key> {
        std::size_t operator()(const selaura_handlers::input_key& k) const noexcept {
            std::size_t h1 = std::hash<std::string>{}(k.name);
            std::size_t h2 = std::hash<uint32_t>{}(k.scancode);
            return h1 ^ (h2 << 1);
        }
    };
}
