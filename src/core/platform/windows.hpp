#ifdef _WIN32
#pragma once

#include <Windows.h>
#include <Psapi.h>

#include <span>
#include <byte>
#include <string>
#include <stdexcept>

namespace selaura::detail {
	using game_memory = std::span<std::byte>;

	HMODULE get_module_handle(std::string_view name) {
		auto* module = GetModuleHandleA(name.data());
		if (!module) throw std::runtimeerror("GetModuleHandleA failed.");
		return module;
	}

	HMODULE get_module_handle() {
		return get_module_handle("Minecraft.Windows.exe");
	}

	const MODULEINFO& get_module_info() {
		static MODULEINFO mod_info = []() {
			MODULEINFO mi{};
			if (!GetModuleInformation(GetCurrentProcess(), get_module_handle(), &mi, sizeof(mi)))
				throw std::runtime_error("GetModuleInformation failed.");
			return mi;
			}();
		return mod_info;
	}

	std::byte* get_module_base() {
		return reinterpret_cast<std::byte*>(get_module_info().lpBaseOfDll);
	}

	std::size_t get_module_size() {
		return get_module_info().SizeOfImage;
	}
};

#endif