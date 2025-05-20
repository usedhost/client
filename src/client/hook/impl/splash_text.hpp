#pragma once

#include "../hook.hpp"
#include "../../io/io.hpp"
#include "../../symbol/map.hpp"
#include "../../../core/bedrock/client/renderer/splash_text_renderer.hpp"

#include <vector>
#include <string>

class splashtext_hooks {
private:
	static selaura::hook_t splashtext_hook;

	static std::vector<std::string>* splashtextrenderer_loadsplashes(selaura::bedrock::SplashTextRenderer* renderer, void* a2, void* a3, void* a4);
public:
	void enable();
};