#pragma once

#include <entt/entt.hpp>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>
#include <functional>

namespace selaura {
	template <class T>
	class dispatcher {
	public:
		static inline entt::sigh<void(T&)> signal;
		static inline entt::sink sink{ signal };

		static void dispatch(T& ev) {
			dispatcher<T>::signal.publish(ev);
		}
	};

	class listener {
	public:
		template <class event, auto callback, typename Self> void subscribe(this Self& self) {
			selaura::dispatcher<event>::sink.template connect<callback>(self);
		}

		template <class event, auto callback, typename Self> void unsubscribe(this Self& self) {
			selaura::dispatcher<event>::sink.template disconnect<callback>(self);
		}

	};
}