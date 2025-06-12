#include "MinecraftUIRenderContext.hpp"
#include "../../../signatures.hpp"

ScreenContext* MinecraftUIRenderContext::getScreenContext() {
	return hat::member_at<ScreenContext*>(this, selaura::signatures::minecraftuirendercontext_screencontext.resolve());
}

ClientInstance* MinecraftUIRenderContext::getClientInstance() {
	return hat::member_at<ClientInstance*>(this, selaura::signatures::minecraftuirendercontext_clientinstance.resolve());
}