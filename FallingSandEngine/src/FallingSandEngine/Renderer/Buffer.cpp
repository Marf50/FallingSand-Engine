#include "fsepch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGl/OpenGLBuffer.h"

namespace FallingSandEngine
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FSE_CORE_ASSERT(false,"Renderer Api is set to none") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}
		FSE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FSE_CORE_ASSERT(false, "Renderer Api is set to none") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(size);
		}
		FSE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FSE_CORE_ASSERT(false, "Renderer Api is set to none") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}
		FSE_CORE_ASSERT(false, "Unknown RendererAPI")
			return nullptr;
	}
}