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
		struct ObjectMesh
		{
			MeshPtr m_mesh;
			MaterialPtr m_material;
			ObjectPtr m_object;
		};
		typedef std::vector< ObjectMesh > ObjectMeshArray;

		class Scene
		{
		public:
			Scene();
			~Scene();

			void draw()const;

			void addObject( ObjectPtr object );
			void removeObject( ObjectPtr object );

			inline Camera & getCamera()
			{
				return m_camera;
			}

			inline Camera const & getCamera()const
			{
				return m_camera;
			}

			inline ObjectArray const & getObjects()const
			{
				return m_objects;
			}

		private:
			ObjectArray m_objects;
			ObjectMeshArray m_opaqueObjects;
			ObjectMeshArray m_transparentObjects;
			Camera m_camera;
		};
	}
}

#endif
