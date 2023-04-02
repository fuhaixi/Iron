#ifndef IRON_GPU_h
#define IRON_GPU_H

#include"object.h"
#include"iron_gl.h"
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

    void render_object(Object& obj);

    void render(const Rmesh& rm, int mode_offset = 2);

    Rmesh meshes_new(const Mesh& mesh);

    Rshader shaders_new(const char* vertex, const char* fragment);

    Rshader shaders_new_from_file(const char* vshader_file_name, const char* fshader_file_name);

    Rtexture texture_new(const Img& img);

    Rtexture cubemap_new(Img* faces);

    Rtexture texture_new(unsigned int width, unsigned int height,int format = GL_RGB, bool repeat = true, bool linear_filter = true);

    Rtexture rgb16f_tex_new(unsigned int width, unsigned int height, bool repeat = true, bool linear_filter = true);

    void renderbuff_new(uint width, uint height);

    Rtexture depth_texture_new(unsigned int width, unsigned int height);

    Rframebuff depth_framebuffer_new(Rtexture depth_map);

    Rframebuff color_frambuff_new(Rtexture color_tex0);


    //auto genarate depth buffer
    Rframebuff framebuff_new(Rtexture color_tex0, Rtexture color_tex1 = Rtexture(), bool use_depth = false);

    void use_frame(Rframebuff rf);


    void bind_tex_at(Rtexture& rt , unsigned int pos);

    void bind_cubemap_at(Rtexture& rt , unsigned int pos);               
    

    void use(Rshader shader);


    void shader_set(const std::string& name, bool value);

    void shader_set(const std::string &name, int value) ;
    void shader_set(const std::string &name, float value);

    void shader_set(const std::string &name, mat4 value);

    void shader_set(const std::string &name, vec3 vec);
    
    void shader_set_viewer(Viewer viewer);

    
    

    GPU(/* args */);
    ~GPU();
};


#endif