#include "fsepch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGl/OpenGLVertexArray.h"
namespace FallingSandEngine
{
	Ref<VertexArray> VertexArray::Create()
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FSE_CORE_ASSERT(false, "Renderer API is set to none");
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
		}
		FSE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}