#include "dllmain.hpp"

DWORD WINAPI init(LPVOID hModule) {
	selaura::get().init(static_cast<HMODULE>(hModule));
	return 0;
}

void WINAPI eject() {
	selaura::get().shutdown();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		if (GetModuleHandleA("Minecraft.Windows.exe") == nullptr) return FALSE;
		DisableThreadLibraryCalls(hModule);
		const auto thread = CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)init, hModule, NULL, nullptr);
		if (!thread) return FALSE;

		return CloseHandle(thread);
	}

	if (dwReason == DLL_PROCESS_DETACH && !lpReserved)
	{
	}

	return TRUE;
}