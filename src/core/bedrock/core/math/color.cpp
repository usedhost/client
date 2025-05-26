#include "color.hpp"

#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>

namespace bedrock {
    std::string mce::Color::toHexString() const
    {
        std::stringstream stream;
        stream << "#" << std::setfill('0') << std::hex       //
            << std::setw(2) << static_cast<int>(r * 255)  //
            << std::setw(2) << static_cast<int>(g * 255)  //
            << std::setw(2) << static_cast<int>(b * 255)  //
            << std::setw(2) << static_cast<int>(a * 255);
        return stream.str();
    }

    mce::Color mce::Color::fromHexString(const std::string& hex_string)
    {
        Color color{};
        if (hex_string.length() != 8) {
            return color;
        }

        const auto value = std::strtoul(hex_string.c_str(), nullptr, 16);
        color.r = static_cast<float>((value >> 24) & 0xFF) / 255.0F;
        color.g = static_cast<float>((value >> 16) & 0xFF) / 255.0F;
        color.b = static_cast<float>((value >> 8) & 0xFF) / 255.0F;
        color.a = static_cast<float>(value & 0xFF) / 255.0F;
        return color;
    }
}