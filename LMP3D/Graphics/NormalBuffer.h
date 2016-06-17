#ifndef ___LMP3D_Graphics_NormalBuffer_H___
#define ___LMP3D_Graphics_NormalBuffer_H___

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		class NormalBuffer
		{
		public:
			explicit inline NormalBuffer( Vector3Array const & data )
				: m_data( data )
			{
			}

			inline ~NormalBuffer()throw()
			{
			}

			inline bool bind()const
			{
				if ( getCount() )
				{
					glEnableClientState( GL_NORMAL_ARRAY );
					glNormalPointer( GL_FLOAT, 0, &m_data[0] );
				}

				return checkGlError( "glNormalPointer" );
			}

			inline void unbind()const
			{
				glDisableClientState( GL_NORMAL_ARRAY );
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
