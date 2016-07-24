#include "Object.h"

#include "Material.h"
#include "Mesh.h"
#include "Scene.h"

#include "Platform.h"

#include "../FileUtils.h"
#include "../StringUtils.h"

namespace LMP3D
{
	namespace Graphics
	{
		Object::Object( Scene & scene, MeshArray const & meshes, MaterialArray const & materials )
			: m_meshes( meshes )
			, m_materials( materials )
			, m_scale( 1.0f, 1.0f, 1.0f )
			, m_scene( scene )
		{
			assert( meshes.size() == materials.size() && "Meshes and materials sizes don't match" );
		}

		Object::~Object()
		{
		}

		ObjectPtr Object::clone()const
		{
			ObjectPtr result = new Object( m_scene, m_meshes, m_materials );
			m_scene.addObject( result );
			return result;
		}
	}
}
