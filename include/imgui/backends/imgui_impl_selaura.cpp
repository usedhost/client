#include "imgui_impl_selaura.hpp"

struct ImGui_ImplSelaura_Data {
	HWND hwnd;
};

static ImGui_ImplSelaura_Data* ImGui_ImplSelaura_GetBackendData() {
	return ImGui::GetCurrentContext() ? (ImGui_ImplSelaura_Data*)ImGui::GetIO().BackendPlatformUserData : nullptr;
}

static ImGuiKey ConvertInputKeyToImGuiKey(const selaura_handlers::input_key& key) {

    if (key == selaura_handlers::keys::Escape)               return ImGuiKey_Escape;
    else if (key == selaura_handlers::keys::F1)              return ImGuiKey_F1;
    else if (key == selaura_handlers::keys::F2)              return ImGuiKey_F2;
    else if (key == selaura_handlers::keys::F3)              return ImGuiKey_F3;
    else if (key == selaura_handlers::keys::F4)              return ImGuiKey_F4;
    else if (key == selaura_handlers::keys::F5)              return ImGuiKey_F5;
    else if (key == selaura_handlers::keys::F6)              return ImGuiKey_F6;
    else if (key == selaura_handlers::keys::F7)              return ImGuiKey_F7;
    else if (key == selaura_handlers::keys::F8)              return ImGuiKey_F8;
    else if (key == selaura_handlers::keys::F9)              return ImGuiKey_F9;
    else if (key == selaura_handlers::keys::F10)             return ImGuiKey_F10;
    else if (key == selaura_handlers::keys::F11)             return ImGuiKey_F11;
    else if (key == selaura_handlers::keys::F12)             return ImGuiKey_F12;
    else if (key == selaura_handlers::keys::Grave)           return ImGuiKey_GraveAccent;
    else if (key == selaura_handlers::keys::Number1)         return ImGuiKey_1;
    else if (key == selaura_handlers::keys::Number2)         return ImGuiKey_2;
    else if (key == selaura_handlers::keys::Number3)         return ImGuiKey_3;
    else if (key == selaura_handlers::keys::Number4)         return ImGuiKey_4;
    else if (key == selaura_handlers::keys::Number5)         return ImGuiKey_5;
    else if (key == selaura_handlers::keys::Number6)         return ImGuiKey_6;
    else if (key == selaura_handlers::keys::Number7)         return ImGuiKey_7;
    else if (key == selaura_handlers::keys::Number8)         return ImGuiKey_8;
    else if (key == selaura_handlers::keys::Number9)         return ImGuiKey_9;
    else if (key == selaura_handlers::keys::Number0)         return ImGuiKey_0;
    else if (key == selaura_handlers::keys::Minus)           return ImGuiKey_Minus;
    else if (key == selaura_handlers::keys::Equals)          return ImGuiKey_Equal;
    else if (key == selaura_handlers::keys::Backspace)       return ImGuiKey_Backspace;
    else if (key == selaura_handlers::keys::Tab)             return ImGuiKey_Tab;
    else if (key == selaura_handlers::keys::Q)               return ImGuiKey_Q;
    else if (key == selaura_handlers::keys::W)               return ImGuiKey_W;
    else if (key == selaura_handlers::keys::E)               return ImGuiKey_E;
    else if (key == selaura_handlers::keys::R)               return ImGuiKey_R;
    else if (key == selaura_handlers::keys::T)               return ImGuiKey_T;
    else if (key == selaura_handlers::keys::Y)               return ImGuiKey_Y;
    else if (key == selaura_handlers::keys::U)               return ImGuiKey_U;
    else if (key == selaura_handlers::keys::I)               return ImGuiKey_I;
    else if (key == selaura_handlers::keys::O)               return ImGuiKey_O;
    else if (key == selaura_handlers::keys::P)               return ImGuiKey_P;
    else if (key == selaura_handlers::keys::LeftBracket)     return ImGuiKey_LeftBracket;
    else if (key == selaura_handlers::keys::RightBracket)    return ImGuiKey_RightBracket;
    else if (key == selaura_handlers::keys::Backslash)       return ImGuiKey_Backslash;
    else if (key == selaura_handlers::keys::CapsLock)        return ImGuiKey_CapsLock;
    else if (key == selaura_handlers::keys::A)               return ImGuiKey_A;
    else if (key == selaura_handlers::keys::S)               return ImGuiKey_S;
    else if (key == selaura_handlers::keys::D)               return ImGuiKey_D;
    else if (key == selaura_handlers::keys::F)               return ImGuiKey_F;
    else if (key == selaura_handlers::keys::G)               return ImGuiKey_G;
    else if (key == selaura_handlers::keys::H)               return ImGuiKey_H;
    else if (key == selaura_handlers::keys::J)               return ImGuiKey_J;
    else if (key == selaura_handlers::keys::K)               return ImGuiKey_K;
    else if (key == selaura_handlers::keys::L)               return ImGuiKey_L;
    else if (key == selaura_handlers::keys::Semicolon)       return ImGuiKey_Semicolon;
    else if (key == selaura_handlers::keys::Apostrophe)      return ImGuiKey_Apostrophe;
    else if (key == selaura_handlers::keys::Enter)           return ImGuiKey_Enter;
    else if (key == selaura_handlers::keys::LeftShift)       return ImGuiKey_LeftShift;
    else if (key == selaura_handlers::keys::RightShift)      return ImGuiKey_RightShift;
    else if (key == selaura_handlers::keys::Z)               return ImGuiKey_Z;
    else if (key == selaura_handlers::keys::X)               return ImGuiKey_X;
    else if (key == selaura_handlers::keys::C)               return ImGuiKey_C;
    else if (key == selaura_handlers::keys::V)               return ImGuiKey_V;
    else if (key == selaura_handlers::keys::B)               return ImGuiKey_B;
    else if (key == selaura_handlers::keys::N)               return ImGuiKey_N;
    else if (key == selaura_handlers::keys::M)               return ImGuiKey_M;
    else if (key == selaura_handlers::keys::Comma)           return ImGuiKey_Comma;
    else if (key == selaura_handlers::keys::Period)          return ImGuiKey_Period;
    else if (key == selaura_handlers::keys::Slash)           return ImGuiKey_Slash;
    else if (key == selaura_handlers::keys::Control)         return ImGuiKey_ModCtrl;
    else if (key == selaura_handlers::keys::Space)           return ImGuiKey_Space;
    else if (key == selaura_handlers::keys::Windows)         return ImGuiKey_LeftSuper;
    else if (key == selaura_handlers::keys::Menu)            return ImGuiKey_Menu;
    else if (key == selaura_handlers::keys::Insert)          return ImGuiKey_Insert;
    else if (key == selaura_handlers::keys::Delete)          return ImGuiKey_Delete;
    else if (key == selaura_handlers::keys::Home)            return ImGuiKey_Home;
    else if (key == selaura_handlers::keys::End)             return ImGuiKey_End;
    else if (key == selaura_handlers::keys::PageUp)          return ImGuiKey_PageUp;
    else if (key == selaura_handlers::keys::PageDown)        return ImGuiKey_PageDown;
    else if (key == selaura_handlers::keys::Up)              return ImGuiKey_UpArrow;
    else if (key == selaura_handlers::keys::Down)            return ImGuiKey_DownArrow;
    else if (key == selaura_handlers::keys::Left)            return ImGuiKey_LeftArrow;
    else if (key == selaura_handlers::keys::Right)           return ImGuiKey_RightArrow;
    else return ImGuiKey_None;
}

