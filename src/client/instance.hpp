#pragma once
#include <memory>
#include "../core/event/event.hpp"
#include "../core/io/logger.hpp"

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
		//std::unique_ptr<selaura::detail::logger> logger;
	};
};