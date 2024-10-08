#include "LoadingScreenLayer.h"
#include "AssetManager.h"
#include "SettingsManager.h"
#include "UI/UILayers/MainMenu/MainMenuUILayer.h"  


namespace FallingSandEngine
{
    LoadingScreenLayer::LoadingScreenLayer()
        : Layer("Loading Screen"), m_Camera(-16.0f, 16.0f, -9.0f, 9.0f)
    {
    }

    void LoadingScreenLayer::OnAttach()
    {
        SettingsManager::RegisterSetting("ChunkRenderDistance", 2.0f);
        SettingsManager::RegisterSetting("CameraZoom", 100.0f);
        SettingsManager::RegisterSetting("WorldSeed", 1233121231);


        Ref<Texture2D> atlasTexture = Texture2D::Create("assets/Textures/UI/UiTiles2.png");

        Ref<Font> font = CreateRef<Font>();

        // Font layout: 16 columns per row, 6 rows, starting from the top-left
        int ascii = 32;  // Start at space character
        int columns = 16;  // 16 columns in the texture
        int totalGlyphs = 95;  // From ASCII 32 to 126
        int rowsLoaded = 0;    // Track rows as we go down the texture

        for (int i = 0; i < totalGlyphs; ++i)
        {
            
            int col = i % columns;
            int row = 15 - (i / columns);  

            
            Ref<SubTexture2D> glyphTexture = SubTexture2D::CreateFromCoords(atlasTexture, { col, row }, { 64, 64 });

            
            float advanceX = 24.0f;
            float offsetX = 0.0f;
            float offsetY = 0.0f;

            
            font->SetGlyph(ascii++, glyphTexture, 64.0f, 64.0f, advanceX, offsetX, offsetY);
        }

        
        AssetManager::LoadAsset("DefaultFont", font);
        


        Ref<UIStyle> style = CreateRef<UIStyle>();
        style->font = font;
        // Load Scalable Textures (e.g., Menu Window)
        style->MenuWindow = {
            SubTexture2D::CreateFromCoords(atlasTexture, { 0, 9 }, { 64, 64 }),  // Top-left corner
            SubTexture2D::CreateFromCoords(atlasTexture, { 1, 9 }, { 64, 64 }),  // Top edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 2, 9 }, { 64, 64 }),  // Top-right corner
            SubTexture2D::CreateFromCoords(atlasTexture, { 0, 8 }, { 64, 64 }),  // Left edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 1, 8 }, { 64, 64 }),  // Center
            SubTexture2D::CreateFromCoords(atlasTexture, { 2, 8 }, { 64, 64 }),  // Right edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 0, 7 }, { 64, 64 }),  // Bottom-left corner
            SubTexture2D::CreateFromCoords(atlasTexture, { 1, 7 }, { 64, 64 }),  // Bottom edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 2, 7 }, { 64, 64 })   // Bottom-right corner
        };

        // Load Button States (Idle, Hovered, Pressed)
        style->ButtonIdle = {
            SubTexture2D::CreateFromCoords(atlasTexture, { 3, 9 }, { 64, 64 }),  // Top-left corner (Idle)
            SubTexture2D::CreateFromCoords(atlasTexture, { 4, 9 }, { 64, 64 }),  // Top edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 5, 9 }, { 64, 64 }),  // Top-right corner
            SubTexture2D::CreateFromCoords(atlasTexture, { 3, 8 }, { 64, 64 }),  // Left edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 4, 8 }, { 64, 64 }),  // Center
            SubTexture2D::CreateFromCoords(atlasTexture, { 5, 8 }, { 64, 64 }),  // Right edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 3, 7 }, { 64, 64 }),  // Bottom-left corner
            SubTexture2D::CreateFromCoords(atlasTexture, { 4, 7 }, { 64, 64 }),  // Bottom edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 5, 7 }, { 64, 64 })   // Bottom-right corner
        };

        // Repeat for Hovered and Pressed button states
        style->ButtonHovered = {
            SubTexture2D::CreateFromCoords(atlasTexture, { 6, 9 }, { 64, 64 }),  // Top-left corner (Hovered)
            SubTexture2D::CreateFromCoords(atlasTexture, { 7, 9 }, { 64, 64 }),  // Top edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 8, 9 }, { 64, 64 }),  // Top-right corner
            SubTexture2D::CreateFromCoords(atlasTexture, { 6, 8 }, { 64, 64 }),  // Left edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 7, 8 }, { 64, 64 }),  // Center
            SubTexture2D::CreateFromCoords(atlasTexture, { 8, 8 }, { 64, 64 }),  // Right edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 6, 7 }, { 64, 64 }),  // Bottom-left corner
            SubTexture2D::CreateFromCoords(atlasTexture, { 7, 7 }, { 64, 64 }),  // Bottom edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 8, 7 }, { 64, 64 })   // Bottom-right corner
        };

        style->ButtonPressed = {
            SubTexture2D::CreateFromCoords(atlasTexture, { 9, 9 }, { 64, 64 }),  // Top-left corner (Pressed)
            SubTexture2D::CreateFromCoords(atlasTexture, { 10, 9 }, { 64, 64 }),  // Top edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 11, 9 }, { 64, 64 }),  // Top-right corner
            SubTexture2D::CreateFromCoords(atlasTexture, { 9, 8 }, { 64, 64 }),  // Left edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 10, 8 }, { 64, 64 }),  // Center
            SubTexture2D::CreateFromCoords(atlasTexture, { 11, 8 }, { 64, 64 }),  // Right edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 9, 7 }, { 64, 64 }),  // Bottom-left corner
            SubTexture2D::CreateFromCoords(atlasTexture, { 10, 7 }, { 64, 64 }),  // Bottom edge
            SubTexture2D::CreateFromCoords(atlasTexture, { 11, 7 }, { 64, 64 })   // Bottom-right corner
        };

        // Load static textures for Slider and ScrollTrack
        style->SliderTrack = {
            SubTexture2D::CreateFromCoords(atlasTexture, { 12, 9 }, { 64, 64 }),  // Left
            SubTexture2D::CreateFromCoords(atlasTexture, { 13, 9 }, { 64, 64 }),  // Middle
            SubTexture2D::CreateFromCoords(atlasTexture, { 14, 9 }, { 64, 64 })   // Right
        };

        style->Knob = SubTexture2D::CreateFromCoords(atlasTexture, { 14, 8 }, { 64, 64 });

        style->ScrollTrack = {
            SubTexture2D::CreateFromCoords(atlasTexture, { 15, 9 }, { 64, 64 }),  // Top
            SubTexture2D::CreateFromCoords(atlasTexture, { 15, 8 }, { 64, 64 }),  // Middle
            SubTexture2D::CreateFromCoords(atlasTexture, { 15, 7 }, { 64, 64 })   // Bottom
        };

        style->ScrollThumb = SubTexture2D::CreateFromCoords(atlasTexture, { 12, 8 }, { 64, 64 });

        // Store the UIStyle in the AssetManager
        AssetManager::LoadAsset("DefaultUIStyle", style);

        // Mark assets as loaded
        m_AssetsLoaded = true;
    }

    void LoadingScreenLayer::OnDetach()
    {
        //FSE_INFO("Loading Detach");
        Application::Get().PushLayer(new MainMenuUILayer());  // Push the main game layer
    }

    void LoadingScreenLayer::OnUpdate(Timestep ts)
    {
        Renderer2D::BeginScene(m_Camera);

        if (!m_AssetsLoaded) {
            // Render a loading message idk man
           
            RenderCommand::SetClearColor({ 0.3, 0.1, 0.2, 1 });
            RenderCommand::Clear();
            
        }
        else {
            // After the assets are fully loaded, push the main game layer and remove the loading screen
            //FSE_INFO("Loading Detach start");
            Application::Get().PopLayer(this);  // Remove the loading screen layer
            m_AssetsLoaded = false;
        }

        Renderer2D::EndScene();
    }
}