bool ImGui_ImplSelaura_Init() {
	ImGuiIO& io = ImGui::GetIO();
	IM_ASSERT(io.BackendPlatformUserData == nullptr && "Already initialized a platform backend!");

	ImGui_ImplSelaura_Data* bd = IM_NEW(ImGui_ImplSelaura_Data)();
	io.BackendPlatformUserData = (void*)bd;
	io.BackendPlatformName = "imgui_impl_selaura";

    bd->hwnd = FindWindowA(nullptr, "Minecraft");

	selaura_handlers::event::subscribe([](selaura_event_types::PointerPressed& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseSourceEvent(ImGuiMouseSource_Mouse);
		io.AddMouseButtonEvent(event.button, true);
	});

	selaura_handlers::event::subscribe([](selaura_event_types::PointerReleased& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseSourceEvent(ImGuiMouseSource_Mouse);
		io.AddMouseButtonEvent(event.button, false);
	});

	selaura_handlers::event::subscribe([](selaura_event_types::PointerWheelChanged& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseSourceEvent(ImGuiMouseSource_Mouse);
		io.AddMouseWheelEvent(0, selaura_handlers::input::get_wheel_delta() > 0 ? 1.f : -1.f);
	});

	selaura_handlers::event::subscribe([](selaura_event_types::PointerMoved& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseSourceEvent(ImGuiMouseSource_Mouse);
		io.AddMousePosEvent(event.x, event.y);
	});

	selaura_handlers::event::subscribe([](selaura_event_types::KeyDown& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(ConvertInputKeyToImGuiKey(*event.key), true);
	});

	selaura_handlers::event::subscribe([](selaura_event_types::KeyUp& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(ConvertInputKeyToImGuiKey(*event.key), false);
	});

    selaura_handlers::event::subscribe([](selaura_event_types::CharReceived& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharacter(event.character);
    });

	return true;
}

void ImGui_ImplSelaura_Shutdown() {
	ImGui_ImplSelaura_Data* bd = ImGui_ImplSelaura_GetBackendData();
	IM_ASSERT(bd != nullptr && "No platform backend to shutdown, or already shutdown?");

	ImGuiIO& io = ImGui::GetIO();
	io.BackendPlatformName = nullptr;
	io.BackendPlatformUserData = nullptr;

	IM_DELETE(bd);
}

void ImGui_ImplSelaura_NewFrame() {
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplSelaura_Data* bd = ImGui_ImplSelaura_GetBackendData();
	IM_ASSERT(bd != nullptr && "Did you call ImGui_ImplSelaura_Init()?");

	RECT rect = { 0, 0, 0, 0 };
	GetClientRect(bd->hwnd, &rect);
	io.DisplaySize = ImVec2((float)(rect.right - rect.left), (float)(rect.bottom - rect.top));
}