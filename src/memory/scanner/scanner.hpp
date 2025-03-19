#pragma once
#include <memory>
#include <optional>
#include <vector>
#include <Windows.h>
#include <Psapi.h>

#include "../../client/io/logger.hpp"

namespace selaura_memory {
    uintptr_t find_pattern(const char* signature);

    template <typename T>
    T member_at(void* base, size_t offset) {
        return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(base) + offset);
    }
};