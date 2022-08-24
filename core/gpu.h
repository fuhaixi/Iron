#ifndef IRON_GPU
#define IRON_GPU

#include"object.h"
#include"driver/gl.h"
#include<vector>
#include"gpu_structure.h"
#include "img.h"

class GPU
{
private:
    std::vector<Rmesh> meshes;
    std::vector<Rshader> shaders;
    std::vector<Rtexture> textures;

public:
    void render_object(Object& obj){
        glUseProgram(obj.rshader.gid);
        glBindVertexArray(obj.rmesh.gid);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, obj.rmesh.size, GL_UNSIGNED_INT, NULL);
    }

    void render(const Rmesh& rm, const Rshader& rs){
        glUseProgram(rs.gid);

        GL::draw(rm.gid, rm.size);
    }

    Rmesh meshes_new(const Mesh& mesh){
        unsigned int id = GL::create_vao_withmesh(mesh);
        Rmesh rm;
        rm.gid = id;
        rm.size = mesh.indices.size();
        meshes.push_back(rm);

        return rm;
    }

    Rshader shaders_new(const char* vertex, const char* fragment){
        uint id = GL::create_shader_program(vertex, fragment);
        Rshader rs;
        rs.gid = id;
        shaders.push_back(rs);
        
        return rs;
    }

    Rtexture texture_new(const Img& img){
        uint id = GL::create_texture(img.width, img.height, img.data);
        Rtexture rt;
        rt.gid = id;
        textures.push_back(rt);

        return rt;
    }


    void bind_tex_at(Rtexture& rt , unsigned int pos){
        
        glActiveTexture(GL_TEXTURE0 + pos);
        glBindTexture(GL_TEXTURE_2D, rt.gid);
    }

    void setBool(Rshader& shader,const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(shader.gid, name.c_str()), (int)value); 
    }
    
    // ------------------------------------------------------------------------
    void setInt(Rshader& shader,const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(shader.gid, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setFloat(Rshader& shader,const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(shader.gid, name.c_str()), value); 
    }

    void setMat4(Rshader& shader,const std::string &name, mat4 value) const
    {
        
        glUniformMatrix4fv(glGetUniformLocation(shader.gid, name.c_str()), 1, GL_FALSE, value.data());
    }




    


    
    

    GPU(/* args */){

    }
    ~GPU(){

    }
};


#endif