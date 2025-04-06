#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif

#include <thread>
#include "io/logger.hpp"

#ifdef _WIN32
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved);
#endif