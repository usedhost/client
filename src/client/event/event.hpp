#pragma once

#include <entt/entt.hpp>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>
#include <functional>
#include <mutex>

namespace selaura::core {
	template <class T>
	class dispatcher {
	public:
		static void dispatch(T& ev) {
			std::scoped_lock lock(mutex());
			signal().publish(ev);
		}

		static entt::sink& get_sink() {
			std::scoped_lock lock(mutex());
			return sink();
		}

	private:
		static entt::sigh<void(T&)>& signal() {
			static entt::sigh<void(T&)> sig;
			return sig;
		}

		static entt::sink& sink() {
			static entt::sink s{ signal() };
			return s;
		}

		static std::mutex& mutex() {
			static std::mutex m;
			return m;
		}
	};

	class listener {
	public:
		template <class event, auto callback, typename Self>
		void subscribe(Self& self) {
			std::scoped_lock lock(dispatcher<event>::mutex());
			dispatcher<event>::get_sink().template connect<callback>(self);
		}

		template <class event, auto callback, typename Self>
		void unsubscribe(Self& self) {
			std::scoped_lock lock(dispatcher<event>::mutex());
			dispatcher<event>::get_sink().template disconnect<callback>(self);
		}
	};
}
