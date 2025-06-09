#pragma once
#include <vector>
#include <memory>
#include <string_view>
#include <type_traits>
#include <algorithm>

#include "feature.hpp"

namespace selaura {
	struct feature_manager {
		feature_manager() = default;

		void init() {
			//add_feature<
			//	selaura::armor_hud,
			//	selaura::direection_hud
			//>();
		}

		template <typename T, typename... Args>
		T* add_feature(Args&&... args) {
			static_assert(std::is_base_of_v<feature, T>, "T must derive from feature");
			auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
			T* raw_ptr = ptr.get();
			features.emplace_back(std::move(ptr));
			return raw_ptr;
		}

		void for_each(auto&& callback) {
			for (auto& scr : features)
				callback(*scr);
		}

		void for_each(auto&& callback) const {
			for (const auto& scr : features)
				callback(*scr);
		}

		template <typename T>
		T* get() {
			for (auto& scr : features) {
				if (auto* casted = dynamic_cast<T*>(scr.get()))
					return casted;
			}
			return nullptr;
		}

	private:
		std::vector<std::unique_ptr<feature>> features;
	};
}