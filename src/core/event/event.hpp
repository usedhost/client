#pragma once

#include <entt/entt.hpp>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>

namespace selaura::detail {

	struct listener {
		virtual ~listener() = default;
	};

	class dispatcher {
	public:
		template <typename Event>
		void dispatch(const Event& ev) {
			get_signal<Event>().publish(ev);
		}

		template <typename Event, typename Receiver>
		entt::connection subscribe(Receiver& object, void (Receiver::* method)(const Event&)) {
			auto conn = get_sink<Event>().template connect<method>(object);
			store_connection<Event>(conn, &object);
			return conn;
		}

		template <typename Event, typename Func>
		entt::connection subscribe(Func&& fn, const void* owner = nullptr) {
			auto conn = get_sink<Event>().connect(std::forward<Func>(fn));
			if (owner) {
				store_connection<Event>(conn, owner);
			}
			return conn;
		}

		template <typename Event>
		void unsubscribeAll() {
			get_signal<Event>().disconnect();
			connections[typeid(Event)].clear();
		}

		template <typename Event>
		void unsubscribe(const void* owner) {
			auto& conns = connections[typeid(Event)];
			for (auto it = conns.begin(); it != conns.end();) {
				if (it->first == owner) {
					it->second.disconnect();
					it = conns.erase(it);
				}
				else {
					++it;
				}
			}
		}

	private:
		template <typename Event>
		entt::sigh<Event>& get_signal() {
			std::type_index type = typeid(Event);
			if (!signals.contains(type)) {
				signals[type] = std::make_unique<entt::sigh<Event>>();
			}
			return *static_cast<entt::sigh<Event>*>(signals[type].get());
		}

		template <typename Event>
		entt::sink<entt::sigh<Event>> get_sink() {
			return entt::sink{ get_signal<Event>() };
		}

		template <typename Event>
		void store_connection(entt::connection conn, const void* owner) {
			connections[typeid(Event)].emplace_back(owner, std::move(conn));
		}

		std::unordered_map<std::type_index, std::unique_ptr<void>> signals;
		std::unordered_map<std::type_index, std::vector<std::pair<const void*, entt::connection>>> connections;
	};

}
