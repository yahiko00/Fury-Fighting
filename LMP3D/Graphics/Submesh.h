#ifndef ___LMP3D_Graphics_Submesh_H___
#define ___LMP3D_Graphics_Submesh_H___

#include "NormalBuffer.h"
#include "TexCoordBuffer.h"
#include "VertexBuffer.h"
#include "Material.h"

namespace LMP3D
{
	namespace Graphics
	{
		class Submesh
		{
		public:
			Submesh( MaterialPtr material, Vector3Array const & vtx, Vector3Array const & nml, Vector2Array const & tex = Vector2Array() );
			~Submesh()throw();

			void draw()const;

		protected:
			VertexBuffer m_vertex;
			NormalBuffer m_normal;
			TexCoordBuffer m_texcoord;
			MaterialPtr m_material;
		};
	}
}

#endif
