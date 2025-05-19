#pragma once
#include <memory>
#include <format>
#include <chrono>
#include <cpp-i18n/Translator.hpp>

#include "event/event.hpp"
#include "io/io.hpp"
#include "feature/feature_manager.hpp"
#include "hook/hook_manager.hpp"

#include "symbol/map.hpp"

#ifdef SELAURA_WINDOWS
#include <winrt/base.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>
#endif

namespace selaura {
	class instance : public selaura::listener {
	public:
		void start();
		void shutdown();

		static instance& get();
	private:
		i18n::Translator translator;
		std::unique_ptr<selaura::resolver> resolver;
		std::unique_ptr<selaura::io> io;
		std::unique_ptr<selaura::feature_manager> feature_manager;
		std::unique_ptr<selaura::hook_manager> hook_manager;
	};
};