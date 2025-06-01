#pragma once
#include "../hook_manager.hpp"

std::vector<std::string>* splashtextrenderer_loadsplashes_hook(void* a1, void* a2, void* a3, void* a4);

namespace selaura {
	struct visual_hooks : public hook_group {
		explicit visual_hooks(hook_manager& mgr);
	};
}