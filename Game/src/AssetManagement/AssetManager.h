#pragma once
#include "FallingSandEngine.h"
#include "UI/UIStyle.h"

namespace FallingSandEngine
{
    class AssetManager
    {
    public:
        // Load Asset Overloads
        static void LoadAsset(const std::string& name, const Ref<Font>& font);
        static void LoadAsset(const std::string& name, const Ref<SubTexture2D>& subtexture);
        static void LoadAsset(const std::string& name, const Ref<UIStyle>& style);
        // Retrieve Assets
        static Ref<Font> GetFont(const std::string& name);
        static Ref<SubTexture2D> GetSubTexture(const std::string& name);
        static Ref<UIStyle> GetUIStyle(const std::string& name);
        // Unload Asset
        static void UnloadAsset(const std::string& name);

    private:
        // Asset storage
        static std::unordered_map<std::string, Ref<Font>> s_Fonts;
        static std::unordered_map<std::string, Ref<SubTexture2D>> s_SubTextures;
        static std::unordered_map<std::string, Ref<UIStyle>> m_Styles;
        // Default assets (e.g., default texture)
        static Ref<SubTexture2D> s_DefaultTexture;
    };
}