#pragma once
#include "../hook_manager.hpp"
#include "../../event/event_manager.hpp"

namespace selaura {
	struct internal_hooks : public hook_group {
		explicit internal_hooks(hook_manager& mgr);
	};
}