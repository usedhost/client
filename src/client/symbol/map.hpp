#pragma once

#include <unordered_map>
#include <array>
#include <string>
#include <optional>
#include <cstdint>

#include "resolver.hpp"

namespace selaura::detail {
	void register_memory();

	enum class platform {
		windows = 0,
		arm64 = 1,
		android64 = 2,
		count
	};

	enum class mem_type {
		signature,
		offset
	};

	using memory_array = std::array<std::optional<uintptr_t>, static_cast<size_t>(platform::count)>;

	struct sig_entry {
		memory_array signatures;
		memory_array offsets;
	};

	class signature_map {
	public:
		static inline signature_map& inst() {
			static signature_map map;
			return map;
		}

		void define_signature(const std::string& name, platform plat, const std::string& sig) {
			entries[name].signatures[static_cast<size_t>(plat)] = selaura::resolver::signature(sig);
		}

		void define_offset(const std::string& name, platform plat, uintptr_t offset) {
			entries[name].offsets[static_cast<size_t>(plat)] = offset;
		}

		std::optional<uintptr_t> get_signature(const std::string& name, platform plat) const {
			auto it = entries.find(name);
			if (it != entries.end()) {
				return it->second.signatures[static_cast<size_t>(plat)];
			}
			return std::nullopt;
		}

		std::optional<uintptr_t> get_offset(const std::string& name, platform plat) const {
			auto it = entries.find(name);
			if (it != entries.end()) {
				return it->second.offsets[static_cast<size_t>(plat)];
			}
			return std::nullopt;
		}

	private:
		std::unordered_map<std::string, sig_entry> entries;
	};
};

#ifndef SELAURA_PLATFORM
#ifdef SELAURA_WINDOWS
#define SELAURA_PLATFORM selaura::detail::platform::windows
#elif SELAURA_ANDROID
#define SELAURA_PLATFORM selaura::detail::platform::arm64
#elif SELAURA_LINUX
#define SELAURA_PLATFORM selaura::detail::platform::android64
#endif
#endif

#define DEFINE_SIGNATURE(name, platform, sig) \
    selaura::detail::signature_map::inst().define_signature(name, platform, sig)

#define DEFINE_OFFSET(name, platform, offset) \
    selaura::detail::signature_map::inst().define_offset(name, platform, offset)

#define GET_SIGNATURE(name) \
    selaura::detail::signature_map::inst().get_signature(name, SELAURA_PLATFORM)

#define GET_OFFSET(name) \
    selaura::detail::signature_map::inst().get_offset(name, SELAURA_PLATFORM)