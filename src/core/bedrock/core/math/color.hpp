#pragma once

#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>

namespace selaura::bedrock {
	namespace mce {
		class Color {
			[[nodiscard]] std::string toHexString() const;
			static Color fromHexString(const std::string& hex_string);

			float r;
			float g;
			float b;
			float a;
		};
	};
};