#ifndef IRON_GPU_STRUCTURE
#define IRON_GPU_STRUCTURE

#include<iostream>

struct Rmesh
{
    uint gid = 0;
    size_t size;
};

struct Rshader
{
    uint gid = 0;
};

struct Rtexture{
    uint gid = 0;
    vec2i size;
};

struct Rframebuff
{
    vec2i size;
    uint gid = 0;
};




#endif