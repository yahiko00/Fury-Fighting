#ifndef ___LMP3D_Graphics_Mesh_H___
#define ___LMP3D_Graphics_Mesh_H___

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		class Mesh
		{
		public:
			Mesh();
			~Mesh()throw();

			void addSubmesh( MaterialPtr material, Vector3Array const & vtx, Vector3Array const & nml, Vector2Array const & tex );

			void draw()const;

		protected:
			SubmeshArray m_submeshes;
		};
	}
}

#endif
