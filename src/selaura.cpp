#include "selaura.hpp"

namespace selaura {
	std::unique_ptr<instance> instance;

	bool init() {
		instance = std::make_unique<instance>();
		instance->start();
		return true;
	}

	void shutdown() {
		instance->shutdown();
	}
}
