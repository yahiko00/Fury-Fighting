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
			explicit inline TexCoordBuffer( Vector2Array const & data = Vector2Array() )
				: m_data( data )
			{
			}

			inline ~TexCoordBuffer()throw()
			{
			}

			bool bind()const;
			void unbind()const;

			inline int getCount()const
			{
				return int( m_data.size() );
			}

		private:
			Vector2Array m_data;
		};
	}
}

#endif
