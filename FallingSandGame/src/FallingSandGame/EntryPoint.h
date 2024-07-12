#pragma once

#ifdef FSG_PLATFORM_WINDOWS

extern FallingSandGame::Application* FallingSandGame::CreateApplication();
int main(int argc, char** argv)
{
	FallingSandGame::Log::Init();
	int a = 5;
	FSG_INFO("Hello! Var={0}", a);
	FSG_CORE_WARN("Initialized Log!");
	//printf("FSG Engine\n");
	auto app = FallingSandGame::CreateApplication();
	app->Run();
	delete app;
}

#endif