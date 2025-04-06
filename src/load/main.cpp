#include "main.hpp"

void init() {
	logger::init();
}

#ifdef _WIN32
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		if (GetModuleHandleA("Minecraft.Windows.exe") == nullptr) return FALSE;
		DisableThreadLibraryCalls(hModule);
		try {
            std::thread(init).detach();
        } catch (...) {
            return FALSE;
        }
	}

	return TRUE;
}
#endif