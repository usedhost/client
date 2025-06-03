#pragma once
#include "../../sdk/mc/MinecraftGame.hpp"
#include "../../sdk/mc/SplashTextRenderer.hpp"
#include "../../sdk/mc/ScreenView.hpp"
#include "../hook_manager.hpp"

namespace selaura {
	struct hook_registry : public hook_group {
		explicit hook_registry(hook_manager& mgr);
	};
}