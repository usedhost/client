#pragma once
#include "mc/game/MinecraftGame.hpp"
#include "mc/gui/controls/renderers/SplashTextRenderer.hpp"

namespace selaura {
    struct globals {
        MinecraftGame* mc_game = nullptr;
    };
};