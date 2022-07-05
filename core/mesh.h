#ifndef MESH
#define MESH

#include "core_structure.h"
#include<vector>

class Mesh
{
    
private:
    /* data */
public:
    std::vector<point> points;
    std::vector<unsigned int > indices;
    
    
    Mesh(/* args */);
    Mesh(const std::vector<point> p_points,const std::vector<unsigned int > p_indices);
    ~Mesh();

    
};

Mesh::Mesh(){

}

Mesh::Mesh(const std::vector<point> p_points,const std::vector<unsigned int> p_indices)
{
    points = p_points;
    indices = p_indices;
}

Mesh::~Mesh()
{

}

#endif

