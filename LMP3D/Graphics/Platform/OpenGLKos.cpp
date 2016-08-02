#if defined( _arch_dreamcast )

#include "../Quaternion.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define GL_BGR 0x80E0
#define GL_BGRA 0x80E1

#if !defined( GL_INVALID_INDEX )
#	define GL_INVALID_INDEX 0xFFFFFFFF
#endif

namespace LMP3D
{
	namespace Graphics
	{
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
						logDebug( "Internal texture format: %s\n", "GL_RGB" );
						return GL_RGB;

					case RGBA:
					case BGRA:
					case ARGB1555:
					case ARGB4444:
						logDebug( "Internal texture format: %s\n", "GL_RGBA" );
						return GL_RGBA;

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
						logDebug( "Texture format: %s\n", "GL_RGB" );
						return GL_UNSIGNED_BYTE;

					case BGR:
						logDebug( "Texture format: %s\n", "GL_BGR" );
						return GL_UNSIGNED_BYTE;

					case RGB565:
					case BGR565:
						logDebug( "Texture format: %s\n", "GL_UNSIGNED_SHORT_5_6_5_TWID" );
						return GL_UNSIGNED_SHORT_5_6_5_TWID;

					case RGBA:
						logDebug( "Texture format: %s\n", "GL_RGBA" );
						return GL_UNSIGNED_BYTE;

					case BGRA:
						logDebug( "Texture format: %s\n", "GL_BGRA" );
						return GL_UNSIGNED_BYTE;

					case ARGB1555:
						logDebug( "Texture format: %s\n", "GL_ARGB1555_TWID" );
						return GL_UNSIGNED_SHORT_1_5_5_5_TWID;

					case ARGB4444:
						logDebug( "Texture format: %s\n", "GL_UNSIGNED_SHORT_4_4_4_4_TWID" );
						return GL_UNSIGNED_SHORT_4_4_4_4;

					default:
						assert( false && "Unexpected texture format" );
						return 3;
					}
				}
			}

			void initialise()
			{
			}

			void cleanup()
			{
			}

			bool initialiseWindow()
			{
				glEnable( GL_TEXTURE_2D );
				glShadeModel( GL_SMOOTH );
				glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
				glClearDepth(1.0f);
				glEnable( GL_DEPTH_TEST);
				glDepthFunc( GL_LEQUAL );
				//glEnable( GL_CULL_FACE );
				//glAlphaFunc( GL_GREATER, 0.0f );
				//glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
				return checkGlError( "glInitialise" );
			}

			void cleanupWindow()
			{
			}

			bool bindVertexPointer( Vector3Array const & data )
			{
				glEnableClientState( GL_VERTEX_ARRAY );
				glVertexPointer( 3, GL_FLOAT, 0, &data[0] );
				return checkGlError( "glNormalPointer" );
			}

			void unbindVertexPointer()
			{
				glDisableClientState( GL_VERTEX_ARRAY );
			}

			bool bindColourPointer( ColourArray const & data )
			{
				glEnableClientState( GL_COLOR_ARRAY );
				glColorPointer( 4, GL_FLOAT, 0, &data[0] );
				return checkGlError( "glColorPointer" );
			}

			void unbindColourPointer()
			{
				glDisableClientState( GL_COLOR_ARRAY );
			}

			bool bindNormalPointer( Vector3Array const & data )
			{
				if ( !data.empty() )
				{
					glEnableClientState( GL_NORMAL_ARRAY );
					glNormalPointer( GL_FLOAT, 0, &data[0] );
				}

				return checkGlError( "glNormalPointer" );
			}

			void unbindNormalPointer()
			{
				glDisableClientState( GL_NORMAL_ARRAY );
			}

			bool bindTexCoordPointer( Vector2Array const & data )
			{
				if ( !data.empty() )
				{
					glEnableClientState( GL_TEXTURE_COORD_ARRAY );
					glTexCoordPointer( 2, GL_FLOAT, 0, &data[0] );
				}

				return checkGlError( "glNormalPointer" );
			}

			void unbindTexCoordPointer()
			{
				glDisableClientState( GL_TEXTURE_COORD_ARRAY );
			}

			bool bindMaterial( Colour4 const & ambient
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

			bool lookAt( Vector3 const & position
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

			void pushMatrix()
			{
				glPushMatrix();
			}

			void popMatrix()
			{
				glPopMatrix();
			}

			bool applyTransform( Vector3 const & position, Vector3 const & scale, Quaternion const & orientation )
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

			bool viewport( Size const & size )
			{
				glViewport( 0, 0, size.x, size.y );
				return checkGlError( "glViewport" );
			}

			bool perspective( float angle, float ratio, float near, float far )
			{
				glEnable( GL_DEPTH_TEST );
				glMatrixMode( GL_PROJECTION );
				glLoadIdentity();
				gluPerspective( angle, ratio, near, far );
				return checkGlError( "glPerspective" );
			}

			bool ortho( float left, float right, float bottom, float top, float near, float far )
			{
				glDisable( GL_DEPTH_TEST );
				glMatrixMode( GL_PROJECTION );
				glLoadIdentity();
				glOrtho( left, right, bottom, top, near, far );
				return checkGlError( "glOrtho" );
			}

			void createTexture( TextureId *& id, ImageData *& data )
			{
				id = new TextureId;
				id->id = GL_INVALID_INDEX;
				data = new ImageData;
				glGenTextures( 1, &id->id );
			}

			bool bindTexture( TextureId const & id )
			{
				glBindTexture( GL_TEXTURE_2D, id.id );
				return checkGlError( "glBindTexture" );
			}

			bool initialiseTexture( TextureId const & id, ImageData const & data )
			{
				glTexImage2D( GL_TEXTURE_2D, 0, getInternal( data.format ), data.size.x, data.size.y, 0, getInternal( data.format ), getFormat( data.format ), &data.data[0] );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
				return checkGlError( "glTexImage2D" );
			}

			void unbindTexture()
			{
				glBindTexture( GL_TEXTURE_2D, 0 );
			}

			void deleteTexture( TextureId *& id, ImageData *& data )
			{
				glDeleteTextures( 1, &id->id );
				delete id;
				id = NULL;
				delete data;
				data = NULL;
			}

			bool draw( int count )
			{
				glDrawArrays( GL_TRIANGLES, 0, count );
				return checkGlError( "glDrawElements" );
			}

			bool enableBlending()
			{
				glEnable( GL_ALPHA_TEST );
				glDisable( GL_CULL_FACE );
				return checkGlError( "glEnableBlend" );
			}

			bool disableBlending()
			{
				glDisable( GL_ALPHA_TEST );
				glEnable( GL_CULL_FACE );
				return checkGlError( "glDisableBlend" );
			}

			void clearFrame()
			{
				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
				checkGlError( "glClear" );
			}

			void flushFrame()
			{
			}
		}
	}
}

#endif
