#pragma once

#include <d3d11.h>
#include <d3d12.h>

#include "../scanner/scanner.hpp"

namespace SDK {
	struct bgfx {
		struct FrameBufferHandle {};
		struct Frame {};
		struct ClearQuad {};
		struct TextVideoMemBlitter {};
		struct d3d11 {
			struct RenderContextD3D11 {
				IDXGISwapChain* getSwapChain();
			};
		};
		struct d3d12 {
			struct RenderContextD3D12 {

			};
		};
	};
};