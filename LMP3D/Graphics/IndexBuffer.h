#pragma once

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		class IndexBuffer
		{
		public:
			explicit inline IndexBuffer()
				: m_data{}
			{
			}

			inline ~IndexBuffer()noexcept
			{
			}

			inline void setData( FaceArray && data )
			{
				m_data = std::move( data );
			}

			inline Face const * getData()const
			{
				return m_data.data();
			}

			inline GLsizei getCount()const
			{
				return static_cast< GLsizei >( m_data.size() );
			}

		private:
			FaceArray m_data;
		};
	}
}
