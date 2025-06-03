#pragma once
#include <imgui.h>
#include "../sdk/mc/MinecraftUIRenderContext.hpp"
#include "../sdk/mc/Tessellator.hpp"
#include "../sdk/mc/mce.hpp"

namespace selaura {
	struct renderer {
		bool initialize_imgui(MinecraftUIRenderContext& ctx);
		void new_frame(MinecraftUIRenderContext& ctx);
		void render_draw_data(ImDrawData* data, MinecraftUIRenderContext& ctx);
	private:
		Tessellator* tessellator;
	};
};