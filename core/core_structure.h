#ifndef CORE_STRUCTURE_H
#define CORE_STRUCTURE_H
#include<stdio.h>
#include<math.h>

#include<string.h>
#include<iostream>

#define PI 3.14159265358979323846 

struct vec2{
    union 
    {
        struct{
            float x;
            float y;
        };
        float components[3];
    };
    
    

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

    vec2 operator -(const vec2& other)const{
        return vec2(x-other.x, y-other.y);
    }

    vec2 operator +(const vec2& other)const{
        return vec2(x+other.x, y+other.y);
    }

    vec2 operator *(const float val){
        return vec2(x*val, y*val);
    }

    void operator =(const vec2& other){
        x = other.x;
        y = other.y;
    }

    void operator +=(const vec2& other){
        *this = *this + other;
    }

    float& operator [](const int index){
        return components[index%2];
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
    union 
    {
        struct 
        {
            float x;
            float y;
            float z;
        };
        
        float components[3];
    };
    
    

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

    void set(float _x, float _y, float _z){
        x = _x;
        y = _y;
        z = _z;
    }

    void normalize(){
        float len = length();
        if(len == 0){
            set(0,0,0);
            return;
        }
        x = x/len;
        y = y/len;
        z = z/len;

    }

    vec3 normalized(){
        vec3 ret = *this;
        ret.normalize();
        return ret;
    }

    float length(){
        return sqrt(x*x +y*y +z*z);
    }

    float length_squared(){
        return x*x + y*y + z*z;
    }

    vec3 operator *(const vec3 other)const{
        return vec3(x*other.x, y*other.y, z*other.z);
    }

    void operator *=(const vec3 other){
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
    }

    vec3 operator +(const vec3 other)const{
        return vec3(x+other.x, y+other.y, z+other.z);
    }
    void operator+=(const vec3 other){
        *this = *this + other;
    }

    vec3 operator -(const vec3 other)const{
        return vec3(x-other.x, y-other.y, z-other.z);
    }


    void operator -=(const vec3 other){
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;

    }

    vec3 operator- ()const{
        return vec3(-x, -y, -z);
    }

    float dot(const vec3 other)const{
        return x*other.x + y*other.y + z * other.z;
    }

    vec3 cross(const vec3 p_b)const{
        vec3 ret(
			(y * p_b.z) - (z * p_b.y),
			(z * p_b.x) - (x * p_b.z),
			(x * p_b.y) - (y * p_b.x));

	    return ret;
    }

    vec3 operator*(float val)const{


        return vec3(x*val, y*val, z*val);
    }

    float & operator[](const int index){
        
        return components[index%3];
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

    void print(){
        printf("(%f,%f,%f),", x.x, x.y, x.z);
        printf("(%f,%f,%f),", y.x, y.y, y.z);
        printf("(%f,%f,%f)", z.x, z.y, z.z);
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

    void set(float _x, float _y, float _z, float _w){
        x= _x;
        y = _y;
        z = _z;
        w = _w;
        
    }

    quat(float p_x, float p_y, float p_z, float p_w){
        x = p_x;
        y = p_y;
        z = p_z;
        w = p_w;
    }

    quat(const vec3 &v0, const vec3 &v1) // shortest arc
	{
		vec3 c = v0.cross(v1);
		float d = v0.dot(v1);

		if (d < -1.0 + 0.001) {
			x = 0;
			y = 1;
			z = 0;
			w = 0;
		} else {
			float s = sqrt((1.0 + d) * 2.0);
			float rs = 1.0 / s;

			x = c.x * rs;
			y = c.y * rs;
			z = c.z * rs;
			w = s * 0.5;
		}
	}

    quat(vec3 axis, float angle){
        float d = axis.length();
        if (d == 0) {
           set(0,0,0,0);
        } else {
            float sin_angle = sin(angle * 0.5);
            float cos_angle = cos(angle * 0.5);
            float s = sin_angle / d;
            set(axis.x * s, axis.y * s, axis.z * s, cos_angle);
	    }
    }

    quat operator*(quat& rhs) {
        quat q;

        q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
        q.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
        q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
        q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;

        return q;
    }

    void inv(){
        xyz = xyz*(-1.0f);
    }


    // quat operator *(const quat other){
        
    // }

    vec3 operator* (const vec3 v)const{

 

        vec3 u(x, y, z);
		vec3 uv = u.cross(v);


		return v + ((uv * w) + u.cross(uv)) * (2.0);
    }

    mat3 operator* (const mat3 m)const{
        mat3 ret;
        ret.x = *this *m.x;
        ret.y = *this *m.y;
        ret.z = *this *m.z;
        return ret;
    }

    void print(){
        
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
    
    static mat4 simu_camera(mat4 cam_trans){
        mat4 ret;
        ret.w.xyz = -cam_trans.w.xyz;
        //right
        ret.x.x = cam_trans.x.x;
        ret.y.x = cam_trans.x.y;
        ret.z.x = cam_trans.x.z;
        //up
        ret.x.y = cam_trans.y.x;
        ret.y.y = cam_trans.y.y;
        ret.z.y = cam_trans.y.z;

        ret.x.z = cam_trans.z.x;
        ret.y.z = cam_trans.z.y;
        ret.z.z = cam_trans.z.z;

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

    mat4 rotate(quat qu){
        mat4 ret = *this;
        ret.x.xyz = qu * ret.x.xyz;
        ret.y.xyz = qu * ret.y.xyz;
        ret.z.xyz = qu * ret.z.xyz;

        return ret;
    }



    float* data(){
        return &x.x;
    }

    void print(){
        printf("(%f,%f,%f,%f),", x.x, x.y, x.z, x.w);
        printf("(%f,%f,%f,%f),", y.x, y.y, y.z, y.w);
        printf("(%f,%f,%f,%f)", z.x, z.y, z.z, z.w);
        printf("(%f,%f,%f,%f)", w.x, w.y, w.z, w.w);
    }

};


struct Vertex{
    vec3 pos;
    vec3 normal;
    vec2 uv;
    vec4 color;

    Vertex (vec3 p_pos, vec2 p_uv = vec2()){
        pos = p_pos;
        uv = p_uv;
    }

    Vertex(){
        
    }
};

#endif