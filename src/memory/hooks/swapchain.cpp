#include "swapchain.hpp"

bool gameReloaded = false;
bool deviceInitialized = false;
bool renderTargetInitialized = false;
bool imguiInitialized = false;

winrt::com_ptr<ID3D11Device> d3d11Device;
winrt::com_ptr<ID3D12Device> d3d12Device;
winrt::com_ptr<ID3D11DeviceContext> d3d11DeviceContext;
winrt::com_ptr<ID3D11On12Device> d3d11On12Device;
winrt::com_ptr<ID3D12CommandQueue> d3d12CommandQueue;

std::vector<winrt::com_ptr<ID3D11Texture2D>> dx11BackBufferTextures = std::vector<winrt::com_ptr<ID3D11Texture2D>>();
std::vector<winrt::com_ptr<ID3D11RenderTargetView>> dx11BackBufferRenderTargetViews = std::vector<winrt::com_ptr<ID3D11RenderTargetView>>();
int backBufferRenderTargetsIndex = 0;

bool isDX12 = true;
IUnknown* swapcoreWindow = nullptr;

HRESULT selaura_hooks::IDXGIFactory2_CreateSwapChainForCoreWindow(IDXGIFactory2* pFactory, IUnknown* pDevice, IUnknown* pWindow, const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain) {
	swapcoreWindow = pWindow;
	return reinterpret_cast<decltype(&selaura_hooks::IDXGIFactory2_CreateSwapChainForCoreWindow)>(selaura_hooks::trampolines::CreateSwapChainForCoreWindow)(pFactory, pDevice, pWindow, pDesc, pRestrictToOutput, ppSwapChain);
};

HRESULT selaura_hooks::IDXGISwapChain_Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	if (!deviceInitialized) {
		if (pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(d3d11Device.put())) == S_OK) {
			isDX12 = false;
		}

		if (pSwapChain->GetDevice(__uuidof(ID3D12Device), reinterpret_cast<void**>(d3d12Device.put())) == S_OK) {
			isDX12 = true;

			ID3D12Device* bad_device;
			if (pSwapChain->GetDevice(IID_PPV_ARGS(&bad_device)) == S_OK)
			{
				dynamic_cast<ID3D12Device5*>(bad_device)->RemoveDevice();

				return reinterpret_cast<decltype(&selaura_hooks::IDXGISwapChain_Present)>(selaura_hooks::trampolines::Present)(pSwapChain, SyncInterval, Flags);
			}


			/*D3D11On12CreateDevice(
				d3d11Device.get(),
				D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_SINGLETHREADED,
				nullptr,
				0,
				reinterpret_cast<IUnknown**>(d3d12CommandQueue.put()),
				1,
				0,
				d3d11Device.put(),
				d3d11DeviceContext.put(),
				nullptr
			);*/
		}

		deviceInitialized = true;
	}

	if (!renderTargetInitialized) {
		d3d11Device->GetImmediateContext(d3d11DeviceContext.put());
		int backBufferCount = (isDX12) ? 3 : 1;

		dx11BackBufferRenderTargetViews.resize(backBufferCount);
		dx11BackBufferTextures.resize(backBufferCount);

		if (!isDX12) {
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(dx11BackBufferTextures.at(0).put()));
			d3d11Device->CreateRenderTargetView(dx11BackBufferTextures.at(0).get(), nullptr, dx11BackBufferRenderTargetViews.at(0).put());
		}
		else {
			D3D11_RESOURCE_FLAGS backBuffer11Flags = {};
			backBuffer11Flags.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			for (int i = 0; i < 3; i++) {

				d3d11Device->QueryInterface(IID_PPV_ARGS(&d3d11On12Device));
				winrt::com_ptr<ID3D12Resource> buffer = nullptr;
				pSwapChain->GetBuffer(i, IID_PPV_ARGS(buffer.put()));

				d3d11On12Device->CreateWrappedResource(
					buffer.get(),
					&backBuffer11Flags,
					D3D12_RESOURCE_STATE_PRESENT,
					D3D12_RESOURCE_STATE_PRESENT,
					IID_PPV_ARGS(dx11BackBufferTextures.at(i).put())
				);

				D3D11_TEXTURE2D_DESC texDesc;
				dx11BackBufferTextures.at(i)->GetDesc(&texDesc);
				D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
				rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
				rtvDesc.Format = texDesc.Format;
				rtvDesc.Texture2D.MipSlice = 0;

				d3d11Device->CreateRenderTargetView(
					dx11BackBufferTextures.at(i).get(),
					nullptr,
					dx11BackBufferRenderTargetViews.at(i).put()
				);
			}
		}
		renderTargetInitialized = true;
	}
	

	if (!imguiInitialized) {
		ImGui::CreateContext();
		ImGui_ImplSelaura_Init();
		ImGui_ImplDX11_Init(d3d11Device.get(), d3d11DeviceContext.get());		

		imguiInitialized = true;
	}

	ImGui_ImplSelaura_NewFrame();
	ImGui_ImplDX11_NewFrame();
	ImGui::NewFrame();


	backBufferRenderTargetsIndex = reinterpret_cast<IDXGISwapChain3*>(pSwapChain)->GetCurrentBackBufferIndex();

	ImGui::ShowDemoWindow();

	selaura_handlers::event::dispatch<selaura_event_types::Render>();

	ImGui::EndFrame();
	ImGui::Render();

	if (isDX12) {
		ID3D11Resource* resource = dx11BackBufferTextures.at(backBufferRenderTargetsIndex).get();
		d3d11On12Device->AcquireWrappedResources(&resource, 1);
	}

	auto rtv = dx11BackBufferRenderTargetViews.at(backBufferRenderTargetsIndex).get();
	d3d11DeviceContext->OMSetRenderTargets(1, &rtv, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	if (isDX12) {
		ID3D11Resource* resource = dx11BackBufferTextures.at(backBufferRenderTargetsIndex).get();
		d3d11On12Device->ReleaseWrappedResources(&resource, 1);

		d3d11DeviceContext->Flush();
	}

	return reinterpret_cast<decltype(&selaura_hooks::IDXGISwapChain_Present)>(selaura_hooks::trampolines::Present)(pSwapChain, SyncInterval, Flags);
}

HRESULT selaura_hooks::IDXGISwapChain_ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
	if (renderTargetInitialized) {
		dx11BackBufferRenderTargetViews.clear();
		dx11BackBufferTextures.clear();
		d3d11DeviceContext->Flush();
		renderTargetInitialized = false;
	}

	selaura_handlers::event::dispatch<selaura_event_types::Resize>();
	return reinterpret_cast<decltype(&selaura_hooks::IDXGISwapChain_ResizeBuffers)>(selaura_hooks::trampolines::ResizeBuffers)(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HRESULT selaura_hooks::ID3D12CommandQueue_ExecuteCommandLists(ID3D12CommandQueue* pCommandQueue, UINT NumCommandLists, ID3D12CommandList* const* ppCommandLists) {
	return reinterpret_cast<decltype(&selaura_hooks::ID3D12CommandQueue_ExecuteCommandLists)>(selaura_hooks::trampolines::ExecuteCommandLists)(pCommandQueue, NumCommandLists, ppCommandLists);
}