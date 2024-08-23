#include "EditorLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "FallingSandEngine/Scene/SceneSerailizer.h"

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
		if (m_ViewPortHovered)
		{
			m_CameraController.OnEvent(e);
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
				if (ImGui::MenuItem("Save"))
				{
					SceneSerializer serializer(m_ActiveScene);
					serializer.Serialize("assets/Scenes/Example.FSEScene");
				}
				if (ImGui::MenuItem("Load"))
				{
					SceneSerializer serializer(m_ActiveScene);
					serializer.Deserialize("assets/Scenes/Example.FSEScene");
				}

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
}
