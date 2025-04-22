#pragma once
#include <memory>
//#include "../core/event/event.hpp"
#include "../core/io/logger.hpp"

namespace selaura {
	class instance {
	public:
		void start();
		void shutdown();
	private:
		//std::unique_ptr<selaura::detail::dispatcher> dispatcher;
		std::unique_ptr<selaura::detail::logger> logger;
	};
};