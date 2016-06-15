#pragma once

#include <vector>
#include <cstdint>
#include <memory>

#include <GL/glew.h>

namespace LMP3D
{
	namespace Graphics
	{
		struct Colour3
		{
			float r{ 0.0f };
			float g{ 0.0f };
			float b{ 0.0f };
		};

		struct Colour4
		{
			float r{ 0.0f };
			float g{ 0.0f };
			float b{ 0.0f };
			float a{ 0.0f };
		};

		struct Vector2
		{
			float x{ 0.0f };
			float y{ 0.0f };
		};

		struct Vector3
		{
			float x{ 0.0f };
			float y{ 0.0f };
			float z{ 0.0f };
		};

		struct Face
		{
			uint16_t a{ 0u };
			uint16_t b{ 0u };
			uint16_t c{ 0u };
		};

		using Vector2Array = std::vector< Vector2 >;
		using Vector3Array = std::vector< Vector3 >;
		using ColourArray = std::vector< Colour4 >;
		using FaceArray = std::vector< Face >;

		class VertexBuffer;
		class ColourBuffer;
		class IndexBuffer;
		class NormalBuffer;
		class TexCoordBuffer;

		class Mesh;
		class ColouredMesh;
		class TexturedMesh;
		using MeshPtr = std::unique_ptr< Mesh >;

#if defined( NDEBUG )

#	define checkGlError( Name ) true

#else

#	define checkGlError( Name ) glCheckError( #Name )
		bool glCheckError( char const * const p_name );

#endif
	}
}
