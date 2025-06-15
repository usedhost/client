#pragma once
#include "symbol.hpp"
#include <vector>
#include <string>

#include "mc/game/MinecraftGame.hpp"
#include "mc/renderer/Tessellator.hpp"
#include "mc/renderer/helpers/MeshHelpers.hpp"
#include "mc/deps/coregraphics/ImageBuffer.hpp"
#include "mc/deps/core/resource/ResourceHelper.hpp"

#ifdef SELAURA_WINDOW
#define THISCALL __thiscall
#else
#define THISCALL
#endif

namespace selaura::signatures {

    using splashtextrenderer_loadsplashes_t = std::vector<std::string>* (THISCALL*)(void*, void*);
    inline signature_symbol<splashtextrenderer_loadsplashes_t> splashtextrenderer_loadsplashes{
        "SplashTextRenderer::_loadSplashes",
        {
            { selaura::platform::windows, { "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B D9 49 8B F8 4C 89 44 24" } },
            { selaura::platform::android, { "? ? ? A9 ? ? ? A9 FD 03 00 91 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? D1 ? ? ? F9 F6 03 02 AA" } }
        }
    };

    using minecraftgame_update_t = void(THISCALL*)();
    inline signature_symbol<minecraftgame_update_t> minecraftgame_update{
        "MinecraftGame::update",
        {
            { selaura::platform::windows, { "48 8B C4 48 89 58 10 48 89 70 18 48 89 78 20 55 41 54 41 55 41 56 41 57 48 8D A8 18 F7" } },
            { selaura::platform::android, { "? ? ? FC ? ? ? A9 ? ? ? 91 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? D1 ? ? ? D5 F3 03 00 AA ? ? ? F9 ? ? ? F8 ? ? ? F9 ? ? ? 95" } }
        }
    };

	using screenview_setupandrender_t = void(THISCALL*)(void*);
    inline signature_symbol<screenview_setupandrender_t> screenview_setupandrender{
        "ScreenView::SetupAndRender",
        {
            { selaura::platform::windows, { "48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 98 FD" } },
            { selaura::platform::android, { "todo: find this" } }
        }
	};

    using tessellator_begin_t = void(THISCALL*)(Tessellator*, mce::PrimitiveMode, const int, const bool);
    inline signature_symbol<tessellator_begin_t> tessellator_begin{
        "Tessellator::begin",
        {
            { selaura::platform::windows, { "40 53 55 48 83 EC 28 80 B9" } },
            { selaura::platform::android, { "todo: find this" } }
        }
    };

    using tessellator_vertexuv_t = void(THISCALL*)(Tessellator*, float, float, float, float, float);
    inline signature_symbol<tessellator_vertexuv_t> tessellator_vertexuv{
        "Tessellator::vertexUV",
        {
            { selaura::platform::windows, { "48 83 EC ? 80 B9 ? ? ? ? ? 0F 57 E4" } },
            { selaura::platform::android, { "todo: find this" } }
        }
    };

    using tessellator_color_t = void(THISCALL*)(Tessellator*, float, float, float, float);
    inline signature_symbol<tessellator_color_t> tessellator_color{
        "Tessellator::color",
        {
            { selaura::platform::windows, { "80 B9 ? ? ? ? ? 4C 8B C1 75" } },
            { selaura::platform::android, { "todo: find this" } }
        }
    };

    using meshhelpers_rendermeshimmediately_t = void(THISCALL*)(void*, void*, void*, BedrockTextureData&, char*);
    inline signature_symbol<meshhelpers_rendermeshimmediately_t> meshhelpers_rendermeshimmediately{
        "MeshHelpers::renderMeshImmediately",
        {
            { selaura::platform::windows, { "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 98 FC FF FF 48 81 EC 68 04 00 00 49" } },
            { selaura::platform::android, { "todo: find this" } }
        }
    };

    using mce_rendermaterialgroup_ui_t = mce::MaterialPtr*(THISCALL*)(void*);
    inline signature_symbol<mce_rendermaterialgroup_ui_t> mce_rendermaterialgroup_ui{
        "mce::RenderMaterialGroup::ui",
        {
            { selaura::platform::windows, { "48 8B 05 ? ? ? ? 48 8D 55 90 48 8D 0D ? ? ? ? 48 8B 40 08 FF 15 ? ? ? ? 48 8B D8" } },
            { selaura::platform::android, { "todo: find this" } }
        }
    };

    using mce_texturegroup_uploadtexture_t = mce::BedrockTexture&(THISCALL*)(void*, const ResourceLocation&, cg::ImageBuffer);
    inline signature_symbol<mce_texturegroup_uploadtexture_t> mce_texturegroup_uploadtexture{
        "mce::TextureGroup::uploadTexture",
        {
            { selaura::platform::windows, {"48 89 5C 24 20 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 D9 48 81 EC C0 00 00 00 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 1F 4D 8B F0"}},
        }
    };

    using mce_texturegroup_unloadalltextures_t = void(*)();
    inline signature_symbol<mce_texturegroup_unloadalltextures_t> mce_texturegroup_unloadalltextures{
        "mce::TextureGroup::unloadAllTextures",
        {
            {selaura::platform::windows, {"48 89 5C 24 ? 57 48 83 EC ? 48 8B 99 ? ? ? ? 48 8B F9 48 8B 1B 80 7B ? ? 75 ? 0F 1F 00 48 8D 53"}}
        }
    };

    inline offset_symbol clientinstance_guidata{
        "ClientInstance::GuiData",
        {
                { selaura::platform::windows, {0x5B8}},
                { selaura::platform::android, {0x0} }
        }
    };

    inline offset_symbol minecraftuirendercontext_screencontext{
        "MinecraftUIRenderContext::ScreenContext",
        {
            { selaura::platform::windows, {0x10}},
            { selaura::platform::android, {0x0} }
        }
    };

    inline offset_symbol minecraftuirendercontext_clientinstance{
        "MinecraftUIRenderContext::ClientInstance",
        {
                { selaura::platform::windows, {0x8}},
                { selaura::platform::android, {0x0} }
        }
    };

    inline offset_symbol screencontext_tessellator{
        "ScreenContext::Tessellator",
        {
                    { selaura::platform::windows, {0xC8}},
                    { selaura::platform::android, {0x0} }
        }
    };

    inline offset_symbol screenview_visualtree{
        "ScreenView::VisualTree",
        {
                        { selaura::platform::windows, {0x48}},
                        { selaura::platform::android, {0x0} }
        }
    };

    inline offset_symbol visualtree_root{
        "VisualTree::root",
        {
                            { selaura::platform::windows, {0x8}},
                            { selaura::platform::android, {0x0} }
        }
    };

    inline offset_symbol uicontrol_layername{
        "UIControl::layerName",
        {
                                { selaura::platform::windows, {0x20}},
                                { selaura::platform::android, {0x0} }
        }
    };

    inline offset_symbol minecraftgame_gettexturegroup{
        "MinecraftGame::getTextureGroup",
        {
                                    { selaura::platform::windows, {0x6C8}},
                                    { selaura::platform::android, {0x0} }
        }
    };
}