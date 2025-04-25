#pragma once

#include "client/types.hpp"
#include "client/instance.hpp"

#include <string>
#include <memory>

namespace selaura {
	extern std::unique_ptr<selaura::instance> inst;

	void init();
};