#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>

#if !defined( USE_GLFW )
#	include <GL/freeglut.h>
#else
#	include <GLFW/glfw3.h>
#endif

#include "MNS.h"

MNS_event event;
int i;
int fenetre = 0, w, h;
float r = 0;
char tab[600];
int sl = 0, sh = 0;

void MNS_Evenement_init( void )
{
	for ( i = 0; i < 600; i++ )
	{
		event.touche[i] = 0;
		tab[i] = 0;
	}

	event.sourisx = 0;
	event.sourisy = 0;

	event.clikdroit = 0;
	event.clikgauche = 0;
}

void MNS_clavier( unsigned char key, int x, int y )
{
	for ( i = 0; i < 255; i++ )
		if ( key == i ) event.touche[i] = 1;
}

void MNS_clavier_up( unsigned char key, int x, int y )
{
	for ( i = 0; i < 255; i++ )
		if ( key == i ) event.touche[i] = 3;
}

void MNS_clavier_sp( int key, int x, int y )
{
	for ( i = 0; i < 255; i++ )
		if ( key == i ) event.touche[i + 255] = 1;
}

void MNS_clavier_sp_up( int key, int x, int y )
{
	for ( i = 0; i < 255; i++ )
		if ( key == i ) event.touche[i + 255] = 3;
}

void MNS_mouse( int button, int state, int x, int y )
{
	//event.clikdroit = state;

	if ( button == 0 )
	{
		event.clikdroit = 1;

		if ( state == 1 ) event.clikdroit = 2;

	}

	event.sourisx = x;
	event.sourisy = y;
}

void MNS_mouse_position( int x, int y )
{
	event.sourisx = x;
	event.sourisy = y;
}

void MNS_joystick( unsigned int buttonMask, int x, int y, int z )
{
	for ( i = 0; i < 20; i++ )
	{
		if ( buttonMask >> i == 0x01 )
		{
			event.touche[i + 560] = 1;
		}
		else
		{
			if ( event.touche[i + 560] == 1 )
				event.touche[i + 560] = 3;
		}
	}

	//xaxis gauche
	i = 580;
	if ( x == 0 && event.touche[i] == 1 )
		event.touche[i] = 3;

	if ( x < -500 )
		event.touche[i] = 1;

		//xaxis droite
	i = 581;
	if ( x == 0 && event.touche[i] == 1 )
		event.touche[i] = 3;

	if ( x > 500 )
		event.touche[i] = 1;

		//yaxis gauche
	i = 582;
	if ( y == 0 && event.touche[i] == 1 )
		event.touche[i] = 3;

	if ( y < -500 )
		event.touche[i] = 1;

		//yaxis droite
	i = 583;
	if ( y == 0 && event.touche[i] == 1 )
		event.touche[i] = 3;

	if ( y > 500 )
		event.touche[i] = 1;

		//zaxis gauche
	i = 584;
	if ( z == 0 && event.touche[i] == 1 )
		event.touche[i] = 3;

	if ( z < -500 )
		event.touche[i] = 1;

		//zaxis droite
	i = 585;
	if ( z == 0 && event.touche[i] == 1 )
		event.touche[i] = 3;

	if ( z > 500 )
		event.touche[i] = 1;

}

void MNS_MouseWheel( int wheel, int direction, int x, int y )
{
   // printf("%d %d\n",x,y);
}

void MNS_Reshape( int largeur, int hauteur )
{
	glViewport( 0, 0, largeur, hauteur );
	r = ( float )largeur / ( float )hauteur;
	sl = largeur;
	sh = hauteur;
}

void MNS_Fenetre_redimension( float *radio )
{
	if ( r != 0 )
		*radio = r;
}

void MNS_imp_ecran( char *dst )
{
	MNS_image image;
	image.w = sl;
	image.h = sh;

	image.type = 3;
	image.bits = 24;
	image.taille = image.h*image.h * 6;

	unsigned char *buffer = malloc( image.taille * sizeof( unsigned char ) );
	glReadPixels( 0, 0, image.w, image.h, GL_RGB, GL_UNSIGNED_BYTE, buffer );
	image.pixel = buffer;

	MNS_save_bitmap( &image, dst );

	free( buffer );
}

#if !defined( USE_GLFW )

#include <GL/freeglut.h>

MNS_event MNS_Evenement( void )
{
	event.clikdroit = 0;

	for ( i = 0; i < 600; i++ )
	{
		if ( event.touche[i] == 3 )
		{
			event.touche[i] = 0;
			tab[i] = 0;
		}
	}

	glutKeyboardFunc( &MNS_clavier );
	glutKeyboardUpFunc( &MNS_clavier_up );
	glutSpecialFunc( &MNS_clavier_sp );
	glutSpecialUpFunc( &MNS_clavier_sp_up );
	glutMouseFunc( &MNS_mouse );
	glutPassiveMotionFunc( &MNS_mouse_position );
	glutMotionFunc( &MNS_mouse_position );
	glutJoystickFunc( &MNS_joystick, 10 );
	glutMouseWheelFunc( &MNS_MouseWheel );

	glutMainLoopEvent();

	for ( i = 0; i < 600; i++ )
	{
		if ( event.touche[i] == 2 )
			event.touche[i] = 1;



		if ( event.touche[i] == 1 && tab[i] == 0 )
		{
			tab[i] = 1;
			event.touche[i] = 2;
		}

		//if(event.touche[i] > 0)
		//	printf("%d %d\n",i, event.touche[i]);

	}

	return event;
}

