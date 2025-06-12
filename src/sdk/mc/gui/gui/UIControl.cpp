#include "UIControl.hpp"
#include "../../../signatures.hpp"

std::string UIControl::getLayerName() {
    return hat::member_at<std::string>(this, selaura::signatures::uicontrol_layername.resolve());
}