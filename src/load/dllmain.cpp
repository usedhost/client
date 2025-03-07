#include "dllmain.hpp"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		if (GetModuleHandleA("Minecraft.Windows.exe") == NULL) return FALSE;
		DisableThreadLibraryCalls(hModule);

		std::thread([=]() {
			FreeLibrary(hModule);

			selaura::get()->init(hModule);
		}).detach();
	}

	if (dwReason == DLL_PROCESS_DETACH && !lpReserved)
	{
		selaura::get()->shutdown();
	}

	return TRUE;
}