#include "MinecraftGame.hpp"

#include "../../instance.hpp"
#include "../../hook/hook_manager.hpp"

void __cdecl MinecraftGame::update() {
    auto inst = selaura::instance::get();
    auto hk = inst->get<selaura::hook_manager>();

    auto original = hk.get_original<&MinecraftGame::update>();
    return (this->*original)();
}