#pragma once
#include "../../sdk/mc/renderer/screen/MinecraftUIRenderContext.hpp"
#include "../../sdk/mc/gui/ScreenView.hpp"
#include "../../renderer/renderer.hpp"
#include "../../input/key.hpp"

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
		ScreenView* screen_view;
	};

	struct key_event : public cancellable {
		selaura::key key;
		selaura::key_action action;
	};
};