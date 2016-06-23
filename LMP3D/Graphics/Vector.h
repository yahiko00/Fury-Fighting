#ifndef ___LMP3D_Graphics_Vector_H___
#define ___LMP3D_Graphics_Vector_H___

#include "Common.h"

#include <cmath>

namespace LMP3D
{
	namespace Graphics
	{
		struct Vector2
		{
			float x;
			float y;

			Vector2( float x = 0.0f, float y = 0.0f )
				: x( x )
				, y( y )
			{
			}

			inline Vector2 & operator+=( Vector2 const & rhs )
			{
				x += rhs.x;
				y += rhs.y;
				return *this;
			}

			inline Vector2 & operator-=( Vector2 const & rhs )
			{
				x -= rhs.x;
				y -= rhs.y;
				return *this;
			}

			inline Vector2 & operator*=( float rhs )
			{
				x *= rhs;
				y *= rhs;
				return *this;
			}

			inline Vector2 & operator/=( float rhs )
			{
				x /= rhs;
				y /= rhs;
				return *this;
			}
		};

		inline Vector2 operator+( Vector2 const & lhs, Vector2 const & rhs )
		{
			Vector2 result( lhs );
			return result += rhs;
		}

		inline Vector2 operator-( Vector2 const & lhs, Vector2 const & rhs )
		{
			Vector2 result( lhs );
			return result -= rhs;
		}

		inline Vector2 operator*( Vector2 const & lhs, float rhs )
		{
			Vector2 result( lhs );
			return result *= rhs;
		}

		inline Vector2 operator/( Vector2 const & lhs, float rhs )
		{
			Vector2 result( lhs );
			return result /= rhs;
		}

		inline Vector2 operator*( float lhs, Vector2 const & rhs )
		{
			Vector2 result( rhs );
			return result *= lhs;
		}

		inline Vector2 operator/( float lhs, Vector2 const & rhs )
		{
			Vector2 result( rhs );
			return result /= lhs;
		}

		inline float length( Vector2 const & vec )
		{
			return sqrt( vec.x * vec.x + vec.y * vec.y );
		}

		inline float dot( Vector2 const & lhs, Vector2 const & rhs )
		{
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		struct Vector3
		{
			float x;
			float y;
			float z;

			Vector3( float x = 0.0f, float y = 0.0f, float z = 0.0f )
				: x( x )
				, y( y )
				, z( z )
			{
			}

			inline Vector3 & operator+=( Vector3 const & rhs )
			{
				x += rhs.x;
				y += rhs.y;
				z += rhs.z;
				return *this;
			}

			inline Vector3 & operator-=( Vector3 const & rhs )
			{
				x -= rhs.x;
				y -= rhs.y;
				z -= rhs.z;
				return *this;
			}

			inline Vector3 & operator*=( float rhs )
			{
				x *= rhs;
				y *= rhs;
				z *= rhs;
				return *this;
			}

			inline Vector3 & operator/=( float rhs )
			{
				x /= rhs;
				y /= rhs;
				z /= rhs;
				return *this;
			}
		};

		inline Vector3 operator+( Vector3 const & lhs, Vector3 const & rhs )
		{
			Vector3 result( lhs );
			return result += rhs;
		}

		inline Vector3 operator-( Vector3 const & lhs, Vector3 const & rhs )
		{
			Vector3 result( lhs );
			return result -= rhs;
		}

		inline Vector3 operator*( Vector3 const & lhs, float rhs )
		{
			Vector3 result( lhs );
			return result *= rhs;
		}

		inline Vector3 operator/( Vector3 const & lhs, float rhs )
		{
			Vector3 result( lhs );
			return result /= rhs;
		}

		inline Vector3 operator*( float lhs, Vector3 const & rhs )
		{
			Vector3 result( rhs );
			return result *= lhs;
		}

		inline Vector3 operator/( float lhs, Vector3 const & rhs )
		{
			Vector3 result( rhs );
			return result /= lhs;
		}

		inline float length( Vector3 const & vec )
		{
			return sqrt( vec.x * vec.x + vec.y * vec.y + vec.z * vec.z );
		}

		inline float dot( Vector3 const & lhs, Vector3 const & rhs )
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
		}

		inline Vector3 cross( Vector3 const & lhs, Vector3 const & rhs )
		{
			return Vector3(
				( lhs.y * rhs.z ) - ( lhs.z * rhs.y ),
				( lhs.z * rhs.x ) - ( lhs.x * rhs.z ),
				( lhs.x * rhs.y ) - ( lhs.y * rhs.x )
			);
		}

		inline void normalise( Vector3 & vec )
		{
			float length = sqrt( dot( vec, vec ) );

			if ( length != 0 )
			{
				vec.x /= length;
				vec.y /= length;
				vec.z /= length;
			}
		}
	}
}

#endif
