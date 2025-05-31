#include "visual_hooks.hpp"

namespace selaura {
	visual_hooks::visual_hooks(hook_manager& mgr) : hook_group(mgr) {
        mgr.register_hook(selaura::signatures::splashtextrenderer_loadsplashes, [](void* ofunc, void* a1, void* a2, void* a3, void* a4) {
            using ofunc_t = selaura::signatures::splashtextrenderer_loadsplashes_t;
            std::vector<std::string>* result = std::bit_cast<ofunc_t>(ofunc)(a1, a2, a3, a4);

            if (result) {
                const static std::string splash_text = "\u00a76Selaura Client \u00a76on top!\u00a7r";
                *result = { splash_text };
            }

            return result;
        });
	};
}