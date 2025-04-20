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
		"48 83 EC 28 80 B9 C8 18 00 00 00 48 8D 54 24 30 48 8B 01 48 8B 40 60 74 38 41 B8 1A"
	});
	hook = safetyhook::create_inline(sig.value(), +[](void* a1) -> float {
		return 25;
	});
}

event_handler::dispatcher& selaura::get_dispatcher() {
	return this->dispatcher;
};