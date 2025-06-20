#include "ScreenContext.hpp"
#include "../../../mem/symbols.hpp"

Tessellator* ScreenContext::getTessellator() {
	return hat::member_at<Tessellator*>(this, selaura::signatures::screencontext_tessellator.resolve());
}