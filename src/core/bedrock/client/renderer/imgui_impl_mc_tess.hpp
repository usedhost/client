#pragma once
#include "minecraft_ui_render_context.hpp"
#include "tessellator.hpp"
#include <imgui.h>

namespace selaura::bedrock {
	class Tessellator;
	namespace mce {
		class TextureGroup;
		class ClientTexture;
		class TexturePtr;
	}
}

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
		static selaura::bedrock::Tessellator* tessellator;
		static selaura::bedrock::mce::TextureGroup* textureGroup;
		static selaura::bedrock::mce::ClientTexture* clientTexture;
		static selaura::bedrock::mce::TexturePtr texturePointer;
		static bool unloadedTextures;
		static int frameCount;
	};
};