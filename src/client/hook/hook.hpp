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

		bool enable();
		bool disable();

		template <typename T>
		T get_original() const {
			return reinterpret_cast<T>(original);
		}
	};

	bool init_hooking();
	void shutdown_hooking();
	hook_t hook(void* target, void* detour);
}
