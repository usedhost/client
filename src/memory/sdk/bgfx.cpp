#include "bgfx.hpp"

namespace SDK {
	IDXGISwapChain* bgfx::d3d11::RenderContextD3D11::getSwapChain() {
		return selaura_memory::member_at<IDXGISwapChain*>(this, 0x228);
	}
};