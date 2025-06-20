#include "ClientInstance.hpp"
#include "../../mem/symbols.hpp"

GuiData* ClientInstance::getGuiData() {
	return hat::member_at<GuiData*>(this, selaura::signatures::clientinstance_guidata.resolve());
}