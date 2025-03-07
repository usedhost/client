#include "selaura.hpp"

std::shared_ptr<selaura> selaura::get() {
	static std::shared_ptr<selaura> instance = std::make_shared<selaura>();
	return instance;
}

void selaura::init(HMODULE hModule) {
	this->hModule = hModule;
	this->initialized = true;
}

void selaura::eject() {
	HANDLE hThread = CreateThread(nullptr, 0, [](LPVOID param) -> DWORD {
		selaura* instance = static_cast<selaura*>(param);
		instance->shutdown();

		Sleep(500);
		FreeLibraryAndExitThread(instance->hModule, 0);
		return 0;
	}, this, 0, nullptr);

	if (hThread) CloseHandle(hThread);
}

void selaura::shutdown() {
	this->initialized = false;
}