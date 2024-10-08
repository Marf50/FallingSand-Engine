#include "fsepch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGl/OpenGLTexture.h"
namespace FallingSandEngine
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		FSE_CORE_ASSERT(false, "RendererAPI::None is not allowed!")
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(path);
		}

		FSE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		FSE_CORE_ASSERT(false, "RendererAPI::None is not allowed!")
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(width, height);
		}

		FSE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, uint32_t channels)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		FSE_CORE_ASSERT(false, "RendererAPI::None is not allowed!")
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(width, height, channels);
		}

		FSE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}