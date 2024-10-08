#include "fsepch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"


namespace FallingSandEngine
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		:m_Width(width), m_Height(height)
	{
		FSE_PROFILE_FUNCTION();
		m_InternalFormat = GL_RGBA8, m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, uint32_t channels)
		:m_Width(width), m_Height(height)
	{
		GLenum internalFormat, dataFormat;

		if (channels == 1)
		{
			internalFormat = GL_R8;     // Single channel texture
			dataFormat = GL_RED;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;   // RGB texture
			dataFormat = GL_RGB;
		}
		else if (channels == 4)
		{
			internalFormat = GL_RGBA8;  // RGBA texture
			dataFormat = GL_RGBA;
		}
		else
		{
			FSE_CORE_ERROR("Number of channels not supported {0}", channels);
		}


		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path)
	{
		FSE_PROFILE_FUNCTION();
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		//stbi_uc* data = nullptr;
		//{
				//FSE_PROFILE_SCOPE("OpenGLTexture2D::OpenGLTexture2D(const std::string&) - stbi_load");
			stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
				
			//FSE_CORE_ERROR("stbi_load Error: {0}", stbi_failure_reason());
		//}

		FSE_CORE_ASSERT(data, "Failed to Load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if(channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		FSE_CORE_ASSERT(internalFormat & dataFormat, "Format not suppored!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);



		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE,data);

		stbi_image_free(data);
	}
	
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		FSE_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		FSE_PROFILE_FUNCTION();

		uint32_t bpp = 0;
		switch (m_DataFormat)
		{
		case GL_RGBA: bpp = 4; break;
		case GL_RGB:  bpp = 3; break;
		case GL_RED:  bpp = 1; break;
		default:
			FSE_CORE_ASSERT(false, "Unsupported Data Format!");
			return;
		}

		FSE_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		FSE_PROFILE_FUNCTION();
		glBindTextureUnit(slot, m_RendererID);
	}



}