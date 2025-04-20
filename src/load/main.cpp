#include "main.hpp"

void init() {
	static std::span<std::byte> game_memory = {
		selaura::detail::get_module_base(),
		selaura::detail::get_module_size()
	};
}

#ifdef _WIN32
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {

	if (dwReason == DLL_PROCESS_ATTACH) {
		HMODULE mc = selaura::detail::get_module_handle();
		if (mc == nullptr) return FALSE;

		DisableThreadLibraryCalls(mc);
		std::thread([=]() {
			init();
		}).detach();
	}

	return TRUE;
}
#endif

#if defined(__unix__) || defined(__APPLE__)
extern "C" [[gnu::visibility("default")]] void mod_preinit() {
    
}

extern "C" [[gnu::visibility("default")]] void mod_init() {
	init();
}
#endif