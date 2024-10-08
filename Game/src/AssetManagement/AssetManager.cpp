#include "AssetManager.h"
#include "FallingSandEngine/Core/Log.h"  // Assuming you have logging set up this way

namespace FallingSandEngine
{
    // Initialize static members
    std::unordered_map<std::string, Ref<Font>> AssetManager::s_Fonts;
    std::unordered_map<std::string, Ref<SubTexture2D>> AssetManager::s_SubTextures;
    Ref<SubTexture2D> AssetManager::s_DefaultTexture = nullptr;  // Set up default texture
    std::unordered_map<std::string, Ref<UIStyle>> AssetManager::m_Styles;
    // Load Font
    void AssetManager::LoadAsset(const std::string& name, const Ref<Font>& font)
    {
        if (s_Fonts.find(name) != s_Fonts.end()) {
            FSE_ERROR("Font {0} already exists in AssetManager!", name);
            return;
        }
        s_Fonts[name] = font;
    }

    // Load SubTexture
    void AssetManager::LoadAsset(const std::string& name, const Ref<SubTexture2D>& subtexture)
    {
        if (s_SubTextures.find(name) != s_SubTextures.end()) {
            FSE_ERROR("SubTexture {0} already exists in AssetManager!", name);
            return;
        }
        s_SubTextures[name] = subtexture;
    }

    void AssetManager::LoadAsset(const std::string& name, const Ref<UIStyle>& style)
    {
        m_Styles[name] = style;
    }

    // Get Font
    Ref<Font> AssetManager::GetFont(const std::string& name)
    {
        if (s_Fonts.find(name) != s_Fonts.end()) {
            return s_Fonts[name];
        }
        FSE_ERROR("Font asset not found: {0}", name);
        return nullptr;  // Return nullptr for fonts if not found
    }

    // Get SubTexture
    Ref<SubTexture2D> AssetManager::GetSubTexture(const std::string& name)
    {
        if (s_SubTextures.find(name) != s_SubTextures.end()) {
            return s_SubTextures[name];
        }
        FSE_ERROR("SubTexture asset not found: {0}", name);
        return s_DefaultTexture;  // Return default texture if not found
    }

    Ref<UIStyle> AssetManager::GetUIStyle(const std::string& name)
    {
        if (m_Styles.find(name) != m_Styles.end())
        {
            return m_Styles[name];
        }
        FSE_ERROR("UIStyle '{0}' not found", name);
        return nullptr;
    }

    // Unload Asset
    void AssetManager::UnloadAsset(const std::string& name)
    {
        if (s_Fonts.erase(name) == 0 && s_SubTextures.erase(name) == 0) {
            FSE_ERROR("Attempted to unload asset {0} that was not found!", name);
        }
    }
}