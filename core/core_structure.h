#ifndef CORE_STRUCTURE_H
#define CORE_STRUCTURE_H
#include<stdio.h>
#include<math.h>
struct vec2{
    float x;
    float y;

    vec2(){
        x=0;
        y=0;
    }

    vec2(float _x, float _y){
        x= _x;
        y= _y;
    }

    vec2(float val){
        x = val;
        y = val;
    }
};


struct vec2i{
    float x;
    float y;

    vec2i(){
        x=0;
        y=0;
    }

    vec2i(int _x, int _y){
        x= _x;
        y= _y;
    }

    vec2i(int val){
        x = val;
        y = val;
    }
};

struct vec3{
    float x;
    float y;
    float z;

    vec3(){
        x=0;
        y=0;
        z=0;
    }

    vec3(float val){
        x = val;
        y=val;
        z=val;
    }

    vec3(vec2 xy, float _z){
        x = xy.x;
        y= xy.y;
        z = _z;
    }
    
    vec3(float _x, float _y, float _z){
        x= _x;
        y = _y;
        z = _z;
    }

    vec3 operator *(const vec3& other)const{
        return vec3(x*other.x, y*other.y, z*other.z);
    }

    vec3 operator +(const vec3& other)const{
        return vec3(x+other.x, y+other.y, z+other.z);
    }
    void operator+=(const vec3& other){
        *this = *this + other;
    }

    vec3 operator -(const vec3& other)const{
        return vec3(x-other.x, y-other.y, z-other.z);
    }

    float dot(const vec3 other)const{
        return x*other.x + y*other.y + z * other.z;
    }

    vec3 cross(const vec3 other)const{
        vec3 ret;
        ret.x = y*other.z - z*other.y;
        ret.y = x*other.z - z*other.x;
        ret.z = x*other.y - y*other.x;
        return ret;
    }

    vec3 operator*(float val)const{


        return vec3(x*val, y*val, z*val);
    }

    void print(){
        printf("{%f, %f, %f}", x,y,z);
    }
};


struct vec3i{
    int x;
    int y;
    int z;

    vec3i(){
        x=0;
        y=0;
        z=0;
    }

    vec3i(int val){
        x = val;
        y=val;
        z=val;
    }

    vec3i(vec2i xy, float _z){
        x = xy.x;
        y= xy.y;
        z = _z;
    }
    
    vec3i(float _x, float _y, float _z){
        x= _x;
        y = _y;
        z = _z;
    }

    void print(){
        printf("{%d, %d, %d}", x,y,z);
    }
};


struct vec4{
    union
    {
        struct{
            float x;
            float y;
            float z;
        };
        vec3 xyz;
        
    };
    float w;

    vec4(){
        x =0;
        y =0;
        z =0;
        w =0;
    }

    vec4(float _x, float _y, float _z, float _w){
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    vec4(float val){
        x =val;
        y =val;
        z =val;
        w =val;
    }

    vec4(vec3 vec, float _w){
        xyz = vec;
        w = _w;
    }


};

struct vec4i{
  int x,y,z,w;

    vec4i(){
        x =0;
        y =0;
        z =0;
        w =0;
    }

    vec4i(int val){
        x =val;
        y =val;
        z =val;
        w =val;
    }

    vec4i(vec3i vec, float _w){
        x = vec.x;
        y = vec.y;
        z = vec.z;
        w = _w;
    }

    vec4 byte2float(){
        vec4 color;
        color.x = x/255.f;
        color.y = y/255.f;
        color.z = z/255.f;
        color.w = w/255.f;
        return color;
    }

};

struct mat3{
    vec3 x;
    vec3 y;
    vec3 z;

    mat3(){
        x= vec3(1,0,0);
        y= vec3(0,1,0);
        z= vec3(0,0,1);
    }

    mat3(vec3 _x, vec3 _y, vec3 _z){
        x = _x;
        y = _y;
        z = _z;
    }

    const vec3 operator *(const vec3 vec){
        return x*vec + y*vec + z*vec;
    }

    
};

struct mat4{
    vec4 x;
    vec4 y;
    vec4 z;
    vec4 w;

    static mat4 ortho(float far, float near, float width, float height){
        mat4 ret;
        ret.x = vec4(2*near/width,0,0,0);
        ret.y = vec4(0, 2*near/height,0,0);
        ret.z = vec4(0,0,-(far+near)/(far-near), -1);
        ret.w = vec4(0,0,-2*far*near/(far-near),0);
        return ret;
    }

    static mat4 persp(float far, float near, float width, float height){
        mat4 ret;
        ret.x = vec4(2*near/width, 0,0,0);
        ret.y = vec4(0,2*near/height,0,0);
        ret.z = vec4(0, 0,-(far+near)/(far-near),-1);
        ret.w = vec4(0, 0,-2*far*near/(far-near),0);
        return ret;
    }
    

    mat4(){
        x = vec4(1.f, 0.f, 0.f, 0.f);
        y = vec4(0.f, 1.f, 0.f, 0.f);
        z = vec4(0.f, 0.f, 1.f, 0.f);
        w = vec4(0.f, 0.f, 0.f, 1.f);
    }

    

    mat4(mat3 basis, vec3 position){
        x.xyz = basis.x;
        y.xyz = basis.y;
        z.xyz = basis.z;
        x.w=0;
        y.w=0;
        z.w=0;
        w.xyz = position;
        w.w = 1;
    }

    mat4 inv(){
        mat4 ret;
        ret.x = vec4(x.x, y.x, z.x, w.x);
        ret.y = vec4(x.y, y.y, z.y, w.y);
        ret.y = vec4(x.y, y.y, z.y, w.y);
        ret.z = vec4(x.z, y.z, z.z, w.z);
        return ret;
    }

    mat4 translated(vec3 translation){
        w.xyz = w.xyz + translation;
        return *this;
    }

    mat4 rotated(vec3 axis, float angle){
        //TODO
        
        
        return *this;
    }



    float* data(){
        return &x.x;
    }

};

struct quat{
    union
    {
        struct{
            float x;
            float y;
            float z;
        };
        vec3 xyz;
        
    };
    float w;

    quat(){
        xyz = vec3(0,0,0);
        w = 1;
    }

    quat(float p_x, float p_y, float p_z, float p_w){
        x = p_x;
        y = p_y;
        z = p_z;
        w = p_w;
    }

    quat(vec3 axis, float angle){
        xyz = axis*sin(angle/2.0);
        w = cos(angle/2.0)*1.0;
    }

    quat inv(){
        xyz = xyz*(-1.0);
    }


    // quat operator *(const quat other){
        
    // }

    vec3 operator* (const vec3 val)const{
        vec3 ret;
        ret = xyz*2.0f* xyz.dot(val);
        auto t = val *  1;
        auto tt = xyz.dot(xyz);
        ret += val*( w*w - xyz.dot(xyz));
        ret += xyz.cross(val)*2.0f*w;
        return ret;
    }

    mat3 operator* (const mat3 m)const{
        mat3 ret;
        ret.x = *this *m.x;
        ret.y = *this *m.y;
        ret.z = *this *m.z;
        return ret;
    }

};


struct point{
    vec3 vertex;
    vec3 normal;
    vec2 uv;
    vec4 color;
};

#endif