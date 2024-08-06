#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("SandBox2D"), m_CameraController(1280.0f/720.0f)
{
}

void Sandbox2D::OnAttach()
{
	
	FSE_PROFILE_FUNCTION();
	// Loading Stuff
	
	m_TileTexture = FallingSandEngine::Texture2D::Create("assets/Textures/Tiles.jpg");
}

void Sandbox2D::OnDetach()
{
	FSE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(FallingSandEngine::Timestep ts)
{
	FSE_PROFILE_FUNCTION();
	
	// Update
	
	
	m_CameraController.OnUpdate(ts);
	
	// Render
	FallingSandEngine::Renderer2D::ResetStats();

	{
		FSE_PROFILE_SCOPE("Sandbox2D::Pre-Render");
		FallingSandEngine::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		FallingSandEngine::RenderCommand::Clear();
	}
	

	FallingSandEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		FSE_PROFILE_SCOPE("Sandbox2D::Renderer");
		
		float rotation = 0.0f;
		rotation += ts;
		for (int x = 0 ; x < 50; x++)
		{
			for (int y = 0; y < 50; y++)
			{
				
				FallingSandEngine::Renderer2D::DrawRotatedQuad({ -25.0f+x , -25.0f+y  , 0.1f}, { 1.0f,1.0f }, rotation+x+y, m_TileTexture);
				
				//FallingSandEngine::Renderer2D::DrawQuad({ 0.0f+x , 0.0f+y }, { 0.9f,0.9f }, { 0.8f,0.2f,0.3f,1.0f });
			}
		}
	}
	
	FallingSandEngine::Renderer2D::EndScene();

	
}

void Sandbox2D::OnImGuiRender()
{
	FSE_PROFILE_FUNCTION();

	ImGui::Begin("Statistics");
	auto stats = FallingSandEngine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::End();



}

void Sandbox2D::OnEvent(FallingSandEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
