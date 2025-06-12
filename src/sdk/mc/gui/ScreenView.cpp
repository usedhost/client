#include "ScreenView.hpp"

#include "../../../instance.hpp"
#include "../../../hook/hook_manager.hpp"
#include "../../../renderer/renderer.hpp"
#include "../../signatures.hpp"
#include <glm/glm.hpp>

void __cdecl ScreenView::SetupAndRender(MinecraftUIRenderContext* ctx) {
    auto inst = selaura::instance::get();
    auto evm = inst->get<selaura::event_manager>();

    // imgui test here
	auto renderer = inst->get<selaura::renderer>();

    if (ImGui::GetCurrentContext() == nullptr) {
        IMGUI_CHECKVERSION();
        ImGui::SetCurrentContext(ImGui::CreateContext());
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO();

        renderer.initialize_imgui(*ctx);
    }

	renderer.new_frame(*ctx);
	ImGui::NewFrame();

    auto drawlist = ImGui::GetBackgroundDrawList();
	drawlist->AddText(ImVec2(0, 0), ImColor(255, 255, 255, 255), "Hello, ImGui!");

	selaura::setupandrender_event ev{ ctx, renderer, this };
	evm.dispatch<selaura::setupandrender_event>(ev);

	inst->get<selaura::screen_manager>().for_each([&](selaura::screen& screen) {
		if (screen.is_enabled()) screen.on_render(ev);
	});

	ImGui::EndFrame();
	ImGui::Render();

	renderer.render_draw_data(ImGui::GetDrawData(), *ctx);

    // imgui test end



    auto hk = inst->get<selaura::hook_manager>();

    auto original = hk.get_original<&ScreenView::SetupAndRender>();
    return (this->*original)(ctx);
}

VisualTree* ScreenView::getVisualTree() {
	return hat::member_at<VisualTree*>(this, selaura::signatures::screenview_visualtree.resolve());
}