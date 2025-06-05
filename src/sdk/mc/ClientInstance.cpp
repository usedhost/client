#include "ClientInstance.hpp"

GuiData* ClientInstance::getGuiData() {
	return hat::member_at<GuiData*>(this, 0x5B8);
}