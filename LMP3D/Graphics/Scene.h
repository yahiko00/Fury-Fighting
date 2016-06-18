#ifndef ___LMP3D_Graphics_Scene_H___
#define ___LMP3D_Graphics_Scene_H___

#include "Material.h"
#include "Mesh.h"
#include "ElementsList.h"
#include "Camera.h"

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

			void addObject( Object const & object );

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

		private:
			MaterialsList m_materials;
			MeshesList m_meshes;
			ObjectArray m_objects;
			Camera m_camera;
		};
	}
}

#endif
