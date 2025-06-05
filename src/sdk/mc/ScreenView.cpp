#include "ScreenView.hpp"

#include "../../instance.hpp"
#include "../../hook/hook_manager.hpp"
#include "../../renderer/renderer.hpp"
#include "../signatures.hpp"

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

        io.Fonts->Clear(); // you can leave this out if nothing was added
        unsigned char* pixels;
        int w, h;
        io.Fonts->GetTexDataAsAlpha8(&pixels, &w, &h);

        renderer.initialize_imgui(*ctx);
    }

	renderer.new_frame(*ctx);
	ImGui::NewFrame();

    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    draw_list->AddCircleFilled(ImVec2(100, 100), 50.f, IM_COL32(255, 0, 0, 255));
    //draw_list->AddRectFilled(ImVec2(100, 100), ImVec2(200, 200), IM_COL32(255, 0, 0, 255), 0.0f);

	ImGui::EndFrame();
	ImGui::Render();

	renderer.render_draw_data(ImGui::GetDrawData(), *ctx);

    // imgui test end

    //selaura::setupandrender_event ev{ ctx };
    //evm.dispatch<selaura::setupandrender_event>(ev);

    auto hk = inst->get<selaura::hook_manager>();

    auto original = hk.get_original<&ScreenView::SetupAndRender>();
    return (this->*original)(ctx);
}