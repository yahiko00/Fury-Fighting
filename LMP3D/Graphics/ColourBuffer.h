#ifndef ___LMP3D_Graphics_ColourBuffer_H___
#define ___LMP3D_Graphics_ColourBuffer_H___

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		class ColourBuffer
		{
		public:
			explicit inline ColourBuffer( ColourArray const & data )
				: m_data( data )
			{
			}

			inline ~ColourBuffer()throw()
			{
			}

			inline bool bind()const
			{
				glEnableClientState( GL_COLOR_ARRAY );
				glColorPointer( 4, GL_FLOAT, 0, &m_data[0] );
				return checkGlError( "glColorPointer" );
			}

			inline void unbind()const
			{
				glDisableClientState( GL_COLOR_ARRAY );
			}

			inline GLsizei getCount()const
			{
				return static_cast< GLsizei >( m_data.size() );
			}

		private:
			ColourArray m_data;
		};
	}
}

#endif
