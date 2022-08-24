#ifndef IRON_GL
#define IRON_GL

#include<driver/glad.h>
#include<iostream>

#include"../core/mesh.h"
namespace GL
{

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

GLuint create_vao_withmesh(const Mesh& p_mesh){
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*p_mesh.points.size(), p_mesh.points.data(), GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);//vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(1);//normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec3));
    glEnableVertexAttribArray(2);//uv
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2*sizeof(vec3)));
    glEnableVertexAttribArray(3);//color
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2*sizeof(vec3)+ sizeof(vec2)));
    
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
    
} // namespace GL


#endif