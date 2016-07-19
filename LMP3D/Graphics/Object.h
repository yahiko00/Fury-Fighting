#ifndef ___LMP3D_Graphics_Object_H___
#define ___LMP3D_Graphics_Object_H___

#include "Quaternion.h"

namespace LMP3D
{
	namespace Graphics
	{
		class Object
		{
		public:
			Object( Scene & scene, MeshArray const & meshes, MaterialArray const & materials );
			~Object();

			ObjectPtr clone()const;

			inline void setOrientation( Quaternion const & value )
			{
				m_orientation = value;
			}

			inline void moveTo( Vector3 const & value )
			{
				m_position = value;
			}

			inline void moveTo( float x, float y, float z )
			{
				m_position.x = x;
				m_position.y = y;
				m_position.z = z;
			}

			inline void setScale( Vector3 const & value )
			{
				m_scale = value;
			}

			inline void setScale( float x, float y, float z )
			{
				m_scale.x = x;
				m_scale.y = y;
				m_scale.z = z;
			}

			inline void rotate( Quaternion const & value )
			{
				m_orientation *= value;
			}

			inline void scale( Vector3 const & value )
			{
				m_scale *= value;
			}

			inline void scale( float x, float y, float z )
			{
				m_scale.x *= x;
				m_scale.y *= y;
				m_scale.z *= z;
			}

			inline void translate( Vector3 const & value )
			{
				m_position += value;
			}

			inline void translate( float x, float y, float z )
			{
				m_position.x += x;
				m_position.y += y;
				m_position.z += z;
			}

			inline Vector3 const & getPosition()const
			{
				return m_position;
			}

			inline Quaternion const & getOrientation()const
			{
				return m_orientation;
			}

			inline Vector3 const & getScale()const
			{
				return m_scale;
			}

			inline MeshArray const & getMeshes()const
			{
				return m_meshes;
			}

			inline MaterialArray const & getMaterials()const
			{
				return m_materials;
			}

		private:
			Quaternion m_orientation;
			Vector3 m_position;
			Vector3 m_scale;
			MeshArray m_meshes;
			MaterialArray m_materials;
			Scene & m_scene;
		};
	}
}

#endif
