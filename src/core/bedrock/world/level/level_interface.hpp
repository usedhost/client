#pragma once
#include "../../core/utility/enable_non_owner_references.hpp"

namespace bedrock {
	class ILevel : Bedrock::EnableNonOwnerReferences {
	public:
		~ILevel() override = default;

	};
};