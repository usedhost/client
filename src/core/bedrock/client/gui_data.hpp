#pragma once
#include "../../core/math/vec2.hpp"

namespace bedrock {
    class GuiData {
    private:
        char pad[0x40];
    public:
        Vec2 mScreenSize;
        Vec2 mScreenSizeScaled;
    private:
        char pad2[0x4];
    public:
        float mGuiScale;

        void displayClientMessage(const std::string& str) {
            if (str.empty()) return;
            static auto sig = GET_SIGNATURE("GuiData::displayClientMessage");
            char a3[0x28]{};

            using func_t = void(*)(GuiData*, const std::string&, char*, bool);
            static auto func = reinterpret_cast<func_t>(sig.value());
            func(this, str, a3, true);
        }
    };
}