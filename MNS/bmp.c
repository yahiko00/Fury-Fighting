#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MNS_structure.h"

MNS_image *MNS_load_bmp(const char *adresse)
{

    MNS_image *image = NULL;

    int i,offset;
    unsigned char chaine[5];
    char chain[5];

    FILE *fichier = NULL;
    fichier = fopen(adresse,"rb");

    if(fichier == NULL)
    {
        fprintf (stderr, "erreur impossible d'ouvrir le fichier bmp %s\n",adresse);
        return NULL;
    }

    //indique une adresse a image
    image = malloc(sizeof(MNS_image));
    image->pixel = NULL;
    image->palette = NULL;

    chain[0] = fgetc(fichier);
    chain[1] = fgetc(fichier);
    chain[2] = 0x00;

    //taille du fichier
    for(i=0;i < 4;i++)
        fgetc(fichier);

    //champ réservé (sur 4 octets)
    for(i=0;i < 4;i++)
        fgetc(fichier);

    //offset est en Hexa
    chaine[0] = fgetc(fichier);
    chaine[1] = fgetc(fichier);
    chaine[2] = fgetc(fichier);
    chaine[3] = fgetc(fichier);

    //je doute que offset sera plus grand que 255 ou 0xFF
    offset = chaine[0];

    //Info sur OS
    for(i=0;i < 4;i++)
        fgetc(fichier);

    //largeur de image
    chaine[0] = fgetc(fichier);
    chaine[1] = fgetc(fichier);
    chaine[2] = fgetc(fichier);
    chaine[3] = fgetc(fichier);

    image->w = chaine[0] + chaine[1]*256 + chaine[2]*256*256 + chaine[3]*256*256*256;

    //hauteur de image
    chaine[0] = fgetc(fichier);
    chaine[1] = fgetc(fichier);
    chaine[2] = fgetc(fichier);
    chaine[3] = fgetc(fichier);

    image->h = chaine[0] + chaine[1]*256 + chaine[2]*256*256 + chaine[3]*256*256*256;

    //valeur est egale a 1
    for(i=0;i < 2;i++)
        fgetc(fichier);

    //taille du codage (1 a 32 bits)
    chaine[0] = fgetc(fichier);
    fgetc(fichier);
    image->bits = chaine[0];

    //Info supplementaires pour opengl
    if(image->bits == 24)
    {
        image->format = 6407;
        image->type = 3;
    }
    if(image->bits == 32)
    {
        image->type = 4;
        image->format = 6408;
    }

    //Methode de compression RLE (flemme de le coder =3)
    for(i=0;i < 4;i++)
        fgetc(fichier);


    //taille en octet de image
    chaine[0] = fgetc(fichier);
    chaine[1] = fgetc(fichier);
    chaine[2] = fgetc(fichier);
    chaine[3] = fgetc(fichier);

    image->taille = chaine[0] + chaine[1]*256 + chaine[2]*256*256 + chaine[3]*256*256*256;

    fseek(fichier, offset, SEEK_SET);

    //Decodage de image
    image->pixel = malloc(image->taille * sizeof(unsigned char)); // On alloue de la mémoire pour le tableau

    for(i=0;i<image->taille;i = i+image->type )
    {
        //les format bitmap ce lise en BVR
        chaine[0] = fgetc(fichier);
        chaine[1] = fgetc(fichier);
        chaine[2] = fgetc(fichier);
        image->pixel[i]= chaine[2];
        image->pixel[i+1]= chaine[1];
        image->pixel[i+2]= chaine[0];

        if(image->type == 4)
        {
            chaine[3] = fgetc(fichier);
            image->pixel[i]= chaine[3];
        }
    }


    fclose(fichier);

    return image;

}

void MNS_save_bitmap(MNS_image *image,char *adresse)
{
    int i;
    unsigned char octet;
    int tmp;

    FILE *fichier = NULL;
    fichier = fopen(adresse,"wb");

    if(fichier == NULL)
        return;

    if(fichier != NULL)
    {

        fputc('B',fichier);
        fputc('M',fichier);

        //taille du fichier
        tmp = 0x36 + (image->w*image->h*image->type);
        octet = tmp;
        fputc(octet,fichier);

        octet = tmp >> 8;
        fputc(octet,fichier);

        octet = tmp >> 16;
        fputc(octet,fichier);

        octet = tmp >> 24;
        fputc(octet,fichier);

        //champ réservé (sur 4 octets)
        for(i=0;i < 4;i++)
            fputc(0,fichier);

        //offset est en Hexa
        fputc(0x36,fichier);
        fputc(0,fichier);
        fputc(0,fichier);
        fputc(0,fichier);


        //Info sur OS
        fputc(0x28,fichier);
        fputc(0,fichier);
        fputc(0,fichier);
        fputc(0,fichier);

        //largeur de image
        tmp = image->w;
        octet = tmp;
        fputc(octet,fichier);

        octet = tmp >> 8;
        fputc(octet,fichier);

        octet = tmp >> 16;
        fputc(octet,fichier);

        octet = tmp >> 24;
        fputc(octet,fichier);

        //hauteur de image
        tmp = image->h;
        octet = tmp;
        fputc(octet,fichier);

        octet = tmp >> 8;
        fputc(octet,fichier);

        octet = tmp >> 16;
        fputc(octet,fichier);

        octet = tmp >> 24;
        fputc(octet,fichier);

        //valeur est egale a 1
        fputc(1,fichier);
        fputc(0,fichier);

        //taille du codage (1 a 32 bits)
        fputc(image->bits,fichier);
        fputc(0,fichier);

        //Methode de compression RLE (flemme de le coder =3)
        for(i=0;i < 4;i++)
            fputc(0,fichier);


        //taille en octet de image
        tmp = (image->w*image->h*image->type);
        octet = tmp;
        fputc(octet,fichier);

        octet = tmp >> 8;
        fputc(octet,fichier);

        octet = tmp >> 16;
        fputc(octet,fichier);

        octet = tmp >> 24;
        fputc(octet,fichier);

        //résolution horizontale
        for(i=0;i < 4;i++)
            fputc(0,fichier);

        //résolution verticale
        for(i=0;i < 4;i++)
            fputc(0,fichier);

        //Le nombre de couleurs de la palette
        for(i=0;i < 4;i++)
            fputc(0,fichier);

        //Le nombre de couleurs importantes de la palette
        for(i=0;i < 4;i++)
            fputc(0,fichier);

        int n;
        n = image->w*image->h*image->type;
        for(i=0;i<n;i = i+image->type)
        {
            //les format bitmap ce lise en BVR
            fputc(image->pixel[i+2],fichier);
            fputc(image->pixel[i+1],fichier);
            fputc(image->pixel[i+0],fichier);

            if(image->type == 4)
                fputc(image->pixel[i+3],fichier);

        }

        fclose(fichier);
    }
}
