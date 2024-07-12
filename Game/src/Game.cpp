#include <FallingSandEngine.h>

class Game : public FallingSandEngine::Application
{
public:
	Game()
	{

	}

	~Game()
	{

	}
};
FallingSandEngine::Application* FallingSandEngine::CreateApplication()
{
	return new Game();
}