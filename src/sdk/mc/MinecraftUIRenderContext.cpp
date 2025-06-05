#include "MinecraftUIRenderContext.hpp"

ScreenContext* MinecraftUIRenderContext::getScreenContext() {
	return hat::member_at<ScreenContext*>(this, 0x10);
}

ClientInstance* MinecraftUIRenderContext::getClientInstance() {
	return hat::member_at<ClientInstance*>(this, 0x8);
}