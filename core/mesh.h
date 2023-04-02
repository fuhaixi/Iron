#ifndef IRON_MESH
#define IRON_MESH

#include "core_structure.h"
#include<vector>



class Mesh
{
    
private:
    /* data */
public:
    std::vector<vec3> pos_arr;
    std::vector<color> col_arr;
    std::vector<vec2> uv_arr;
    std::vector<vec3> normal_arr;
    std::vector<vec3> tangent_arr;
    std::vector<unsigned int > indices;
    


    void add_polygon(std::vector<vec3>& _pos_arr, std::vector<vec2>& _uv_arr, bool inverse = false);

    void add_grid(float width, float height, mat4 transform, int width_sub);

    static Mesh quad();
    
    static Mesh box(float size, bool flip_face = false);

    static Mesh plane(float width, float depth, int width_sub, int depth_sub);

    static Mesh cubeSphere(float radius, int sub);

    void merge_with(const Mesh &other);

    void transform_verts(mat4 transform);

    void clac_tangents();
    
    Mesh(/* args */);
    Mesh(const std::vector<Vertex> p_points,const std::vector<unsigned int > p_indices);
    ~Mesh();

    
};


#endif

