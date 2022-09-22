#version 330 core

in vec2 uv;
out vec4 FragColor;
uniform sampler2D tex;

void main(){
    float depth = texture(tex, uv).r;
    FragColor = vec4(vec3(depth), 1.0);
}