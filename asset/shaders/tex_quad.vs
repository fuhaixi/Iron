#version 330 core
layout (location = 0) in vec3 apos;
layout (location = 2) in vec2 auv;

out vec2 uv;

void main()
{
    gl_Position =vec4(apos, 1.0);
    uv = auv;
} 