void MNS_Display( void )
{
	//glutReshapeWindow(w,h);
}

void MNS_Fenetre( int largeur, int hauteur, int fullscreen )
{
	w = largeur;
	h = hauteur;


	if ( sl == 0 )sl = largeur;
	if ( sh == 0 )sh = hauteur;

	//if(fullscreen == 1)
	//	glutFullScreen();
	//else
	//	glutLeaveFullScreen();

	glutReshapeFunc( &MNS_Reshape );
	glutDisplayFunc( &MNS_Display );
	glutLeaveMainLoop();
}

#else

static int mousex = 0;
static int mousey = 0;

/*! @brief The function for keyboard key callbacks.
*
*  This is the function for keyboard key callback functions.
*
*  @param[in] window The window that received the event.
*  @param[in] key The [keyboard key](@ref keys) that was pressed or released.
*  @param[in] scancode The system-specific scancode of the key.
*  @param[in] action `GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`.
*  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
*  held down.
*/
static void MNS_GLFW_clavier( GLFWwindow * window, int key, int scancode, int action, int mods )
{
	if ( action == GLFW_PRESS )
	{
		MNS_clavier( ( unsigned char )key, 0, 0 );
	}
	else if ( action == GLFW_RELEASE )
	{
		MNS_clavier_up( ( unsigned char )key, 0, 0 );
	}
}

/*! @brief The function for cursor position callbacks.
*
*  This is the function for cursor position callback functions.
*
*  @param[in] window The window that received the event.
*  @param[in] xpos The new x-coordinate, in screen coordinates, of the cursor.
*  @param[in] ypos The new y-coordinate, in screen coordinates, of the cursor.
*/
static void MNS_GLFW_cursorpos( GLFWwindow * window, double xpos, double ypos )
{
	mousex = ( int )xpos;
	mousey = ( int )ypos;
	MNS_mouse_position( mousex, mousey );
}

/*! @brief The function for mouse button callbacks.
*
*  This is the function for mouse button callback functions.
*
*  @param[in] window The window that received the event.
*  @param[in] button The [mouse button](@ref buttons) that was pressed or
*  released.
*  @param[in] action One of `GLFW_PRESS` or `GLFW_RELEASE`.
*  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
*  held down.
*/
static void MNS_GLFW_mousebutton( GLFWwindow * window, int button, int action, int mods )
{
	MNS_mouse( button, action, mousex, mousey );
}

/*! @brief The function for scroll callbacks.
*
*  This is the function for scroll callback functions.
*
*  @param[in] window The window that received the event.
*  @param[in] xoffset The scroll offset along the x-axis.
*  @param[in] yoffset The scroll offset along the y-axis.
*
*  @sa glfwSetScrollCallback
*
*  @ingroup input
*/
static void MNS_GLFW_scroll( GLFWwindow * window, double xoffset, double yoffset )
{
	MNS_MouseWheel( 0, 0, ( int )xoffset, ( int )yoffset );
}

MNS_event MNS_Evenement( GLFWwindow * window )
{
	event.clikdroit = 0;

	for ( i = 0; i < 600; i++ )
	{
		if ( event.touche[i] == 3 )
		{
			event.touche[i] = 0;
			tab[i] = 0;
		}
	}

	glfwSetKeyCallback( window, MNS_GLFW_clavier );
	glfwSetCursorPosCallback( window, MNS_GLFW_cursorpos );
	glfwSetMouseButtonCallback( window, MNS_GLFW_mousebutton );
	glfwSetScrollCallback( window, MNS_GLFW_scroll );

	/* Poll for and process events */
	glfwPollEvents();

	for ( i = 0; i < 600; i++ )
	{
		if ( event.touche[i] == 2 )
			event.touche[i] = 1;



		if ( event.touche[i] == 1 && tab[i] == 0 )
		{
			tab[i] = 1;
			event.touche[i] = 2;
		}

		//if(event.touche[i] > 0)
		//	printf("%d %d\n",i, event.touche[i]);

	}

	return event;
}

void MNS_Display( void )
{
	//glutReshapeWindow(w,h);
}

//void MNS_Fenetre( int largeur, int hauteur, int fullscreen )
//{
//	w = largeur;
//	h = hauteur;
//
//	if ( sl == 0 ) sl = largeur;
//	if ( sh == 0 ) sh = hauteur;
//
//	//if(fullscreen == 1)
//	//	glutFullScreen();
//	//else
//	//	glutLeaveFullScreen();
//
//	glutReshapeFunc( &MNS_Reshape );
//	glutDisplayFunc( &MNS_Display );
//	glutLeaveMainLoop();
//}

#endif

