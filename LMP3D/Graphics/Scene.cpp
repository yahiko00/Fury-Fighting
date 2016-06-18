#include "Scene.h"

#include "Object.h"

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

		void Scene::addObject( Object const & object )
		{
			m_objects.push_back( object );
		}

		void Scene::draw()const
		{
			if ( m_camera.apply() )
			{
				for ( ObjectArray::const_iterator it = m_objects.begin(); it != m_objects.end(); ++it )
				{
					it->draw();
				}
			}
		}
	}
}
