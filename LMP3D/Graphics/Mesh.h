#ifndef ___LMP3D_Graphics_Mesh_H___
#define ___LMP3D_Graphics_Mesh_H___

#include "NormalBuffer.h"
#include "TexCoordBuffer.h"
#include "VertexBuffer.h"
#include "Material.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			Holds an asset's data.
		*/
		class Mesh
		{
		public:
			/**
			@brief
				Constructor.
			*/
			Mesh();
			/**
			@brief
				Destructor.
			*/
			~Mesh()throw();
			/**
			@brief
				Sets the mesh's buffers' data.
			*/
			void setData( Vector3Array const & vtx, Vector3Array const & nml, Vector2Array const & tex = Vector2Array() );
			/**
			@brief
				Draws the mesh, using its buffers.
			*/
			void draw()const;

		private:
			VertexBuffer m_vertex;
			NormalBuffer m_normal;
			TexCoordBuffer m_texcoord;
		};
	}
}

#endif
