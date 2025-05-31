#pragma once

#include <libhat/Signature.hpp>
#include <optional>
#include <string_view>
#include <stdexcept>
#include <cstdint>

#include "process.hpp"

#include <spdlog/spdlog.h>

namespace selaura {

	enum class platform {
		windows,
		android,
		linux
	};

#if defined(SELAURA_WINDOWS)
	constexpr platform current_platform = platform::windows;
#elif defined(SELAURA_ANDROID)
	constexpr platform current_platform = platform::android;
#elif defined(SELAURA_LINUX)
	constexpr platform current_platform = platform::linux;
#else
#error Unknown platform
#endif

	inline std::optional<uintptr_t> find_pattern(std::string_view pattern) {
		const auto parsed = hat::parse_signature(pattern);
		if (!parsed.has_value()) {
			spdlog::error("Invalid signature! {:s}", pattern);
			return std::nullopt;
		}

		static auto process = selaura::get_process_handle();

		const auto begin = process.get_process_base();
		const auto end = begin + process.get_process_size();
		const auto result = hat::find_pattern(begin, end, parsed.value());

		if (!result.has_result()) {
			return std::nullopt;
		}
		return reinterpret_cast<uintptr_t>(result.get());
	}

	template <typename T>
	struct base_symbol {
		virtual void* resolve() const = 0;
		virtual ~base_symbol() = default;

		using type = T;
	};

	template <typename T>
	struct signature_symbol : base_symbol<T> {
		std::string_view name;
		std::string_view pattern;
		std::ptrdiff_t offset;
		platform target;
		mutable void* cached = nullptr;

		signature_symbol(std::string_view nm, std::string_view pat, platform plat, std::ptrdiff_t off = 0)
			: name(nm), pattern(pat), offset(off), target(plat) {
		}

		void* resolve() const override {
			if (target != current_platform)
				spdlog::error("Symbol not for this platform");

			if (!cached) {
				auto base = find_pattern(pattern);
				if (!base.has_value()) {
					spdlog::error("Signature not valid! {:s}", name);
					return nullptr;
				}
				cached = reinterpret_cast<void*>(*base + offset);
			}
			return cached;
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
