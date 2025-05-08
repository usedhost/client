#pragma once

#include <string_view>
#include <optional>
#include <cstddef>
#include <cstdint>
#include <span>
#include <stdexcept>
#include <utility>
#include <type_traits>

#include <libhat/scanner.hpp>

#ifdef SELAURA_WINDOWS
#include <Windows.h>
#include <Psapi.h>
#include <string>
#include <string_view>
#endif

#if SELAURA_LINUX
#include <dlfcn.h>
#include <link.h>
#endif

namespace selaura::detail {
	struct process_module {
		std::byte* base;
		std::size_t size;

		void* native;

		std::byte* get_module_base();
		std::size_t get_module_size();
	};

	process_module get_module_handle(std::string_view name);
	process_module get_module_handle();
}
