#include "ObjLoader.h"

#include "Mesh.h"
#include "Object.h"
#include "Material.h"
#include "Texture.h"

#include "LMP3D/StringUtils.h"

#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include <SDL/SDL_image.h>

namespace LMP3D
{
	namespace Graphics
	{
		template< typename T >
		struct pointer
		{
			typedef void( *dtorFunc )( T * );

			inline pointer( T * pointer, dtorFunc dtor )
				: m_pointer( pointer )
				, m_dtor( dtor )
			{
			}

			inline ~pointer()
			{
				( *m_dtor )( m_pointer );
			}

			inline T * operator->()
			{
				return m_pointer;
			}

			inline operator T*()
			{
				return m_pointer;
			}

		private:
			T * m_pointer;
			dtorFunc m_dtor;
		};

		TexturePtr LoadTexture( std::string const & fileName )
		{
			pointer< SDL_Surface > image( IMG_Load( fileName.c_str() ), SDL_FreeSurface );
			TexturePtr ret = NULL;

			if ( image )
			{
				int format = GL_BGR;

				if ( image->format->BytesPerPixel == 3 )
				{
					format = GL_RGB;
				}
				else if ( image->format->BytesPerPixel == 4 )
				{
					if ( image->format->Amask > image->format->Rmask )
					{
						format = GL_BGRA;
					}
					else
					{
						format = GL_RGBA;
					}
				}

				uint8_t * data = reinterpret_cast< uint8_t * >( image->pixels );
				ret = new Texture( ByteArray( data, data + image->pitch * image->h ), Size( image->w, image->h ), format );
			}

			return ret;
		}

		void LoadMtlFile( std::string const & fileName, Mesh & mesh, MaterialMap & materials )
		{
			std::ifstream file( fileName.c_str() );
			std::string line;
			MaterialMap::iterator select = materials.end();

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
					select = materials.find( name );
				}
				else if ( select != materials.end() )
				{
					if ( ident == "Ka" )
					{
						Colour3 value;
						stream >> value.r >> value.g >> value.b;
						select->second->setAmbient( value );
					}
					else if ( ident == "Kd" )
					{
						Colour3 value;
						stream >> value.r >> value.g >> value.b;
						select->second->setDiffuse( value );
					}
					else if ( ident == "Ks" )
					{
						Colour3 value;
						stream >> value.r >> value.g >> value.b;
						select->second->setSpecular( value );
					}
					else if ( ident == "Ns" )
					{
						float value;
						stream >> value;
						select->second->setExponent( value );
					}
					else if ( ident == "d" )
					{
						float value;
						stream >> value;
						select->second->setOpacity( value );
					}
					else if ( ident == "map_Kd" )
					{
						std::string path;
						stream >> path;
						select->second->setTexture( LoadTexture( getPath( fileName ) + PATH_SEPARATOR + path ) );
					}
				}
			}
		}

		Object LoadObjFile( std::string const & fileName, MaterialMap materials )
		{
			std::ifstream file( fileName.c_str() );
			std::string line;
			std::string mtlfile;
			uint16_t nv = 0u;
			uint16_t nvt = 0u;
			uint16_t nvn = 0u;
			uint16_t nf = 0u;
			uint16_t ntf = 0u;
			uint16_t ng = 0u;
			std::vector< uint16_t > faces;
			MaterialArray submeshesMaterials;
			std::string mtlname;

			while ( std::getline( file, line ) )
			{
				trim_left( line );
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

					if ( ident == "usemtl" )
					{
						stream >> mtlname;
						MaterialPtr material = new Material;
						materials.insert( std::make_pair( mtlname, material ) );
					}

					if ( !mtlname.empty() )
					{
						submeshesMaterials.push_back( materials.find( mtlname )->second );
					}
				}
				else if ( ident == "mtllib" )
				{
					mtlfile = line.substr( line.find_first_of( " " ) + 1 );
				}
			}

			if ( ntf )
			{
				faces.push_back( ntf );
			}

			file.clear();
			file.seekg( 0, std::ios::beg );

			Vector3Array allvtx( nv );
			Vector2Array alltex( nvt );
			Vector3Array allnml( nvn );
			Vector3Array::iterator vtxit = allvtx.begin();
			Vector2Array::iterator texit = alltex.begin();
			Vector3Array::iterator nmlit = allnml.begin();

			std::cout << "    Vertex count: " << nv << std::endl;
			std::cout << "    TexCoord count: " << nvt << std::endl;
			std::cout << "    Normal count: " << nvn << std::endl;
			std::cout << "    Group count: " << faces.size() << std::endl;

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
			std::vector< std::string > textures;
			textures.reserve( faces.size() );
			MeshPtr mesh = new Mesh;
			uint32_t submeshIndex = 0u;

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
						mesh->addSubmesh( submeshesMaterials[submeshIndex++]
										  , Vector3Array( vertex.begin(), vtxit )
										  , Vector3Array( normal.begin(), nmlit )
										  , Vector2Array( texcoord.begin(), texit ) );
						vtxit = vertex.begin();
						nmlit = normal.begin();
						texit = texcoord.begin();
						++facesit;
					}

					std::cout << "    Group faces count: " << *facesit << std::endl;
				}
				else if ( ident == "usemtl" )
				{
					std::string name;
					stream >> name;
					textures.push_back( name );
				}
				else if ( ident == "f" )
				{
					for ( uint32_t i = 0u; i < 3u; i++ )
					{
						std::string face;
						stream >> face;

						auto index1 = face.find( '/' );
						std::string component = face.substr( 0, index1 );
						uint32_t iv = std::stoul( component ) - 1;
						vtxit->x = allvtx[iv].x;
						vtxit->y = allvtx[iv].y;
						vtxit->z = allvtx[iv].z;
						++vtxit;

						++index1;
						auto index2 = face.find( '/', index1 );
						component = face.substr( index1, index2 - index1 );
						uint32_t ivt = std::stoul( component ) - 1;
						texit->x = alltex[ivt].x;
						texit->y = alltex[ivt].y;
						++texit;

						++index2;
						component = face.substr( index2 );
						uint32_t ivn = std::stoul( component ) - 1;
						nmlit->x = allnml[ivn].x;
						nmlit->y = allnml[ivn].y;
						nmlit->z = allnml[ivn].z;
						++nmlit;
					}
				}
			}

			if ( vtxit != vertex.begin()
				 && facesit != faces.end() )
			{
				mesh->addSubmesh( submeshesMaterials[submeshIndex++]
								  , Vector3Array( vertex.begin(), vtxit )
								  , Vector3Array( normal.begin(), nmlit )
								  , Vector2Array( texcoord.begin(), texit ) );
			}

			LoadMtlFile( getPath( fileName ) + PATH_SEPARATOR + mtlfile, *mesh, materials );
			return Object( mesh );
		}
	}
}
