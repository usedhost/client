#pragma once
#include <memory>
#include <cpp-i18n/Translator.hpp>

#include "event/event.hpp"
#include "io/io.hpp"
#include "feature/feature_manager.hpp"
#include "hook/hook.hpp"

#include "symbol/resolver.hpp"

namespace selaura {
	class instance : public selaura::listener {
	public:
		void start();
		void shutdown();
	private:
		i18n::Translator translator;
		std::unique_ptr<selaura::io> io;
		std::unique_ptr<selaura::feature_manager> feature_manager;
	};
};