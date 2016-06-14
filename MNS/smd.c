#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <GL/glew.h>

#if !defined( USE_GLFW )
#	include <GL/freeglut.h>
#else
#	include <GLFW/glfw3.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include "MNS.h"

#define TAILLE_MAX 1000

void MNS_SMD_create_skeleton( MNS_Anim3D *anim, int n, short *bones );
void MNS_rotatation( float rotx, float roty, float rotz, float *x, float *y, float *z );

MNS_Model3D *MNS_load_3D_smd( char *nom_du_fichier )
{
	FILE* fichier = NULL;
	char chaine[TAILLE_MAX] = "";

	MNS_Model3D *obj;
	obj = malloc( sizeof( MNS_Model3D ) );

	char chiffre[100];
	char ch[100], dossier[100], material[100];
	material[0] = 0;

	int header = 0, lecture = 0, k, l, ifc = 0, ib = 0, v = 0;
	dossier[0] = 0;

	MNS_Model_init( obj );
	obj->type = 0x02;
	obj->format = 1;



	fichier = fopen( nom_du_fichier, "r" );
	if ( fichier != NULL )
	{
		while ( ( !feof(fichier ) ) && fgets( chaine, TAILLE_MAX, fichier ) != NULL )
		{
			MNS_lecture_chaine( chaine, ch, 0 );

			if ( strcmp( ch, "end" ) == 0 )
				header = 0;

			if ( header == 1 )
				obj->nbones++;

			if ( header == 2 )
			{
				if ( strcmp( "time", ch ) == 0 )
					obj->defaut.ntime++;
				else
					obj->defaut.n++;
			}

			if ( header == 3 )
			{
				if ( lecture == 0 )
				{
					if ( strcmp( material, ch ) != 0 )
					{
						strcpy( material, ch );
						obj->ntexture++;
					}
					obj->nf++;
				}

				if ( lecture == 3 )
					lecture = -1;

				lecture++;
			}

			if ( strcmp( ch, "nodes" ) == 0 )
				header = 1;

			if ( strcmp( ch, "skeleton" ) == 0 )
				header = 2;

			if ( strcmp( ch, "triangles" ) == 0 )
				header = 3;

		}


		obj->nv = 3 * obj->nf;
		obj->v = malloc( obj->nv * 3 * sizeof( float ) );
		obj->vt = malloc( obj->nv * 2 * sizeof( float ) );
		obj->vn = malloc( obj->nv * 3 * sizeof( float ) );
		obj->va = malloc( obj->nv * 3 * sizeof( float ) );

		obj->texture = malloc( obj->ntexture * sizeof( int ) );
		obj->texture_begin = malloc( obj->ntexture * sizeof( int ) );
		obj->name = malloc( obj->ntexture * sizeof( CHAINE ) );


		obj->id = malloc( obj->nv * 1 * sizeof( float ) );
		obj->bones = malloc( obj->nbones * 1 * sizeof( short ) );
		obj->nodes = malloc( obj->nbones * 1 * sizeof( VEC3 ) );
		obj->precalcul = malloc( obj->nbones * 1 * sizeof( MATRIX3x2 ) );
		obj->defaut.skeleton = malloc( obj->defaut.n * 1 * sizeof( MATRIX3x2 ) );

		fseek( fichier, 0, SEEK_SET );
		material[0] = 0;


		while ( ( !feof( fichier ) ) && fgets( chaine, TAILLE_MAX, fichier ) != NULL )
		{
			MNS_lecture_chaine( chaine, ch, 0 );

			if ( strcmp( ch, "end" ) == 0 )
				header = 0;

			if ( header == 1 )
			{
				l = atoi( ch );
				MNS_lecture_chaine( chaine, ch, 2 );
				obj->bones[l] = atoi( ch );
			}

			if ( header == 2 )
			{
				if ( strcmp( "time", ch ) == 0 )
				{
					MNS_lecture_chaine( chaine, ch, 1 );
					l = atoi( ch );
				}
				else
				{
					k = atoi( ch ) + ( l*obj->nbones );

					MNS_lecture_chaine( chaine, ch, 1 );
					obj->defaut.skeleton[k].p.x = ( float )atof( ch );
					MNS_lecture_chaine( chaine, ch, 2 );
					obj->defaut.skeleton[k].p.z = ( float )atof( ch );
					MNS_lecture_chaine( chaine, ch, 3 );
					obj->defaut.skeleton[k].p.y = -( float )atof( ch );

					MNS_lecture_chaine( chaine, ch, 4 );
					obj->defaut.skeleton[k].r.x = ( float )atof( ch );
					MNS_lecture_chaine( chaine, ch, 5 );
					obj->defaut.skeleton[k].r.y = ( float )atof( ch );
					MNS_lecture_chaine( chaine, ch, 6 );
					obj->defaut.skeleton[k].r.z = ( float )atof( ch );
				}

			}

			if ( header == 3 )
			{
				if ( lecture == 0 )
				{
					if ( strcmp( material, ch ) != 0 )
					{
						strcpy( material, ch );
						strcpy( obj->name[ib], ch );
						obj->texture_begin[ib] = ifc * 3;

						ib++;
					}
					ifc++;
				}

				if ( lecture >= 1 )
				{
					MNS_lecture_chaine( chaine, chiffre, 1 );
					obj->v[v * 3 + 0] = ( float )atof( chiffre );
					MNS_lecture_chaine( chaine, chiffre, 2 );
					obj->v[v * 3 + 2] = ( float )atof( chiffre );
					MNS_lecture_chaine( chaine, chiffre, 3 );
					obj->v[v * 3 + 1] = -( float )atof( chiffre );


					obj->va[v * 3 + 0] = obj->v[v * 3 + 0];
					obj->va[v * 3 + 1] = obj->v[v * 3 + 1];
					obj->va[v * 3 + 2] = obj->v[v * 3 + 2];

					MNS_lecture_chaine( chaine, chiffre, 4 );
					obj->vn[v * 3 + 0] = ( float )atof( chiffre );
					MNS_lecture_chaine( chaine, chiffre, 5 );
					obj->vn[v * 3 + 1] = ( float )atof( chiffre );
					MNS_lecture_chaine( chaine, chiffre, 6 );
					obj->vn[v * 3 + 2] = ( float )atof( chiffre );

					MNS_lecture_chaine( chaine, chiffre, 7 );
					obj->vt[v * 2 + 0] = ( float )atof( chiffre );
					MNS_lecture_chaine( chaine, chiffre, 8 );
					obj->vt[v * 2 + 1] = ( float )atof( chiffre );

					MNS_lecture_chaine( chaine, chiffre, 0 );
					obj->id[v] = ( float )atoi( chiffre );

					v++;

					if ( lecture == 3 )
						lecture = -1;
				}

				lecture++;
			}

			if ( strcmp( ch, "nodes" ) == 0 )
				header = 1;

			if ( strcmp( ch, "skeleton" ) == 0 )
				header = 2;

			if ( strcmp( ch, "triangles" ) == 0 )
				header = 3;
		}

		fclose( fichier );
	}

	MNS_dossier_out( nom_du_fichier, dossier );
	MNS_load_texture_tab( obj, dossier );

	MNS_SMD_create_skeleton( &obj->defaut, obj->nbones, obj->bones );

	return obj;
}


