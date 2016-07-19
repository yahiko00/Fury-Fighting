#ifndef ___LMP3D_Platform_OpenGL_H___
#define ___LMP3D_Platform_OpenGL_H___

#include "../Quaternion.h"

#if defined( _WIN32 )

#	include <Windows.h>
#	undef near
#	undef far
#	undef min
#	undef max
#	undef abs
#	undef LoadImage

#else

#endif

#include <GL/gl.h>
#include <GL/glu.h>

#define GL_BGR 0x80E0
#define GL_BGRA 0x80E1
#define GL_RGB565 0x8D62
#define GL_ARGB1555 0x8057
#define GL_ARGB4444 0x804F

#if !defined( GL_INVALID_INDEX )
#	define GL_INVALID_INDEX 0xFFFFFFFF
#endif

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
#if defined( NDEBUG )

#	define checkGlError( Name ) true

#else

#	define checkGlError( Name ) Platform::checkError( #Name )
			static uint32_t const ErrorCount = 6;

			inline bool checkError( char const * const p_name )
			{
				static char const * const Errors[ErrorCount] =
				{
					"Invalid Enum",
					"Invalid Value",
					"Invalid Operation",
					"Stack Overflow",
					"Stack Underflow",
					"Out Of Memory",
				};

				unsigned int l_error = 0;
				bool l_return = true;

				while ( ( l_error = glGetError() ) != GL_NO_ERROR )
				{
					logError( "Error encountered executing OpenGL function %s (0x%04x)", p_name, l_error );
					l_error -= GL_INVALID_ENUM;

					if ( l_error < ErrorCount )
					{
						logError( "%s\n", Errors[l_error] );
					}
					else
					{
						logError( "%s\n", "Unknown error" );
					}

					l_return = false;
				}

				return l_return;
			}

