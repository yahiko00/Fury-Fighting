#ifndef ___LMP3D_Graphics_Common_H___
#define ___LMP3D_Graphics_Common_H___

#include <cassert>
#include <iostream>
#include <map>
#include <memory>

#include "LMP3D/Common.h"

namespace LMP3D
{
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
		typedef Mesh * MeshPtr;
		typedef std::vector< MeshPtr > MeshArray;

		class Scene;
		class Camera;
		class Object;
		typedef std::vector< Object > ObjectArray;

		template< typename T > class ElementsList;
		typedef ElementsList< Material > MaterialsList;
		typedef ElementsList< Mesh > MeshesList;
	}
}

#endif
