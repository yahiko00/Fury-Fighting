#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <float.h>

#include "MNS_type.h"
#include "MNS_GL_structure.h"

void MNS_rotatation(float rotx,float roty,float rotz,float *x,float *y,float *z);
float Al_Kashi_C(float a,float b,float c);
float Anglex(VEC3 a,VEC3 b,VEC3 c);

void MNS_bone_rotation(MNS_Model3D *obj)
{
    int id,l;
    float tx,ty,tz,c,s;
    VEC3 p,*v,*va;

    v = (void*)obj->v;
    va = (void*)obj->va;

    for(l = 0;l < obj->nv;l++)
    {
        p.x = v[l].x;
        p.y = v[l].y;
        p.z = v[l].z;

        id = obj->id[l];

        while(1)
        {
            if(id == 0) break;

            p.x -= obj->defaut.skeleton[id].p.x;
            p.y -= obj->defaut.skeleton[id].p.y;
            p.z -= obj->defaut.skeleton[id].p.z;

            ty = p.y;
            tz = p.z;
            c = obj->precalcul[id].p.x;
            s = obj->precalcul[id].r.x;
            p.z = ( c * tz ) - ( s *ty);
            p.y = ( s * tz ) + ( c *ty);

            tx = p.x;
            ty = p.y;
            c = obj->precalcul[id].p.y;
            s = obj->precalcul[id].r.y;
            p.y = ( c * ty ) - ( s *tx);
            p.x = ( s * ty ) + ( c *tx);

            tx = p.x;
            tz = p.z;
            c = obj->precalcul[id].p.z;
            s = obj->precalcul[id].r.z;
            p.x = ( c * tx ) - ( s *tz);
            p.z = ( s * tx ) + ( c *tz);

            p.x += obj->defaut.skeleton[id].p.x;
            p.y += obj->defaut.skeleton[id].p.y;
            p.z += obj->defaut.skeleton[id].p.z;

            id = obj->bones[id];
            if(id == -1) break;
        }


        va[l].x = p.x;
        va[l].y = p.y;
        va[l].z = p.z;
    }
}

