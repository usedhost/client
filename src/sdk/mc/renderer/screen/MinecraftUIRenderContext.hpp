#pragma once
#include "ScreenContext.hpp"
#include "../../game/ClientInstance.hpp"
#include <libhat/access.hpp>

struct MinecraftUIRenderContext {
	ScreenContext* getScreenContext();
	ClientInstance* getClientInstance();
};