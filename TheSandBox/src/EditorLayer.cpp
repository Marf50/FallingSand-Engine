#include "EditorLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "FallingSandEngine/Scene/SceneSerailizer.h"
#include "FallingSandEngine/Utils/PlatformUtils.h"

namespace FallingSandEngine
{
	EditorLayer::EditorLayer()
		:Layer("TheSandbox"), m_CameraController(1280.0f / 720.0f)
	{

	}
	void EditorLayer::OnAttach()
	{
		// Load Stuff Here

		// Framebuffer Setup
		{
			FramebufferSpecification FramebufferSpec;
			FramebufferSpec.Width = 1280;
			FramebufferSpec.Height = 720;
			m_Framebuffer = Framebuffer::Create(FramebufferSpec);
		}
		// Texture Loading
		{

		}
		// Scene
		{
			m_ActiveScene = CreateRef<Scene>();
			
			m_ScenehierarchyPanel.SetContext(m_ActiveScene);


		}
	}
	void EditorLayer::OnDetach()
	{

	}
	void EditorLayer::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);


		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(FSE_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
	}
	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{

		// Shortcuts
		if (e.GetRepeatCount() > 0)
			return false;
		bool controlPressed = (Input::IsKeyPressed(KeyCode::Left_Control) || Input::IsKeyPressed(KeyCode::Right_Control));
		bool shiftPressed = (Input::IsKeyPressed(KeyCode::Left_Shift) || Input::IsKeyPressed(KeyCode::Right_Shift));
		switch (e.GetKeyCode())
		{
			case KeyCode::S:
			{
				if (shiftPressed)
					SaveSceneAs();
				break;
			}
			case KeyCode::N:
			{
				if (controlPressed)
					NewScene();
				break;
			}
			case KeyCode::O:
			{
				if (controlPressed)
					OpenScene();
				break;
			}
		}
	}
	void EditorLayer::OnUpdate(Timestep ts)
	{
		

		// Update // 
		{
			if (m_ViewPortFocused)
			{
				m_CameraController.OnUpdate(ts);
			}
			
		}
		// Render // 
		{
			Renderer2D::ResetStats();
			// Pre Render
			{
				m_Framebuffer->Bind();
				RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
				RenderCommand::Clear();
			}
			
			m_ActiveScene->OnUpdate(ts);
			
			m_Framebuffer->UnBind();
		}
	}
	void EditorLayer::OnImGuiRender()
	{
		
		// DockSpace
		ImGui::DockSpaceOverViewport();

		//MenuBar
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
					NewScene();

				if (ImGui::MenuItem("Save As", "Ctrl+Shift+S"))
					SaveSceneAs();

				if (ImGui::MenuItem("Open", "Ctrl+O"))
					OpenScene();

				if (ImGui::MenuItem("Exit"))
					Application::Get().Close();

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		//ViewPort
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
			ImGui::Begin("ViewPort");
			m_ViewPortFocused = ImGui::IsWindowFocused();
			m_ViewPortHovered = ImGui::IsWindowHovered();
			Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewPortFocused || !m_ViewPortHovered);
			ImVec2 ViewPortSize = ImGui::GetContentRegionAvail();
			if (m_ViewPortSize != *((glm::vec2*)&ViewPortSize))
			{
				m_Framebuffer->Resize((uint32_t)ViewPortSize.x, (uint32_t)ViewPortSize.y);
				m_ViewPortSize = { ViewPortSize.x,ViewPortSize.y };
				
				m_CameraController.ResizeBounds(ViewPortSize.x, ViewPortSize.y);
				m_ActiveScene->ResizeBounds((uint32_t)ViewPortSize.x, (uint32_t)ViewPortSize.y);
			}
			
			uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
			ImGui::Image((void*)textureID, ImVec2{m_ViewPortSize.x, m_ViewPortSize.y}, ImVec2{0,1}, ImVec2{1,0});
			ImGui::End();
			ImGui::PopStyleVar();
		}
		m_ScenehierarchyPanel.OnImGuiRender();
	}

	void EditorLayer::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->ResizeBounds((uint32_t)m_ViewPortSize.x, (uint32_t)m_ViewPortSize.y);
		m_ScenehierarchyPanel.SetContext(m_ActiveScene);
	}
	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("Falling Sand Engine Scene (*.FSEScene)\0*.FSEScene\0");
		if (!filepath.empty())
		{
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(filepath);
		}
	}
	void EditorLayer::OpenScene()
	{
		std::string filepath = FileDialogs::OpenFile("Falling Sand Engine Scene (*.FSEScene)\0*.FSEScene\0");
		if (!filepath.empty())
		{
			m_ActiveScene = CreateRef<Scene>();
			m_ActiveScene->ResizeBounds((uint32_t)m_ViewPortSize.x, (uint32_t)m_ViewPortSize.y);
			m_ScenehierarchyPanel.SetContext(m_ActiveScene);
			SceneSerializer serializer(m_ActiveScene);
			serializer.Deserialize(filepath);
		}
	}
}
