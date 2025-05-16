#pragma once
#include <optional>

#include "module.hpp"

namespace selaura {
	class resolver {
	public:
		std::optional<uintptr_t> signature(std::string_view sig);
	};
};