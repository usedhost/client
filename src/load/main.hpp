#pragma once

#include "../selaura.hpp"
#include <thread>

#ifdef SELAURA_WINDOWS
#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved);
#endif

#ifdef SELAURA_LINUX
#include <dlfcn.h>
#include <link.h>

extern "C" [[gnu::visibility("default")]] void mod_preinit();
extern "C" [[gnu::visibility("default")]] void mod_init();
#endif

#ifdef SELAURA_ANDROID
#include <pthread.h>

__attribute__((constructor))
void lib_main();
#endif