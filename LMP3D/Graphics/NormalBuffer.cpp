#include "NormalBuffer.h"

#include "Platform.h"

namespace LMP3D
{
	namespace Graphics
	{
		bool NormalBuffer::bind()const
		{
			return Platform::bindNormalPointer( m_data );
		}

		void NormalBuffer:: unbind()const
		{
			Platform::unbindNormalPointer();
		}
	}
}
