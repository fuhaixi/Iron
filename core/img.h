#include<stdio.h>
#include<math.h>
#include<stdlib.h>
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

Img::Img(const char* path){
    FILE* fin = fopen(path, "rb");
    fseek(fin, 0, SEEK_END);
    long size= ftell(fin);
    fseek(fin, 0, SEEK_SET); 

    width = height = sqrt(size/3);
    data = (unsigned char *)malloc(size);
    fread(data, size, 1, fin);
    
}

Img::~Img()
{
    free(data);
}
