#ifndef IRON_OBJECT
#define IRON_OBJECT
#include"core_structure.h"
#include"mesh.h"
#include "material.h"
#include"gpu_structure.h"

class Object
{
private:
   

public:
    mat4 transform;
    Rmesh rmesh;
    Rshader rshader;
    
    
    Object(/* args */){
        
    }

    ~Object();
};


#endif