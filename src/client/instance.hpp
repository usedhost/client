#pragma once
#include <memory>
#include <cpp-i18n/Translator.hpp>

#include "event/event.hpp"
#include "io/logger.hpp"

#include "symbol/resolver.hpp"

struct test {
	int d;
};

namespace selaura {
	class instance : public selaura::core::listener {
	public:
		void func(test& ev);

		void start();
		void shutdown();
	private:
		i18n::Translator translator;
		//std::unique_ptr<selaura::detail::logger> logger;
	};
};