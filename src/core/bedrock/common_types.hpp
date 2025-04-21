#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

#include "world/actor/actor.hpp"

namespace selaura::bedrock {
	using ActorList = std::vector<class Actor*>;

	enum class SubClientId : std::uint8_t {
		Server = 0,
		PrimaryClient = 0,
		Client2 = 1,
		Client3 = 2,
		Client4 = 3,
		ExtraIdSlotStart = 100,
		EditorUI = 101
	};

	using BlockRuntimeId = std::uint32_t;
	using BiomeIdType = std::uint16_t;
};