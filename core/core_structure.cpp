#include "core_structure.h"


float clamp(float val, float min, float max){
    if(val<min) val =min;
    else if (val>max) val = max;
    
    return val;
};

vec2::vec2(){
    x=0;
    y=0;
}

vec2::vec2(float _x, float _y){
    x= _x;
    y= _y;
}

vec2::vec2(float val){
    x = val;
    y = val;
}

vec2 vec2::operator -(const vec2& other)const{
    return vec2(x-other.x, y-other.y);
}

vec2 vec2::operator +(const vec2& other)const{
    return vec2(x+other.x, y+other.y);
}

vec2 vec2::operator *(const float val){
    return vec2(x*val, y*val);
}

void vec2::operator =(const vec2& other){
    x = other.x;
    y = other.y;
}

void vec2::operator +=(const vec2& other){
    *this = *this + other;
}

float& vec2::operator [](const int index){
    return components[index%2];
}

void vec2::print(){
    printf("(%f,%f)", x, y);
}




vec2i::vec2i(){
    x=0;
    y=0;
}

vec2i::vec2i(int _x, int _y){
    x= _x;
    y= _y;
}

vec2i::vec2i(int val){
    x = val;
    y = val;
}

float vec2i::aspect(){
    return float(x)/float(y);
}



    

vec3::vec3(){
    x=0;
    y=0;
    z=0;
}

vec3::vec3(float val){
    x = val;
    y=val;
    z=val;
}

vec3::vec3(vec2 xy, float _z){
    x = xy.x;
    y= xy.y;
    z = _z;
}

vec3::vec3(float _x, float _y, float _z){
    x= _x;
    y = _y;
    z = _z;
}

void vec3::set(float _x, float _y, float _z){
    x = _x;
    y = _y;
    z = _z;
}

void vec3::normalize(){
    float len = length();
    if(len == 0){
        set(0,0,0);
        return;
    }
    x = x/len;
    y = y/len;
    z = z/len;

}

vec3 vec3::normalized() const{
    vec3 ret = *this;
    ret.normalize();
    return ret;
}

float vec3::length(){
    return sqrt(x*x +y*y +z*z);
}

float vec3::length_squared(){
    return x*x + y*y + z*z;
}

vec3 vec3::operator *(const vec3 other)const{
    return vec3(x*other.x, y*other.y, z*other.z);
}

void vec3::operator *=(const vec3 other){
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
}

void vec3::operator /=(const vec3 other){
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
}

vec3 vec3::operator +(const vec3 other)const{
    return vec3(x+other.x, y+other.y, z+other.z);
}
void vec3::operator+=(const vec3 other){
    *this = *this + other;
}

vec3 vec3::operator -(const vec3 other)const{
    return vec3(x-other.x, y-other.y, z-other.z);
}


void vec3::operator -=(const vec3 other){
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;

}

vec3 vec3::operator- ()const{
    return vec3(-x, -y, -z);
}

float vec3::dot(const vec3 other)const{
    return x*other.x + y*other.y + z * other.z;
}

vec3 vec3::cross(const vec3 p_b)const{
    vec3 ret(
        (y * p_b.z) - (z * p_b.y),
        (z * p_b.x) - (x * p_b.z),
        (x * p_b.y) - (y * p_b.x));

    return ret;
}

vec3 vec3::operator*(float val)const{


    return vec3(x*val, y*val, z*val);
}

vec3 vec3::operator/(float val)const{


    return vec3(x/val, y/val, z/val);
}

float& vec3::operator[](const int index){
    
    return components[index%3];
}

float * vec3::data(){
    return &x;
}


void vec3::print(){
    printf("{%f, %f, %f}", x,y,z);
}

float dot(vec3 a, vec3 b){
    return a.x*b.x + a.y*b.y + a.z * b.z;
}

vec3 cross(vec3 a, vec3 b){
    vec3 ret(
			(a.y * b.z) - (a.z * b.y),
			(a.z * b.x) - (a.x * b.z),
			(a.x * b.y) - (a.y * b.x));

	return ret;
}

vec3 normalize(vec3 v){
    return v.normalized();
}





vec3i::vec3i(){
    x=0;
    y=0;
    z=0;
}

vec3i::vec3i(int val){
    x = val;
    y=val;
    z=val;
}

vec3i::vec3i(vec2i xy, float _z){
    x = xy.x;
    y= xy.y;
    z = _z;
}
    
vec3i::vec3i(float _x, float _y, float _z){
    x= _x;
    y = _y;
    z = _z;
}

void vec3i::print(){
    printf("(%d, %d, %d)", x,y,z);
}





