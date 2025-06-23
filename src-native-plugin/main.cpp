#include <../src-client/plugins/plugin_api.hpp>

extern "C" SELAURA_API selaura_mod_info SelauraRuntime_LoadModInfo(std::shared_ptr<selaura_runtime> runtime) {
    return runtime->ret_info("Selaura Example Mod");
}

extern "C" SELAURA_API void SelauraRuntime_LoadMod(std::shared_ptr<selaura_runtime> runtime) {
    runtime->warn("This mod is an example mod, it does not do anything useful.");
}