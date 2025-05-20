#pragma once

#include "client/types.hpp"
#include "client/instance.hpp"

#include <string>
#include <memory>
#include <mutex>

#ifdef SELAURA_WINDOWS
#include <Windows.h>
#endif

namespace selaura {
#ifdef SELAURA_WINDOWS
	extern HMODULE hmodule;
#endif
	void init();
};
