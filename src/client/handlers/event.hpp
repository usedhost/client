#pragma once
#include <functional>
#include <vector>
#include <algorithm>
#include <memory>
#include <cstdint>
#include <type_traits>
#include "../types/event_types.hpp"

namespace selaura_handlers {

    template <typename T>
    struct callable_traits;

    template <typename R, typename Arg>
    struct callable_traits<R(*)(Arg)> {
        using argument_type = Arg;
    };

    template <typename R, typename Arg>
    struct callable_traits<std::function<R(Arg)>> {
        using argument_type = Arg;
    };

    template <typename C, typename R, typename Arg>
    struct callable_traits<R(C::*)(Arg) const> {
        using argument_type = Arg;
    };

    template <typename C, typename R, typename Arg>
    struct callable_traits<R(C::*)(Arg)> {
        using argument_type = Arg;
    };

    template <typename F>
    struct callable_traits : callable_traits<decltype(&F::operator())> {};

    class event {
    public:
        using SubscriptionToken = std::uint64_t;
        template<typename T>
        using listener_t = std::function<void(T&)>;
        template<typename T>
        struct ListenerContainer {
            struct ListenerEntry {
                SubscriptionToken token;
                std::function<void(T&)> callback;
                void* instance = nullptr;
                void* memberFunction = nullptr;
            };
            std::vector<ListenerEntry> listeners;
            SubscriptionToken nextToken = 1;
        };
        template <typename T>
        static void dispatch(T& eventObj) {
            auto listenersCopy = getListenerContainer<T>().listeners;
            for (const auto& entry : listenersCopy) {
                entry.callback(eventObj);
            }
        }
        template <typename T>
        static void dispatch() {
            T eventObj{};
            dispatch<T>(eventObj);
        }
        template <typename T>
        static SubscriptionToken subscribe(std::function<void(T&)> listener) {
            auto& container = getListenerContainer<T>();
            SubscriptionToken token = container.nextToken++;
            typename ListenerContainer<T>::ListenerEntry entry;
            entry.token = token;
            entry.callback = std::move(listener);
            entry.instance = nullptr;
            entry.memberFunction = nullptr;
            container.listeners.push_back(std::move(entry));
            return token;
        }
        template <typename Func>
        static SubscriptionToken subscribe(Func listener) {
            using raw_event_type = typename callable_traits<Func>::argument_type;
            using event_type = std::remove_reference_t<raw_event_type>;
            return subscribe<event_type>(listener_t<event_type>{listener});
        }
        template <typename T, typename C>
        static SubscriptionToken subscribe(void (C::* listener)(T&), C* instance) {
            auto& container = getListenerContainer<T>();
            SubscriptionToken token = container.nextToken++;
            typename ListenerContainer<T>::ListenerEntry entry;
            entry.token = token;
            entry.callback = [instance, listener](T& eventObj) {
                (instance->*listener)(eventObj);
                };
            entry.instance = static_cast<void*>(instance);
            entry.memberFunction = *reinterpret_cast<void**>(&listener);
            container.listeners.push_back(std::move(entry));
            return token;
        }
        template <typename T>
        static void unsubscribe(const std::function<void(T&)>& listener) {
            auto& entries = getListenerContainer<T>().listeners;
            for (auto it = entries.begin(); it != entries.end(); ++it) {
                if (it->instance != nullptr)
                    continue;
                if (it->callback.target_type() != listener.target_type())
                    continue;
                if (auto ptr1 = it->callback.template target<void(*)(T&)>()) {
                    if (auto ptr2 = listener.template target<void(*)(T&)>()) {
                        if (*ptr1 == *ptr2) {
                            entries.erase(it);
                            return;
                        }
                    }
                }
                if (it->callback.target<void>() == listener.target<void>()) {
                    entries.erase(it);
                    return;
                }
            }
        }
        template <typename T, typename Func>
        static void unsubscribe(Func listener) {
            unsubscribe<T>(listener_t<T>{listener});
        }
        template <typename T, typename C>
        static void unsubscribe(void (C::* listener)(T&), C* instance) {
            auto& entries = getListenerContainer<T>().listeners;
            void* targetInstance = static_cast<void*>(instance);
            void* targetMemberFunc = *reinterpret_cast<void**>(&listener);
            for (auto it = entries.begin(); it != entries.end(); ++it) {
                if (it->instance == targetInstance && it->memberFunction == targetMemberFunc) {
                    entries.erase(it);
                    return;
                }
            }
        }
    private:
        template<typename T>
        static ListenerContainer<T>& getListenerContainer() {
            static ListenerContainer<T> container;
            return container;
        }
    };

}
