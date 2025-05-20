#include "main.hpp"

#ifdef SELAURA_WINDOWS
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	selaura::hmodule = hModule;

	if (dwReason == DLL_PROCESS_ATTACH) {
		HMODULE mc = GetModuleHandleA("Minecraft.Windows.exe");
		if (mc == nullptr) return FALSE;

		DisableThreadLibraryCalls(mc);
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)selaura::init, hModule, 0, nullptr));
	}

	return TRUE;
}
#endif

#ifdef SELAURA_LINUX
extern "C" [[gnu::visibility("default")]] void mod_preinit() {
    
}

extern "C" [[gnu::visibility("default")]] void mod_init() {
	std::thread([]() {
		selaura::init();
	}).detach();
}
#endif

#ifdef SELAURA_ANDROID
static void (*android_main_minecraft)(struct android_app* app);
static void (*ANativeActivity_onCreate_minecraft)(ANativeActivity* activity, void* savedState, size_t savedStateSize);

extern "C" void android_main(struct android_app* app) {
	android_main_minecraft(app);
}

extern "C" void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
	ANativeActivity_onCreate_minecraft(activity, savedState, savedStateSize);
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	void* handle = dlopen("libminecraftpe.so", RTLD_LAZY);
	android_main_minecraft = (void (*)(struct android_app*)) dlsym(handle, "android_main");
	ANativeActivity_onCreate_minecraft = (void (*)(ANativeActivity*, void*, size_t)) dlsym(handle, "ANativeActivity_onCreate");

	std::thread([]() {
		selaura::init();
	}).detach();

	return JNI_VERSION_1_6;
}

#endif