#include "resolver.hpp"

namespace selaura {
    std::optional<uintptr_t> resolver::signature(std::string_view sig) {
        static selaura::detail::process_module game = selaura::detail::get_module_handle();

        const auto parsed = hat::parse_signature(sig);
        const auto result = hat::find_pattern(game.base, game.base + game.size, parsed.value());

        if (!result.has_result()) return std::nullopt;
        return reinterpret_cast<uintptr_t>(result.get());
	};
};