vec4::vec4(){
    xyz = vec3();
    w =0;
}

vec4::vec4(float _x, float _y, float _z, float _w){
    xyz.x = _x;
    xyz.y = _y;
    xyz.z = _z;
    w = _w;
}

vec4::vec4(float val){
    xyz.x =val;
    xyz.y =val;
    xyz.z =val;
    w =val;
}

vec4::vec4(vec3 vec, float _w){
    xyz = vec;
    w = _w;
}

float vec4::dot(vec4 const& other){
    return x*other.x + y*other.y + z*other.z + w*other.w;
}


float & vec4::operator [](const int index){
    switch (index%4)
    {
    case 0:
        return x;
    
    case 1:
        return y;
    case 2:
        return z;
    case 3:
        return w;
    }

    return x;
}

void vec4::print(){
    printf("(%f, %f, %f, %f)", x,y,z,w);
}





vec4i::vec4i(){
    x =0;
    y =0;
    z =0;
    w =0;
}

vec4i::vec4i(int val){
    x =val;
    y =val;
    z =val;
    w =val;
}

vec4i::vec4i(vec3i vec, float _w){
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = _w;
}

vec4 vec4i::byte2float(){
    vec4 color;
    color.xyz.x = x/255.f;
    color.xyz.y = y/255.f;
    color.xyz.z = z/255.f;
    color.w = w/255.f;
    return color;
}





    
    color::color(){
        code = 0;
    }

    //!Take notice that byte 
    color::color(unsigned int _code){
        code = _code;
    }

    color::color(float _r, float _g, float _b, float _a){
        
        r = _r*255;
        g = _g*255;
        b = _b*255;
        a = _a*255;
    }

    color::color(int _r, int _g, int _b, int _a){
        
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }


    color color::operator*(float val){
        color ret(
        r * val,
        g * val,
        b * val,
        a * val
        );

        return ret;
    }

    vec3 color::to_vec3(){
        vec3 ret(r/255.f, g/255.f, b/255.f);
        return ret;
    }

    vec4 color::to_vec4(){
        vec4 ret(r/255.f, g/255.f, b/255.f, a/255.f);
        return ret;
    }

    void color::print(){
       to_vec4().print();
    }


mat3::mat3(){
    x= vec3(1,0,0);
    y= vec3(0,1,0);
    z= vec3(0,0,1);
}

mat3::mat3(vec3 _x, vec3 _y, vec3 _z){
    x = _x;
    y = _y;
    z = _z;
}

mat3::mat3(vec3 const& p_axis, float p_phi){
    vec3 axis_sq(p_axis.x * p_axis.x, p_axis.y * p_axis.y, p_axis.z * p_axis.z);
    float cosine = cos(p_phi);
    x[0] = axis_sq.x + cosine * (1.0 - axis_sq.x);
    y[1] = axis_sq.y + cosine * (1.0 - axis_sq.y);
    z[2] = axis_sq.z + cosine * (1.0 - axis_sq.z);

    float sine = sin(p_phi);
    float t = 1 - cosine;

    float xyzt = p_axis.x * p_axis.y * t;
    float zyxs = p_axis.z * sine;
    y[0] = xyzt - zyxs;
    x[1] = xyzt + zyxs;

    xyzt = p_axis.x * p_axis.z * t;
    zyxs = p_axis.y * sine;
    z[0] = xyzt + zyxs;
    x[2] = xyzt - zyxs;

    xyzt = p_axis.y * p_axis.z * t;
    zyxs = p_axis.x * sine;
    z[1] = xyzt - zyxs;
    y[2] = xyzt + zyxs;
}

const vec3 mat3::operator *(const vec3 vec){
    return x*vec.x + y*vec.y + z*vec.z;
}

void mat3::print(){
    printf("(%f,%f,%f),", x.x, x.y, x.z);
    printf("(%f,%f,%f),", y.x, y.y, y.z);
    printf("(%f,%f,%f)", z.x, z.y, z.z);
}

mat3 mat3::transposed(){
    mat3 ret;
    ret = *this;
    std::swap(ret.x[1], ret.y[0]);
    std::swap(ret.x[2], ret.z[0]);
    std::swap(ret.y[2], ret.z[1]);

    return ret;
}

void mat3::rotate(const vec3& axis, float angle){
    *this = mat3(axis,angle) * (*this);
}

    

mat3 mat3::rotated(const vec3& axis, float angle){
    mat3 ret = *this;
    ret.rotate(axis, angle);
    return ret;
}

