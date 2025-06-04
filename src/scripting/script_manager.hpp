#pragma once
#include <filesystem>
#include <spdlog/spdlog.h>

namespace selaura {
	struct script_manager {
		void init();
	private:
		std::filesystem::path data_folder;
		std::shared_ptr<spdlog::logger> logger;
	};
}