#pragma once
#include <span>
#include <memory>
#include <string>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include <libhat/scanner.hpp>

class memory_handler {
public:
	static void init(std::span<std::byte> mem);

	static std::optional<uintptr_t> find_pattern(std::string_view pattern);
	static std::optional<uintptr_t> find_patterns(const std::vector<std::string_view>& patterns);
private:
	static std::span<std::byte> mem;
};