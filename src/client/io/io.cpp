#include "io.hpp"

namespace selaura {
	std::filesystem::path io::data_folder;
	std::filesystem::path io::log_file;
	std::ofstream io::log_stream;
}