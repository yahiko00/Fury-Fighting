#ifndef ___LMP3D_Graphics_ColourBuffer_H___
#define ___LMP3D_Graphics_ColourBuffer_H___

#include "GraphicsCommon.h"

namespace LMP3D
{
	namespace Graphics
	{
		class ColourBuffer
		{
		public:
			explicit inline ColourBuffer( ColourArray const & data = ColourArray() )
				: m_data( data )
			{
			}

			inline ~ColourBuffer()throw()
			{
			}

			bool bind()const;
			void unbind()const;

			inline int getCount()const
			{
				return int( m_data.size() );
			}

		private:
			ColourArray m_data;
		};
	}
}

#endif
