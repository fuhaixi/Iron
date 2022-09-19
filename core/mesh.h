#ifndef IRON_MESH
#define IRON_MESH

#include "core_structure.h"
#include<vector>

class Mesh
{
    
private:
    /* data */
public:
    std::vector<Vertex> points;
    std::vector<unsigned int > indices;

    void add_polygon(std::vector<vec3>& pos_arr, std::vector<vec2>& uv_arr, bool inverse = false){
        int tnum = pos_arr.size() - 2;
        for (size_t i = 0; i < tnum; i++)
        {
            indices.push_back(points.size());
            if(inverse){
                indices.push_back(points.size()+ i+ 2);
                indices.push_back(points.size()+ i + 1);
            }
            else{
                indices.push_back(points.size()+ i+ 1);
                indices.push_back(points.size()+ i + 2);
            }
            
        }

        for (size_t i = 0; i < pos_arr.size(); i++)
        {
            Vertex v(pos_arr[i], uv_arr[i]);
            points.push_back(v);
        }
        
    }

    void add_grid(float width, float height, mat4 transform, int width_sub){

    }

    static Mesh quad(){
        Mesh ret;

        std::vector<vec2> uv_arr(4);
        uv_arr[0] = vec2(0,0);
        uv_arr[1] = vec2(1,0);
        uv_arr[2] = vec2(1,1);
        uv_arr[3] = vec2(0,1);

        std::vector<vec3> vx_arr(4);
        vx_arr[0] = vec3(-1,-1, 0);
        vx_arr[1] = vec3(1,-1,0);
        vx_arr[2] = vec3(1,1,0);
        vx_arr[3] = vec3(-1,1,0);

            
        ret.add_polygon(vx_arr, uv_arr);
        return ret;
    }
    
    static Mesh box(float size, bool flip_face = false){
        Mesh ret;
        std::vector<Vertex> points;

        std::vector<vec2> uv_arr(4);
        uv_arr[0] = vec2(0,0);
        uv_arr[1] = vec2(1,0);
        uv_arr[2] = vec2(1,1);
        uv_arr[3] = vec2(0,1);

        std::vector<vec2> vx_arr(4);
        vx_arr[0] = vec2(-1,-1);
        vx_arr[1] = vec2(1,-1);
        vx_arr[2] = vec2(1,1);
        vx_arr[3] = vec2(-1,1);
        
        for (size_t fi = 0; fi < 6; fi++){
            std::vector<vec3> vxpos_arr(4);
            for (size_t i = 0; i < 4; i++)
            {
                if(fi>=3){
                    vxpos_arr[i][fi] = -size;
                    vxpos_arr[i][fi+1] = vx_arr[i].y*size;
                    vxpos_arr[i][fi+2] = vx_arr[i].x*size;

                }
                else{
                    vxpos_arr[i][fi] = size;
                    vxpos_arr[i][fi+2] = vx_arr[i].y*size;
                    vxpos_arr[i][fi+1] = vx_arr[i].x*size;
                }
            }
            
            ret.add_polygon(vxpos_arr, uv_arr, flip_face);
        }


        return ret;
    }

    static Mesh plane(float width, float depth, int width_sub, int depth_sub){
        float unit_width = width/width_sub;
        float unit_depth = depth/depth_sub;
        float unit_uv_width = 1.0f/width_sub;
        float unit_uv_depth = 1.0f/depth_sub;

        Mesh ret;

        std::vector<vec2> uv_arr(4);
        uv_arr[0] = vec2(0,0);
        uv_arr[1] = vec2(1,0);
        uv_arr[2] = vec2(1,1);
        uv_arr[3] = vec2(0,1);

        std::vector<vec3> vx_arr(4);
        vx_arr[0] = vec3(-0.5,0,-0.5);
        vx_arr[3] = vec3(0.5,0,-0.5);
        vx_arr[2] = vec3(0.5,0,0.5);
        vx_arr[1] = vec3(-0.5,0,0.5);

        vec2 begin_pos(-width/2+unit_width/2, -depth/2+unit_depth/2);
        
        
        for (size_t di = 0; di < depth_sub; di++)
        {
            for (size_t wi = 0; wi < width_sub; wi++)
            {
                std::vector<vec3> v_arr(4);
                std::vector<vec2> u_arr(4);
                for (size_t vi = 0; vi < 4; vi++)
                {
                    //sacle
                    v_arr[vi][0] = vx_arr[vi][0] * unit_width;
                    v_arr[vi][2] = vx_arr[vi][2] * unit_depth;


                    //offset
                    v_arr[vi] += vec3(begin_pos.x + unit_width*wi, 0, begin_pos.y + unit_depth*di);
                    u_arr[vi] = vec2((v_arr[vi].x + width/2.0f)/width, (v_arr[vi].z + depth/2.0f)/depth);
                }
                ret.add_polygon(v_arr, u_arr);                
            }
        }

        for (auto &&i : ret.points)
        {
            i.normal = vec3(0,1,0);
        }
        
        return ret;
    }

    static Mesh cubeSphere(float radius, int sub){
        Mesh py = plane(1,1,sub,sub);
        Mesh ny = py;
        Mesh px = py;
        Mesh nx = py;
        Mesh pz = py;
        Mesh nz = py;

        py.transform_verts(mat4(mat3(), vec3(0,0.5,0)));
        ny.transform_verts(mat4(mat3().scaled(vec3(-1,1,1)), vec3(0,-0.5,0)));
        px.transform_verts(mat4(mat3(vec3(0,0,-1), PI/2), vec3(0.5,0,0)));
        nx.transform_verts(mat4(mat3(vec3(0,0,1), PI/2), vec3(-0.5,0,0)));
        pz.transform_verts(mat4(mat3(vec3(1,0,0), PI/2), vec3(0,0,0.5)));
        nz.transform_verts(mat4(mat3(vec3(-1,0,0), PI/2), vec3(0,0,-0.5)));
        
        py.merge_with(ny);
        py.merge_with(px);
        py.merge_with(nx);
        py.merge_with(pz);
        py.merge_with(nz);

        for (auto &&i : py.points)
        {
            i.pos = vec3(tan(i.pos.x*PI/4), tan(i.pos.y*PI/4), tan(i.pos.z*PI/4));
            i.normal = i.pos.normalized();
            i.pos = i.normal*radius;

        }
        
        

        return py;
    }

    void merge_with(const Mesh &other){
        int last = points.size();

        int last_size = indices.size();
        points.insert(points.end(), other.points.begin(), other.points.end());
        indices.resize(indices.size() +other.indices.size());
        for (size_t i = 0; i < other.indices.size(); i++)
        {
            indices[last_size + i] = other.indices[i] + last;
        }
        
    }

    void transform_verts(mat4 transform){
        for (size_t i = 0; i < points.size(); i++)
        {
            points[i].pos = transform * points[i].pos;
        }
        

    }
    
    Mesh(/* args */);
    Mesh(const std::vector<Vertex> p_points,const std::vector<unsigned int > p_indices);
    ~Mesh();

    
};

Mesh::Mesh(){

}

Mesh::Mesh(const std::vector<Vertex> p_points,const std::vector<unsigned int> p_indices)
{
    points = p_points;
    indices = p_indices;
}

Mesh::~Mesh()
{

}

#endif

