#ifndef ___LMP3D_Graphics_H___
#define ___LMP3D_Graphics_H___

#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "Object.h"
#include "Scene.h"
#include "Texture.h"
#include "Viewport.h"
#include "ElementsList.h"
#include "../Singleton.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			Class holding non scene related graphics data.
		@remarks
			This class is a singleton, so you *MUST* call Graphics::initialise,
			and Graphics::cleanup when appropriate. (Done in LMP3D::Window ctor)
		*/
		class Graphics
			: public Singleton< Graphics >
		{
		private:
			/**
			@brief
				Constructor.
			*/
			Graphics();
			/**
			@brief
				Destructor.
			*/
			~Graphics();

		public:
			/**
			@brief
				The singleton initialisation function.
			*/
			static void initialise();
			/**
			@brief
				The singleton cleanup function.
			*/
			static void cleanup();
			/**
			@return
				The materials list.
			*/
			inline MaterialsList & getMaterials()
			{
				return m_materials;
			}
			/**
			@return
				The materials list.
			*/
			inline MaterialsList const & getMaterials()const
			{
				return m_materials;
			}
			/**
			@return
				The meshes list.
			*/
			inline MeshesList & getMeshes()
			{
				return m_meshes;
			}
			/**
			@return
				The meshes list.
			*/
			inline MeshesList const & getMeshes()const
			{
				return m_meshes;
			}
			/**
			@return
				The textures list.
			*/
			inline TexturesList & getTextures()
			{
				return m_textures;
			}
			/**
			@return
				The textures list.
			*/
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
