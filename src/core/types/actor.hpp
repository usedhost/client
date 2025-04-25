#pragma once
#include "../bedrock/world/actor/actor.hpp"

namespace selaura::core {
	class actor {
	public:
		// setSprinting(true) can call actor->setSprinting(true) but say this were to become a component
		// i can change it here without having to change every single piece a code that uses this
		// making it 10 times easier to update the client.
	};
};