#include "selaura.hpp"

selaura::selaura(std::span<std::byte> bytes) : game_bytes(bytes) {
	
}

std::optional<uintptr_t> selaura::find_pattern(std::string_view pattern) {
	const auto parsed = hat::parse_signature(signature);
	if (!parsed.has_value()) {
		throw std::runtime_error(std::format("Invalid signature: {}", signature));
	}

	const auto result = hat::find_pattern(this->game_bytes.begin(), this->game_bytes.end(), parsed.value());

	if (!result.has_result()) return std::nullopt;
	return reinterpret_cast<uintptr_t>(result.get());
};

selaura*& selaura::instance_ptr() {
	static selaura* instance = nullptr;
	return instance;
}

void selaura::init(std::span<std::byte> bytes) {
	auto*& inst = instance_ptr();
	if (inst != nullptr)
		throw std::runtime_error("selaura already initialized");

	inst = new selaura(bytes);
}

selaura& selaura::get() {
	auto* inst = instance_ptr();
	if (!inst)
		throw std::runtime_error("selaura not initialized");
	return *inst;
}
