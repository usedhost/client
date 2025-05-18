#include "hook.hpp"

namespace selaura {

	bool hook_t::enable() {
#ifdef SELAURA_WINDOWS
		return MH_EnableHook(target) == MH_OK;
#else
		return true;
#endif
	}

	bool hook_t::disable() {
#ifdef SELAURA_WINDOWS
		return MH_DisableHook(target) == MH_OK;
#else
		return DobbyDestroy(target) == 0;
#endif
	}

	bool init_hooking() {
#ifdef SELAURA_WINDOWS
		return MH_Initialize() == MH_OK;
#else
		return true;
#endif
	}

	void shutdown_hooking() {
#ifdef SELAURA_WINDOWS
		MH_Uninitialize();
#endif
	}

	hook_t hook(void* target, void* detour) {
		void** original_out;
#ifdef SELAURA_WINDOWS
		MH_CreateHook(target, detour, original_out);
#else
		DobbyHook(target, detour, original_out);
#endif
		return { target, detour, *original_out };
	}
}
