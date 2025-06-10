#pragma once
#include "../../sdk/mc/renderer/screen/MinecraftUIRenderContext.hpp"
#include "../../renderer/renderer.hpp"

namespace selaura {
	struct cancellable {
		bool* cancelled;

		void cancel() {
			bool c = true;
			*cancelled = c;
		}
	};
	struct minecraftgame_update_event {};
	struct setupandrender_event {
		MinecraftUIRenderContext* ctx;
		selaura::renderer& renderer;
	};

	enum class key_action {
		key_down,
		key_up,
		system_key_down,
		system_key_up,
		unknown
	};
	struct key_event : public cancellable {
		uint32_t key;
		key_action action;
	};
};