#include "ScreenContext.hpp"

Tessellator* ScreenContext::getTessellator() {
	return hat::member_at<Tessellator*>(this, 0xC8);
}