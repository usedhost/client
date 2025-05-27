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
    public:
        ClientInstance* clientInstance;
        ScreenContext* screenContext;
        std::byte padding24[64];
        Bedrock::NonOwnerPointer<mce::TextureGroup> textures;
        std::byte padding80[248 - 104];
        const void* currentScene; // const UIScene*

        MinecraftUIRenderContext(IClientInstance& client, ScreenContext& screenContext, const void* currentScene);

        ClientInstance* getClientInstance() {
            return hat::member_at<ClientInstance*>(this, 0x8);
        };

        ScreenContext* getScreenContext() {
            return hat::member_at<ScreenContext*>(this, 0x10);
        };

        virtual ~MinecraftUIRenderContext();
        virtual float getLineLength(Font& font, const std::string& text, float fontSize, bool showColorSymbol);
        virtual float getTextAlpha();
        virtual void setTextAlpha(float alpha);
        virtual void drawDebugText(const RectangleArea* rect, const std::string* text, const mce::Color* color, float alpha, TextAlignment alignment, const TextMeasureData* textData, const CaretMeasureData* caretData);
        virtual void drawText(Font& font, const RectangleArea& rect, const std::string& text, const mce::Color& color, float alpha, TextAlignment alignment, const TextMeasureData& textData, const CaretMeasureData& caretData);
        virtual void flushText(float deltaTime);
        virtual void drawImage(const mce::TexturePtr& texture, const Vec2& position, const Vec2& size, Vec2& uv, Vec2& uvSize, int degree);
        virtual void drawNineslice(const mce::TexturePtr* texture, void* nineslice);
        virtual void flushImages(const mce::Color& color, float alpha, void* materialNameHash);
        virtual void beginSharedMeshBatch(ComponentRenderBatch& renderBatch);
        virtual void endSharedMeshBatch(ComponentRenderBatch& renderBatch);
        virtual void drawRectangle(const RectangleArea& rect, const mce::Color& color, float alpha, int thickness);
        virtual void fillRectangle(const RectangleArea& rect, const mce::Color& color, float alpha);
        virtual void increaseStencilRef();
        virtual void decreaseStencilRef();
        virtual void resetStencilRef();
        virtual void fillRectangleStencil(const RectangleArea& rect);
        virtual void enableScissorTest(const RectangleArea& rect);
        virtual void disableScissorTest();
        virtual void setClippingRectangle(const RectangleArea& rect) {
            using func_t = void(*)(MinecraftUIRenderContext*, const RectangleArea&);
            auto vtable = *(void***)this;
            static auto func = reinterpret_cast<func_t>(vtable[0x14]);
            func(this, rect);
        };
        virtual void setFullClippingRectangle();
        virtual void saveCurrentClippingRectangle() {
            using func_t = void(*)(MinecraftUIRenderContext*);
            auto vtable = *(void***)this;
            static auto func = reinterpret_cast<func_t>(vtable[0x16]);
            func(this);
        };
        virtual void restoreSavedClippingRectangle() {
            using func_t = void(*)(MinecraftUIRenderContext*);
            auto vtable = *(void***)this;
            static auto func = reinterpret_cast<func_t>(vtable[0x17]);
            func(this);
        };
        virtual RectangleArea getFullClippingRectangle();
        virtual bool updateCustom(void* customRenderer);
        virtual void renderCustom(void* customRenderer, int pass, RectangleArea& renderAABB);
        virtual void cleanup();
        virtual void removePersistentMeshes();
        virtual mce::TexturePtr getTexture(const ResourceLocation& resourceLocation, bool forceReload);
        virtual mce::TexturePtr getZippedTexture(/*const Core::Path*/ void* zippedFolderPath, const ResourceLocation& resourceLocation, bool forceReload);
        virtual void unloadTexture(ResourceLocation const&);
    };
}