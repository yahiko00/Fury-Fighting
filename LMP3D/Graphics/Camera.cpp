#include "Camera.h"

#include "Platform.h"

namespace LMP3D
{
	namespace Graphics
	{
		Camera::Camera()
			: Movable()
		{
			setOrientation( Quaternion( Vector3( 0, 1, 0 ), radians( 180 ) ) );
		}

		Camera::~Camera()
		{
		}

		bool Camera::apply()const
		{
			static Vector3 l_up;
			static Vector3 l_right;
			static Vector3 l_front;
			getOrientation().toAxes( l_right, l_up, l_front );
			return Platform::lookAt( getPosition(), l_front, l_up );
		}
	}
}
