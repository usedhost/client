#include "imgui_impl_mc_tess.hpp"

namespace selaura::core {
	bool imgui_tess::init(selaura::bedrock::MinecraftUIRenderContext& ctx) {
		this->tessellator = &ctx.screenContext->tessellator;
		this->load_font_texture(ctx);

		return true;
	}

	void imgui_tess::shutdown() {
		this->tessellator = nullptr;
	}

	void imgui_tess::new_frame(selaura::bedrock::MinecraftUIRenderContext& ctx) {
		ImGuiIO& io = ImGui::GetIO();

		// hardcode display size to 1920x1080
		// in the future this will be gotten through GuiData
		io.DisplaySize.x = 1920;
		io.DisplaySize.y = 1080;
	}

	void imgui_tess::render_draw_data(ImDrawData* drawData, selaura::bedrock::MinecraftUIRenderContext& ctx) {
		this->frameCount += 1;
	}

	void imgui_tess::unload() {
		this->unloadedTextures = true;
	}

	void imgui_tess::load_font_texture(selaura::bedrock::MinecraftUIRenderContext& ctx) {
		ImGuiIO& io = ImGui::GetIO();

		// set font 
	}
};