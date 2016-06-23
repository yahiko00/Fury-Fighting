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

			Object & addObject( std::string const & name, MeshArray const & meshes, MaterialArray const & materials );

			inline Camera & getCamera()
			{
				return m_camera;
			}

			inline Camera const & getCamera()const
			{
				return m_camera;
			}

			inline ObjectList const & getObjects()const
			{
				return m_objects;
			}

			inline ObjectList & getObjects()
			{
				return m_objects;
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
			ObjectList m_objects;
			ObjectMeshArray m_opaqueObjects;
			ObjectMeshArray m_transparentObjects;
			Camera m_camera;
		};
	}
}

#endif
