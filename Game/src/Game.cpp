#include <FallingSandEngine.h>

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

class Game : public FallingSandEngine::Application
{
public:
	Game()
	{
		PushOverlay(new FallingSandEngine::ImGuiLayer());
	}

	~Game()
	{

	}
};
FallingSandEngine::Application* FallingSandEngine::CreateApplication()
{
	return new Game();
}