#include "instance.hpp"

#include "plugins/plugin.hpp"
#include "plugins/runtime.hpp"

namespace selaura {
    std::shared_ptr<selaura::instance> inst;

    bool instance::start() {
        if (auto self = shared_from_this(); self) {
            selaura::inst = self;
        }
        else {
            throw std::runtime_error("selaura::instance must be managed by an std::shared_ptr");
        }

        return true;
    }

    void instance::init() {
        auto log_file = selaura::platform::get_data_folder() / "logs.txt";

        auto logger = spdlog::basic_logger_mt("selaura", log_file.string(), true);
        logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
        logger->set_level(spdlog::level::debug);
        logger->flush_on(spdlog::level::debug);

        spdlog::set_default_logger(logger);

        std::filesystem::path mods_path = selaura::platform::get_data_folder() / "mods";

        if (!std::filesystem::exists(mods_path)) {
            std::filesystem::create_directory(mods_path);
        } else {
            this->runtime = std::make_shared<selaura::runtime>();
            selaura::runtime_link(this->runtime);

            for (const auto& entry : std::filesystem::directory_iterator(mods_path)) {
                if (!entry.is_regular_file() || (entry.path().extension() != ".dll" && entry.path().extension() != ".so")) continue;

                auto mod = selaura::platform::load_plugin(entry.path());
                mod->on_load(this->runtime);
                spdlog::info("Loaded mod: {}, version: {}.{}.{}", mod->_name, mod->_version.major, mod->_version.minor, mod->_version.patch);
            }
        }

        selaura::platform::set_title(fmt::runtime("Selaura Client {}"), CLIENT_VERSION);
    }

    std::shared_ptr<selaura::instance> get() {
        return selaura::inst;
    }
};