#endif

			namespace
			{
				GLint getInternal( PixelFormat format )
				{
					switch ( format )
					{
					case RGB:
					case BGR:
					case RGB565:
					case BGR565:
						return 3;

					case RGBA:
					case BGRA:
					case ARGB1555:
					case ARGB4444:
						return 4;

					default:
						assert( false && "Unexpected texture format" );
						return 3;
					}
				}

				GLenum getFormat( PixelFormat format )
				{
					switch ( format )
					{
					case RGB:
						return GL_RGB;

					case BGR:
						return GL_BGR;

					case RGB565:
					case BGR565:
						return GL_RGB565;

					case RGBA:
						return GL_RGBA;

					case BGRA:
						return GL_BGRA;

					case ARGB1555:
						return GL_ARGB1555;

					case ARGB4444:
						return GL_ARGB4444;

					default:
						assert( false && "Unexpected texture format" );
						return 3;
					}
				}
			}

			inline void initialise()
			{
			}

			inline void cleanup()
			{
			}

			inline bool initialiseWindow()
			{
				glClearColor( 0.5f, 0.5f, 0.5f, 0.0f );
				glEnable( GL_CULL_FACE );
				glEnable( GL_TEXTURE_2D );
				glAlphaFunc( GL_GREATER, 0.0f );
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
				return checkGlError( "glInitialise" );
			}

			inline void cleanupWindow()
			{
			}

			inline bool bindVertexPointer( Vector3Array const & data )
			{
				glEnableClientState( GL_VERTEX_ARRAY );
				glVertexPointer( 3, GL_FLOAT, 0, &data[0] );
				return checkGlError( "glNormalPointer" );
			}

			inline void unbindVertexPointer()
			{
				glDisableClientState( GL_VERTEX_ARRAY );
			}

			inline bool bindColourPointer( ColourArray const & data )
			{
				glEnableClientState( GL_COLOR_ARRAY );
				glColorPointer( 4, GL_FLOAT, 0, &data[0] );
				return checkGlError( "glColorPointer" );
			}

			inline void unbindColourPointer()
			{
				glDisableClientState( GL_COLOR_ARRAY );
			}

			inline bool bindNormalPointer( Vector3Array const & data )
			{
				if ( !data.empty() )
				{
					glEnableClientState( GL_NORMAL_ARRAY );
					glNormalPointer( GL_FLOAT, 0, &data[0] );
				}

				return checkGlError( "glNormalPointer" );
			}

			inline void unbindNormalPointer()
			{
				glDisableClientState( GL_NORMAL_ARRAY );
			}

			inline bool bindTexCoordPointer( Vector2Array const & data )
			{
				if ( !data.empty() )
				{
					glEnableClientState( GL_TEXTURE_COORD_ARRAY );
					glTexCoordPointer( 2, GL_FLOAT, 0, &data[0] );
				}

				return checkGlError( "glNormalPointer" );
			}

			inline void unbindTexCoordPointer()
			{
				glDisableClientState( GL_TEXTURE_COORD_ARRAY );
			}

			inline bool bindMaterial( Colour4 const & ambient
									  , Colour4 const & diffuse
									  , Colour4 const & specular
									  , Colour4 const & emissive
									  , float exponent )
			{
				glMaterialfv( GL_FRONT, GL_AMBIENT, &ambient.r );
				glMaterialfv( GL_FRONT, GL_AMBIENT, &diffuse.r );
				glMaterialfv( GL_FRONT, GL_AMBIENT, &specular.r );
				glMaterialfv( GL_FRONT, GL_AMBIENT, &emissive.r );
				glMaterialf( GL_FRONT, GL_SHININESS, exponent );
				return checkGlError( "glMaterial" );
			}

			inline bool lookAt( Vector3 const & position
								, Vector3 const & lookAt
								, Vector3 const & up )
			{
				glMatrixMode( GL_MODELVIEW );
				glLoadIdentity();
				gluLookAt( position.x, position.y, position.z,
						   position.x + lookAt.x, position.y + lookAt.y, position.z + lookAt.z,
						   up.x, up.y, up.z );
				return checkGlError( "gluLookAt" );
			}

			inline void pushMatrix()
			{
				glPushMatrix();
			}

			inline void popMatrix()
			{
				glPopMatrix();
			}

			inline bool applyTransform( Vector3 const & position, Vector3 const & scale, Quaternion const & orientation )
			{
				static float matrix[16];

				float const qxx( orientation.x * orientation.x );
				float const qyy( orientation.y * orientation.y );
				float const qzz( orientation.z * orientation.z );
				float const qxz( orientation.x * orientation.z );
				float const qxy( orientation.x * orientation.y );
				float const qyz( orientation.y * orientation.z );
				float const qwx( orientation.w * orientation.x );
				float const qwy( orientation.w * orientation.y );
				float const qwz( orientation.w * orientation.z );

				matrix[0] = scale.x * ( 1 - 2 * ( qyy + qzz ) );
				matrix[1] = scale.x * ( 2 * ( qxy + qwz ) );
				matrix[2] = scale.x * ( 2 * ( qxz - qwy ) );
				matrix[3] = 0;

				matrix[4] = scale.y * ( 2 * ( qxy - qwz ) );
				matrix[5] = scale.y * ( 1 - 2 * ( qxx + qzz ) );
				matrix[6] = scale.y * ( 2 * ( qyz + qwx ) );
				matrix[7] = 0;

				matrix[8] = scale.z * ( 2 * ( qxz + qwy ) );
				matrix[9] = scale.z * ( 2 * ( qyz - qwx ) );
				matrix[10] = scale.z * ( 1 - 2 * ( qxx + qyy ) );
				matrix[11] = 0;

				matrix[12] = position.x;
				matrix[13] = position.y;
				matrix[14] = position.z;
				matrix[15] = 1;

				glMultMatrixf( matrix );
				return checkGlError( "glTransform" );
			}

			inline bool viewport( Size const & size )
			{
				glViewport( 0, 0, size.x, size.y );
				return checkGlError( "glViewport" );
			}

			inline bool perspective( float angle, float ratio, float near, float far )
			{
				glEnable( GL_DEPTH_TEST );
				glMatrixMode( GL_PROJECTION );
				glLoadIdentity();
				gluPerspective( angle, ratio, near, far );
				return checkGlError( "glPerspective" );
			}

			inline bool ortho( float left, float right, float bottom, float top, float near, float far )
			{
				glDisable( GL_DEPTH_TEST );
				glMatrixMode( GL_PROJECTION );
				glLoadIdentity();
				glOrtho( left, right, bottom, top, near, far );
				return checkGlError( "glOrtho" );
			}

			inline void createTexture( TextureId *& id, ImageData *& data )
			{
				id = new TextureId;
				id->id = GL_INVALID_INDEX;
				data = new ImageData;
				glGenTextures( 1, &id->id );
			}

			inline bool bindTexture( TextureId const & id )
			{
				glBindTexture( GL_TEXTURE_2D, id.id );
				return checkGlError( "glBindTexture" );
			}

			inline bool initialiseTexture( TextureId const & id, ImageData const & data )
			{
				glTexImage2D( GL_TEXTURE_2D, 0, getInternal( data.format ), data.size.x, data.size.y, 0, getFormat( data.format ), GL_UNSIGNED_BYTE, &data.data[0] );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
				return checkGlError( "glTexImage2D" );
			}

			inline void unbindTexture()
			{
				glBindTexture( GL_TEXTURE_2D, 0 );
			}

			inline void deleteTexture( TextureId *& id, ImageData *& data )
			{
				glDeleteTextures( 1, &id->id );
				delete id;
				id = NULL;
				delete data;
				data = NULL;
			}

			inline bool draw( int count )
			{
				glDrawArrays( GL_TRIANGLES, 0, count );
				return checkGlError( "glDrawElements" );
			}

			inline bool enableBlending()
			{
				glEnable( GL_ALPHA_TEST );
				glDisable( GL_CULL_FACE );
				return checkGlError( "glEnableBlend" );
			}

			inline bool disableBlending()
			{
				glDisable( GL_ALPHA_TEST );
				glEnable( GL_CULL_FACE );
				return checkGlError( "glDisableBlend" );
			}

			inline void clearFrame()
			{
				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			}

			inline void flushFrame()
			{
				glFlush();
			}
		}
	}
}

#endif
