#pragma once
#include <memory>
#include <filesystem>
#include <cpp-i18n/Translator.hpp>

#include "event/event.hpp"
#include "io/logger.hpp"
#include "feature/feature_manager.hpp"

#include "symbol/resolver.hpp"

namespace selaura {
	class instance : public selaura::listener {
	public:
		void start();
		void shutdown();
	private:
		i18n::Translator translator;
		std::unique_ptr<selaura::logger> logger;
		std::unique_ptr<selaura::feature_manager> feature_manager;

		std::filesystem::path data_folder;
	};
};