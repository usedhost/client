#pragma once
#include <imgui.h>
#include "../sdk/mc/renderer/screen/MinecraftUIRenderContext.hpp"
#include "../sdk/mc/renderer/Tessellator.hpp"
#include "../sdk/mc/renderer/helpers/MeshHelpers.hpp"
#include <spdlog/spdlog.h>

#include <glm/glm.hpp>

namespace selaura {
	struct renderer {
		bool initialize_imgui(MinecraftUIRenderContext& ctx);
		void load_fonts(MinecraftUIRenderContext& ctx);
		void new_frame(MinecraftUIRenderContext& ctx);
		void render_draw_data(ImDrawData* data, MinecraftUIRenderContext& ctx);

		void draw_rect(glm::vec2 pos, glm::vec2 size, glm::vec4 color, float stroke_width, float radius = 0.f);
		void draw_rect(glm::vec2 pos, glm::vec2 size, glm::vec3 color, float stroke_width, float radius = 0.f);

		void draw_filled_rect(glm::vec2 pos, glm::vec2 size, glm::vec4 color, float radius = 0.f, ImDrawFlags flags = 0);
		void draw_filled_rect(glm::vec2 pos, glm::vec2 size, glm::vec3 color, float radius = 0.f, ImDrawFlags flags = 0);
	};
};