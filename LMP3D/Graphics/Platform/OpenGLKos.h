#ifndef ___LMP3D_Platform_OpenGLKos_H___
#define ___LMP3D_Platform_OpenGLKos_H___

#include "../GraphicsCommon.h"

namespace LMP3D
{
	namespace Graphics
	{
		struct TextureId
		{
			unsigned int id;
		};

		namespace Platform
		{
			void initialise();
			void cleanup();
			bool initialiseWindow();
			void cleanupWindow();
			bool bindVertexPointer( Vector3Array const & data );
			void unbindVertexPointer();
			bool bindColourPointer( ColourArray const & data );
			void unbindColourPointer();
			bool bindNormalPointer( Vector3Array const & data );
			void unbindNormalPointer();
			bool bindTexCoordPointer( Vector2Array const & data );
			void unbindTexCoordPointer();
			bool bindMaterial( Colour4 const & ambient
							   , Colour4 const & diffuse
							   , Colour4 const & specular
							   , Colour4 const & emissive
							   , float exponent );
			bool lookAt( Vector3 const & position
						 , Vector3 const & lookAt
						 , Vector3 const & up );
			void pushMatrix();
			void popMatrix();
			bool applyTransform( Vector3 const & position
								 , Vector3 const & scale
								 , Quaternion const & orientation );;
			bool viewport( Size const & size );
			bool perspective( float angle, float ratio, float near, float far );
			bool ortho( float left, float right, float bottom, float top, float near, float far );
			void createTexture( TextureId *& id, ImageData *& data );
			bool bindTexture( TextureId const & id );
			bool initialiseTexture( TextureId const & id, ImageData const & data );
			void unbindTexture();
			void deleteTexture( TextureId *& id, ImageData *& data );
			bool draw( int count );
			bool enableBlending();
			bool disableBlending();
			void clearFrame();
			void flushFrame();
		}
	}
}

#endif
