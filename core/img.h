// #define STB_IMAGE_IMPLEMENTATION
#ifndef IRON_IMG
#define IRON_IMG
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"../stb/stb_image.h"
class Img
{
private:
    /* data */
public:
    unsigned int width;
    unsigned int height;
    unsigned char* data;
    Img(/* args */); 
    Img(const char* path);
    ~Img();
};

Img::Img(/* args */)
{

}

// Img::Img(const char* path){
//     FILE* fin = fopen(path, "rb");
//     fseek(fin, 0, SEEK_END);
//     long size= ftell(fin);
//     fseek(fin, 0, SEEK_SET); 

//     width = height = sqrt(size/3);
//     data = (unsigned char *)malloc(size);
//     fread(data, size, 1, fin);
    
// }

Img::Img(const char* path){
    int x,y,c;
    data = stbi_load(path,&x,&y,&c,0);
    
    width = x;
    height = y;
}

Img::~Img()
{
    free(data);
}

#endif