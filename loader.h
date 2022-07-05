#include<stdio.h>
#include<string.h>
#include<vector>
#include<iostream>
#include<string>
#include"core/core_structure.h"
#include"core/mesh.h"
#include<cassert>

#define streq(a, b) strcmp(a, b)==0

using std::vector;

namespace Loader
{
    
Mesh ply2mesh(const char*file_name){
    FILE* fin = fopen(file_name, "r");
    if(fin == NULL){
        printf("no such file");
        return Mesh();
    }

    char buf[512];
    int property_num=0;
    int v_num =0;
    int f_num =0;

    while (fscanf(fin, "%s", buf)== 1){
        if(streq(buf, "end_header")) break;

        if(strcmp(buf, "vertex")==0){
            fscanf(fin, "%d", &v_num);
        }

        if(strcmp(buf, "property")==0) property_num++;

        if(strcmp(buf, "face")==0){
            fscanf(fin, "%d", &f_num);
        }
    }

    printf("property%d", property_num);

    vector<point> points;
    int count = property_num*v_num;


    for(int vi=0; vi<v_num; vi++){
        point p;
        fscanf(fin ,"%f %f %f", &p.vertex.x, &p.vertex.y, &p.vertex.z);
        fscanf(fin ,"%f %f %f", &p.normal.x, &p.normal.y, &p.normal.z);
        fscanf(fin ,"%f %f", &p.uv.x, &p.uv.y);
        vec4i color;
        fscanf(fin ,"%d %d %d %d", &color.x, &color.y, &color.z, &color.w);
        p.color = color.byte2float();
        points.push_back(p);
    }
    

    vector<unsigned int> indices;
    for(int i=0; i<f_num; i++){
        
        int poly;
        fscanf(fin,"%d", &poly);

        vector<int> polygon;
        for(int vi=0; vi<poly; vi++){
            int index;
            fscanf(fin,"%d", &index);
            polygon.push_back(index);
        }

        for(int vi=1; vi<poly-1; vi++){
            indices.push_back(polygon[0]);
            indices.push_back(polygon[vi]);
            indices.push_back(polygon[vi+1]);
        }
    }

    


    Mesh mesh= Mesh(points, indices);

    
    return mesh;
}
    
} 




void load_obj2mesh(const char* file_name){

    FILE* fin = fopen(file_name, "r");
    
    
    if(fin == NULL){
        printf("no such file");
        return;
    }

    char buf[100];
    char ch;
    vector<vec3> vertex_array;
    vector<vec3> normal_array;
    vector<vec2> uv_array;
    vector<float> vertex_array_buffer;

   
    while (fscanf(fin, "%s", buf)== 1)
    {
        if(strcmp(buf, "#")==0){
            // printf("buf:%s " ,buf);
            while( ch =getc(fin) !='\n'){
                printf("%c", ch);
            };
        }
        else if(strcmp(buf, "v")==0){//vertex
            vec3 vec;
            fscanf(fin, "%f %f %f", &vec.x, &vec.y, &vec.z);
            vertex_array.push_back(vec);
        }
        else if(strcmp(buf, "vn")==0){//normal
            vec3 vec;
            fscanf(fin, "%f %f %f", &vec.x, &vec.y, &vec.z);
            normal_array.push_back(vec);

        }
        else if(strcmp(buf, "vt")==0){//uv
            vec2 vec;
            fscanf(fin, "%f %f", &vec.x, &vec.y);
            uv_array.push_back(vec);
        }
        else if(strcmp(buf, "f")==0){//face
            
            // fscanf(fin, "%d/%d/%d %d/%d/%d %d/%d/%d", &a, &b, &c);
            
        }
        else{
            printf("%s", buf);
        }
        
        // printf("%s ", buf);
    }
    

    // do{
        
    //     fscanf(fin, "%s", buf);

        
        
    // }while(ch != EOF);

    fclose(fin);
    
    
    return;

    
}