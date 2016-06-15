#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MNS.h"

#define TAILLE_MAX 1000

MNS_image* MNS_load( const char *adresse );


MNS_Model3D *MNS_load_3D_bcm( char *nom_du_fichier )
{
	FILE* fichier = NULL;
	int i, l;

	MNS_Model3D *obj;
	obj = malloc( sizeof( MNS_Model3D ) );

	MNS_Model_init( obj );
	obj->format = 3;

	fichier = fopen( nom_du_fichier, "rb" );
	int octet = 0;

	if ( fichier != NULL )
	{
		//signature
		fgetc( fichier );
		fgetc( fichier );
		fgetc( fichier );
		fgetc( fichier );

		//version / info
		fgetc( fichier );
		obj->type = fgetc( fichier );
		//obj->type = 0x01;

		//offset
		octet = read_type_short( fichier );
		fseek( fichier, octet, SEEK_SET );

		//nombre de vertex/texture/normal
		obj->nv = read_type_long( fichier );
		obj->v = malloc( obj->nv * 3 * sizeof( float ) );
		obj->vt = malloc( obj->nv * 2 * sizeof( float ) );
		obj->vn = malloc( obj->nv * 3 * sizeof( float ) );

		obj->va = obj->v;

		if ( obj->type & 0x02 )
		{
			obj->id = malloc( obj->nv * sizeof( float ) );
			obj->va = malloc( obj->nv * 3 * sizeof( float ) );
		}


		for ( i = 0; i < obj->nv; i++ )
		{
			obj->v[i * 3 + 0] = read_type_float( fichier );
			obj->v[i * 3 + 1] = read_type_float( fichier );
			obj->v[i * 3 + 2] = read_type_float( fichier );

			obj->vn[i * 3 + 0] = read_type_float( fichier );
			obj->vn[i * 3 + 1] = read_type_float( fichier );
			obj->vn[i * 3 + 2] = read_type_float( fichier );

			obj->vt[i * 2 + 0] = read_type_float( fichier );
			obj->vt[i * 2 + 1] = read_type_float( fichier );

			if ( obj->type & 0x02 )
			{
				obj->va[i * 3 + 0] = obj->v[i * 3 + 0];
				obj->va[i * 3 + 1] = obj->v[i * 3 + 1];
				obj->va[i * 3 + 2] = obj->v[i * 3 + 2];
				obj->id[i] = read_type_short( fichier );
			}

		}

		//nombre de face /index
		obj->nf = read_type_long( fichier );

		obj->f = malloc( obj->nf * 3 * sizeof( short ) );

		for ( i = 0; i < obj->nf * 3; i++ )
			obj->f[i] = read_type_short( fichier );


		//texture
		obj->ntexture = read_type_short( fichier );

		obj->name = malloc( obj->ntexture * sizeof( CHAINE ) );
		obj->texture = malloc( obj->ntexture * sizeof( int ) );
		obj->texture_begin = malloc( obj->ntexture * sizeof( int ) );

		for ( i = 0; i < obj->ntexture; i++ )
		{
			for ( l = 0; l < 20; l++ )
				obj->name[i][l] = fgetc( fichier );

			obj->texture_begin[i] = read_type_long( fichier );
		}

		if ( obj->type & 0x02 )
		{
			//skeleton nodes
			obj->nbones = read_type_short( fichier );

			obj->bones = malloc( obj->nbones * sizeof( short ) );
			obj->nodes = malloc( obj->nbones * sizeof( VEC3 ) );
			obj->precalcul = malloc( obj->nbones * sizeof( MATRIX3x2 ) );

			for ( i = 0; i < obj->nbones; i++ )
			{
				for ( l = 0; l < 20; l++ )
					fgetc( fichier );

				obj->bones[i] = read_type_short( fichier );
			}

			//Animation
			obj->defaut.ntime = read_type_short( fichier );

			obj->defaut.n = obj->defaut.ntime * obj->nbones;
			obj->defaut.skeleton = malloc( obj->defaut.n * sizeof( MATRIX3x2 ) );

			for ( i = 0; i < obj->defaut.n; i++ )
			{
				obj->defaut.skeleton[i].p.x = read_type_float( fichier );
				obj->defaut.skeleton[i].p.y = read_type_float( fichier );
				obj->defaut.skeleton[i].p.z = read_type_float( fichier );

				obj->defaut.skeleton[i].r.x = read_type_float( fichier );
				obj->defaut.skeleton[i].r.y = read_type_float( fichier );
				obj->defaut.skeleton[i].r.z = read_type_float( fichier );
			}
		}

		fclose( fichier );
	}

	printf( "%d %d\n", obj->nv, obj->nf );

	char dossier[100];
	MNS_dossier_out( nom_du_fichier, dossier );
	MNS_load_texture_tab( obj, dossier );

	return obj;
}

