#include "main.hpp"

#include <stdexcept>

#include "libhat/system.hpp"

#ifdef SELAURA_WINDOWS
DWORD WINAPI init(LPVOID lpvoid) {
    selaura::platform::create_instance(mc_handle);
    return true;
}

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD dw_reason, LPVOID lp_reserved) {
    if (dw_reason == DLL_PROCESS_ATTACH) {
        mc_handle = GetModuleHandleW(L"Minecraft.Windows.exe");
        if (mc_handle == nullptr) return false;

        DisableThreadLibraryCalls(mc_handle);
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)init, hmodule, 0, nullptr));
    }

    return true;
}
#else
void init_linux() {
    std::thread([]() {
        auto instance = std::make_shared<selaura::instance>();

        void* mc_handle = dlopen("libminecraftpe.so", 0);
        if (!mc_handle) throw std::runtime_error("Failed to open libminecraftpe.so");

        selaura::platform::create_instance(mc_handle);

    }).detach();
}
#endif

#ifdef SELAURA_LINUX
extern "C" [[gnu::visibility("default")]] void mod_preinit() {}

extern "C" [[gnu::visibility("default")]] void mod_init() {
    init_linux();
}
#endif

#ifdef SELAURA_ANDROID
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    init_linux();

    return JNI_VERSION_1_6;
}
#endif