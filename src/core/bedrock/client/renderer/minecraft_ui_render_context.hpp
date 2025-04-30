#pragma once

#include "../client_instance.hpp"
#include "screen_context.hpp"
#include "../../core/utility/enable_non_owner_references.hpp"

namespace selaura::bedrock {
	class MinecraftUIRenderContext {
	public:
		IClientInstance* clientInstance;
		ScreenContext* screenContext;
		std::byte padding24[64];
		Bedrock::EnableNonOwnerReferences<int> textures; // Bedrock::EnableNonOwnerReferences<mce::TextureGroup>
		std::byte padding80[248 - 104];
		const void* currentScene; // const UIScene*

		MinecraftUIRenderContext(IClientInstance& client, ScreenContext& screenContext, const void* currentScene);
	}
};	