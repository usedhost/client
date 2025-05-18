#pragma once

#include "../hook.hpp"
#include "../../symbol/resolver.hpp"

class screenview_hooks {
private:
	static selaura::hook_t setupandrender_hook;
	static void setupandrender(void* a1, void* a2);
public:
	void enable();
};