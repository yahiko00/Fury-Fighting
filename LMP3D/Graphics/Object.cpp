#include "Object.h"

#include "Material.h"
#include "Mesh.h"

#include "Platform.h"

namespace LMP3D
{
	namespace Graphics
	{
		Object::Object( std::string const & name, MeshArray const & meshes, MaterialArray const & materials )
			: m_name( name )
			, m_meshes( meshes )
			, m_materials( materials )
		{
			assert( meshes.size() == materials.size() && "Meshes and materials sizes don't match" );
		}

		Object::~Object()
		{
		}
	}
}
