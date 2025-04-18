#pragma once
#include <span>
#include <memory>
#include <unordered_map>
#include <string>

#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <safetyhook.hpp>

#include <libhat/scanner.hpp>

class memory_handler {
public:
	static void init(std::span<std::byte> mem);

	static std::optional<uintptr_t> find_pattern(std::string_view pattern);
	static std::optional<uintptr_t> find_patterns(const std::vector<std::string_view>& patterns);

	static void add_hook(std::string name, SafetyHookInline hook);
private:
	static std::span<std::byte> mem;
	static std::unordered_map<std::string, SafetyHookInline> hooks;
};