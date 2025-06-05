#include "GuiData.hpp"

Vec2<float> GuiData::getScreenSize() {
	return hat::member_at<Vec2<float>>(this, 0x40);
}

float GuiData::getGuiScale() {
	return hat::member_at<float>(this, 0x5C);
}