void MNS_bone_transition(MNS_Model3D *obj)
{
    int ida,idas,id,f = obj->play;
    float r;

    float x,y,z;
    id = obj->time*obj->nbones;

    if(obj->time < obj->anim[f]->ntime -1)
        idas = (obj->time+1)*obj->nbones;
    else
        idas = 0;


    x = obj->anim[f]->skeleton[idas].p.x - obj->anim[f]->skeleton[id].p.x;
    y = obj->anim[f]->skeleton[idas].p.y - obj->anim[f]->skeleton[id].p.y;
    z = obj->anim[f]->skeleton[idas].p.z - obj->anim[f]->skeleton[id].p.z;

    x = (x/(obj->anim[f]->ncadence+1))*obj->cadence;
    y = (y/(obj->anim[f]->ncadence+1))*obj->cadence;
    z = (z/(obj->anim[f]->ncadence+1))*obj->cadence;


    x += obj->anim[f]->skeleton[id].p.x - obj->defaut.skeleton[0].p.x;
    y += obj->anim[f]->skeleton[id].p.y - obj->defaut.skeleton[0].p.y;
    z += obj->anim[f]->skeleton[id].p.z - obj->defaut.skeleton[0].p.z;

    glTranslatef(x,z,-y);

    r = obj->anim[f]->skeleton[id].r.x - obj->defaut.skeleton[0].r.x;
    r += ( (obj->anim[f]->skeleton[idas].r.x - obj->anim[f]->skeleton[id].r.x)/(obj->anim[f]->ncadence+1) * obj->cadence);
    r = (r/PI)*180;
    glRotatef(r,1,0,0);

    r = obj->anim[f]->skeleton[id].r.y - obj->defaut.skeleton[0].r.y;
    r += ( (obj->anim[f]->skeleton[idas].r.y - obj->anim[f]->skeleton[id].r.y)/(obj->anim[f]->ncadence+1) * obj->cadence);
    r = (r/PI)*180;
    glRotatef(r,0,1,0);

    r = obj->anim[f]->skeleton[id].r.z - obj->defaut.skeleton[0].r.z;
    r += ( (obj->anim[f]->skeleton[idas].r.z - obj->anim[f]->skeleton[id].r.z)/(obj->anim[f]->ncadence+1) * obj->cadence);
    r = (r/PI)*180;
    glRotatef(r,0,0,1);

    for(id = 0;id < obj->nbones;id++)
    {
        ida = id +obj->nbones*obj->time;

        if(obj->time < obj->anim[f]->ntime -1)
            idas = ida + obj->nbones;
        else
        idas = id;

        r = obj->anim[f]->skeleton[idas].r.x - obj->anim[f]->skeleton[ida].r.x;
        r = r/(obj->anim[f]->ncadence+1);
        r = r* obj->cadence;
        r += obj->anim[f]->skeleton[ida].r.x;

        //if(id == 0) r -= obj->defaut.skeleton[id].r.x;

        obj->precalcul[id].p.x = cos(-r);
        obj->precalcul[id].r.x = sin(-r);

        r = obj->anim[f]->skeleton[idas].r.y - obj->anim[f]->skeleton[ida].r.y;
        r = r/(obj->anim[f]->ncadence+1);
        r = r* obj->cadence;
        r += obj->anim[f]->skeleton[ida].r.y;

        obj->precalcul[id].p.y = cos(-r);
        obj->precalcul[id].r.y = sin(-r);


        //if(id == 0) r = 0;

        r = obj->anim[f]->skeleton[idas].r.z - obj->anim[f]->skeleton[ida].r.z;
        r = r/(obj->anim[f]->ncadence+1);
        r = r* obj->cadence;
        r += obj->anim[f]->skeleton[ida].r.z;

        obj->precalcul[id].p.z = cos(r);
        obj->precalcul[id].r.z = sin(r);
    }

    //return;

    int i;
    VEC3 p,p2;
    float tx,ty,tz,c,s;

    for(i = 0;i < obj->nbones;i++)
    {
        p.x = obj->defaut.skeleton[i].p.x;
        p.y = obj->defaut.skeleton[i].p.y;
        p.z = obj->defaut.skeleton[i].p.z;

        p2 = p;
        p2.x = p2.x + 1.0;

        id = i;

        while(1)
        {
            if(id == 0) break;
            p.x -= obj->defaut.skeleton[id].p.x;
            p.y -= obj->defaut.skeleton[id].p.y;
            p.z -= obj->defaut.skeleton[id].p.z;

            ty = p.y;
            tz = p.z;
            c = obj->precalcul[id].p.x;
            s = obj->precalcul[id].r.x;
            p.z = ( c * tz ) - ( s *ty);
            p.y = ( s * tz ) + ( c *ty);

            tx = p.x;
            ty = p.y;
            c = obj->precalcul[id].p.y;
            s = obj->precalcul[id].r.y;
            p.y = ( c * ty ) - ( s *tx);
            p.x = ( s * ty ) + ( c *tx);

            tx = p.x;
            tz = p.z;
            c = obj->precalcul[id].p.z;
            s = obj->precalcul[id].r.z;
            p.x = ( c * tx ) - ( s *tz);
            p.z = ( s * tx ) + ( c *tz);

            p.x += obj->defaut.skeleton[id].p.x;
            p.y += obj->defaut.skeleton[id].p.y;
            p.z += obj->defaut.skeleton[id].p.z;

            id = obj->bones[id];
            if(id == -1) break;
        }


        obj->nodes[i].x = p.x;
        obj->nodes[i].y = p.y;
        obj->nodes[i].z = p.z;
    }


}

//---------------------------------------

void MNS_bone_rotation_old(MNS_Model3D *obj)
{
    int id,l;
    float tx,ty,tz,c,s,r;
    VEC3 p,*v,*va;

    v = (void*)obj->v;
    va = (void*)obj->va;

    for(l = 0;l < obj->nv;l++)
    {
        p.x = v[l].x;
        p.y = v[l].y;
        p.z = v[l].z;

        id = obj->id[l];

        p.x -= obj->defaut.skeleton[id].p.x;
        p.y -= obj->defaut.skeleton[id].p.y;
        p.z -= obj->defaut.skeleton[id].p.z;

        ty = p.y;
        tz = p.z;
        c = obj->precalcul[id].p.x;
        s = obj->precalcul[id].r.x;
        p.z = ( c * tz ) - ( s *ty);
        p.y = ( s * tz ) + ( c *ty);

        tx = p.x;
        ty = p.y;
        c = obj->precalcul[id].p.y;
        s = obj->precalcul[id].r.y;
        p.y = ( c * ty ) - ( s *tx);
        p.x = ( s * ty ) + ( c *tx);

        tx = p.x;
        tz = p.z;
        c = obj->precalcul[id].p.z;
        s = obj->precalcul[id].r.z;
        p.x = ( c * tx ) - ( s *tz);
        p.z = ( s * tx ) + ( c *tz);

        p.x += obj->nodes[id].x;
        p.y += obj->nodes[id].y;
        p.z += obj->nodes[id].z;

        va[l].x = p.x;
        va[l].y = p.y;
        va[l].z = p.z;
    }
}

