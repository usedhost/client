#include "hooks.hpp"

void selaura_hooks::initialize() {
	MH_Initialize();

	if (kiero::init(kiero::RenderType::D3D12) == kiero::Status::Success) {
		kiero::bind(140, reinterpret_cast<void**>(&selaura_hooks::trampolines::Present), selaura_hooks::IDXGISwapChain_Present);
		kiero::bind(145, reinterpret_cast<void**>(&selaura_hooks::trampolines::ResizeBuffers), selaura_hooks::IDXGISwapChain_ResizeBuffers);
		kiero::bind(54, reinterpret_cast<void**>(&selaura_hooks::trampolines::ExecuteCommandLists), selaura_hooks::ID3D12CommandQueue_ExecuteCommandLists);
	}
	else if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {
		kiero::bind(8, reinterpret_cast<void**>(&selaura_hooks::trampolines::Present), selaura_hooks::IDXGISwapChain_Present);
		kiero::bind(13, reinterpret_cast<void**>(&selaura_hooks::trampolines::ResizeBuffers), selaura_hooks::IDXGISwapChain_ResizeBuffers);
	}

	auto sig = selaura_memory::find_pattern("48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 98 FD");
	MH_CreateHook((LPVOID)sig, (LPVOID)selaura_hooks::ScreenView_SetupAndRender, (LPVOID*)&selaura_hooks::trampolines::SetupAndRender);
	MH_EnableHook((LPVOID)sig);
}

void selaura_hooks::shutdown() {
	kiero::unbind(8);
	kiero::unbind(13);
	kiero::unbind(140);
	kiero::unbind(145);
	kiero::unbind(54);
	kiero::shutdown();

	MH_Uninitialize();
}