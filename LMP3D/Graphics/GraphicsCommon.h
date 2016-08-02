#ifndef ___LMP3D_Graphics_Common_H___
#define ___LMP3D_Graphics_Common_H___

#include <cassert>
#include <map>
#include <memory>
#include <list>

#include "../Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			RGB colour.
		*/
		struct Colour3
		{
			/**
			@brief
				Constructor.
			*/
			Colour3( float r = 0.0f, float g = 0.0f, float b = 0.0f )
				: r( r )
				, g( g )
				, b( b )
			{
			}

			float r;
			float g;
			float b;
		};
		/**
		@brief
			RGBA colour.
		*/
		struct Colour4
		{
			/**
			@brief
				Constructor.
			*/
			Colour4( float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f )
				: r( r )
				, g( g )
				, b( b )
				, a( a )
			{
			}

			float r;
			float g;
			float b;
			float a;
		};

		struct Vector2;
		struct Vector3;
		class Quaternion;

		typedef std::vector< Vector2 > Vector2Array;
		typedef std::vector< Vector3 > Vector3Array;
		typedef std::vector< Colour4 > ColourArray;

		class VertexBuffer;
		class ColourBuffer;
		class NormalBuffer;
		class TexCoordBuffer;

		class Material;
		struct TextureId;
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
		typedef Object * ObjectPtr;
		typedef std::vector< ObjectPtr > ObjectArray;

		template< typename T > class ElementsList;
		typedef ElementsList< Material > MaterialsList;
		typedef ElementsList< Mesh > MeshesList;
		typedef ElementsList< Texture > TexturesList;
	}
}

#endif
