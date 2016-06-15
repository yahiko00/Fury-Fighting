#pragma once

#include "IndexBuffer.h"
#include "NormalBuffer.h"
#include "VertexBuffer.h"

namespace LMP3D
{
	namespace Graphics
	{
		class Mesh
		{
		public:
			Mesh();
			~Mesh()noexcept;

			virtual bool draw()const = 0;

		protected:
			VertexBuffer m_vertex;
			NormalBuffer m_normal;
			std::vector< IndexBuffer > m_indices;
		};
	}
}
