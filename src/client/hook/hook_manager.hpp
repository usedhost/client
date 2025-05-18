#pragma once
#include <string_view>
#include <type_traits>

#include "impl/screenview.hpp"

namespace selaura {
	template <typename T, typename... remainingT>
	struct hook_storage {
		T hook;
		hook_storage<remainingT...> remaining;

		void for_each(auto callback) {
			callback(hook);
			remaining.for_each(callback);
		}
	};

	template <typename T>
	struct hook_storage<T> {
		T hook;
		void for_each(auto callback) {
			callback(hook);
		}
	};

	struct hook_manager {
		using hooks_type = hook_storage<
			screenview_hooks
		>;

		void for_each(auto callback) {
			hooks.for_each(callback);
		}

		void for_each(auto callback) const {
			hooks.for_each(callback);
		}

		template <typename T>
		T* get() {
			T* result = nullptr;
			hooks.for_each([&]<typename hooks_type>(hooks_type & h) {
				if (result != nullptr) return;
				if (std::is_same_v<T, hooks_type>) {
					result = &h;
				}
			});
			return result;
		}
	private:
		hooks_type hooks;
	};
}
