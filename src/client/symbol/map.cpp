#include "map.hpp"

using namespace selaura::detail;

namespace selaura::detail {
	void register_memory() {
		DEFINE_SIGNATURE("ScreenView::SetupandRender", platform::windows, "48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 98 FD");
	}
};