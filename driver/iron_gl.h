#ifndef IRON_GL_H
#define IRON_GL_H

#include "glad.h"
#include<iostream>

#include"core/mesh.h"

namespace IRON_GL
{

GLuint create_shader_program(const char* vshader_source, const char * fshader_source, const char* name = "");

GLuint create_shader_program(GLuint vshader, GLuint fshader);


GLuint create_vshader(const char* source);

GLuint create_fshader(const char* source);


GLuint create_texture(unsigned int height, unsigned int width, unsigned char* data);
void draw(GLuint VAO, size_t size);

}
#endif // IRON_GL_H