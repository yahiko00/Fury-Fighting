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
				Constructor from specified values.
			@param[in] x,y,z,w
				The values.
			*/
			inline Quaternion( float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f )
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
				Sets this quaternion from axis and angle.
			@param[in] axis
				The axis.
			@param[in] angle
				The angle.
			*/
			inline void fromAxisAngle( Vector3 const & axis, float angle )
			{
				float const h = angle * 0.5f;
				float const s = sin( h * 0.5f );
				w = cos( h * 0.5f );
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
				Computes the magnitude (norm) of the quaternion.
			@return
				The magnitude.
			*/
			inline float getMagnitude()const
			{
				return sqrt( x * x + y * y + z * z + w * w );
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
			Converts degrees to radians.
		@param[in] degrees
			The angle in degrees.
		*/
		inline float radians( float degrees )
		{
			static double const pi = 3.1415926535897932384626433832795028841968;
			return float( degrees * pi / 180.0 );
		}
		/**
		@brief
			Normalises a quaternion.
		@param[in,out] quat
			The quaternion to normalise.
		*/
		inline void normalise( Quaternion & quat )
		{
			float norm = quat.getMagnitude();

			if ( norm != 0 )
			{
				quat.x /= norm;
				quat.y /= norm;
				quat.z /= norm;
				quat.w /= norm;
			}
		}
	}
}

#endif
