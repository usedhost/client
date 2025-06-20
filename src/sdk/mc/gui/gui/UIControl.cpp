#include "UIControl.hpp"
#include "../../../mem/symbols.hpp"

std::string UIControl::getLayerName() {
    return hat::member_at<std::string>(this, selaura::signatures::uicontrol_layername.resolve());
}