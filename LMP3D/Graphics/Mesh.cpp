#include "Mesh.h"

#include "Platform.h"

namespace LMP3D
{
	namespace Graphics
	{
		Mesh::Mesh()
		{
		}

		Mesh::~Mesh()throw()
		{
		}

		void Mesh::setData( Vector3Array const & vtx, Vector3Array const & nml, Vector2Array const & tex )
		{
			m_vertex = VertexBuffer( vtx );
			m_normal = NormalBuffer( nml );
			m_texcoord = TexCoordBuffer( tex );
		}

		void Mesh::draw()const
		{
			if ( m_vertex.bind() && m_normal.bind() && m_texcoord.bind() )
			{
				Platform::Draw( m_vertex.getCount() );
				m_vertex.unbind();
				m_normal.unbind();
				m_texcoord.unbind();
			}
		}
	}
}
