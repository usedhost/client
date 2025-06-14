#include "MinecraftUIRenderContext.hpp"
#include "../../../signatures.hpp"

ScreenContext* MinecraftUIRenderContext::getScreenContext() {
	return hat::member_at<ScreenContext*>(this, selaura::signatures::minecraftuirendercontext_screencontext.resolve());
}

ClientInstance* MinecraftUIRenderContext::getClientInstance() {
	return hat::member_at<ClientInstance*>(this, selaura::signatures::minecraftuirendercontext_clientinstance.resolve());
}

mce::TexturePtr MinecraftUIRenderContext::getTexture(const ResourceLocation& resourceLocation, bool forceReload) {
	return selaura::call_virtual<mce::TexturePtr>(this, 29, resourceLocation, forceReload);
}