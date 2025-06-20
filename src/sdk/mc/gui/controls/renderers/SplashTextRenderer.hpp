#pragma once
#include <vector>
#include <string>
#include "../../../../mem/signatures.hpp"
#include "../../../renderer/screen/MinecraftUIRenderContext.hpp"
#include "../../gui/UIControl.hpp"

struct SplashTextRenderer {
    std::byte pad[0x10];
    int mCurrentSplash;
    std::byte pad2[0x28 - 0x10];
    std::vector<std::string> mSplashes;

    void render(MinecraftUIRenderContext* ctx, ClientInstance* ci, UIControl* owner, int pass, void* renderAABB);
};
