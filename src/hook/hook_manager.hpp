#pragma once
#include "../sdk/symbol.hpp"
#include "../sdk/signatures.hpp"

#ifdef SELAURA_WINDOWS
#include <MinHook.h>
#else
#include <dobby.h>
#endif

#include <vector>
#include <memory>
#include <type_traits>

namespace selaura {

    struct hook_group;

    struct hook_t {
        hook_t(uintptr_t address, void* detour, void* ptr) {
            this->address = address;
            this->detour = detour;
            this->ptr = ptr;
        }
        ~hook_t() = default;

		uintptr_t address;
        void* detour;
        void* ptr;

        template <typename fn_t>
        inline fn_t ofunc() {
			return static_cast<fn_t>(this->ptr);
        }
    };

    struct hook_manager {
        hook_manager() = default;
        void init();

        std::shared_ptr<hook_t> register_hook(void* target, void* trampoline, void* out) {
#ifdef SELAURA_WINDOWS
            MH_CreateHook(target, trampoline, reinterpret_cast<void**>(out));
            MH_EnableHook(target);
#else
            DobbyHook(target, trampoline, reinterpret_cast<void**>(out));
#endif
            return std::make_shared<hook_t>(
                reinterpret_cast<uintptr_t>(target),
                trampoline,
                out
            );
        }

        template <typename hookgroup_t, typename... args_t>
        void register_hookgroup(args_t... args) {
            hookGroups.emplace_back(std::make_unique<hookgroup_t>(*this, std::forward<args_t>(args)...));
        }

    private:
        std::vector<std::unique_ptr<hook_group>> hookGroups{};
    };

    struct hook_group {
        explicit hook_group(hook_manager& mgr);
    };
}
