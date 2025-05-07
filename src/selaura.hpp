#pragma once

#include "client/types.hpp"
#include "client/instance.hpp"

#include <string>
#include <memory>
#include <mutex>

namespace selaura {
	extern std::unique_ptr<selaura::instance> inst;

	void init();
};
