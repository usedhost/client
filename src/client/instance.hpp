#pragma once
#include <memory>
#include "../core/event/event.hpp"

namespace selaura {
	class instance {
	public:
		void start();
		void shutdown();
	private:
		std::unique_ptr<selaura::detail::dispatcher> dispatcher;
	};
};