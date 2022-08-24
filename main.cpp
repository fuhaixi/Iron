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


const char* vshader_s = R"(
    #version 330 core
    layout (location = 0) in vec3 apos;
    layout (location = 1) in vec3 anormal;
    layout (location = 2) in vec2 auv;
    layout (location = 3) in vec4 acolor;


    out vec2 uv;
    out vec4 color;

    uniform mat4 transform;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main(){
        gl_Position = projection*view*model*vec4(apos, 1.0f);
        uv = auv;
        color = acolor;
    }
)";

const char* fshader_s= R"(
    #version 330 core
    out vec4 FragColor;
    in vec2 uv;
    in vec4 color;

    uniform sampler2D albedo;
    void main(){
        FragColor = texture(albedo, uv);
        //FragColor = vec4(uv, 1.0, 1.0);
    }
)";


mat4 view(mat3(), vec3(0,0,-5));

double last_time;
double delta_time;
double now_time;


void camera_control(){
    
}

void test(){
    vec3 a(1,1,1);
    quat q(vec3(0,0,1), PI/4);

    vec3 b = q*a;

    b.print();
}

int main(){
    
    test();

    OS os;
    now_time = OS::getTime();
    last_time = now_time;


    Shader shaderp (vshader_s, fshader_s);
    shaderp.use();

    

    
    Mesh mesh = Mesh::box(0.5);
    printf("%ld", mesh.indices.size());
    Img img = Img("./asset/Untitled.png");
    
    GLint64 VAO =  GL::create_vao_withmesh(mesh);
    GLuint TBO = GL::create_texture(img.width, img.height, img.data);

    shaderp.setInt("albedo", 0);


    mat3 basis = mat3();
    mat4 trans(mat3(), vec3(0,0,0));
    mat4 projection = mat4::persp(100, 0.1, 0.1, 0.1);


    shaderp.setMat4("model", trans);
    shaderp.setMat4("view", view);
    shaderp.setMat4("projection", projection);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); 
    vec2 cam_mv;


    vec2 last_cursor_pos;
    vec2 cursor_pos;
    while (true)
    {
        if(OS::get_key(256)) break;//esc


        now_time = OS::getTime();
        delta_time = now_time - last_time;
        last_time = now_time;
        
        OS::poll_event();

        OS::get_frame_buffer();
        glViewport(0, 0 ,OS::instance->window.width, OS::instance->window.height);
        mat4 trans2(quat(vec3(0,1,1).normalized(), now_time) * basis, vec3());
        
        cursor_pos = OS::get_cursor_pos();
        vec2 cursor_realtive = cursor_pos - last_cursor_pos;
        if(OS::get_mouse_button(0)){
            cam_mv += cursor_realtive * 0.02;
        }

        quat qu(vec3(1,0,0) ,cam_mv.y);
        quat qu2(vec3(0,1,0) ,cam_mv.x);

        mat4 t = view.rotate(qu*qu2);
        

        shaderp.setMat4("view", t);
        
        // shaderp.setMat4("model", trans2);
        

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TBO);


        shaderp.setMat4("model", mat4(mat3(), vec3(0,0,0)));
        shaderp.use();
        GL::draw(VAO, mesh.indices.size());

        shaderp.setMat4("model", mat4(mat3(), vec3(0,0,3)));
        shaderp.use();
        GL::draw(VAO, mesh.indices.size());

        OS::swap_buffers();

        last_cursor_pos = cursor_pos;
    }

    // exit();
    return 0;
}


