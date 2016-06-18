#ifndef ___LMP3D_Graphics_Object_H___
#define ___LMP3D_Graphics_Object_H___

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		class Object
		{
		public:
			explicit Object( MeshArray const & meshes, MaterialArray const & materials );
			~Object();

			void draw()const;

			Vector3 const & getPosition()const
			{
				return m_position;
			}

			float getAngle()const
			{
				return m_angle;
			}

			Vector3 const & getAxis()const
			{
				return m_axis;
			}

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
			float m_angle;
			Vector3 m_axis;
			Vector3 m_position;
			MeshArray m_meshes;
			MaterialArray m_materials;
		};
	}
}

#endif
