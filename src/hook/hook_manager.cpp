#include "hook_manager.hpp"
#include <spdlog/spdlog.h>

#include "impl/visual_hooks.hpp"

namespace selaura {
    hook_group::hook_group(hook_manager& mgr) {};

    void hook_manager::init() {
#ifdef SELAURA_WINDOWS
        MH_Initialize();
#endif

        register_hookgroup<visual_hooks>();
        
    }
}