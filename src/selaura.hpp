#pragma once

#include "client/types.hpp"
#include "client/instance.hpp"
#include "core/platform/windows.hpp"

#include <string>
#include <memory>

namespace selaura {
	extern std::unique_ptr<instance> instance;

	bool init();
	void shutdown();
};