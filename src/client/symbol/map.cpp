#include "map.hpp"

using namespace selaura::detail;

namespace selaura::detail {
	void register_memory() {
		DEFINE_SIGNATURE("ScreenView::SetupandRender", platform::windows, "48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 98 FD");
		DEFINE_SIGNATURE("SplashTextRenderer::_loadSplashes", platform::windows, "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B D9 49 8B F8 4C 89 44 24");
		DEFINE_SIGNATURE("SplashTextRenderer::render", platform::windows, "48 89 5C 24 ? 55 56 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B FA 48 8B D9 33 F6 33 D2");
		DEFINE_SIGNATURE("CameraBobSystem::tick::_bobMovement", platform::windows, "FF 15 ? ? ? ? 80 7C 24 60 ? 0F 84 ? ? ? ? 48 89");
	}
};