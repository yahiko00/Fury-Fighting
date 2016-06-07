#ifndef _MNS_STRUCTURE_GL_
#define _MNS_STRUCTURE_GL_

typedef struct
{
    VEC3 position;
    VEC3 vision;
    VEC3 haut;
    float angle,radio,min,max;
}MNS_CAMERA;

typedef struct
{
    MATRIX3x2 *skeleton;
    short ntime,ncadence,n;
}MNS_Anim3D;

typedef struct
{
    //Mesh
    float *v,*vt,*vn,*va;
    int nv,nf;
    unsigned short *f;

    //groupe
    unsigned short *groupe;
    short ngroupe;

    //Texture
    int *texture,*texture_begin;
    short ntexture,uv;
    CHAINE *name;

    //Animation
    short time; //frame
    short play_old,cadence; // variable temporaire
    short play,boucle,end; //control de animation read/write
    short nanim;//nombre animation
    MATRIX3x2 *precalcul; //precalcul de cos/sin
    VEC3 *nodes; //skelette nodes


    MNS_Anim3D defaut,**anim; //Squelette
    float *id; //attribut pour chaque vertex
    short *bones; //relation entre bones parent/enfant
    short nbones; //nombre de bones

    //Autre information
    short format; //format obj = 0 , smd = 1 ,pmd = 2,bcm = 3,md5 = 4
    short type; //Drapeau 0x01 = (0)Array/(1)Index ,0x02 = (0)Static/(1)Anim

    //Opengl
    int VBO[3]; //VBO
    int shaders; //shader
    int dlist; //display list



}MNS_Model3D;

#endif
