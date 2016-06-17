#ifndef ___LMP3D_Graphics_VertexBuffer_H___
#define ___LMP3D_Graphics_VertexBuffer_H___

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		class VertexBuffer
		{
		public:
			explicit inline VertexBuffer( Vector3Array const & data )
				: m_data( data )
			{
			}

			inline ~VertexBuffer()throw()
			{
			}

			inline bool bind()const
			{
				glEnableClientState( GL_VERTEX_ARRAY );
				glVertexPointer( 3, GL_FLOAT, 0, &m_data[0] );
				return checkGlError( "glVertexPointer" );
			}

			inline void unbind()const
			{
				glDisableClientState( GL_VERTEX_ARRAY );
			}

			inline GLsizei getCount()const
			{
				return static_cast< GLsizei >( m_data.size() );
			}

		private:
			Vector3Array m_data;
		};
	}
}

#endif
