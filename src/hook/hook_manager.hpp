#pragma once
#include "../sdk/symbol.hpp"
#include "../sdk/signatures.hpp"

#ifdef SELAURA_WINDOWS
#include <MinHook.h>
#else
#include <dobby.h>
#endif

#include <functional>
#include <type_traits>

namespace selaura {

    struct hook_group;

    struct hook_manager {
        hook_manager() = default;
        void init();

        template <typename symbol_t>
        void register_hook(symbol_t& symbol, auto callback) {
            pass_callback(symbol.resolve(), callback);
        }

        template <typename hookgroup_t, typename... args_t>
        void register_hookgroup(args_t... args) {
            hookGroups.emplace_back(std::make_unique<hookgroup_t>(*this, std::forward<args_t>(args)...));
        }
    private:
        std::vector<std::unique_ptr<hook_group>> hookGroups{};

        template <typename callback_t>
        void pass_callback(void* addr, callback_t callback, typename std::enable_if<std::is_function_v<std::remove_pointer_t<callback_t>>>::type* = 0) {
            return resolve_callback(addr, callback);
        }

        template <typename callback_t>
        void pass_callback(void* addr, callback_t callback, typename std::enable_if<not std::is_function_v<std::remove_pointer_t<callback_t>>>::type* = 0) {
            return resolve_callback(addr, callback, &callback_t::operator());
        }

        template <typename lambda_t, typename return_t, typename... args_t>
        void resolve_callback(void* addr, auto callback, return_t(__thiscall lambda_t::*)(void*, args_t...) const) {
            static uintptr_t ofunc = 0;
            static auto cb = callback;

            static auto invoker = [](args_t... args) -> return_t {
                return cb(std::bit_cast<void*>(ofunc), args...);
            };

            hook(addr, static_cast<return_t(__thiscall*)(args_t...)>(invoker), (void**)&ofunc);
        }

        void hook(void* target, void* trampoline, void** out) {
#ifdef SELAURA_WINDOWS
            MH_CreateHook(target, trampoline, out);
            MH_EnableHook(target);
#else
            DobbyHook(target, trampoline, out);
#endif
        }
    };

    struct hook_group {
        explicit hook_group(hook_manager& mgr);
    };
}
