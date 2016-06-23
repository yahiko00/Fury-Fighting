#ifndef ___LMP3D_Platform_OpenGL_H___
#define ___LMP3D_Platform_OpenGL_H___

#include "LMP3D/Graphics/Quaternion.h"

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

				unsigned int l_error = glGetError();
				bool l_return = l_error == GL_NO_ERROR;

				if ( !l_return )
				{
					l_error -= GL_INVALID_ENUM;
					std::cerr << "Error encountered executing OpenGL function " << p_name << " ";

					if ( l_error < ErrorCount )
					{
						std::cerr << Errors[l_error] << std::endl;
					}
					else
					{
						std::cerr << "Unknow error (" << std::hex << ( l_error + GL_INVALID_ENUM ) << ")" << std::endl;
					}
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
						return 3;

					case RGBA:
					case BGRA:
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

					case RGBA:
						return GL_RGBA;

					case BGRA:
						return GL_BGRA;

					default:
						assert( false && "Unexpected texture format" );
						return 3;
					}
				}
			}

			inline bool initialise()
			{
				glClearColor( 0.5f, 0.5f, 0.5f, 0.0f );
				glEnable( GL_CULL_FACE );
				glEnable( GL_TEXTURE_2D );
				glAlphaFunc( GL_GREATER, 0.0f );
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
				return checkGlError( "glInitialise" );
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

			inline bool applyTransform( Vector3 const & position, Quaternion const & orientation )
			{
				static float matrix[16];
				orientation.toMatrix( matrix );
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

			inline unsigned int createTexture()
			{
				unsigned int ret = GL_INVALID_INDEX;
				glGenTextures( 1, &ret );
				return ret;
			}

			inline bool bindTexture( unsigned int id )
			{
				glBindTexture( GL_TEXTURE_2D, id );
				return checkGlError( "glBindTexture" );
			}

			inline bool initialiseTexture( Size const & size, PixelFormat format, ByteArray const & data )
			{
				glTexImage2D( GL_TEXTURE_2D, 0, getInternal( format ), size.x, size.y, 0, getFormat( format ), GL_UNSIGNED_BYTE, &data[0] );
				glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
				glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
				return checkGlError( "glTexImage2D" );
			}

			inline void unbindTexture()
			{
				glBindTexture( GL_TEXTURE_2D, 0 );
			}

			inline void deleteTexture( unsigned int id )
			{
				glDeleteTextures( 1, &id );
			}

			inline bool draw( int count )
			{
				glDrawArrays( GL_TRIANGLES, 0, count );
				return checkGlError( "glDrawElements" );
			}

			inline bool enableBlending()
			{
				glEnable( GL_BLEND );
				glDisable( GL_CULL_FACE );
				glDepthMask( GL_FALSE );
				return checkGlError( "glEnableBlend" );
			}

			inline bool disableBlending()
			{
				glDisable( GL_BLEND );
				glEnable( GL_CULL_FACE );
				glDepthMask( GL_TRUE );
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
