#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>

#if !defined( USE_GLFW )
#	include <GL/freeglut.h>
#else
#	include <GLFW/glfw3.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <float.h>

#include "MNS.h"

void MNS_openglva(MNS_Model3D *obj)
{
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );

    glVertexPointer(3,GL_FLOAT,0,obj->va);
    glTexCoordPointer(2,GL_FLOAT,0,obj->vt);
    glNormalPointer(GL_FLOAT,0,obj->vn);

    int i,end,begin;


    if(obj->uv <= 0 || obj->ntexture == 0)
    {
        if(obj->uv == -1)
            glBindTexture(GL_TEXTURE_2D,0);

        if(obj->type & 0x01)
            glDrawElements(GL_TRIANGLES,obj->nf*3,GL_UNSIGNED_SHORT,obj->f);
        else
            glDrawArrays( GL_TRIANGLES,0,obj->nf*3);
    }
    else
    for(i = 0;i < obj->ntexture;i++)
    {
        glBindTexture(GL_TEXTURE_2D,obj->texture[i]);

        begin = obj->texture_begin[i];

        if(i+1 < obj->ntexture)
            end = obj->texture_begin[i+1];
        else
            end = obj->nf*3;

        end -= begin;

        if(obj->type & 0x01)
            glDrawElements(GL_TRIANGLES,end,GL_UNSIGNED_SHORT,obj->f + begin);
        else
            glDrawArrays( GL_TRIANGLES, begin,end);

    }

    glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );
}


void MNS_rendu(MNS_Model3D *obj)
{

    if(obj->anim != NULL)
    {
        MNS_bone_transition_old(obj);
        MNS_bone_rotation_old(obj);
    }

    if(obj->type & 0x02)
        glRotatef(90,-1,0,0);

    glScalef(5,5,5);
    MNS_openglva(obj);

    if(obj->anim == NULL) return;

    int n = obj->play;

    if(obj->play != obj->play_old)
    {
        obj->play_old = obj->play;
        obj->cadence = 0;
        obj->time = 0;
    }

    obj->cadence++;
    if(obj->cadence >= obj->anim[n]->ncadence)
    {
        obj->cadence = 0;
        obj->time++;
    }

    obj->end = 0;
    if(obj->time >= obj->anim[n]->ntime)
    {
        obj->cadence = 0;
        obj->time = 0;
        obj->end = 1;
    }
}

void MNS_draw_skeleton(MNS_Model3D *obj)
{
    if(obj->nodes == NULL) return;


    glBindTexture(GL_TEXTURE_2D,0);
    int i;
    float x,y,z;
    glPointSize(5);
    glColor3f(1.0f, 0.0f, 0.0f);
    for(i = 0;i < obj->nbones;i++)
    {
        x = obj->nodes[i].x;
        y = obj->nodes[i].y;
        z = obj->nodes[i].z;

        glBegin(GL_POINTS);
        glVertex3f(x,y,z);
        glEnd();
    }

    glColor3f(0.0f, 1.0f, 0.0f);
    int id;
    for(i = 0;i < obj->nbones;i++)
    {
        x = obj->nodes[i].x;
        y = obj->nodes[i].y;
        z = obj->nodes[i].z;

        glBegin(GL_LINES);
        glVertex3f( x,y,z);

        id = obj->bones[i];
        if(id < 0) id = i;

        x = obj->nodes[id].x;
        y = obj->nodes[id].y;
        z = obj->nodes[id].z;

        glVertex3f( x,y,z);
        glEnd();
    }

    glColor3f(1.0f, 1.0f, 1.0f);
}

void MNS_draw_skeleton_sp(MNS_Model3D *obj,MNS_Anim3D anim)
{
    glBindTexture(GL_TEXTURE_2D,0);
    int i,l;
    float x,y,z;
    glPointSize(5);
    glColor3f(1.0f, 0.0f, 0.0f);
    for(i = 0;i < obj->nbones;i++)
    {
        l = i + (obj->nbones*obj->time);
        if(obj->time > anim.ntime) l = i;

        x = anim.skeleton[l].p.x;
        y = anim.skeleton[l].p.y;
        z = anim.skeleton[l].p.z;

        glBegin(GL_POINTS);
        glVertex3f( x,y,z);
        glEnd();
    }

    glColor3f(0.0f, 1.0f, 0.0f);
    int id;
    for(i = 0;i < obj->nbones;i++)
    {
        l = i + (obj->nbones*obj->time);
        if(obj->time > anim.ntime) l = i;


        x = anim.skeleton[l].p.x;
        y = anim.skeleton[l].p.y;
        z = anim.skeleton[l].p.z;

        glBegin(GL_LINES);
        glVertex3f( x,y,z);

        id = obj->bones[i];
        if(id < 0) id = i;

        l = id + (obj->nbones*obj->time);
        if(obj->time > anim.ntime) l = id;

        x = anim.skeleton[l].p.x;
        y = anim.skeleton[l].p.y;
        z = anim.skeleton[l].p.z;

        glVertex3f( x,y,z);
        glEnd();
    }

    glColor3f(1.0f, 1.0f, 1.0f);
}
