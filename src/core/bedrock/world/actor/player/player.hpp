#pragma once

#include "../mob.hpp"
#include "../../level/level.hpp"
#include "../../level/game_type.hpp"
#include "../../../platform/uuid.hpp"
#include "../../../network/packet_sender.hpp"
#include "../../../network/network_identifier.hpp"
#include "../../../entity/gamerefs_entity/entity_context.hpp"
#include "../../../common_types.hpp"

#include <string>
#include <memory>

namespace selaura::bedrock {
	class Player : public Mob {
		Player(
			class Level&,
			class PacketSender& PacketSender,
			enum GameType playerGameType,
			bool isHostingPlayer,
			const NetworkIdentifier& owner,
			class SubClientId subid,
			class mce::UUID uuid,
			class std::string const& playFabId,
			class std::string const& deviceId,
			void* const& gameServerToken,
			EntityContext& entityContext,
			std::string const& platformId,
			std::string const& platformOnlineId
		);
	};
};