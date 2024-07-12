#include <FallingSandGame.h>

class Game : public FallingSandGame::Application
{
public:
	Game()
	{

	}

	~Game()
	{

	}
};
FallingSandGame::Application* FallingSandGame::CreateApplication()
{
	return new Game();
}