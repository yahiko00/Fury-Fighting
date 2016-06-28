#ifndef ___LPM3D_Graphics_Viewport_H___
#define ___LPM3D_Graphics_Viewport_H___

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		class Viewport
		{
		public:
			explicit Viewport( Size const & size );
			~Viewport();

			void resize( int x, int y );
			void perspective();
			void ortho();

			inline void resize( Size const & size )
			{
				resize( size.x, size.y );
			}

		private:
			Size m_size;
			float m_angle;
			float m_ratio;
			float m_near;
			float m_far;
		};
	}
}

#endif
