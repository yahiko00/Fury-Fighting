#ifndef ___LMP3D_Graphics_VertexBuffer_H___
#define ___LMP3D_Graphics_VertexBuffer_H___

#include "GraphicsCommon.h"

namespace LMP3D
{
	namespace Graphics
	{
		class VertexBuffer
		{
		public:
			explicit inline VertexBuffer( Vector3Array const & data = Vector3Array() )
				: m_data( data )
			{
			}

			inline ~VertexBuffer()throw()
			{
			}

			bool bind()const;
			void unbind()const;

			inline int getCount()const
			{
				return int( m_data.size() );
			}

		private:
			Vector3Array m_data;
		};
	}
}

#endif
