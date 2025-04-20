#pragma once
#include "../core/platform/windows.hpp"
#include "../core/platform/linux.hpp"

#include "../instance.hpp"

#ifdef _WIN32
#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved);
#endif

#if defined(__unix__) || defined(__APPLE__)
#include <dlfcn.h>
#include <link.h>

extern "C" [[gnu::visibility("default")]] void mod_preinit();
extern "C" [[gnu::visibility("default")]] void mod_init();
#endif