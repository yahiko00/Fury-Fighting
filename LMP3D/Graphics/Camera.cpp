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
			static float matrix[16];
			static Vector3 l_up( matrix[1], matrix[5], matrix[9] );
			static Vector3 l_lookAt( matrix[2], matrix[6], matrix[10] );

			getOrientation().toMatrix( reinterpret_cast< float * >( matrix ) );
			l_up = Vector3( matrix[1], matrix[5], matrix[9] );
			l_lookAt = Vector3( matrix[2], matrix[6], matrix[10] );
			return Platform::lookAt( getPosition(), l_lookAt, l_up );
		}

		//void MNS_camera_vue_sub( Camera *camera, Vector3 *a, float v, int *touche )
		//{
		//	if ( touche[0] == 1 )
		//		a->x += v;

		//	if ( touche[0] == 2 )
		//		a->x -= v;

		//	if ( touche[2] == 1 )
		//		a->y += v;

		//	if ( touche[2] == 2 )
		//		a->y -= v;

		//	camera->vision.x = ( float )( cos( a->x )*sin( a->y ) );
		//	camera->vision.y = ( float )cos( a->y );
		//	camera->vision.z = ( float )( -sin( a->x )*sin( a->y ) );

		//	if ( touche[1] == 1 )
		//	{
		//		camera->position.z = camera->position.z + ( a->z *camera->vision.z );
		//		camera->position.x = camera->position.x + ( a->z *camera->vision.x );
		//		camera->position.y = camera->position.y + ( a->z *camera->vision.y );
		//	}

		//	if ( touche[1] == 2 )
		//	{
		//		camera->position.z = camera->position.z - ( a->z *camera->vision.z );
		//		camera->position.x = camera->position.x - ( a->z *camera->vision.x );
		//		camera->position.y = camera->position.y - ( a->z *camera->vision.y );
		//	}
		//}

		//void MNS_rotate( float c, float s, float *x, float *y );

		//void MNS_camera_vue_obj( Camera *camera, Vector3 *p, Vector3 *a, float v, float vit, int *touche )
		//{
		//	if ( touche[0] == 1 )
		//		a->x += v;

		//	if ( touche[0] == 2 )
		//		a->x -= v;

		//	if ( touche[1] == 1 )
		//		a->y += v;

		//	if ( touche[1] == 2 )
		//		a->y -= v;

		//	if ( a->x > ( PI * 2 ) ) a->x = a->x - ( float )( PI * 2 );
		//	if ( a->x < 0 )          a->x = ( float )( PI * 2 ) + a->x;
		//	if ( a->y > ( PI * 2 ) ) a->y = a->y - ( float )( PI * 2 );
		//	if ( a->y < 0 )          a->y = ( float )( PI * 2 ) + a->y;

		//	if ( a->y >= PI ) camera->haut.y = -1;
		//	else
		//		camera->haut.y = 1;

		//	if ( touche[2] == 1 ) a->z += v;
		//	if ( touche[2] == 2 ) a->z -= v;

		//	camera->vision.x = ( float )-cos( a->x );
		//	camera->vision.z = ( float )sin( a->x );
		//	if ( touche[3] == 1 )
		//	{
		//		p->x += camera->vision.x*vit;
		//		p->z += camera->vision.z*vit;
		//	}

		//	if ( touche[3] == 2 )
		//	{
		//		p->x -= camera->vision.x*vit;
		//		p->z -= camera->vision.z*vit;
		//	}

		//	if ( touche[4] == 1 )
		//	{
		//		camera->vision.x = ( float )cos( a->x - PI / 2 );
		//		camera->vision.z = ( float )-sin( a->x - PI / 2 );
		//		p->x += camera->vision.x*vit;
		//		p->z += camera->vision.z*vit;
		//	}

		//	if ( touche[4] == 2 )
		//	{
		//		camera->vision.x = ( float )cos( a->x - PI / 2 );
		//		camera->vision.z = ( float )-sin( a->x - PI / 2 );
		//		p->x -= camera->vision.x*vit;
		//		p->z -= camera->vision.z*vit;
		//	}

		//	camera->position.x = ( float )( cos( a->x )*sin( a->y ) );
		//	camera->position.y = ( float )cos( a->y );
		//	camera->position.z = ( float )( -sin( a->x )*sin( a->y ) );

		//	camera->position.x = ( camera->position.x*a->z ) + p->x;
		//	camera->position.y = ( camera->position.y*a->z ) + p->y;
		//	camera->position.z = ( camera->position.z*a->z ) + p->z;

		//	camera->vision.x = p->x - camera->position.x;
		//	camera->vision.y = p->y - camera->position.y;
		//	camera->vision.z = p->z - camera->position.z;

		//	if ( touche[4] == 2 )
		//		a->x -= v;

		//	if ( touche[4] == 1 )
		//		a->x += v;
		//}
	}
}