float mat3::tdotx(vec3 v){
    return vec3(x.x, y.x, z.x).dot(v);
}

float mat3::tdoty(vec3 v){
    return vec3(x.y, y.y, z.y).dot(v);
}

float mat3::tdotz(vec3 v){
    return vec3(x.z, y.z, z.z).dot(v);
}

mat3 mat3::operator*(mat3 mb){
    return mat3(
        vec3(tdotx(mb.x),tdoty(mb.x),tdotz(mb.x)),
        vec3(tdotx(mb.y), tdoty(mb.y), tdotz(mb.y)),
        vec3(tdotx(mb.z),tdoty(mb.z),tdotz(mb.z))
    );
}

void mat3::scale(const vec3& p_scale){
    
    x[0] *= p_scale.x;
    x[1] *= p_scale.x;
    x[2] *= p_scale.x;
    y[0] *= p_scale.y;
    y[1] *= p_scale.y;
    y[2] *= p_scale.y;
    z[0] *= p_scale.z;
    z[1] *= p_scale.z;
    z[2] *= p_scale.z;

}

mat3 mat3::scaled(const vec3& scale_vec){
    mat3 ret = *this;
    ret.scale(scale_vec);
    return ret;
}




quat::quat(){
    xyz = vec3(0,0,0);
    w = 1;
}

void quat::set(float _x, float _y, float _z, float _w){
    x= _x;
    y = _y;
    z = _z;
    w = _w;
    
}

quat::quat(float p_x, float p_y, float p_z, float p_w){
    x = p_x;
    y = p_y;
    z = p_z;
    w = p_w;
}

quat::quat(vec3 const&v0,  vec3 const&v1) // shortest arc
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

