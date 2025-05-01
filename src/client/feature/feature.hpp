#pragma once
#include <memory>
#include <vector>
#include <string>
#include <variant>

#include <glm/glm.hpp>
#include <libhat/fixed_string.hpp>
#include "../../core/event/event.hpp"

namespace selaura {

	using feature_setting_type = std::variant<
		float, // slider
		bool, // toggle
		int, // enum index
		glm::vec4 // color
	>;

	struct feature_setting {
		std::string name;
		feature_setting_type value;
	};

	template <hat::fixed_string name_str = "String Not Found", hat::fixed_string description_str = "Description Not Found">
	struct feature_traits {
		static constexpr auto name = name_str;
		static constexpr auto description = description_str;
	};

	#define DEFINE_FEATURE_TRAITS(name, description) using info = feature_traits<name, description>;

	struct feature : public selaura::core::listener {
		using info = feature_traits<>;
		feature() = default;
		virtual ~feature() noexcept;

		virtual void on_disable();
		virtual void on_enable();

		void set_enabled(bool enabled = true);
		bool is_enabled() const;
		void toggle();

		void set_hotkey(int hotkey = 0);
		int get_hotkey() const;

		template<typename setting_t = feature_setting, typename... args_t>
		auto* add_settings(args_t... args) {
			return settings.emplace_back(std::make_unique<setting_t>(std::forward<args_t>(args)...)).get();
		}

		const std::vector<std::unique_ptr<feature_setting>>& get_settings() const {
			return settings;
		}

		virtual void set_feature_size(const glm::vec2& size);
		virtual void set_feature_position(const glm::vec2& pos);
		const glm::vec2& get_feature_size();
		const glm::vec2& get_feature_pos();

	private:
		bool enabled = false;
		int hotkey;
		glm::vec2 pos{};
		glm::vec2 size{};
		std::vector<std::unique_ptr<feature_setting>> settings;
	};
}