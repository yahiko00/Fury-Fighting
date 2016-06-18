#include "ColourBuffer.h"

#include "Platform.h"

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
