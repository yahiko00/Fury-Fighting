#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MNS.h"

void MNS_free(MNS_image *image)
{
    if(image->pixel != NULL) free(image->pixel);
    if(image->palette != NULL) free(image->palette);
    free(image);
}

static int octets = 0;

MNS_image* MNS_load(const char *adresse)
{
    FILE *fichier = NULL;
    MNS_image *image = NULL;
    char chaine[5];

    fichier = fopen(adresse, "rb");
    if(fichier == NULL)
    {
        fprintf (stderr, "erreur impossible d'ouvrir le fichier : %s\n",adresse);
        return NULL;
    }

    chaine[0] = fgetc(fichier);
    chaine[1] = fgetc(fichier);
    chaine[2] = 0x00;

    if(strcmp(chaine,"BM") == 0 )
    {
        fclose(fichier);
        image = MNS_load_bmp(adresse);
        octets += image->w * image->h * image->type;
        return image;
    }


    fseek(fichier, 0, SEEK_SET);
    fgetc(fichier);
    chaine[0] = fgetc(fichier);
    chaine[1] = fgetc(fichier);
    chaine[2] = fgetc(fichier);
    chaine[3] = 0x00;
    if(strcmp(chaine,"PNG") == 0 )
    {
        fclose(fichier);
        image = MNS_load_png(adresse);
        octets += image->w * image->h * image->type;
        return image;
    }

    fseek(fichier, 0, SEEK_SET);
    chaine[0] = fgetc(fichier);
    if(chaine[0] == 0x0A)
    {
        fclose(fichier);
        image = MNS_load_pcx(adresse);
        octets += image->w * image->h * image->type;
        return image;
    }

    fclose(fichier);

    return NULL;
}

void MNS_printf_octets_image()
{
    printf("Texture size : %d o or %d ko or %.3f mo\n",octets,octets/1000,(float)octets/1000000.0f);
}

void MNS_load_texture_tab(MNS_Model3D *obj,char *dossier)
{
    int i;
    char chaine[100];
    MNS_image *image;
    for(i = 0;i < obj->ntexture;i++)
    {
        sprintf(chaine,"%s%s",dossier,obj->name[i]);

        image = MNS_load(chaine);
        MNS_load_texture(image,&obj->texture[i]);
        MNS_free(image);
    }
}

MNS_Model3D *MNS_load_3D(char *nom_du_fichier)
{
    char ch[100];
    MNS_lecture_chaine_ext(nom_du_fichier,ch,20,'.');

    MNS_Model3D *model = NULL;

    if(strcmp(ch,"obj") == 0)
        model = MNS_load_3D_obj(nom_du_fichier);

    if(strcmp(ch,"smd") == 0)
        model = MNS_load_3D_smd(nom_du_fichier);

    if(strcmp(ch,"bcm") == 0)
        model = MNS_load_3D_bcm(nom_du_fichier);

    return model;
}



/*

void MNS_free_anim(MNS_ANIM *anim)
{
    if(anim->skl != NULL) free(anim->skl);
    //if(anim->k != NULL)   free(anim->k);
    if(anim != NULL)      free(anim);
}

/*
void MNS_free_3D(MNS_3D *obj)
{

    if(obj->v != NULL)      free(obj->v);
    if(obj->va != NULL)     free(obj->va);
    if(obj->vt != NULL)     free(obj->vt);
    if(obj->f != NULL)      free(obj->f);

    if(obj->id != NULL)     free(obj->id);
    if(obj->nodes != NULL)  free(obj->nodes);
    if(obj->bone != NULL)   free(obj->bone);
    if(obj->precl != NULL)  free(obj->precl);


    if(obj->texture.vt != NULL)free(obj->texture.vt);

    //printf("ok5.5\n");
    if(obj->texture.p != NULL) free(obj->texture.p);

    if(obj->type == 0)
    glDeleteLists(obj->list,1);

    if(obj->uv == 0)
    glDeleteTextures(obj->texture.n,obj->idt);

    if(obj->idt != NULL)    free(obj->idt);
    int i;

    if(obj->anim != NULL)
    for(i = 0;i<obj->nanim;i++)
    {

        if(obj->anim[i] != NULL);
        {
            if(i != 0)
            MNS_free_anim(obj->anim[i]);
        }

    }

    if(obj->anim != NULL) free(obj->anim);

    if(obj != NULL)         free(obj);
}

/*
void MNS_free_image_3D(MNS_3D *obj)
{
    int i;
    if(obj->texture.image != NULL)
    {
        for(i = 0;i<obj->texture.n;i++)
        {
            if(obj->texture.image[i] != NULL);
            {
                MNS_free(obj->texture.image[i]);
            }
        }
    }

    if(obj->texture.image != NULL)
    free(obj->texture.image);
}

*/

void MNS_Model_init(MNS_Model3D *obj)
{
    obj->v = NULL;
    obj->vt = NULL;
    obj->vn = NULL;
    obj->va = NULL;
    obj->f = NULL;
    obj->groupe = NULL;
    obj->texture = NULL;
    obj->texture_begin = NULL;
    obj->name = NULL;
    obj->anim = NULL;
    obj->id = NULL;
    obj->bones = NULL;
    obj->precalcul = NULL;
    obj->nodes = NULL;

    obj->nv = 0;
    obj->nf = 0;
    obj->ngroupe = 0;
    obj->ntexture = 0;
    obj->uv = 1;
    obj->time = 0;
    obj->cadence = 0;
    obj->play = 0;
    obj->play_old = 0;
    obj->boucle = 1;
    obj->end = 0;
    obj->nbones = 0;

    obj->defaut.n = 0;
    obj->defaut.ntime = 0;
    obj->defaut.ncadence = 0;
}

