#pragma once
#include "tessellator.hpp"
#include <libhat/access.hpp>

namespace selaura::bedrock {
	class ScreenContext /* : public UIScreenContext, public mce::MeshContent*/ {
	public:
		std::byte padding0[160];
		Tessellator* tessellator; // Tessellator&

		Tessellator* getTessellator() {
			return hat::member_at<Tessellator*>(this, 0xC8);
		}
	};
};