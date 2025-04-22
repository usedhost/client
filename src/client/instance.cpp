#include "instance.hpp"

namespace selaura {
	void instance::func(test& ev) {

	}
	void instance::start() {
		//this->dispatcher = std::make_unique<selaura::detail::dispatcher>();
		
		this->subscribe<test, &instance::func>();

		test ev( 1 );
		selaura::core::dispatcher<test>::dispatch(ev);
	}
};