#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#if !defined( USE_GLFW )
#	include <GL/freeglut.h>
#else
#	include <GLFW/glfw3.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#if !defined( USE_GLFW )

void game();

int main( int argc, char ** argv )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );//| GLUT_MULTISAMPLE );

	glutInitWindowSize( 800, 600 );
	//glutInitWindowPosition(300,100);
	glutCreateWindow( "test" );

	glClearColor( 0.5, 0.5, 0.5, 0 );
	//glClearColor(0,0,0,0);

	//glEnable(GL_CULL_FACE);

	//glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
	glEnable( GL_TEXTURE_2D );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	game();

	return 0;
}

void test_fps()
{
	char chaine[100];
	int fps = 0, T0 = 0;

	fps++;
	if ( T0 < glutGet( GLUT_ELAPSED_TIME ) )
	{
		sprintf( chaine, "Frame rate: %d", fps );
		T0 = glutGet( GLUT_ELAPSED_TIME ) + 1000;
		fps = 0;
	}

	MNS_Camera_Ortho();
	glLoadIdentity();
	glRasterPos2i( -1, -1 );


	glDisable( GL_TEXTURE_2D );
	glColor4f( 0, 0, 0, 0 );

	glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, chaine );

	glColor4f( 1, 1, 1, 1 );
	glEnable( GL_TEXTURE_2D );
}

#else

void game( GLFWwindow * window );

int main( int argc, char ** argv )
{
	GLFWwindow * window;

	/* Initialize the library */
	if ( !glfwInit() )
	{
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow( 800, 600, "Fury Fighting", NULL, NULL );

	if ( !window )
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent( window );

	game( window );

	glfwTerminate();
	return 0;
}

static double prevTime = 0;

void test_fps( GLFWwindow * window )
{
	char chaine[100];
	int fps = 0, T0 = 0;
	double time = glfwGetTime() - prevTime;

	fps++;
	if ( T0 < time )
	{
		sprintf( chaine, "Fury Fighting - Frame rate: %d", fps );
		T0 = time + 1000;
		fps = 0;
	}

	MNS_Camera_Ortho();
	glLoadIdentity();
	glRasterPos2i( -1, -1 );


	glDisable( GL_TEXTURE_2D );
	glColor4f( 0, 0, 0, 0 );

	glfwSetWindowTitle( window, chaine );

	glColor4f( 1, 1, 1, 1 );
	glEnable( GL_TEXTURE_2D );
}

#endif


