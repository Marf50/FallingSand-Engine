#include "EditorLayer.h"

#include <imgui/imgui.h>



namespace FallingSandEngine
{
	EditorLayer::EditorLayer()
		:Layer("TheSandbox"), m_CameraController(1280.0f / 720.0f)
	{

	}
	void EditorLayer::OnAttach()
	{
		// Load Stuff Here
		//Framebuffer Setup
		{
			FramebufferSpecification FramebufferSpec;
			FramebufferSpec.Width = 1280;
			FramebufferSpec.Height = 720;
			m_Framebuffer = Framebuffer::Create(FramebufferSpec);
		}
		//Texture Loading
		{

		}

	}
	void EditorLayer::OnDetach()
	{

	}
	void EditorLayer::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);
	}
	void EditorLayer::OnUpdate(Timestep ts)
	{
		// Update

		m_CameraController.OnUpdate(ts);

		// Render
		Renderer2D::ResetStats();
		// Pre Render
		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		RenderCommand::Clear();


		Renderer2D::BeginScene(m_CameraController.GetCamera());
		{
			Renderer2D::DrawQuad({ 0.0f,0.0f }, { 1.0f,1.0f }, { 1.0f,0.3f,0.2f,1.0f });

		}
		Renderer2D::EndScene();
		m_Framebuffer->UnBind();
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
			ImVec2 ViewPortSize = ImGui::GetContentRegionAvail();
			if (m_ViewPortSize != *((glm::vec2*)&ViewPortSize))
			{
				m_Framebuffer->Resize((uint32_t)ViewPortSize.x, (uint32_t)ViewPortSize.y);
				m_ViewPortSize = { ViewPortSize.x,ViewPortSize.y };
				
				m_CameraController.ResizeBounds(ViewPortSize.x, ViewPortSize.y);
			}
			
			uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
			ImGui::Image((void*)textureID, ImVec2{m_ViewPortSize.x, m_ViewPortSize.y}, ImVec2{0,1}, ImVec2{1,0});
			ImGui::End();
			ImGui::PopStyleVar();
		}
	}
}