void MNS_write_bcm( MNS_Model3D *model, char *dst )
{
	FILE* fichier = NULL;
	int i, l;
	int ok, n = 0;


	fichier = fopen( dst, "wb" );

	if ( fichier != NULL )
	{
		//signature
		fputs( "BCM", fichier );
		fputc( 0, fichier );

		//info version et info
		fputc( 0, fichier );
		fputc( model->type | 0x01, fichier );

		//offset
		write_type_short( fichier, 8 );

		int tp = 0;

		if ( model->type & 0x01 )
			tp = 1;
		else
			tp = 0;

		//vertex
		VEC3 *v = ( void* )model->v;
		VEC3 *vn = ( void* )model->vn;
		VEC2 *vt = ( void* )model->vt;
		if ( tp == 0 )
		{
			unsigned short *f = malloc( model->nf * 3 * sizeof( short ) );

			VEC3 *va = malloc( model->nv * sizeof( VEC3 ) );
			VEC3 *van = malloc( model->nv * sizeof( VEC3 ) );
			VEC2 *vat = malloc( model->nv * sizeof( VEC2 ) );
			short *id = malloc( model->nv * sizeof( short ) );

			for ( i = 0; i < model->nv; i++ )
			{
				ok = 0;
				for ( l = 0; l < i; l++ )
				{
					if (
						v[i].x == v[l].x && v[i].y == v[l].y && v[i].z == v[l].z &&
						vt[i].x == vt[l].x && vt[i].y == vt[l].y &&
						vn[i].x == vn[l].x && vn[i].y == vn[l].y && vn[i].z == vn[l].z
						)
					{
						ok = 1;
						l = i;
					}
				}

				if ( ok == 0 )
				{
					va[n].x = v[i].x;
					va[n].y = v[i].y;
					va[n].z = v[i].z;

					van[n].x = vn[i].x;
					van[n].y = vn[i].y;
					van[n].z = vn[i].z;

					vat[n].x = vt[i].x;
					vat[n].y = vt[i].y;

					if ( model->type & 0x02 )
						id[n] = ( short )model->id[i];

					f[i] = n;
					n++;

				}
				else
				{
					for ( l = 0; l < n; l++ )
					{
						if (
							v[i].x == va[l].x && v[i].y == va[l].y && v[i].z == va[l].z &&
							vt[i].x == vat[l].x && vt[i].y == vat[l].y &&
							vn[i].x == van[l].x && vn[i].y == van[l].y && vn[i].z == van[l].z
							)
						{
							ok = l;
							l = i;
						}
					}
					f[i] = ok;
				}

			}

			//nombre de vertex
			write_type_long( fichier, n );

			for ( i = 0; i < n; i++ )
			{
				write_type_float( fichier, va[i].x );
				write_type_float( fichier, va[i].y );
				write_type_float( fichier, va[i].z );

				write_type_float( fichier, van[i].x );
				write_type_float( fichier, van[i].y );
				write_type_float( fichier, van[i].z );

				write_type_float( fichier, vat[i].x );
				write_type_float( fichier, vat[i].y );

				if ( model->type & 0x02 )
					write_type_short( fichier, id[i] );
			}

			//nombre de face
			write_type_long( fichier, model->nf );
			for ( i = 0; i < model->nf * 3; i++ )
			{
				write_type_short( fichier, f[i] );
			}

			free( van );
			free( vat );
			free( va );
			free( f );

			if ( model->type & 0x02 )
				free( id );




		}
		else
		{

			//nombre de vertex
			write_type_long( fichier, model->nv );

			for ( i = 0; i < model->nv; i++ )
			{
				write_type_float( fichier, v[i].x );
				write_type_float( fichier, v[i].y );
				write_type_float( fichier, v[i].z );

				write_type_float( fichier, vn[i].x );
				write_type_float( fichier, vn[i].y );
				write_type_float( fichier, vn[i].z );

				write_type_float( fichier, vt[i].x );
				write_type_float( fichier, vt[i].y );

				if ( model->type & 0x02 )
					write_type_short( fichier, ( short )model->id[i] );
			}
			//nombre de face
			write_type_long( fichier, model->nf );

			for ( i = 0; i < model->nf * 3; i++ )
			{
				if ( model->f != NULL )
					write_type_short( fichier, model->f[i] );
				else
					write_type_short( fichier, i );
			}

		}

		//texture
		write_type_short( fichier, model->ntexture );
		for ( i = 0; i < model->ntexture; i++ )
		{

			fputs( model->name[i], fichier );
			n = 20 - strlen( model->name[i] );
			for ( l = 0; l < n; l++ )
				fputc( 0, fichier );

			write_type_long( fichier, model->texture_begin[i] );
		}

		if ( model->type & 0x02 )
		{
			//Skeleton nodes
			write_type_short( fichier, model->nbones );

			for ( i = 0; i < model->nbones; i++ )
			{
				for ( l = 0; l < 20; l++ )
					fputc( 0, fichier );

				write_type_short( fichier, model->bones[i] );
			}

			//Animation
			write_type_short( fichier, model->defaut.ntime );
			for ( i = 0; i < model->nbones; i++ )
			{
				write_type_float( fichier, model->defaut.skeleton[i].p.x );
				write_type_float( fichier, model->defaut.skeleton[i].p.y );
				write_type_float( fichier, model->defaut.skeleton[i].p.z );
				write_type_float( fichier, model->defaut.skeleton[i].r.x );
				write_type_float( fichier, model->defaut.skeleton[i].r.y );
				write_type_float( fichier, model->defaut.skeleton[i].r.z );
			}
		}

		fclose( fichier );
	}
}

