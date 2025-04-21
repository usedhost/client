#pragma once

#include <memory>

namespace selaura::detail {
	struct version_format {
		int max;
		int min;
		int build;
		int revision;
	};
};