#pragma once

#include "Aspen/Math/Vector2.h"

#include "Aspen/Debug/Log.h"
#include <glad/glad.h>

namespace Aspen
{
	class Image
	{
	public:
		Image(const std::string& imagePath, int desiredChannels = 4);
		~Image();

		void Free();
		inline Vector2i GetSize() { return m_Size; }
		inline GLenum GetFormat() { return m_Format; }

		inline unsigned char* GetData() { return m_ImageData; }

	private:
		unsigned char* m_ImageData;
		GLenum m_Format;
		Vector2i m_Size;
	};
}