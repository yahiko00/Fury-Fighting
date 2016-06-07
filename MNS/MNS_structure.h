#ifndef _MNS_structure_
#define _MNS_structure_

typedef struct
{
    int ta;
    int tp;

}MNS_FPS;

typedef struct
{
  unsigned short w;
  unsigned short h;
  unsigned char *pixel,*palette;
  int taille;
  short bits;
  short format;
  short type;

}MNS_image;

typedef struct
{
    short clikdroit;
    short clikgauche;
    short sourisx;
    short sourisy;
    short quit;

    char touche[600];

}MNS_event;


#endif
