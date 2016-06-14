#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <float.h>

#include "MNS_type.h"
#include "MNS_GL_structure.h"

void MNS_rotatation(float rotx,float roty,float rotz,float *x,float *y,float *z);

void MNS_bone_rotation(MNS_Model3D *obj)
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

        id = ( int )obj->id[l];


        p.x -= obj->defaut.skeleton[id].p.x;
        p.y -= obj->defaut.skeleton[id].p.y;
        p.z -= obj->defaut.skeleton[id].p.z;

        ty = p.y;
        tz = p.z;
        r = -obj->defaut.skeleton[id].r.x;
        c = ( float )cos(r);
        s = ( float )sin(r);
        p.z = ( c * tz ) - ( s *ty);
        p.y = ( s * tz ) + ( c *ty);

        tx = p.x;
        ty = p.y;
        r = -obj->defaut.skeleton[id].r.y;
        c = ( float )cos(r);
        s = ( float )sin(r);
        p.y = ( c * ty ) - ( s *tx);
        p.x = ( s * ty ) + ( c *tx);

        tx = p.x;
        tz = p.z;
        r = obj->defaut.skeleton[id].r.z;
        c = ( float )cos(r);
        s = ( float )sin(r);
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

/*
void MNS_bone_transition(MNS_Model3D *obj)
{
    int i,id,ida,idas,f;
    f = obj->play;
    float r;

    for(id = 0;id < obj->nbones;id++)
    {
        //interpolation en x
        obj->nodes[id].x = obj->anim[f]->skeleton[id].p.x;

        r = 0;
        i = id;
        r = obj->anim[f]->skeleton[i].r.x;
        obj->precalcul[id].p.x = cos(r);
        obj->precalcul[id].r.x = sin(r);


        //interpolation en y
        obj->nodes[id].y = obj->anim[f]->skeleton[id].p.y;

        r = obj->anim[f]->skeleton[i].r.y;

        obj->precalcul[id].p.y = cos(r);
        obj->precalcul[id].r.y = sin(r);


        //interpolation en z
        obj->nodes[id].z = obj->anim[f]->skeleton[id].p.z;

        r = obj->anim[f]->skeleton[i].r.z;
        obj->precalcul[id].p.z = cos(r);
        obj->precalcul[id].r.z = sin(r);


    }
}
*/
void MNS_bone_rotation_old(MNS_Model3D *obj)
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

        id = ( int )obj->id[l];

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

void MNS_bone_transition_old(MNS_Model3D *obj)
{
    int ida,idas,id,f = obj->play;
    float r;
    VEC3 rot[200];

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
        rot[id].x = r;

        obj->precalcul[id].p.x = ( float )cos(-r);
        obj->precalcul[id].r.x = ( float )sin(-r);

        r = obj->anim[f]->skeleton[idas].r.y - obj->anim[f]->skeleton[ida].r.y;
        r = r/(obj->anim[f]->ncadence+1);
        r = r* obj->cadence;
        r += obj->anim[f]->skeleton[ida].r.y;
        rot[id].y = r;

        obj->precalcul[id].p.y = ( float )cos(-r);
        obj->precalcul[id].r.y = ( float )sin(-r);

        r = obj->anim[f]->skeleton[idas].r.z - obj->anim[f]->skeleton[ida].r.z;
        r = r/(obj->anim[f]->ncadence+1);
        r = r* obj->cadence;
        r += obj->anim[f]->skeleton[ida].r.z;
        rot[id].z = r;

        obj->precalcul[id].p.z = ( float )cos(r);
        obj->precalcul[id].r.z = ( float )sin(r);
    }

    int i;
    VEC3 p;
    float tx,ty,tz,c,s;

    for(i = 0;i < obj->nbones;i++)
    {
        p.x = obj->defaut.skeleton[i].p.x;
        p.y = obj->defaut.skeleton[i].p.y;
        p.z = obj->defaut.skeleton[i].p.z;

        obj->defaut.skeleton[i].r.x = 0;
        obj->defaut.skeleton[i].r.y = 0;
        obj->defaut.skeleton[i].r.z = 0;

        id = i;

        while(1)
        {
            if(id == 0) break;

            p.x -= obj->defaut.skeleton[id].p.x;
            p.y -= obj->defaut.skeleton[id].p.y;
            p.z -= obj->defaut.skeleton[id].p.z;

            obj->defaut.skeleton[i].r.x += rot[id].x;
            obj->defaut.skeleton[i].r.y += rot[id].y;
            obj->defaut.skeleton[i].r.z += rot[id].z;

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
