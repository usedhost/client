#include "internal_hooks.hpp"

namespace selaura {
    internal_hooks::internal_hooks(hook_manager& mgr) : hook_group(mgr) {
        mgr.register_hook(selaura::signatures::minecraftgame_update, +[](void* ofunc, ::MinecraftGame* _thisptr) {
            using ofunc_t = selaura::signatures::minecraftgame_update_t;
            std::bit_cast<ofunc_t>(ofunc)(_thisptr);


            minecraftgame_update_event ev{};
            event_manager::get()->dispatch(ev);
        });
    };
}