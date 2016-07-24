#ifndef ___LMP3D_Graphics_Vector_H___
#define ___LMP3D_Graphics_Vector_H___

#include "GraphicsCommon.h"

#include <cmath>

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			Two dimensions vector.
		*/
		struct Vector2
		{
			/**
			@brief
				Constructor.
			*/
			Vector2( float x = 0.0f, float y = 0.0f )
				: x( x )
				, y( y )
			{
			}
			/**
			@brief
				Addition assignment operator.
			@param[in] rhs
				The other element.
			@return
				A reference to this object.
			*/
			inline Vector2 & operator+=( Vector2 const & rhs )
			{
				x += rhs.x;
				y += rhs.y;
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
			inline Vector2 & operator-=( Vector2 const & rhs )
			{
				x -= rhs.x;
				y -= rhs.y;
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
			inline Vector2 & operator*=( float rhs )
			{
				x *= rhs;
				y *= rhs;
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
			inline Vector2 & operator/=( float rhs )
			{
				x /= rhs;
				y /= rhs;
				return *this;
			}

			float x;
			float y;
		};
		/**
		@brief
			Addition operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Vector2 operator+( Vector2 const & lhs, Vector2 const & rhs )
		{
			Vector2 result( lhs );
			return result += rhs;
		}
		/**
		@brief
			Subtraction operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Vector2 operator-( Vector2 const & lhs, Vector2 const & rhs )
		{
			Vector2 result( lhs );
			return result -= rhs;
		}
		/**
		@brief
			Multiplication operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Vector2 operator*( Vector2 const & lhs, float rhs )
		{
			Vector2 result( lhs );
			return result *= rhs;
		}
		/**
		@brief
			Division operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Vector2 operator/( Vector2 const & lhs, float rhs )
		{
			Vector2 result( lhs );
			return result /= rhs;
		}
		/**
		@brief
			Multiplication operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Vector2 operator*( float lhs, Vector2 const & rhs )
		{
			Vector2 result( rhs );
			return result *= lhs;
		}
		/**
		@brief
			Division operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Vector2 operator/( float lhs, Vector2 const & rhs )
		{
			Vector2 result( rhs );
			return result /= lhs;
		}
		/**
		@brief
			Computes the dot product of two vectors.
		@param[in] lhs, rhs
			The operands.
		@return
			The dot product.
		*/
		inline float dot( Vector2 const & lhs, Vector2 const & rhs )
		{
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}
		/**
		@brief
			Computes the euclidian length of a vector.
		@param[in] vec
			The vector.
		@return
			The vector's length.
		*/
		inline float length( Vector2 const & vec )
		{
			return sqrt( dot( vec, vec ) );
		}
		/**
		@brief
			Normalises a vector.
		@param[in,out] vec
			The vector to normalise.
		*/
		inline void normalise( Vector2 & vec )
		{
			float norm = length( vec );

			if ( std::abs( norm ) >= 0.000001 )
			{
				vec.x /= norm;
				vec.y /= norm;
			}
		}
		/**
		@brief
			Three dimensions vector.
		*/
		struct Vector3
		{
			/**
			@brief
				Constructor.
			*/
			Vector3( float x = 0.0f, float y = 0.0f, float z = 0.0f )
				: x( x )
				, y( y )
				, z( z )
			{
			}
			/**
			@brief
				Addition assignment operator.
			@param[in] rhs
				The other element.
			@return
				A reference to this object.
			*/
			inline Vector3 & operator+=( Vector3 const & rhs )
			{
				x += rhs.x;
				y += rhs.y;
				z += rhs.z;
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
			inline Vector3 & operator-=( Vector3 const & rhs )
			{
				x -= rhs.x;
				y -= rhs.y;
				z -= rhs.z;
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
			inline Vector3 & operator*=( float rhs )
			{
				x *= rhs;
				y *= rhs;
				z *= rhs;
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
			inline Vector3 & operator/=( float rhs )
			{
				x /= rhs;
				y /= rhs;
				z /= rhs;
				return *this;
			}

			float x;
			float y;
			float z;
		};
		/**
		@brief
			Addition operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Vector3 operator+( Vector3 const & lhs, Vector3 const & rhs )
		{
			Vector3 result( lhs );
			return result += rhs;
		}
		/**
		@brief
			Subtraction operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Vector3 operator-( Vector3 const & lhs, Vector3 const & rhs )
		{
			Vector3 result( lhs );
			return result -= rhs;
		}
		/**
		@brief
			Multiplication operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Vector3 operator*( Vector3 const & lhs, float rhs )
		{
			Vector3 result( lhs );
			return result *= rhs;
		}
		/**
		@brief
			Division operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Vector3 operator/( Vector3 const & lhs, float rhs )
		{
			Vector3 result( lhs );
			return result /= rhs;
		}
		/**
		@brief
			Multiplication operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Vector3 operator*( float lhs, Vector3 const & rhs )
		{
			Vector3 result( rhs );
			return result *= lhs;
		}
		/**
		@brief
			Division operator.
		@param[in] lhs, rhs
			The operands.
		*/
		inline Vector3 operator/( float lhs, Vector3 const & rhs )
		{
			Vector3 result( rhs );
			return result /= lhs;
		}
		/**
		@brief
			Computes the dot product of two vectors.
		@param[in] lhs, rhs
			The operands.
		@return
			The dot product.
		*/
		inline float dot( Vector3 const & lhs, Vector3 const & rhs )
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
		}
		/**
		@brief
			Computes the cross product of two vectors.
		@param[in] lhs, rhs
			The operands.
		@return
			The cross product.
		*/
		inline Vector3 cross( Vector3 const & lhs, Vector3 const & rhs )
		{
			return Vector3(
				( lhs.y * rhs.z ) - ( lhs.z * rhs.y ),
				( lhs.z * rhs.x ) - ( lhs.x * rhs.z ),
				( lhs.x * rhs.y ) - ( lhs.y * rhs.x )
			);
		}
		/**
		@brief
			Computes the euclidian length of a vector.
		@param[in] vec
			The vector.
		@return
			The vector's length.
		*/
		inline float length( Vector3 const & vec )
		{
			return sqrt( dot( vec, vec) );
		}
		/**
		@brief
			Normalises a vector.
		@param[in,out] vec
			The vector to normalise.
		*/
		inline void normalise( Vector3 & vec )
		{
			float norm = length( vec );

			if ( std::abs( norm ) >= 0.000001 )
			{
				vec.x /= norm;
				vec.y /= norm;
				vec.z /= norm;
			}
		}
	}
}

#endif
