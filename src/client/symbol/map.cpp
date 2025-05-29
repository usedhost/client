#include "map.hpp"

using namespace selaura::detail;

namespace selaura::detail {
	void register_memory() {
		DEFINE_SIGNATURE("ScreenView::SetupandRender", platform::windows, "48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 98 FD");
		DEFINE_SIGNATURE("SplashTextRenderer::_loadSplashes", platform::windows, "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B D9 49 8B F8 4C 89 44 24");
		DEFINE_SIGNATURE("ClientInstance::_updateScreenSizeVariables", platform::windows, "48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 C8 FE FF FF 48 81 EC 00 02 00 00 0F 29 70 B8 0F 29 78 A8 44 0F 29 40 98 44 0F 29 48 88 44 0F 29 90 78 FF FF FF 44 0F 29 A0");
		DEFINE_SIGNATURE("GuiData::displayClientMessage", platform::windows, "40 55 53 56 57 41 56 48 8D AC 24 A0 FE FF FF 48 81 EC 60 02 00 00 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 50 01 00 00 41");
	}
};
