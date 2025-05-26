#pragma once

#include <cstdint>
#include <string>
#include <iomanip>
#include <sstream>

namespace bedrock {
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