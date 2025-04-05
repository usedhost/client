#pragma once
#include <memory>

#include "../include/imgui/imgui.h"
#include "../../client/handlers/event.hpp"
#include "../../client/io/logger.hpp"
#include "memory/sdk/bgfx.hpp"

namespace selaura_hooks {
	namespace trampolines {
		inline uintptr_t renderContextD3D11_submit = 0;
		inline uintptr_t renderContextD3D12_submit = 0;
		inline uintptr_t renderContextD3D11_SetFrameBuffer = 0;
	};
	// bgfx::d3d11::RenderContextD3D11::submit(bgfx::d3d11::RenderContextD3D11 *this, bgfx::Frame *_render, bgfx::ClearQuad *_clearQuad, bgfx::TextVideoMemBlitter *_textVideoMemBlitter);
	// bgfx::d3d12::RenderContextD3D12::submit(bgfx::d3d12::RenderContextD3D12 *this, bgfx::Frame *_render, bgfx::ClearQuad *_clearQuad, bgfx::TextVideoMemBlitter *_textVideoMemBlitter);
	void RenderContextD3D11_Submit(SDK::bgfx::d3d11::RenderContextD3D11* _this, SDK::bgfx::Frame* _render, SDK::bgfx::ClearQuad* _clearQuad, SDK::bgfx::TextVideoMemBlitter* _textVideoMemBlitter);
	void RenderContextD3D12_Submit(SDK::bgfx::d3d12::RenderContextD3D12* _this, SDK::bgfx::Frame* _render, SDK::bgfx::ClearQuad* _clearQuad, SDK::bgfx::TextVideoMemBlitter* _textVideoMemBlitter);
	void RenderContextD3D11_SetFrameBuffer(SDK::bgfx::d3d11::RenderContextD3D11* _this, void* a2, bool _msaa, bool _needPresent);
}