#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifdef __MINGW32__
#include <libpng10/png.h>
#endif

#ifndef __MINGW32__
#include <png.h>
#endif

#include "MNS_structure.h"

MNS_image *MNS_load_png(const char *adresse)
{
    MNS_image *image = NULL;
    int bit_depth, color_type;
    png_byte magic[8];
    png_bytep *row_pointers = NULL;

    int i;

    FILE *fichier = NULL;
    fichier = fopen(adresse,"rb");

    if(fichier == NULL)
    {
        fprintf (stderr, "erreur impossible d'ouvrir le fichier png %s\n",adresse);
        return NULL;
    }

    //indique une adresse a image
    image = malloc(sizeof(MNS_image));
    image->pixel = NULL;
    image->palette = NULL;


    fread (magic, 1, sizeof (magic), fichier);

    #ifdef __MINGW32__
    png_check_sig (magic, sizeof (magic));
    #endif

    #ifndef __MINGW32__
    png_sig_cmp (magic,0, sizeof (magic));
    #endif

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct (png_ptr);

    png_init_io (png_ptr, fichier);

    png_set_sig_bytes (png_ptr, sizeof (magic));

    png_read_info (png_ptr, info_ptr);

    bit_depth = png_get_bit_depth (png_ptr, info_ptr);
    color_type = png_get_color_type (png_ptr, info_ptr);


    if (bit_depth == 16)
        png_set_strip_16 (png_ptr);
    else if (bit_depth < 8)
        png_set_packing (png_ptr);

    png_read_update_info (png_ptr, info_ptr);

    png_get_IHDR (png_ptr, info_ptr,(png_uint_32*)(&image->w),(png_uint_32*)(&image->h),&bit_depth, &color_type,NULL, NULL, NULL);

    switch (color_type)
    {
        case PNG_COLOR_TYPE_GRAY:
          image->format = 6409;
          image->type = 1;
        break;

        case PNG_COLOR_TYPE_GRAY_ALPHA:
          image->format = 6410;
          image->type = 2;
        break;

        case PNG_COLOR_TYPE_RGB:
          image->format = 6407;
          image->type = 3;
        break;

        case PNG_COLOR_TYPE_RGB_ALPHA:
          image->format = 6408;
          image->type = 4;
        break;

        default:
        break;
    }

    image->bits = image->type*8;

    image->taille = image->w*image->h * image->type;

    image->pixel = malloc(image->w*image->h * 4);

    row_pointers = (png_bytep *)malloc (sizeof (png_bytep) * image->h);

    for (i = 0; i < image->h; ++i)
    {
        row_pointers[i] = (png_bytep)(image->pixel +
        ((image->h - (i + 1)) * image->w * image->type));
    }

    /* read pixel data using row pointers */
    png_read_image (png_ptr, row_pointers);

    png_read_end (png_ptr, NULL);
    png_destroy_read_struct (&png_ptr, &info_ptr, NULL);

    free(row_pointers);

    fclose (fichier);

    return image;

}
