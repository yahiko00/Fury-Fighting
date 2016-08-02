#ifndef ___LMP3D_Graphics_Object_H___
#define ___LMP3D_Graphics_Object_H___

#include "Movable.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			Group of meshes, materials and spacial informations, representing an object in the scene.
		*/
		class Object
			: public Movable
		{
		public:
			/**
			@brief
				Constructor.
			*/
			Object( Scene & scene, MeshArray const & meshes, MaterialArray const & materials );
			/**
			@brief
				Destructor.
			*/
			~Object();
			/**
			@brief
				Clones this object.
			@return
				The clone.
			*/
			ObjectPtr clone()const;
			/**
			@brief
				Sets the object scale.
			@param[in] value
				The new scale.
			*/
			inline void setScale( Vector3 const & value )
			{
				m_scale = value;
			}
			/**
			@brief
				Sets the object scale.
			@param[in] x,y,z
				The new scale.
			*/
			inline void setScale( float x, float y, float z )
			{
				m_scale.x = x;
				m_scale.y = y;
				m_scale.z = z;
			}
			/**
			@brief
				Scales the object by given scale.
			@param[in] value
				The scale.
			*/
			inline void scale( Vector3 const & value )
			{
				m_scale.x *= value.x;
				m_scale.y *= value.y;
				m_scale.z *= value.z;
			}
			/**
			@brief
				Scales the object by given scale.
			@param[in] x,y,z
				The scale.
			*/
			inline void scale( float x, float y, float z )
			{
				m_scale.x *= x;
				m_scale.y *= y;
				m_scale.z *= z;
			}
			/**
			@return
				The object's scale.
			*/
			inline Vector3 const & getScale()const
			{
				return m_scale;
			}
			/**
			@return
				The object's meshes.
			*/
			inline MeshArray const & getMeshes()const
			{
				return m_meshes;
			}
			/**
			@return
				The object's materials.
			*/
			inline MaterialArray const & getMaterials()const
			{
				return m_materials;
			}

		private:
			Quaternion m_orientation;
			Vector3 m_position;
			Vector3 m_scale;
			MeshArray m_meshes;
			MaterialArray m_materials;
			Scene & m_scene;
		};
	}
}

#endif
