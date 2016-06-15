#pragma once

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		class VertexBuffer
		{
		public:
			explicit inline VertexBuffer()
				: m_data{}
			{
			}

			inline ~VertexBuffer()noexcept
			{
			}

			inline void setData( Vector3Array && data )
			{
				m_data = std::move( data );
			}

			inline bool bind()const
			{
				glVertexPointer( 3, GL_FLOAT, 0, m_data.data() );
				return checkGlError( "glVertexPointer" );
			}

			inline GLsizei getSize()const
			{
				return static_cast< GLsizei >( m_data.size() );
			}

		private:
			Vector3Array m_data;
		};
	}
}
