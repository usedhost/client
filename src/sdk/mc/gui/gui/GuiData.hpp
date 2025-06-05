#pragma once
#include <libhat/access.hpp>
#include "../../world/phys/Vec2.hpp"

struct GuiData {
	Vec2 getScreenSize();
	float getGuiScale();
};