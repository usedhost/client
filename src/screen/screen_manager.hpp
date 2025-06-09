#pragma once
#include <vector>
#include <memory>
#include <string_view>
#include <type_traits>
#include <algorithm>

#include "screen.hpp"
#include "impl/click_gui.hpp"

namespace selaura {
    struct screen_manager {
        screen_manager() = default;

        void init() {
            add_screen<selaura::click_gui>();
        }

        template <typename T, typename... Args>
        T* add_screen(Args&&... args) {
            static_assert(std::is_base_of_v<screen, T>, "T must derive from screen");
            auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
            T* raw_ptr = ptr.get();
            screens.emplace_back(std::move(ptr));
            return raw_ptr;
        }

        void for_each(auto&& callback) {
            for (auto& scr : screens)
                callback(*scr);
        }

        void for_each(auto&& callback) const {
            for (const auto& scr : screens)
                callback(*scr);
        }

        template <typename T>
        T* get() {
            for (auto& scr : screens) {
                if (auto* casted = dynamic_cast<T*>(scr.get()))
                    return casted;
            }
            return nullptr;
        }

    private:
        std::vector<std::unique_ptr<screen>> screens;
    };
}
