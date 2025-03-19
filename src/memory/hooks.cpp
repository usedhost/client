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

	auto sig2 = selaura_memory::find_pattern("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 0F B7 41");
	MH_CreateHook((LPVOID)sig2, (LPVOID)selaura_hooks::RenderContextD3D11_SetFrameBuffer, (LPVOID*)&selaura_hooks::trampolines::renderContextD3D11_SetFrameBuffer);
	MH_EnableHook((LPVOID)sig2);

	auto sig3 = selaura_memory::find_pattern("48 8B C4 55 53 56 57 41 54 41 55 41 56 41 57 48 81 EC");
	MH_CreateHook((LPVOID)sig3, (LPVOID)selaura_hooks::RenderContextD3D11_Submit, (LPVOID*)&selaura_hooks::trampolines::renderContextD3D11_submit);
	MH_EnableHook((LPVOID)sig3);

	auto sig4 = selaura_memory::find_pattern("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 0F 29 B4 24 ? ? ? ? 0F 29 BC 24 ? ? ? ? 44 0F 29 84 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 89 4C 24");
	MH_CreateHook((LPVOID)sig4, (LPVOID)selaura_hooks::RenderContextD3D12_Submit, (LPVOID*)&selaura_hooks::trampolines::renderContextD3D12_submit);
	MH_EnableHook((LPVOID)sig4);
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