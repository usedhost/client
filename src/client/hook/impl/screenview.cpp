#include "screenview.hpp"

selaura::hook_t screenview_hooks::setupandrender_hook;

void screenview_hooks::setupandrender(void* a1, selaura::bedrock::MinecraftUIRenderContext* mcuirc) {
	/*
	auto tess = mcuirc->getScreenContext()->getTessellator();

    int x = 0;
    int y = 0;
    int width = 50;
    int height = 50;

    tess->begin(selaura::bedrock::mce::PrimitiveMode::QuadList);
    tess->color(0.0f, 255.0f, 255.0f, 255.0f);
    tess->vertex(x, y);
    tess->begin(selaura::bedrock::mce::PrimitiveMode::QuadList);
    tess->color(0.0f, 255.0f, 255.0f, 255.0f);
    tess->vertex(x + width, y);
    tess->begin(selaura::bedrock::mce::PrimitiveMode::QuadList);
    tess->color(0.0f, 255.0f, 255.0f, 255.0f);
    tess->vertex(x + width, y + height);
    tess->begin(selaura::bedrock::mce::PrimitiveMode::QuadList);
    tess->color(0.0f, 255.0f, 255.0f, 255.0f);
    tess->vertex(x, y + height);
     
    */

	//setupandrender_hook.get_original<decltype(&setupandrender)>()(a1, mcuirc);
}

void screenview_hooks::enable() {
    auto sig = GET_SIGNATURE("ScreenView::SetupandRender");
    setupandrender_hook = selaura::hook((void*)sig.value(), (void*)setupandrender);
	setupandrender_hook.enable();
}