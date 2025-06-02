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
}