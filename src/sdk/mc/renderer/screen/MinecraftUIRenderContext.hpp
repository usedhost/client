#pragma once
#include "ScreenContext.hpp"
#include "../../game/ClientInstance.hpp"
#include "../../deps/core/resource/ResourceHelper.hpp"
#include <libhat/access.hpp>


struct MinecraftUIRenderContext {
	uintptr_t** vtable;
	ScreenContext* getScreenContext();
	ClientInstance* getClientInstance();
	mce::TexturePtr getTexture(const ResourceLocation& resourceLocation, bool forceReload);
};
