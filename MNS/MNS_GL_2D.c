#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <string.h>
#include <float.h>

#include "MNS.h"

float _rotation = 0;

void MNS_draw( float l, float h, VEC2 position, float tl, float th, float *vt )
{
	position.x = ( position.x - ( l / 2 ) ) / ( l / 2 );
	position.x = position.x + tl / l;


	position.y = ( ( h / 2 ) - position.y ) / ( h / 2 );
	position.y = position.y - th / h;

	glLoadIdentity();

	glTranslatef( position.x, position.y, 0 );

	glRotatef( _rotation, 0, 0, 1 );
	_rotation += 1;

	l = tl / l;
	h = th / h;

	glBegin( GL_TRIANGLE_STRIP );

	glTexCoord2f( vt[2], vt[3] );
	glVertex2f( l, -h );

	glTexCoord2f( vt[4], vt[5] );
	glVertex2f( l, h );

	glTexCoord2f( vt[0], vt[1] );
	glVertex2f( -l, -h );

	glTexCoord2f( vt[6], vt[7] );
	glVertex2f( -l, h );

	glEnd();


}

void MNS_blit( MNS_RECT tile, MNS_RECTF *t, VEC2 p )
{
	float vt[8];

	if ( t != NULL )
	{
		t->w = t->w / tile.w;
		t->h = t->h / tile.h;

		t->x = t->x / tile.w;
		t->y = t->y / tile.h;

		t->y = -t->y + 1;
		vt[0] = t->x;
		vt[1] = t->y - t->h;

		vt[2] = t->x + t->w;
		vt[3] = t->y - t->h;

		vt[4] = t->x + t->w;
		vt[5] = t->y;

		vt[6] = t->x;
		vt[7] = t->y;

		tile.w = ( int )( tile.w * t->w );
		tile.h = ( int )( tile.h * t->h );
	}
	else
	{
		vt[0] = 0.0;
		vt[1] = 0.0;

		vt[2] = 1.0;
		vt[3] = 0.0;

		vt[4] = 1.0;
		vt[5] = 1.0;

		vt[6] = 0.0;
		vt[7] = 1.0;
	}

	MNS_draw( ( float )tile.x, ( float )tile.y, p, ( float )tile.w, ( float )tile.h, vt );
}

void MNS_DrawArray( float *v, float *vt, int nf )
{
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );

	glVertexPointer( 3, GL_FLOAT, 0, v );
	glTexCoordPointer( 2, GL_FLOAT, 0, vt );

	glDrawArrays( GL_TRIANGLES, 0, nf * 3 );

	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );
}


