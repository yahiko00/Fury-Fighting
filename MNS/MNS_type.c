#include <stdlib.h>
#include <stdio.h>

#include "MNS.h"

VEC2 MNS_vec2(float x,float y)
{
    VEC2 v;
    v.x = x;
    v.y = y;

    return v;
}

VEC3 MNS_vec3(float x,float y,float z)
{
    VEC3 v;
    v.x = x;
    v.y = y;
    v.z = z;

    return v;
}

VEC4 MNS_vec4(float x,float y,float z,float w)
{
    VEC4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;

    return v;
}


MNS_RECTF MNS_rectf(float x,float y,float w,float h)
{
    MNS_RECTF v;
    v.x = x;
    v.y = y;
    v.h = h;
    v.w = w;

    return v;
}

MNS_RECT MNS_rect(short x,short y,short w,short h)
{
    MNS_RECT v;
    v.x = x;
    v.y = y;
    v.h = h;
    v.w = w;

    return v;
}

