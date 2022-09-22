#ifndef IRON_VIEWER
#define IRON_VIEWER

#include "core_structure.h"
class Viewer
{
private:
    mat4 transform;

public:
    mat4 projection;
    mat4 view;
    Viewer(/* args */){

    }
    ~Viewer(){

    }
    void set_transform(mat4 val){
        transform = val;
        view = val.inv();
    }

    mat4 get_tranform(){
        return transform;
    }
};



#endif