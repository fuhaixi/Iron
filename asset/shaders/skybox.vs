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
    vec4 pos = projection*_view*vec4(apos, 1.0);
    gl_Position = pos.xyww;
}