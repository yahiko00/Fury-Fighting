#include "TexCoordBuffer.h"

#include "Platform.h"

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
