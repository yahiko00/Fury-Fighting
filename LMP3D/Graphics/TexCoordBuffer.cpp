#include "TexCoordBuffer.h"

#include "Platform.h"

namespace LMP3D
{
	namespace Graphics
	{
		bool TexCoordBuffer::bind()const
		{
			return Platform::bindTexCoordPointer( m_data );
		}

		void TexCoordBuffer::unbind()const
		{
			Platform::unbindTexCoordPointer();
		}
	}
}
