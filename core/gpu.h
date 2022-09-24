#ifndef IRON_GPU
#define IRON_GPU

#include"object.h"
#include"driver/gl.h"
#include<vector>
#include"gpu_structure.h"
#include "img.h"
#include "viewer.h"

class GPU
{
private:
    std::vector<Rmesh> meshes;
    std::vector<Rshader> shaders;
    std::vector<Rtexture> textures;
    uint shader_id;
    Rshader simple_shader;
    Rmesh quad;

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
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &EBO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*mesh.indices.size(), mesh.indices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, (sizeof(vec3)*3+ sizeof(color)+sizeof(vec2))*mesh.pos_arr.size(), NULL, GL_STATIC_DRAW);


        size_t offset = 0;
        glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vec3)*mesh.pos_arr.size(), mesh.pos_arr.data());
        size_t col_offset = offset + sizeof(vec3)*mesh.pos_arr.size();
        glBufferSubData(GL_ARRAY_BUFFER, col_offset, sizeof(color)*mesh.col_arr.size(), mesh.col_arr.data());
        size_t uv_offset = col_offset + sizeof(color)*mesh.col_arr.size();
        glBufferSubData(GL_ARRAY_BUFFER, uv_offset, sizeof(vec2)*mesh.uv_arr.size(), mesh.uv_arr.data());
        size_t normal_offset =  uv_offset + sizeof(vec2)*mesh.uv_arr.size();
        glBufferSubData(GL_ARRAY_BUFFER, normal_offset, sizeof(vec3)*mesh.normal_arr.size(), mesh.normal_arr.data());
        size_t tangent_offset = normal_offset+ sizeof(vec3)*mesh.normal_arr.size();
        glBufferSubData(GL_ARRAY_BUFFER, tangent_offset, sizeof(vec3)*mesh.tangent_arr.size(), mesh.tangent_arr.data());


        glEnableVertexAttribArray(0);//vertex
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);  

        glEnableVertexAttribArray(1);//col
        glVertexAttribPointer(1, 4, GL_BYTE, GL_TRUE, sizeof(color), (void*)(col_offset));

        glEnableVertexAttribArray(2);//uv
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)(uv_offset));

        glEnableVertexAttribArray(3);//normal
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)(normal_offset));
        
        glEnableVertexAttribArray(4);//tangent
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)(tangent_offset));

        glBindVertexArray(0);

        Rmesh rm;
        rm.gid = VAO;
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

    Rshader shaders_new_from_file(const char* vshader_file_name, const char* fshader_file_name){
        std::ifstream t(vshader_file_name);
        std::stringstream vbuffer;
        vbuffer << t.rdbuf();
        vbuffer.str().c_str();

        std::ifstream tt(fshader_file_name);
        std::stringstream fbuffer;
        fbuffer << tt.rdbuf();
        fbuffer.str().c_str();

        

        
        uint id = GL::create_shader_program(vbuffer.str().c_str(), fbuffer.str().c_str(), fshader_file_name);
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

    Rtexture texture_new(unsigned int width, unsigned int height,int format = GL_RGB, bool repeat = true, bool linear_filter = true){
        unsigned int textureColorbuffer;
        glGenTextures(1, &textureColorbuffer);
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer); 
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linear_filter? GL_LINEAR :GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linear_filter? GL_LINEAR :GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat? GL_REPEAT :GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat? GL_REPEAT :GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, 0);

        Rtexture rt;
        rt.gid = textureColorbuffer;
        rt.size = vec2i(width, height);
        textures.push_back(rt);

        return rt;
    }

    Rtexture rgb16f_tex_new(unsigned int width, unsigned int height, bool repeat = true, bool linear_filter = true){
        unsigned int textureColorbuffer;
        glGenTextures(1, &textureColorbuffer);
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linear_filter? GL_LINEAR :GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linear_filter? GL_LINEAR :GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat? GL_REPEAT :GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat? GL_REPEAT :GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, 0);

        Rtexture rt;
        rt.gid = textureColorbuffer;
        rt.size = vec2i(width, height);
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
        
        // create depth texture
        unsigned int depthMap;
        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        glBindTexture(GL_TEXTURE_2D, 0);
        Rtexture rt;
        rt.gid = depthMap;
        rt.size = vec2i(width, height);
        textures.push_back(rt);

        return rt;
    }

    Rframebuff depth_framebuffer_new(Rtexture depth_map){
        Rframebuff ret;
        unsigned int depthMapFBO;
        glGenFramebuffers(1, &depthMapFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map.gid, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ret.size = depth_map.size;
        ret.gid = depthMapFBO;
        return ret;
    }

    Rframebuff color_frambuff_new(Rtexture color_tex0){

        Rframebuff ret;
        unsigned int fbo;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_tex0.gid, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ret.size = color_tex0.size;
        ret.gid = fbo;

        return ret;
    }


    //auto genarate depth buffer
    Rframebuff framebuff_new(Rtexture color_tex0, Rtexture color_tex1 = Rtexture(), bool use_depth = false){
        Rframebuff ret;
        unsigned int fbo;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_tex0.gid, 0);
        if(color_tex1.gid != 0)
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, color_tex1.gid, 0);

        if(use_depth){
            unsigned int rboDepth;
            glGenRenderbuffers(1, &rboDepth);
            glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, color_tex0.size.x, color_tex0.size.y);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
        }

        
        if(color_tex1.gid != 0){
            unsigned int attachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
            glDrawBuffers(2, attachments);
        }



        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);



        ret.size = color_tex0.size;
        ret.gid = fbo;

        return ret;
    }




    void use_frame(Rframebuff rf){
        glViewport(0, 0, rf.size.x, rf.size.y);
        glBindFramebuffer(GL_FRAMEBUFFER, rf.gid);
        
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
    
    void shader_set_viewer(Viewer viewer){
        shader_set("view", viewer.view);
        shader_set("projectionn", viewer.projection);
    }

    
    

    GPU(/* args */){
        
        
    }
    ~GPU(){

    }
};


#endif