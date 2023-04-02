#ifndef CORE_STRUCTURE_H
#define CORE_STRUCTURE_H
#include<stdio.h>
#include<math.h>

#include<string.h>
#include<iostream>

typedef unsigned int uint;

#define SHORT_U 1.525902189e-05F

#define PI 3.14159265358979323846 





float clamp(float val, float min, float max);





struct vec2{
    union 
    {
        struct{
            float x;
            float y;
        };
        float components[2];
    };
    
    

    vec2();

    vec2(float _x, float _y);

    vec2(float val);
    vec2 operator -(const vec2& other)const;

    vec2 operator +(const vec2& other)const;

    vec2 operator *(const float val);

    void operator =(const vec2& other);

    void operator +=(const vec2& other);

    float& operator [](const int index);

    void print();
};


struct vec2i{
    int x;
    int y;

    vec2i();
    vec2i(int _x, int _y);
    vec2i(int val);

    float aspect();
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
    
    

    vec3();

    vec3(float val);

    vec3(vec2 xy, float _z);
    
    vec3(float _x, float _y, float _z);

    void set(float _x, float _y, float _z);

    void normalize();

    vec3 normalized() const;

    float length();

    float length_squared();

    vec3 operator *(const vec3 other)const;

    void operator *=(const vec3 other);

    void operator /=(const vec3 other);

    vec3 operator +(const vec3 other)const;
    void operator+=(const vec3 other);

    vec3 operator -(const vec3 other)const;


    void operator -=(const vec3 other);

    vec3 operator- ()const;

    float dot(const vec3 other)const;

    vec3 cross(const vec3 p_b)const;

    vec3 operator*(float val)const;
    vec3 operator/(float val)const;

    float & operator[](const int index);

    float * data();
    

    void print();
};

float dot(vec3 a, vec3 b);

vec3 cross(vec3 a, vec3 b);

vec3 normalize(vec3 v);



struct vec3i{
    int x;
    int y;
    int z;

    vec3i();

    vec3i(int val);

    vec3i(vec2i xy, float _z);
    
    vec3i(float _x, float _y, float _z);

    void print();
};


struct vec4{
    union 
    {
        struct 
        {
           float x;
           float y;
           float z;
           
        };
        vec3 xyz;
    };
    float w;
    

    vec4();

    vec4(float _x, float _y, float _z, float _w);

    vec4(float val);

    vec4(vec3 vec, float _w);

    float dot(vec4 const& other);


    float &operator [](const int index);

    void print();
};



struct vec4i{
  int x,y,z,w;

    vec4i();

    vec4i(int val);

    vec4i(vec3i vec, float _w);

    vec4 byte2float();

};


struct color{
    union 
    {
        struct 
        {//byte order
        unsigned char a;
        unsigned char b;
        unsigned char g;
        unsigned char r;
        };
        
        unsigned int code;
    };
    
    color();

    //!Take notice that byte 
    color(unsigned int _code);

    color(float _r, float _g, float _b, float _a);

    color(int _r, int _g, int _b, int _a);


    color operator*(float val);

    vec3 to_vec3();

    vec4 to_vec4();

    void print();
};

struct mat3{
    vec3 x;
    vec3 y;
    vec3 z;

    mat3();
    mat3(vec3 _x, vec3 _y, vec3 _z);

    mat3(vec3 const& p_axis, float p_phi);

    const vec3 operator *(const vec3 vec);

    void print();

    mat3 transposed();

    void rotate(const vec3& axis, float angle);
    

    mat3 rotated(const vec3& axis, float angle);

    float tdotx(vec3 v);

    float tdoty(vec3 v);

    float tdotz(vec3 v);

    mat3 operator*(mat3 mb);

    void scale(const vec3& p_scale);

    mat3 scaled(const vec3& scale_vec);
    
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

    quat();

    void set(float _x, float _y, float _z, float _w);

    quat(float p_x, float p_y, float p_z, float p_w);

    quat(const vec3 &v0, const vec3 &v1); // shortest arc
	

    quat(vec3 axis, float angle);

    quat operator*(quat const& rhs) ;

    void inv();
    
    quat inversed();

    // quat operator *(const quat other){
        
    // }

    vec3 operator* ( vec3 const&v)const;

    mat3 operator* ( mat3 const& m)const;
    void print();

};


struct mat4{

    vec4 x;
    vec4 y;
    vec4 z;
    vec4 w;

    

    static mat4 ortho(float far, float near, float width, float height);

    static mat4 persp(float far, float near, float width, float height);
    


    static mat4 lookAt(vec3 const& eye, vec3 const& center, vec3 const& up);

    mat4();

    vec4 row_x();

    vec4 row_y();

    vec4 row_z();

    vec4 row_w();

    mat4(mat3 basis, vec3 position);

    //only inverse rotation and translation
    mat4 inv();
    void translate(vec3 translation);

    mat4 translated(vec3 translation);

    mat4 basis_rotated(quat qu);

    mat4 rotated(quat qu);

    void scale(vec3 vec);

    mat4 scaled(vec3 vec);
    

    void rotate(quat qu);

    mat3 basis();

    mat4 operator*(const mat4 other);

    vec3 operator*(const vec3& v);
    float* data();
    void print();
};

namespace LowPrecision
{
    struct uvec2_01{
        unsigned short x;
        unsigned short y;

        uvec2_01(vec2 val);

        vec2 to_vec2();

        void print();
    };

    struct vec3_01
    {
        short x;
        short y;
        short z;

        vec3_01(vec3 val);

        vec3 to_vec3();

        void print();
    };
    
}



struct  Vertex{
    vec3 pos;
    vec3 normal;
    vec2 uv;
    vec4 color;
    

    Vertex (vec3 p_pos, vec2 p_uv = vec2());

    Vertex();
};

#endif