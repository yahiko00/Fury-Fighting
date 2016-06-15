#pragma once

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		class NormalBuffer
		{
		public:
			explicit inline NormalBuffer()
				: m_data{}
			{
			}

			inline ~NormalBuffer()noexcept
			{
			}

			inline void setData( Vector3Array && data )
			{
				m_data = std::move( data );
			}

			inline bool bind()const
			{
				glNormalPointer( GL_FLOAT, 0, m_data.data() );
				return checkGlError( "glNormalPointer" );
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
