#include "Scene.h"

#include "Object.h"

#include "Platform.h"

#include "LMP3D/FileUtils.h"
#include "LMP3D/StringUtils.h"

#include "ObjLoader.h"
#include "SmdLoader.h"

#include <algorithm>

namespace LMP3D
{
	namespace Graphics
	{
		namespace
		{
			void displayObject( Object const & object, Mesh const & mesh, Material const & material )
			{
				if ( Platform::applyTransform( object.getPosition(), object.getScale(), object.getOrientation() ) )
				{
					material.bind();
					mesh.draw();
					material.unbind();
				}
			}

			struct ObjectFinder
			{
				ObjectFinder( ObjectPtr object )
					: m_object( object )
				{
				}

				bool operator()( ObjectMesh const & objMesh )
				{
					return objMesh.m_object == m_object;
				}

				ObjectPtr m_object;
			};
		}

		Scene::Scene()
		{
		}

		Scene::~Scene()
		{
			m_opaqueObjects.clear();
			m_transparentObjects.clear();

			for ( ObjectArray::iterator it = m_objects.begin(); it != m_objects.end(); ++it )
			{
				delete *it;
			}
		}

		ObjectPtr Scene::createObject( std::string const & filePath )
		{
			std::string extension = lowerCase( getFileExtension( filePath ) );
			ObjectPtr result = NULL;

			if ( extension == "obj" )
			{
				result = loadObjFile( filePath, *this );
			}
			else if ( extension == "smd" )
			{
				result = loadSmdFile( filePath, *this );
			}
			else
			{
				assert( false && "Unsupported file format" );
			}

			if ( result )
			{
				addObject( result );
			}
			else
			{
				logError( "Couldn't load object %s\n", filePath.c_str() );
			}

			return result;
		}

		void Scene::addObject( ObjectPtr object )
		{
			assert( object && "Null object given" );

			if ( std::find( m_objects.begin(), m_objects.end(), object ) != m_objects.end() )
			{
				assert( false && "Object has already been added" );
				return;
			}

			m_objects.push_back( object );
			assert( object->getMeshes().size() == object->getMaterials().size() && "Object's meshes and materials sizes don't match" );

			MeshArray::const_iterator mshit = object->getMeshes().begin();
			MeshArray::const_iterator mshitend = object->getMeshes().end();
			MaterialArray::const_iterator mtlit = object->getMaterials().begin();

			while ( mshit != mshitend )
			{
				ObjectMesh objMesh;
				objMesh.m_material = *mtlit;
				objMesh.m_mesh = *mshit;
				objMesh.m_object = object;

				if ( objMesh.m_material->isOpaque() )
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

		void Scene::removeObject( ObjectPtr object )
		{
			ObjectArray::iterator it = std::find( m_objects.begin(), m_objects.end(), object );

			if ( it == m_objects.end() )
			{
				assert( false && "Object not found (did you forget to add it?" );
				return;
			}

			ObjectFinder finder( object );
			m_opaqueObjects.erase( std::remove_if( m_opaqueObjects.begin(), m_opaqueObjects.end(), finder ), m_opaqueObjects.end() );
			m_transparentObjects.erase( std::remove_if( m_transparentObjects.begin(), m_transparentObjects.end(), finder ), m_opaqueObjects.end() );
		}

		void Scene::draw()const
		{
			if ( m_camera.apply() )
			{
				for ( ObjectMeshArray::const_iterator it = m_opaqueObjects.begin(); it != m_opaqueObjects.end(); ++it )
				{
					Platform::pushMatrix();
					displayObject( *it->m_object, *it->m_mesh, *it->m_material );
					Platform::popMatrix();
				}

				for ( ObjectMeshArray::const_iterator it = m_transparentObjects.begin(); it != m_transparentObjects.end(); ++it )
				{
					Platform::pushMatrix();
					displayObject( *it->m_object, *it->m_mesh, *it->m_material );
					Platform::popMatrix();
				}
			}
		}
	}
}
