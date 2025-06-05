#include "renderer.hpp"

namespace selaura {
	bool renderer::initialize_imgui(MinecraftUIRenderContext& ctx) {
		ImGui::GetStyle().AntiAliasedLines = true;
		ImGui::GetStyle().AntiAliasedFill = true;

		return true;
	}

	void renderer::new_frame(MinecraftUIRenderContext& ctx) {
		auto& io = ImGui::GetIO();

		io.DisplaySize.x = 500.0f;
		io.DisplaySize.y = 888.8f;
	}

	void renderer::render_draw_data(ImDrawData* data, MinecraftUIRenderContext& ctx) {
		float scale = 1.0f; // todo: get actual scale from guidata
		static ScreenContext* screen_context = ctx.getScreenContext();
		static Tessellator* tess = screen_context->getTessellator();

		for (int n = 0; n < data->CmdListsCount; n++) {
			ImDrawList* cmd_list = data->CmdLists[n];
			
			for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
				const ImDrawCmd& cmd = cmd_list->CmdBuffer[cmd_i];
				const ImDrawVert* vtx_buffer = cmd_list->VtxBuffer.Data;
				const ImDrawIdx* idx_buffer = cmd_list->IdxBuffer.Data;

				tess->begin(mce::PrimitiveMode::TriangleList, 0);

				for (unsigned int i = 0; i < cmd.ElemCount; i += 3) {
					const ImDrawVert& v0 = vtx_buffer[idx_buffer[i + 2]];
					const ImDrawVert& v1 = vtx_buffer[idx_buffer[i + 1]];
					const ImDrawVert& v2 = vtx_buffer[idx_buffer[i + 0]];

					tess->color(v0.col);
					tess->vertexUV(v0.pos.x / scale, v0.pos.y / scale, 0.0f, v0.uv.x, v0.uv.y);

					tess->color(v1.col);
					tess->vertexUV(v1.pos.x / scale, v1.pos.y / scale, 0.0f, v1.uv.x, v1.uv.y);

					tess->color(v2.col);
					tess->vertexUV(v2.pos.x / scale, v2.pos.y / scale, 0.0f, v2.uv.x, v2.uv.y);
				}

				
				mce::MaterialPtr* material = mce::MaterialPtr::createMaterial(HashedString("ui_fill_color"));
				MeshHelpers::renderMeshImmediately(screen_context, tess, material);
			}
		}
	}
}