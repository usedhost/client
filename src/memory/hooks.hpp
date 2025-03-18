#pragma once
#include <minhook/minhook.h>
#include <kiero/kiero.h>
#include "scanner/scanner.hpp"

#include "hooks/swapchain.hpp"
#include "hooks/screenview.hpp"

namespace selaura_hooks {
	void initialize();
	void shutdown();
};