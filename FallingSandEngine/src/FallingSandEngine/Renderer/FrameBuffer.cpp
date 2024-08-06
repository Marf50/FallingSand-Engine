#include "fsepch.h"
#include "Framebuffer.h"
#include "FallingSandEngine/Renderer/Renderer.h"
#include "Platform/OpenGl/OpenGLFrameBuffer.h"
namespace FallingSandEngine
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FSE_CORE_ASSERT(false, "Renderer API is set to none");
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(spec);
		}
		FSE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}