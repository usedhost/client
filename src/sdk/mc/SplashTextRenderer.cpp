#include "SplashTextRenderer.hpp"

std::vector<std::string> SplashTextRenderer::_loadSplashes(void* a1, void* a2) {
    const static std::string splash_text = "\u00a76Selaura Client \u00a76on top!\u00a7r";
    return { splash_text };
}