#pragma once
#include "tessellator.hpp"

namespace selaura::bedrock {
	class ScreenContext /* : public UIScreenContext, public mce::MeshContent*/ {
	public:
		std::byte padding0[160];
		Tessellator* tessellator; // Tessellator&
	};
};