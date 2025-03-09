#pragma once

#include <format>
#include <string>
#include <utility>
#include <fstream>
#include <chrono>
#include <ctime>
#include <shlobj.h>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

namespace logger {
	void write(const std::string& message);
	void clear();

	template<typename... Args>
	void info(const std::string& fmt, Args&&... args) {
		const std::string message = fmt::vformat(fmt, fmt::make_format_args(args...));
		write("[INFO] " + message);
	}

	template<typename... Args>
	void warn(const std::string& fmt, Args&&... args) {
		const std::string message = fmt::vformat(fmt, fmt::make_format_args(args...));
		write("[WARN] " + message);
	}

	template<typename... Args>
	void error(const std::string& fmt, Args&&... args) {
		const std::string message = fmt::vformat(fmt, fmt::make_format_args(args...));
		write("[ERROR] " + message);
	}

	template<typename... Args>
	void debug(const std::string& fmt, Args&&... args) {
		#ifdef _DEBUG
			const std::string message = fmt::vformat(fmt, fmt::make_format_args(args...));
			write("[DEBUG] " + message);
		#endif
	}

};