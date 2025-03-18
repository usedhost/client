#include "bgfx_hooks.hpp"

void selaura_hooks::RenderContextD3D11_Submit(void* a1, void* a2, void* a3, void* a4) {
	auto& trampoline = trampolines::renderContextD3D11_submit;
	

	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(50, 50), 0xFF0000FF);
	logger::debug("RenderContextD3D11_Submit");
	reinterpret_cast<void(*)(void*, void*, void*, void*)>(trampoline)(a1, a2, a3, a4);
}

void selaura_hooks::RenderContextD3D12_Submit(void* a1, void* a2, void* a3, void* a4) {
	auto& trampoline = trampolines::renderContextD3D12_submit;
	/*
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(50, 50), 0xFF0000FF);
	*/
	reinterpret_cast<void(*)(void*, void*, void*, void*)>(trampoline)(a1, a2, a3, a4);
}