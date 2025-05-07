#pragma once
#include <entt/entt.hpp>
#include <unordered_map>
#include <string>

#include "feature.hpp"

namespace selaura {
	template <typename T, typename... remainingT>
	struct feature_storage {
		T mod;
		feature_storage<remainingT...> remaining;

		void for_each(auto callback) {
			callback(mod);
			remaining.for_each(callback);
		}
	};

	template <typename T>
	struct feature_storage<T> {
		T mod;
		void for_each(auto callback) {
			callback(mod);
		}
	};

	struct feature_manager {
		using features_type = feature_storage<>;
		
		void for_each(auto callback) {
			features.for_each(callback);
		}

		void for_each(auto callback) const {
			features.for_each(callback);
		}

		template <typename T>
		T* get() {
			T* result = nullptr;
			features.for_each([&]<typename features_type>(features_type& feature) {
				if (result != nullptr) return;
				if (std::is_same_v<T, features_type>) {
					result = &feature;
				}
			});

			return result;
		}

		[[nodiscard]] auto* find(std::string_view name) {
			feature* result = nullptr;
			features.for_each([&]<typename features_type>(features_type & feature) {
				if (result != nullptr) return;
				if (features_type::info::name == name) {
					result = &feature;
				}
			});

			return result;
		}
	private:
		features_type features;
	};
};