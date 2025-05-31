#include "event_manager.hpp"

namespace selaura {
    std::shared_ptr<selaura::event_manager> ev_inst;

    std::shared_ptr<selaura::event_manager> event_manager::get() {
        return selaura::ev_inst;
    }
};