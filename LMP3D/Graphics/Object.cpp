#include "Object.h"

#include "Material.h"
#include "Mesh.h"

#include "ObjLoader.h"
#include "SmdLoader.h"

#include "Platform.h"

#include "../FileUtils.h"
#include "../StringUtils.h"

namespace LMP3D
{
	namespace Graphics
	{
		Object::Object( MeshArray const & meshes, MaterialArray const & materials )
			: m_meshes( meshes )
			, m_materials( materials )
		{
			assert( meshes.size() == materials.size() && "Meshes and materials sizes don't match" );
		}

		Object::~Object()
		{
		}

		ObjectPtr Object::create( std::string const & filePath )
		{
			std::string extension = lowerCase( getFileExtension( filePath ) );
			ObjectPtr result = NULL;

			if ( extension == "obj" )
			{
				result = loadObjFile( filePath );
			}
			else if ( extension == "smd" )
			{
				result = loadSmdFile( filePath );
			}
			else
			{
				assert( false && "Unsupported file format" );
			}

			return result;
		}

		ObjectPtr Object::clone()const
		{
			return new Object( m_meshes, m_materials );
		}
	}
}
