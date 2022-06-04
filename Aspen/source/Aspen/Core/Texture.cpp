#include "aspch.h"
#include "Texture.h"

namespace Aspen
{
	Texture::Texture(Image& img)
		:m_Type(GL_TEXTURE_2D), m_Image(img)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(m_Type, m_ID);

		glTexParameteri(m_Type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_Type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(m_Type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		glTexParameteri(m_Type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

#		if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#		endif

		glTexImage2D(m_Type, 0, m_Image.GetFormat(), m_Image.GetSize().x, m_Image.GetSize().y, 0, m_Image.GetFormat(), GL_UNSIGNED_BYTE, m_Image.GetData());
	}
}