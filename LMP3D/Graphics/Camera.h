#ifndef ___LPM3D_Graphics_Camera_H___
#define ___LPM3D_Graphics_Camera_H___

#include "Vector.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			Camera management class.
		*/
		class Camera
		{
		public:
			/**
			@brief
				Constructor.
			*/
			Camera();
			/**
			@brief
				Destructor.
			*/
			~Camera();
			/**
			@brief
				Applies camera's transformations.
			*/
			bool apply()const;
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
				Rotates the camera by given axis and angle.
			@param[in] angle
				The rotation angle.
			@param[in] x, y, z
				The rotation axis.
			*/
			void rotate( float angle, float x, float y, float z )
			{
			}
			/**
			@brief
				Rotates the camera by given axis and angle.
			@param[in] angle
				The rotation angle.
			@param[in] axis
				The rotation axis.
			*/
			inline void rotate( float angle, Vector3 const & axis )
			{
				rotate( angle, axis.x, axis.y, axis.z );
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

		private:
			Vector3 m_position;
			Vector3 m_lookAt;
			Vector3 m_up;
		};
	}
}

#endif
