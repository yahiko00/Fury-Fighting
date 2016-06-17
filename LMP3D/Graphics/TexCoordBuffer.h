#ifndef ___LMP3D_Graphics_TexCoordBuffer_H___
#define ___LMP3D_Graphics_TexCoordBuffer_H___

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		class TexCoordBuffer
		{
		public:
			explicit inline TexCoordBuffer( Vector2Array const & data )
				: m_data( data )
			{
			}

			inline ~TexCoordBuffer()throw()
			{
			}

			inline bool bind()const
			{
				glEnableClientState( GL_TEXTURE_COORD_ARRAY );
				glTexCoordPointer( 2, GL_FLOAT, 0, &m_data[0] );
				return checkGlError( "glVertexPointer" );
			}

			inline void unbind()const
			{
				glDisableClientState( GL_TEXTURE_COORD_ARRAY );
			}

			inline GLsizei getCount()const
			{
				return static_cast< GLsizei >( m_data.size() );
			}

		private:
			Vector2Array m_data;
		};
	}
}

#endif
