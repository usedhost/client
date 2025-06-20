#pragma once

#include <optional>
#include <string_view>
#include <stdexcept>
#include <cstdint>

#include "process.hpp"
#include "signatures.hpp"

#include <spdlog/spdlog.h>

namespace selaura {

	enum class platform {
		windows,
		android,
		linux_platform
	};

#if defined(SELAURA_WINDOWS)
	constexpr platform current_platform = platform::windows;
#elif defined(SELAURA_ANDROID)
	constexpr platform current_platform = platform::android;
#elif defined(SELAURA_LINUX)
	constexpr platform current_platform = platform::linux_platform;
#else
#error Unknown platform
#endif



	template <typename T>
	struct base_symbol {
		virtual void* resolve() const = 0;
		virtual ~base_symbol() = default;

		using type = T;
	};

	template <typename T>
	struct signature_symbol : base_symbol<T> {
		struct signature_info {
			std::string_view pattern;
			std::ptrdiff_t offset = 0;
		};

		std::string_view name;
		std::unordered_map<platform, signature_info> platform_signatures;
		mutable void* cached = nullptr;

		signature_symbol(std::string_view nm, std::unordered_map<platform, signature_info> list)
			: name(nm), platform_signatures(list) {
		}

		void* resolve() const override {
			auto it = platform_signatures.find(current_platform);
			if (it == platform_signatures.end()) {
				spdlog::error("No symbol for current platform: {}", name);
				return nullptr;
			}

			if (!cached) {
				auto base = find_pattern(it->second.pattern);
				if (!base.has_value()) {
					spdlog::error("Signature not valid! {}", name);
					return nullptr;
				}
				cached = reinterpret_cast<void*>(*base + it->second.offset);
			}
			return cached;
		}
	};

	struct offset_symbol {
		struct offset_info {
			uintptr_t offset;
		};

		std::string_view name;
		std::unordered_map<platform, offset_info> platform_offsets;

		offset_symbol(std::string_view nm, std::unordered_map<platform, offset_info> list)
			: name(nm), platform_offsets(list) {
		}

		uintptr_t resolve() const {
			auto it = platform_offsets.find(current_platform);
			if (it == platform_offsets.end()) {
				spdlog::error("No symbol for current platform: {}", name);
				return 0;
			}

			return it->second.offset;
		}
	};

	template <typename T>
	struct direct_symbol : base_symbol<T> {
		void* direct_address;

		direct_symbol(void* addr) : direct_address(addr) {}

		void* resolve() const override {
			return direct_address;
		}
	};
}
