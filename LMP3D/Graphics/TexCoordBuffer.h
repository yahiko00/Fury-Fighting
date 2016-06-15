#pragma once

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		class TexCoordBuffer
		{
		public:
			explicit inline TexCoordBuffer()
				: m_data{}
			{
			}

			inline ~TexCoordBuffer()noexcept
			{
			}

			inline void setData( Vector2Array && data )
			{
				m_data = std::move( data );
			}

			inline bool bind()const
			{
				glTexCoordPointer( 2, GL_FLOAT, 0, m_data.data() );
				return checkGlError( "glVertexPointer" );
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
