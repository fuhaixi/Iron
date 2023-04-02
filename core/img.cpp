#include "img.h"


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

