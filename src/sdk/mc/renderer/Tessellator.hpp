#pragma once
#include "helpers/MeshHelpers.hpp"

struct Tessellator {
	void begin(mce::PrimitiveMode vertexFormat, const int maxVertices, const bool buildFaceData = false);
	void vertexUV(float x, float y, float z, float u, float v);
	void color(float r, float g, float b, float a);
	void color(unsigned int col);
};