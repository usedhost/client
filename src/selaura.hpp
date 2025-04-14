#pragma once

#include <thread>
#include <span>
#include <cstddef>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <optional>
#include <string>
#include <format>
#include <mutex>

#include <libhat/scanner.hpp>

class selaura {
public:
	static void init(std::span<std::byte> bytes);
	static selaura& get();

	static std::optional<uintptr_t> find_pattern(std::string_view pattern);

	template <typename T>
	static T& get_service() {
		auto& inst = get();
		auto it = inst.services.find(std::type_index(typeid(T)));
		if (it == inst.services.end())
			throw std::runtime_error("Service not registered");
		return *static_cast<T*>(it->second.get());
	}

	template <typename T, typename... Args>
	void register_service(Args&&... args) {
		auto ptr = new T(std::forward<Args>(args)...);
		services[std::type_index(typeid(T))] = {
			ptr,
			&deleter<T>
		};
	}

	std::span<std::byte> get_bytes() const { return game_bytes; }

private:
	explicit selaura(std::span<std::byte> bytes);

	std::span<std::byte> game_bytes;
	std::unordered_map<std::type_index, std::unique_ptr<void, void(*)(void*)>> services;

	template<typename T>
	static void deleter(void* ptr) {
		delete static_cast<T*>(ptr);
	}

	static std::unique_ptr<selaura> instance;
	static std::once_flag init_flag;
};
