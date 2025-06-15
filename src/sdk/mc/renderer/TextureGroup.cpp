#include "TextureGroup.hpp"
#include "../../signatures.hpp"
#include "../../../instance.hpp"
#include "../../../renderer/renderer.hpp"
#include <spdlog/spdlog.h>

namespace mce {
    mce::BedrockTexture& TextureGroup::uploadTexture(const ResourceLocation& resource, cg::ImageBuffer image_buffer) {
        static auto func = reinterpret_cast<selaura::signatures::mce_texturegroup_uploadtexture_t>(selaura::signatures::mce_texturegroup_uploadtexture.resolve());
        return func(this, resource, image_buffer);
    }

    void TextureGroup::unloadAllTextures() {
        auto inst = selaura::instance::get();
        auto renderer = inst->get<selaura::renderer>();

        renderer.set_textures_unloaded();

        auto hk = inst->get<selaura::hook_manager>();
        auto original = hk.get_original<&mce::TextureGroup::unloadAllTextures>();
        return (this->*original)();
    }
}   