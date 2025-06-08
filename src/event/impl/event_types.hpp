#pragma once
#include "../../sdk/mc/renderer/screen/MinecraftUIRenderContext.hpp"
#include "../../renderer/renderer.hpp"

namespace selaura {
	struct minecraftgame_update_event {};
	struct setupandrender_event {
		MinecraftUIRenderContext* ctx;
		selaura::renderer& renderer;
	};
};