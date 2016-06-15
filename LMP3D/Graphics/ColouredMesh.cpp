#include "ColouredMesh.h"

namespace LMP3D
{
	namespace Graphics
	{
		ColouredMesh::ColouredMesh()
		{
		}

		ColouredMesh::~ColouredMesh()noexcept
		{
		}

		bool ColouredMesh::draw()const
		{
			bool l_return{ m_vertex.bind() && m_normal.bind() && m_colour.bind() };

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
