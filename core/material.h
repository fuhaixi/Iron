#ifndef IRON_MATERIAL
#define IRON_MATERIAL


#include"shader.h"

class Material
{
private:
    /* data */
public:
    Shader* shader;

    
    Material(/* args */);
    ~Material();
};


#endif