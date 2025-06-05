#pragma once
#include <libhat/access.hpp>
#include "math.hpp"

struct GuiData {
	Vec2<float> getScreenSize();
	float getGuiScale();
};