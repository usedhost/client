#pragma once

#include "../sdk/symbol.hpp"
#include "../sdk/signatures.hpp"

#ifdef SELAURA_WINDOWS
#include <MinHook.h>
#else
#include <dobby.h>
#endif

#include <memory>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <cassert>

namespace selaura {

    struct hook_group;

    class hook_manager {
    public:
        hook_manager() = default;
        void init();

        template <auto detour, typename symbol_t>
        void register_hook(base_symbol<symbol_t>& symbol) {
            using fn_t = decltype(detour);

            const auto hash = get_hash<detour>();
            if (hooks_.count(hash)) return;

            void* target = symbol.resolve();
            if (!target) return;

            void* detour_ptr = resolve_func_ptr(detour);
            fn_t original_fn = nullptr;

            hook_platform_install(target, detour_ptr, reinterpret_cast<void**>(&original_fn));

            hooks_.emplace(hash, std::make_shared<typed_hook<fn_t>>(original_fn));
            hook_entries_.emplace_back(target, detour_ptr);
        }

        template <auto detour>
        auto get_original() const {
            using fn_t = decltype(detour);
            const auto hash = get_hash<detour>();

            auto it = hooks_.find(hash);
            assert(it != hooks_.end() && "original function not found");

            return std::static_pointer_cast<typed_hook<fn_t>>(it->second)->original;
        }

        template <typename group_t, typename... Args>
        void register_hookgroup(Args&&... args) {
            hook_groups_.emplace_back(std::make_shared<group_t>(*this, std::forward<Args>(args)...));
        }

    private:
        struct hook_entry {
            void* target;
            void* detour;
            hook_entry(void* t, void* d) : target(t), detour(d) {}
        };

        struct hook_base {
            virtual ~hook_base() = default;
        };

        template <typename fn_t>
        struct typed_hook : hook_base {
            fn_t original;
            explicit typed_hook(fn_t fn) : original(fn) {}
        };

        std::vector<hook_entry> hook_entries_;
        std::unordered_map<size_t, std::shared_ptr<hook_base>> hooks_;
        std::vector<std::shared_ptr<hook_group>> hook_groups_;

        template <typename fn_t>
        void* resolve_func_ptr(fn_t fn) {
            if constexpr (std::is_pointer_v<fn_t>) {
                return reinterpret_cast<void*>(fn);
            }
            else if constexpr (std::is_member_function_pointer_v<fn_t>) {
#if defined(_MSC_VER)
                return *reinterpret_cast<void**>(&fn);
#elif defined(__clang__)
                union {
                    fn_t mfp;
                    struct {
                        void* addr;
                        ptrdiff_t adj;
                    } s;
                } caster{ .mfp = fn };
                return caster.s.addr;
#endif
            }
            else {
                static_assert(always_false<fn_t>, "unsupported function type for hook resolution");
            }
        }

        void hook_platform_install(void* target, void* detour, void** original) {
#ifdef SELAURA_WINDOWS
            MH_CreateHook(target, detour, original);
            MH_EnableHook(target);
#else
            DobbyHook(target, detour, original);
#endif
        }

        template <auto fn>
        static constexpr size_t get_hash() {
            return reinterpret_cast<size_t>(&fn);
        }

        template <typename>
        static constexpr bool always_false = false;
    };

    struct hook_group {
        explicit hook_group(hook_manager& mgr);
    };
}
