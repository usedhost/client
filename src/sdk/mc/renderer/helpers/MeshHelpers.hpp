#pragma once
#include <cstddef>
#include <cstdint>
#include <variant>
#include <memory>

#include "../../HashedString.hpp"

namespace mce {
    enum class PrimitiveMode : uint8_t {
        None,
        QuadList,
        TriangleList,
        TriangleStrip,
        LineList,
        LineStrip
    };

    struct BedrockTexture {};
    struct TexturePtr {};

    struct MaterialPtr {
        static mce::MaterialPtr* createMaterial(const HashedString& name);
    };
};

struct MeshHelpers {
    static void renderMeshImmediately(void* a1, void* a2, void* a3);
};