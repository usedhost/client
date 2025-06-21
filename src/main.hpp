#pragma once

#include <thread>
#include <memory>
#include "instance.hpp"
#include "platform.hpp"

#ifdef SELAURA_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Psapi.h>

static HMODULE mc_handle;
DWORD WINAPI init(LPVOID lpvoid);
BOOL APIENTRY DllMain(HMODULE hmodule, DWORD dw_reason, LPVOID lp_reserved);
#endif

#ifdef SELAURA_LINUX
extern "C" [[gnu::visibility("default")]] void mod_preinit();
extern "C" [[gnu::visibility("default")]] void mod_init();
#endif

#ifdef SELAURA_ANDROID
#include <jni.h>
#include <android/native_activity.h>

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved);
#endif