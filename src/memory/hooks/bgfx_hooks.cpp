#include "bgfx_hooks.hpp"

void selaura_hooks::RenderContextD3D11_Submit(SDK::bgfx::d3d11::RenderContextD3D11* _this, SDK::bgfx::Frame* _render, SDK::bgfx::ClearQuad* _clearQuad, SDK::bgfx::TextVideoMemBlitter* _textVideoMemBlitter) {
	auto& trampoline = trampolines::renderContextD3D11_submit;

	logger::debug("RenderContextD3D11_Submit");	
	reinterpret_cast<void(*)(void*, void*, void*, void*)>(trampoline)(_this, _render, _clearQuad, _textVideoMemBlitter);
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(50, 50), 0xFF0000FF);
}

void selaura_hooks::RenderContextD3D12_Submit(SDK::bgfx::d3d12::RenderContextD3D12* _this, SDK::bgfx::Frame* _render, SDK::bgfx::ClearQuad* _clearQuad, SDK::bgfx::TextVideoMemBlitter* _textVideoMemBlitter) {
	auto& trampoline = trampolines::renderContextD3D12_submit;
	/*
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(50, 50), 0xFF0000FF);
	*/
	logger::debug("RenderContextD3D12_Submit");
	reinterpret_cast<void(*)(void*, void*, void*, void*)>(trampoline)(_this, _render, _clearQuad, _textVideoMemBlitter);
}

void selaura_hooks::RenderContextD3D11_SetFrameBuffer(SDK::bgfx::d3d11::RenderContextD3D11* _this, void* a2, bool _msaa, bool _needPresent) {
	auto& trampoline = trampolines::renderContextD3D11_SetFrameBuffer;
	logger::debug("RenderContextD3D11_SetFrameBuffer");
	reinterpret_cast<void(*)(void*, void*, bool, bool)>(trampoline)(_this, a2, _msaa, _needPresent);
}