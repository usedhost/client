#pragma once
#include <Windows.h>
#include <memory>

#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.Foundation.h>

#include <magic_enum/magic_enum.hpp>

#include "io/logger.hpp"
#include "utils/winrt_utils.hpp"
#include "handlers/input.hpp"

class selaura {
public:
	static std::shared_ptr<selaura> get();

	void init(HMODULE hModule);
	void shutdown();
	void eject();
private:
	HMODULE hModule = nullptr;
	std::atomic<bool> m_initialized{ false };
};