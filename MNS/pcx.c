#include <stdio.h>
#include <stdlib.h>

#include "MNS_structure.h"

void MNS_Image_alpha(MNS_image *image);
MNS_image *MNS_load_pcx(const char *adresse)
{

    MNS_image *image = NULL;

    int i,offset,rle,nbits,version,l;
    unsigned char chaine[5],palette[769];

    FILE *fichier = NULL;
    fichier = fopen(adresse,"rb");

    if(fichier == NULL)
    {
        fprintf (stderr, "erreur impossible d'ouvrir le fichier pcx %s\n",adresse);
        return NULL;
    }

    //indique une adresse a image
    image = malloc(sizeof(MNS_image));

    //Rempli la palette
    offset = 0;

    fseek(fichier,-768,SEEK_END);
    //palette = ftell(fichier);

    for(i = 0;offset != -1;i++)
    {
        offset = fgetc(fichier);
        palette[i] = offset;
    }

    fseek(fichier,0, SEEK_SET);

    //La valeur hexadécimale 0A désigne un fichier PCX.
    chaine[0] = fgetc(fichier);
    if(chaine[0] != 0x0A)
        return NULL;

    //Version
    chaine[0] = fgetc(fichier);
    version = chaine[0];

    //1 si codage RLE est active
    chaine[0] = fgetc(fichier);
    rle = chaine[0];

    //Le nombre de bits par pixel par plan (sur un octet)
    chaine[0] = fgetc(fichier);
    nbits = chaine[0];

    //champ pour les angles
    for(i=0;i < 4;i++)
        fgetc(fichier);

    //résolution horizontale (sur deux octets)
    chaine[0] = fgetc(fichier);
    chaine[1] = fgetc(fichier);
    image->w = chaine[0] + chaine[1]*256+1;


    //résolution verticale (sur deux octets)
    chaine[0] = fgetc(fichier);
    chaine[1] = fgetc(fichier);
    image->h = chaine[0] + chaine[1]*256+1;

    printf("%d %d\n",image->w,image->h);

    for(i=0;i < 4;i++)
        fgetc(fichier);

    //Palette (sur 48 octets)
    offset = 0x40;
    fseek(fichier, offset, SEEK_SET);

    //reserve
    fgetc(fichier);

    //Nombre de plans de couleur (sur un octet)
    chaine[0] = fgetc(fichier);

    //Nombre de bits par ligne (sur 2 octets)
    chaine[0] = fgetc(fichier);
    chaine[1] = fgetc(fichier);

    //Type de palette (sur 2 octets)
    chaine[0] = fgetc(fichier);
    chaine[1] = fgetc(fichier);


    //Creation de la structure image
    image->bits = 24;
    image->format = 6407;
    image->type = 3;
    image->taille  = image->w*image->h*3;
    image->pixel = malloc(image->taille * sizeof(unsigned char));

    //Decodage de image
    offset = 0x80;
    fseek(fichier, offset, SEEK_SET);

    for(i = 0;i < image->taille;)
    {
        chaine[0] = fgetc(fichier);
        if(chaine[0] < 0xC1)
        {
            image->pixel[i+0]= palette[(chaine[0]*3)];
            image->pixel[i+1]= palette[(chaine[0]*3)+1];
            image->pixel[i+2]= palette[(chaine[0]*3)+2];
            i = i+3;
        }else
        {
            chaine[3] = fgetc(fichier);
            rle = 0X3F & chaine[0];
            for(l = 0;l < rle;l++)
            {
                image->pixel[i+0]= palette[(chaine[3]*3)];
                image->pixel[i+1]= palette[(chaine[3]*3)+1];
                image->pixel[i+2]= palette[(chaine[3]*3)+2];
                i = i+3;

                if(i>=image->taille) break;

            }
        }
    }


    fclose(fichier);


    MNS_Image_alpha(image);
    return image;

}


void MNS_Image_alpha(MNS_image *image)
{
    unsigned char *couleur;
    int x,y,i = 0,l = 0;

    if(image == NULL) return;

    image->bits = 32;
    image->format = 6408;
    image->taille  = image->w*image->h*4;

    couleur = malloc(image->taille*sizeof(unsigned char));

    l = image->w*image->h*3 - 3;
    for(y=0;y <image->h;y++)
    {
        for(x=0;x <image->w;x++)
        {
            couleur[i+0] = image->pixel[l+0];
            couleur[i+1] = image->pixel[l+1];
            couleur[i+2] = image->pixel[l+2];
            couleur[i+3] = 0;

            i += 4;

            l -= image->type;
        }
    }

    image->type = 4;
    free(image->pixel);
    image->pixel = couleur;

}
