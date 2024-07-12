#pragma once
#include "Core.h"
namespace FallingSandGame {

	class FSG_API Application
	{
	public:
		//Application();
		//virtual ~Application();
		
		void Run();
	};
	//Defined in Client
	Application* CreateApplication();
}


