#ifndef ___LMP3D_GRAPHICS_QUATERNION_H___
#define ___LMP3D_GRAPHICS_QUATERNION_H___

#include "Vector.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			Normalises a quaternion.
		@param[in,out] quat
			The quaternion to normalise.
		*/
		inline void normalise( Quaternion & quat );
		/**
		@brief
			Quaternion class.
		*/
		class Quaternion
		{
		public:
			/**
			@brief
				Default constructor.
			*/
			inline Quaternion()
				: x( 0.0f )
				, y( 0.0f )
				, z( 0.0f )
				, w( 1.0f )
			{
			}
			/**
			@brief
				Constructor from specified values.
			@param[in] x,y,z,w
				The values.
			*/
			inline Quaternion( float x, float y, float z, float w )
				: x( x )
				, y( y )
				, z( z )
				, w( w )
			{
				normalise( *this );
			}
			/**
			@brief
				Constructor from axis and angle.
			@param[in] axis
				The axis.
			@param[in] angle
				The angle.
			*/
			inline Quaternion( Vector3 const & axis, float angle )
			{
				fromAxisAngle( axis, angle );
			}
			/**
			@brief
				Constructor from axis and angle.
			@param[in] axis
				The axis.
			@param[in] angle
				The angle.
			*/
			inline Quaternion( float pitch, float yaw, float roll )
			{
				fromEulerAngles( pitch, yaw, roll );
			}
			/**
			@brief
				Sets this quaternion from axis and angle.
			@param[in] axis
				The axis.
			@param[in] angle
				The angle.
			*/
			inline void fromAxisAngle( Vector3 const & axis, float angle )
			{
				float const h = angle * 0.5f;
				float const s = sin( h );
				w = cos( h );
				x = axis.x * s;
				y = axis.y * s;
				z = axis.z * s;
				normalise( *this );
			}
			/**
			@brief
				Retrieves axis and angle from this quaternion.
			@param[out] axis
				The axis.
			@param[out] angle
				The angle.
			*/
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
			/**
			@brief
				Sets this quaternion from Euler angles.
			@param[in] pitch, yaw, roll
				The angles.
			*/
			inline void fromEulerAngles( float pitch, float yaw, float roll )
			{
				pitch *= 0.5f;
				yaw *= 0.5f;
				roll *= 0.5f;
				float cp = cos( pitch );
				float cy = cos( yaw );
				float cr = cos( roll );
				float sp = sin( pitch );
				float sy = sin( yaw );
				float sr = sin( roll );

				w = cp * cr * cr + sp * sy * sr;
				x = sp * cr * cr - cp * sy * sr;
				y = cp * sr * cr + sp * cy * sr;
				z = cp * cr * sr - sp * sy * cr;

				//w = ( cy * cr * cp ) - ( sy * sr * sp );
				//x = ( sy * sr * cp ) + ( cy * cr * sp );
				//y = ( sy * cr * cp ) + ( cy * sr * sp );
				//z = ( cy * sr * cp ) - ( sy * cr * sp );
			}
			/**
			@brief
				Retrieves Euler angles from this quaternion.
			@param[out] pitch, yaw, roll
				Receive the angles.
			*/
			inline void toEulerAngles( float & pitch, float & yaw, float & roll )const
			{
				roll = float( atan2( 2.0f * ( x * y + w * z ), w * w + x * x - y * y - z * z ) );
				pitch = float( atan2( 2.0f * ( y * z + w * x ), w * w - x * x - y * y + z * z ) );
				yaw = asin( -2.0f * ( x * z - w * y ) );
			}
			/**
			@brief
				Retrieves a rotation matrix from this quaternion.
			@param[out] matrix
				Receive the rotation matrix.
			*/
			inline void toMatrix( float * matrix )const
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

				matrix[0] = ( 1 - 2 * ( qyy + qzz ) );
				matrix[1] = ( 2 * ( qxy + qwz ) );
				matrix[2] = ( 2 * ( qxz - qwy ) );
				matrix[3] = 0;

				matrix[4] = ( 2 * ( qxy - qwz ) );
				matrix[5] = ( 1 - 2 * ( qxx + qzz ) );
				matrix[6] = ( 2 * ( qyz + qwx ) );
				matrix[7] = 0;

				matrix[8] = ( 2 * ( qxz + qwy ) );
				matrix[9] = ( 2 * ( qyz - qwx ) );
				matrix[10] = ( 1 - 2 * ( qxx + qyy ) );
				matrix[11] = 0;

				matrix[12] = 0;
				matrix[13] = 0;
				matrix[14] = 0;
				matrix[15] = 1;
			}
			/**
			@brief
				Retrieves the coordinate system described by this quaternion.
			@param[out] p_x, p_y, p_z
				Receive the coordinate system.
			*/
			inline void toAxes( Vector3 & p_x, Vector3 & p_y, Vector3 & p_z )const
			{
				float matrix[16];
				toMatrix( matrix );
				p_x = Vector3( matrix[0], matrix[4], matrix[8] );
				p_y = Vector3( matrix[1], matrix[5], matrix[9] );
				p_z = Vector3( matrix[2], matrix[6], matrix[10] );
			}
			/**
			@brief
				Addition assignment operator.
			@param[in] rhs
				The other element.
			@return
				A reference to this object.
			*/
			inline Quaternion & operator+=( Quaternion const & rhs )
			{
				x += rhs.x;
				y += rhs.y;
				z += rhs.z;
				w += rhs.w;
				normalise( *this );
				return *this;
			}
			/**
			@brief
				Subtraction assignment operator.
			@param[in] rhs
				The other element.
			@return
				A reference to this object.
			*/
			inline Quaternion & operator-=( Quaternion const & rhs )
			{
				x -= rhs.x;
				y -= rhs.y;
				z -= rhs.z;
				w -= rhs.w;
				normalise( *this );
				return *this;
			}
			/**
			@brief
				Multiplication assignment operator.
			@param[in] rhs
				The other element.
			@return
				A reference to this object.
			*/
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
			/**
			@brief
				Multiplication assignment operator.
			@param[in] rhs
				The scalar.
			@return
				A reference to this object.
			*/
			inline Quaternion & operator*=( float p_rhs )
			{
				x *= p_rhs;
				y *= p_rhs;
				z *= p_rhs;
				w *= p_rhs;
				normalise( *this );
				return *this;
			}
			/**
			@brief
				Division assignment operator.
			@param[in] rhs
				The scalar.
			@return
				A reference to this object.
			*/
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
		/**
		@brief
			Addition operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Quaternion operator+( Quaternion const & lhs, Quaternion const & rhs )
		{
			Quaternion l_return( lhs );
			l_return += rhs;
			return l_return;
		}
		/**
		@brief
			Subtraction operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Quaternion operator-( Quaternion const & lhs, Quaternion const & rhs )
		{
			Quaternion l_return( lhs );
			l_return -= rhs;
			return l_return;
		}
		/**
		@brief
			Multiplication operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Quaternion operator*( Quaternion const & lhs, Quaternion const & rhs )
		{
			Quaternion l_return( lhs );
			l_return *= rhs;
			return l_return;
		}
		/**
		@brief
			Multiplication operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Quaternion operator*( Quaternion const & lhs, float rhs )
		{
			Quaternion l_return( lhs );
			l_return *= rhs;
			return l_return;
		}
		/**
		@brief
			Multiplication operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Quaternion operator*( float lhs, Quaternion const & rhs )
		{
			Quaternion l_return( rhs );
			l_return *= lhs;
			return l_return;
		}
		/**
		@brief
			Division operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Quaternion operator/( Quaternion const & lhs, float rhs )
		{
			Quaternion l_return( lhs );
			l_return /= rhs;
			return l_return;
		}
		/**
		@brief
			Negation operator.
		@param[in] q
			The operand.
		*/
		inline Quaternion operator-( Quaternion const & q )
		{
			Quaternion l_return( q );
			l_return.w = -l_return.w;
			return l_return;
		}
		/**
		@brief
			Computes the dot product of two quaternions.
		@return
			The dot product.
		*/
		inline float dot( Quaternion const & lhs, Quaternion const & rhs )
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
		}
		/**
		@brief
			Computes the cross product of two quaternions.
		@param[in] lhs, rhs
			The operands.
		@return
			The cross product.
		*/
		inline Quaternion cross( Quaternion const & lhs, Quaternion const & rhs )
		{
			return Quaternion(
				( lhs.w * rhs.x ) + ( lhs.x * rhs.w ) + ( lhs.y * rhs.z ) - ( lhs.z * rhs.y ),
				( lhs.w * rhs.y ) + ( lhs.y * rhs.w ) + ( lhs.z * rhs.x ) - ( lhs.x * rhs.z ),
				( lhs.w * rhs.z ) + ( lhs.z * rhs.w ) + ( lhs.x * rhs.y ) - ( lhs.y * rhs.x ),
				( lhs.w * rhs.w ) - ( lhs.x * rhs.x ) - ( lhs.y * rhs.y ) - ( lhs.z * rhs.z )
			);
		}
		/**
		@brief
			Computes the magnitude (norm) of the quaternion.
		@return
			The magnitude.
		*/
		inline float length( Quaternion const & quat )
		{
			return sqrt( dot( quat, quat ) );
		}
		/**
		@brief
			Normalises a quaternion.
		@param[in,out] quat
			The quaternion to normalise.
		*/
		inline void normalise( Quaternion & quat )
		{
			float norm = length( quat );

			if ( norm != 0 )
			{
				quat.x /= norm;
				quat.y /= norm;
				quat.z /= norm;
				quat.w /= norm;
			}
		}
		/**
		@brief
			Converts degrees to radians.
		@param[in] degrees
			The angle in degrees.
		*/
		inline float radians( float degrees )
		{
			static double const pi = 3.1415926535897932384626433832795028841968;
			return float( degrees * pi / 180.0 );
		}
	}
}

#endif
