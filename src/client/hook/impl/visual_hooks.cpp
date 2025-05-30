#include "visual_hooks.hpp"

//selaura::hook_t visual_hooks::setupandrender_hook;
selaura::hook_t visual_hooks::splashtext_hook;
/*
void visual_hooks::screenview_setupandrender(void* a1, bedrock::MinecraftUIRenderContext* mcuirc) {
    auto ci = mcuirc->clientInstance;
    auto guiData = ci->guiData;

    auto screenSize = guiData->mScreenSize;
    static bedrock::Vec2 safeZone = { 0.f, 0.f };
    //ci->_updateScreenSizeVariables(&screenSize, &safeZone, 2);

    static bool once = false;
    if (!once) {
        //guiData->displayClientMessage("Selaura on Top!");
        once = true;
    }

	setupandrender_hook.get_original<decltype(&screenview_setupandrender)>()(a1, mcuirc);
}
*/
std::vector<std::string>* visual_hooks::splashtextrenderer_loadsplashes(void* a1, void* a2, void* a3, void* a4) {
    auto original_func = splashtext_hook.get_original<decltype(&splashtextrenderer_loadsplashes)>();
    std::vector<std::string>* result = original_func(a1, a2, a3, a4);

    if (result) {
        const static std::string splash_text = "\u00a76Selaura Client \u00a76on top!\u00a7r";
        *result = { splash_text };
    }

    return result;
}

void visual_hooks::enable() {
    //auto sig = GET_SIGNATURE("ScreenView::SetupandRender");
    //auto hook_test = selaura::hook((void*)sig.value(), (void*)screenview_setupandrender);
    //hook_test.enable();

    auto sig2 = GET_SIGNATURE("SplashTextRenderer::_loadSplashes");
    splashtext_hook = selaura::hook((void*)sig2.value(), (void*)splashtextrenderer_loadsplashes);
    splashtext_hook.enable();
}

void visual_hooks::disable() {
    //setupandrender_hook.disable();
    splashtext_hook.disable();
}
