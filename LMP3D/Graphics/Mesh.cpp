#include "Mesh.h"

#include "Submesh.h"

namespace LMP3D
{
	namespace Graphics
	{
		Mesh::Mesh()
		{
		}

		Mesh::~Mesh()throw()
		{
			for ( SubmeshArray::iterator it = m_submeshes.begin(); it != m_submeshes.end(); ++it )
			{
				delete ( *it );
			}
		}

		void Mesh::addSubmesh( MaterialPtr material, Vector3Array const & vtx, Vector3Array const & nml, Vector2Array const & tex )
		{
			m_submeshes.push_back( new Submesh( material,vtx, nml, tex ) );
		}

		void Mesh::draw()const
		{
			for ( SubmeshArray::const_iterator it = m_submeshes.begin(); it != m_submeshes.end(); ++it )
			{
				( *it )->draw();
			}
		}
	}
}
