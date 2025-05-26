#include "uuid.hpp"
#include <iomanip>
#include <sstream>

namespace bedrock {
	namespace mce {
        UUID UUID::EMPTY{};

        std::string UUID::asString() const
        {
            std::ostringstream oss;
            oss << std::hex << std::setfill('0');
            oss << std::setw(8) << (data[0] >> 32 & 0xFFFFFFFF);
            oss << '-';
            oss << std::setw(4) << (data[0] >> 16 & 0xFFFF);
            oss << '-';
            oss << std::setw(4) << (data[0] & 0xFFFF);
            oss << '-';
            oss << std::setw(4) << (data[1] >> 48 & 0xFFFF);
            oss << '-';
            oss << std::setw(12) << (data[1] & 0xFFFFFFFFFFFF);
            return oss.str();
        }
	};
};