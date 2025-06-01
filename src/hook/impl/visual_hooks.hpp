#pragma once
#include "../hook_manager.hpp"
#include "../../sdk/mc/SplashTextRenderer.hpp"

std::vector<std::string> __cdecl splashtextrenderer_loadsplashes_hook(void* a1, void* a2);

namespace selaura {
	struct visual_hooks : public hook_group {
		explicit visual_hooks(hook_manager& mgr);
	};
}