#pragma once
#include "FallingSandEngine/Core/Core.h"

#ifdef FSE_PLATFORM_WINDOWS

extern FallingSandEngine::Application* FallingSandEngine::CreateApplication();

int main(int argc, char** argv)
{

	FallingSandEngine::Log::Init();

	FSE_BEGIN_PROFILE_SESSION("Startup", "FallingSandEngine-Profile-Startup.json");
	auto app = FallingSandEngine::CreateApplication();
	FSE_END_PROFILE_SESSION();

	FSE_BEGIN_PROFILE_SESSION("Runtime", "FallingSandEngine-Profile-Runtime.json");
	app->Run();
	FSE_END_PROFILE_SESSION();

	FSE_BEGIN_PROFILE_SESSION("Shutdown", "FallingSandEngine-Profile-Shutdown.json");
	delete app;
	FSE_END_PROFILE_SESSION();

}

#endif