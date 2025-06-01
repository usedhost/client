#include "internal_hooks.hpp"

void* minecraftgame_update_ofunc;

void minecraftgame_update_hook(::MinecraftGame* _thisptr) {
    spdlog::info("{}", reinterpret_cast<void*>(_thisptr));
    auto func = reinterpret_cast<decltype(&minecraftgame_update_hook)>(minecraftgame_update_ofunc);
    func(_thisptr);
}

namespace selaura {
    internal_hooks::internal_hooks(hook_manager& mgr) : hook_group(mgr) {
        mgr.register_hook(signatures::minecraftgame_update.resolve(), reinterpret_cast<void*>(minecraftgame_update_hook), &minecraftgame_update_ofunc);
    };
}