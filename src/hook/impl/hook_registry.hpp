#pragma once
#include "../../sdk/mc/game/MinecraftGame.hpp"
#include "../../sdk/mc/gui/controls/renderers/SplashTextRenderer.hpp"
#include "../../sdk/mc/gui/ScreenView.hpp"
#include "../hook_manager.hpp"
#include "../../sdk/mem/symbols.hpp"

namespace selaura {
	struct hook_registry : public hook_group {
		explicit hook_registry(hook_manager& mgr);
	};
}