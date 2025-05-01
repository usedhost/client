#pragma once
#include "minecraft_ui_render_context.hpp"
#include "tessellator.hpp"
#include <imgui/imgui.hpp>

namespace selaura::core {
	class imgui_tess {
	public:
		static bool init(selaura::bedrock::MinecraftUIRenderContext& ctx);
		static void shutdown();
		static void new_frame(selaura::bedrock::MinecraftUIRenderContext& ctx);
		static void render_draw_data(ImDrawData* data, selaura::bedrock::MinecraftUIRenderContext& ctx);
		static void unload();
		static void load_font_texture(selaura::bedrock::MinecraftUIRenderContext& ctx);
	private:
		static Tessellator* tessellator = nullptr;
		static selaura::bedrock::mce::TextureGroup* textureGroup = nullptr;
		static selaura::bedrock::mce::ClientTexture* clientTexture = nullptr;
		static selaura::bedrock::mce::TexturePtr texturePointer;
		static bool unloadedTextures = false;
		static int frameCount = 0;
	};
};