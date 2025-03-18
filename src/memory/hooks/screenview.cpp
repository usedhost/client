#include "screenview.hpp"

void selaura_hooks::ScreenView_SetupAndRender(void* a1, void* a2) {
	auto& trampoline = trampolines::SetupAndRender;

	/*
	while (true) {
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(50, 50), 0xFF0000FF);
	}
	*/

	reinterpret_cast<void(*)(void*, void*)>(trampoline)(a1, a2);
}