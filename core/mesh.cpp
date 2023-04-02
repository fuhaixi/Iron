#include "mesh.h"

    


void Mesh::add_polygon(std::vector<vec3>& _pos_arr, std::vector<vec2>& _uv_arr, bool inverse){
    int tnum = _pos_arr.size() - 2;
    for (size_t i = 0; i < tnum; i++)
    {
        indices.push_back(pos_arr.size());

        if(inverse){
            indices.push_back(pos_arr.size()+ i+ 2);
            indices.push_back(pos_arr.size()+ i + 1);
        }
        else{
            indices.push_back(pos_arr.size()+ i+ 1);
            indices.push_back(pos_arr.size()+ i + 2);
        }
        
    }

    for (size_t i = 0; i < _pos_arr.size(); i++)
    {
        this->pos_arr.push_back(_pos_arr[i]);
        this->uv_arr.push_back(_uv_arr[i]);
    }

    col_arr.resize(this->pos_arr.size());
    normal_arr.resize(this->pos_arr.size());
    tangent_arr.resize(this->pos_arr.size());
    
}

void Mesh::add_grid(float width, float height, mat4 transform, int width_sub){

}

Mesh Mesh::quad(){
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

Mesh Mesh::box(float size, bool flip_face){
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

Mesh Mesh::plane(float width, float depth, int width_sub, int depth_sub){
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

    

    for(int i =0; i<ret.pos_arr.size(); i++){
        ret.normal_arr[i] = vec3(0,1,0);
        ret.tangent_arr[i] = vec3(0,0,1);
    }
    
    
    return ret;
}

Mesh Mesh::cubeSphere(float radius, int sub){
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

    for (int i =0; i< py.pos_arr.size(); i++)
    {
        py.pos_arr[i] = vec3(tan(py.pos_arr[i].x*PI/4), tan(py.pos_arr[i].y*PI/4), tan(py.pos_arr[i].z*PI/4));
        py.normal_arr[i] = py.pos_arr[i].normalized();
        py.pos_arr[i] = py.normal_arr[i]*radius;
    }
    
    py.clac_tangents();
    return py;
}

void Mesh::merge_with(const Mesh &other){
    int last = pos_arr.size();

    int last_size = indices.size();
    pos_arr.insert(pos_arr.end(), other.pos_arr.begin(), other.pos_arr.end());
    uv_arr.insert(uv_arr.end(), other.uv_arr.begin(), other.uv_arr.end());
    col_arr.insert(col_arr.end(), other.col_arr.begin(), other.col_arr.end());
    normal_arr.insert(normal_arr.end(), other.normal_arr.begin(), other.normal_arr.end());
    tangent_arr.insert(tangent_arr.end(), other.tangent_arr.begin(), other.tangent_arr.end());

    indices.resize(indices.size() +other.indices.size());
    for (size_t i = 0; i < other.indices.size(); i++)
    {
        indices[last_size + i] = other.indices[i] + last;
    }
    
}

void Mesh::transform_verts(mat4 transform){
    for (size_t i = 0; i < pos_arr.size(); i++)
    {
        pos_arr[i] = transform * pos_arr[i];
    }
    

}

    void Mesh::clac_tangents(){
        for(int i = 0; i< indices.size(); i+=3){
            int index0 = indices[i];
            int index1 = indices[i+1];
            int index2 = indices[i+2];
            vec3 p0 = pos_arr[index0] - pos_arr[index1];
            vec3 p1 = pos_arr[index0] - pos_arr[index2];
            vec2 uv0 = uv_arr[index0] - uv_arr[index1];
            vec2 uv1 = uv_arr[index0] - uv_arr[index2];

            vec3 T = (p0*uv1.y - p1*uv0.y)/(uv1.y*uv0.x - uv0.y*uv1.x);

            tangent_arr[index0] += T;
            tangent_arr[index1] += T;
            tangent_arr[index2] += T;
        }

        for(int i = 0; i<tangent_arr.size(); i++){
            tangent_arr[i].normalize();
        }
    }
    


Mesh::Mesh(){

}



Mesh::~Mesh()
{

}



