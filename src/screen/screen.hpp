#pragma once
#include <memory>
#include <vector>
#include <string>
#include <variant>

#include <glm/glm.hpp>
#include <libhat/fixed_string.hpp>
#include "../event/event_manager.hpp"

namespace selaura {
	template <hat::fixed_string name_str = "String Not Found">
	struct screen_traits {
		static constexpr auto name = name_str;
	};

#define DEFINE_SCREEN_TRAITS(name) using info = screen_traits<name>;

	struct screen {
		using info = screen_traits<>;
		screen() = default;
		virtual ~screen() noexcept;

		virtual void on_disable();
		virtual void on_enable();
		virtual void on_render(selaura::setupandrender_event& ev);

		void set_enabled(bool enabled = true);
		bool is_enabled() const;
		void toggle();

		void set_hotkey(int hotkey = 0);
		int get_hotkey() const;

	private:
		bool enabled = false;
		int hotkey;
	};
}