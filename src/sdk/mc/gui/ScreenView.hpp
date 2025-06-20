#pragma once
#include "../renderer/screen/MinecraftUIRenderContext.hpp"
#include "../../mem/symbols.hpp"
#include <spdlog/spdlog.h>
#include <imgui.h>

#include "gui/VisualTree.hpp"

struct ScreenView {
    void __cdecl SetupAndRender(MinecraftUIRenderContext* ctx);
    VisualTree* getVisualTree();
};