#include "input.hpp"

namespace selaura_handlers {
	std::unordered_map<input::key, bool> input::m_keyStates;
	std::unordered_map<input::key, bool> input::m_keyPressed;
	std::unordered_map<input::key, bool> input::m_keyReleased;

	float input::m_x;
	float input::m_y;
	std::unordered_map<int, bool> input::m_buttonStates;
	std::unordered_map<int, bool> input::m_buttonPressed;
	std::unordered_map<int, bool> input::m_buttonReleased;
	float input::m_wheelDelta;

	winrt::event_token input::m_keyDownToken;
	winrt::event_token input::m_keyUpToken;
	winrt::event_token input::m_charRecievedToken;

	winrt::event_token input::m_pointerMovedToken;
	winrt::event_token input::m_pointerExitedToken;
	winrt::event_token input::m_pointerPressedToken;
	winrt::event_token input::m_pointerReleasedToken;
	winrt::event_token input::m_pointerWheelChangedToken;

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

	bool input::is_key_down(input::key key) {
		return m_keyStates[key];
	}

	bool input::is_key_pressed(input::key key) {
		bool pressed = m_keyPressed[key];
		m_keyPressed[key] = false;
		return pressed;
	}

	bool input::is_key_released(input::key key) {
		bool released = m_keyReleased[key];
		m_keyReleased[key] = false;
		return released;
	}

	bool input::is_key_down(std::string key_name) {
		std::string translated_key_name;
		uint32_t scancode;
		if (key_name == "RightShift") {
			translated_key_name = "Shift";
			scancode = 54;
		}
		else if (key_name == "LeftShift") {
			translated_key_name = "Shift";
			scancode = 42;
		}
		else {
			translated_key_name = key_name;
		}

		for (const auto& [key, state] : m_keyStates) {
			if (key.name == translated_key_name && state) {
				if (key.name == "Shift") {
					if (key.scancode == scancode) {
						return true;
					}
				}
				else {
					return true;
				}
				return true;
			}
		}
		return false;
	}

	bool input::is_key_pressed(std::string key_name) {
		for (auto& [key, pressed] : m_keyPressed) {
			if (key.name == key_name && pressed) {
				pressed = false;
				return true;
			}
		}
		return false;
	}

	bool input::is_key_released(std::string key_name) {
		for (auto& [key, released] : m_keyReleased) {
			if (key.name == key_name && released) {
				released = false;
				return true;
			}
		}
		return false;
	}

	float input::get_mouse_x() {
		return m_x;
	}

	float input::get_mouse_y() {
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
		auto translated_key = input::key{ std::string{ magic_enum::enum_name(key) }, args.KeyStatus().ScanCode };
		if (!m_keyStates[translated_key]) {
			m_keyPressed[translated_key] = true;
		}
		m_keyStates[translated_key] = true;
	}

	void input::OnKeyUp(winrt::Windows::UI::Core::CoreWindow const& sender,
		winrt::Windows::UI::Core::KeyEventArgs const& args) {

		auto key = args.VirtualKey();
		auto translated_key = input::key{ std::string{ magic_enum::enum_name(key) }, args.KeyStatus().ScanCode };
		m_keyStates[translated_key] = false;
		m_keyReleased[translated_key] = true;
	}

	void input::OnCharReceived(winrt::Windows::UI::Core::CoreWindow const& sender,
		winrt::Windows::UI::Core::CharacterReceivedEventArgs const& args) {
	}

	void input::OnPointerMoved(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::PointerEventArgs const& args) {
		winrt::Windows::UI::Input::PointerPoint point = args.CurrentPoint();
		winrt::Windows::Foundation::Point pos = point.Position();
		m_x = pos.X;
		m_y = pos.Y;
	}

	void input::OnPointerExited(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::PointerEventArgs const& args) {
		m_x = -1.0f;
		m_y = -1.0f;
	}

	void input::OnPointerPressed(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::PointerEventArgs const& args) {
		winrt::Windows::UI::Input::PointerPoint point = args.CurrentPoint();
		winrt::Windows::Foundation::Point pos = point.Position();
		m_x = pos.X;
		m_y = pos.Y;
		if (point.Properties().IsLeftButtonPressed()) {
			m_buttonStates[0] = true;
			m_buttonPressed[0] = true;
		}
		if (point.Properties().IsRightButtonPressed()) {
			m_buttonStates[1] = true;
			m_buttonPressed[1] = true;
		}
		if (point.Properties().IsMiddleButtonPressed()) {
			m_buttonStates[2] = true;
			m_buttonPressed[2] = true;
		}
	}

	void input::OnPointerReleased(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::PointerEventArgs const& args) {
		winrt::Windows::UI::Input::PointerPoint point = args.CurrentPoint();
		winrt::Windows::Foundation::Point pos = point.Position();
		m_x = pos.X;
		m_y = pos.Y;
		if (!point.Properties().IsLeftButtonPressed()) {
			m_buttonStates[0] = false;
			m_buttonReleased[0] = true;
		}
		if (!point.Properties().IsRightButtonPressed()) {
			m_buttonStates[1] = false;
			m_buttonReleased[1] = true;
		}
		if (!point.Properties().IsMiddleButtonPressed()) {
			m_buttonStates[2] = false;
			m_buttonReleased[2] = true;
		}
	}

	void input::OnPointerWheelChanged(winrt::Windows::UI::Core::CoreWindow const& sender, winrt::Windows::UI::Core::PointerEventArgs const& args) {
		winrt::Windows::UI::Input::PointerPoint point = args.CurrentPoint();
		m_wheelDelta += point.Properties().MouseWheelDelta();
	}

}