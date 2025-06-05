#pragma once
#include "ScreenContext.hpp"
#include "ClientInstance.hpp"
#include <libhat/access.hpp>

struct MinecraftUIRenderContext {
	ScreenContext* getScreenContext();
	ClientInstance* getClientInstance();
};