#include "ColourBuffer.h"

#include "Platform/OpenGL.h"

namespace LMP3D
{
	namespace Graphics
	{
		bool ColourBuffer::bind()const
		{
			return Platform::BindColourPointer( m_data );
		}

		void ColourBuffer::unbind()const
		{
			Platform::UnbindColourPointer();
		}
	}
}
