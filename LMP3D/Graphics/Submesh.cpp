#include "Submesh.h"

namespace LMP3D
{
	namespace Graphics
	{
		Submesh::Submesh( MaterialPtr material, Vector3Array const & vtx, Vector3Array const & nml, Vector2Array const & tex )
			: m_material( material )
			, m_vertex( vtx )
			, m_normal( nml )
			, m_texcoord( tex )
		{
		}

		Submesh::~Submesh()throw()
		{
		}

		void Submesh::draw()const
		{
			assert( m_material && "No material for submesh" );

			if ( m_material->bind() && m_vertex.bind() && m_normal.bind() && m_texcoord.bind() )
			{
				glDrawArrays( GL_TRIANGLES, 0, m_vertex.getCount()  );
				checkGlError( "glDrawElements" );
				m_vertex.unbind();
				m_normal.unbind();
				m_texcoord.unbind();
				m_material->unbind();
			}
		}
	}
}
