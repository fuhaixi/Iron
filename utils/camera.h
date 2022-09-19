#ifndef IRON_CAMERA
#define IRON_CAMERA

#include"core/core_structure.h"
#include"core/os.h"
class Camera
{
private:
    vec2 cam_mv;
public:
    mat4 transform;
    mat4 begin_transform;
    Camera* current;

    vec3 center;

    Camera(/* args */){

    }
    ~Camera(){

    }

    mat4 get_view_mat(){
        return transform.inv();
    }

    void _process(){
        if(OS::get_key('W')) {
            center += -transform.z.xyz * 0.05;
        }

        if(OS::get_key('S')) center += transform.z.xyz * 0.05;
        if(OS::get_key('A')) center += -transform.x.xyz * 0.05;
        if(OS::get_key('D')) center += transform.x.xyz * 0.05;
        if(OS::get_key('Q')) center += transform.y.xyz * 0.05;
        if(OS::get_key('E')) center += -transform.y.xyz * 0.05;

        if(OS::get_key('C')) center = vec3(0);

        if(OS::get_mouse_button(0)){
            cam_mv += OS::cursor_relative * 0.02;
        }

        quat qux(vec3(1,0,0), -cam_mv.y);
        quat quy(vec3(0,1,0), -cam_mv.x);
        quat rot = quy*qux;
        transform = begin_transform.rotated(rot);
        transform.translate(center);


    }

};


#endif