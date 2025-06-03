#pragma once
#include "MinecraftUIRenderContext.hpp"
#include <spdlog/spdlog.h>
#include <imgui.h>

struct ScreenView {
    void __cdecl SetupAndRender(MinecraftUIRenderContext* ctx);
};