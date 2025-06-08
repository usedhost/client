#pragma once
#include "../screen.hpp"

namespace selaura {
    struct click_gui : public screen {
        DEFINE_SCREEN_TRAITS("ClickGUI");

        click_gui();

        void on_render(selaura::setupandrender_event& ev) override;
    };
};