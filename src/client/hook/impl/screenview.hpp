#pragma once

#include "../hook.hpp"
#include "../../io/io.hpp"
#include "../../symbol/map.hpp"
#include "../../../core/bedrock/client/renderer/minecraft_ui_render_context.hpp"
#include "../../../core/bedrock/core/math/vec2.hpp"

class screenview_hooks {
private:
	static selaura::hook_t setupandrender_hook;

	static void setupandrender(void* a1, selaura::bedrock::MinecraftUIRenderContext* mcuirc);
public:
	void enable();
};