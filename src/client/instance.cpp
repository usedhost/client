#include "instance.hpp"
#include "../core/hook/hook.hpp"

namespace selaura {
	void instance::start() {
		this->logger = std::make_unique<selaura::logger>();
		selaura::init_hooking();

		/*
		
		i18n::LocaleConfig config;
		this->translator = i18n::Translator(config);

		auto p = hat::parse_signature("? ? ? ? ? ? ? 48 89 ? ? 57 48 81 EC ? ? ? ? 0F 29 ? ? 0F 29 ? ? 44 0F ? ? ? 44 0F ? ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? ? 41 0F");
		auto re = hat::find_pattern(p.value(), ".text");
		uintptr_t reptr = reinterpret_cast<uintptr_t>(re.get());

		auto hook = selaura::hook((void*)reptr, (void*)fov_hook, (void**)&funcOriginal);
		hook.enable();

		this->subscribe<test, &instance::func>();

		test ev( 1 );
		selaura::dispatcher<test>::dispatch(ev);
		*/
	}
};
