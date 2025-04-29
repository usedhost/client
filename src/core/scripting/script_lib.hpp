#pragma once
#include <LuaBridge/LuaBridge.h>

namespace selaura::core {
	class script_lib {
	public:
		script_lib() = default;
		virtual ~script_lib() = default;

		virtual void init(lua_state* L) {};

		template <typename T>
		static void register_lib(lua_state* L) {
			T lib;
			lib.init(L);
		}
	};
};