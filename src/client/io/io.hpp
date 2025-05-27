#pragma once
#include <filesystem>
#include <fstream>
#include <format>
#include <chrono>
#include <ctime>

namespace selaura {
	class io {
	public:
		std::filesystem::path data_folder;
		std::filesystem::path log_file;
		std::ofstream log_stream;

		void init() {
#ifdef SELAURA_WINDOWS
			char* localAppData = nullptr;
			size_t size = 0;
			_dupenv_s(&localAppData, &size, "APPDATA");
			if (localAppData) {
				data_folder = std::filesystem::path(localAppData + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Selaura"));
			}
#elif defined(SELAURA_LINUX)
			data_folder = "/data/data/com.mojang.minecraftpe/Selaura";
#elif defined(SELAURA_ANDROID)
			data_folder = "/data/data/com.selauraclient.launcher/Selaura";
#endif
			log_file = data_folder / "logs.txt";
			std::filesystem::create_directories(data_folder);
			log_stream.open(log_file, std::ios::trunc);
		}

		void shutdown() {
			if (log_stream.is_open()) log_stream.close();
		}

		template<typename... Args>
		void info(std::format_string<Args...> fmt, Args&&... args) {
			log("INFO", std::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		void warn(std::format_string<Args...> fmt, Args&&... args) {
			log("WARN", std::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		void error(std::format_string<Args...> fmt, Args&&... args) {
			log("ERROR", std::format(fmt, std::forward<Args>(args)...));
		}

	private:
		void log(const std::string& level, const std::string& msg) {
			if (!log_stream.is_open()) return;

			auto now = std::chrono::system_clock::now();
			auto time_t_now = std::chrono::system_clock::to_time_t(now);
			auto local_tm = std::localtime(&time_t_now);

			char timestamp[20];
			std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", local_tm);

			log_stream << std::format("[{}] [{}] {}\n", timestamp, level, msg);
			log_stream.flush();
		}
	};
}
