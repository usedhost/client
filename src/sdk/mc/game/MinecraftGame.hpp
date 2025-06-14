#pragma once
#include <memory>
#include "../renderer/TextureGroup.hpp"

struct MinecraftGame {
    void __cdecl update();
	std::shared_ptr<mce::TextureGroup> getTextureGroup();
};