float hypotenuse(float x,float y,float z);
#define hypotenuse2D(_x_,_y_) sqrt((_x_*_x_) + (_y_*_y_))

float Al_Kashi(float ax,float bx,float cx,float ay,float by,float cy);

static VEC3 calcul_skl(MNS_Model3D *obj,int i,VEC3 add)
{
    int id;
    VEC3 p;
    float tx,ty,tz,c,s;

    p.x = obj->defaut.skeleton[i].p.x + add.x;
    p.y = obj->defaut.skeleton[i].p.y + add.y;
    p.z = obj->defaut.skeleton[i].p.z + add.z;

    id = i;

    while(1)
    {
        if(id == 0) break;

        p.x -= obj->defaut.skeleton[id].p.x;
        p.y -= obj->defaut.skeleton[id].p.y;
        p.z -= obj->defaut.skeleton[id].p.z;

        ty = p.y;
        tz = p.z;
        c = obj->precalcul[id].p.x;
        s = obj->precalcul[id].r.x;
        p.z = ( c * tz ) - ( s *ty);
        p.y = ( s * tz ) + ( c *ty);

        tx = p.x;
        ty = p.y;
        c = obj->precalcul[id].p.y;
        s = obj->precalcul[id].r.y;
        p.y = ( c * ty ) - ( s *tx);
        p.x = ( s * ty ) + ( c *tx);

        tx = p.x;
        tz = p.z;
        c = obj->precalcul[id].p.z;
        s = obj->precalcul[id].r.z;
        p.x = ( c * tx ) - ( s *tz);
        p.z = ( s * tx ) + ( c *tz);

        p.x += obj->defaut.skeleton[id].p.x;
        p.y += obj->defaut.skeleton[id].p.y;
        p.z += obj->defaut.skeleton[id].p.z;

        id = obj->bones[id];
        if(id == -1) break;
    }

    return p;
}

