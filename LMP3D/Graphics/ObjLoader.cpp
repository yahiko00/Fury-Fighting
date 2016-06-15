#include "ObjLoader.h"

#include "TexturedMesh.h"

#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace LMP3D
{
	namespace Graphics
	{
		inline void trim_left( std::string & text )
		{
			auto index = text.find_first_not_of( " \t" );

			if ( index != std::string::npos )
			{
				text = text.substr( index );
			}
		}

		inline void trim_right( std::string & text )
		{
			auto index = text.find_last_not_of( " \t" );

			if ( index != std::string::npos )
			{
				text = text.substr( 0, index + 1 );
			}
		}

		inline void trim( std::string & text )
		{
			trim_left( text );
			trim_right( text );
		}

		void LoadMtlFile( std::string const & fileName, TexturedMesh & mesh, std::vector< std::string > & names )
		{
			std::ifstream file{ fileName };
			std::string line;
			auto select = names.end();

			while ( std::getline( file, line ) )
			{
				trim( line );
				std::stringstream stream{ line };
				std::string ident;
				stream >> ident;

				if ( ident == "newmtl" )
				{
					std::string name;
					stream >> name;
					select = std::find( names.begin(), names.end(), name );
				}
				else if ( ident == "map_Kd" )
				{
					std::string path;
					stream >> path;
					*select = path;
				}
			}
		}

		MeshPtr LoadObjFile( std::string const & fileName )
		{
			std::ifstream file{ fileName };
			std::string line;
			std::string mtlfile;
			uint32_t nv{ 0u };
			uint32_t nvt{ 0u };
			uint32_t nvn{ 0u };
			uint32_t nf{ 0u };
			uint32_t ntf{ 0u };
			uint32_t ng{ 0u };
			std::vector< FaceArray > faces;

			while ( std::getline( file, line ) )
			{
				trim_left( line );
				std::stringstream stream{ line };
				std::string ident;
				stream >> ident;

				if ( ident == "v" )
				{
					if ( ntf )
					{
						faces.push_back( FaceArray{ ntf } );
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
						faces.push_back( FaceArray{ ntf } );
						ntf = 0u;
					}
				}
				else if ( ident == "mtllib" )
				{
					mtlfile = line.substr( line.find_first_of( " " ) + 1 );
				}
			}

			if ( ntf )
			{
				faces.push_back( FaceArray{ ntf } );
			}

			file.clear();
			file.seekg( 0, std::ios::beg );

			Vector3Array allvtx{ nv };
			Vector2Array alltex{ nvt };
			Vector3Array allnml{ nvn };
			auto vtxit = allvtx.begin();
			auto texit = alltex.begin();
			auto nmlit = allnml.begin();

			std::cout << "    Vertex count: " << nv << std::endl;
			std::cout << "    TexCoord count: " << nvt << std::endl;
			std::cout << "    Normal count: " << nvn << std::endl;
			std::cout << "    Group count: " << faces.size() << std::endl;

			while ( std::getline( file, line ) )
			{
				trim( line );
				std::stringstream stream{ line };
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

			Vector3Array vertex{ nf * 3 };
			Vector3Array normal{ nf * 3 };
			Vector2Array texcoord{ nf * 3 };
			vtxit = vertex.begin();
			texit = texcoord.begin();
			nmlit = normal.begin();
			auto facesit = faces.end();
			FaceArray::iterator idxit;
			uint32_t idx{ 0u };
			std::vector< std::string > textures;
			textures.reserve( faces.size() );

			while ( std::getline( file, line ) )
			{
				trim( line );
				std::stringstream stream{ line };
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
						++facesit;
					}

					idxit = facesit->begin();
					std::cout << "    Group faces count: " << facesit->size() << std::endl;
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

					idxit->a = idx++;
					idxit->b = idx++;
					idxit->c = idx++;
					++idxit;
				}
			}

			auto ret = std::make_unique< TexturedMesh >();
			ret->setData( std::move( vertex ), std::move( normal ), std::move( texcoord ), std::move( faces ) );

			LoadMtlFile( mtlfile, *ret, textures );
			return std::move( ret );
		}
	}
}
