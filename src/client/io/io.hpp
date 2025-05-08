#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <chrono>
#include <format>

namespace selaura {
	struct io {
		std::filesystem::path data_folder;
		std::filesystem::path log_file;
		std::ofstream log_stream;

		io() {
#ifdef SELAURA_WINDOWS
			const char* localAppData = std::getenv("LOCALAPPDATA");
			if (localAppData) {
				data_folder = std::filesystem::path(localAppData) /
					"Packages/Microsoft.MinecraftUWP_8wekyb3d8bbwe/RoamingState/Selaura";
			}
#elif defined(SELAURA_LINUX)
			data_folder = "/data/data/com.mojang.minecraftpe/Selaura";
#else
			// android?
#endif
			log_file = data_folder / "logs.txt";
			std::filesystem::create_directories(data_folder);
			log_stream.open(log_file, std::ios::app);
		}

		~io() {
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

			using namespace std::chrono;
			auto now = zoned_time{ current_zone(), system_clock::now() };
			auto timestamp = std::format("{:%Y-%m-%d %H:%M:%S}", now);

			log_stream << std::format("[{}] [{}] {}\n", timestamp, level, msg);
			log_stream.flush();
		}
	};
}
