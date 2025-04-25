#pragma once
#include "../../core/utility/enable_non_owner_references.hpp"

namespace selaura::bedrock {
	class ILevel : Bedrock::EnableNonOwnerReferences {
	public:
		~ILevel() override = default;

	};
};