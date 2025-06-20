#pragma once
#include "process.hpp"
#include <spdlog/spdlog.h>

namespace selaura {
    inline std::optional<uintptr_t> find_pattern(std::string_view pattern) {
        const auto parsed = hat::parse_signature(pattern);
        if (!parsed.has_value()) {
            spdlog::error("Invalid signature! {:s}", pattern);
            return std::nullopt;
        }

        static auto process = selaura::get_handle();

        const auto begin = process.base;
        const auto end = begin + process.size;
        const auto result = hat::find_pattern(begin, end, parsed.value());

        if (!result.has_result()) {
            return std::nullopt;
        }
        return reinterpret_cast<uintptr_t>(result.get());
    }

    inline uintptr_t offset_from_sig(uintptr_t sig, int offset) {
        if (sig == 0) return 0;
        return sig + offset + 4 + *reinterpret_cast<int*>(sig + offset);
    }

    template<typename Ret>
    inline Ret offset_from_sig(const uintptr_t sig, const int offset) {
        return reinterpret_cast<Ret>(offset_from_sig(sig, offset));
    }
};