#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <float.h>

#include "MNS_type.h"
#include "MNS_GL_structure.h"

MNS_CAMERA MNS_Camera_Init(float radio)
{
    MNS_CAMERA camera;
    camera.position.x = 0;
    camera.position.y = 0;
    camera.position.z = 0;
    camera.vision.x = 0;
    camera.vision.y = 0;
    camera.vision.z = -1;
    camera.haut.x = 0;
    camera.haut.y = 1;
    camera.haut.z = 0;
    camera.angle = 72;
    camera.min = 0.1f;
    camera.max = 1000;
    camera.radio = radio;

    return camera;
}

void MNS_Camera(MNS_CAMERA camera)
{
    gluLookAt(camera.position.x,camera.position.y,camera.position.z,
              camera.position.x+camera.vision.x,camera.position.y+camera.vision.y,camera.position.z+camera.vision.z,
              camera.haut.x,camera.haut.y,camera.haut.z);
}

void MNS_Camera_Perspective(MNS_CAMERA camera)
{
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(camera.angle,camera.radio,camera.min,camera.max);
    glMatrixMode( GL_MODELVIEW );
}

void MNS_Camera_Ortho()
{
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1,-1,1);
    glMatrixMode(GL_MODELVIEW);
}

void MNS_camera_vue_sub(MNS_CAMERA *camera,VEC3 *a,float v,int *touche)
{
    if(touche[0] == 1)
        a->x += v;

    if(touche[0] == 2)
        a->x -= v;

    if(touche[2] == 1)
        a->y += v;

    if(touche[2] == 2)
        a->y -= v;

    camera->vision.x = cos(a->x)*sin(a->y);
    camera->vision.y = cos(a->y);
    camera->vision.z = -sin(a->x)*sin(a->y);

    if(touche[1] == 1)
    {
        camera->position.z =  camera->position.z + (a->z *camera->vision.z);
        camera->position.x =  camera->position.x + (a->z *camera->vision.x);
        camera->position.y =  camera->position.y + (a->z *camera->vision.y);
    }

    if(touche[1] == 2)
    {
        camera->position.z =  camera->position.z - (a->z *camera->vision.z);
        camera->position.x =  camera->position.x - (a->z *camera->vision.x);
        camera->position.y =  camera->position.y - (a->z *camera->vision.y);
    }
}

void MNS_rotate(float c,float s,float *x,float *y);

void MNS_camera_vue_obj(MNS_CAMERA *camera,VEC3 *p,VEC3 *a,float v,float vit,int *touche)
{
    if(touche[0] == 1)
        a->x += v;

    if(touche[0] == 2)
        a->x -= v;

    if(touche[1] == 1)
        a->y += v;

    if(touche[1] == 2)
        a->y -= v;

    if(a->x > (PI*2)) a->x = a->x - (PI*2);
    if(a->x < 0)      a->x = (PI*2) + a->x;
    if(a->y > (PI*2)) a->y = a->y - (PI*2);
    if(a->y < 0)      a->y = (PI*2) + a->y;

    if(a->y >= PI) camera->haut.y = -1;
    else
    camera->haut.y = 1;

    if(touche[2] == 1) a->z += v;
    if(touche[2] == 2) a->z -= v;

    camera->vision.x = -cos(a->x);
    camera->vision.z =  sin(a->x);
    if(touche[3] == 1)
    {
        p->x += camera->vision.x*vit;
        p->z += camera->vision.z*vit;
    }

    if(touche[3] == 2)
    {
        p->x -= camera->vision.x*vit;
        p->z -= camera->vision.z*vit;
    }

    if(touche[4] == 1)
    {
        camera->vision.x = cos(a->x-PI/2);
        camera->vision.z = -sin(a->x-PI/2);
        p->x += camera->vision.x*vit;
        p->z += camera->vision.z*vit;
    }

    if(touche[4] == 2)
    {
        camera->vision.x = cos(a->x-PI/2);
        camera->vision.z = -sin(a->x-PI/2);
        p->x -= camera->vision.x*vit;
        p->z -= camera->vision.z*vit;
    }

    camera->position.x = cos(a->x)*sin(a->y);
    camera->position.y = cos(a->y);
    camera->position.z = -sin(a->x)*sin(a->y);

    camera->position.x = (camera->position.x*a->z) + p->x;
    camera->position.y = (camera->position.y*a->z) + p->y;
    camera->position.z = (camera->position.z*a->z) + p->z;

    camera->vision.x  = p->x - camera->position.x;
    camera->vision.y  = p->y - camera->position.y;
    camera->vision.z  = p->z - camera->position.z;

    if(touche[4] == 2)
        a->x -= v;

    if(touche[4] == 1)
        a->x += v;

}


