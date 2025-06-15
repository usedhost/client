#include "hook_registry.hpp"

namespace selaura {
	hook_registry::hook_registry(hook_manager& mgr) : hook_group(mgr) {
		mgr.register_hook<&MinecraftGame::update>(signatures::minecraftgame_update);
		mgr.register_hook<&SplashTextRenderer::_loadSplashes>(signatures::splashtextrenderer_loadsplashes);
		mgr.register_hook<&ScreenView::SetupAndRender>(signatures::screenview_setupandrender);
		mgr.register_hook<&mce::TextureGroup::unloadAllTextures>(signatures::mce_texturegroup_unloadalltextures);
	};
}