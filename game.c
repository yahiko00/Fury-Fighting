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

#include "MNS/MNS.h"

int MNS_base_tableau( char *nom, char *tab, char *mot, char *adresse );

#if !defined( USE_GLFW )

void test_fps();

void game()

#else

void test_fps( GLFWwindow * window );

void game( GLFWwindow * window )

#endif
{
	MNS_FPS t;
	MNS_event event;

	MNS_CAMERA camera;
	camera = MNS_Camera_Init( ( float )( 800.0 / 600.0 ) );

	MNS_Evenement_init();

	int touche[10];

	VEC3 angle;
	angle.x = 1.6f;
	angle.y = 1.5f;
	angle.z = 1.0f;

	camera.position.x = 7;
	camera.position.y = 115;
	camera.position.z = 100;

	int mode = 1;

	MNS_Model3D *model;

	int perso;
	perso = 0;

	char adresse[100], adresse2[100], chaine[100];
	adresse2[0] = 0;


	MNS_base_tableau( "adr.txt", "[config]", "Load", adresse );
	model = MNS_load_3D( adresse );

	MNS_base_tableau( "adr.txt", "[config]", "Anim", adresse2 );
	if ( adresse2[0] != 0 )
	{
		model->nanim = 2;
		model->anim = malloc( model->nanim * sizeof( MNS_Anim3D ) );

		model->anim[0] = MNS_load_3D_anim( adresse2 );
		model->anim[0]->ncadence = MNS_base_tableau( "adr.txt", "[config]", "cadence", adresse2 );; //vitesse de l'animation
	}

	VEC3 map_position[10];
	MNS_Model3D *map[10];

	for ( int i = 0; i < 10; i++ )
	{
		sprintf( chaine, "obj%d.load", i + 1 );
		MNS_base_tableau( "map.txt", "[map0]", chaine, adresse );
		map[i] = MNS_load_3D( adresse );

		sprintf( chaine, "obj%d.position.x", i + 1 );
		MNS_base_tableau( "map.txt", "[map0]", chaine, adresse );
		map_position[i].x = ( float )atof( adresse );

		sprintf( chaine, "obj%d.position.y", i + 1 );
		MNS_base_tableau( "map.txt", "[map0]", chaine, adresse );
		map_position[i].y = ( float )atof( adresse );

		sprintf( chaine, "obj%d.position.z", i + 1 );
		MNS_base_tableau( "map.txt", "[map0]", chaine, adresse );
		map_position[i].z = ( float )atof( adresse );
	}

#if !defined( USE_GLFW )
	while ( 1 )
#else
	while ( !glfwWindowShouldClose( window ) )
#endif
	{
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );


#if !defined( USE_GLFW )
		//evenement
		event = MNS_Evenement();

		if ( event.touche[27] == 1 ) return;
		if ( event.touche[' '] == 2 ) mode = !mode;
		if ( event.touche[GLUT_KEY_F2 + 255] == 2 ) MNS_imp_ecran( "screen.bmp" );

		//controle de la camera
		for ( i = 0; i < 10; i++ )
			touche[i] = 0;

		if ( event.touche['d'] == 1 ) touche[0] = 1;
		if ( event.touche['g'] == 1 ) touche[0] = 2;

		if ( event.touche['r'] == 1 ) touche[2] = 2;
		if ( event.touche['f'] == 1 ) touche[2] = 1;

		if ( event.touche['a'] == 1 )   touche[1] = 1;
		if ( event.touche['z'] == 1 ) touche[1] = 2;
#else
		//evenement
		event = MNS_Evenement( window );

		if ( event.touche[27] == 1 ) return;
		if ( event.touche[' '] == 2 ) mode = !mode;
		if ( event.touche[GLFW_KEY_F2 + 255] == 2 ) MNS_imp_ecran( "screen.bmp" );

		//controle de la camera
		for ( size_t i = 0; i < 10; i++ )
			touche[i] = 0;

		if ( event.touche['d'] == 1 ) touche[0] = 1;
		if ( event.touche['g'] == 1 ) touche[0] = 2;

		if ( event.touche['r'] == 1 ) touche[2] = 2;
		if ( event.touche['f'] == 1 ) touche[2] = 1;

		if ( event.touche['a'] == 1 )   touche[1] = 1;
		if ( event.touche['z'] == 1 ) touche[1] = 2;
#endif

		//camera
		MNS_Camera_Perspective( camera );
		MNS_camera_vue_sub( &camera, &angle, 0.1f, touche );

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		//---------------------------------
		//affichage

		//printf("%f %f %f\n",camera.position.x,camera.position.y,camera.position.z);

		glLoadIdentity();
		MNS_Camera( camera );
		MNS_rendu( model );
		//MNS_draw_skeleton(model);
		//MNS_draw_skeleton_sp(model,model->anim);

/*
		for(i = 0;i < 10;i++)
		{
			if(map[i] != 0)
			{
				glLoadIdentity();
				MNS_Camera(camera);
				glTranslatef(map_position[i].x,map_position[i].y,map_position[i].z);
				MNS_rendu(map[i]);

			}

		}*/

		test_fps( window );

		//Pour la 2D
		MNS_Camera_Ortho();

		//affichage 2D (HUD ect)

#if !defined( USE_GLFW )

		glutSwapBuffers();

#else

		/* Swap front and back buffers */
		glfwSwapBuffers( window );

#endif

		if ( mode == 1 )
		{
			MNS_Fps( &t, 30 );
		}
	}
}
