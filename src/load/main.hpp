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
#include <jni.h>
#include <dlfcn.h>
#include <android/native_activity.h>
#include <android_native_app_glue.h>

extern "C" void android_main(struct android_app* app);
extern "C" void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize);
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved);
#endif