#pragma once

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		class ColourBuffer
		{
		public:
			explicit inline ColourBuffer()
				: m_data{}
			{
			}

			inline ~ColourBuffer()noexcept
			{
			}

			inline void setData( ColourArray && data )
			{
				m_data = std::move( data );
			}

			inline bool bind()const
			{
				glColorPointer( 4, GL_FLOAT, 0, m_data.data() );
				return checkGlError( "glColorPointer" );
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
