#ifndef ___LMP3D_Platform_OpenGL_H___
#define ___LMP3D_Platform_OpenGL_H___

#include "LMP3D/Graphics/Common.h"

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

#	define checkGlError( Name ) Platform::CheckError( #Name )
			static uint32_t const ErrorCount = 6;

			inline bool CheckError( char const * const p_name )
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
				GLint GetInternal( PixelFormat format )
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

				GLenum GetFormat( PixelFormat format )
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

			inline bool BindVertexPointer( Vector3Array const & data )
			{
				glEnableClientState( GL_VERTEX_ARRAY );
				glVertexPointer( 3, GL_FLOAT, 0, &data[0] );
				return checkGlError( "glNormalPointer" );
			}

			inline void UnbindVertexPointer()
			{
				glDisableClientState( GL_VERTEX_ARRAY );
			}

			inline bool BindColourPointer( ColourArray const & data )
			{
				glEnableClientState( GL_COLOR_ARRAY );
				glColorPointer( 4, GL_FLOAT, 0, &data[0] );
				return checkGlError( "glColorPointer" );
			}

			inline void UnbindColourPointer()
			{
				glDisableClientState( GL_COLOR_ARRAY );
			}

			inline bool BindNormalPointer( Vector3Array const & data )
			{
				if ( !data.empty() )
				{
					glEnableClientState( GL_NORMAL_ARRAY );
					glNormalPointer( GL_FLOAT, 0, &data[0] );
				}

				return checkGlError( "glNormalPointer" );
			}

			inline void UnbindNormalPointer()
			{
				glDisableClientState( GL_NORMAL_ARRAY );
			}

			inline bool BindTexCoordPointer( Vector2Array const & data )
			{
				if ( !data.empty() )
				{
					glEnableClientState( GL_TEXTURE_COORD_ARRAY );
					glTexCoordPointer( 2, GL_FLOAT, 0, &data[0] );
				}

				return checkGlError( "glNormalPointer" );
			}

			inline void UnbindTexCoordPointer()
			{
				glDisableClientState( GL_TEXTURE_COORD_ARRAY );
			}

			inline bool BindMaterial( Colour4 const & ambient
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

			inline bool LookAt( Vector3 const & position
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

			inline void PushMatrix()
			{
				glPushMatrix();
			}

			inline void PopMatrix()
			{
				glPopMatrix();
			}

			inline bool ApplyTransform( Vector3 const & position, float angle, Vector3 const & axis )
			{
				glRotatef( angle, axis.x, axis.y, axis.z );
				glTranslatef( position.x, position.y, position.z );
				return checkGlError( "glTransform" );
			}

			inline bool Viewport( Size const & size )
			{
				glViewport( 0, 0, size.x, size.y );
				return checkGlError( "glViewport" );
			}

			inline bool Perspective( float angle, float ratio, float near, float far )
			{
				glEnable( GL_DEPTH_TEST );
				glMatrixMode( GL_PROJECTION );
				glLoadIdentity();
				gluPerspective( angle, ratio, near, far );
				return checkGlError( "glPerspective" );
			}

			inline bool Ortho( float left, float right, float bottom, float top, float near, float far )
			{
				glDisable( GL_DEPTH_TEST );
				glMatrixMode( GL_PROJECTION );
				glLoadIdentity();
				glOrtho( left, right, bottom, top, near, far );
				return checkGlError( "glOrtho" );
			}

			inline unsigned int CreateTexture()
			{
				unsigned int ret = GL_INVALID_INDEX;
				glGenTextures( 1, &ret );
				return ret;
			}

			inline bool BindTexture( unsigned int id )
			{
				glBindTexture( GL_TEXTURE_2D, id );
				return checkGlError( "glBindTexture" );
			}

			inline bool InitialiseTexture( Size const & size, PixelFormat format, ByteArray const & data )
			{
				glTexImage2D( GL_TEXTURE_2D, 0, GetInternal( format ), size.x, size.y, 0, GetFormat( format ), GL_UNSIGNED_BYTE, &data[0] );
				glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
				glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
				return checkGlError( "glTexImage2D" );
			}

			inline void UnbindTexture()
			{
				glBindTexture( GL_TEXTURE_2D, 0 );
			}

			inline void DeleteTexture( unsigned int id )
			{
				glDeleteTextures( 1, &id );
			}

			inline bool Draw( int count )
			{
				glDrawArrays( GL_TRIANGLES, 0, count );
				return checkGlError( "glDrawElements" );
			}

			inline bool EnableBlending()
			{
				glEnable( GL_BLEND );
				glDepthMask( GL_FALSE );
				return checkGlError( "glEnableBlend" );
			}

			inline bool DisableBlending()
			{
				glDisable( GL_BLEND );
				glDepthMask( GL_TRUE );
				return checkGlError( "glDisableBlend" );
			}
		}
	}
}

#endif
