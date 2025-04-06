#include "main.hpp"

DWORD WINAPI init(LPVOID hModule) {
	logger::init();
	return 1;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		if (GetModuleHandleA("Minecraft.Windows.exe") == nullptr) return FALSE;
		DisableThreadLibraryCalls(hModule);
		auto thread = CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)init, hModule, NULL, nullptr);
		if (!thread) return FALSE;

		return CloseHandle(thread);
	}

	return TRUE;
}