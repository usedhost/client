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

selaura::plugin* selaura::platform::load_plugin(std::filesystem::path path) {
#ifdef SELAURA_WINDOWS

    HMODULE plugin_handle = LoadLibraryW(path.wstring().c_str());
    if (!plugin_handle) {
        spdlog::error("Failed to load plugin: {}", path.filename().string());
    }

    auto plugin_entry = reinterpret_cast<plugin_entry_t>(GetProcAddress(plugin_handle, "SelauraRuntime_RegisterPlugin"));

#else

    void* plugin_handle = dlopen(path.c_str(), RTLD_NOW);
    if (!plugin_handle) {
        spdlog::error("Failed to load plugin: {}: {}", path.filename().string(), dlerror());
        continue;
    }

    auto plugin_entry = reinterpret_cast<plugin_entry_t>(dlsym(plugin_handle, "SelauraRuntime_RegisterPlugin"));

#endif

    if (!plugin_entry) {
        spdlog::warn("Plugin {} does not export SelauraRuntime_RegisterPlugin", path.filename().string());
    }

    return plugin_entry();
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