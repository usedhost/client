#include "tessellator.hpp"
#include "../../../../client/symbol/resolver.hpp"

namespace selaura::bedrock {
	void Tessellator::begin(mce::PrimitiveMode mode, int maxVertices) {
        using func_t = void(*)(Tessellator*, mce::PrimitiveMode, int, bool);
        static auto func = reinterpret_cast<func_t>(selaura::resolver::signature("40 53 55 48 83 EC 28 80 B9").value());
        func(this, mode, maxVertices, false);
    }
	void Tessellator::vertex(float x, float y, float z) {
        using func_t = void(*)(Tessellator*, float, float, float);
        static auto func = reinterpret_cast<func_t>(selaura::resolver::signature("40 57 48 81 EC ? ? ? ? 0F 29 7C ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 8B 81").value());
        func(this, x, y, z);
    }
	void Tessellator::vertex(const Vec3& vec) {
		this->vertex(vec.x, vec.y, vec.z);
	}
	void Tessellator::vertex(float x, float y) {
		this->vertex(x, y, 0);
	}
	void Tessellator::vertex(const Vec2& vec) {
		this->vertex(vec.x, vec.y, 0);
	}
	void Tessellator::vertexUV(float x, float y, float z, float uvX, float uvY) {
        using func_t = void(*)(Tessellator*, float, float, float, float, float);
        static auto func = reinterpret_cast<func_t>(selaura::resolver::signature("48 83 EC ? 80 B9 ? ? ? ? ? 0F 57 E4").value());
        func(this, x, y, z, uvX, uvY);
    }
	void Tessellator::vertexUV(const Vec3& vec, float uvX, float uvY) {
		this->vertexUV(vec.x, vec.y, vec.z, uvX, uvY);
	}
	mce::Mesh Tessellator::end(uint64_t a3, std::string_view debugName, int a5) {
        using func_t = mce::Mesh(*)(Tessellator*, uint64_t, std::string_view, int);
        static auto func = reinterpret_cast<func_t>(selaura::resolver::signature("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 44 0F 29 90 ? ? ? ? 44 0F 29 98 ? ? ? ? 44 0F 29 A0 ? ? ? ? 44 0F 29 A8 ? ? ? ? 44 0F 29 B0 ? ? ? ? 44 0F 29 B8 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F9").value());
        return func(this, a3, debugName, a5);
    }
	void Tessellator::setPostTransformOffset(float xo, float yo, float zo) {
		this->postTransformOffset.x = xo;
		this->postTransformOffset.y = yo;
		this->postTransformOffset.z = zo;
	}

    void Tessellator::setPosTransformOffset(Vec3 v) {
        this->postTransformOffset = v;
    }

    Vec3* Tessellator::getPostTransformOffset() {
        return &this->postTransformOffset;
    }

    void Tessellator::addPostTransformOffset(float x, float y, float z) {
        this->postTransformOffset.x += x;
        this->postTransformOffset.y += y;
        this->postTransformOffset.z += z;
    }

    void Tessellator::addPostTransformOffset(Vec3 v) {
        this->postTransformOffset = this->postTransformOffset + v;
    }

    void Tessellator::resetPostTransformScale() {
        this->postTransformScale = Vec3(1.0f, 1.0f, 1.0f);
    }

    void Tessellator::color(float r, float g, float b, float a) {
        using func_t = void(*)(Tessellator*, float, float, float, float);
        static auto func = reinterpret_cast<func_t>(selaura::resolver::signature("80 B9 ? ? ? ? ? 4C 8B C1 75").value());
        func(this, r, g, b, a);
    }

    void Tessellator::color(unsigned int rgba) {
        float r = ((rgba >> 24) & 0xFF) / 255.0f;
        float g = ((rgba >> 16) & 0xFF) / 255.0f;
        float b = ((rgba >> 8) & 0xFF) / 255.0f;
        float a = (rgba & 0xFF) / 255.0f;
        this->color(r, g, b, a);
    }

    void Tessellator::beginOverride() {
        begin(mce::PrimitiveMode::QuadList, 0);
        voidBeginEnd = true;
    }

    //void Tessellator::clear() {}

    mce::Mesh Tessellator::endOverride(uint64_t a3, std::string_view debugName, int a5) {
        voidBeginEnd = false;
        return end(a3, debugName, a5);
    }
};