quat::quat(vec3 axis, float angle){
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

quat quat::operator*(quat const& rhs) {
    quat q;

    q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    q.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
    q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
    q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;

    return q;
}

void quat::inv(){
    xyz = xyz*(-1.0f);
}

quat quat::inversed(){
    quat ret = *this;
    ret.inv();
    return ret;
}

// quat operator *(const quat other){
    
// }

vec3 quat::operator* ( vec3 const& v)const{



    vec3 u(x, y, z);
    vec3 uv = u.cross(v);


    return v + ((uv * w) + u.cross(uv)) * (2.0);
}

mat3 quat::operator* ( mat3 const& m)const{
    mat3 ret;
    ret.x = *this *m.x;
    ret.y = *this *m.y;
    ret.z = *this *m.z;
    return ret;
}

void quat::print(){
    
}




    

mat4 mat4::ortho(float far, float near, float width, float height){
    mat4 ret;
    ret.x = vec4(2*near/width,0,0,0);
    ret.y = vec4(0, 2*near/height,0,0);
    ret.z = vec4(0,0,-2/(far-near), 0);
    ret.w = vec4(0,0,-(far+near)/(far-near),1);
    return ret;
}

mat4 mat4::persp(float far, float near, float width, float height){
    mat4 ret;
    ret.x = vec4(2*near/width, 0,0,0);
    ret.y = vec4(0,2*near/height,0,0);
    ret.z = vec4(0, 0,-(far+near)/(far-near),-1);
    ret.w = vec4(0, 0,-2*far*near/(far-near),0);
    return ret;
}



mat4 mat4::lookAt(vec3 const& eye, vec3 const& center, vec3 const& up)
{
    vec3 const zaxis(normalize(eye - center));
    vec3 const xaxis(normalize(cross(zaxis, up)));
    vec3 const yaxis(cross(zaxis, xaxis));

    mat4 rotation(mat3(xaxis, yaxis, zaxis), vec3());
    mat4 translation(mat3(), eye);

    mat4 ret = translation*rotation ;
    
    return ret;
}

mat4::mat4(){
    x = vec4(1.f, 0.f, 0.f, 0.f);
    y = vec4(0.f, 1.f, 0.f, 0.f);
    z = vec4(0.f, 0.f, 1.f, 0.f);
    w = vec4(0.f, 0.f, 0.f, 1.f);
}

vec4 mat4::row_x(){
    return vec4(x.x, y.x, z.x, w.x);
}

vec4 mat4::row_y(){
    return vec4(x.y, y.y, z.y, w.y);
}

vec4 mat4::row_z(){
    return vec4(x.z, y.z, z.z, w.z);
}

vec4 mat4::row_w(){
    return vec4(x.w, y.w, z.w, w.w);
}

mat4::mat4(mat3 basis, vec3 position){
    x.xyz = basis.x;
    y.xyz = basis.y;
    z.xyz = basis.z;
    x.w=0;
    y.w=0;
    z.w=0;
    w.xyz = position;
    w.w = 1;
}

//only inverse rotation and translation
mat4 mat4::inv(){
    mat4 ret;

    ret.x.xyz = vec3(x[0], y[0], z[0]);
    ret.y.xyz = vec3(x[1], y[1], z[1]);
    ret.z.xyz = vec3(x[2], y[2], z[2]);

    ret.w.xyz = mat3(ret.x.xyz, ret.y.xyz, ret.z.xyz)*(-w.xyz);
    return ret;
}

void mat4::translate(vec3 translation){
    
    w.xyz = w.xyz + translation;
    
}

mat4 mat4::translated(vec3 translation){

    mat4 ret = *this;
    ret.translate(translation);
    return ret;
}

mat4 mat4::basis_rotated(quat qu){
    mat4 ret = *this;
    ret.x.xyz = qu * ret.x.xyz;
    ret.y.xyz = qu * ret.y.xyz;
    ret.z.xyz = qu * ret.z.xyz;

    return ret;
}

mat4 mat4::rotated(quat qu){
    mat4 ret = *this;
    ret.rotate(qu);

    return ret;
}

void mat4::scale(vec3 vec){
    x.xyz = x.xyz * vec.x;
    y.xyz = y.xyz * vec.y;
    z.xyz = z.xyz * vec.z;
}

mat4 mat4::scaled(vec3 vec){
    mat4 ret = *this;
    ret.scale(vec);
    return ret;
}


void mat4::rotate(quat qu){
    
    this->x.xyz = qu * this->x.xyz;
    this->y.xyz = qu * this->y.xyz;
    this->z.xyz = qu * this->z.xyz;
    this->w.xyz = qu * this->w.xyz;
    
}

mat3 mat4::basis(){
    return mat3(x.xyz, y.xyz, z.xyz);
}

mat4 mat4::operator*(const mat4 other){
    mat4 ret;
    vec4 rx = row_x();
    vec4 ry = row_y();
    vec4 rz = row_z();
    vec4 rw = row_w();

    ret.x = vec4(rx.dot(other.x), ry.dot(other.x), rz.dot(other.x), rw.dot(other.x) );
    ret.y = vec4(rx.dot(other.y), ry.dot(other.y), rz.dot(other.y), rw.dot(other.y) );
    ret.z = vec4(rx.dot(other.z), ry.dot(other.z), rz.dot(other.z), rw.dot(other.z) );
    ret.w = vec4(rx.dot(other.w), ry.dot(other.w), rz.dot(other.w), rw.dot(other.w) );

    return ret;
}

vec3 mat4::operator*( vec3 const& v){
    return basis()*v + w.xyz;
}

float* mat4::data(){
    return &x[0];
}

void mat4::print(){
    printf("(%f,%f,%f,%f),", x[0], x[1], x[2], x[3]);
    printf("(%f,%f,%f,%f),", y[0], y[1], y[2], y[3]);
    printf("(%f,%f,%f,%f)", z[0], z[1], z[2], z[3]);
    printf("(%f,%f,%f,%f)", w[0], w[1], w[2], w[3]);
}


using namespace LowPrecision;



LowPrecision::uvec2_01::uvec2_01(vec2 val){
    //clamp to 01
    val.x = clamp(val.x, 0, 1);
    val.y = clamp(val.y, 0, 1);
    
    
    x = val.x/SHORT_U;
    y = val.y/SHORT_U;
}

vec2 LowPrecision::uvec2_01::to_vec2(){
    vec2 ret;
    ret.x = x*SHORT_U;
    ret.y = y*SHORT_U;

    return ret;
}

void LowPrecision::uvec2_01::print(){
    to_vec2().print();
}


LowPrecision::vec3_01::vec3_01(vec3 val){
    //clamp to -1 1
    val.x = clamp(val.x, -1, 1);
    val.y = clamp(val.y, -1, 1);
    val.z = clamp(val.z, -1, 1);
    const float u = 2.f/65535;

    x = val.x/u;
    y = val.y/u;
    z = val.z/u;
    
}

vec3 LowPrecision::vec3_01::to_vec3(){
    const float u = 2.f/65534;

    vec3 ret;
    ret.x = x*u;
    ret.y = y*u;
    ret.z = z*u;
    return ret;
}

void LowPrecision::vec3_01::print(){
    
    to_vec3().print();
}

    


    

Vertex::Vertex (vec3 p_pos, vec2 p_uv){
    pos = p_pos;
    uv = p_uv;
}

Vertex::Vertex(){
    
}


