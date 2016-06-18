#include "VertexBuffer.h"

#include "Platform/OpenGL.h"

namespace LMP3D
{
	namespace Graphics
	{
		bool VertexBuffer::bind()const
		{
			return Platform::BindVertexPointer( m_data );
		}

		void VertexBuffer::unbind()const
		{
			Platform::UnbindVertexPointer();
		}
	}
}
