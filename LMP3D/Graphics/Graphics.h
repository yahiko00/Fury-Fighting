#ifndef ___LMP3D_Graphics_H___
#define ___LMP3D_Graphics_H___

#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "Object.h"
#include "ObjLoader.h"
#include "Scene.h"
#include "SmdLoader.h"
#include "Texture.h"
#include "Viewport.h"
#include "ElementsList.h"

namespace LMP3D
{
	namespace Graphics
	{
		class Graphics
		{
		public:
			Graphics();
			~Graphics();

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
			MaterialsList m_materials;
			MeshesList m_meshes;
			TexturesList m_textures;
		};
	}
}

#endif
