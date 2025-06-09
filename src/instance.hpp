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

#include "sdk/signatures.hpp"
#include "event/event_manager.hpp"
#include "hook/hook_manager.hpp"
#include "renderer/renderer.hpp"
#include "input/input_manager.hpp"
#include "feature/feature_manager.hpp"
#include "screen/screen_manager.hpp"
#include "scripting/script_manager.hpp"

#include "sdk/mc/game/MinecraftGame.hpp"

namespace selaura {
	struct instance : public std::enable_shared_from_this<instance> {
		using components_t = std::tuple<
			event_manager,
			hook_manager,
			renderer,
			input_manager,
			feature_manager,
			screen_manager,
			script_manager
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
}