#include "imgui_impl_mc_tess.hpp"

namespace selaura::core {
	bool imgui_tess::init(selaura::bedrock::MinecraftUIRenderContext& ctx) {
		// step 1: get tessellator
		// step 2: load font textures

		return true;
	}

	void imgui_tess::shutdown() {
		this->tessellator = nullptr;
	}
};