#ifndef ___LMP3D_Graphics_Object_H___
#define ___LMP3D_Graphics_Object_H___

#include "Quaternion.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			Group of meshes, materials and spacial informations, representing an object in the scene.
		*/
		class Object
		{
		public:
			/**
			@brief
				Constructor.
			*/
			Object( MeshArray const & meshes, MaterialArray const & materials );
			/**
			@brief
				Destructor.
			*/
			~Object();
			/**
			@brief
				Creates and loads an objet from a file.
			@param[in] filePath
				The file full path.
			@return
				The created and loaded object.
			*/
			static ObjectPtr create( std::string const & filePath );
			/**
			@brief
				Clones this object.
			@return
				The clone.
			*/
			ObjectPtr clone()const;
			/**
			@return
				The object's position.
			*/
			inline Vector3 const & getPosition()const
			{
				return m_position;
			}
			/**
			@return
				The object's orientation.
			*/
			inline Quaternion const & getOrientation()const
			{
				return m_orientation;
			}
			/**
			@brief
				Sets the object orientation.
			@param[in] value
				The new orientation.
			*/
			inline void setOrientation( Quaternion const & value )
			{
				m_orientation = value;
			}
			/**
			@brief
				Moves the object to given position.
			@param[in] value
				The new position.
			*/
			inline void moveTo( Vector3 const & value )
			{
				m_position = value;
			}
			/**
			@brief
				Moves the object to given position.
			@param[in] x,y,z
				The new position.
			*/
			inline void moveTo( float x, float y, float z )
			{
				m_position.x = x;
				m_position.y = y;
				m_position.z = z;
			}
			/**
			@brief
				Rotates the object by given quaternion.
			@param[in] value
				The orientation.
			*/
			inline void rotate( Quaternion const & value )
			{
				m_orientation *= value;
			}
			/**
			@brief
				Translates the camera by given vector.
			@param[in] value
				The translation vector.
			*/
			inline void translate( Vector3 const & value )
			{
				m_position += value;
			}
			/**
			@brief
				Translates the camera by given vector.
			@param[in] x,y,z
				The translation vector.
			*/
			inline void translate( float x, float y, float z )
			{
				m_position.x += x;
				m_position.y += y;
				m_position.z += z;
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
			MeshArray m_meshes;
			MaterialArray m_materials;
		};
	}
}

#endif
