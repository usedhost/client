#include "TextureGroup.hpp"
#include "../../signatures.hpp"
#include <spdlog/spdlog.h>

namespace mce {
    mce::BedrockTexture& TextureGroup::uploadTexture(const ResourceLocation& resource, cg::ImageBuffer image_buffer) {
        static auto func = reinterpret_cast<selaura::signatures::mce_texturegroup_uploadtexture_t>(selaura::signatures::mce_texturegroup_uploadtexture.resolve());
        spdlog::info("sig addr {}", reinterpret_cast<uintptr_t>(selaura::signatures::mce_texturegroup_uploadtexture.resolve()));
        return func(this, resource, image_buffer);
    }
}   