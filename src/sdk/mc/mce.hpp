#pragma once
#include <cstdint>
#include <variant>

namespace mce {
    enum class PrimitiveMode : uint8_t {
        None,
        QuadList,
        TriangleList,
        TriangleStrip,
        LineList,
        LineStrip
    };
};

struct MeshHelpers {
    static void renderMeshImmediately(void* a1, void* a2, void* a3);
};