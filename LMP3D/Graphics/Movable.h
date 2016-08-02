#ifndef ___LPM3D_Graphics_Movable_H___
#define ___LPM3D_Graphics_Movable_H___

#include "Quaternion.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			Movable management class.
		@remarks
			A movable is something than can move and rotate.
		*/
		class Movable
		{
		public:
			/**
			@brief
				Constructor.
			*/
			Movable()
			{
			}
			/**
			@brief
				Destructor.
			*/
			~Movable()
			{
			}
			/**
			@brief
				Sets the object orientation.
			@param[in] value
				The new orientation.
			*/
			inline void setOrientation( Quaternion const & value )
			{
				m_orientation = value;
			}
			/**
			@brief
				Moves the camera to given position.
			@param[in] value
				The new position.
			*/
			inline void moveTo( Vector3 const & value )
			{
				m_position = value;
			}
			/**
			@brief
				Moves the camera to given position.
			@param[in] x,y,z
				The new position.
			*/
			inline void moveTo( float x, float y, float z )
			{
				m_position.x = x;
				m_position.y = y;
				m_position.z = z;
			}
			/**
			@brief
				Rotates the object using a quaternion.
			@param[in] value
				The orientation.
			*/
			inline void rotate( Quaternion const & value )
			{
				m_orientation *= value;
			}
			/**
			@brief
				Rotates the object using Euler angles.
			@param[in] value
				The orientation.
			*/
			inline void rotate( float x, float y, float z )
			{
				m_orientation *= Quaternion( x, y, z );
			}
			/**
			@brief
				Translates the camera by given vector.
			@param[in] value
				The translation vector.
			*/
			inline void translate( Vector3 const & value )
			{
				m_position += value;
			}
			/**
			@brief
				Translates the camera by given vector.
			@param[in] x,y,z
				The translation vector.
			*/
			inline void translate( float x, float y, float z )
			{
				m_position.x += x;
				m_position.y += y;
				m_position.z += z;
			}
			/**
			@return
				The object's position.
			*/
			inline Vector3 const & getPosition()const
			{
				return m_position;
			}
			/**
			@return
				The object's orientation.
			*/
			inline Quaternion const & getOrientation()const
			{
				return m_orientation;
			}

		private:
			Quaternion m_orientation;
			Vector3 m_position;
		};
	}
}

#endif