void MNS_bone_transition_old(MNS_Model3D *obj)
{
    int ida,idas,id,f = obj->play;
    float r;
    float x,y,z;
    VEC3 rot[200];

    id = obj->time*obj->nbones;

    if(obj->time < obj->anim[f]->ntime -1)
        idas = (obj->time+1)*obj->nbones;
    else
        idas = 0;

    x = obj->anim[f]->skeleton[idas].p.x - obj->anim[f]->skeleton[id].p.x;
    y = obj->anim[f]->skeleton[idas].p.y - obj->anim[f]->skeleton[id].p.y;
    z = obj->anim[f]->skeleton[idas].p.z - obj->anim[f]->skeleton[id].p.z;

    x = (x/(obj->anim[f]->ncadence+1))*obj->cadence;
    y = (y/(obj->anim[f]->ncadence+1))*obj->cadence;
    z = (z/(obj->anim[f]->ncadence+1))*obj->cadence;


    x += obj->anim[f]->skeleton[id].p.x - obj->defaut.skeleton[0].p.x;
    y += obj->anim[f]->skeleton[id].p.y - obj->defaut.skeleton[0].p.y;
    z += obj->anim[f]->skeleton[id].p.z - obj->defaut.skeleton[0].p.z;

    glTranslatef(x,z,-y);

    r = obj->anim[f]->skeleton[id].r.x - obj->defaut.skeleton[0].r.x;
    r += ( (obj->anim[f]->skeleton[idas].r.x - obj->anim[f]->skeleton[id].r.x)/(obj->anim[f]->ncadence+1) * obj->cadence);
    r = (r/PI)*180;
    glRotatef(r,1,0,0);

    r = obj->anim[f]->skeleton[id].r.y - obj->defaut.skeleton[0].r.y;
    r += ( (obj->anim[f]->skeleton[idas].r.y - obj->anim[f]->skeleton[id].r.y)/(obj->anim[f]->ncadence+1) * obj->cadence);
    r = (r/PI)*180;
    glRotatef(r,0,0,1);

    r = obj->anim[f]->skeleton[id].r.z - obj->defaut.skeleton[0].r.z;
    r += ( (obj->anim[f]->skeleton[idas].r.z - obj->anim[f]->skeleton[id].r.z)/(obj->anim[f]->ncadence+1) * obj->cadence);
    r = (r/PI)*180;
    glRotatef(r,0,-1,0);

    for(id = 0;id < obj->nbones;id++)
    {

        ida = id +obj->nbones*obj->time;

        if(obj->time < obj->anim[f]->ntime -1)
            idas = ida + obj->nbones;
        else
        idas = id;

        r = obj->anim[f]->skeleton[idas].r.x - obj->anim[f]->skeleton[ida].r.x;
        r = r/(obj->anim[f]->ncadence+1);
        r = r* obj->cadence;
        r += obj->anim[f]->skeleton[ida].r.x;
        rot[id].x = -r;

        obj->precalcul[id].p.x = cos(-r);
        obj->precalcul[id].r.x = sin(-r);

        r = obj->anim[f]->skeleton[idas].r.y - obj->anim[f]->skeleton[ida].r.y;
        r = r/(obj->anim[f]->ncadence+1);
        r = r* obj->cadence;
        r += obj->anim[f]->skeleton[ida].r.y;
        rot[id].y = -r;

        obj->precalcul[id].p.y = cos(-r);
        obj->precalcul[id].r.y = sin(-r);

        r = obj->anim[f]->skeleton[idas].r.z - obj->anim[f]->skeleton[ida].r.z;
        r = r/(obj->anim[f]->ncadence+1);
        r = r* obj->cadence;
        r += obj->anim[f]->skeleton[ida].r.z;
        rot[id].z = r;

        obj->precalcul[id].p.z = cos(r);
        obj->precalcul[id].r.z = sin(r);
    }

    int i;
    VEC3 p,mr;
    float tx,ty,tz,c,s,angle;

    for(i = 0;i < obj->nbones;i++)
    {
        p = calcul_skl(obj,i,MNS_vec3(0,0,0));

        mr = calcul_skl(obj,i,MNS_vec3(0,1,0));
        angle = Al_Kashi(p.z,mr.z,p.z , p.y+1,mr.y,p.y);
        if(i == 0) angle = 0;
        if(mr.z > p.z ) angle = -angle;
        rot[i].x = angle;

        mr = calcul_skl(obj,i,MNS_vec3(1,0,0));
        angle = Al_Kashi(p.y,mr.y,p.y , p.x+1,mr.x,p.x);
        if(i == 0) angle = 0;
        if(mr.y > p.y ) angle = -angle;
        rot[i].y = angle;

        mr = calcul_skl(obj,i,MNS_vec3(1,0,0));
        angle = Al_Kashi(p.z,mr.z,p.z , p.x+1,mr.x,p.x);
        if(i == 0) angle = 0;
        if(mr.z < p.z ) angle = -angle;
        rot[i].z = angle;
/*
        obj->cadence = 0;
        obj->time = 3;
/*

        rot[i].x = 0;
        rot[i].z = 0;
*/
        printf("%d : %f %f %f\n",i,rot[i].x,rot[i].y,rot[i].z);

        obj->nodes[i].x = p.x;
        obj->nodes[i].y = p.y;
        obj->nodes[i].z = p.z;
    }


    printf("--------------------\n");

    for(i = 0;i < obj->nbones;i++)
    {
        r = rot[i].x;
        obj->precalcul[i].p.x = cos(r);
        obj->precalcul[i].r.x = sin(r);

        r = rot[i].y;
        obj->precalcul[i].p.y = cos(r);
        obj->precalcul[i].r.y = sin(r);

        r = rot[i].z;
        obj->precalcul[i].p.z = cos(r);
        obj->precalcul[i].r.z = sin(r);
    }

}

float Al_Kashi(float ax,float bx,float cx,float ay,float by,float cy)
{
    float a,b,c,angle;

    a = hypotenuse2D( (ax - cx), (ay - cy) );
    b = hypotenuse2D( (bx - cx), (by - cy) );
    c = hypotenuse2D( (ax - bx), (ay - by) );

    angle = (a*a) + (b*b) - (c*c);
    angle = angle/(2*a*b);
    angle = acos(angle);

    if(isnan(angle) == 1) angle = 0;

    return angle;
}

float hypotenuse(float x,float y,float z)
{
    float h;
    h = sqrt( (x*x) + (z*z) );
    h = (h*h) + (y*y);
    return sqrt(h);
}
