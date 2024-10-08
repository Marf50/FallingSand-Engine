#include "EscMenuUILayer.h"

namespace FallingSandEngine
{
    EscMenuUILayer::EscMenuUILayer()
        : Layer("Esc Menu"),
        m_Camera(0.0f, 1920.0f, 0.0f, 1080.0f)  // Adjust the camera to your needs
    {
    }

    void EscMenuUILayer::OnAttach()
    {
       

        // Retrieve the UIStyle from the AssetManager
        Ref<UIStyle> style = AssetManager::GetUIStyle("DefaultUIStyle");
        if (style) {
            m_Style = *style;  // Assign it to m_Style if it's valid
            m_UI.SetStyle(m_Style);
        } else {
            FSE_ERROR("UIStyle not found in AssetManager");
        }

        // Set up the grid for the menu
        glm::vec2 screenSize = { Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight()  };
        m_Camera.SetProjection(0.0f, Application::Get().GetWindow().GetWidth(), 0.0f, Application::Get().GetWindow().GetHeight());
        m_UI.SetGrid(9, 16, screenSize);  // Set a grid for the UI
    }

    void EscMenuUILayer::OnDetach()
    {
        delete this;
    }

    void EscMenuUILayer::OnUpdate(Timestep ts)
    {

        Renderer2D::BeginScene(m_Camera);
        
        // Draw a simple menu with a "Resume" and "Exit" button
        m_UI.Depth = 0.1f;
        m_UI.DrawMenu(0, 0, 4, 9);  // Example menu coordinates

        m_UI.Depth = 0.2f;
        if (m_UI.DrawButton(0, 2, 4, 4, 32, "Resume"))
        {
            m_ShouldClose = true;  // Set flag to close the menu and resume the game
        }

        m_UI.Depth = 0.3f;
        if (m_UI.DrawButton(0, 1, 4, 3, 32, "Options"))
        {
            m_OptionsOpen = !m_OptionsOpen;
        }
       
        m_UI.Depth = 0.4f;
        if (m_UI.DrawButton(0, 0, 4, 2, 32, "Main Menu")) 
        {
            m_ShouldCloseToMainMenu = true;  // Exit the game
        }

        if (m_OptionsOpen)
        {
            m_UI.Depth = 0.1f;
            m_UI.DrawMenu(4, 0, 12, 9);

            m_UI.Depth = 0.2f;
            m_UI.DrawUiText(4, 7, 8, 9, 48, "Render Distance");

            // Convert the current slider value to a string to display next to the "Render Distance" text
            std::string renderDistanceValue = std::to_string(static_cast<int>(m_ChunkRenderDistance)); // Convert to integer and string

            m_UI.Depth = 0.25f;
            // Render the slider value to the right of the title
            m_UI.DrawUiText(9, 7, 11, 9, 48, renderDistanceValue);

            m_UI.Depth = 0.3f;
            m_UI.DrawSlider(4, 7, 12, 8, &m_ChunkRenderDistance, 1.0f, 15.0f, 32, 16);
            SettingsManager::UpdateSetting("ChunkRenderDistance", m_ChunkRenderDistance);

            std::string cameraZoomValue = std::to_string(static_cast<int>(m_CameraZoom));

            m_UI.Depth = 0.4f;
            m_UI.DrawUiText(4, 6, 8, 8, 48, "Camera Zoom");
            m_UI.DrawUiText(8, 6, 12, 8, 48, cameraZoomValue);
            m_UI.Depth = 0.5f;
            m_UI.DrawSlider(4, 6, 12, 7, &m_CameraZoom, 1.0f, 1000.0f, 32, 16);
            SettingsManager::UpdateSetting("CameraZoom", m_CameraZoom);
            
            m_UI.Depth = 0.6f;
            if (m_UI.DrawButton(10, 0, 12, 2, 32, "Apply"))
            {
                SettingsManager::ApplySettings();
            }
        }



        Renderer2D::EndScene();

        // Close the menu if necessary
        if (m_ShouldClose) {
            Application::Get().PopLayer(this);  // Pop the Esc menu layer
            m_ShouldClose = false;
            //FSE_INFO("Popping Esc Menu");
        }
        if (m_ShouldCloseToMainMenu)
        {
            Application::Get().PushLayer(new MainMenuUILayer);
            Application::Get().PopOverlay(this);
            Sandbox2D* gameLayer = Application::Get().GetLayerByType<Sandbox2D>();
            if (gameLayer)
            {
                Application::Get().PopLayer(gameLayer);
            }
            
            m_ShouldCloseToMainMenu = false;
        }
    }

    void EscMenuUILayer::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
       
        
        dispatcher.Dispatch<KeyPressedEvent>(FSE_BIND_EVENT_FN(EscMenuUILayer::OnKeyPressed));
        dispatcher.Dispatch<WindowResizeEvent>(FSE_BIND_EVENT_FN(EscMenuUILayer::OnWindowResize));
        m_UI.OnEvent(e);
    }

    bool EscMenuUILayer::OnKeyPressed(KeyPressedEvent& e)
    {
        // If escape is pressed again, close the menu
        if (e.GetKeyCode() == KeyCode::Escape) {
            m_ShouldClose = true;
            return true;  // Mark event as handled
        }

        return false;
    }
    bool EscMenuUILayer::OnWindowResize(WindowResizeEvent& e)
    {
        int width = e.GetWidth();
        int height = e.GetHeight();

        // Update the camera's projection matrix with the new width and height
        m_Camera.SetProjection(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
        glm::vec2 screenSize = { Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight() };
        m_Camera.SetProjection(0.0f, Application::Get().GetWindow().GetWidth(), 0.0f, Application::Get().GetWindow().GetHeight());
        m_UI.SetGrid(9, 16, screenSize);  // Set a grid for the UI
        return false;  // Return false to indicate we don't fully consume the event
    }
}