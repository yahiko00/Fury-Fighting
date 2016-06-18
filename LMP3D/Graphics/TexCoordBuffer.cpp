#include "TexCoordBuffer.h"

#include "Platform/OpenGL.h"

namespace LMP3D
{
	namespace Graphics
	{
		bool TexCoordBuffer::bind()const
		{
			return Platform::BindTexCoordPointer( m_data );
		}

		void TexCoordBuffer::unbind()const
		{
			Platform::UnbindTexCoordPointer();
		}
	}
}
