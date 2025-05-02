#include "imgui_impl_mc_tess.hpp"

namespace selaura::core {
	selaura::bedrock::Tessellator* imgui_tess::tessellator;
	selaura::bedrock::mce::TextureGroup* imgui_tess::textureGroup = nullptr;
	selaura::bedrock::mce::ClientTexture* imgui_tess::clientTexture = nullptr;
	selaura::bedrock::mce::TexturePtr imgui_tess::texturePointer;
	bool imgui_tess::unloadedTextures = false;
	int imgui_tess::frameCount = 0;

	bool imgui_tess::init(selaura::bedrock::MinecraftUIRenderContext& ctx) {
		imgui_tess::tessellator = ctx.screenContext->tessellator;
		imgui_tess::load_font_texture(ctx);

		return true;
	}

	void imgui_tess::shutdown() {
		imgui_tess::tessellator = nullptr;
	}

	void imgui_tess::new_frame(selaura::bedrock::MinecraftUIRenderContext& ctx) {
		ImGuiIO& io = ImGui::GetIO();

		// hardcode display size to 1920x1080
		// in the future this will be gotten through GuiData
		io.DisplaySize.x = 1920;
		io.DisplaySize.y = 1080;
	}

	void imgui_tess::render_draw_data(ImDrawData* drawData, selaura::bedrock::MinecraftUIRenderContext& ctx) {
		imgui_tess::frameCount += 1;
	}

	void imgui_tess::unload() {
		imgui_tess::unloadedTextures = true;
	}

	void imgui_tess::load_font_texture(selaura::bedrock::MinecraftUIRenderContext& ctx) {
		ImGuiIO& io = ImGui::GetIO();

		// set font 
	}
};