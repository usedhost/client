#pragma once
#include <memory>
#include <optional>
#include <vector>
#include <Windows.h>
#include <Psapi.h>

#include "../../client/io/logger.hpp"

namespace selaura_memory {
    uintptr_t find_pattern(const char* signature);
};