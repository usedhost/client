#include "GuiData.hpp"

Vec2<float> GuiData::getScreenSize() {
	return hat::member_at<Vec2<float>>(this, 0x40);
}