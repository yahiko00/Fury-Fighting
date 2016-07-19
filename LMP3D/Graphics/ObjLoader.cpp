#include "ObjLoader.h"

#include "Material.h"
#include "Mesh.h"
#include "Object.h"
#include "Scene.h"
#include "Texture.h"
#include "Graphics.h"

#include "../StringUtils.h"
#include "../FileUtils.h"

#include "../LMP3D.h"

#include <cstdlib>
#include <fstream>
#include <sstream>

namespace LMP3D
{
	namespace Graphics
	{
		namespace
		{
			inline TexturePtr loadTexture( std::string const & fileName, Scene & scene )
			{
				std::string name = getFileName( fileName, true );
				TexturePtr ret = scene.getTextures().getElement( name );

				if ( !ret )
				{
					ret = scene.getTextures().addElement( name );
					ret->load( fileName );
				}

				return ret;
			}

			inline void createMesh( std::string const & mshname
									, std::string const & mtlname
									, Vector3Array const & vertex
									, Vector3Array const & normal
									, Vector2Array const & texcoord
									, MeshArray & meshes
									, MaterialArray & materials
									, Scene & scene )
			{
				MeshPtr mesh = scene.getMeshes().addElement( mshname );
				mesh->setData( vertex, normal, texcoord );
				materials.push_back( scene.getMaterials().getElement( mtlname ) );
				meshes.push_back( mesh );
			}
		}

		void loadMtlFile( std::string const & fileName, Scene & scene )
		{
			std::ifstream file( fileName.c_str() );

			if ( !file.is_open() )
			{
				logError( "Failed to open the MTL file %s%s\n", LMP3D::getCurrentDirectory().c_str(), fileName.c_str() );
				return;
			}
			std::string line;
			MaterialPtr select = NULL;

			while ( std::getline( file, line ) )
			{
				trim( line );
				std::stringstream stream( line );
				std::string ident;
				stream >> ident;

				if ( ident == "newmtl" )
				{
					std::string name;
					stream >> name;
					select = scene.getMaterials().addElement( name );
				}
				else if ( select )
				{
					if ( ident == "Ka" )
					{
						Colour3 value;
						stream >> value.r >> value.g >> value.b;
						select->setAmbient( value );
					}
					else if ( ident == "Kd" )
					{
						Colour3 value;
						stream >> value.r >> value.g >> value.b;
						select->setDiffuse( value );
					}
					else if ( ident == "Ks" )
					{
						Colour3 value;
						stream >> value.r >> value.g >> value.b;
						select->setSpecular( value );
					}
					else if ( ident == "Ns" )
					{
						float value;
						stream >> value;
						select->setExponent( value );
					}
					else if ( ident == "d" )
					{
						float value;
						stream >> value;
						select->setOpacity( value );
					}
					else if ( ident == "map_Kd" )
					{
						std::string path;
						stream >> path;
						select->setTexture( loadTexture( getFilePath( fileName ) + PATH_SEPARATOR + path, scene ) );
					}
				}
			}
		}

