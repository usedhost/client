#pragma once
#include <memory>

#if _WIN32
    #define SELAURA_API __declspec(dllexport)
#elif defined(__linux__)
    #define SELAURA_API __attribute__((visibility("default")))
#else
    #define SELAURA_API
#endif

#include "runtime.hpp"

namespace selaura {
    struct plugin_version {
        int major, minor, patch;
    };
    struct plugin {
        virtual ~plugin() = default;

        virtual void on_load(class std::shared_ptr<selaura::runtime> runtime) = 0;

        virtual const char* name() const final { return _name; }
        virtual const char* description() const final { return _desc; }
        virtual const char* author() const final { return _author; }
        virtual plugin_version version() const final { return _version; }

        const char* _name = "Unnamed Mod";
        const char* _desc = "No description";
        const char* _author = "Unknown";
        plugin_version _version = {0, 0, 1};
    };
};