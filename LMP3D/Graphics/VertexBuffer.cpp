#include "VertexBuffer.h"

#include "Platform.h"

namespace LMP3D
{
	namespace Graphics
	{
		bool VertexBuffer::bind()const
		{
			return Platform::bindVertexPointer( m_data );
		}

		void VertexBuffer::unbind()const
		{
			Platform::unbindVertexPointer();
		}
	}
}
