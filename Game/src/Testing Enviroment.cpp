#include <FallingSandEngine.h>
#include <FallingSandEngine/Core/EntryPoint.h>

#include <imgui/imgui.h>


#include <glm/gtc/matrix_transform.hpp>
#include "Platform/OpenGl/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>
#include "Sandbox2D.h"
#include "TileTestGame.h"

//uses layer as a subclass and overrides the virtual funtions
//class ExampleLayer : public FallingSandEngine::Layer
//{
//public:
//	ExampleLayer()
//		: Layer("Example")
//	{
//	}
//
//	void OnUpdate() override
//	{
//		FSE_INFO("ExampleLayer::Update");
//	}
//
//	void OnEvent(FallingSandEngine::Event& event) override
//	{
//		FSE_TRACE("{0}", event.ToString());
//	}
//};

//EntryPoint
class Game : public FallingSandEngine::Application
{
public:
	Game()
	{
		
		//PushLayer(new Sandbox2D());
		PushLayer(new TileTestGame());
	}

	~Game()
	{

	}
};

FallingSandEngine::Application* FallingSandEngine::CreateApplication()
{
	return new Game();
}