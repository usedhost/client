#pragma once
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Input.h>

#define MAGIC_ENUM_HEADER_ONLY
#include <magic_enum/magic_enum.hpp>

#include <functional>

namespace selaura_handlers {
	class input {
	public:

		struct key {
			//winrt::Windows::System::VirtualKey vkey;
			std::string name;
			uint32_t scancode;

			bool operator==(const key& other) const {
				return name == other.name && scancode == other.scancode;
			}
		};

		static void initialize(winrt::Windows::UI::Core::CoreWindow const& window);
		static void shutdown();

		static bool is_key_down(input::key key);
		static bool is_key_pressed(input::key key);
		static bool is_key_released(input::key key);

		static bool is_key_down(std::string key_name);
		static bool is_key_pressed(std::string key_name);
		static bool is_key_released(std::string key_name);

		static float get_mouse_x();
		static float get_mouse_y();
		static bool is_button_down(int button);
		static bool is_button_pressed(int button);
		static bool is_button_released(int button);
		static float get_wheel_delta();
	private:
		static std::unordered_map<input::key, bool> m_keyStates;
		static std::unordered_map<input::key, bool> m_keyPressed;
		static std::unordered_map<input::key, bool> m_keyReleased;

		static float m_x;
		static float m_y;
		static std::unordered_map<int, bool> m_buttonStates;
		static std::unordered_map<int, bool> m_buttonPressed;
		static std::unordered_map<int, bool> m_buttonReleased;
		static float m_wheelDelta;

		static winrt::event_token m_keyDownToken;
		static winrt::event_token m_keyUpToken;
		static winrt::event_token m_charRecievedToken;

		static winrt::event_token m_pointerMovedToken;
		static winrt::event_token m_pointerExitedToken;
		static winrt::event_token m_pointerPressedToken;
		static winrt::event_token m_pointerReleasedToken;
		static winrt::event_token m_pointerWheelChangedToken;

		static void OnKeyDown(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::KeyEventArgs const& args);
		static void OnKeyUp(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::KeyEventArgs const& args);
		static void OnCharReceived(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::CharacterReceivedEventArgs const& args);
		static void OnPointerMoved(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::PointerEventArgs const& args);
		static void OnPointerExited(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::PointerEventArgs const& args);
		static void OnPointerPressed(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::PointerEventArgs const& args);
		static void OnPointerReleased(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::PointerEventArgs const& args);
		static void OnPointerWheelChanged(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::PointerEventArgs const& args);

		static winrt::Windows::UI::Core::CoreWindow m_window;
	};
};

namespace std {
	template <>
	struct hash<selaura_handlers::input::key> {
		std::size_t operator()(const selaura_handlers::input::key& k) const {
			std::size_t h1 = std::hash<std::string>{}(k.name);
			std::size_t h2 = std::hash<uint32_t>{}(k.scancode);
			return h1 ^ (h2 << 1);
		}
	};
}