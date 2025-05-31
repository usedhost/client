#pragma once
#include <memory>
#include <format>
#include <chrono>
#include <tuple>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>

#ifdef SELAURA_WINDOWS
#include <winrt/base.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>
#endif

#include "sdk/symbol.hpp"
#include "hook/hook_manager.hpp"

namespace selaura {
	struct instance : public std::enable_shared_from_this<instance> {
		using components_t = std::tuple<
			symbol,
			hook_manager
		>;

		bool start();
		void init();
		void shutdown();

		template<typename component>
		constexpr auto& get() {
			return std::get<component>(components);
		}

		const std::filesystem::path& get_data_folder();
		static std::shared_ptr<selaura::instance> get();
	private:
		components_t components{};
		std::filesystem::path data_folder;
	};
};