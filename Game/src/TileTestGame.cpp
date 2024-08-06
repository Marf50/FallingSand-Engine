#include "TileTestGame.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

static const uint32_t mapWidth = 32;
static const uint32_t mapHeight = 32;
static const char* s_MapTiles =
"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"
"wwwwwwwwwwwwwdddwwwwwwwwwwwwwwww"
"wwwwwwwwdddddddddwwwwwwwwwwwwwww"
"wwwwwwwddddddddddddwwwwwwwwwwwww"
"wwwwwwdddddddddddddddwwwwwwwwwww"
"wwwwwdddddddddddddddddwwwwwwwwww"
"wwwwddddddddddddddddddddwwwwwwww"
"wwwwddddddddddddddddddddddwwwwww"
"wwwwwddddddddddddddddddddddwwwww"
"wwwwwwddddddddddddddddddddwwwwww"
"wwwwwwwddddddddddddddddddwwwwwww"
"wwwwwwwdddddddddddddddddwwwwwwww"
"wwwwwwwwddddddddddddddddwwwwwwww"
"wwwwwwwwwdddddddddddddddwwwwwwww"
"wwwwwwwwwdddddddddddddddwwwwwwww"
"wwwwwwwwddddddddddddddddwwwwwwww"
"wwwwwwwddddddddddddddddddddddwww"
"wwwwwwddddddddddddddddddwwwwwwww"
"wwwwwdddddddddddddddddddwwwwwwww"
"wwwwdddddddddddddddddddddwwwwwww"
"wwwdddddddddddddddddddddddwwwwww"
"wwwddddddddddddwwddddddddddwwwww"
"wwwdddddddddddwwwwwwddddddddwwww"
"wwwwwddddddddddwwwwdddddddddwwww"
"wwwwwwwdddddddddddddddddddddwwww"
"wwwwwwwwwwddddddddddddddddddwwww"
"wwwwwwwwwwwdddddddddddddddddwwww"
"wwwwwwwwwwwwwddddwwwdddddddwwwww"
"wwwwwwwwwwwwwwddwwwwwdddddwwwwww"
"wwwwwwwwwwwwwwwwwwwwwwddddwwwwww"
"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"
"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"
;
TileTestGame::TileTestGame()
	:Layer("TileTestGame"), m_CameraController(1280.0f / 720.0f)
{
}

void TileTestGame::OnAttach()
{
	// Loading Stuff
	m_TileTextureSheet = FallingSandEngine::Texture2D::Create("TileTestGame/assets/Textures/roguelikeSheet_transparent.png");

	s_TextureMap['w'] = FallingSandEngine::SubTexture2D::CreateFromCoords(m_TileTextureSheet, {0,30}, {16,16}, {1,1}, 1);
	s_TextureMap['d'] = FallingSandEngine::SubTexture2D::CreateFromCoords(m_TileTextureSheet, {6,30}, {16,16}, {1,1}, 1);

	//FallingSandEngine::FramebufferSpecification FramebufferSpec;
	//FramebufferSpec.Width = 1280;
	//FramebufferSpec.Height = 720;
	//m_Framebuffer = FallingSandEngine::Framebuffer::Create(FramebufferSpec);
}

void TileTestGame::OnDetach()
{

}

void TileTestGame::OnUpdate(FallingSandEngine::Timestep ts)
{


	// Update


	m_CameraController.OnUpdate(ts);

	// Render
	FallingSandEngine::Renderer2D::ResetStats();

	//m_Framebuffer->Bind();
	FallingSandEngine::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
	FallingSandEngine::RenderCommand::Clear();
	

	FallingSandEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	
	for (uint32_t y = 0; y < mapHeight; y++)
	{
		for (uint32_t x = 0; x < mapWidth; x++)
		{

			char tileType = s_MapTiles[x + y * mapWidth];
			FallingSandEngine::Ref<FallingSandEngine::SubTexture2D> texture;
			texture = s_TextureMap[tileType];
			FallingSandEngine::Renderer2D::DrawQuad({ 0.0 + x,0.0 - y }, { 1.0f,1.0f } , texture);
		}
	}

	FallingSandEngine::Renderer2D::EndScene();
	//m_Framebuffer->UnBind();

}

void TileTestGame::OnImGuiRender()
{
	


}

void TileTestGame::OnEvent(FallingSandEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
