#include "MinecraftGame.hpp"

#include "../../../instance.hpp"
#include "../../../hook/hook_manager.hpp"

void __cdecl MinecraftGame::update() {
    auto inst = selaura::instance::get();
    auto evm = inst->get<selaura::event_manager>();

    inst->set_minecraftgame(this);

    selaura::minecraftgame_update_event ev{};
    evm.dispatch<selaura::minecraftgame_update_event>(ev);

    auto hk = inst->get<selaura::hook_manager>();

    auto original = hk.get_original<&MinecraftGame::update>();
    return (this->*original)();
}