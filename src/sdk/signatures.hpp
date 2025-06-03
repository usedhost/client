#pragma once
#include "symbol.hpp"
#include <vector>
#include <string>

#include "mc/MinecraftGame.hpp"
#include "mc/mce.hpp"

#ifdef SELAURA_WINDOW
#define THISCALL __thiscall
#else
#define THISCALL
#endif

namespace selaura::signatures {

    using splashtextrenderer_loadsplashes_t = std::vector<std::string>* (THISCALL*)(void*, void*);
    inline signature_symbol<splashtextrenderer_loadsplashes_t> splashtextrenderer_loadsplashes{
        "SplashTextRenderer::_loadSplashes",
        {
            { selaura::platform::windows, { "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B D9 49 8B F8 4C 89 44 24" } },
            { selaura::platform::android, { "? ? ? A9 ? ? ? A9 FD 03 00 91 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? D1 ? ? ? F9 F6 03 02 AA" } }
        }
    };

    using minecraftgame_update_t = void(THISCALL*)();
    inline signature_symbol<minecraftgame_update_t> minecraftgame_update{
        "MinecraftGame::update",
        {
            { selaura::platform::windows, { "48 8B C4 48 89 58 10 48 89 70 18 48 89 78 20 55 41 54 41 55 41 56 41 57 48 8D A8 18 F7" } },
            { selaura::platform::android, { "? ? ? FC ? ? ? A9 ? ? ? 91 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? D1 ? ? ? D5 F3 03 00 AA ? ? ? F9 ? ? ? F8 ? ? ? F9 ? ? ? 95" } }
        }
    };

	using screenview_setupandrender_t = void(THISCALL*)(void*);
    inline signature_symbol<screenview_setupandrender_t> screenview_setupandrender{
        "ScreenView::SetupAndRender",
        {
            { selaura::platform::windows, { "48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 98 FD" } },
            { selaura::platform::android, { "todo: find this" } }
        }
	};

    using tessellator_begin_t = void(THISCALL*)(mce::PrimitiveMode, const int, const bool);
    inline signature_symbol<tessellator_begin_t> tessellator_begin{
        "Tessellator::begin",
        {
            { selaura::platform::windows, { "40 53 55 48 83 EC 28 80 B9" } },
            { selaura::platform::android, { "todo: find this" } }
        }
    };

    using tessellator_vertexuv_t = void(THISCALL*)(float, float, float, float, float);
    inline signature_symbol<tessellator_vertexuv_t> tessellator_vertexuv{
        "Tessellator::vertex",
        {
            { selaura::platform::windows, { "48 83 EC ? 80 B9 ? ? ? ? ? 0F 57 E4" } },
            { selaura::platform::android, { "todo: find this" } }
        }
    };

    using tessellator_color_t = void(THISCALL*)(float, float, float, float);
    inline signature_symbol<tessellator_color_t> tessellator_color{
        "Tessellator::color",
        {
            { selaura::platform::windows, { "80 B9 ? ? ? ? ? 4C 8B C1 75" } },
            { selaura::platform::android, { "todo: find this" } }
        }
    };

    using meshhelpers_rendermeshimmediately_t = void(THISCALL*)(void*, void*, void*);
    inline signature_symbol<meshhelpers_rendermeshimmediately_t> meshhelpers_rendermeshimmediately{
        "MeshHelpers::renderMeshImmediately",
        {
            { selaura::platform::windows, { "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 98 FC FF FF 48 81 EC 68 04 00 00 49" } },
            { selaura::platform::android, { "todo: find this" } }
        }
    };
}