MNS_Anim3D *MNS_load_3D_anim( char *nom_du_fichier )
{
	FILE* fichier = NULL;
	char chaine[TAILLE_MAX] = "";
	MNS_Anim3D *anim;
	anim = malloc( sizeof( MNS_Anim3D ) );

	int header = 0, k;
	char ch[100];

	int nbones = 0, l;
	short bones[200];

	anim->n = 0;
	anim->ntime = 0;


	fichier = fopen( nom_du_fichier, "r" );
	if ( fichier != NULL )
	{

		while ( fgets( chaine, TAILLE_MAX, fichier ) != NULL )
		{
			MNS_lecture_chaine( chaine, ch, 0 );

			if ( strcmp( ch, "end" ) == 0 )
				header = 0;

			if ( header == 1 )
				nbones++;

			if ( header == 2 )
			{
				if ( strcmp( "time", ch ) == 0 )
					anim->ntime++;
				else
					anim->n++;
			}

			if ( strcmp( ch, "skeleton" ) == 0 )
				header = 2;

			if ( strcmp( ch, "nodes" ) == 0 )
				header = 1;
		}

		fseek( fichier, 0, SEEK_SET );

		anim->skeleton = malloc( anim->n * sizeof( MATRIX3x2 ) );

		while ( fgets( chaine, TAILLE_MAX, fichier ) != NULL )
		{
			MNS_lecture_chaine( chaine, ch, 0 );

			if ( strcmp( ch, "end" ) == 0 )
				header = 0;

			if ( header == 1 )
			{
				l = atoi( ch );
				MNS_lecture_chaine( chaine, ch, 2 );
				bones[l] = atoi( ch );
			}

			if ( header == 2 )
			{
				if ( strcmp( "time", ch ) == 0 )
				{
					MNS_lecture_chaine( chaine, ch, 1 );
					l = atoi( ch );
				}
				else
				{

					k = atoi( ch ) + ( l*nbones );

					MNS_lecture_chaine( chaine, ch, 1 );
					anim->skeleton[k].p.x = ( float )atof( ch );
					MNS_lecture_chaine( chaine, ch, 2 );
					anim->skeleton[k].p.z = ( float )atof( ch );
					MNS_lecture_chaine( chaine, ch, 3 );
					anim->skeleton[k].p.y = -( float )atof( ch );

					MNS_lecture_chaine( chaine, ch, 4 );
					anim->skeleton[k].r.x = ( float )atof( ch );
					MNS_lecture_chaine( chaine, ch, 5 );
					anim->skeleton[k].r.y = ( float )atof( ch );
					MNS_lecture_chaine( chaine, ch, 6 );
					anim->skeleton[k].r.z = ( float )atof( ch );
				}

			}

			if ( strcmp( ch, "skeleton" ) == 0 )
				header = 2;

			if ( strcmp( ch, "nodes" ) == 0 )
				header = 1;
		}

		fclose( fichier );
	}


	MNS_SMD_create_skeleton( anim, nbones, bones );

	return anim;
}


