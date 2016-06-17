#ifndef ___LMP3D_Graphics_Common_H___
#define ___LMP3D_Graphics_Common_H___

#include <vector>
#include <memory>
#include <string>
#include <cassert>
#include <map>

#include <GL/glew.h>

namespace LMP3D
{
	typedef unsigned long uint32_t;
	typedef unsigned short uint16_t;
	typedef unsigned char uint8_t;

	typedef long int32_t;
	typedef short int16_t;
	typedef char int8_t;

	namespace Graphics
	{
		struct Colour3
		{
			float r;
			float g;
			float b;

			Colour3( float r = 0.0f, float g = 0.0f, float b = 0.0f )
				: r( r )
				, g( g )
				, b( b )
			{
			}
		};

		struct Colour4
		{
			float r;
			float g;
			float b;
			float a;

			Colour4( float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f )
				: r( r )
				, g( g )
				, b( b )
				, a( a )
			{
			}
		};

		struct Vector2
		{
			float x;
			float y;

			Vector2( float x = 0.0f, float y = 0.0f )
				: x( x )
				, y( y )
			{
			}
		};

		struct Vector3
		{
			float x;
			float y;
			float z;

			Vector3( float x = 0.0f, float y = 0.0f, float z = 0.0f )
				: x( x )
				, y( y )
				, z( z )
			{
			}
		};

		struct Size
		{
			int x;
			int y;

			Size( int x = 0, int y = 0 )
				: x( x )
				, y( y )
			{
			}
		};

		typedef std::vector< Vector2 > Vector2Array;
		typedef std::vector< Vector3 > Vector3Array;
		typedef std::vector< Colour4 > ColourArray;

		class VertexBuffer;
		class ColourBuffer;
		class NormalBuffer;
		class TexCoordBuffer;

		class Material;
		class Texture;
		typedef Material * MaterialPtr;
		typedef Texture * TexturePtr;
		typedef std::vector< MaterialPtr > MaterialArray;
		typedef std::map< std::string, MaterialPtr > MaterialMap;

		class Mesh;
		class Submesh;
		typedef Submesh * SubmeshPtr;
		typedef Mesh * MeshPtr;
		typedef std::vector< SubmeshPtr > SubmeshArray;

		class Camera;
		class Object;

		typedef std::vector< std::string > StringArray;
		typedef std::vector< uint8_t > ByteArray;

#if defined( NDEBUG )

#	define checkGlError( Name ) true

#else

#	define checkGlError( Name ) glCheckError( #Name )
		bool glCheckError( char const * const p_name );

#endif
	}
}

#endif
