#define STB_IMAGE_IMPLEMENTATION

#include <driver/gl.h>
#include<GLFW/glfw3.h>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include"core/core_structure.h"
#include"core/img.h"
#include"core/mesh.h"
#include"core/shader.h"
#include"loader.h"
#include"core/os.h"
#include<cmath>
#include "core/gpu.h"
#include "utils/camera.h"






mat4 view(mat3(), vec3(0,0,-5));

double last_time;
double delta_time;
double now_time;


void test(){
    vec3 a(1,1,1);
    quat q(vec3(0,0,1), PI/4);

    vec3 b = q*a;

    b.print();
}


int render_mode = 2;

void key_callback(int key, int scancode, int action, int mods){

    if(key == 'P' && action == 1){
        render_mode = (render_mode +1)%3;
        
    }

}


int main(){
    OS os(500, 600);
    os.key_callback = key_callback;
    now_time = OS::getTime();
    last_time = now_time;

    const int SHADOW_WIDTH = 2048;
    const int SHADOW_HEIGHT = 2048;
    

    Camera cam;
    cam.begin_transform = mat4(mat3(), vec3(0,0,5));
    cam.set_projection(100, 0.1, 1, os.window_aspect);
    
    GPU gpu;

    Rtexture depth_map = gpu.depth_texture_new(SHADOW_WIDTH, SHADOW_HEIGHT);

    Rframebuff shadow_framebuff = gpu.depth_framebuffer_new(depth_map);

   

    Rshader simple_shader =gpu.shaders_new_from_file("./asset/shaders/tex_quad.vs", "./asset/shaders/tex_quad.fs");
    Rmesh quad = gpu.meshes_new( Mesh::quad());

    Rshader normal_shader = gpu.shaders_new_from_file("./asset/shaders/basic.vs", "./asset/shaders/basic.fs");
    Rshader color_shader = gpu.shaders_new_from_file("./asset/shaders/basic.vs", "./asset/shaders/color.fs");
    Rshader skybox_shader = gpu.shaders_new_from_file("./asset/shaders/skybox.vs", "./asset/shaders/skybox.fs");
    Rshader light_shader = gpu.shaders_new_from_file("./asset/shaders/simple.vs", "./asset/shaders/empty.fs");


    Mesh mesh = Mesh::cubeSphere(1,10);
    Rmesh rmesh_box = gpu.meshes_new(mesh);
    Rmesh rmesh_plane = gpu.meshes_new(Mesh::plane(6,6,2,2));
    Rmesh sky_box_mesh = gpu.meshes_new(Mesh::box(1., true));
    Rmesh sky_box_mesh2 = gpu.meshes_new(Mesh::box(10., true));
    
    Img img = Img("./asset/Untitled.png");
    Rtexture rtex = gpu.texture_new(img);

    Img faces[6];
    faces[0] = Img("./asset/skybox/right.jpg");
    faces[1] = Img("./asset/skybox/left.jpg");

    faces[2] = Img("./asset/skybox/top.jpg");
    faces[3] = Img("./asset/skybox/bottom.jpg");
    faces[4] = Img("./asset/skybox/front.jpg");
    faces[5] = Img("./asset/skybox/back.jpg");

    Rtexture cubemap = gpu.cubemap_new(faces);

    //must use shader before set uniform
    gpu.use(normal_shader);

    gpu.shader_set("albedo", 0);

    mat4 trans(mat3(), vec3(0,0,0));
    
    vec3 light_dir = vec3(-2.0f, 4.0f, -1.0f);
    gpu.shader_set("light_color", vec3(1,1,1));
    gpu.shader_set("ambient", vec3(0.2));
    
    vec3 scene_center(0);
    mat4 light_transform = mat4::lookAt(vec3(0,3, 3), scene_center, vec3(0,1,0));
    mat4 light_view = light_transform.inv();
    mat4 light_projection =  mat4::ortho(8,.1, 3, 3);
    gpu.shader_set("light_dir", light_transform.w.xyz - scene_center);

    
    gpu.use(light_shader);
    gpu.shader_set("view", light_view);
    gpu.shader_set("projection", light_projection);

    gpu.use(color_shader);
    gpu.shader_set("color", vec3(1,1,1));
    

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); 
  
    while(true){

        if(OS::get_key(256)) break;//esc

        OS::frame_begin();
        cam.set_projection(100, 0.1, 1, os.window_aspect);


        // gpu.bind_cubemap_at(cubemap, 0);
        cam._process();

        // shadow map
        gpu.use_frame(shadow_framebuff);
        glClear(GL_DEPTH_BUFFER_BIT);

        light_transform = mat4::lookAt( vec3(sin(OS::time*.1)*3,3, cos(OS::time*.1)*3),scene_center, vec3(0,1,0));
        light_view = light_transform.inv();


        gpu.use(light_shader);
        gpu.shader_set("view", light_view);
        gpu.shader_set("projection", light_projection);

        gpu.shader_set("model", mat4());
        
        gpu.render(rmesh_box);

        gpu.shader_set("model", mat4(mat3(), vec3(0,-1,0)));
        gpu.render(rmesh_plane);

        
        gpu.use_frame(os.default_frame);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        

        //pass2
        gpu.use_frame(os.default_frame);
        gpu.bind_tex_at(rtex, 0);
        gpu.bind_tex_at(depth_map, 1);
        gpu.use(normal_shader);
        gpu.shader_set("albedo", 0);
        gpu.shader_set("shadow_map", 1);
        gpu.shader_set("light_view", light_view);
        gpu.shader_set("light_projection", light_projection);
        gpu.shader_set("light_dir", light_transform.w.xyz);
        
        gpu.shader_set("view", cam.get_view_mat());
        gpu.shader_set("projection", cam.projection);
        gpu.shader_set("camera_pos", cam.transform.w.xyz);

        gpu.shader_set("model", mat4(mat3(), vec3(0,0,0)));
        
        gpu.render(rmesh_box);

        gpu.shader_set("model", mat4(mat3(), vec3(0,-1,0)));
        gpu.render(rmesh_plane);

        //light
        gpu.use(color_shader);
        gpu.shader_set("model", light_transform);
        gpu.shader_set("view", cam.get_view_mat());
        gpu.shader_set("projection", cam.projection);
        gpu.render(rmesh_box);

        //sky box
        gpu.bind_tex_at(rtex, 0);
        gpu.use(skybox_shader);
        gpu.shader_set("sky_box", 0);
        gpu.shader_set("view", cam.get_view_mat());
        gpu.shader_set("projection", cam.projection);
        glDepthFunc(GL_LEQUAL);
        gpu.render(sky_box_mesh);
        glDepthFunc(GL_LESS);



        OS::frame_end();
    }

    // exit();
    return 0;
}


