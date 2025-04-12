#pragma once

#if defined(__unix__) || defined(__APPLE__)
#if !defined(__ANDROID__)
#define PLATFORM_LINUX
#endif
#endif

#include <thread>
#include <span>
#include <cstddef>
#include "io/logger.hpp"

#ifdef _WIN32
#include <Windows.h>
#include <Psapi.h>
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved);
#endif

#ifdef PLATFORM_LINUX
extern "C" [[gnu::visibility("default")]] void mod_preinit();
extern "C" [[gnu::visibility("default")]] void mod_init();
#endif