#pragma once
#include "../renderer/screen/MinecraftUIRenderContext.hpp"
#include <spdlog/spdlog.h>
#include <imgui.h>

struct ScreenView {
    void __cdecl SetupAndRender(MinecraftUIRenderContext* ctx);
};