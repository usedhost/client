#pragma once
#include <filesystem>
#include <string>
#include <functional>

#if _WIN32
    #define SELAURA_API __declspec(dllexport)
#elif defined(__linux__)
    #define SELAURA_API __attribute__((visibility("default")))
#else
    #define SELAURA_API
#endif

struct selaura_mod_version {
    int major;
    int minor;
    int patch;
};

struct selaura_mod_info {
    const char* name;
    const char* description;
    selaura_mod_version version;
    const char* author;
};

struct selaura_runtime {
    selaura_runtime() = default;
    using log_fn = std::function<void(const char*)>;

    const char* name;
    const char* description;
    selaura_mod_version version;
    const char* author;

    log_fn info = nullptr;
    log_fn debug = nullptr;
    log_fn warn = nullptr;
    log_fn error = nullptr;

    selaura_mod_info ret_info(const char* name = "Unknown Mod Name", const char* description = "Unknown Mod Description", selaura_mod_version version = {0, 1, 0}, const char* author = "Author") {
        this->name = name;
        this->description = description;
        this->version = version;
        this->author = author;

        return {
            name,
            description,
            version,
            author
        };
    };
};