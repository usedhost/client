#pragma once

#include "../hook.hpp"
#include "../../io/io.hpp"
#include "../../symbol/map.hpp"
#include "../../../core/bedrock/client/renderer/minecraft_ui_render_context.hpp"
#include "../../../core/bedrock/core/math/vec2.hpp"

// TODO: 

class visual_hooks {
private:
	static selaura::hook_t setupandrender_hook;
	static selaura::hook_t splashtext_hook;

	static void screenview_setupandrender(void* a1, selaura::bedrock::MinecraftUIRenderContext* mcuirc);
	static std::vector<std::string>* splashtextrenderer_loadsplashes(void* a1, void* a2, void* a3, void* a4);
public:
	void enable();
	void disable();
};