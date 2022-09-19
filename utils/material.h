#include "core/gpu_structure.h"
#include "core/core_structure.h"
#include<vector>

class Material
{
private:
    Rshader rshader;
    
    std::vector<bool> bool_params;
    std::vector<int> int_params;
    std::vector<float> float_params;
    std::vector<mat4> mat4_params;
    std::vector<vec3> vec3_params;
public:
    Material(/* args */);
    ~Material();
};

Material::Material(/* args */)
{
}

Material::~Material()
{
}