		ObjectPtr loadObjFile( std::string const & fileName, Scene & scene )
		{
			std::string objectName = getFileName( fileName );
			std::ifstream file( fileName.c_str() );

			if ( !file )
			{
				logError( "Failed to open the OBJ file %s\n", fileName.c_str() );
				return NULL;
			}

			std::string line;
			std::string mtlfile;
			uint16_t nv = 0u;
			uint16_t nvt = 0u;
			uint16_t nvn = 0u;
			uint16_t nf = 0u;
			uint16_t ntf = 0u;
			uint16_t ng = 0u;
			std::vector< uint16_t > faces;

			while ( std::getline( file, line ) )
			{
				trimLeft( line );
				std::stringstream stream( line );
				std::string ident;
				stream >> ident;

				if ( ident == "v" )
				{
					if ( ntf )
					{
						faces.push_back( ntf );
						ntf = 0u;
					}

					++nv;
				}
				else if ( ident == "vt" )
				{
					++nvt;
				}
				else if ( ident == "vn" )
				{
					++nvn;
				}
				else if ( ident == "f" )
				{
					++nf;
					++ntf;
				}
				else if ( ident == "g" || ident == "usemtl" )
				{
					if ( ntf )
					{
						faces.push_back( ntf );
						ntf = 0u;
					}
				}
				else if ( ident == "mtllib" )
				{
					mtlfile = line.substr( line.find_first_of( " " ) + 1 );
					trim( mtlfile );
				}
			}

			if ( ntf )
			{
				faces.push_back( ntf );
			}

			if ( !mtlfile.empty() )
			{
			  loadMtlFile( getFilePath( fileName ) + PATH_SEPARATOR + mtlfile, scene );
			}

			file.clear();
			file.seekg( 0, std::ios::beg );

			Vector3Array allvtx( nv );
			Vector2Array alltex( nvt );
			Vector3Array allnml( nvn );
			Vector3Array::iterator vtxit = allvtx.begin();
			Vector2Array::iterator texit = alltex.begin();
			Vector3Array::iterator nmlit = allnml.begin();

			logDebug( "    Vertex count: %d\n", nv );
			logDebug( "    TexCoord count: %d\n", nvt );
			logDebug( "    Normal count: %d\n", nvn );
			logDebug( "    Group count: %d\n", faces.size() );

			while ( std::getline( file, line ) )
			{
				trim( line );
				std::stringstream stream( line );
				std::string ident;
				stream >> ident;

				if ( ident == "v" )
				{
					stream >> vtxit->x >> vtxit->y >> vtxit->z;
					++vtxit;
				}
				else if ( ident == "vt" )
				{
					stream >> texit->x >> texit->y;
					++texit;
				}
				else if ( ident == "vn" )
				{
					stream >> nmlit->x >> nmlit->y >> nmlit->z;
					++nmlit;
				}
			}

			file.clear();
			file.seekg( 0, std::ios::beg );

			Vector3Array vertex( nf * 3 );
			Vector3Array normal( nf * 3 );
			Vector2Array texcoord( nf * 3 );
			vtxit = vertex.begin();
			texit = texcoord.begin();
			nmlit = normal.begin();
			std::vector< uint16_t >::iterator facesit = faces.end();
			uint32_t submeshMtlIndex = 0u;
			std::string mtlname;
			MeshArray meshes;
			MaterialArray materials;
			meshes.reserve( faces.size() );
			materials.reserve( faces.size() );

			while ( std::getline( file, line ) )
			{
				trim( line );
				std::stringstream stream( line );
				std::string ident;
				stream >> ident;

				if ( ident == "g" )
				{
					if ( facesit == faces.end() )
					{
						facesit = faces.begin();
					}
					else
					{
						std::stringstream name;
						name << objectName << "_" << ( meshes.size() + 1 );
						createMesh( name.str(), mtlname
									, Vector3Array( vertex.begin(), vtxit )
									, Vector3Array( normal.begin(), nmlit )
									, Vector2Array( texcoord.begin(), texit )
									, meshes, materials, scene );
						vtxit = vertex.begin();
						nmlit = normal.begin();
						texit = texcoord.begin();
						++facesit;
					}

					logDebug( "    Group faces count: %d\n", *facesit );
				}
				else if ( ident == "usemtl" )
				{
					if ( facesit == faces.end() )
					{
						facesit = faces.begin();
					}
					else if ( vertex.begin() != vtxit )
					{
						std::stringstream name;
						name << objectName << "_" << ( meshes.size() + 1 );
						createMesh( name.str(), mtlname
									, Vector3Array( vertex.begin(), vtxit )
									, Vector3Array( normal.begin(), nmlit )
									, Vector2Array( texcoord.begin(), texit )
									, meshes, materials, scene );
						vtxit = vertex.begin();
						nmlit = normal.begin();
						texit = texcoord.begin();
						++facesit;
					}

					stream >> mtlname;
					trim( mtlname );
				}
				else if ( ident == "f" )
				{
					for ( uint32_t i = 0u; i < 3u; i++ )
					{
						std::string face;
						stream >> face;

						size_t index1 = face.find( '/' );
						std::string component = face.substr( 0, index1 );
						uint32_t iv = atoi( component.c_str() ) - 1;
						*vtxit++ = allvtx[iv];

						++index1;
						size_t index2 = face.find( '/', index1 );
						component = face.substr( index1, index2 - index1 );
						uint32_t ivt = atoi( component.c_str() ) - 1;
						texit->x = alltex[ivt].x;
						texit->y = 1.0f - alltex[ivt].y;
						++texit;

						++index2;
						component = face.substr( index2 );
						uint32_t ivn = atoi( component.c_str() ) - 1;
						*nmlit++ = allnml[ivn];
					}
				}
			}

			if ( vtxit != vertex.begin()
				 && facesit != faces.end() )
			{
				std::stringstream name;
				name << objectName << "_" << ( meshes.size() + 1 );
				createMesh( name.str(), mtlname
							, Vector3Array( vertex.begin(), vtxit )
							, Vector3Array( normal.begin(), nmlit )
							, Vector2Array( texcoord.begin(), texit )
							, meshes, materials, scene );
			}

			return new Object( scene, meshes, materials );
		}
	}
}
