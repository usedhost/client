#pragma once
#include "../../core/math/vec2.hpp"
#include "../../core/math/vec3.hpp"
#include "../../../../client/symbol/resolver.hpp"
#include <memory>
#include <vector>
#include <optional>
#include <bit>
#include <string_view>

namespace bedrock {
    namespace mce {
        class TexturePtr;
        class MeshContext {};
        class MaterialPtr {};
        class Mesh {
        public:
            void renderMesh(mce::MeshContext& mctx, const mce::MaterialPtr& mPtr, const mce::TexturePtr& texture) {
                using func_t = void(*)(Mesh*, mce::MeshContext&, const mce::MaterialPtr&, const mce::TexturePtr&);
                static uintptr_t val = selaura::resolver::signature("40 53 56 57 48 81 EC ? ? ? ? 48 8B D9 C6 44 24").value();
                static auto func = reinterpret_cast<func_t>(val);
                func(this, mctx, mPtr, texture);
            }
        };
        class MeshData {
        public:
            std::byte padding0[8];
            std::vector<Vec3> mPositions;
            std::byte padding32[272 - 32];
        };

        enum class PrimitiveMode : int {
            None = 0,
            QuadList = 1,
            TriangleList = 2,
            TriangleStrip = 3,
            LineList = 4,
            LineStrip = 5,
        };
    }

    struct TessellatorQuadInfo {
    public:
        unsigned char facing;
        unsigned char twoFace;
        Vec3 centroid;
    };

	class Tessellator {
    public:
        bool isFormatFixed;
        std::byte padding1[7];
        mce::MeshData meshData;
        std::byte padding280[328 - 280];
        std::optional<unsigned int> nextColor;
        std::byte padding336[12];
        Vec3 postTransformOffset;
        Vec3 postTransformScale;
        std::byte padding372[4];
        std::vector<TessellatorQuadInfo> quadInfoList;
        std::byte padding400[16];
        bool applyTransform;
        std::byte padding417[67];
        bool noColor;
        bool voidBeginEnd;
        std::byte padding486[46];
        bool tessellating;
        std::byte padding533[19];
        unsigned int count;
        std::byte padding556[5];
        bool buildFaceData;
    public:
        void begin(mce::PrimitiveMode mode = mce::PrimitiveMode::TriangleList, int maxVertices = 0);
        void beginOverride();

        void vertex(float x, float y, float z);
        void vertex(const Vec3&);
        void vertex(float x, float y);
        void vertex(const Vec2&);
        void vertexUV(float x, float y, float z, float uvX, float uvY);
        void vertexUV(const Vec3&, float uvX, float uvY);

        void color(float r, float g, float b, float a);
        void color(unsigned int rgba);

        void setPostTransformOffset(float xo, float yo, float zo);
        void setPosTransformOffset(Vec3 v);
        Vec3* getPostTransformOffset();
        void addPostTransformOffset(float x, float y, float z);
        void addPostTransformOffset(Vec3 v);

        void resetPostTransformScale();

        mce::Mesh end(uint64_t a3, std::string_view debugName, int a5);
        void clear();
        mce::Mesh endOverride(uint64_t a3, std::string_view debugName, int a5);
	};
}