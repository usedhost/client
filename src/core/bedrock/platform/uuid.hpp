#pragma once

#include <cstdint>
#include <string>

namespace selaura::bedrock {
	namespace mce {
        class UUID {
        public:
            static UUID EMPTY;
            UUID() = default;
            [[nodiscard]] std::string asString() const;

            std::int64_t data[2]{ 0, 0 };
        };
	}
};