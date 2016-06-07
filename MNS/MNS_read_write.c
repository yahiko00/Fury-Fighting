#include <stdio.h>
#include <stdlib.h>


short read_type_short(FILE *fichier)
{
    int octet,itype;
    octet = fgetc(fichier);
    itype = octet;

    octet = fgetc(fichier);
    itype += octet<<8;

    return itype;
}

long read_type_long(FILE *fichier)
{
    int octet ,itype;
    octet = fgetc(fichier);
    itype = octet;

    octet = fgetc(fichier);
    itype += octet<<8;

    octet = fgetc(fichier);
    itype += octet << 16;

    octet = fgetc(fichier);
    itype += octet << 24;

    return itype;
}

float read_type_float(FILE *fichier)
{
    int octet ,itype;
    octet = fgetc(fichier);
    itype = octet;

    octet = fgetc(fichier);
    itype += octet<<8;

    octet = fgetc(fichier);
    itype += octet << 16;

    octet = fgetc(fichier);
    itype += octet << 24;

    void *ftype = &itype;
    float *g = ftype;

    return *g;
}

void write_type_short(FILE *fichier,short itype)
{
    int octet;

    octet = itype;
    fputc(octet,fichier);

    octet = itype>>8;
    fputc(octet,fichier);
}

void write_type_long(FILE *fichier,long itype)
{
    int octet;

    octet = itype;
    fputc(octet,fichier);

    octet = itype>>8;
    fputc(octet,fichier);

    octet = itype>>16;
    fputc(octet,fichier);

    octet = itype>>24;
    fputc(octet,fichier);
}

void write_type_int(FILE *fichier,int itype)
{
    int octet;

    octet = itype;
    fputc(octet,fichier);

    octet = itype>>8;
    fputc(octet,fichier);

    octet = itype>>16;
    fputc(octet,fichier);

    octet = itype>>24;
    fputc(octet,fichier);
}

void write_type_float(FILE *fichier,float g)
{
    int *itype = (void*)&g;
    fputc((*itype),fichier);
    fputc((*itype)>>8,fichier);
    fputc((*itype)>>16,fichier);
    fputc((*itype)>>24,fichier);
}
