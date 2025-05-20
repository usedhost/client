#include "splash_text.hpp"

selaura::hook_t splashtext_hooks::splashtext_hook;

std::vector<std::string>* splashtext_hooks::splashtextrenderer_loadsplashes(selaura::bedrock::SplashTextRenderer* renderer, void* a2, void* a3, void* a4) {
    auto original_func = splashtext_hook.get_original<decltype(&splashtextrenderer_loadsplashes)>();
    std::vector<std::string>* result = original_func(renderer, a2, a3, a4);

    if (result) {
        const static std::string splash_text = "\u00a76Selaura Client \u00a76on top!\u00a7r";
        *result = { splash_text };
    }

    return result;
}

void splashtext_hooks::enable() {
    auto sig = GET_SIGNATURE("SplashTextRenderer::_loadSplashes");
    splashtext_hook = selaura::hook((void*)sig.value(), (void*)splashtextrenderer_loadsplashes);
    splashtext_hook.enable();
}   