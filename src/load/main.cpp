#include "main.hpp"

#ifdef SELAURA_WINDOWS
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {

	if (dwReason == DLL_PROCESS_ATTACH) {
		HMODULE mc = GetModuleHandleA("Minecraft.Windows.exe");
		if (mc == nullptr) return FALSE;

		DisableThreadLibraryCalls(mc);
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)selaura::init, hModule, 0, nullptr));
	}

	return TRUE;
}
#endif

#ifdef SELAURA_LINUX
extern "C" [[gnu::visibility("default")]] void mod_preinit() {
    
}

extern "C" [[gnu::visibility("default")]] void mod_init() {
	selaura::init();
}
#endif