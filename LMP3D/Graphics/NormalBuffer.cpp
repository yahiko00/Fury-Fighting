#include "NormalBuffer.h"

#include "Platform/OpenGL.h"

namespace LMP3D
{
	namespace Graphics
	{
		bool NormalBuffer::bind()const
		{
			return Platform::BindNormalPointer( m_data );
		}

		void NormalBuffer:: unbind()const
		{
			Platform::UnbindNormalPointer();
		}
	}
}
