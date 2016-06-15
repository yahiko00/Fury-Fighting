#pragma once

#include "Mesh.h"
#include "TexCoordBuffer.h"

namespace LMP3D
{
	namespace Graphics
	{
		class TexturedMesh
			: public Mesh
		{
		public:
			TexturedMesh();
			~TexturedMesh()noexcept;

			bool draw()const override;

			inline void setData( Vector3Array && vertex, Vector3Array && normal, Vector2Array && texcoord, std::vector< FaceArray > && faces )
			{
				m_vertex.setData( std::move( vertex ) );
				m_normal.setData( std::move( normal ) );
				m_texcoord.setData( std::move( texcoord ) );
				m_indices.resize( faces.size() );

				for ( size_t i = 0; i < faces.size(); ++i )
				{
					m_indices[i].setData( std::move( faces[i] ) );
				}
			}

		private:
			TexCoordBuffer m_texcoord;
		};
	}
}
