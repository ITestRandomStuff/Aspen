#pragma once

#include "Aspen/Core/Image.h"

namespace Aspen
{
	class Texture
	{
	public:
		Texture(Image& img);

		inline Vector2i GetSize() { return m_Image.GetSize(); }
		inline GLenum GetFormat() { return m_Image.GetFormat(); }

		inline GLuint GetType() { return m_Type; }
		inline GLuint GetID() { return m_ID; }

	private:
		Image& m_Image;

		GLuint m_Type;
		GLuint m_ID;
	};
}