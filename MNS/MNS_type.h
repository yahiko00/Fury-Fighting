#ifndef _MNS_type_
#define _MNS_type_

typedef struct
{
    float x,y;
}VEC2;

typedef struct
{
    int x,y;
}IVEC2;

typedef struct
{
    float x,y,z;
}VEC3;

typedef struct
{
    int x,y,z;
}IVEC3;

typedef struct
{
    float x,y,z,w;
}VEC4;

typedef struct
{
    int x,y,z,w;
}IVEC4;

typedef struct
{
    VEC3 p,r;
}MATRIX3x2;

typedef struct
{
    int x,y,h,w;
}MNS_RECT;

typedef struct
{
    float x,y,h,w;
}MNS_RECTF;

typedef char CHAINE[100];

VEC2 MNS_vec2(float x,float y);
VEC3 MNS_vec3(float x,float y,float z);
VEC4 MNS_vec4(float x,float y,float z,float w);

MNS_RECTF MNS_rectf(float x,float y,float h,float w);
MNS_RECT MNS_rect(short x,short y,short h,short w);

#define  PI 3.141592654


#endif
