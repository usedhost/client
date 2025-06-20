#include "SplashTextRenderer.hpp"

#include "../../../../../instance.hpp"
#include "../../../../../event/event_manager.hpp"

#include <spdlog/spdlog.h>

void SplashTextRenderer::render(MinecraftUIRenderContext* ctx, ClientInstance* ci, UIControl* owner, int pass, void* renderAABB) {
    auto inst = selaura::instance::get();
    auto hk = inst->get<selaura::hook_manager>();

    auto original = hk.get_original<&SplashTextRenderer::render>();
    (this->*original)(ctx, ci, owner, pass, renderAABB);

    this->mCurrentSplash = 0;
    this->mSplashes = { "\u00a76Selaura Client \u00a76on top!\u00a7r" };
}