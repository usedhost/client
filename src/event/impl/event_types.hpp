#pragma once
#include "../../sdk/mc/MinecraftUIRenderContext.hpp"

namespace selaura {
	struct minecraftgame_update_event {};
	struct setupandrender_event {
		MinecraftUIRenderContext* ctx;
	};
};