#pragma once

#include <string_view>
#include <optional>

#include <libhat/scanner.hpp>

namespace selaura {
    struct symbol {
        std::string_view name;
        uintptr_t addr = 0;

        symbol() = default;

        symbol(std::string_view sym, uintptr_t abs_addr) {
            this->name = sym;
            this->addr = abs_addr;
        }

        symbol(std::string_view sym, std::string_view sig) {
            this->name = sym;

            const auto parsed = hat::parse_signature(sig);
            if (!parsed.has_value()) return;

#if defined(_WIN32) || defined(_WIN64)
            constexpr std::string_view minecraft_module_name = "Minecraft.Windows.exe";
#else
            constexpr std::string_view minecraft_module_name = "libminecraftpe.so";
#endif
            const static auto mod = hat::process::get_module(minecraft_module_name);
            const auto begin = reinterpret_cast<std::byte*>(mod.value().address());
            const auto end = begin + 1;
            const auto result = hat::find_pattern(begin, end, parsed.value());

            this->addr = reinterpret_cast<uintptr_t>(result.get());
        }

        symbol(std::string_view sym, std::string_view sig, ptrdiff_t offset) {
            this->name = sym;
        }

        [[nodiscard]] bool valid() const { return addr != 0; }
        [[nodiscard]] uintptr_t get() const { return addr; }
    };
};

#define DEFINE_OFFSET(symbolName, offset) \
    selaura::symbol symbolName{ #symbolName, offset }

#define DEFINE_SIGNATURE(symbolName, signature) \
    selaura::symbol symbolName{ #symbolName, signature }

#define DEFINE_SIGNATURE_OFFSET(symbolName, signature, offset) \
    selaura::symbol symbolName{ #symbolName, signature, offset }