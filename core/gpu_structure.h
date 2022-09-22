#ifndef IRON_GPU_STRUCTURE
#define IRON_GPU_STRUCTURE

#include<iostream>

struct Rmesh
{
    uint gid;
    size_t size;
};

struct Rshader
{
    uint gid;
};

struct Rtexture{
    uint gid;
    vec2i size;
};

struct Rframebuff
{
    vec2i size;
    uint gid;
};




#endif