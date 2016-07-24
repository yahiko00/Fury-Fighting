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
		/**
		@brief
			An object's mesh and its material for this mesh, in the scene.
		*/
		struct ObjectMesh
		{
			//! The mesh.
			MeshPtr m_mesh;
			//! The mesh's material.
			MaterialPtr m_material;
			//! The parent object.
			ObjectPtr m_object;
		};
		typedef std::vector< ObjectMesh > ObjectMeshArray;
		/**
		@brief
			A scene, holds the camera, the drawn objects.
		*/
		class Scene
		{
		public:
			/**
			@brief
				Constructor.
			*/
			Scene();
			/**
			@brief
				Destructor.
			*/
			~Scene();
			/**
			@brief
				Draws the scene's objects, through the camera view.
			*/
			void draw()const;
			/**
			@brief
				Creates an object and loads it from a file.
			@param[in] filePath
				The object's file.
			@return
				The created and loaded object.
			*/
			ObjectPtr createObject( std::string const & filePath );
			/**
			@brief
				Adds an external object to the scene.
			@param[in] object
				The object to add.
			*/
			void addObject( ObjectPtr object );
			/**
			@brief
				Removes an object from the scene.
			@param[in] object
				The object to remove.
			*/
			void removeObject( ObjectPtr object );
			/**
			@return
				The camera.
			*/
			inline Camera & getCamera()
			{
				return m_camera;
			}
			/**
			@return
				The camera.
			*/
			inline Camera const & getCamera()const
			{
				return m_camera;
			}
			/**
			@return
				The objects list.
			*/
			inline ObjectArray const & getObjects()const
			{
				return m_objects;
			}
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
			ObjectArray m_objects;
			ObjectMeshArray m_opaqueObjects;
			ObjectMeshArray m_transparentObjects;
			Camera m_camera;
			MaterialsList m_materials;
			MeshesList m_meshes;
			TexturesList m_textures;
		};
	}
}

#endif
