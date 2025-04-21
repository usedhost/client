#include "main.hpp"

void init() {
	
}

#ifdef _WIN32
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {

	if (dwReason == DLL_PROCESS_ATTACH) {
		HMODULE mc = selaura::detail::get_module_handle();
		if (mc == nullptr) return FALSE;

		DisableThreadLibraryCalls(mc);
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)init, hModule, 0, nullptr));
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