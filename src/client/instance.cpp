#include "instance.hpp"
#include "../core/hook/hook.hpp"
typedef float(__thiscall* getFovOriginal)(void*, float, void*, void*);
static inline getFovOriginal funcOriginal = nullptr;

float fov_hook(void* a1, void* a2, void* a3, void* a4) {
	return 30.f;
}

namespace selaura {
	void instance::func(test& ev) {

	}
	void instance::start() {
		//this->dispatcher = std::make_unique<selaura::detail::dispatcher>();
		
		// use hat::process::get_module as its crossplatform now!
		i18n::LocaleConfig config;
		this->translator = i18n::Translator(config);

		auto p = hat::parse_signature("? ? ? ? ? ? ? 48 89 ? ? 57 48 81 EC ? ? ? ? 0F 29 ? ? 0F 29 ? ? 44 0F ? ? ? 44 0F ? ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? ? 41 0F");
		auto re = hat::find_pattern(p.value(), ".text");
		uintptr_t reptr = reinterpret_cast<uintptr_t>(re.get());

		selaura::core::init_hooking();
		auto hook = selaura::core::hook((void*)reptr, (void*)fov_hook, (void**)&funcOriginal);
		hook.enable();

		this->subscribe<test, &instance::func>();

		test ev( 1 );
		selaura::core::dispatcher<test>::dispatch(ev);
	}
};
