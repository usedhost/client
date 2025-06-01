#include "visual_hooks.hpp"

void* splashtextrenderer_loadsplashes_ofunc;


namespace selaura {
	visual_hooks::visual_hooks(hook_manager& mgr) : hook_group(mgr) {
        mgr.register_hook(signatures::splashtextrenderer_loadsplashes.resolve(), mgr.get_member_func_addr(&SplashTextRenderer::_loadSplashes), &splashtextrenderer_loadsplashes_ofunc);
	};
}