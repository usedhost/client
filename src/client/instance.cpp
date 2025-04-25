#include "instance.hpp"

namespace selaura {
	void instance::func(test& ev) {

	}
	void instance::start() {
		//this->dispatcher = std::make_unique<selaura::detail::dispatcher>();
		
		// use hat::process::get_module as its crossplatform now!
		i18n::LocaleConfig config;
		this->translator = i18n::Translator(config);

		this->subscribe<test, &instance::func>();

		test ev( 1 );
		selaura::core::dispatcher<test>::dispatch(ev);
	}
};