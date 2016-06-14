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

#include <string.h>
#include <float.h>

#include "MNS.h"


void MNS_affichage_texture(MNS_image *image)
{
    glTexImage2D (
    GL_TEXTURE_2D, 	//Type : texture 2D
    0, 	//Mipmap : aucun
    image->type, 	//Couleurs : 4
    image->w, 	//Largeur
    image->h, 	//Hauteur
    0, 	//Largeur du bord : 0
    image->format,
    GL_UNSIGNED_BYTE, 	//Type des couleurs
    image->pixel 	//Addresse de l'image
    );
}

void MNS_load_texture(MNS_image *image,int *id)
{
    glGenTextures(1,id);

    glBindTexture(GL_TEXTURE_2D,*id);

    if(image != NULL) MNS_affichage_texture(image);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if(image->type == 4)
    {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }
}

void MNS_affiche_texture(MNS_image *image)
{
    int id;
    glGenTextures(1,&id);

    glBindTexture(GL_TEXTURE_2D,id) ;

    if(image != NULL)
        MNS_affichage_texture(image);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glDeleteTextures(1,&id);

}

void MNS_delete_texture(int *id)
{
    glDeleteTextures(1,id);
}

