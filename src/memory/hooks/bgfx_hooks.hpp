#pragma once
#include <memory>

#include <imgui/imgui.h>
#include "../../client/handlers/event.hpp"
#include "../../client/io/logger.hpp"

namespace selaura_hooks {
	namespace trampolines {
		inline uintptr_t renderContextD3D11_submit = 0;
		inline uintptr_t renderContextD3D12_submit = 0;
	};

	// bgfx::d3d11::RenderContextD3D11::submit(bgfx::d3d11::RenderContextD3D11 *this, bgfx::Frame *_render, bgfx::ClearQuad *_clearQuad, bgfx::TextVideoMemBlitter *_textVideoMemBlitter);
	// bgfx::d3d12::RenderContextD3D12::submit(bgfx::d3d12::RenderContextD3D12 *this, bgfx::Frame *_render, bgfx::ClearQuad *_clearQuad, bgfx::TextVideoMemBlitter *_textVideoMemBlitter);
	void RenderContextD3D11_Submit(void* a1, void* a2, void* a3, void* a4);
	void RenderContextD3D12_Submit(void* a1, void* a2, void* a3, void* a4);
}