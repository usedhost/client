#pragma once

#include <Windows.h>
#include <memory>
#include <d3d11.h>
#include <d3d12.h>
#include <d3d11on12.h>
#include <dxgi1_4.h>

#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <CoreWindow.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_dx11.h>
#include <imgui/backends/imgui_impl_dx12.h>
#include <imgui/backends/imgui_impl_selaura.hpp>

#include "../../client/handlers/event.hpp"
#include "../../client/renderer/renderer.hpp"

namespace selaura_hooks {
	namespace trampolines {
		inline uintptr_t CreateSwapChainForCoreWindow = 0;
		inline uintptr_t Present = 0;
		inline uintptr_t ResizeBuffers = 0;
		inline uintptr_t ExecuteCommandLists = 0;
	};
	HRESULT IDXGIFactory2_CreateSwapChainForCoreWindow(IDXGIFactory2* pFactory, IUnknown* pDevice, IUnknown* pWindow, const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain);
	HRESULT IDXGISwapChain_Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	HRESULT IDXGISwapChain_ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	HRESULT ID3D12CommandQueue_ExecuteCommandLists(ID3D12CommandQueue* pCommandQueue, UINT NumCommandLists, ID3D12CommandList* const* ppCommandLists);
}