#include <FallingSandEngine.h>
#include <FallingSandEngine/Core/EntryPoint.h>

#include <imgui/imgui.h>


#include <glm/gtc/matrix_transform.hpp>
#include "Platform/OpenGl/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>
#include "EditorLayer.h"
namespace FallingSandEngine
{
	//EntryPoint
	class TheSandbox : public Application
	{
	public:
		TheSandbox()
			: Application("The Sandbox")
		{
			PushLayer(new EditorLayer());
		}
		~TheSandbox()
		{

		}
	};

	Application* CreateApplication()
	{
		return new TheSandbox();
	}
}