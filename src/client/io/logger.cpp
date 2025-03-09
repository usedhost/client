#include "logger.hpp"

void logger::write(const std::string& message) {
    char* localAppData = nullptr;
    size_t len = 0;
    std::string path;

    if (_dupenv_s(&localAppData, &len, "APPDATA") == 0 && localAppData) {
        path = std::string(localAppData) +
            "\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Selaura";

        CreateDirectoryA(path.c_str(), nullptr);

        free(localAppData);
    }

    std::ofstream out(path + "\\logs.txt", std::ios::app);

    if (out.is_open()) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm timeInfo;
        localtime_s(&timeInfo, &now_c);

        std::ostringstream timestamp;
        timestamp << "[" << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S") << "] ";

        out << timestamp.str() << message << std::endl;
        out.close();
    }
}

void logger::clear() {
    char* localAppData = nullptr;
    size_t len = 0;
    std::string path;

    if (_dupenv_s(&localAppData, &len, "APPDATA") == 0 && localAppData) {
        path = std::string(localAppData) +
            "\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Selaura";

        CreateDirectoryA(path.c_str(), nullptr);

        free(localAppData);
    }


    std::ofstream out = std::ofstream(path + "\\logs.txt");

    if (out.is_open()) {
        out.clear();
        out.close();
    }
}