#include "fsepch.h"
#include "FallingSandEngine/Renderer/RenderCommand.h"
#include "Platform/OpenGl/OpenGLRendererAPI.h"

namespace FallingSandEngine
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
	
}
