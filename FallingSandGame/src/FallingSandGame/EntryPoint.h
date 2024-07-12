#pragma once

#ifdef FSG_PLATFORM_WINDOWS

extern FallingSandGame::Application* FallingSandGame::CreateApplication();
int main(int argc, char** argv)
{
	printf("FSG Engine\n");
	auto app = FallingSandGame::CreateApplication();
	app->Run();
	delete app;
}

#endif