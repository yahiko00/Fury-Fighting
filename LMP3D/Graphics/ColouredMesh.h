#pragma once

#include "Mesh.h"
#include "ColourBuffer.h"

namespace LMP3D
{
	namespace Graphics
	{
		class ColouredMesh
			: public Mesh
		{
		public:
			ColouredMesh();
			~ColouredMesh()noexcept;

			bool draw()const override;

			inline void setData( Vector3Array && vertex, Vector3Array && normal, ColourArray && colour, std::vector< FaceArray > && faces )
			{
				m_vertex.setData( std::move( vertex ) );
				m_normal.setData( std::move( normal ) );
				m_colour.setData( std::move( colour ) );
				m_indices.resize( faces.size() );

				for ( size_t i = 0; i < faces.size(); ++i )
				{
					m_indices[i].setData( std::move( faces[i] ) );
				}
			}

		private:
			ColourBuffer m_colour;
		};
	}
}
