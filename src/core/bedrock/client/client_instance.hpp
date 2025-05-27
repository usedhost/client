#pragma once
#include "../../../../client/symbol/resolver.hpp"
#include "client_instance_interface.hpp"
#include "../core/math/vec2.hpp"
#include <libhat/access.hpp>

#include "gui_data.hpp"

namespace bedrock {
	class ClientInstance : public IClientInstance {
	public:
		void _updateScreenSizeVariables(Vec2* totalScreenSize, Vec2* safeZone, float guiScale) {
			static auto sig = GET_SIGNATURE("ClientInstance::_updateScreenSizeVariables");
			auto fn = reinterpret_cast<void(__thiscall*)(ClientInstance*, Vec2*, Vec2*, float)>(sig.value());
			fn(this, totalScreenSize, safeZone, guiScale);
		};

		bedrock::GuiData* getGuiData() {
			return hat::member_at<bedrock::GuiData*>(this, 0x5B8);
		};
	};
};