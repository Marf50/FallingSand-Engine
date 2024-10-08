#include "MainMenuUILayer.h"

namespace FallingSandEngine
{
    MainMenuUILayer::MainMenuUILayer()
        : Layer("Main Menu"),
        m_Camera(0.0f, 1920.0f, 0.0f, 1080.0f)  // Adjust the camera to your needs
    {
    }

    void MainMenuUILayer::OnAttach()
    {


        // Retrieve the UIStyle from the AssetManager
        Ref<UIStyle> style = AssetManager::GetUIStyle("DefaultUIStyle");
        if (style) {
            m_Style = *style;  // Assign it to m_Style if it's valid
            m_UI.SetStyle(m_Style);
        }
        else {
            FSE_ERROR("UIStyle not found in AssetManager");
        }

        // Set up the grid for the menu
        glm::vec2 screenSize = { Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight() };
        m_Camera.SetProjection(0.0f, Application::Get().GetWindow().GetWidth(), 0.0f, Application::Get().GetWindow().GetHeight());
        m_UI.SetGrid(9, 16, screenSize);  // Set a grid for the UI
    }

    void MainMenuUILayer::OnDetach()
    {
        delete this;
    }

    void MainMenuUILayer::OnUpdate(Timestep ts)
    {
        RenderCommand::SetClearColor(glm::vec4(0.2, 0.2, 0.2, 1.0));
        RenderCommand::Clear();
        Renderer2D::BeginScene(m_Camera);
        m_UI.Depth = 0.1f;
        m_UI.DrawMenu(4, 0, 11, 9);
        m_UI.Depth = 0.2f;
        if (m_UI.DrawButton(4, 7, 11, 9, 32, "Start New Game"))
        {
            m_ShouldOpenGame = true;
        }
        if (m_UI.DrawButton(4, 0, 11, 2, 32, "Exit Game"))
        {
            Application::Get().Close();
        }
        
        Renderer2D::EndScene();

        if (m_ShouldOpenGame)
        {
            Application::Get().PushLayer(new Sandbox2D());
            Application::Get().PopLayer(this);
            m_ShouldOpenGame = false;
        }
    }

    void MainMenuUILayer::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);


        dispatcher.Dispatch<KeyPressedEvent>(FSE_BIND_EVENT_FN(MainMenuUILayer::OnKeyPressed));
        dispatcher.Dispatch<WindowResizeEvent>(FSE_BIND_EVENT_FN(MainMenuUILayer::OnWindowResize));
        m_UI.OnEvent(e);
    }

    bool MainMenuUILayer::OnKeyPressed(KeyPressedEvent& e)
    {
        return false;
    }
    bool MainMenuUILayer::OnWindowResize(WindowResizeEvent& e)
    {
        int width = e.GetWidth();
        int height = e.GetHeight();

        // Update the camera's projection matrix with the new width and height
        m_Camera.SetProjection(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
        // Set up the grid for the menu
        glm::vec2 screenSize = { Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight() };
        m_Camera.SetProjection(0.0f, Application::Get().GetWindow().GetWidth(), 0.0f, Application::Get().GetWindow().GetHeight());
        m_UI.SetGrid(9, 16, screenSize);  // Set a grid for the UI
        return false;  // Return false to indicate we don't fully consume the event
    }
}