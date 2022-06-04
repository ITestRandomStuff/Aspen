#include "aspch.h"
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Aspen
{
	Image::Image(const std::string& imagePath, int desiredChannels)
	{
		int channels;
		m_ImageData = stbi_load(imagePath.c_str(), &m_Size.x, &m_Size.y, &channels, desiredChannels);
		ASP_ASSERT(m_ImageData == NULL, "Failed to load image.");

		switch (channels)
		{
		case 1:
			m_Format = GL_RED;
			break;
		
		case 3:
			m_Format = GL_RGB;
			break;

		case 4:
			m_Format = GL_RGBA;
			break;

		default:
			ASP_ERROR("Invalid number of channels.");
		}
	}

	Image::~Image()
	{
		Free();
	}

	void Image::Free()
	{
		if (!m_ImageData) return;
		stbi_image_free(m_ImageData);
	}
}