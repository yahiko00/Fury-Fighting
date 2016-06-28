#ifndef ___LMP3D_GRAPHICS_QUATERNION_H___
#define ___LMP3D_GRAPHICS_QUATERNION_H___

#include "Vector.h"

namespace LMP3D
{
	namespace Graphics
	{
		inline void normalise( Quaternion & quat );

		class Quaternion
		{
		public:
			inline Quaternion()
				: x( 0 )
				, y( 0 )
				, z( 0 )
				, w( 1 )
			{
			}

			inline Quaternion( float x, float y, float z, float w )
				: x( x )
				, y( y )
				, z( z )
				, w( w )
			{
				normalise( *this );
			}

			inline Quaternion( Vector3 const & vector, float angle )
			{
				fromAxisAngle( vector, angle );
			}

			inline void fromAxisAngle( Vector3 const & vector, float angle )
			{
				float const h = angle * 0.5f;
				float const s = sin( h * 0.5f );
				w = cos( h * 0.5f );
				x = vector.x * s;
				y = vector.y * s;
				z = vector.z * s;
				normalise( *this );
			}

			inline void toAxisAngle( Vector3 & vector, float & angle )const
			{
				angle = 2.0f * acos( w );
				float tmp = 1.0f - w * w;

				if ( tmp <= 0.0f )
				{
					vector.x = 0;
					vector.y = 0;
					vector.z = 1;
				}
				else
				{
					tmp = 1.0f / sqrt( tmp );
					vector.x = x * tmp;
					vector.y = y * tmp;
					vector.z = z * tmp;
				}
			}

			inline void toMatrix( float matrix[16] )const
			{
				float const qxx( x * x );
				float const qyy( y * y );
				float const qzz( z * z );
				float const qxz( x * z );
				float const qxy( x * y );
				float const qyz( y * z );
				float const qwx( w * x );
				float const qwy( w * y );
				float const qwz( w * z );
				matrix[0] = 1 - 2 * ( qyy + qzz );
				matrix[1] = 2 * ( qxy + qwz );
				matrix[2] = 2 * ( qxz - qwy );
				matrix[3] = 0;

				matrix[4] = 2 * ( qxy - qwz );
				matrix[5] = 1 - 2 * ( qxx + qzz );
				matrix[6] = 2 * ( qyz + qwx );
				matrix[7] = 0;

				matrix[8] = 2 * ( qxz + qwy );
				matrix[9] = 2 * ( qyz - qwx );
				matrix[10] = 1 - 2 * ( qxx + qyy );
				matrix[11] = 0;

				matrix[12] = 0;
				matrix[13] = 0;
				matrix[14] = 0;
				matrix[15] = 1;
			}

			inline float getMagnitude()const
			{
				return sqrt( x * x + y * y + z * z + w * w );
			}

			inline Quaternion & operator+=( Quaternion const & rhs )
			{
				x += rhs.x;
				y += rhs.y;
				z += rhs.z;
				w += rhs.w;
				normalise( *this );
				return *this;
			}

			inline Quaternion & operator-=( Quaternion const & rhs )
			{
				x -= rhs.x;
				y -= rhs.y;
				z -= rhs.z;
				w -= rhs.w;
				normalise( *this );
				return *this;
			}

			inline Quaternion & operator*=( Quaternion const & rhs )
			{
				float const tmpx = x;
				float const tmpy = y;
				float const tmpz = z;
				float const tmpw = w;
				x = tmpw * rhs.x + tmpx * rhs.w + tmpy * rhs.z - tmpz * rhs.y;
				y = tmpw * rhs.y + tmpy * rhs.w + tmpz * rhs.x - tmpx * rhs.z;
				z = tmpw * rhs.z + tmpz * rhs.w + tmpx * rhs.y - tmpy * rhs.x;
				w = tmpw * rhs.w - tmpx * rhs.x - tmpy * rhs.y - tmpz * rhs.z;
				normalise( *this );
				return *this;
			}

			inline Quaternion & operator*=( float p_rhs )
			{
				x *= p_rhs;
				y *= p_rhs;
				z *= p_rhs;
				w *= p_rhs;
				normalise( *this );
				return *this;
			}

			inline Quaternion & operator/=( float p_rhs )
			{
				x /= p_rhs;
				y /= p_rhs;
				z /= p_rhs;
				w /= p_rhs;
				normalise( *this );
				return *this;
			}

		public:
			float x;
			float y;
			float z;
			float w;
		};

		inline Quaternion operator+( Quaternion const & lhs, Quaternion const & rhs )
		{
			Quaternion l_return( lhs );
			l_return += rhs;
			return l_return;
		}

		inline Quaternion operator-( Quaternion const & lhs, Quaternion const & rhs )
		{
			Quaternion l_return( lhs );
			l_return -= rhs;
			return l_return;
		}

		inline Quaternion operator*( Quaternion const & lhs, Quaternion const & rhs )
		{
			Quaternion l_return( lhs );
			l_return *= rhs;
			return l_return;
		}

		inline Quaternion operator*( Quaternion const & lhs, float rhs )
		{
			Quaternion l_return( lhs );
			l_return *= rhs;
			return l_return;
		}

		inline Quaternion operator*( float lhs, Quaternion const & rhs )
		{
			Quaternion l_return( rhs );
			l_return *= lhs;
			return l_return;
		}

		inline Quaternion operator/( Quaternion const & lhs, float rhs )
		{
			Quaternion l_return( lhs );
			l_return /= rhs;
			return l_return;
		}

		inline Quaternion operator-( Quaternion const & q )
		{
			Quaternion l_return( q );
			l_return.w = -l_return.w;
			return l_return;
		}

		inline float radians( float degrees )
		{
			static double const pi = 3.1415926535897932384626433832795028841968;
			return float( degrees * pi / 180.0 );
		}

		inline void normalise( Quaternion & quat )
		{
			float length = quat.getMagnitude();

			if ( length != 0 )
			{
				quat.x /= length;
				quat.y /= length;
				quat.z /= length;
				quat.w /= length;
			}
		}
	}
}

#endif
