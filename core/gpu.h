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
    uint shader_id;

public:
    void render_object(Object& obj){
        glUseProgram(obj.rshader.gid);
        glBindVertexArray(obj.rmesh.gid);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, obj.rmesh.size, GL_UNSIGNED_INT, NULL);
    }

    void render(const Rmesh& rm, int mode = 2){
        glBindVertexArray(rm.gid);
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT + mode);
        glDrawElements(GL_TRIANGLES, rm.size, GL_UNSIGNED_INT, NULL);
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

    Rtexture cubemap_new(Img* faces){
        Rtexture rt;

        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        for (unsigned int i = 0; i < 6; i++)
        {
           

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                        0, GL_RGB, faces[i].width, faces[i].height, 0, GL_RGB, GL_UNSIGNED_BYTE, faces[i].data
            );
                
            
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        rt.gid = textureID;
        return rt;
    }

    Rtexture texture_new(unsigned int width, unsigned int height){
        unsigned int textureColorbuffer;
        glGenTextures(1, &textureColorbuffer);
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        Rtexture rt;
        rt.gid = textureColorbuffer;
        textures.push_back(rt);

        return rt;
    }

    void renderbuff_new(uint width, uint height){
        unsigned int rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);  
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    Rtexture depth_texture_new(unsigned int width, unsigned int height){
        
        unsigned int depthMap;
        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
                    width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  

        Rtexture rt;
        rt.gid = depthMap;
        textures.push_back(rt);

        return rt;
    }




    void bind_tex_at(Rtexture& rt , unsigned int pos){
        
        glActiveTexture(GL_TEXTURE0 + pos);
        glBindTexture(GL_TEXTURE_2D, rt.gid);
    }

    void bind_cubemap_at(Rtexture& rt , unsigned int pos){
        glActiveTexture(GL_TEXTURE0 + pos);
        glBindTexture(GL_TEXTURE_CUBE_MAP, rt.gid);
                                                                
    }

    void use(Rshader shader){
        glUseProgram(shader.gid);
        shader_id = shader.gid;
    }


    void shader_set(const std::string& name, bool value){
        glUniform1i(glGetUniformLocation(shader_id, name.c_str()), (int)value); 
        
    }


    void shader_set(const std::string &name, int value) 
    { 
        glUniform1i(glGetUniformLocation(shader_id, name.c_str()), value); 

    }
    // ------------------------------------------------------------------------
    void shader_set(const std::string &name, float value) 
    { 
        glUniform1f(glGetUniformLocation(shader_id, name.c_str()), value); 
    }

    void shader_set(const std::string &name, mat4 value) 
    {
        
        glUniformMatrix4fv(glGetUniformLocation(shader_id, name.c_str()), 1, GL_FALSE, value.data());
    }

    void shader_set(const std::string &name, vec3 vec) {
        glUniform3fv(glGetUniformLocation(shader_id, name.c_str()), 1, vec.data());

    }
    


    
    

    GPU(/* args */){

    }
    ~GPU(){

    }
};


#endif