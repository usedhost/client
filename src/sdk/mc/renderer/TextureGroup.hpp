#pragma once
#include "../../../sdk/mc/deps/minecraftrenderer/renderer/BedrockTexture.hpp"
#include "../../../sdk/mc/deps/core/resource/ResourceHelper.hpp"
#include "../../../sdk/mc/deps/coregraphics/ImageBuffer.hpp"
#include "../../../sdk/mc/renderer/helpers/MeshHelpers.hpp"

namespace mce {
    class TextureGroup {
    public:
        mce::BedrockTexture& uploadTexture(const ResourceLocation& resource, cg::ImageBuffer image_buffer);
        void unloadAllTextures();
    };
};