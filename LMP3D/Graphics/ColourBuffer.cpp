#include "ColourBuffer.h"

#include "Platform.h"

namespace LMP3D
{
	namespace Graphics
	{
		bool ColourBuffer::bind()const
		{
			return Platform::bindColourPointer( m_data );
		}

		void ColourBuffer::unbind()const
		{
			Platform::unbindColourPointer();
		}
	}
}
