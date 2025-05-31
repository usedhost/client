#include "process.hpp"

namespace selaura {
    std::byte* process::get_process_base() {
        return this->base;
    }
    std::size_t process::get_process_size() {
        return this->size;
    }
    process get_process_handle() {
#ifdef SELAURA_WINDOWS
        std::string_view name = "Minecraft.Windows.exe";
        HMODULE hModule = GetModuleHandleW(std::wstring(name.begin(), name.end()).c_str());
        if (!hModule) {
            throw std::runtime_error("Failed to get module handle.");
        }

        MODULEINFO moduleInfo;
        if (!GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(moduleInfo))) {
            throw std::runtime_error("GetModuleInformation failed.");
        }

        return {
            reinterpret_cast<std::byte*>(moduleInfo.lpBaseOfDll),
            moduleInfo.SizeOfImage,
            reinterpret_cast<void*>(hModule)
        };
#else
        std::string_view name = "libminecraftpe.so";
        void* handle = dlopen(name.data(), RTLD_NOLOAD);
        if (!handle) {
            throw std::runtime_error("dlopen failed.");
        }

        process detail;
        detail.native = handle;

        dl_iterate_phdr([](dl_phdr_info* info, size_t, void* data) -> int {
            auto* detail = reinterpret_cast<process_module*>(data);
            if (info->dlpi_name && std::string_view(info->dlpi_name).contains("libminecraftpe.so")) {
                detail->base = reinterpret_cast<std::byte*>(info->dlpi_addr);
                detail->size = info->dlpi_phdr[1].p_memsz;
                return 1;
            }
            return 0;
            }, &detail);

        return {
            detail.base,
            detail.size,
            detail.native
        };
#endif
    }
};