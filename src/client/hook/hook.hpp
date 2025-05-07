#pragma once

#ifdef SELAURA_WINDOWS
#include <Windows.h>
#include <MinHook.h>
#else
#include <dobby.h>
#endif

namespace selaura {

	struct hook_t {
		void* target;
		void* detour;
		void* original;

		bool enable() {
#ifdef SELAURA_WINDOWS
			return MH_EnableHook(target) == MH_OK;
#else
			return true;
#endif
		}

		bool disable() {
#ifdef SELAURA_WINDOWS
			return MH_DisableHook(target) == MH_OK;
#else
			return DobbyDestroy(target) == RT_SUCCESS;
#endif
		}

		template <typename T>
		T get_original() const {
			return reinterpret_cast<T>(original);
		}
	};

	inline bool init_hooking() {
#ifdef SELAURA_WINDOWS
		return MH_Initialize() == MH_OK;
#else
		return true;
#endif
	}

	inline void shutdown_hooking() {
#ifdef SELAURA_WINDOWS
		MH_Uninitialize();
#endif
	}

	inline hook_t hook(void* target, void* detour, void** original_out) {
#ifdef SELAURA_WINDOWS
		MH_CreateHook(target, detour, original_out);
#else
		DobbyHook(target, detour, original_out);
#endif
		return { target, detour, *original_out };
	}
}
