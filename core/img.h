// #define STB_IMAGE_IMPLEMENTATION
#ifndef IRON_IMG_H
#define IRON_IMG_H
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"../stb/stb_image.h"
class Img
{
private:
    /* data */
public:
    int width;
    int height;
    int chanel;
    unsigned int ref_count=0;

    unsigned char* data = 0;
    Img(/* args */); 
    Img(const char* path, bool flip_v = true);
    Img(const Img& other);
    ~Img();
};

#endif