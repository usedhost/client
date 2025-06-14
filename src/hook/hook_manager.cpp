#include "hook_manager.hpp"
#include <spdlog/spdlog.h>

#include "impl/hook_registry.hpp"

namespace selaura {
    hook_group::hook_group(hook_manager& mgr) {};

    void hook_manager::init() {
#ifdef SELAURA_WINDOWS
        MH_Initialize();
#endif

        register_hookgroup<hook_registry>();
        
    }

    void hook_manager::destroy() {
#ifdef SELAURA_WINDOWS
        MH_RemoveHook(MH_ALL_HOOKS);
        MH_Uninitialize();
#else
        for (auto& hook : hook_entries_) {
            DobbyDestroy((void*)hook.target);
        }
#endif
    }

}