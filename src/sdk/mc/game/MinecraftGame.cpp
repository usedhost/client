#include "MinecraftGame.hpp"

#include "../../../instance.hpp"
#include "../../../sdk/globals.hpp"
#include "../../../hook/hook_manager.hpp"

void __cdecl MinecraftGame::update() {
    auto inst = selaura::instance::get();
    auto evm = inst->get<selaura::event_manager>();

    inst->get<selaura::globals>().mc_game = this;

    selaura::minecraftgame_update_event ev{};
    evm.dispatch<selaura::minecraftgame_update_event>(ev);

    auto hk = inst->get<selaura::hook_manager>();

    auto original = hk.get_original<&MinecraftGame::update>();
    return (this->*original)();
}

std::shared_ptr<mce::TextureGroup> MinecraftGame::getTextureGroup() {
    return hat::member_at<std::shared_ptr<mce::TextureGroup>>(this, selaura::signatures::minecraftgame_gettexturegroup.resolve());
}