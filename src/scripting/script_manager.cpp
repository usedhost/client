#include "script_manager.hpp"
#include "../instance.hpp"

namespace selaura {
	void script_manager::init() {
		auto inst = selaura::instance::get();
		this->data_folder = inst->get_data_folder() / "scripts";
		auto log_file = inst->get_data_folder() / "logs.txt";

		this->logger = spdlog::basic_logger_mt("selaura scripting", log_file.string(), true);
		this->logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] [Scripting] %v");
		this->logger->set_level(spdlog::level::debug);
		this->logger->flush_on(spdlog::level::debug);

		int scriptsLoaded = 0;
		if (!std::filesystem::exists(this->data_folder) || std::filesystem::is_empty(this->data_folder)) {
			std::filesystem::create_directory(this->data_folder);
		}
		else {
			for (const auto& entry : std::filesystem::directory_iterator(this->data_folder)) {
				if (entry.is_regular_file() && entry.path().extension() == ".lua") { // todo: find what language we're going to use for scripting
					scriptsLoaded++;
					this->logger->info("Loading script: {}", entry.path().filename().string());
				}
			}
		}

		this->logger->info("{} scripts loaded.", scriptsLoaded);
	}
};