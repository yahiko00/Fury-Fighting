#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <float.h>

#include "MNS_structure.h"

void MNS_rotatation(float rotx,float roty,float rotz,float *x,float *y,float *z)
{
    float tx,ty,tz,c,s;

    //x axis
    ty = *y,tz = *z;

    c = cos(rotx);
    s = sin(rotx);
    *y = ( c * ty ) - ( s * tz );
    *z = ( s * ty ) + ( c * tz );

    //y axis
    tx = *x,tz = *z;

    c = cos(roty);
    s = sin(roty);
    *z = ( c * tz ) - ( s * tx );
    *x = ( s * tz ) + ( c * tx );

    //z axis
    tx = *x,ty = *y;

    c = cos(-rotz);
    s = sin(-rotz);
    *y = ( c * ty ) - ( s * tx );
    *x = ( s * ty ) + ( c * tx );
}


void MNS_rotate(float c,float s,float *x,float *y)
{
    float tx,ty;

    tx = *x,ty = *y;

    *x = ( c * tx ) - ( s *ty);
    *y = ( s * tx ) + ( c *ty);
}


void MNS_rotate_position(float px,float py,float pz,float rotx,float roty,float rotz,float *posx,float *posy,float *posz)
{
    float tx,ty,tz,c,s;


    *posx -= px;
    *posy -= py;
    *posz -= pz;

    ty = *posy;
    tz = *posz;
    c = cos(rotx);
    s = sin(rotx);
    *posy = ( c * ty ) - ( s * tz );
    *posz = ( s * ty ) + ( c * tz );

    tx = *posx;
    ty = *posy;
    c = cos(roty);
    s = sin(roty);
    *posz = ( c * tz ) - ( s * tx );
    *posx = ( s * tz ) + ( c * tx );


    tx = *posx;
    tz = *posz;
    c = cos(rotz);
    s = sin(rotz);
    *posy = ( c * ty ) - ( s * tx );
    *posx = ( s * ty ) + ( c * tx );


    *posx += px;
    *posy += py;
    *posz += pz;


}

float Al_Kashi_C(float a,float b,float c)
{
    double t,k,r;
    t = ( (a*a) + (b*b) ) - (c*c);
    k = 2*a*b;
    r = acos(t/k);
    //printf("%f/%f = %f   ",t,k,r);

    return r;
}

float hypothenuse(float a,float b)
{
    return sqrt( (a*a) + (b*b) );
}

typedef struct
{
    float x,y,z;
}VEC3;

float Anglex(VEC3 a,VEC3 b,VEC3 c)
{
    float A,B,C,r;
    a.x += 1;
    a.y += 1;
    A = hypothenuse(b.x - c.x,b.y - c.y);
    B = hypothenuse(a.x - c.x,a.y - c.y);
    C = hypothenuse(a.x - b.x,a.y - b.y);

    r = Al_Kashi_C(A,B,C);
    //r = 0;

    return r;
}
