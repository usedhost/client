#include "screen.hpp"

namespace selaura {
    screen::~screen() noexcept {
        this->enabled = false;
    }

    void screen::set_enabled(bool enabled) {
        this->enabled = enabled;
    }

    bool screen::is_enabled() const {
        return this->enabled;
    }

    void screen::toggle() {
        this->enabled = !this->enabled;
    }

    void screen::set_hotkey(int hotkey) {
        this->hotkey = hotkey;
    }

    int screen::get_hotkey() const {
        return this->hotkey;
    }

    void screen::on_enable() {}
    void screen::on_disable() {}
    void screen::on_render(selaura::setupandrender_event& ev) {}
};