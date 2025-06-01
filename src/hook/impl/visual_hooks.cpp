#include "visual_hooks.hpp"

void* splashtextrenderer_loadsplashes_ofunc;

std::vector<std::string>* splashtextrenderer_loadsplashes_hook(void* a1, void* a2, void* a3, void* a4) {
    auto func = static_cast<decltype(&splashtextrenderer_loadsplashes_hook)>(splashtextrenderer_loadsplashes_ofunc);
    std::vector<std::string>* result = func(a1, a2, a3, a4);

    if (result) {
        const static std::string splash_text = "\u00a76Selaura Client \u00a76on top!\u00a7r";
        *result = { splash_text };
    }

    return result;
}

namespace selaura {
	visual_hooks::visual_hooks(hook_manager& mgr) : hook_group(mgr) {
        mgr.register_hook(signatures::splashtextrenderer_loadsplashes.resolve(), splashtextrenderer_loadsplashes_hook, &splashtextrenderer_loadsplashes_ofunc);
	};
}