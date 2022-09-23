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

Img::Img(/* args */)
{

}

Img::Img(const Img& other){
    width = other.width;
    height = other.height;
    chanel = other.chanel;
    data = other.data;
    ref_count ++;
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

Img::Img(const char* path, bool flip_v){
    int x,y,c;
    stbi_set_flip_vertically_on_load(flip_v); 
    data = stbi_load(path,&x,&y,&c,0);
    if(!data){
        free(data);
        printf("fail load img from %s", path);
    } 
    
    width = x;
    height = y;
    chanel = c;
}

Img::~Img()
{
    ref_count --;

    if(ref_count == 0 && data){
        free(data);
        data = nullptr;
    }
}

#endif