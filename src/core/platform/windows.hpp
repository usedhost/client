#ifdef _WIN32
#pragma once

#include <Windows.h>
#include <Psapi.h>

#include <span>
#include <string>
#include <stdexcept>

namespace selaura::detail {
	HMODULE get_module_handle(std::wstring_view name) {
		std::wstring module_name(name);
		auto* module = GetModuleHandleW(module_name.c_str());
		if (!module) throw std::runtime_error("GetModuleHandleW failed.");
		return module;
	}

	HMODULE get_module_handle() {
		return get_module_handle(L"Minecraft.Windows.exe");
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

	static std::span<std::byte> get_game_memory() {
		static std::span<std::byte> memory = {
			selaura::detail::get_module_base(),
			selaura::detail::get_module_size()
		};
	};
};

#endif
