#pragma once

#include "../../core/math/vec2.hpp"
#include "../../world/phys/aabb.hpp"

namespace bedrock {
	struct AABBShapeComponent {
		AABB aabb;
		Vec2 dim;
	};
};