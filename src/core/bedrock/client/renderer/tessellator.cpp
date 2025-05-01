#include "tessellator.hpp"

namespace selaura::bedrock {
	void Tessellator::begin(mce::PrimitiveMode mode, int maxVertices) {}
	void Tessellator::vertex(float x, float y, float z) {}
	void Tessellator::vertex(const Vec3& vec) {
		this->vertex(vec.x, vec.y, vec.z);
	}
	void Tessellator::vertex(float x, float y) {
		this->vertex(x, y, 0);
	}
	void Tessellator::vertex(const Vec2& vec) {
		this->vertex(vec.x, vec.y, 0);
	}
	void Tessellator::vertexUV(float x, float y, float z, float uvX, float uvY) {}
	void Tessellator::vertexUV(const Vec3& vec, float uvX, float uvY) {
		this->vertexUV(vec.x, vec.y, vec.z, uvX, uvY);
	}
	mce::Mesh Tessellator::end(uint64_t a3, std::string_view debugName, int a5) {}
	void Tessellator::setPostTransformOffset(float xo, float yo, float zo) {
		this->PostTransformOffset.x = xo;
		this->PostTransformOffset.y = yo;
		this->PostTransformOffset.z = zo;
	}

    void Tessellator::setPosTransformOffset(Vec3 v) {
        this->PostTransformOffset = v;
    }

    Vec3* Tessellator::getPostTransformOffset() {
        return &this->PostTransformOffset;
    }

    void Tessellator::addPostTransformOffset(float x, float y, float z) {
        this->PostTransformOffset.x += x;
        this->PostTransformOffset.y += y;
        this->PostTransformOffset.z += z;
    }

    void Tessellator::addPostTransformOffset(Vec3 v) {
        this->PostTransformOffset = this->PostTransformOffset + v;
    }

    void Tessellator::resetPostTransformScale() {
        this->PostTransformScale = Vec3(1.0f, 1.0f, 1.0f);
    }

    void Tessellator::color(float r, float g, float b, float a) {
        struct PackedColors {
            union {
                struct {
                    char r;
                    char g;
                    char b;
                    char a;
                };
                unsigned int intValue;
            };
        };

        PackedColors result{};
        result.r = static_cast<char>(r * 255.0f);
        result.g = static_cast<char>(g * 255.0f);
        result.b = static_cast<char>(b * 255.0f);
        result.a = static_cast<char>(a * 255.0f);

        nextColor = result.intValue;
    }

    void Tessellator::color(uint32_t packed) {
        nextColor = packed;
    }

    void Tessellator::beginOverride() {
        begin(mce::PrimitiveMode::QuadList, 0);
        voidBeginEnd = true;
    }

    void Tessellator::clear() {}

    mce::Mesh Tessellator::endOverride(uint64_t a3, std::string_view debugName, int a5) {
        voidBeginEnd = false;
        return end(a3, debugName, a5);
    }
};