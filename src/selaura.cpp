#include "selaura.hpp"

alignas(selaura) char selauraBuffer[sizeof(selaura)];
SafetyHookInline hook;

selaura& selaura::get() {
	return *std::launder(reinterpret_cast<selaura*>(selauraBuffer));
}

struct Test {
	float number;
};

selaura::selaura() {
	static auto sig = memory_handler::find_pattern({
		"? ? ? ? ? ? ? 48 89 ? ? 57 48 81 EC ? ? ? ? 0F 29 ? ? 0F 29 ? ? 44 0F ? ? ? 44 0F ? ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? ? 41 0F"
	});
	memory_handler::add_hook("FOV", sig, +[](void* a1, float a2, void* a3, void* a4) -> float {
		return 30;
	});
}

event_handler::dispatcher& selaura::get_dispatcher() {
	return this->dispatcher;
};