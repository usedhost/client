#include "selaura.hpp"

std::unique_ptr<selaura> selaura::instance;
std::once_flag selaura::init_flag;

typedef float(__thiscall* jmp_time)(void* a1, void* a2, void* a3);
static inline jmp_time time_original = nullptr;
float hk_time(void* a1, void* a2, void* a3) {
	//float time = time_original(a1, a2, a3);
	return 0.f;
}

selaura::selaura(std::span<std::byte> bytes) {
	this->game_bytes = bytes;

	auto sig = selaura::find_pattern("? ? ? ? ? ? 76 05 F7 EA C1 FA 09 8B C2");
	DobbyHook((void*)sig.value(), (void*)hk_time, (void**)&time_original);
}

void selaura::init(std::span<std::byte> bytes) {
	std::call_once(init_flag, [&] {
		instance = std::make_unique<selaura>(bytes);
		});
}

selaura& selaura::get() {
	if (!instance)
		throw std::runtime_error("selaura not initialized");
	return *instance;
}

std::optional<uintptr_t> selaura::find_pattern(std::string_view signature) {
	const auto parsed = hat::parse_signature(signature);
	if (!parsed.has_value()) {
		throw std::runtime_error(fmt::format("Invalid signature: {}", signature));
	}

	const auto result = hat::find_pattern(instance->game_bytes.begin(), instance->game_bytes.end(), parsed.value());

	if (!result.has_result()) return std::nullopt;
	return reinterpret_cast<uintptr_t>(result.get());
}
