#include "instance.hpp"

namespace selaura {
	void instance::start() {
		this->logger = std::make_unique<selaura::detail::logger>();
		//this->dispatcher = std::make_unique<selaura::detail::dispatcher>();
		
		//this->logger->info("hii {}", 2);
	}
};