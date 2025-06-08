#pragma once
#include <string_view>
#include <type_traits>

#include "impl/click_gui.hpp"

namespace selaura {
    template <typename T, typename... remainingT>
    struct screen_storage {
        T mod;
        screen_storage<remainingT...> remaining;

        void for_each(auto callback) {
            callback(mod);
            remaining.for_each(callback);
        }
    };

    template <typename T>
    struct screen_storage<T> {
        T mod;
        void for_each(auto callback) {
            callback(mod);
        }
    };

    struct screen_manager {
        screen_manager() = default;

        using screens_type = screen_storage<
            selaura::click_gui
        >;

        void for_each(auto callback) {
            screens.for_each(callback);
        }

        void for_each(auto callback) const {
            screens.for_each(callback);
        }

        template <typename T>
        T* get() {
            T* result = nullptr;
            screens.for_each([&]<typename screens_type>(screens_type & screen) {
                if (result != nullptr) return;
                if (std::is_same_v<T, screens_type>) {
                    result = &screen;
                }
            });

            return result;
        }

        [[nodiscard]] auto* find(std::string_view name) {
            screen* result = nullptr;
            screens.for_each([&]<typename screens_type>(screens_type & screen) {
                if (result != nullptr) return;
                if (screens_type::info::name == name) {
                    result = &screen;
                }
            });

            return result;
        }
    private:
        screens_type screens;
    };
};