#include "MinecraftUIRenderContext.hpp"

ScreenContext* MinecraftUIRenderContext::getScreenContext() {
	return hat::member_at<ScreenContext*>(this, 0x10);
}