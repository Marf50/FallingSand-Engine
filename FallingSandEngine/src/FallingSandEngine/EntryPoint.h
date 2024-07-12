#pragma once

#ifdef FSE_PLATFORM_WINDOWS

extern FallingSandEngine::Application* FallingSandEngine::CreateApplication();
int main(int argc, char** argv)
{
	FallingSandEngine::Log::Init();
	int a = 5;
	FSE_INFO("Hello! Var={0}", a);
	FSE_CORE_WARN("Initialized Log!");
	//printf("FSE Engine\n");
	auto app = FallingSandEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif