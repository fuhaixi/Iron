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

const char* vshader_s = R"(
    #version 330 core
    layout (location = 0) in vec3 apos;
    layout (location = 1) in vec3 anormal;
    layout (location = 2) in vec2 auv;
    layout (location = 3) in vec4 acolor;


    out vec2 uv;
    out vec4 color;
    out vec3 normal;
    out vec3 frag_pos;

    uniform mat4 transform;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main(){
        gl_Position = projection*view*model*vec4(apos, 1.0f);
        uv = auv;
        color = acolor;
        normal = (model *vec4(anormal, 0)).xyz;

        frag_pos = (model * vec4(apos, 1.0f)).xyz;
    }
)";

const char* color_fshader_s=R"(
    #version 330 core
    out vec4 FragColor;
    uniform vec3 color;
    void main(){
        //world space
        
        FragColor = vec4(color, 1);
        //FragColor = vec4(uv, 1.0, 1.0);
    }
)";

const char* sky_box_vshader_s=R"(
    #version 330 core
    layout (location = 0) in vec3 apos;
    layout (location = 1) in vec3 anormal;
    layout (location = 2) in vec2 auv;
    layout (location = 3) in vec4 acolor;


    out vec3 tex_coord;
    uniform mat4 view;
    uniform mat4 projection;

    void main(){
        tex_coord = apos;
        mat4 _view = view;
        _view[3].xyz = vec3(0);
        vec4 pos = projection*_view*vec4(apos, 1.0f);
        gl_Position = pos.xyzw;
       
    }
)";

const char* sky_box_fshader_s=R"(
    #version 330 core
    out vec4 FragColor;
    in vec3 tex_coord;

    uniform samplerCube sky_box;
    void main(){
        FragColor = texture(sky_box, tex_coord);
        // FragColor = vec4(1.);
    }
)";

const char* phong_fshader_s= R"(
    #version 330 core
    out vec4 FragColor;
    in vec2 uv;
    in vec4 color;
    in vec3 normal;
    in vec3 frag_pos;

    uniform vec3 light_pos;
    uniform sampler2D albedo;
    uniform vec3 light_color;
    uniform vec3 ambient;
    uniform vec3 camera_pos;

    void main(){
        //world space
        vec3 N = normalize(normal);
        vec3 L = normalize(light_pos);
        vec3 R = reflect(-L, N);
        vec3 E = normalize(camera_pos - frag_pos);

        float diffuse = max(dot(N, L), 0.0);
        float specular = pow(max(dot(R,E),0.0), 5.);
        vec3 diffuse_color = diffuse * light_color;
        vec3 specular_color = specular * vec3(0,0,1.);
        

        vec3 Color = texture(albedo, uv).xyz * (diffuse_color +specular_color + ambient) ;
        FragColor = vec4(Color, 1);
        //FragColor = vec4(uv, 1.0, 1.0);
    }
)";






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
    
    test();

    OS os;
    os.key_callback = key_callback;
    now_time = OS::getTime();
    last_time = now_time;



    Camera cam;
    cam.begin_transform = mat4(mat3(), vec3(0,0,5));
    
    GPU gpu;
    Rshader normal_shader = gpu.shaders_new(vshader_s, phong_fshader_s);
    Rshader color_shader = gpu.shaders_new(vshader_s, color_fshader_s);
    Rshader skybox_shader = gpu.shaders_new(sky_box_vshader_s, sky_box_fshader_s);


    Mesh mesh = Mesh::cubeSphere(1,10);
    Rmesh rmesh_box = gpu.meshes_new(mesh);
    Rmesh rmesh_plane = gpu.meshes_new(Mesh::plane(10,10,2,2));
    Rmesh sky_box_mesh = gpu.meshes_new(Mesh::box(1., true));
    
    Img img = Img("./asset/Untitled.png");
    Rtexture rtex = gpu.texture_new(img);

    // Img aa = Img("./asset/skybox/right.jpg");
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


    mat3 basis = mat3();
    mat4 projection = mat4::persp(100, 0.1, 0.1, 0.1);
    mat4 cam_transform;
    cam_transform = mat4(mat3(), vec3(0,0,5));



    gpu.shader_set("light_pos", vec3(3,3,3));
    gpu.shader_set("light_color", vec3(1,1,1));
    gpu.shader_set("ambient", vec3(0.2));
    

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); 
    vec2 cam_mv;


    vec2 last_cursor_pos;
    vec2 cursor_pos;

    vec3 eye(0,0,5);
    vec3 target;

    

    while (true)
    {
        if(OS::get_key(256)) break;//esc

        OS::frame_begin();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // gpu.bind_cubemap_at(cubemap, 0);

        cam._process();
        gpu.bind_tex_at(rtex, 0);
        gpu.use(skybox_shader);
        gpu.shader_set("sky_box", 0);
        gpu.shader_set("view", cam.get_view_mat());
        gpu.shader_set("projection", projection);

        gpu.render(sky_box_mesh);
        

        glViewport(0, 0 ,OS::instance->window.width, OS::instance->window.height);

        OS::frame_end();
    }

    // exit();
    return 0;
}


