#version 330 core
layout (location = 0) in vec3 apos;
layout (location = 1) in vec4 acolor;
layout (location = 2) in vec2 auv;
layout (location = 3) in vec3 anormal;
layout (location = 4) in vec3 atangent;


out vec2 uv;
out vec4 color;
out vec3 normal;
out mat3 TBN;
out vec3 frag_pos;
out vec4 frag_pos_light_space;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;

uniform mat4 light_view;
uniform mat4 light_projection;

uniform mat4 projection;

void main(){
    gl_Position = projection*view*model*vec4(apos, 1.0);
    uv = auv;
    color = acolor;
    normal = (model *vec4(anormal, 0)).xyz;

    vec3 T = (model*vec4(atangent, 0)).xyz;
    vec3 B = cross(normal, T);

    TBN = mat3( T,B,normal);

    frag_pos = (model * vec4(apos, 1.0)).xyz;
    frag_pos_light_space = light_projection*light_view*model*vec4(apos, 1.0);
}