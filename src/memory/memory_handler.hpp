#pragma once
#include <span>
#include <memory>
#include <unordered_map>
#include <string>
#include <optional>
#include <vector>
#include <bit>
#include <type_traits>
#include <utility>

#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <safetyhook.hpp>
#include <libhat/scanner.hpp>

struct hook_info {
	std::string name;
	uintptr_t address;
	safetyhook::InlineHook hook;

	std::function<void()> remover;
};

class memory_handler {
public:
	static void init(std::span<std::byte> mem);

	static std::optional<uintptr_t> find_pattern(std::string_view pattern);
	static std::optional<uintptr_t> find_patterns(const std::vector<std::string_view>& patterns);

	static std::optional<hook_info*> get_hook(const std::string& name);
	static bool remove_hook(const std::string& name);

	template <typename HookFn>
	static std::optional<hook_info*> add_hook(const std::string& name, std::optional<uintptr_t> pattern, HookFn&& fn) {
		if (hooks.contains(name))
			return std::nullopt;

		if (!pattern.has_value())
			return std::nullopt;

		auto hook = safetyhook::create_inline(pattern.value(), std::forward<HookFn>(fn));
		auto [it, _] = hooks.emplace(name, hook_info{
			.name = name,
			.address = pattern.value(),
			.hook = std::move(hook),
			});

		return &it->second;
	}

	template<typename Fn, typename Inst, typename... Args>
	static decltype(auto) call_member(Inst* instance, uintptr_t addr, Args&&... args) {
		using memfn_t = typename details::resolve_func<Fn>::template memfn_t<Inst>;
		const auto memfn = std::bit_cast<memfn_t>(addr);
		return (instance->*memfn)(std::forward<Args>(args)...);
	}

	template<size_t Index, typename Fn, typename Inst, typename... Args>
	static decltype(auto) call_virtual(Inst* instance, Args&&... args) {
		const auto vtable = *reinterpret_cast<uintptr_t* const*>(instance);
		return call_member<Fn>(instance, vtable[Index], std::forward<Args>(args)...);
	}

private:
	static std::span<std::byte> mem;
	static inline std::unordered_map<std::string, hook_info> hooks;

	struct details {
		template<typename>
		struct resolve_func;

		template<typename R, typename... Args>
		struct resolve_func<R(Args...)> {
			template<typename T>
			struct memfn : std::type_identity<R(T::*)(Args...)> {};

			template<typename T>
			struct memfn<const T> : std::type_identity<R(T::*)(Args...) const> {};

			template<typename T>
			using memfn_t = typename memfn<T>::type;
		};

		template<typename R, typename T, typename... Args>
		struct resolve_func<R(T::*)(Args...)> {
			template<typename>
			using memfn_t = R(T::*)(Args...);
		};

		template<typename R, typename T, typename... Args>
		struct resolve_func<R(T::*)(Args...) const> {
			template<typename>
			using memfn_t = R(T::*)(Args...) const;
		};
	};
};