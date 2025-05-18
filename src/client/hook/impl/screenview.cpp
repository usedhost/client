#include "screenview.hpp"
#include "../../symbol/resolver.hpp"

selaura::hook_t screenview_hooks::setupandrender_hook;

void screenview_hooks::setupandrender(void* a1, void* a2) {
	setupandrender_hook.get_original<decltype(&setupandrender)>()(a1, a2);
}

void screenview_hooks::enable() {
	auto sig = selaura::resolver::signature("48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 98 FD");
	setupandrender_hook = selaura::hook((void*)sig.value(), (void*)setupandrender);
	setupandrender_hook.enable();
}