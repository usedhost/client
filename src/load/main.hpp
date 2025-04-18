#pragma once

#if defined(__unix__) || defined(__APPLE__)
//#if !defined(__ANDROID__)
#define PLATFORM_LINUX
//#endif
#endif

#include <thread>
#include <span>
#include <cstddef>
#include "../selaura.hpp"
#include "../memory/memory_handler.hpp"

#ifdef _WIN32
#include <Windows.h>
#include <Psapi.h>
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved);
#endif

#ifdef PLATFORM_LINUX
#include <dlfcn.h>
#include <link.h>

struct MenuEntryABI {
    const char* name;
    void* user = nullptr;
    bool (*selected)(void* user) = [](void*) { return false; };
    void (*click)(void* user) = nullptr;
    size_t        length = 0;
    MenuEntryABI* subentries = nullptr;
};

struct ControlABI {
    int type = 0; // button
    union {
        struct {
            const char* label;
            void* user;
            void (*onClick)(void* user);
        } button;

        struct {
            const char* label;
            int         min;
            int         def;
            int         max;
            void* user;
            void (*onChange)(void* user, int value);
        } sliderint;

        struct {
            const char* label;
            float       min;
            float       def;
            float       max;
            void* user;
            void (*onChange)(void* user, float value);
        } sliderfloat;

        struct {
            const char* label;
            int         size; // 0 normal, 1 small title...
        } text;

        struct {
            const char* label;
            const char* def;
            const char* placeholder;
            void* user;
            void (*onChange)(void* user, const char* value);
        } textinput;
    } data;
};

inline void* g_window;

inline void* (*getPrimaryWindow)();
inline bool (*isMouseLocked)(void* handle);
inline void (*addKeyboardCallback)(void* handle, void* user, bool (*callback)(void* user, int keyCode, int action));
inline bool (*addMouseButtonCallback)(void* handle, void* user, bool (*hook)(void* user, double x, double y, int button, int action));
inline bool (*addMousePositionCallback)(void* handle, void* user, bool (*hook)(void* user, double x, double y, bool relative));
inline void (*addMouseScrollCallback)(void* handle, void* user, bool (*callback)(void* user, double x, double y, double dx, double dy));
inline void (*addWindowCreationCallback)(void* user, void (*onCreated)(void* user));
inline void (*addMenu)(size_t length, MenuEntryABI* entries);
inline void (*showWindow)(const char* title, int isModal, void* user, void (*onClose)(void* user), int count, ControlABI* controls);
inline void (*closeWindow)(const char* title);

extern "C" [[gnu::visibility("default")]] void mod_preinit();
extern "C" [[gnu::visibility("default")]] void mod_init();
#endif
