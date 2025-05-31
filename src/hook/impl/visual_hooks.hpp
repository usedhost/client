#pragma once
#include "../hook_manager.hpp"

namespace selaura {
	struct visual_hooks : public hook_group {
		explicit visual_hooks(hook_manager& mgr);
	};
}