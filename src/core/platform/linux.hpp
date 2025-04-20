#if defined(__unix__) || defined(__APPLE__)
#pragma once

#include <link.h>
#include <dlfcn.h>

#include <span>
#include <byte>
#include <string>
#include <stdexcept>

namespace selaura::detail {
	using game_memory = std::span<std::byte>;

	void* get_module_handle(std::string_view name) {
		void* module = dlopen(name.data(), RTLD_NOLOAD);
		if (!module) throw std::runtime_error("dlopen failed for " + std::string(name));
		return module;
	}

	void* get_module_handle() {
		return get_module_handle("libminecraftpe.so");
	}

	void get_module_info(std::byte*& base, std::size_t& size) {
		static bool info_initialized = false;
		if (!info_initialized) {
			void* handle = dlopen("libminecraftpe.so", RTLD_NOLOAD);
			if (!handle) throw std::runtime_error("dlopen failed for libminecraftpe.so");

			dl_iterate_phdr([](dl_phdr_info* info, size_t, void* data) -> int {
				void* handle = dlopen(info->dlpi_name, RTLD_NOLOAD);
				dlclose(handle);
				if (handle == data) {
					for (int i = 0; i < info->dlpi_phnum; ++i) {
						const auto& phdr = info->dlpi_phdr[i];
						if (phdr.p_type == PT_LOAD && (phdr.p_flags & PF_X)) {
							auto& result = *reinterpret_cast<std::pair<std::byte**, std::size_t>*>(data);
							result.first = reinterpret_cast<std::byte*>(info->dlpi_addr + phdr.p_vaddr);
							result.second = phdr.p_memsz;
							return 1;
						}
					}
				}
				return 0;
				}, &std::make_pair(base, size));

			info_initialized = true;
		}
	}

	std::byte* get_module_base() {
		static std::byte* base = nullptr;
		std::size_t size = 0;
		get_module_info(base, size);
		return base;
	}

	std::size_t get_module_size() {
		static std::byte* base = nullptr;
		std::size_t size = 0;
		get_module_info(base, size);
		return size;
	}
};
#endif
