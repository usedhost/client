#include "SplashTextRenderer.hpp"

#include "../../instance.hpp"
#include "../../hook/hook_manager.hpp"

std::vector<std::string> __cdecl SplashTextRenderer::_loadSplashes(void* a1, void* a2) {
    auto inst = selaura::instance::get();
    auto hk = inst->get<selaura::hook_manager>();

    auto original = hk.get_original<&SplashTextRenderer::_loadSplashes>();
    return (this->*original)(a1, a2);
}