#pragma once

#include "../../include/entt/entt.hpp"
#include "../../include/magic_enum/magic_enum.hpp"
#include <type_traits>
#include <thread>

#include "io/logger.hpp"
#include "platform_backend.hpp"

class selaura {
public:
    static selaura& get();

    template <typename System, typename... Args>
    System& add_system(Args&&... args) {
        return registry.ctx().emplace<System>(std::forward<Args>(args)...);
    }

    template <typename System>
    System& get_system() {
        return registry.ctx().get<System>();
    }

    template <typename handle>
    void init(handle _handle) {
        static_assert(std::is_convertible<handle, module_handle_t>::value,
            "Provided handle must be convertible to the platform's module handle type");
        auto& backend = add_system<platform_backend>();
        backend.init(static_cast<module_handle_t>(_handle));

        logger::clear();
        logger::info("Initializing Selaura Client");

        backend.run_async([&]() {
            std::string backend_debug = "";
#if SELAURA_WIN32
            backend_debug = (backend.debug) ? "/Debug" : "/Release";
            backend.set_title("Selaura Client (Windows{}) - {}", backend_debug, "Version Soon");
#elif SELAURA_LINUX
			backend_debug = (backend.debug) ? "Debug" : "Release";
			backend.set_title("Selaura Client (Linux{}) - {}", backend_debug, "Version Soon");
#endif
        });
    }

    void shutdown() {
        logger::info("Shutting down Selaura Client.");
        get_system<platform_backend>().shutdown();
    }

private:
    selaura() = default;
    ~selaura() = default;
    selaura(const selaura&) = delete;
    selaura& operator=(const selaura&) = delete;

	entt::registry registry;
};
