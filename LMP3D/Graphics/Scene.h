#ifndef ___LMP3D_Graphics_Scene_H___
#define ___LMP3D_Graphics_Scene_H___

#include "Material.h"
#include "Mesh.h"
#include "ElementsList.h"
#include "Camera.h"
#include "Texture.h"

namespace LMP3D
{
	namespace Graphics
	{
		class Scene
		{
		public:
			Scene();
			~Scene();

			void draw()const;

			void addObject( MeshArray const & meshes, MaterialArray const & materials );

			inline Camera & getCamera()
			{
				return m_camera;
			}

			inline Camera const & getCamera()const
			{
				return m_camera;
			}

			inline MaterialsList & getMaterials()
			{
				return m_materials;
			}

			inline MaterialsList const & getMaterials()const
			{
				return m_materials;
			}

			inline MeshesList & getMeshes()
			{
				return m_meshes;
			}

			inline MeshesList const & getMeshes()const
			{
				return m_meshes;
			}

			inline TexturesList & getTextures()
			{
				return m_textures;
			}

			inline TexturesList const & getTextures()const
			{
				return m_textures;
			}

		private:
			struct ObjectMesh
			{
				MeshPtr m_mesh;
				MaterialPtr m_material;
				ObjectPtr m_object;
			};
			typedef std::vector< ObjectMesh > ObjectMeshArray;

		private:
			MaterialsList m_materials;
			MeshesList m_meshes;
			TexturesList m_textures;
			ObjectList m_objects;
			ObjectMeshArray m_opaqueObjects;
			ObjectMeshArray m_transparentObjects;
			Camera m_camera;
		};
	}
}

#endif
