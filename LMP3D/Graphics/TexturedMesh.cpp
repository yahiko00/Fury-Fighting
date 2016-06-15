#include "TexturedMesh.h"

namespace LMP3D
{
	namespace Graphics
	{
		TexturedMesh::TexturedMesh()
		{
		}

		TexturedMesh::~TexturedMesh()noexcept
		{
		}

		bool TexturedMesh::draw()const
		{
			bool l_return{ m_vertex.bind() && m_normal.bind() && m_texcoord.bind() };

			if ( l_return )
			{
				for ( auto const & index : m_indices )
				{
					glDrawElements( GL_TRIANGLES, index.getCount(), GL_UNSIGNED_SHORT, index.getData() );
					l_return &= checkGlError( "glDrawArrays" );
				}
			}

			return l_return;
		}
	}
}
