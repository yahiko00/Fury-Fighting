#ifndef ___LMP3D_Graphics_NormalBuffer_H___
#define ___LMP3D_Graphics_NormalBuffer_H___

#include "GraphicsCommon.h"

namespace LMP3D
{
	namespace Graphics
	{
		class NormalBuffer
		{
		public:
			explicit inline NormalBuffer( Vector3Array const & data = Vector3Array() )
				: m_data( data )
			{
			}

			inline ~NormalBuffer()throw()
			{
			}

			bool bind()const;
			void unbind()const;

			inline int getCount()const
			{
				return int( m_data.size() );
			}

		private:
			Vector3Array m_data;
		};
	}
}

#endif
