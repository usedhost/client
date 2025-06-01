#pragma once
#include "symbol.hpp"
#include <vector>
#include <string>

#include "mc/MinecraftGame.hpp"

#ifdef SELAURA_WINDOW
#define THISCALL __thiscall
#else
#define THISCALL
#endif

namespace selaura::signatures {

    using splashtextrenderer_loadsplashes_t = std::vector<std::string>* (THISCALL*)(void*, void*, void*, void*);
    inline signature_symbol<splashtextrenderer_loadsplashes_t> splashtextrenderer_loadsplashes{
        "SplashTextRenderer::_loadSplashes",
        {
            { selaura::platform::windows, { "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B D9 49 8B F8 4C 89 44 24" } },
            { selaura::platform::android, { "? ? ? A9 ? ? ? A9 FD 03 00 91 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? D1 ? ? ? F9 F6 03 02 AA" } }
        }
    };

    using minecraftgame_update_t = void(*)(MinecraftGame*);
    inline signature_symbol<minecraftgame_update_t> minecraftgame_update{
        "MinecraftGame::update",
        {
            { selaura::platform::windows, { "48 8B C4 48 89 58 10 48 89 70 18 48 89 78 20 55 41 54 41 55 41 56 41 57 48 8D A8 18 F7" } },
            { selaura::platform::android, { "? ? ? FC ? ? ? A9 ? ? ? 91 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? D1 ? ? ? D5 F3 03 00 AA ? ? ? F9 ? ? ? F8 ? ? ? F9 ? ? ? 95" } }
        }
    };
}