#pragma once

#include "symbol.hpp"

namespace selaura {
	namespace signatures {
		inline symbol_entry::signature_symbol splashtextrenderer_loadsplashes{
			"SplashTextRenderer::_loadSplashes",
			"48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B D9 49 8B F8 4C 89 44 24",
			platform::windows
		};
	};
};