#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include"core/core_structure.h"
#include"core/img.h"
#include"core/mesh.h"
#include"loader.h"
#include"glm/common.hpp"


const char* vshader_s = R"(
    #version 330 core
    layout (location = 0) in vec3 apos;
    layout (location = 1) in vec3 anormal;
    layout (location = 2) in vec2 auv;
    layout (location = 3) in vec4 acolor;

    out vec2 uv;
    out vec4 color;

    uniform mat4 transform;

    void main(){
        gl_Position = transform*vec4(apos, 1.0f);
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






void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else{
        printf("k:%d, scancode:%d", key, scancode);
    }
}



GLuint create_shader_program(const char* vshader_source, const char * fshader_source){
    
    GLuint vshader;
    vshader  = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, &vshader_source, NULL);
    glCompileShader(vshader);

    int vshader_success;
    char vshader_infolog[512];
    glGetShaderiv(vshader, GL_COMPILE_STATUS, &vshader_success);
    if(!vshader_success){
        glGetShaderInfoLog(vshader, 512, NULL, vshader_infolog);
        fprintf(stderr, "vshader: %s",vshader_infolog);
    }

    GLuint fshader;
    fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, &fshader_source, NULL);
    glCompileShader(fshader);
    int fshader_success;
    char fshader_infolog[512];
    glGetShaderiv(fshader, GL_COMPILE_STATUS, &fshader_success);
    if(!fshader_success){
        glGetShaderInfoLog(fshader, 512, NULL, fshader_infolog);
        fprintf(stderr, "fshader %s", fshader_infolog);
    }


    GLuint shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vshader);
    glAttachShader(shader_program, fshader);
    glLinkProgram(shader_program);
    
    int link_success;
    char link_infolog[512];
    glGetShaderiv(shader_program, GL_LINK_STATUS, &link_success);
    if(!link_success){
        glGetShaderInfoLog(shader_program, 512, NULL, link_infolog);
        fprintf(stderr, "link  error%s", link_infolog);
    }

    glDeleteShader(fshader);
    glDeleteShader(vshader);

    return shader_program;
}

GLuint create_shader_program(GLuint vshader, GLuint fshader){
    GLuint shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vshader);
    glAttachShader(shader_program, fshader);
    glLinkProgram(shader_program);
    
    int link_success;
    char link_infolog[512];
    glGetShaderiv(fshader, GL_LINK_STATUS, &link_success);
    if(!link_success){
        glGetShaderInfoLog(fshader, 512, NULL, link_infolog);
        fprintf(stderr, "link error %s", link_infolog);
    }

    return shader_program;
}


GLuint create_vshader(const char* source){
    GLuint vshader;
    vshader  = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, &source, NULL);
    glCompileShader(vshader);

    int vshader_success;
    char vshader_infolog[512];
    glGetShaderiv(vshader, GL_COMPILE_STATUS, &vshader_success);
    if(!vshader_success){
        glGetShaderInfoLog(vshader, 512, NULL, vshader_infolog);
        fprintf(stderr, "vshader: %s",vshader_infolog);
    }
    return vshader;
}

GLuint create_fshader(const char* source){
    GLuint fshader;
    fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, &source, NULL);
    glCompileShader(fshader);
    int fshader_success;
    char fshader_infolog[512];
    glGetShaderiv(fshader, GL_COMPILE_STATUS, &fshader_success);
    if(!fshader_success){
        glGetShaderInfoLog(fshader, 512, NULL, fshader_infolog);
        fprintf(stderr, "fshader %s", fshader_infolog);
    }

    return fshader;
}

GLuint create_vao_withmesh(Mesh p_mesh){
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*p_mesh.indices.size(), p_mesh.indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point)*p_mesh.points.size(), p_mesh.points.data(), GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);//vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(point), (void *)0);
    glEnableVertexAttribArray(1);//normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(point), (void*)sizeof(vec3));
    glEnableVertexAttribArray(2);//uv
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(point), (void*)(2*sizeof(vec3)));
    glEnableVertexAttribArray(3);//color
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(point), (void*)(2*sizeof(vec3)+ sizeof(vec2)));
    
    glBindVertexArray(0);

    return VAO;
};

GLuint create_texture(unsigned int height, unsigned int width, unsigned char* data){
    GLuint TBO;
    glGenTextures(1, &TBO);
    glBindTexture(GL_TEXTURE_2D, TBO);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    return TBO;
}

void draw(GLuint VAO, size_t size){
    glBindVertexArray(VAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, NULL);
}



GLFWwindow* glfw_init(){
    glfwSetErrorCallback(error_callback);
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "ERROR: Window or OpenGL context creation failed");
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSetKeyCallback(window, key_callback);

    printf("%s\n", glGetString(GL_VERSION));
    return window;
}


void init(){
    
}

int main(){
    init();

    GLFWwindow* window = glfw_init();
    GLuint shaderp = create_shader_program(vshader_s, fshader_s);
    glUseProgram(shaderp);

    std::vector<vec3> ves;
    ves.resize(4);
    
    ves[0] = vec3(0.5f , 0.5f, 0);
    ves[1] = vec3(-0.5f, 0.5f, 0);
    ves[2] = vec3(-0.5f, -0.5f, 0);
    ves[3] = vec3(0.5, -0.5, 0);
 
    unsigned int indices[6] = {0,1,2, 2,3,0};
    
    Mesh mesh = Loader::ply2mesh("./asset/untitled.ply");
    Img img = Img("./asset/Untitled.data");
    
    
    GLint64 VAO =  create_vao_withmesh(mesh);
    GLuint TBO = create_texture(img.width, img.height, img.data);
    glUniform1i(glGetUniformLocation(shaderp, "albedo"), 0);

    mat3 basis = quat(vec3(1,0,0),1)*mat3();
    mat4 trans(basis, vec3(0,0,0));

    glUniformMatrix4fv(glGetUniformLocation(shaderp, "transform"), 1, GL_FALSE, trans.data());

    
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        float ratio;
        int width;
        int height;

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0 ,width, height);

        glClear(GL_COLOR_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TBO);

        draw(VAO, mesh.indices.size());

        glfwSwapBuffers(window);

    }


    glfwDestroyWindow(window);
    glfwTerminate();

    
    // exit();
    return 0;
}
