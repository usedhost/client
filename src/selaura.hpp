#pragma once

#include "client/types.hpp"
#include "client/instance.hpp"
#include "core/platform/windows.hpp"

#include <string>
#include <memory>

namespace selaura {
	detail::version_format version = { 1, 0, 0, 0 };
	std::string name = "Selaura Client";

	std::unique_ptr<selaura::instance> instance;

	bool init() {
		instance = std::make_unique<selaura::instance>();
		instance->start();
		return true;
	}

	void shutdown() {
		instance->shutdown();
	}
};