#include "selaura.hpp"

std::unique_ptr<selaura> selaura::instance;
std::once_flag selaura::init_flag;

selaura::selaura(std::span<std::byte> bytes) {
	this->game_bytes = bytes;	
}

void selaura::init(std::span<std::byte> bytes) {
	std::call_once(init_flag, [&] {
		instance = std::unique_ptr<selaura>(new selaura(bytes));
	});
}

std::unique_ptr<selaura> selaura::get() {
	if (!instance)
		throw std::runtime_error("selaura not initialized");
	return instance;
}

std::optional<uintptr_t> selaura::find_pattern(std::string_view signature) {
	const auto parsed = hat::parse_signature(signature);
	if (!parsed.has_value()) {
		throw std::runtime_error(std::format("Invalid signature: {}", signature));
	}

	const auto result = hat::find_pattern(instance->game_bytes.begin(), instance->game_bytes.end(), parsed.value());

	if (!result.has_result()) return std::nullopt;
	return reinterpret_cast<uintptr_t>(result.get());
}
