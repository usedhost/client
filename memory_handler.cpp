#include "memory_handler.hpp"

std::span<std::byte> memory_handler::mem = {};

void memory_handler::init(std::span<std::byte> bytes) {
	memory_handler::mem = bytes;
}

std::optional<uintptr_t> memory_handler::find_pattern(std::string_view signature) {
	const auto parsed = hat::parse_signature(signature);
	if (!parsed.has_value()) {
		throw std::runtime_error(fmt::format("Invalid signature: {}", signature));
	}

	const auto result = hat::find_pattern(memory_handler::mem.begin(), memory_handler::mem.end(), parsed.value());

	if (!result.has_result()) return std::nullopt;
	return reinterpret_cast<uintptr_t>(result.get());
}

std::optional<uintptr_t> memory_handler::find_patterns(const std::vector<std::string_view>& patterns) {
	for (const auto& pattern : patterns) {
		auto result = find_pattern(pattern);
		if (result.has_value()) {
			return result;
		}
	}
	return std::nullopt;
}

std::optional<hook_info*> memory_handler::get_hook(const std::string& name) {
	auto it = hooks.find(name);
	if (it != hooks.end()) {
		return &it->second;
	}
	return std::nullopt;
}

bool memory_handler::remove_hook(const std::string& name) {
	auto it = hooks.find(name);
	if (it == hooks.end())
		return false;

	if (it->second.remover)
		it->second.remover();

	hooks.erase(it);
	return true;
}
