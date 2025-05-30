#include "map.hpp"

using namespace selaura::detail;

namespace selaura::detail {
	void register_memory() {
		DEFINE_SIGNATURE("ScreenView::SetupandRender", platform::windows, "48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 98 FD");
		DEFINE_SIGNATURE("SplashTextRenderer::_loadSplashes", platform::windows, "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B D9 49 8B F8 4C 89 44 24");
		DEFINE_SIGNATURE("ClientInstance::_updateScreenSizeVariables", platform::windows, "48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 C8 FE FF FF 48 81 EC 00 02 00 00 0F 29 70 B8 0F 29 78 A8 44 0F 29 40 98 44 0F 29 48 88 44 0F 29 90 78 FF FF FF 44 0F 29 A0");
		DEFINE_SIGNATURE("GuiData::displayClientMessage", platform::windows, "40 55 53 56 57 41 56 48 8D AC 24 A0 FE FF FF 48 81 EC 60 02 00 00 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 50 01 00 00 41");

		DEFINE_SIGNATURE("ScreenView::SetupandRender", platform::arm64, "E8 0F 19 FC FD 7B 01 A9 FD 43 00 91 FC 6F 02 A9 FA 67 03 A9 F8 5F 04 A9 F6 57 05 A9 F4 4F 06 A9 FF 03 07 D1 48 D0 3B D5 F9");
		DEFINE_SIGNATURE("SplashTextRenderer::_loadSplashes", platform::arm64, "FD 7B BA A9 FC 6F 01 A9 FD 03 00 91 FA 67 02 A9 F8 5F 03 A9 F6 57 04 A9 F4 4F 05 A9 FF C3 06 D1 E1 13");
		DEFINE_SIGNATURE("ClientInstance::_updateScreenSizeVariables", platform::arm64, "48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 C8 FE FF FF 48 81 EC 00 02 00 00 0F 29 70 B8 0F 29 78 A8 44 0F 29 40 98 44 0F 29 48 88 44 0F 29 90 78 FF FF FF 44 0F 29 A0");
		DEFINE_SIGNATURE("GuiData::displayClientMessage", platform::arm64, "FF 83 07 D1 FD 7B 18 A9 FD 03 06 91 FC 6F 19 A9 FA 67 1A A9 F8 5F 1B A9 F6 57 1C A9 F4 4F 1D A9 E8 07");
	}
};
