#ifndef ___LPM3D_Graphics_Camera_H___
#define ___LPM3D_Graphics_Camera_H___

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		class Camera
		{
		public:
			Camera();
			~Camera();

			bool apply()const;

			void rotate( float angle, float x, float y, float z )
			{
			}

			inline void rotate( float angle, Vector3 const & axis )
			{
				rotate( angle, axis.x, axis.y, axis.z );
			}

			void translate( float x, float y, float z )
			{
				m_position.x += x;
				m_position.y += y;
				m_position.z += z;
			}

			inline void translate( Vector3 const & value )
			{
				translate( value.x, value.y, value.z );
			}

		private:
			Vector3 m_position;
			Vector3 m_lookAt;
			Vector3 m_up;
		};
	}
}

#endif
