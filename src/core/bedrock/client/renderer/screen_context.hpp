#pragma once

namespace selaura::bedrock {
	class ScreenContext /* : public UIScreenContext, public mce::MeshContent*/ {
	public:
		std::byte padding0[160];
		void* tessellator; // Tessellator&
	};
};