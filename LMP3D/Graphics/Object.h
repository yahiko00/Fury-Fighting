#ifndef ___LMP3D_Graphics_Object_H___
#define ___LMP3D_Graphics_Object_H___

#include "Quaternion.h"
#include "Vector.h"

namespace LMP3D
{
	namespace Graphics
	{
		class Object
		{
		public:
			explicit Object( std::string const & name, MeshArray const & meshes, MaterialArray const & materials );
			~Object();

			void draw()const;

			inline Vector3 const & getPosition()const
			{
				return m_position;
			}

			inline Quaternion const & getOrientation()const
			{
				return m_orientation;
			}

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

			inline void rotate( Quaternion const & value )
			{
				m_orientation *= value;
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

		private:
			std::string const m_name;
			Quaternion m_orientation;
			Vector3 m_position;
			MeshArray m_meshes;
			MaterialArray m_materials;
		};
	}
}

#endif
