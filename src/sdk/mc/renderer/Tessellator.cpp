#include "Tessellator.hpp"
#include "../../signatures.hpp"

void Tessellator::begin(mce::PrimitiveMode vertexFormat, const int maxVertices, const bool buildFaceData) {
    static auto func = reinterpret_cast<selaura::signatures::tessellator_begin_t>(selaura::signatures::tessellator_begin.resolve());
    func(this, vertexFormat, maxVertices, buildFaceData);
}

void Tessellator::vertexUV(float x, float y, float z, float u, float v) {
    static auto func = reinterpret_cast<selaura::signatures::tessellator_vertexuv_t>(selaura::signatures::tessellator_vertexuv.resolve());
    func(this, x, y, z, u, v);
}

void Tessellator::color(float r, float g, float b, float a) {
    static auto func = reinterpret_cast<selaura::signatures::tessellator_color_t>(selaura::signatures::tessellator_color.resolve());
    func(this, r, g, b, a);
}

void Tessellator::color(unsigned int col) {
    float r = ((col >> 0) & 0xFF) / 255.0f;
    float g = ((col >> 8) & 0xFF) / 255.0f;
    float b = ((col >> 16) & 0xFF) / 255.0f;
    float a = ((col >> 24) & 0xFF) / 255.0f;

    this->color(r, g, b, a);
}