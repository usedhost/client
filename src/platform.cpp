#include "platform.hpp"
#include "instance.hpp"

void selaura::platform::set_title(const std::string& title) {
#ifdef SELAURA_WINDOWS
    winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [title]() {
        winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(winrt::to_hstring(title));
    });
#endif
}

void selaura::platform::create_instance(void* mc_handle) {
    auto instance = std::make_shared<selaura::instance>();
#ifdef SELAURA_WINDOWS
    MODULEINFO module_info;
    if (!GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(mc_handle), &module_info, sizeof(module_info))) {
        throw std::runtime_error("Failed to get module information.");
    }

    mc_bytes = { reinterpret_cast<std::byte*>(module_info.lpBaseOfDll), module_info.SizeOfImage };
#else
    dl_iterate_phdr([](dl_phdr_info* info, size_t, void* data) -> int {
        if (info->dlpi_name && std::string_view(info->dlpi_name).contains("libminecraftpe.so")) {
            mc_bytes = { reinterpret_cast<std::byte*>(info->dlpi_addr), info->dlpi_phdr[1].p_memsz };
            return 1;
        }
        return 0;
    }, &mc_bytes);

    instance->set_mc_bytes(mc_bytes);
#endif
    if (instance->start()) instance->init();
}

std::filesystem::path selaura::platform::get_data_folder() {
    std::filesystem::path dir = {};
#ifdef SELAURA_WINDOWS
    char* localAppData = nullptr;
    size_t size = 0;
    _dupenv_s(&localAppData, &size, "APPDATA");

    if (localAppData) {
        dir = std::filesystem::path(localAppData + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Selaura"));
    }
#elif defined(SELAURA_LINUX)
    dir = "/data/data/com.mojang.minecraftpe/Selaura";
#elif defined(SELAURA_ANDROID)
    dir = "/data/data/com.selauraclient.launcher/Selaura";
#endif
    std::filesystem::create_directories(dir);

    return dir;
}

selaura::platform::mod_info_t selaura::platform::load_mod_info(std::filesystem::path path) {
#ifdef SELAURA_WINDOWS

    HMODULE mod_handle = LoadLibraryW(path.wstring().c_str());
    if (!mod_handle) {
        spdlog::error("Failed to load mod: {}", path.filename().string());
    }

    auto mod_entry = reinterpret_cast<mod_info_t>(GetProcAddress(mod_handle, "SelauraRuntime_LoadModInfo"));

#else

    void* mod_handle = dlopen(path.c_str(), RTLD_NOW);
    if (!mod_handle) {
        spdlog::error("Failed to load mod: {}: {}", path.filename().string(), dlerror());
        continue;
    }

    auto mod_entry = reinterpret_cast<mod_info_t>(dlsym(mod_handle, "SelauraRuntime_LoadModInfo"));

#endif

    if (!mod_entry) {
        spdlog::warn("Mod {} does not export SelauraRuntime_LoadModInfo", path.filename().string());
    }

    return mod_entry;
}


selaura::platform::mod_entry_t selaura::platform::load_mod(std::filesystem::path path) {
#ifdef SELAURA_WINDOWS

    HMODULE mod_handle = LoadLibraryW(path.wstring().c_str());
    if (!mod_handle) {
        spdlog::error("Failed to load mod: {}", path.filename().string());
    }

    auto mod_entry = reinterpret_cast<mod_entry_t>(GetProcAddress(mod_handle, "SelauraRuntime_LoadMod"));

#else

    void* mod_handle = dlopen(path.c_str(), RTLD_NOW);
    if (!mod_handle) {
        spdlog::error("Failed to load mod: {}: {}", path.filename().string(), dlerror());
        continue;
    }

    auto mod_entry = reinterpret_cast<mod_entry_t>(dlsym(mod_handle, "SelauraRuntime_LoadMod"));

#endif

    if (!mod_entry) {
        spdlog::warn("Mod {} does not export SelauraRuntime_LoadMod", path.filename().string());
    }

    return mod_entry;
}

void selaura::platform::hook_init() {
#ifdef SELAURA_WINDOWS
    MH_Initialize();
#else
    return;
#endif
}

void selaura::platform::hook(void* target, void* detour, void** original) {
#ifdef SELAURA_WINDOWS
    MH_CreateHook(target, detour, original);
    MH_EnableHook(target);
#else
    DobbyHook(target, detour, original);
#endif
}