void MNS_SMD_create_skeleton( MNS_Anim3D *anim, int n, short *bones )
{
	VEC3 bone[200], p[200];
	int id, i, l;
	float rx, ry, rz;




	for ( l = 0; l < anim->ntime; l++ )
	{
		for ( i = 0; i < n; i++ )
		{
			id = i;
			bone[i].x = 0;
			bone[i].y = 0;
			bone[i].z = 0;

			while ( 1 )
			{

				bone[i].x += anim->skeleton[id + l*n].p.x;
				bone[i].y += anim->skeleton[id + l*n].p.y;
				bone[i].z += anim->skeleton[id + l*n].p.z;

				id = bones[id];

				if ( id == -1 ) break;
			}

			p[i].x = bone[i].x;
			p[i].y = bone[i].y;
			p[i].z = bone[i].z;
		}


		for ( i = 0; i < n; i++ )
		{
			id = i;

			while ( 1 )
			{
				bone[i].x -= p[id].x;
				bone[i].y -= p[id].y;
				bone[i].z -= p[id].z;

				rx = anim->skeleton[id + l*n].r.x;
				ry = anim->skeleton[id + l*n].r.y;
				rz = anim->skeleton[id + l*n].r.z;

				MNS_rotatation( rx, ry, rz, &bone[i].x, &bone[i].y, &bone[i].z );

				bone[i].x += p[id].x;
				bone[i].y += p[id].y;
				bone[i].z += p[id].z;

				id = bones[id];

				if ( id == -1 ) break;
			}

			anim->skeleton[i + l*n].p.x = bone[i].x;
			anim->skeleton[i + l*n].p.y = bone[i].y;
			anim->skeleton[i + l*n].p.z = bone[i].z;

		}
	}
}
