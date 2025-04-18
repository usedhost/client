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
#include <mutex>

#ifdef _WIN32
#include <winrt/base.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>
#endif

#include "memory/memory_handler.hpp"
#include <safetyhook.hpp>

class selaura {
public:
	explicit selaura();

	static void init();
	static selaura& get();

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
	std::span<std::byte> game_bytes;
	std::unordered_map<std::type_index, std::unique_ptr<void, void(*)(void*)>> services;

	template<typename T>
	static void deleter(void* ptr) {
		delete static_cast<T*>(ptr);
	}

	static std::unique_ptr<selaura> instance;
	static std::once_flag init_flag;
};
