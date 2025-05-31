#pragma once
#include "symbol.hpp"
#include <vector>
#include <string>

namespace selaura::signatures {

    using splashtextrenderer_loadsplashes_t = std::vector<std::string>* (__thiscall*)(void*, void*, void*, void*);
    inline signature_symbol<splashtextrenderer_loadsplashes_t> splashtextrenderer_loadsplashes{
        "SplashTextRenderer::_loadSplashes",
        {
            { selaura::platform::windows, { "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B D9 49 8B F8 4C 89 44 24" } },
            { selaura::platform::android, { "FD 7B BA A9 FC 6F 01 A9 FD 03 00 91 FA 67 02 A9 F8 5F 03 A9 F6 57 04 A9 F4 4F 05 A9 FF C3 06 D1 E1 13" } }
        }
    };

}