#pragma once
#include <memory>

#include "../include/imgui/imgui.h"
#include "../../client/handlers/event.hpp"

namespace selaura_hooks {
	namespace trampolines {
		inline uintptr_t SetupAndRender = 0;
	};
	void ScreenView_SetupAndRender(void* a1, void* a2);
}