#include "main.hpp"

void init(std::span<std::byte> bytes) {
	logger::init();
	logger::info("loaded selaura");
}

#ifdef _WIN32
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
        HMODULE hMinecraft = GetModuleHandleA("Minecraft.Windows.exe");
        if (hMinecraft == nullptr) return FALSE;

		DisableThreadLibraryCalls(hModule);
		try {
            MODULEINFO modInfo;
            if (GetModuleInformation(GetCurrentProcess(), hMinecraft, &modInfo, sizeof(MODULEINFO))) {
                std::span<std::byte> game_bytes(
                    reinterpret_cast<std::byte*>(modInfo.lpBaseOfDll),
                    modInfo.SizeOfImage
                );

                std::thread([=]() {
                    init(game_bytes);
                }).detach();
            }
            else {
                return FALSE;
            }
        } catch (...) {
            return FALSE;
        }
	}

	return TRUE;
}
#endif

#ifdef PLATFORM_LINUX
extern "C" [[gnu::visibility("default")]] void mod_preinit() {}

extern "C" [[gnu::visibility("default")]] void mod_init() {
    static std::span<std::byte> game_bytes;

    dl_iterate_phdr([](dl_phdr_info* info, size_t, void* mc) {
        auto h = dlopen(info->dlpi_name, RTLD_NOLOAD);
        dlclose(h);
        if (h == mc) {
            for (auto& phdr : std::span{ info->dlpi_phdr, info->dlpi_phnum }) {
                if (phdr.p_type == PT_LOAD && phdr.p_flags & PF_X) {
                    game_bytes = { reinterpret_cast<std::byte*>(info->dlpi_addr + phdr.p_vaddr), phdr.p_memsz };
                    return 1;
                }
            }
        }
        return 0;
        }, dlopen("libminecraftpe.so", 0));

    std::thread([=]() {
        init(game_bytes);
    }).detach();
}
#endif