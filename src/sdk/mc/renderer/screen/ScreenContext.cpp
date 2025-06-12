#include "ScreenContext.hpp"
#include "../../../signatures.hpp"

Tessellator* ScreenContext::getTessellator() {
	return hat::member_at<Tessellator*>(this, selaura::signatures::screencontext_tessellator.resolve());
}