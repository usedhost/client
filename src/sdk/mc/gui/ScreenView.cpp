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

    // get screen size from imgui
	auto& io = ImGui::GetIO();
	/*glm::vec2 mod_menu_size = { io.DisplaySize.x * 0.5 , io.DisplaySize.x * 0.3 };
    glm::vec2 mod_menu_pos = { (io.DisplaySize.x - mod_menu_size.x) / 2 , (io.DisplaySize.y - mod_menu_size.y) / 2 };
	glm::vec2 sidebar_size = { mod_menu_size.x * 0.3, mod_menu_size.y };

    renderer.draw_filled_rect({ mod_menu_pos.x - 2, mod_menu_pos.y - 2 }, { mod_menu_size.x + 4, mod_menu_size.y + 4 }, { 68, 68, 68, 255 }, 15.0f);
    renderer.draw_filled_rect(mod_menu_pos, mod_menu_size, {34, 34, 34, 255}, 15.0f);
	renderer.draw_filled_rect(mod_menu_pos, sidebar_size, {24, 24, 24, 255}, 15.0f, ImDrawFlags_RoundCornersLeft);
	renderer.draw_filled_rect({ mod_menu_pos.x + sidebar_size.x, mod_menu_pos.y }, { 2, mod_menu_size.y }, { 68, 68, 68, 255 }, 0.f);
*/

    auto drawlist = ImGui::GetBackgroundDrawList();
	drawlist->AddText(ImVec2(0, 0), ImColor(255, 255, 255, 255), "Hello, ImGui!");

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