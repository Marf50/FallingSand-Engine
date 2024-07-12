#pragma once
#include "Core.h"
namespace FallingSandEngine {

	class FSE_API Application
	{
	public:
		//Application();
		//virtual ~Application();
		
		void Run();
	};
	//Defined in Client
	Application* CreateApplication();
}


