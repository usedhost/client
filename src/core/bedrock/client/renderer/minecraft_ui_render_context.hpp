#pragma once

#include "../client_instance.hpp"
#include "screen_context.hpp"
#include "../../core/utility/enable_non_owner_references.hpp"
#include "../../core/math/color.hpp"
#include "../../core/math/vec2.hpp"
#include <libhat/access.hpp>

#include <memory>
#include <map>
#include <string>

namespace bedrock::mce {
    class BedrockTexture;
    class ClientTexture;
}

namespace bedrock {
    class ComponentRenderBatch {};
    struct BedrockTextureData {
        mce::ClientTexture* clientTexture;
    };
    class ResourceLocation {
    public:
        void* mFileSystem; // ResourceFileSystem
        std::string mPath;
        uint64_t mPathHash;
        uint64_t mFullHash;

        ~ResourceLocation();
        ResourceLocation();
        ResourceLocation(const std::string& path);
        ResourceLocation(const char* path);
    private:
        void _computeHashes();
    };

    namespace cg {
        class ImageBuffer {};
    }

    namespace mce {
        class ClientTexture {
            std::byte padding0[32];
        };
        class TextureGroup : public Bedrock::EnableNonOwnerReferences {
        public:
            std::byte padding48[352];
            std::map<ResourceLocation, BedrockTexture> mLoadedTextures;

            BedrockTexture& uploadTexture(const ResourceLocation& resource, /*const mce::TextureContainer&*/ void* texture, std::optional<std::string_view> debugName);
            BedrockTexture& uploadTexture(const ResourceLocation& resource, cg::ImageBuffer imageBuffer);
            void unloadAllTextures();
        };
        class TexturePtr {
        public:
            std::shared_ptr<const BedrockTextureData> mClientTexture;
            std::shared_ptr<ResourceLocation> mResourceLocation;
        };
    };
    class UIScene {};
    class Font {};
    struct RectangleArea {
        float _x0;
        float _x1;
        float _y0;
        float _y1;
    };

    enum TextAlignment : uint8_t {
        Left = 0x0,
        Right = 0x1,
        Center = 0x2
    };

    struct TextMeasureData {
        float fontSize;
        int linePadding;
        bool renderShadow;
        bool showColorSymbol;
        bool hideHyphen;
    };
    struct CaretMeasureData {
        int position;
        bool shouldRender;
    };
    class MinecraftUIRenderContext {
    private:
        char pad0[0x8];
    public:
        ClientInstance* clientInstance;
    private:
        char pad1[0x8];
    public:
        ScreenContext* screenContext;
    };
}