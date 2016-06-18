#include "Scene.h"

#include "Object.h"

#include "Platform.h"

namespace LMP3D
{
	namespace Graphics
	{
		Scene::Scene()
		{
		}

		Scene::~Scene()
		{
		}

		void Scene::addObject( MeshArray const & meshes, MaterialArray const & materials )
		{
			m_objects.push_back( Object( meshes, materials ) );

			ObjectPtr object = &m_objects.back();
			MeshArray::const_iterator mshit = meshes.begin();
			MaterialArray::const_iterator mtlit = materials.begin();

			while ( mshit != meshes.end() )
			{
				ObjectMesh objMesh;
				objMesh.m_material = *mtlit;
				objMesh.m_mesh = *mshit;
				objMesh.m_object = object;

				if ( ( *mtlit )->isOpaque() )
				{
					m_opaqueObjects.push_back( objMesh );
				}
				else
				{
					m_transparentObjects.push_back( objMesh );
				}

				++mshit;
				++mtlit;
			}
		}

		void Scene::draw()const
		{
			if ( m_camera.apply() )
			{
				for ( ObjectMeshArray::const_iterator it = m_opaqueObjects.begin(); it != m_opaqueObjects.end(); ++it )
				{
					Platform::PushMatrix();

					if ( Platform::ApplyTransform( it->m_object->getPosition(), it->m_object->getAngle(), it->m_object->getAxis() ) )
					{
						it->m_material->bind();
						it->m_mesh->draw();
						it->m_material->unbind();
					}

					Platform::PopMatrix();
				}

				for ( ObjectMeshArray::const_iterator it = m_transparentObjects.begin(); it != m_transparentObjects.end(); ++it )
				{
					Platform::PushMatrix();

					if ( Platform::ApplyTransform( it->m_object->getPosition(), it->m_object->getAngle(), it->m_object->getAxis() ) )
					{
						it->m_material->bind();
						it->m_mesh->draw();
						it->m_material->unbind();
					}

					Platform::PopMatrix();
				}
			}
		}
	}
}
