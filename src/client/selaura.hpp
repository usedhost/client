#pragma once
#include <Windows.h>
#include <memory>

class selaura {
public:
	static std::shared_ptr<selaura> get();

	void init(HMODULE hModule);
	void shutdown();
	void eject();
private:
	HMODULE hModule = nullptr;
	bool initialized = false;
};