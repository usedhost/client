#pragma once

#include <LuaBridge/LuaBridge.h>
#include <concepts>
#include <type_traits>

namespace selaura {
	template <typename T>
	concept StaticScriptLib = requires(lua_State * L) {
		{ T::init(L) } -> std::same_as<void>;
	};

	template <typename T>
	concept DynamicScriptLib = requires(T t, lua_State * L) {
		{ t.init(L) } -> std::same_as<void>;
	};

	class script_lib {
	public:
		script_lib() = default;
		virtual ~script_lib() = default;

		virtual void init(lua_State* L) = 0;

		template <StaticScriptLib T>
		static void register_lib(lua_State* L) {
			T::init(L);
		}

		template <DynamicScriptLib T>
		static void register_lib(lua_State* L) {
			T{}.init(L);
		}
	};
};