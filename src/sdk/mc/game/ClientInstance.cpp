#include "ClientInstance.hpp"
#include "../../signatures.hpp"

GuiData* ClientInstance::getGuiData() {
	return hat::member_at<GuiData*>(this, selaura::signatures::clientinstance_guidata.resolve());
}